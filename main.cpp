#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <vector>
#include <iostream>
#include <cmath>
#include "Player.hpp"
#include "Game.hpp"

int main()
{
	glfwInit();

	int count;
	GLFWmonitor ** monitors = glfwGetMonitors(&count);
	GLFWmonitor * monitor = monitors[0];
	//GLFWmonitor * monitor = glfwGetPrimaryMonitor();
	GLFWvidmode const * mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	std::shared_ptr<GLFWwindow> window(glfwCreateWindow(mode->width, mode->height, "TOR", nullptr, nullptr), glfwDestroyWindow);
    glfwMakeContextCurrent(window.get());

	glViewport(0, 0, mode->width, mode->height);
	glLoadIdentity();
	gluPerspective(90, static_cast<double>(mode->width) / static_cast<double>(mode->height), 1, 1024);
	gluLookAt(0, 0, 256, 0, 0, 0, 0, 1, 0);
	/*
	glfwSetWindowSizeCallback(window.get(),[](GLFWwindow * window, int w, int h)
	{
		glViewport(0, 0, w, h);
		glLoadIdentity();
		gluPerspective(90, static_cast<double>(w) / static_cast<double>(h), 1, 100);
		gluLookAt(0, 0, 64, 0, 0, 0, 0, 1, 0);
	});
	*/
	Game game(window);

    while(!glfwWindowShouldClose(window.get()))
	{
		glClearColor(0x30 / static_cast<double>(0xFF), 0x40 / static_cast<double>(0xFF), 0x60 / static_cast<double>(0xFF), 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		game.run();
		game.draw();
		glfwSwapBuffers(window.get());
		glfwPollEvents();
	}
	glfwTerminate();
}

