#include <GLFW/glfw3.h>

void drawSquare(double x1, double y1, double sidelength)
{
    double halfside = sidelength / 6;

    glColor3d(0, 0, 0);
    glBegin(GL_POLYGON);

    glVertex2d(x1 + halfside, y1 + halfside);
    glVertex2d(x1 + halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 + halfside);

    glEnd();
}