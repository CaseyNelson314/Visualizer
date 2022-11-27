#pragma once

#include "ElementManege.h"

namespace Element {

	/// @brief 座標表示

	class Coordinate {
		const Font& font;
		RectF parent;
		String str;
		Vec3 position;
	public:
		Coordinate(const Font& font, String&& str)
			: parent()
			, font(font)
			, str(std::move(str))
			, position()
		{}

		Coordinate& setPosition(const Vec3& pos) {
			position = pos;
			return *this;
		}

		Coordinate& resize(const RectF& form) {
			parent = form;
			return *this;
		}

		Coordinate& draw() {
			/// タイトル,X,Y,Yaw で4分割
			const auto elements = splitVertical(parent.stretched(-20), { 1, 1, 1, 1 });

			font(str).drawAt(elements.front().center());
			font(U"X : {}"_fmt(static_cast<int64>(position.x))).draw(Arg::leftCenter = elements.at(1).leftCenter() + Vec2{ 20, 0 });
			font(U"Y : {}"_fmt(static_cast<int64>(position.y))).draw(Arg::leftCenter = elements.at(2).leftCenter() + Vec2{ 20, 0 });
			font(U"θ : {}°"_fmt(static_cast<int64>(Math::ToDegrees(position.z))))
				.draw(Arg::leftCenter = elements.at(3).leftCenter() + Vec2{ 20, 0 });

			parent.drawFrame();

			return *this;
		}
	};

}
