/***************************************************************************
                          3DBox.h  -  description
                             -------------------
    begin                : Sun Jan 30 2000
    copyright            : (C) 2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/

#ifndef _3DBox_H
#define _3DBox_H

#include "3DShape.h"

#include <GL/gl.h>

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

      virtual void Draw();

    protected:
      bool NormalsMake();
      long DisplayListMake();
      bool DisplayListDelete();
    }; // class C3DBox
  } // namespace 3DCpp
  #endif // _3DBox_H
