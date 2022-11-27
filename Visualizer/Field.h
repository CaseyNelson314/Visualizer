#pragma once

#include "VirtualElement.h"
#include "Landing.h"
#include "Constant.h"
#include "Robot.h"
#include "SerialManeger.h"

namespace Element {

	class Field {

		/// 着陸点
		Array<LandingInterface*> landingList{
			&Constant::spotList.at(0), /// 左前
			&Constant::spotList.at(1), /// 右前
			&Constant::spotList.at(2), /// 左後
			&Constant::spotList.at(3), /// 中心
			&Constant::spotList.at(4), /// 右前
			&Constant::runwayList.at(0), /// 左
			&Constant::runwayList.at(1), /// 右
			&Constant::baseList.at(0), /// A
			&Constant::baseList.at(1), /// B
		};
		/// フィールド
		Array<RectF*> fieldList{
			&Constant::landingArea,
			&Constant::leftStartArea,
			&Constant::rightStartArea,
			&Constant::takeoffArea,
		};

		/// 開始位置
		enum class StartArea : uint8 {
			right,
			left
		} startArea;

		const Font& font;

		VirtualElement vElement;
		Robot robot;
		std::array<Optional<LandingInterface*>, 2> selectLandingList;
		size_t shootPatternScelector;

	public:
		Field(const Font& font);

		/// @brief サイズ更新
		/// @param parent 
		/// @return 
		Field& resize(const RectF& parent);

		/// @brief 更新
		/// @return 
		Field& update();

		Field& landingUpdate();

		/// @brief ロボットの座標をセットする[ロボットから見た座標][mm]
		/// @param pos 座標
		Field& setRobotPos(const Vec3& pos);

		/// @brief 発射情報 [着陸点ID,飛行距離,発射角] を取得
		std::array<std::tuple<Optional<size_t>, double, double>, 2> getShootParameter();

		/// @brief 描画
		Field& draw();

	};
}
