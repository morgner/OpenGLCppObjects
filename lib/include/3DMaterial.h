/***************************************************************************
                          3DMaterial.h  -  description
                             -------------------
    begin                : Sun Jan 30 2000
    copyright            : (C) 2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/


#ifndef _3DMaterial_H
#define _3DMaterial_H

#include <GL/gl.h>


#define MAT_NO_PROPERTIES        0x00
#define MAT_AMBIENT              0x01
#define MAT_DIFFUSE              0x02
#define MAT_SPECULAR             0x04
#define MAT_EMISSION             0x08
#define MAT_SHININESS            0x10
#define MAT_AMBIENT_AND_DIFFUSE  0x20
#define MAT_COLOR_INDEXES        0x40

namespace N3DCpp
  {

  class C3DMaterial  
    {
    protected:
      static GLfloat *s_pfNullProperty;

    public:
               C3DMaterial();
      virtual ~C3DMaterial();

      GLfloat* Allocate(GLfloat*& mem, char cSize);
      void PropertySet(GLenum eProperty, GLfloat p1, GLfloat p2 = 0.f, GLfloat p3 = 0.f, GLfloat p4 = 0.f);	// ???
//      void PropertySet(GLenum eProperty, GLfloat p0, GLfloat p1 = 0.f, GLfloat p2 = 0.f, GLfloat p3 = 0.f);
      
  //    const GLfloat*& PropertyGet(GLenum eProperty);	// ???
      GLfloat*& PropertyGet(GLenum eProperty);

      void PropertyDelete(GLenum eProperty);

      void   FaceSet(GLenum eFace); // GL_FRONT, GL_BACK, GL_FRONT_AND_BACK
      GLenum FaceGet();


      void GLMaterial();

    protected:
      char    m_cProperties;

      GLenum  m_eFace;

      GLfloat *m_pfParamAmbient;            // 4
      GLfloat *m_pfParamDiffuse;            // 4
      GLfloat *m_pfParamSpecular;           // 4
      GLfloat *m_pfParamEmission;           // 4
      GLfloat *m_pfParamShininess;          // 1
      GLfloat *m_pfParamColorIndexes;       // 3

  /*
  GL_FRONT, GL_BACK, GL_FRONT_AND_BACK

  GL_AMBIENT 
    The params parameter contains four integer or floating-point values that specify the ambient RGBA reflectance of the material.
    Integer values are mapped linearly such that the most positive representable value maps to 1.0, and the most negative representable value maps to 1.0.
    Floating-point values are mapped directly. Neither integer nor floating-point values are clamped.
    The default ambient reflectance for both front- and back-facing materials is (0.2, 0.2, 0.2, 1.0). 

  GL_DIFFUSE 
    The params parameter contains four integer or floating-point values that specify the diffuse RGBA reflectance of the material.
    Integer values are mapped linearly such that the most positive representable value maps to 1.0, and the most negative representable value maps to 1.0.
    Floating-point values are mapped directly. Neither integer nor floating-point values are clamped.
    The default diffuse reflectance for both front- and back-facing materials is (0.8, 0.8, 0.8, 1.0). 

  GL_SPECULAR 
    The params parameter contains four integer or floating-point values that specify the specular RGBA reflectance of the material.
    Integer values are mapped linearly such that the most positive representable value maps to 1.0, and the most negative representable value maps to 1.0.
    Floating-point values are mapped directly. Neither integer nor floating-point values are clamped.
    The default specular reflectance for both front- and back-facing materials is (0.0, 0.0, 0.0, 1.0). 

  GL_EMISSION 
    The params parameter contains four integer or floating-point values that specify the RGBA emitted light intensity of the material.
    Integer values are mapped linearly such that the most positive representable value maps to 1.0, and the most negative representable value maps to 1.0.
    Floating-point values are mapped directly. Neither integer nor floating-point values are clamped.
    The default emission intensity for both front- and back-facing materials is (0.0, 0.0, 0.0, 1.0). 

  GL_SHININESS 
    The params parameter is a single integer or floating-point value that specifies the RGBA specular exponent of the material.
    Integer and floating-point values are mapped directly. Only values in the range [0,128] are accepted.
    The default specular exponent for both front- and back-facing materials is 0. 

  GL_AMBIENT_AND_DIFFUSE 
    Equivalent to calling glMaterial twice with the same parameter values, once with GL_AMBIENT and once with GL_DIFFUSE. 

  GL_COLOR_INDEXES 
    The params parameter contains three integer or floating-point values specifying the color indexes for ambient, diffuse, and specular lighting.
    These three values, and GL_SHININESS, are the only material values used by the color-index mode lighting equation.
    Refer to glLightModel for a discussion of color-index lighting. 

  */
  //   static GLfloat sphere_mat[] = {1.f, .5f, 0.f, .5f};
  //   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphere_mat);

    }; // class C3DMaterial

  } // namespace mm3Dlib

#endif // _3DMaterial_H
