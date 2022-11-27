#pragma once

/// @brief フィールド関連の定数

#include "VirtualElement.h"
#include "Landing.h"

namespace Element {

	namespace Constant {

		/// 着陸エリア
		inline Array<Landing<Circle>> spotList{
			{ Circle{ Vec2{ 3700, 5650 }, 200 }, { Vec2{ 0, 0 } }, { 1 } },  /// 左前
			{ Circle{ Vec2{ 6700, 5650 }, 200 }, { Vec2{ 0, 0 } }, { 2 } },  /// 右前
			{ Circle{ Vec2{ 2700, 7650 }, 250 }, { Vec2{ 0, 0 } }, { 3 } },  /// 左奥
			{ Circle{ Vec2{ 5200, 7650 }, 250 }, { Vec2{ 0, 0 } }, { 4 } },  /// 中心
			{ Circle{ Vec2{ 7700, 7650 }, 250 }, { Vec2{ 0, 0 } }, { 5 } },  /// 右奥
		};
		inline Array<Landing<RectF>> runwayList{
			{ RectF{ Arg::center = Vec2{ 2700, 2650 }, Vec2{ 450, 1500 } }, { Vec2{ 0, 600 } }, { 6 } },  /// 左
			{ RectF{ Arg::center = Vec2{ 7700, 2650 }, Vec2{ 450, 1500 } }, { Vec2{ 0, 600 } }, { 7 } },  /// 右
		};
		inline Array<Landing<RectF>> baseList{
			{ RectF{ Arg::center = Vec2{ 5200, 4550 }, Vec2{ 800, 400 }}, { Vec2{ -400, 0 }, Vec2{ 400, 0 } }, { 8, 9 } },  /// A
			{ RectF{ Arg::center = Vec2{ 5200, 1000 }, Vec2{ 200, 800 }}, { Vec2{ 0, 400 } }, { 10 } },  /// B
		};

		/// フィールド
		inline RectF landingArea{
			Vec2{ 1350, 150  },
			Vec2{ 8000, 9350 },
		};
		inline RectF takeoffArea{
			Vec2{ 1350, 9650 },
			Vec2{ 8000, 2500 },
		};
		inline RectF leftStartArea{
			Vec2{ 150 , 10950 },
			Vec2{ 1200, 1200  },
		};
		inline RectF rightStartArea{
			Vec2{ 9350, 10950 },
			Vec2{ 1200, 1200  },
		};
	}
}
