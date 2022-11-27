#include "Robot.h"


Element::Robot::Robot(CoordinateMode coordinateMode)
	: coordinateMode(coordinateMode)
	, shooterOffsetList{ Vec3{-205.3250, -118.545, 0}, Vec3{205.3250, -118.545, 0} }
	, offset()
	, position()
{}

/// @brief 描画
/// @param vElement
/// @return 
Element::Robot& Element::Robot::draw(const VirtualElement& vElement) {

	/// メインフレーム
	vElement
		.toPhysical(getForm())
		.rotated(position.z + Math::ToRadians(60))
		.drawFrame(3, Palette::White);

	/// 左右発射機構
	for (const auto& it : shooterOffsetList) {
		vElement
			.toPhysical(RectF{ Arg::center = toVec2(position) + toVec2(it).rotated(position.z), { 200, 300 }/*発射機構の大きさ*/ })
			.rotated(it.z)
			.drawFrame(2);
	}

	return *this;
}

/// @brief 開始座標をセット
/// @param pos
/// @return 
Element::Robot& Element::Robot::setStartPos(const Vec3& pos) {
	offset = pos;
	return *this;
}

/// @brief ロボットの現在座標をセットする
/// @param pos 現在座標
/// @return 
Element::Robot& Element::Robot::setPos(const Vec3& pos) {
	position = toFieldPos(pos);
	return *this;
}

/// @brief フィールドから見たロボットの座標を取得
/// @return 座標
Vec3 Element::Robot::getFieldPos() const {
	return position;
}

/// @brief ロボットの形を取得
/// @return ロボットの形
Triangle Element::Robot::getForm() {
	return { position.x, position.y, 730 };
}

/// @brief フィールドから見た発射機構の座標を取得
/// @return 
Array<Vec2> Element::Robot::getShooterPos() const {
	return shooterOffsetList.map([&](const Vec3& raw) {
		const auto offset = toVec2(raw).rotated(position.z);
		return Vec2{ offset.x + position.x, offset.y + position.y };
		});
}

/// @brief 発射機構の角度をセットする
/// @param pos 左右どちらか
/// @param angle 
/// @return 
Element::Robot& Element::Robot::setShooterAngle(ShooterPosition pos, double angle) {
	shooterOffsetList.at(pos).z = angle;
	return *this;
}

/// @brief ロボットから見た座標からフィールドの座標に変換する
/// @param raw 
/// @return 
Vec2 Element::Robot::toFieldPos(const Vec2& raw) const {
	switch (coordinateMode) {
	case CoordinateMode::up: return { toVec2(offset) + Vec2{ raw.x, -raw.y } };
	case CoordinateMode::down: return { toVec2(offset) + raw };
	default:return Vec2{};
	}
}

/// @brief ロボットから見た座標からフィールドの座標に変換する
/// @param raw 
/// @return 
Vec3 Element::Robot::toFieldPos(const Vec3& raw) const {
	switch (coordinateMode) {
	case CoordinateMode::up: return { offset + Vec3{ raw.x, -raw.y, raw.z } };
	case CoordinateMode::down: return { offset + raw };
	default:return Vec3{};
	}
}
Vec3 Element::Robot::toRobotPos(const Vec3& raw) const {
	switch (coordinateMode) {
	case CoordinateMode::up: return { Vec3{ raw.x, -raw.y, raw.z } - offset };
	case CoordinateMode::down: return { raw - offset };
	default:return Vec3{};
	}
}

Vec2 Element::Robot::toVec2(const Vec3& raw) const {
	return { raw.x, raw.y };
}
