// main.cpp
// Application entry point.

#include "Profiling/Breakpoint.hpp"
#include "Callbacks.hpp"
#include "../CheckeredFloor.hpp"

int main(void)
{
	CG::Logger::Init();

	CG::Renderer renderer("Checker board", 1920, 1080);
	CG::GUI gui(renderer.window(), CG::GUI::Style::DARK);
	CG::CheckeredFloor floor(50, 20);
	CG::ShaderLoader blueCheckerShader;
	CG::ShaderLoader lightBlueCheckerShader;
	CG::ShaderLoader cubeShader;

	CG::NoClipCameraController controller(
		renderer.window(),
		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.f)
	);
	controller.speed = 0.1f;

	std::unique_ptr<CG::AShape> cube = std::make_unique<CG::Cube>(
		glm::vec3(0.f, 1.f, -3.f),
		glm::vec3(0.f),
		glm::vec3(1.f)
	);

	blueCheckerShader.load("./res/shaders/checker.shader");
	blueCheckerShader.attach("triangle");
	blueCheckerShader.attach("color_blue");
	blueCheckerShader.createExecutable();

	lightBlueCheckerShader.load("./res/shaders/checker.shader");
	lightBlueCheckerShader.attach("triangle");
	lightBlueCheckerShader.attach("color_light_blue");
	lightBlueCheckerShader.createExecutable();

	cubeShader.load("./res/shaders/square.shader");
	cubeShader.attach("triangle");
	cubeShader.attach("color");
	cubeShader.createExecutable();

	renderer.registerKeyBindingCallback(GLFW_KEY_ESCAPE, escape_callback);
	renderer.registerKeyBindingCallback(GLFW_KEY_SPACE, spacebar_callback);

	float deltaTime = 0.f;
	float lastFrame = 0.f;
	bool _fpsMode = false;

	while (!renderer.windowShouldClose()) {

		float currentFrame = (float)glfwGetTime();

		// computing deltatime;
		deltaTime = currentFrame - deltaTime;
		lastFrame = currentFrame;

		controller.update(deltaTime);

		renderer.pollEvents();
		gui.newFrame();
		renderer.clear();

		// updating the fps mode.
		if (glfwGetMouseButton(renderer.window(), GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
			_fpsMode = !_fpsMode;
			if (_fpsMode)
				glfwSetInputMode(renderer.window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			else
				glfwSetInputMode(renderer.window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		const auto& board = floor.board();

		// Rendering the floor.
		for (size_t x = 0, it = 0; x < floor.nsquare(); ++x, it += floor.nsquare()) {
			for (size_t z = 0, i = x; z < floor.nsquare(); ++z, ++i) {

				int idx = it + z;

				if (i % 2 == 1) {
					blueCheckerShader.setUniform("u_mvp", controller.view() * board[idx]->transform.model());
					renderer.draw(*(board[idx]), blueCheckerShader);
				} else {
					lightBlueCheckerShader.setUniform("u_mvp", controller.view() * board[idx]->transform.model());
					renderer.draw(*(board[idx]), lightBlueCheckerShader);
				}
			}
		}

		// rendering the cube.
		cubeShader.setUniform("u_mvp", controller.view() * cube->transform.model());
		renderer.draw(*cube, cubeShader);

		gui.drawDebugUI();
		gui.renderGUI();
		renderer.swapBuffers();
	}

	return 0;
}