/***************************************************************************
                          3DBox.cpp  -  description
                             -------------------
    begin                : Fri  Apr 15 2023
    copyright            : (C) 2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/


#include "3DBox.h"

#include <GL/glext.h>
#include <stdio.h>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define KEY_ESC 27 // GLUT doesn't supply this 

using namespace N3DCpp;

GLfloat XR{0};
GLfloat YR{0};

C3DBox::C3DBox()    {    }

C3DBox::~C3DBox()    {    }

void C3DBox::Draw()
    {
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glPushMatrix();
   gluLookAt( 0.0f, 0.0f, 3.0f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
{
    glPushMatrix();
   //Setup object matrices.
  glTranslatef(m_fPosition.X, m_fPosition.Y, m_fPosition.Z);
  glRotatef(XR+=0.005f,1,0,0);
  glRotatef(YR+=0.005f,0,1,0);

       glTranslatef(m_fPosition.X, m_fPosition.Y, m_fPosition.Z);

        if (m_uDisplayList > 0)  { glCallList( m_uDisplayList ); return; }

        auto x = m_fGeometry.X/2;
        auto y = m_fGeometry.Y/2;
        auto z = m_fGeometry.Z/2;

        m_uDisplayList = glGenLists( 1 );
        glNewList(m_uDisplayList, GL_COMPILE);


        
/*
   GLfloat ambient[] = {0.7, 0.9, 0.7, 1.0};
   GLfloat position[] = {0.0, 0.0, 5.0, 1.0};
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
*/


        glBegin(GL_QUADS);

        glColor3f ( .7f, .6f, .9f);
        // FRONT
        glVertex3f(-x, -y,  z);
        glColor3f ( 0.0f,  1.0f,  0.0f);
        glVertex3f( x, -y,  z);
        glVertex3f( x,  y,  z);
        glColor3f ( 1.0f,  0.0f,  0.0f);
        glVertex3f(-x,  y,  z);
        // BACK
        glVertex3f(-x, -y, -z);
        glVertex3f(-x,  y, -z);
        glColor3f ( 0.0f,  1.0f,  0.0f);
        glVertex3f( x,  y, -z);
        glVertex3f( x, -y, -z);

        glColor3f ( 0.0f,  1.0f,  0.0f);
        // LEFT
        glVertex3f(-x, -y,  z);
        glVertex3f(-x,  y,  z);
        glColor3f ( 0.0f,  0.0f,  1.0f);
        glVertex3f(-x,  y, -z);
        glColor3f ( 1.0f,  0.0f,  0.0f);
        glVertex3f(-x, -y, -z);
        // RIGHT
        glVertex3f( x, -y, -z);
        glVertex3f( x,  y, -z);
        glColor3f ( 0.0f,  1.0f,  0.0f);
        glVertex3f( x,  y,  z);
        glColor3f ( 0.0f,  0.0f,  1.0f);
        glVertex3f( x, -y,  z);

        glColor3f ( 0.0f,  0.0f,  1.0f);
        // TOP
        glVertex3f(-x,  y,  z);
        glVertex3f( x,  y,  z);
        glColor3f ( 0.0f,  1.0f,  0.0f);
        glVertex3f( x,  y, -z);
        glVertex3f(-x,  y, -z);
        glColor3f ( 1.0f,  0.0f,  0.0f); 
        // BOTTOM
        glVertex3f(-x, -y,  z);
        glColor3f ( 0.0f,  0.0f,  1.0f);
        glVertex3f(-x, -y, -z);
        glVertex3f( x, -y, -z);
        glVertex3f( x, -y,  z);
        glEnd();

        glEndList();

  glPopMatrix();
}
glPopMatrix(); //Remove camera matrix. MODELVIEW is now identity.
    }

GLint  C3DBox::NormalsMake()
    {
    return 1;
    }
