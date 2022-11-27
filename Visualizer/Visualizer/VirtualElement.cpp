#include "stdafx.h"
#include "VirtualElement.h"

/// @brief 仮想座標を扱う要素を作成
/// @param physical 実要素
/// @param virtualSize 仮想要素サイズ
Element::VirtualElement::VirtualElement(Vec2&& virtualSize) noexcept
	: physical()
	, virtualSize(std::move(virtualSize))
	, virtualElementPos()
	, scaling()
{
}

/// @brief リサイズ
/// @param physical 実要素
Element::VirtualElement& Element::VirtualElement::resize(const RectF& parent) {
	physical = parent;

	const double physicalRatio = parent.left().length() / parent.top().length();
	const double virtualRatio = virtualSize.y / virtualSize.x;

	if (physicalRatio > virtualRatio) { /// 横の長さが限界に到達
		scaling = parent.top().length() / virtualSize.x;
	}
	else {  /// 縦の長さが限界に到達
		scaling = parent.left().length() / virtualSize.y;
	}

	virtualElementPos = parent.center() - virtualSize * 0.5 * scaling;

	return *this;
}

/// @brief 実要素、仮想要素を描画
Element::VirtualElement& Element::VirtualElement::drawPhysical() {
	physical.drawFrame();
	return *this;
}

Element::VirtualElement& Element::VirtualElement::drawVirtual() {
	toPhysical(RectF{ 0, 0, virtualSize }).drawFrame();
	return *this;
}

/// @brief 仮想座標から実座標に変換
/// @param raw 
/// @return 実座標系での図形
RectF Element::VirtualElement::toPhysical(const RectF& raw) const {
	return {
		raw.pos * scaling + virtualElementPos,
		raw.size * scaling
	};
}
Circle Element::VirtualElement::toPhysical(const Circle& raw) const {
	return {
		raw.center * scaling + virtualElementPos,
		raw.r * scaling
	};
}
Triangle Element::VirtualElement::toPhysical(const Triangle& raw) const {
	return {
		raw.p0 * scaling + virtualElementPos,
		raw.p1 * scaling + virtualElementPos,
		raw.p2 * scaling + virtualElementPos
	};
}
Vec2 Element::VirtualElement::toPhysical(const Vec2& raw) const {
	return raw * scaling + virtualElementPos;
}
Line Element::VirtualElement::toPhysical(const Line& raw) const {
	return { toPhysical(raw.begin), toPhysical(raw.end) };
}


RectF Element::VirtualElement::toVirtual(const RectF& raw) const {
	return {
		(raw.pos - virtualElementPos) / scaling,
		raw.size / scaling
	};
}
Circle Element::VirtualElement::toVirtual(const Circle& raw) const {
	return {
		(raw.center - virtualElementPos) / scaling,
		raw.r / scaling
	};
}
Triangle Element::VirtualElement::toVirtual(const Triangle& raw) const {
	return {
		(raw.p0 - virtualElementPos) / scaling,
		(raw.p1 - virtualElementPos) / scaling,
		(raw.p2 - virtualElementPos) / scaling
	};
}
Vec2 Element::VirtualElement::toVirtual(const Vec2& raw) const {
	return (raw - virtualElementPos) / scaling;
}

double Element::VirtualElement::toPhysicalScalar(double raw) const {
	return raw * scaling;
}

double Element::VirtualElement::toVirtualScalar(double raw) const {
	return raw / scaling;
}
