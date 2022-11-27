#pragma once

#include "VirtualElement.h"

namespace Element {

	/// @brief 着陸エリア(スポット、滑走路、ベース)を管理するための抽象クラス

	class LandingInterface {
	public:
		virtual Array<Vec2> getLandingPosition() const = 0;
		virtual Vec2 getSelectPosition() const = 0;
		virtual bool isSelected() const = 0;
		virtual size_t getId() const = 0;
		virtual void update(const Element::VirtualElement& vElement) = 0;
		virtual void draw(const Element::VirtualElement& vElement, const Color& color) const = 0;
	};

}
