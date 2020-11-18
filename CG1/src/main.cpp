// main.cpp
// Application entry point.

#include "Profiling/Breakpoint.hpp"
#include "Callbacks.hpp"
#include "../CheckeredFloor.hpp"

int main(void)
{
	CG::Logger::Init();

	// Creating the renderer and GUI elements.
	CG::Renderer renderer("Checker board", 1920, 1080);
	CG::GUI gui(renderer.window(), CG::GUI::Style::DARK);

	// Creating the checker board with its shaders.
	CG::CheckeredFloor floor(50, 16);
	CG::ShaderLoader blueCheckerShader;
	CG::ShaderLoader lightBlueCheckerShader;

	// Creating the camera controller.
	CG::NoClipCameraController controller(
		renderer.window(),
		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.f)
	);
	controller.speed = 0.1f;

	// Creating a cube with it's shader.
	std::unique_ptr<CG::AShape> cube = std::make_unique<CG::Cube>(
		glm::vec3(0.f, 1.1f, 0.f),
		glm::vec3(0.f),
		glm::vec3(1.f)
	);
	CG::ShaderLoader cubeShader;

	// laoding shaders.
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

	// assigning callbacks for the renderer.
	renderer.registerKeyBindingCallback(GLFW_KEY_ESCAPE, escape_callback);
	
	// useful variables for frame independent code and fps mode for the controller.
	float deltaTime = 0.f;
	float lastFrame = 0.f;
	bool _fpsMode = false;

	while (!renderer.windowShouldClose()) {

		float currentFrame = (float)glfwGetTime();

		// computing deltatime;
		deltaTime = currentFrame - deltaTime;
		lastFrame = currentFrame;

		controller.update(deltaTime);

		// cleaning the screen and starting new frame for imgui.
		renderer.pollEvents();
		gui.newFrame();
		renderer.clear();

		// updating the fps mode if mouse clicked.
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

				// rendering one of two plane with a different color.
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

		// draw all elements from the gui.
		gui.drawDebugUI();
		gui.renderGUI();
		renderer.swapBuffers();
	}

	return 0;
}