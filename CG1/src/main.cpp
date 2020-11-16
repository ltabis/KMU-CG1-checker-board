// main.cpp
// Application entry point.

#include <glm/gtx/string_cast.hpp>
#include "Callbacks.hpp"
#include "Profiling/Breakpoint.hpp"

int main(void)
{
	CG::Logger::Init();

	std::shared_ptr<CG::Renderer> renderer = std::make_shared<CG::Renderer>("Test framework", 1920, 1080);
	std::shared_ptr<CG::GUI> gui = std::make_shared<CG::GUI>(renderer->window(), CG::GUI::Style::DARK);

	renderer->registerKeyBindingCallback(GLFW_KEY_ESCAPE, escape_callback);
	renderer->registerKeyBindingCallback(GLFW_KEY_SPACE, spacebar_callback);

	while (!renderer->windowShouldClose()) {

	}

	return 0;
}