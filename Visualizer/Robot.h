#pragma once

#include "VirtualElement.h"
#include "SerialManeger.h"

namespace Element {

	class Robot {
	public:
		/// 座標モード [ y軸上正 or 下正 ]
		enum class CoordinateMode {
			up,
			down
		};

		/// 発射機構選択
		enum /*class*/ ShooterPosition {
			left,
			right
		};
	private:
		CoordinateMode coordinateMode;
		Array<Vec3> shooterOffsetList;  /// 発射機構から中心までのオフセット[mm]

		Vec3 offset;    /// ロボットのスタート座標 [フィールドから見た座標][mm]
		Vec3 position;  /// ロボットの座標　　　　 [フィールドから見た座標][mm]

	public:
		Robot(CoordinateMode coordinateMode = CoordinateMode::up);

		/// @brief 描画
		/// @param vElement
		/// @return 
		Robot& draw(const VirtualElement& vElement);

		/// @brief 開始座標をセット
		/// @param pos
		/// @return 
		Robot& setStartPos(const Vec3& pos);

		/// @brief ロボットの現在座標をセットする
		/// @param pos 現在座標
		/// @return 
		Robot& setPos(const Vec3& pos);

		/// @brief フィールドから見たロボットの座標を取得
		/// @return 座標
		Vec3 getFieldPos() const;

		/// @brief ロボットの形を取得
		/// @return ロボットの形
		Triangle getForm();

		/// @brief フィールドから見た発射機構の座標を取得
		/// @return 
		Array<Vec2> getShooterPos() const;

		/// @brief 発射機構の角度をセットする
		/// @param pos 左右どちらか
		/// @param angle 
		/// @return 
		Robot& setShooterAngle(ShooterPosition pos, double angle);

	private:

		/// @brief ロボットから見た座標からフィールドの座標に変換する
		/// @param raw 
		/// @return 
		Vec2 toFieldPos(const Vec2& raw) const;

		/// @brief ロボットから見た座標からフィールドの座標に変換する
		/// @param raw 
		/// @return 
		Vec3 toFieldPos(const Vec3& raw) const;
		Vec3 toRobotPos(const Vec3& raw) const;

		Vec2 toVec2(const Vec3& raw) const;
	};

}
