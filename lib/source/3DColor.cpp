/***************************************************************************
                          3DColor.cpp  -  description
                             -------------------
    begin                : Sun Jan 30 2000
    copyright            : (C) 2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/

#include "3DColor.h"


using namespace N3DCpp;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DColor::C3DColor(GLfloat nR, GLfloat nG, GLfloat nB, GLfloat nA)
  : R(nR),
    G(nG),
    B(nB),
    A(nA)
  {
  } // C3DColor::C3DColor(GLfloat &rR, GLfloat &rG, GLfloat &rB, GLfloat &rA)

 // glColor4f(R, G, B, A);
 

C3DColor::~C3DColor()
    {
    }
