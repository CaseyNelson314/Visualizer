#pragma once

#include "Button.h"
#include "ElementManege.h"
#include "SerialManeger.h"

namespace Element {

	/// @brief 浮動コントローラ
	class FloatingController {
	public:
		enum class SpeedCtrl {
			right,
			left
		};
	private:
		const Font& font;
		const Font buttonFont;

		RectF parent;

		SpeedCtrl speedCtrlPosition;

		Button<String> buttonSpeedUp;
		Button<String> buttonSpeedDown;
		Button<String> buttonRight;
		Button<String> buttonLeft;

		Button<Texture> buttonUp;
		Button<Texture> buttonDown;
		Button<Texture> buttonRelease;

		Vec2 buttonTitleSpeed;
		Vec2 buttonTitleDir;

		Circle returnButton;

		bool grab;

	public:

		FloatingController(Vec2&& initPos, SpeedCtrl speedCtrlPosition, const Font& font)
			: font(font)
			, buttonFont(23)
			, parent(Arg::center = std::move(initPos), Vec2{ 530, 400 })
			, speedCtrlPosition(speedCtrlPosition)
			, buttonSpeedUp(buttonFont, U"▲")
			, buttonSpeedDown(buttonFont, U"▼")
			, buttonRight(buttonFont, U"▶")
			, buttonLeft(buttonFont, U"◀")
			, buttonUp(
				speedCtrlPosition == SpeedCtrl::left  ? Texture{ 0xf2f9_icon, 30 } :
				speedCtrlPosition == SpeedCtrl::right ? Texture{ 0xe4bd_icon, 30 } :
				Texture{}
			)
			, buttonDown(Texture{ 0xf079_icon, 30 })
			, buttonRelease(Texture{ 0xe22d_icon, 30 })
			, buttonTitleSpeed()
			, buttonTitleDir()
			, returnButton()
			, grab()
		{}

		/// @brief 更新
		/// @return ボタン入力
		Com::SerialManeger::WriteDataFrame::Shooter update() {
			/// ドラッグ処理
			{
				if (grab) {
					parent.moveBy(Cursor::Delta());
				}
				if (parent.leftClicked()) {
					grab = true;
				}
				else if (MouseL.up()) {
					grab = false;
				}
				if (grab || parent.mouseOver()) {
					Cursor::RequestStyle(CursorStyle::Hand);
				}
			}

			const auto element = parent.stretched(-10);

			const auto [dir, speed] = [&] {
				switch (speedCtrlPosition) {
				case SpeedCtrl::left:
					return splitHorizontalFixedRight(element, 125);
				case SpeedCtrl::right: {
					const auto [speed, dir] = splitHorizontalFixedLeft(element, 125);
					return std::make_pair(dir, speed);
				}
				default:
					return std::make_pair(RectF{}, RectF{});
				}
			}();

			/// ボタンの要素(3*3)を生成
			Array<RectF> dirButton;
			for (const auto& horizontal : splitHorizontal(dir, { 1, 1, 1 })) {
				for (const auto& grid : splitVertical(horizontal, { 1, 1, 1 })) {
					dirButton.push_back(grid);
				}
			}
			buttonUp.resize(dirButton.at(3).stretched(-20));
			buttonRight.resize(dirButton.at(7).stretched(-20));
			buttonDown.resize(dirButton.at(5).stretched(-20));
			buttonLeft.resize(dirButton.at(1).stretched(-20));
			buttonTitleDir = dirButton.at(4).center();

			const auto speedButton = splitVertical(speed.stretched(-20), { 1, 2, 1 });
			buttonSpeedUp.resize(speedButton.at(0));
			buttonSpeedDown.resize(speedButton.at(2));
			buttonTitleSpeed = speedButton.at(1).center();

			switch (speedCtrlPosition) {
			case SpeedCtrl::left: buttonRelease.resize(dirButton.at(6).stretched(-20)); break;
			case SpeedCtrl::right: buttonRelease.resize(dirButton.at(0).stretched(-20)); break;
			}

			/// シーン外に出た場合外枠に円を出現させ、押下することでその座標に復帰させる
			if (const auto point = Line{ Scene::Center(), parent.center() }.intersectsAt(Scene::Rect().stretched(-40))) {
				returnButton = {};
				for (auto& it : *point) {
					returnButton = Circle{ it, 40 };
				}
				if (returnButton.leftClicked()) {
					parent.setCenter(returnButton.center);
				}
			}
			return Com::SerialManeger::WriteDataFrame::Shooter{
				.upPress = buttonUp.press(),
				.rightPress = buttonRight.press(),
				.downPress = buttonDown.press(),
				.leftPress = buttonLeft.press(),
				.speedUp = buttonSpeedUp.press(),
				.speedDown = buttonSpeedDown.press(),
				.releasePress = buttonRelease.press()
			};
		}

		bool hover() const {
			return parent.mouseOver();
		}

		/// @brief 描画
		/// @return 
		FloatingController& draw() {
			parent
				.rounded(20)
				.drawShadow(Vec2{ 4, 4 }, 16, 2)
				.draw(Color{ 53, 53, 63 })
				.drawFrame(2, Color{ 53, 53, 63 });

			buttonUp.update().draw();
			buttonRight.update().draw();
			buttonDown.update().draw();
			buttonLeft.update().draw();
			buttonSpeedUp.update().draw();
			buttonSpeedDown.update().draw();
			buttonRelease.update().draw();

			font(U"ANGLE").drawAt(buttonTitleDir);
			font(U"SPEED").drawAt(buttonTitleSpeed);

			returnButton.draw(Color{ 100, 100, 100 }).drawFrame();
			return *this;
		}
	};
}
