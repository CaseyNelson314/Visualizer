#pragma once

#include "ElementManege.h"

#include "Field.h"
#include "Coordinate.h"
#include "FloatingController.h"

#include "SerialManeger.h"
#include "SerialListView.h"

#define VISUALIZER_DEBUG_MODE /// キーボード > 座標入力

namespace Element {

	class Visualizer {
		const Font font;
		Com::SerialManeger serial;

		Field field;
		Coordinate currentCoordinate;
		SerialListView portList;
		FloatingController controllerLeft;
		FloatingController controllerRight;

		RectF portElement;

		bool isFullscreen;
	public:
		Visualizer();

		/// @brief 初期設定
		static void init();

		/// @brief 描画サイズ更新
		/// @param parent 親要素
		Visualizer& resize(const RectF& parent);

		/// @brief 更新
		Visualizer& update();

		/// @brief 描画
		Visualizer& draw();

		/// @brief フルスクリーン有効化 [Fキー]
		Visualizer& enableFullscreen();

		/// @brief シリアルポートを開けていないときに警告 [外枠を赤色に]
		Visualizer& enableSerialWarning();

	private:
		auto modAngleRad(double raw) -> double;
		auto getDebugPosition() -> Vec3;
	};

}
