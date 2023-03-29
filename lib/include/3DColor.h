/***************************************************************************
                          3DColor.h  -  description
                             -------------------
    begin                : Sun Jan 30 2000
    copyright            : (C) 2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/


#ifndef _3DColor_H
#define _3DColor_H

#include <GL/gl.h>

#define OGLCLIB_ALPHA_SOLID 1.f

namespace N3DCpp
  {

  class C3DColor
    {
    friend class C3DShape;

    public:
       C3DColor() = delete;
       C3DColor(GLfloat nR = 0, GLfloat nG = 0, GLfloat nB = 0, GLfloat nA =  1.f); // not transparent by default
     ~C3DColor();

    public:
      GLfloat R{ 1 };
      GLfloat G{ 1 };
      GLfloat B{ 1 };
      GLfloat A{ 1 }; // 0.0f = full transparent, 1.0f = not transparent
   
    }; // class C3DColor

  } // namespace N3DCpp

#endif // _3DColor_H
