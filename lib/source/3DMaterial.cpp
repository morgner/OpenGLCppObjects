/***************************************************************************
                          3DMaterial.cpp  -  description
                             -------------------
    begin                : Sun Jan 30 2000
    copyright            : (C) 2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "3DMaterial.h"


using namespace N3DCpp;

GLfloat *C3DMaterial::s_pfNullProperty = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DMaterial::C3DMaterial()
  {
  m_cProperties = MAT_NO_PROPERTIES;
  m_eFace       = GL_FRONT;

  m_pfParamAmbient      = 0;
  m_pfParamDiffuse      = 0;
  m_pfParamSpecular     = 0;
  m_pfParamEmission     = 0;
  m_pfParamShininess    = 0;
  m_pfParamColorIndexes = 0;
  }

C3DMaterial::~C3DMaterial()
  {
  m_cProperties = MAT_NO_PROPERTIES;
  m_eFace       = GL_NONE;

  delete m_pfParamAmbient;
  delete m_pfParamDiffuse;
  delete m_pfParamSpecular;
  delete m_pfParamEmission;
  delete m_pfParamShininess;
  delete m_pfParamColorIndexes;
  } // C3DMaterial::~C3DMaterial()


GLfloat* C3DMaterial::Allocate(GLfloat*& mem, char cSize)
  {
  if (mem != 0)
    {
    return mem;
    }
  return mem = new GLfloat(cSize);
  } // GLfloat* C3DMaterial::Allocate(GLfloat*& mem, char cSize)

void C3DMaterial::PropertySet(GLenum eProperty, GLfloat p0, GLfloat p1, GLfloat p2, GLfloat p3)
  {
  GLfloat *pf;
  switch (eProperty)
    {
    case GL_AMBIENT:
      pf = Allocate(m_pfParamAmbient, 4);
      pf[0] = p0;
      pf[1] = p1;
      pf[2] = p2;
      pf[3] = p3;
      m_cProperties |= MAT_AMBIENT;
      break;

    case GL_DIFFUSE:
      pf = Allocate(m_pfParamDiffuse, 4);
      pf[0] = p0;
      pf[1] = p1;
      pf[2] = p2;
      pf[3] = p3;
      m_cProperties |= MAT_DIFFUSE;
      break;

    case GL_AMBIENT_AND_DIFFUSE:
      pf = Allocate(m_pfParamAmbient, 4);
      pf[0] = p0;
      pf[1] = p1;
      pf[2] = p2;
      pf[3] = p3;
      m_cProperties |= MAT_AMBIENT;
      pf = Allocate(m_pfParamDiffuse, 4);
      pf[0] = p0;
      pf[1] = p1;
      pf[2] = p2;
      pf[3] = p3;
      m_cProperties |= MAT_DIFFUSE;
      break;

    case GL_SPECULAR:
      pf = Allocate(m_pfParamSpecular, 4);
      pf[0] = p0;
      pf[1] = p1;
      pf[2] = p2;
      pf[3] = p3;
      m_cProperties |= MAT_SPECULAR;
      break;

    case GL_EMISSION:
      pf = Allocate(m_pfParamEmission, 4);
      pf[0] = p0;
      pf[1] = p1;
      pf[2] = p2;
      pf[3] = p3;
      m_cProperties |= MAT_EMISSION;
      break;

    case GL_SHININESS:
      pf = Allocate(m_pfParamShininess, 1);
      pf[0] = p0;
      m_cProperties |= MAT_SHININESS;
      break;

    case GL_COLOR_INDEXES:
      pf = Allocate(m_pfParamColorIndexes, 3);
      pf[0] = p0;
      pf[1] = p1;
      pf[2] = p2;
      m_cProperties |= MAT_COLOR_INDEXES;
      break;

    default:
      break;
    } // switch (eProperty)
  } // void C3DMaterial::PropertySet(GLenum eProperty, GLfloat p1, GLfloat p2, GLfloat p3, GLfloat p4)

 GLfloat*& C3DMaterial::PropertyGet(GLenum eProperty)	// ???
 // GLfloat*& C3DMaterial::PropertyGet(GLenum eProperty)
  {
  switch (eProperty)
    {
    case GL_AMBIENT:
      return m_pfParamAmbient;
      break;

    case GL_DIFFUSE:
      return m_pfParamDiffuse;
      break;

    case GL_SPECULAR:
      return m_pfParamSpecular;
      break;

    case GL_EMISSION:
      return m_pfParamEmission;
      break;

    case GL_SHININESS:
      return m_pfParamShininess;
      break;

    case GL_COLOR_INDEXES:
      return m_pfParamColorIndexes;
      break;

    default:
      return s_pfNullProperty;
    } // switch (eProperty)

  return s_pfNullProperty;
  } // const GLfloat*& C3DMaterial::PropertyGet(GLenum eProperty)

void C3DMaterial::PropertyDelete(GLenum eProperty)
  {
  switch (eProperty)
    {
    case GL_AMBIENT:
      m_cProperties &= ~MAT_AMBIENT;
      break;

    case GL_DIFFUSE:
      m_cProperties &= ~MAT_DIFFUSE;
      break;

    case GL_SPECULAR:
      m_cProperties &= ~MAT_EMISSION;
      break;

    case GL_EMISSION:
      m_cProperties &= ~MAT_EMISSION;
      break;

    case GL_SHININESS:
      m_cProperties &= ~MAT_SHININESS;
      break;

    case GL_COLOR_INDEXES:
      m_cProperties &= ~MAT_COLOR_INDEXES;
      break;

    default:
      break;
    } // switch (eProperty)

  } // void C3DMaterial::PropertyDelete(GLenum eProperty);

void C3DMaterial::FaceSet(GLenum eFace) // GL_FRONT, GL_BACK, GL_FRONT_AND_BACK
  {
  m_eFace = eFace;
  } // void C3DMaterial::FaceSet(GLenum eFace)

GLenum C3DMaterial::FaceGet()
  {
  return m_eFace;
  } // 

// realize the colormaterial on the GL render context
void C3DMaterial::GLMaterial()
  {
  if ( (m_cProperties & MAT_AMBIENT)       == MAT_AMBIENT )       { glMaterialfv(m_eFace, GL_AMBIENT,       m_pfParamAmbient);      }
  if ( (m_cProperties & MAT_DIFFUSE)       == MAT_DIFFUSE )       { glMaterialfv(m_eFace, GL_DIFFUSE,       m_pfParamDiffuse);      }
  if ( (m_cProperties & MAT_SPECULAR)      == MAT_SPECULAR )      { glMaterialfv(m_eFace, GL_SPECULAR,      m_pfParamSpecular);     }
  if ( (m_cProperties & MAT_EMISSION)      == MAT_EMISSION )      { glMaterialfv(m_eFace, GL_EMISSION,      m_pfParamEmission);     }
  if ( (m_cProperties & MAT_SHININESS)     == MAT_SHININESS )     { glMaterialfv(m_eFace, GL_SHININESS,     m_pfParamShininess);    }
  if ( (m_cProperties & MAT_COLOR_INDEXES) == MAT_COLOR_INDEXES ) { glMaterialfv(m_eFace, GL_COLOR_INDEXES, m_pfParamColorIndexes); }
  } // C3DMaterial::GLMaterial()

