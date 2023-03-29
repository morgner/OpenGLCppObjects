#include "3DBox.h"

#include <string>

#include <GL/glut.h>
#include <GL/gl.h>

// #define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
// #include <glad/gl.h>




N3DCpp::C3DBox  box({.4f, .4f, .4f}, {.4f, .4f, .4f}, {.4f, .4f, .4f});
//mm3Dlib::C3DTorus  box{};
// mm3Dlib::C3DText box("Arial", .4f);
// mm3Dlib::C3DPartialDisk box{1.f, .1f, .2};
// mm3Dlib::C3DPartialDisk box{};

GLfloat z{15};

void renderFunction()
{
//    box.RotateTo(45,30,z++);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    box.Draw();

    glEnd();
    glFlush();
}
/*
int main(int argc, char **argv)
{
//   glfwInit();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1024, 1024);
    glutInitWindowPosition(512, 512);
    glutCreateWindow("OpenGL - Creating a triangle");
    glutDisplayFunc(renderFunction);
    glutMainLoop();
    return 0;
}
*/
