#pragma once

namespace Element {

	/// @brief ボタン

	template<class> class Button;

	/// ボタンタイトル:文字列
	template<>
	class Button<String> {
		const Font& font;
		RectF parent;
		String str;
	public:
		Button(const Font& font, String&& str)
			: parent()
			, font(font)
			, str(std::move(str))
		{}
		operator bool() {
			return parent.leftClicked();
		}
		bool press() const {
			return parent.leftPressed();
		}
		Button& resize(const RectF& form) {
			parent = form;
			return *this;
		}
		Button& rename(String&& name) {
			str = std::move(name);
			return *this;
		}
		Button& update() {
			if (parent.leftPressed()) {
				parent.rounded(10).draw({ Palette::Gray, 100 });
			}
			if (parent.mouseOver()) {
				Cursor::RequestStyle(CursorStyle::Hand);
			}
			return *this;
		}
		RectF getForm() const {
			return parent;
		}
		Button& draw() {
			parent.rounded(10).drawFrame();
			if (font.height() < parent.h) {
				font(str).drawAt(parent.center());
			}
			return *this;
		}
	};

	/// ボタンタイトル : テクスチャ
	template<>
	class Button<Texture> {
		RectF parent;
		Texture icon;
	public:
		Button(Texture&& icon)
			: parent()
			, icon(std::move(icon))
		{}
		operator bool() {
			return parent.leftClicked();
		}
		bool press() const {
			return parent.leftPressed();
		}
		Button& resize(const RectF& form) {
			parent = form;
			return *this;
		}
		Button& rename(Texture&& r) {
			icon = std::move(r);
			return *this;
		}
		Button& update() {
			if (parent.leftPressed()) {
				parent.rounded(10).draw({ Palette::Gray, 100 });
			}
			if (parent.mouseOver()) {
				Cursor::RequestStyle(CursorStyle::Hand);
			}
			return *this;
		}
		RectF getForm() const {
			return parent;
		}
		Button& draw() {
			parent.rounded(10).drawFrame();
			if (icon.height() < parent.h) {
				icon.drawAt(parent.center());
			}
			return *this;
		}
	};

}
