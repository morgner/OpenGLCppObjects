/***************************************************************************
                          3DBox.cpp  -  description
                             -------------------
    begin                : Sun Jan 30 2000
    copyright            : (C) 2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/


#include "3DBox.h"

#include <stdio.h>
#include <iostream>

#include <GL/gl.h>
#include <GL/glut.h>
#define KEY_ESC 27 // GLUT doesn't supply this 

using namespace N3DCpp;


C3DBox::C3DBox()
    {
//    DisplayListDelete();
    }


C3DBox::~C3DBox()
    {
    DisplayListDelete();
    }

void C3DBox::Draw()
    {

        glTranslatef(m_fPosition.X, m_fPosition.Y, m_fPosition.Z);

        glBegin(GL_QUADS);

        auto x = m_fGeometry.X/2;
        auto y = m_fGeometry.Y/2;
        auto z = m_fGeometry.Z/2;

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
    }

bool C3DBox::NormalsMake()
    {
    return true;
    }

bool C3DBox::DisplayListDelete()
    {
    return true;
    }

long C3DBox::DisplayListMake()
    {
    return 0;
    }

