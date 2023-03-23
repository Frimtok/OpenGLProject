#include <GLFW/glfw3.h>
#include <iostream>
#include <ctime>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cmath>


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

class Square : public GeometrShape
{
public:
	Square();
	~Square();
	void drawSquare(float x, float y)
	{

		glBegin(GL_POLYGON);
		SetColot(1, 1, 1);
		glVertex2d(x, y);
		glVertex2d(x, -y);
		glVertex2d(-x, -y);
		glVertex2d(-x, y);

		glEnd();
	}
private:
	void SetColot(float r, float g, float b)
	{
		glColor3d(r, g, b);
	}
};
class Circle : public GeometrShape
{
public:
	Circle();
	~Circle();
	void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
		const float PI = 3.1415926535;
		int triangleAmount = 20;
		GLfloat twicePi = 2.0f * PI;
		CreatingTrianglesInCircle(x, y, twicePi, radius, triangleAmount);
	}
private:
	void CreatingTrianglesInCircle(GLfloat x, GLfloat y, GLfloat twicePi, GLfloat radius, int triangleAmount) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				x + (radius * cos(i * twicePi / triangleAmount)),
				y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
		glEnd();
	}

};

Circle::Circle()
{
}

Circle::~Circle()
{
}
Square::Square()
{
}

Square::~Square()
{
}
int main(void)
{
	srand(time(NULL));
	GLFWwindow* window;
	Point point;
	Square WhiteSquare;
	Circle circle;
	GeometrShape geometrShape;
	const int Arraylength = 100;
	float positionX[Arraylength];
	float positionY[Arraylength];
	float spawnAreaX = geometrShape.ConvertToPixel(200, 800);
	float spawnAreaY = geometrShape.ConvertToPixel(200, 600);
	float xSquare = geometrShape.ConvertToPixel(100, 800);
	float ySquare = geometrShape.ConvertToPixel(100, 600);
	float r = geometrShape.ConvertToPixel(10, 800);
	for (int i = 0; i < Arraylength; i++)
	{
		positionX[i] = point.randomSpawn(-spawnAreaX, spawnAreaX);
		positionY[i] = point.randomSpawn(-spawnAreaY, spawnAreaY);
	}

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
		/* Render here */
		glClearColor(0.138, 0.138, 0.138, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		WhiteSquare.drawSquare(xSquare, ySquare);
		for (int i = 0; i < Arraylength; i++)
		{
			point.DrawPoint(positionX[i], positionY[i]);
			if (positionY[i] < -ySquare || positionY[i] > ySquare || positionX[i] > xSquare || positionX[i] < -xSquare)
			{
				glColor3f(0.255f, 0, 0);
				circle.drawFilledCircle(positionX[i], positionY[i], r);
				glEnd();
			}
			else
			{
				glColor3f(0.154, 0.6, 0.2);
				circle.drawFilledCircle(positionX[i], positionY[i], r);
				glEnd();
			}
		}

		glEnd();
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}