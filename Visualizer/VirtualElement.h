#pragma once

namespace Element {

	/// @brief 仮想座標を扱う要素クラス
	class VirtualElement {

		RectF physical;         /// 実要素
		Vec2 virtualSize;       /// 仮想要素サイズ(仮想座標系)
		Vec2 virtualElementPos; /// 仮想要素座標(左上, 実座標系)
		double scaling;         /// 仮想座標から実座標に変換するときの拡大率

	public:
		/// @brief 仮想座標を扱う要素を作成
		/// @param virtualSize 仮想要素サイズ
		VirtualElement(Vec2&& virtualSize) noexcept;

		/// @brief リサイズ
		/// @param physical 実要素
		VirtualElement& resize(const RectF& physical);

		/// @brief 実要素、仮想要素を描画
		VirtualElement& drawPhysical();
		VirtualElement& drawVirtual();

		/// @brief 仮想座標から実座標に変換
		/// @param raw 
		/// @return 変換された図形
		RectF toPhysical(const RectF& raw) const;
		Circle toPhysical(const Circle& raw) const;
		Triangle toPhysical(const Triangle& raw) const;
		Vec2 toPhysical(const Vec2& raw) const;
		Line toPhysical(const Line& raw) const;

		/// @brief 実座標から仮想座標に変換
		/// @param raw 
		/// @return 変換された図形
		RectF toVirtual(const RectF& raw) const;
		Circle toVirtual(const Circle& raw) const;
		Triangle toVirtual(const Triangle& raw) const;
		Vec2 toVirtual(const Vec2& raw) const;

		/// @brief 大きさを変換
		double toPhysicalScalar(double raw) const;
		double toVirtualScalar(double raw) const;
	};
}
