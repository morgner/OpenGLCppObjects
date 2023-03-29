/***************************************************************************
                          3DLight.cpp  -  description
                             -------------------
    begin                : Sat Feb 12 2000
    copyright            : (C) 2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/




#include "3DLight.h"
#include <cstring>


using namespace N3DCpp;

GLfloat C3DLight::s_fModelLocalViewer =   0.f;
GLfloat C3DLight::s_afModelAmbient[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat C3DLight::s_fModelTwoSide     =   1.f;  // OGL-default is 0.f

GLfloat C3DLight::s_afColorAmbient [] = {0.6f, 0.6f, 0.6f, OGLCLIB_ALPHA_SOLID};//ge�ndert RS
GLfloat C3DLight::s_afColorDiffuse [] = {1.0f, 1.0f, 1.0f, OGLCLIB_ALPHA_SOLID};//ge�ndert RS
GLfloat C3DLight::s_afColorSpecular[] = {1.0f, 1.0f, 1.0f, OGLCLIB_ALPHA_SOLID};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DLight::C3DLight()
  {
  } // C3DLight::C3DLight()

