/***************************************************************************
                          3DLight.h  -  description
                             -------------------
    begin                : Sat Feb 12 2000
    copyright            : (C) 2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/


#ifndef _3DLIGHT_H
#define _3DLIGHT_H

#include "3DColor.h"

// STL
#include <vector>


namespace N3DCpp
  {
  class C3DLight;
  typedef std::vector<C3DLight*> CVectorLights;

  class C3DLight  //: public C3DPoint  
    {
    // transient properties for defaults
    protected:
      static GLfloat s_fModelLocalViewer;
      static GLfloat s_afModelAmbient[];
      static GLfloat s_fModelTwoSide;

      static GLfloat s_afColorAmbient []; // 4
      static GLfloat s_afColorDiffuse []; // 4
      static GLfloat s_afColorSpecular[]; // 4

    public:
               C3DLight();
      virtual ~C3DLight();

    }; // class C3DLight : public C3DPoint  

  } // namespace mm3Dlib

#endif // _3DLIGHT_H
