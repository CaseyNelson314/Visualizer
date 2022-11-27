#include "Field.h"


Element::Field::Field(const Font& font)
	: font(font)
	, vElement({ 10700, 12300 })
	, startArea(StartArea::left)
	, robot()
	, shootPatternScelector()
{}


/// @brief サイズ更新
/// @param parent 
/// @return 
Element::Field& Element::Field::resize(const RectF& parent) {
	vElement.resize(parent);
	return *this;
}


/// @brief 更新
/// @return 
Element::Field& Element::Field::update() {

	/// スタートゾーン切り替え
	{
		if (vElement.toPhysical(Constant::leftStartArea).leftClicked()) {
			startArea = StartArea::left;
		}
		if (vElement.toPhysical(Constant::rightStartArea).leftClicked()) {
			startArea = StartArea::right;
		}
		switch (startArea) {
		case StartArea::right: robot.setStartPos({ 9950, 11550,0 }); break;
		case StartArea::left: robot.setStartPos({ 750, 11550, 0 }); break;
		}
	}

	/// ロボット更新
	{
		const auto selectedLandingList = [&] {
			Array<LandingInterface*> list;
			for (const auto& it : landingList) {
				if (it->isSelected())
					list.push_back(it);
			}
			return list;
		}();

		const auto shooterPos = robot.getShooterPos();  /// at(0):左 at(1):右
		Array<Optional<LandingInterface*>> leftShooterPattern;
		Array<Optional<LandingInterface*>> rightShooterPattern;
		switch (selectedLandingList.size()) { // 頭悪くないかぁ？？？？？
		case 1:
			leftShooterPattern.push_back({});
			rightShooterPattern.push_back(selectedLandingList.at(0));
			leftShooterPattern.push_back(selectedLandingList.at(0));
			rightShooterPattern.push_back({});
			break;
		case 2:
			leftShooterPattern.push_back(selectedLandingList.at(0));
			rightShooterPattern.push_back(selectedLandingList.at(1));
			leftShooterPattern.push_back(selectedLandingList.at(1));
			rightShooterPattern.push_back(selectedLandingList.at(0));
			break;
		default:
			break;
		}

		/// 発射パターンの中から選択
		for (auto& shooter : selectLandingList) {
			shooter.reset();
		}
		if (leftShooterPattern.size() > 0) {

			const auto pos = robot.getFieldPos();
			shootPatternScelector +=
				vElement
				.toPhysical(Circle{ pos.x, pos.y, 2000 })
				.leftClicked();

			shootPatternScelector %= leftShooterPattern.size();
			selectLandingList.at(0) = rightShooterPattern.at(shootPatternScelector);
			selectLandingList.at(1) = leftShooterPattern.at(shootPatternScelector);
		}

		/// 発射機構の角度を更新
		const auto updateShooterAngle = [&](Robot::ShooterPosition pos) {
			if (const auto shooter = selectLandingList.at(pos))
				robot.setShooterAngle(pos, (shooter.value()->getSelectPosition() - Vec2{ robot.getFieldPos().x, robot.getFieldPos().y }).getAngle());
			else
				robot.setShooterAngle(pos, robot.getFieldPos().z);
		};

		updateShooterAngle(Robot::ShooterPosition::left);
		updateShooterAngle(Robot::ShooterPosition::right);
	}

	return *this;
}

/// @brief 着陸点更新
/// @return 
Element::Field& Element::Field::landingUpdate() {
	for (auto& landing : landingList) {
		landing->update(vElement);
	}
	return *this;
}


/// @brief ロボットの座標をセットする[ロボットから見た座標][mm]
/// @param pos 座標
Element::Field& Element::Field::setRobotPos(const Vec3& pos) {
	robot.setPos(pos);
	return *this;
}


/// @brief 発射情報 [着陸点ID,飛行距離,発射角] を取得
std::array<std::tuple<Optional<size_t>, double, double>, 2> Element::Field::getShootParameter() {
	const auto line = [&](size_t shooter, Optional<LandingInterface*> landing) {
		if (landing)
			return Line{ robot.getShooterPos().at(shooter), landing.value()->getSelectPosition() };
		else
			return Line{};
	};
	return {
		std::make_tuple(
			selectLandingList.at(0) ? selectLandingList.at(0).value()->getId() : Optional<size_t>{},
			selectLandingList.at(0) ? line(Robot::ShooterPosition::left, selectLandingList.at(0)).length() : 0.,
			selectLandingList.at(0) ? line(Robot::ShooterPosition::left, selectLandingList.at(0)).vector().getAngle() - robot.getFieldPos().z : 0.
		),
		std::make_tuple(
			selectLandingList.at(1) ? selectLandingList.at(1).value()->getId() : Optional<size_t>{},
			selectLandingList.at(1) ? line(Robot::ShooterPosition::right, selectLandingList.at(1)).length() : 0.,
			selectLandingList.at(1) ? line(Robot::ShooterPosition::right, selectLandingList.at(1)).vector().getAngle() - robot.getFieldPos().z : 0.
		)
	};
}


/// @brief 描画
Element::Field& Element::Field::draw() {

	/// フィールド描画
	{
		const double frameWidth = vElement.toPhysicalScalar(30);

		const auto drawFrame = [&](const RectF& form) {
			vElement
				.toPhysical(form)
				.drawFrame(0, frameWidth, Palette::White);
		};

		drawFrame(Constant::landingArea);
		drawFrame(Constant::leftStartArea);
		drawFrame(Constant::rightStartArea);

		switch (startArea) {
		case StartArea::right:
			vElement
				.toPhysical(Constant::rightStartArea)
				.drawFrame(0, frameWidth, Color{ 210, 120, 250 });
			break;
		case StartArea::left:
			vElement
				.toPhysical(Constant::leftStartArea)
				.drawFrame(0, frameWidth, Color{ 210, 120, 250 });
			break;
		}

		drawFrame(Constant::takeoffArea);

		const auto draw = [&](const RectF& form, Color&& color) {
			vElement
				.toPhysical(form)
				.draw(std::move(color));
		};
		draw(Constant::landingArea, Color{ 72, 72, 72 });
		draw(Constant::takeoffArea, Color{ 61, 120, 0 });
		draw(Constant::leftStartArea, Color{ 116, 98, 114 });
		draw(Constant::rightStartArea, Color{ 69, 104, 126 });
	}

	/// 着陸エリア描画
	{
		for (auto& landing : landingList) {
			landing->draw(vElement, Color{ 228, 182, 87, 200 });
		}
	}

	/// ロボット描画
	{
		robot.draw(vElement);

		/// 発射ライン描画
		const auto drawShootLine = [&](size_t shooter, Optional<LandingInterface*> landing) {
			if (landing) {
				const auto line = Line{ robot.getShooterPos().at(shooter), landing.value()->getSelectPosition() };
				const auto length = static_cast<int64>(line.length());
				/// 発射ライン描画
				vElement
					.toPhysical(line)
					.drawArrow(vElement.toPhysicalScalar(50), SizeF{ 5.0, 5.0 }, Color{ 194, 205, 255 });
				/// 飛行距離描画
				font(length)
					.drawAt(vElement.toPhysical(line.center()));
			}
		};

		for (const auto [index, shooter] : Indexed(selectLandingList)) {
			drawShootLine(index, shooter);
		}

	}

	return *this;
}
