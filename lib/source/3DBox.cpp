/***************************************************************************
                          3DBox.cpp  -  description
                             -------------------
    begin                : Fri  Apr 15 2023
    copyright            : (C) 2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/


#include "3DBox.h"

#include <GL/glext.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define KEY_ESC 27 // GLUT doesn't supply this 

using namespace N3DCpp;


C3DBox::C3DBox()    {    }

C3DBox::~C3DBox()    {    }

void C3DBox::Draw() {

        if (m_uDisplayList) { glCallList(m_uDisplayList); return; }
         glNewList(m_uDisplayList, GL_COMPILE);

  glTranslatef(m_fPosition.X, m_fPosition.Y, m_fPosition.Z);

  //        glRotatef(m_fRotation.X, 1.f, 0, 0);
  //        glRotatef(m_fRotation.Y, 0.f, 1.f, 0);
  //        glRotatef(m_fRotation.Z, 0.f, 0, 1.f);

  glRotatef(0, 1.f, 0, 0);
  glRotatef(0, 0.f, 1.f, 0);
  glRotatef(0, 0.f, 0, 1.f);

  auto x = m_fGeometry.X / 2;
  auto y = m_fGeometry.Y / 2;
  auto z = m_fGeometry.Z / 2;

  glNewList(m_uDisplayList, GL_COMPILE);

  glBegin(GL_QUADS);

  glColor3f(.7f, .6f, .9f);
  // FRONT
  glVertex3f(-x, -y, z);
  //        glColor3f ( 0.0f,  1.0f,  0.0f);
  glVertex3f(x, -y, z);
  glVertex3f(x, y, z);
  //        glColor3f ( 1.0f,  0.0f,  0.0f);
  glVertex3f(-x, y, z);
  // BACK
  glVertex3f(-x, -y, -z);
  glVertex3f(-x, y, -z);
  //        glColor3f ( 0.0f,  1.0f,  0.0f);
  glVertex3f(x, y, -z);
  glVertex3f(x, -y, -z);
  //        glColor3f ( 0.0f,  1.0f,  0.0f);
  // LEFT
  glVertex3f(-x, -y, z);
  glVertex3f(-x, y, z);
  //        glColor3f ( 0.0f,  0.0f,  1.0f);
  glVertex3f(-x, y, -z);
  //        glColor3f ( 1.0f,  0.0f,  0.0f);
  glVertex3f(-x, -y, -z);
  // RIGHT
  glVertex3f(x, -y, -z);
  glVertex3f(x, y, -z);
  //        glColor3f ( 0.0f,  1.0f,  0.0f);
  glVertex3f(x, y, z);
  //        glColor3f ( 0.0f,  0.0f,  1.0f);
  glVertex3f(x, -y, z);
  //        glColor3f ( 0.0f,  0.0f,  1.0f);
  // TOP
  glVertex3f(-x, y, z);
  glVertex3f(x, y, z);
  //        glColor3f ( 0.0f,  1.0f,  0.0f);
  glVertex3f(x, y, -z);
  glVertex3f(-x, y, -z);
  //        glColor3f ( 1.0f,  0.0f,  0.0f);
  // BOTTOM
  glVertex3f(-x, -y, z);
  //        glColor3f ( 0.0f,  0.0f,  1.0f);
  glVertex3f(-x, -y, -z);
  glVertex3f(x, -y, -z);
  glVertex3f(x, -y, z);
  glEnd();
  glEndList();
        }


GLint  C3DBox::NormalsMake()
    {
    return 1;
    }
