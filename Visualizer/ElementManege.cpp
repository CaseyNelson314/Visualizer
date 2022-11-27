#include "ElementManege.h"

/// @brief 指定ピクセルを基に横方向に分割する
/// @param parent 親要素
/// @param px     固定長
/// @return 分割された四角形
std::pair<RectF, RectF> Element::splitHorizontalFixedRight(const RectF& parent, double px) {
	return std::make_pair(
		RectF{
			parent.pos,
			Vec2{ px < parent.w ? parent.w - px : 0, parent.h }
		},
		RectF{
			parent.pos + Vec2{ px < parent.w ? parent.w - px : 0, 0 },
			Vec2{ px < parent.w ? px : parent.w, parent.h }
		}
	);
}
std::pair<RectF, RectF> Element::splitHorizontalFixedLeft(const RectF& parent, double px) {
	return std::make_pair(
		RectF{
			parent.pos,
			Vec2{ px < parent.w ? px : parent.w, parent.h }
		},
		RectF{
			parent.pos + Vec2{ px, 0 },
			Vec2{ px < parent.w ? parent.w - px : 0, parent.h }
		}
	);
}

/// @brief 指定ピクセルを基に横方向に分割する
/// @param parent 親要素
/// @param px     固定長
/// @return 分割された四角形
std::pair<RectF, RectF> Element::splitVerticalFixedTop(const RectF& parent, double px) {
	return std::make_pair(
		RectF{
			parent.pos,
			Vec2{ parent.w, px < parent.h ? px : parent.h }
		},
		RectF{
			parent.pos + Vec2{ 0, px },
			Vec2{ parent.w, px < parent.h ? parent.h - px : 0 }
		}
	);
}
std::pair<RectF, RectF> Element::splitVerticalFixedBottom(const RectF& parent, double px) {
	return std::make_pair(
		RectF{
			parent.pos,
			Vec2{ parent.w, px < parent.h ? parent.h - px : 0 }
		},
		RectF{
			parent.pos + Vec2{ 0, px < parent.h ? parent.h - px : 0 },
			Vec2{ parent.w, px < parent.h ? px : parent.h }
		}
	);
}

/// @brief 四角形を横に分割する
/// @param parent 分割する四角形
/// @param left   左分割比率
/// @param right  右分割比率
/// @return 分割された四角形
std::pair<RectF, RectF> Element::splitHorizontal(const RectF& parent, double left, double right) {
	const double firstElementWidth = parent.w * left / (left + right);
	const double secondElementWidth = parent.w * right / (left + right);

	return std::make_pair(
		RectF{ parent.x                    , parent.y, firstElementWidth , parent.h },
		RectF{ parent.x + firstElementWidth, parent.y, secondElementWidth, parent.h }
	);
}

/// @brief 四角形を縦に分割する
/// @param parent 分割する四角形
/// @param top 	  上分割比率
/// @param bottom 下分割比率
/// @return 分割された四角形
std::pair<RectF, RectF> Element::splitVertical(const RectF& parent, double top, double bottom) {
	const double firstElementHeight = parent.h * top / (top + bottom);
	const double secondElementHeight = parent.h * bottom / (top + bottom);
	return std::make_pair(
		RectF{ parent.x, parent.y                     , parent.w, firstElementHeight },
		RectF{ parent.x, parent.y + firstElementHeight, parent.w, secondElementHeight }
	);
}

/// @brief 四角形を横に分割する
/// @param parent 分割する四角形
/// @param ratios 分割比率
/// @return 分割された四角形
Array<RectF> Element::splitVertical(const RectF& parent, Array<double> ratios) {

	double parameter = {};  /// 比母数
	for (const auto& it : ratios) {
		parameter += it;
	}

	double beginPoint = {};
	Array<RectF> children;

	for (const auto& it : ratios) {
		const auto height = parent.h * (it / parameter);
		children.push_back({
			parent.x,
			parent.y + beginPoint,
			parent.w,
			height
		});
		beginPoint += height;
	}

	return children;
}

/// @brief 四角形を横に分割する
/// @param parent 分割する四角形
/// @param ratios 分割比率
/// @return 分割された四角形
Array<RectF> Element::splitHorizontal(const RectF& parent, Array<double> ratios) {

	double parameter = {};  /// 比母数
	for (const auto& it : ratios) {
		parameter += it;
	}

	double beginPoint = {};
	Array<RectF> children;

	for (const auto& it : ratios) {
		const auto width = parent.w * (it / parameter);
		children.push_back({
			parent.x + beginPoint,
			parent.y,
			width,
			parent.h
		});
		beginPoint += width;
	}

	return children;
}


/// @brief 親要素から内側に指定ピクセル数縮小する
/// @param parent 親要素
/// @param top    上間隔
/// @param right  右間隔
/// @param bottom 下間隔
/// @param left   左間隔
/// @return 縮小後の四角形
RectF Element::padding(const RectF& parent, double top, double right, double bottom, double left) {
	return {
		parent.x + left,
		parent.y + top,
		parent.w - left - right,
		parent.h - top - bottom
	};
}
