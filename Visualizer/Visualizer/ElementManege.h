#pragma once

namespace Element {

	/// @brief 四角形を横に分割する
	/// @param parent 分割する四角形
	/// @param left   左分割比率
	/// @param right  右分割比率
	/// @return 分割された四角形
	std::pair<RectF, RectF> splitHorizontal(const RectF& parent, double left, double right);

	/// @brief 四角形を縦に分割する
	/// @param parent 分割する四角形
	/// @param top 	  上分割比率
	/// @param bottom 下分割比率
	/// @return 分割された四角形
	std::pair<RectF, RectF> splitVertical(const RectF& parent, double top, double bottom);

	/// @brief 四角形を横に分割する
	/// @param parent 分割する四角形
	/// @param ratios 分割比率
	/// @return 分割された四角形
	Array<RectF> splitVertical(const RectF& parent, Array<double> ratios);

	/// @brief 四角形を横に分割する
	/// @param parent 分割する四角形
	/// @param ratios 分割比率
	/// @return 分割された四角形
	Array<RectF> splitHorizontal(const RectF& parent, Array<double> ratios);

	/// @brief 指定ピクセルを基に横方向に分割 (1要素:可変,1要素:固定(親要素が閾値より下回った場合可変))
	/// @param parent 親要素
	/// @param px     固定長
	/// @return 分割された四角形
	std::pair<RectF, RectF> splitHorizontalFixedRight(const RectF& parent, double px);
	std::pair<RectF, RectF> splitHorizontalFixedLeft(const RectF& parent, double px);

	/// @brief 指定ピクセルを基に横方向に分割する (1要素:可変,1要素:固定(親要素が閾値より下回った場合可変))
	/// @param parent 親要素
	/// @param px     固定長
	/// @return 分割された四角形
	std::pair<RectF, RectF> splitVerticalFixedTop(const RectF& parent, double px);
	std::pair<RectF, RectF> splitVerticalFixedBottom(const RectF& parent, double px);

	/// @brief 親要素から内側に指定ピクセル数縮小する
	/// @param parent 親要素
	/// @param top    上間隔
	/// @param right  右間隔
	/// @param bottom 下間隔
	/// @param left   左間隔
	/// @return 縮小後の四角形
	RectF padding(const RectF& parent, double top, double right, double bottom, double left);

}
