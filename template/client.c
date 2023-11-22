#include "client.h"

#include <foxel/foxel_renderer.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static void client_linkResize(GLFWwindow* window, int width, int height)
{
	client_resize(width, height);
}
static void client_linkMouseMove(GLFWwindow* window, double x, double y)
{
	client_mousemove(x, y);
}
static void client_linkMousePress(GLFWwindow* window, int button, int action, int mods)
{
	client_mousepress(button, action, mods);
}
static void client_linkKeyPress(GLFWwindow* window, int button, int scancode, int action, int mod)
{
	client_keypress(button, action, mod);
}

void client_resize(int width, int height)
{
}
void client_mousemove(float x, float y)
{
}
void client_mousepress(int button, int action, int mods)
{
}
void client_keypress(int button, int action, int mods)
{
}

void client_update(float delta)
{
}
void client_draw()
{
}

void client_main()
{
	if (!glfwInit())
	{
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Fun", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, client_linkResize);
	glfwSetCursorPosCallback(window, client_linkMouseMove);
	glfwSetMouseButtonCallback(window, client_linkMousePress);
	glfwSetKeyCallback(window, client_linkKeyPress);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		printf("GLAD could not initiate.");
		return;
	}

	printf("ENGINE: Initializing.\n");

	glfwSwapInterval(1);
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	clock_t last = clock();
	float delta = 0;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		delta += (last - clock()) / (CLOCKS_PER_SEC / 60.0f);
		last = clock();

		if (delta >= 1)
		{
			client_update(delta);
			delta = 0;
		}

		client_draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	printf("ENGINE: Garbage cleaning.\n");

	glfwTerminate();
}

