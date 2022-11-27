#pragma once

#include "SerialManeger.h"
#include "ElementManege.h"
#include "Button.h"

namespace Element {

	/// @brief シリアルポートリスト

	class SerialListView {
		const Font& font;
		RectF parent;
		String str;
		Button<String> selector;
		Optional<String> selectPort;
		bool isLock;  /// ポート選択ロック
	public:
		SerialListView(const Font& font, String&& str)
			: parent()
			, font(font)
			, str(std::move(str))
			, selector(font, U"OPEN")
			, isLock()
		{}

		SerialListView& resize(const RectF& form) {
			parent = form;
			return *this;
		}

		Optional<String> getScelectPortName() const {
			const auto portList = getSerialPortList();
			if (std::find(portList.begin(), portList.end(), selectPort) != portList.end())
				return selectPort;
			else
				return {};
		}

		auto button() const {
			return selector;
		}

		SerialListView& lock() {
			isLock = true;
			return *this;
		}
		SerialListView& unlock() {
			isLock = false;
			return *this;
		}

		SerialListView& update() {
			const auto [title, other] = splitVerticalFixedTop(parent, 60);
			const auto [button, list] = splitVerticalFixedTop(other, 70);

			const auto portList = getSerialPortList();

			if (std::find(portList.begin(), portList.end(), selectPort) != portList.end())
				;
			else
				selectPort.reset();

			updatePort(list, portList.begin(), portList.end());

			return *this;
		}

		SerialListView& draw() {
			const auto [title, other] = splitVerticalFixedTop(parent, 60);
			const auto [button, list] = splitVerticalFixedTop(other, 70);

			font(str).drawAt(title.center());

			selector
				.resize(padding(button, 5, 15, 10, 15))
				.update()
				.draw();

			const auto portList = getSerialPortList();
			drawPort(list, portList.begin(), portList.end());

			return *this;
		}

	private:

		/// @brief ポートのリストを更新(再帰)
		/// @param element 
		/// @param it 
		/// @param end 
		void updatePort(const RectF& element, Array<String>::const_iterator&& it, Array<String>::const_iterator&& end) {
			if (it == end) return;

			const auto [div, other] = splitVerticalFixedTop(element, 70);
			const auto portElement = padding(div, 5, 15, 5, 15);

			if (portElement.mouseOver()) {
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			/// 選択されたポート名を保存
			if (not isLock && portElement.leftClicked()) {
				selectPort = *it;
			}
			updatePort(other, std::move(++it), std::move(end));
		}

		/// @brief ポートのリストを描画(再帰)
		/// @param element 
		/// @param it 
		/// @param end 
		void drawPort(const RectF& element, Array<String>::const_iterator&& it, Array<String>::const_iterator&& end) {
			if (it == end) return;

			const auto [div, other] = splitVerticalFixedTop(element, 70);
			const auto portElement = padding(div, 5, 15, 5, 15);

			const auto form = portElement.rounded(10);
			if (form.leftPressed()) {
				form.draw(Palette::Gray);
			}

			/// ポート名描画
			form.drawFrame();
			if (font.height() < portElement.h) {
				if (selectPort == *it) {
					Triangle{ portElement.leftCenter() + Vec2{ 20, 0 }, 20, 90_deg }.draw(Palette::White);
				}
				font(*it).drawAt(portElement.center());
			}
			drawPort(other, std::move(++it), std::move(end));
		}

		/// @brief  シリアルポートのリストを取得
		/// @return シリアルポート一覧
		Array<String> getSerialPortList() const {
			return System::EnumerateSerialPorts().map([](const SerialPortInfo& info) {
				return info.port;
				});
		}
	};
}
