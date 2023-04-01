#include "3DBox.h"
#include "3DShape.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <array>

using namespace N3DCpp;

C3DBox box ({.2f, .2f, .2f}, {1.0f, 1.f, 1.f}, {0.f, 0.f, 0.f});

CVectorShapes bv;


int fullscreen = 0;
int mouseDown  = 0;

float xrot =  10.0f;
float yrot = -10.0f;

float xdiff = 10.0f;
float ydiff = 10.0f;

float tra_x = 0.0f;
float tra_y = 0.0f;
float tra_z = 0.0f;

float grow_shrink = 70.0f;
float resize_f = 1.0f;


bool initlights(void) {

    glClearColor(0.9, 0.9, 0.9, 0.0);

   GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
   GLfloat position[] = {0.0, 0.0, 2.0, 1.0};
   GLfloat mat_diffuse[] = {0.6, 0.6, 0.6, 1.0};
   GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat mat_shininess[] = {50.0};

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, position);

   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    return true;
}

void init(void) {
    glColor3f(0,1,0);
    for (int x : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9})
        for (int y : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9})
            bv.push_back(   new C3DBox({.2f, .2f, .2f}, {.15f*x, .15f*y, 0.0f}, {0.f, 0.f, 0.f}) );
            
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);


   
// Microsoft:  GLfloat ctrlpoints[0][0][0];   glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,   0, 1, 12, 4, &ctrlpoints);
   glEnable(GL_MAP2_VERTEX_3);
   glEnable(GL_AUTO_NORMAL);
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
   initlights();
}

void display(void)
    {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 //   glMatrixMode(GL_MODELVIEW); 

//    glLoadIdentity();

//    gluLookAt( 0.0f, 0.0f, 3.0f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glColor3f(1.0f, 0.5f, 0.5f);
//    glutSolidSphere(0.5, 20, 20);

    glRotatef(-xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(-yrot, 0.0f, 1.0f, 0.0f);

    for (auto const & a : bv) { a->Draw();}
    
    glRotatef(2*xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(2*yrot, 0.0f, 1.0f, 0.0f);

 //   for (auto const & a : bv) { a->Draw();}

    glFlush();
    glutSwapBuffers();
    }

void reshape (int w, int h)
    {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
       glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
          1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
       glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
          1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
        xrot += .3f;
        yrot += .4f;
        box.Rotate({xrot, yrot, 0});
        }
    glutPostRedisplay();
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
//        case 'h': case 'H': mySpecialFunction(key, x, y); break;
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

       if (fullscreen)
           {
           glutFullScreen();
           }
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


int main(int argc, char** argv)
{
        glutInit(&argc, argv);

        glutInitWindowPosition(50, 50);
        glutInitWindowSize(500, 500);

        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

        glutCreateWindow("13 - Solid Shapes");

        glutDisplayFunc(display);
        glutKeyboardFunc(keyboard);
        glutSpecialFunc(specialKeyboard);
        glutMouseFunc(mouse);
        glutMotionFunc(mouseMotion);
        glutReshapeFunc(reshape);
//        glutReshapeFunc(resize);
        glutIdleFunc(idle);

        //     if (!init()) return 1;
        init();

        glutMainLoop();

        return 0;
}
























