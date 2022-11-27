#include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include "Visualizer.h"

void Main() {
	Element::Visualizer::init();
	Element::Visualizer visualizer;
	while (System::Update()) {
		visualizer
			.resize(Scene::Rect())
			.update()
			.draw()
			.enableFullscreen()
			//.enableSerialWarning()
			;
	}
}
