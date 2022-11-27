#pragma once

#include "LandingInterface.h"

namespace Element {

	/// @brief 着陸エリア(滑走路、ベース、スポット)
	template<class Form>
	class Landing : public LandingInterface {
		Form form;
		Array<Vec2> offset;
		Array<size_t> id;
		size_t selector;
	public:

		/// @brief 着陸エリアを生成する
		/// @param form
		/// @param offset 中心から着陸座標までのオフセット
		Landing(const Form& form, Array<Vec2>&& offsets, Array<size_t>&& id)
			: form(form)
			, offset(std::move(offsets))
			, id(std::move(id))
			, selector()
		{}

		/// @brief 更新
		/// @param vElement 
		void update(const Element::VirtualElement& vElement) override {
			/// 着陸エリアが小さいので拡大して押しやすく   ↓
			selector += vElement.toPhysical(form.stretched(850)).leftClicked();
			selector %= offset.size() + 1;
		}

		/// @brief 着陸点が選択されている場合、オフセットを加味した着陸点の座標を取得
		/// @return 
		Vec2 getSelectPosition() const override {
			if (isSelected())
				return getCenter(form) + offset.at(selector - 1);
			else {
				return {};
			}
		}

		/// @brief オフセットを加味した着陸点の座標を取得
		/// @return 
		Array<Vec2> getLandingPosition() const override {
			return offset.map([&](const Vec2& offset) {
				return getCenter(form) + offset;
			});
		}

		/// @brief 着陸点のID取得
		/// @return 
		size_t getId() const override {
			return isSelected() ? id.at(selector - 1) : size_t{};
		}

		/// @brief 着陸点が選択されているか
		/// @return 
		bool isSelected() const override {
			return selector > 0;
		}

		/// @brief 描画
		/// @param vElement 
		/// @param color 
		void draw(const Element::VirtualElement& vElement, const Color& color) const override {
			const auto resizedForm = vElement.toPhysical(form);
			resizedForm.draw(color);

			if (isSelected()) {
				resizedForm.drawFrame(0, vElement.toPhysicalScalar(50), Palette::Lightgreen);

				/// 着陸点を描画
				const auto point = vElement.toPhysical(getSelectPosition());
				Shape2D::Cross(vElement.toPhysicalScalar(100), vElement.toPhysicalScalar(50), point).draw(Palette::Red);
			}

			/// タッチできる当たり判定エリア描画
			/// vElement.toPhysical(form.stretched(850)).drawFrame();
		}
	private:
		/// @brief 中心座標を求める(四角形と円で取得方法が違うため)
		static Vec2 getCenter(const RectF& form) {
			return form.center();
		}
		static Vec2 getCenter(const Circle& form) {
			return form.center;
		}
	};

}
