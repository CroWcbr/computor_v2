# include "../include/draw_curve.hpp"
# include <iostream>
#include <limits>

static double _ft_abs_rat(double const tmp) { return tmp < 0 ? -1 * tmp : tmp; }

void draw(std::vector<double> &x, std::vector<double> &y)
{
	if (!glfwInit())
	{
		throw std::runtime_error("Can't initialize GLFW!");
	}
	double	x_min = x.front();
	double	x_max = x.back();
	double	y_max = y[0];
	for (auto i : y)
	{
		if (_ft_abs_rat(i) > y_max)
			y_max = _ft_abs_rat(i);
	}
	y_max++;
	if (y_max == std::numeric_limits<double>::infinity())
		y_max = std::numeric_limits<double>::max();
	int		width = x_max - x_min;
	int		height = width;

	GLFWwindow* pWindow = glfwCreateWindow(width, height, "Graph", nullptr, nullptr);
	if (!pWindow)
	{
		glfwTerminate();
		throw std::runtime_error("Can't initialize window");
	}
	glfwMakeContextCurrent(pWindow);

	for (size_t i = 0; i < x.size(); ++i)
	{
		x[i] /= x_max;
		y[i] /= y_max;
	}
	while (!glfwWindowShouldClose(pWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_POINTS);
		glColor3f(1.0f, 0.f, 1.0f);
		for (size_t i = 0; i < x.size(); ++i)
		{
			glVertex2d(x[i], 0);
			glVertex2d(0, x[i]);
		}

		glColor3f(1.0f, 1.0f, 1.0f);
		for (size_t i = 0; i < x.size(); ++i)
		{
			glVertex2d(x[i], y[i]);
		}
		glEnd();

		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}
	glfwTerminate();
}
