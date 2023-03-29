#include "3DBox.h"
#include "3DShape.h"

#include <GL/glut.h>



using namespace N3DCpp;

C3DBox box ({.4f, .4f, .4f}, {0.f, 0.f, 0.f}, {0.f, 0.f, 0.f});
C3DBox box2({.7f, .3f, .2f}, {0.f, 0.f, 0.f}, {0.f, 0.f, 0.f});

// CVectorShapes oSzene(new C3DBox({.5f, .5f, .5f}, {0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}));

int fullscreen = 0;
int mouseDown  = 0;

float xrot =  100.0f;
float yrot = -100.0f;
        
float xdiff = 100.0f;
float ydiff = 100.0f;
        
float tra_x = 0.0f; 
float tra_y = 0.0f; 
float tra_z = 0.0f; 
        
float grow_shrink = 70.0f;
float resize_f = 1.0f;



int init(void)
{
        glClearColor(0.93f, 0.93f, 0.93f, 0.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glClearDepth(1.0f);

        return 1;
    }

void display(void)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        gluLookAt(
        0.0f, 0.0f, 3.0f,
        -0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);

        glRotatef(-xrot, 1.0f, 0.0f, 0.0f);
        glRotatef(-yrot, 0.0f, 1.0f, 0.0f);
        
        box2.Draw();

        glRotatef(2*xrot, 1.0f, 0.0f, 0.0f);
        glRotatef(2*yrot, 0.0f, 1.0f, 0.0f);

        box.Draw();

        glFlush();
        glutSwapBuffers();
    }

void resize(int w, int h)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(0, 0, w, h);

        gluPerspective(grow_shrink, resize_f * w / h, resize_f, 100 * resize_f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

void idle(void)
    {
        if (!mouseDown)
            {
            box.MoveTo( {-1.f, -1.f, 0.f} );
            box2.MoveTo( {1.f, 1.f, 0.f} );
            xrot += .3f;
            yrot += .4f;
            box.Rotate({xrot, yrot, 0});
            box2.Rotate({xrot, yrot, 0});
            }

        glutPostRedisplay();
    }

void mySpecialFunction(int key, int x, int y)
    {
    //if (key == GLUT_KEY_F1)
    //{
        printf("U -----------> rotate clockwise\n");
        printf("Y -----------> rotate counter clockwise\n");
        printf("W or w ------> Up\n");
        printf("S or s -----> Down\n");
        printf("D or d ------> Right\n");
        printf("A or a ------> Left\n");
        printf("Z or z ------> Shrink\n"); printf("X or x ------> Grow\n");
        printf("Escape Key ---> exit the program\n\n");
    }

void keyboard(unsigned char key, int x, int y)
    {
        switch(key)
            {
                case 27 : exit(1); break;
                case 'w': case 'W': box.Move({ 0.1f, 0, 0}); break;
                case 's': case 'S': box.Move({-0.1f, 0, 0}); break;
                case 'a': case 'A': box.Move({ 0, 0, 0.1f}); break;
                case 'd': case 'D': box.Move({ 0, 0,-0.1f}); break;
                case 'u': case 'U': xrot += 1.0f; yrot += 1.0f; xdiff += 1.0f; ydiff += 1.0f; break;
                case 'y': case 'Y': xrot -= 1.0f; yrot -= 1.0f; xdiff += 1.0f; ydiff += 1.0f; break;
                case 'h': case 'H': mySpecialFunction(key, x, y); break;
                case 'Z': case 'z': grow_shrink--; resize(500, 500); break;
                case 'X': case 'x': grow_shrink++; resize(500, 500); break;
            }
        glutPostRedisplay();
    }

void specialKeyboard(int key, int x, int y)
    {
        if (key == GLUT_KEY_F1)
            {
                fullscreen = !fullscreen;

                if (fullscreen) glutFullScreen();
                else
                    {
                        glutReshapeWindow(500, 500);
                        glutPositionWindow(50, 50);
                    }
            }
    }

void mouse(int button, int state, int x, int y)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            {
                mouseDown = 1;
                xdiff = x - yrot;
                ydiff = -y + xrot;
            }
        else
                mouseDown = 0;
    }



void mouseMotion(int x, int y)
    {
        if (mouseDown)
            {
                yrot = x - xdiff;
                xrot = y + ydiff;
                glutPostRedisplay();
            }
    }


int main(int argc, char *argv[])
    {
        glutInit(&argc, argv);

        glutInitWindowPosition(50, 50);
        glutInitWindowSize(500, 500);

        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

        glutCreateWindow("13 - Solid Shapes");

        glutDisplayFunc(display);
        glutKeyboardFunc(keyboard);
        glutSpecialFunc(specialKeyboard);
        glutMouseFunc(mouse);
        glutMotionFunc(mouseMotion);
        glutReshapeFunc(resize);
        glutIdleFunc(idle);

        if (!init()) return 1;

        glutMainLoop();

        return 0;
    }

