/***************************************************************************
                          3DBox.h  -  description
                             -------------------
    begin                : Fri  Apr 15 2023
    copyright            : (C) 2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/

#ifndef _3DBox_H
#define _3DBox_H

#include "3DShape.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

namespace N3DCpp
  {
  class C3DBox : public C3DShape
    {
  public:

        S3DGeometry m_fGeometry{1.f, 1.f, 1.f};
        S3DPosition m_fPosition{0.f, 0.f, 0.f};
        S3DRotation m_fRotation{0.f, 0.f, 0.f};

    public:
               C3DBox(); // = default;
               C3DBox(S3DGeometry const & crGeometry, S3DPosition const & crPosition, S3DRotation const & crRotation)
                    : m_fGeometry(crGeometry), m_fPosition(crPosition), m_fRotation(crRotation)
                    {}
      virtual ~C3DBox();
    
      GLint NormalsMake();
      virtual void Draw();

      
    }; // class C3DBox
  } // namespace 3DCpp
  #endif // _3DBox_H
