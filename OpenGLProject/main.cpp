#include <GLFW/glfw3.h>
#include <iostream>
#include <ctime>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cmath>
#include <math.h>


class  GeometrShape
{
public:
	GeometrShape();
	~GeometrShape();
	float ConvertToPixel(int pixel, int ScreenSize)
	{
		return (float)pixel / (float)ScreenSize;
	}

private:
};

GeometrShape::GeometrShape()
{
}

GeometrShape::~GeometrShape()
{
}
class Point : public GeometrShape
{

public:
	Point();
	~Point();
	void DrawPoint(float x, float y)
	{
		glPointSize(1);
		glBegin(GL_POINTS);
		SetColor(0.75f, 0.14f, 0.2f);
		glVertex2f(x, y);
		glEnd();
	}
	double randomSpawn(double min, double max)
	{
		return (double)(rand()) / RAND_MAX * (max - min) + min;
	}
private:
	void SetColor(float r, float g, float b)
	{
		glColor3f(r, g, b);
	}
};

Point::Point()
{
}

Point::~Point()
{
}

void drawClockFace(int numTicks, float radius)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0); // center of the clock face
	for (int i = 0; i <= numTicks; ++i) {
		float angle = i * ((2 * M_PI) / numTicks);
		glVertex2f(radius * cos(angle), radius * sin(angle));
	}
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < numTicks; ++i) {
		float angle = i * ((2 * M_PI) / numTicks);
		glVertex2f(radius * cos(angle), radius * sin(angle));
		glVertex2f(0.9 * radius * cos(angle), 0.9 * radius * sin(angle));
	}
	glEnd();
}
void drawHands(int hour, float minute, float second, float radius)
{
	const float pi = 3.14159265358979323846;
	const float secondsAngle = (second / 60.0) * (2 * pi);
	const float minutesAngle = ((minute + second / 60.0) / 60.0) * (2 * pi); 
	const float hoursAngle = (((hour + minute / 60.0f) / 12.0f) * (2.0f * pi));

	glVertex2f(0, 0);
	glVertex2f(radius * sin(hoursAngle), radius * cos(hoursAngle));
	glVertex2f(0, 0);
	glVertex2f(radius * sin(minutesAngle), radius * cos(minutesAngle));
	glVertex2f(0, 0);
	glVertex2f(0.8 * radius * sin(secondsAngle), 0.8 * radius * cos(secondsAngle));
}

void drawClock(float hour, float minute, float second, float radius)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);

	drawClockFace(12, radius);
	drawHands(hour, minute, second, radius);

	glFlush();
}
int main(void)
{
	srand(time(NULL));
	GLFWwindow* window;
	Point point;
	GeometrShape geometrShape;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "Project", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		       int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float t = (float)glfwGetTime();

		int hour = ((int)t / 3600) % 10;
        float minute = fmod(t / 60.0, 60.0);
        float second = fmod(t, 60.0);
		float a = 10;
		float b = 5;
        drawClock(hour, minute, second, 0.1);

		glfwPollEvents();
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
