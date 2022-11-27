#include "stdafx.h"
#include "Visualizer.h"

Element::Visualizer::Visualizer()
	: font(23, Typeface::Regular, FontStyle::Italic)
	, field(font)
	, currentCoordinate(font, U"POSITION")
	, portList(font, U"SERIAL PORT")
	, controllerLeft (Vec2{  300, 500 }, FloatingController::SpeedCtrl::left , font)
	, controllerRight(Vec2{ 1200, 500 }, FloatingController::SpeedCtrl::right, font)
	, serial()
	, portElement()
	, isFullscreen()
{}

/// @brief 初期設定
void Element::Visualizer::init() {
	Window::SetStyle(WindowStyle::Sizable);
	Window::SetTitle(U"Visualizer");
	Window::SetMinimumFrameBufferSize({ 1000, 800 });
	Window::Resize({ 1500, 1100 });
	Scene::SetBackground(Color{ 43, 44, 50 });
}

/// @brief 描画サイズ更新
/// @param parent 親要素
Element::Visualizer& Element::Visualizer::resize(const RectF& parent) {

	/// フィールド要素、入力要素に分割
	const auto [fieldElement, rightInputElement] = splitHorizontalFixedRight(parent, 250);

	/// シリアル用要素、座標表示要素に分割
	const auto [portListElement, coordinateElement] = splitVerticalFixedBottom(rightInputElement, 190);

	/// フィールドと右側を分けるやつ
	portElement = portListElement;

	currentCoordinate.resize(coordinateElement);

	field.resize(fieldElement.stretched(-30));

	portList.resize(portListElement.stretched(-20));

	return *this;
}


/// @brief 更新
Element::Visualizer& Element::Visualizer::update() {

	serial.readUpdate();

	portList.update();

	/// フィールド更新
	{
		/// コントローラーを使用中に着陸点の変更をしない
		if (controllerLeft.hover() || controllerRight.hover());
		else {
			field.landingUpdate();
		}

		field.update();

		const auto pos =
#ifdef VISUALIZER_DEBUG_MODE
			getDebugPosition();
#else
			Vec3{
				static_cast<double>(serial.read().x  ),
				static_cast<double>(serial.read().y  ),
				static_cast<double>(serial.read().yaw)
		};
#endif
		field.setRobotPos(pos);
		currentCoordinate.setPosition(pos);
	}

	/// シリアル関係の更新
	{
		/// ポート関連更新
		if (serial) {
			portList.lock().button().rename(U"CLOSE");
			if (portList.button()) {
				serial.close();
			}
		}
		else {
			portList.unlock().button().rename(U"OPEN");
			if (portList.button()) {
				if (const auto portname = portList.getScelectPortName())
					serial.open(*portname);
			}
		}

		/// 送信処理
		const auto toWriteFrameParameter = [&](const std::tuple<Optional<size_t>, double, double>& r) {
			const auto& [id, length, angle] = r;
			return Com::SerialManeger::WriteDataFrame::Target{
				.id     = static_cast<uint8>(id ? *id : 0                       ),
				.length = static_cast<float>(length                             ),
				.angle  = static_cast<float>(Math::ToDegrees(modAngleRad(angle))),
			};
		};
		const auto shootParam = field.getShootParameter();
		serial.write({
			.leftTarget   = toWriteFrameParameter(shootParam.at(0)),
			.rightTarget  = toWriteFrameParameter(shootParam.at(1)),
			.leftShooter  = controllerLeft .update(),
			.rightShooter = controllerRight.update()
		});
	}

	serial.writeUpdate();
	return *this;
}


/// @brief 描画
Element::Visualizer& Element::Visualizer::draw() {
	portElement.drawFrame();
	portList.draw();
	currentCoordinate.draw();
	field.draw();
	controllerRight.draw();
	controllerLeft.draw();
	return *this;
}


/// @biref フルスクリーンを有効化 [Fキー]
Element::Visualizer& Element::Visualizer::enableFullscreen() {
	isFullscreen ^= KeyF.down();
	Window::SetFullscreen(isFullscreen);
	return *this;
}


/// @brief シリアルポートを開けていないときに警告する [外枠の色変更]
Element::Visualizer& Element::Visualizer::enableSerialWarning() {
	if (not serial) {
		Scene::Rect()
			.drawFrame(5, 0, Palette::Red);
		font(U"Serial port is not open")
			.draw(Scene::Rect().pos + Vec2{ 15, 10 }, Color{ 227, 59, 46 });
	}
	return *this;
}

/// @brief 角度[rad]-π～πの範囲にまとめる
/// @param raw 
/// @return 
auto Element::Visualizer::modAngleRad(double raw) -> double {
	raw += Math::Pi;
	raw = Fmod(raw, 2 * Math::Pi);  /// 正の数用
	raw -= 2 * Math::Pi;
	raw = Fmod(raw, 2 * Math::Pi);  /// 負の数用
	raw += Math::Pi;
	return raw;
}

/// @brief キー入力から座標を作成 [内部に座標を保持]
/// @return 
auto Element::Visualizer::getDebugPosition() -> Vec3 {
	static Vec3 pos;
	pos.x += (KeyD.pressed() - KeyA.pressed()) * Scene::DeltaTime() * 2000;
	pos.y += (KeyW.pressed() - KeyS.pressed()) * Scene::DeltaTime() * 2000;
	pos.z += (KeyE.pressed() - KeyQ.pressed()) * Scene::DeltaTime() * 2;
	pos.z = modAngleRad(pos.z);
	return pos;
}
