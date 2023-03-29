/***************************************************************************
                          3DShape.cpp  -  description
                             -------------------
    begin                : Sun Jan 30 2000
    copyright            : (C) 2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/


#include "3DShape.h"

using namespace N3DCpp;

// GLUquadricObj *C3DShape::s_pGluQuadricObj = gluNewQuadric();

// ?? gluDeleteQuadric(s_pGluQuadricObj);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DShape::C3DShape()
  {
  } // C3DShape::C3DShape()


C3DShape::~C3DShape()
  {
  if ( m_nIdDisplayList > 0 )
    {
    glDeleteLists(m_nIdDisplayList, 2);
  }
  }
//  delete [] m_poTexture;
//  delete [] m_poMaterial;

//  } // C3DShape::~C3DShape()

/*
void C3DShape::BoxPlanesMake(GLfloat cx, GLfloat cy, GLfloat cz)
  {
  const GLfloat cx2 = cx/2;
  const GLfloat cy2 = cy/2;
  const GLfloat cz2 = cz/2;

  glBegin(GL_QUADS);
    //
    glNormal3f( 0.f, 0.f, 1.f);
    glVertex3f( cx2, cy2, cz2); glVertex3f(-cx2, cy2, cz2);
    glVertex3f(-cx2,-cy2, cz2); glVertex3f( cx2,-cy2, cz2);
    //
    glNormal3f( 0.f, 0.f,-1.f);
    glVertex3f(-cx2,-cy2,-cz2); glVertex3f(-cx2, cy2,-cz2);
    glVertex3f( cx2, cy2,-cz2); glVertex3f( cx2,-cy2,-cz2);
    //
    glNormal3f( 0.f, 1.f, 0.f);
    glVertex3f( cx2, cy2, cz2); glVertex3f( cx2, cy2,-cz2);
    glVertex3f(-cx2, cy2,-cz2); glVertex3f(-cx2, cy2, cz2);
    //
    glNormal3f( 0.f,-1.f, 0.f);
    glVertex3f(-cx2,-cy2,-cz2); glVertex3f( cx2,-cy2,-cz2);
    glVertex3f( cx2,-cy2, cz2); glVertex3f(-cx2,-cy2, cz2);
    //
    glNormal3f( 1.f, 0.f, 0.f);
    glVertex3f( cx2, cy2, cz2); glVertex3f( cx2,-cy2, cz2);
    glVertex3f( cx2,-cy2,-cz2); glVertex3f( cx2, cy2,-cz2);
    //
    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f(-cx2,-cy2,-cz2); glVertex3f(-cx2,-cy2, cz2);
    glVertex3f(-cx2, cy2, cz2); glVertex3f(-cx2, cy2,-cz2);
    glEnd();
  } // void C3DShape::BoxPlanesMake(GLfloat cx, GLfloat cy, GLfloat cz)

void C3DShape::BoxPlanesMakeTextured(GLfloat cx, GLfloat cy, GLfloat cz)
  {
  const GLfloat cx2 = cx/2;
  const GLfloat cy2 = cy/2;
  const GLfloat cz2 = cz/2;

  const GLfloat xr  = TextureRepeatXGet();//RS Voreinstellung xr=1
  const GLfloat yr  = TextureRepeatYGet();

  glBegin(GL_QUADS);
    // Front Face
	  glNormal3f( 0.f, 0.f, 1.f);
	  glTexCoord2f(0.f, 0.f); glVertex3f(-cx2, -cy2,  cz2);
	  glTexCoord2f(xr, 0.f); glVertex3f( cx2, -cy2,  cz2);
	  glTexCoord2f(xr, xr); glVertex3f( cx2,  cy2,  cz2);
	  glTexCoord2f(0.f, xr); glVertex3f(-cx2,  cy2,  cz2);
	  // Back Face
	  glNormal3f( 0.f, 0.f,-1.f);
	  glTexCoord2f(xr, 0.f); glVertex3f(-cx2, -cy2, -cz2);
	  glTexCoord2f(xr, xr); glVertex3f(-cx2,  cy2, -cz2);
	  glTexCoord2f(0.f, xr); glVertex3f( cx2,  cy2, -cz2);
	  glTexCoord2f(0.f, 0.f); glVertex3f( cx2, -cy2, -cz2);
	  // Top Face
	  glNormal3f( 0.f, 1.f, 0.f);
	  glTexCoord2f(0.f, yr); glVertex3f(-cx2,  cy2, -cz2);
	  glTexCoord2f(0.f, 0.f); glVertex3f(-cx2,  cy2,  cz2);
	  glTexCoord2f(xr, 0.f); glVertex3f( cx2,  cy2,  cz2);
	  glTexCoord2f(xr, yr); glVertex3f( cx2,  cy2, -cz2);
	  // Bottom Face
	  glNormal3f( 0.f,-1.f, 0.f);
	  glTexCoord2f(xr, yr); glVertex3f(-cx2, -cy2, -cz2);
	  glTexCoord2f(0.f, yr); glVertex3f( cx2, -cy2, -cz2);
	  glTexCoord2f(0.f, 0.f); glVertex3f( cx2, -cy2,  cz2);
	  glTexCoord2f(xr, 0.f); glVertex3f(-cx2, -cy2,  cz2);
	  // Right face
	  glNormal3f( 1.f, 0.f, 0.f);
	  glTexCoord2f(yr, 0.f); glVertex3f( cx2, -cy2, -cz2);
	  glTexCoord2f(yr, xr); glVertex3f( cx2,  cy2, -cz2);
	  glTexCoord2f(0.f, xr); glVertex3f( cx2,  cy2,  cz2);
	  glTexCoord2f(0.f, 0.f); glVertex3f( cx2, -cy2,  cz2);
	  // Left Face
	  glNormal3f(-1.f, 0.f, 0.f);
	  glTexCoord2f(0.f, 0.f); glVertex3f(-cx2, -cy2, -cz2);
	  glTexCoord2f(yr, 0.f); glVertex3f(-cx2, -cy2,  cz2);
	  glTexCoord2f(yr, xr); glVertex3f(-cx2,  cy2,  cz2);
	  glTexCoord2f(0.f, xr); glVertex3f(-cx2,  cy2, -cz2);
    glEnd();
  } // void C3DShape::BoxPlanesMakeTextured(GLfloat cx, GLfloat cy, GLfloat cz)

void C3DShape::BoxPlanesMakeWired(GLfloat cx, GLfloat cy, GLfloat cz)
  {
  const GLfloat cx2 = cx/2;
  const GLfloat cy2 = cy/2;
  const GLfloat cz2 = cz/2;
  //
  glBegin(GL_LINE_STRIP);
    glNormal3f( 0.f, 0.f, 1.f);
    glVertex3f( cx2, cy2, cz2); glVertex3f(-cx2, cy2, cz2);
    glVertex3f(-cx2,-cy2, cz2); glVertex3f( cx2,-cy2, cz2);
    glEnd();
  //
  glBegin(GL_LINE_STRIP);
    glNormal3f( 0.f, 0.f,-1.f);
    glVertex3f(-cx2,-cy2,-cz2); glVertex3f(-cx2, cy2,-cz2);
    glVertex3f( cx2, cy2,-cz2); glVertex3f( cx2,-cy2,-cz2);
    glEnd();
  //
  glBegin(GL_LINE_STRIP);
    glNormal3f( 0.f, 1.f, 0.f);
    glVertex3f( cx2, cy2, cz2); glVertex3f( cx2, cy2,-cz2);
    glVertex3f(-cx2, cy2,-cz2); glVertex3f(-cx2, cy2, cz2);
    glEnd();
  //
  glBegin(GL_LINE_STRIP);
    glNormal3f( 0.f,-1.f, 0.f);
    glVertex3f(-cx2,-cy2,-cz2); glVertex3f( cx2,-cy2,-cz2);
    glVertex3f( cx2,-cy2, cz2); glVertex3f(-cx2,-cy2, cz2);
    glEnd();
  //
  glBegin(GL_LINE_STRIP);
    glNormal3f( 1.f, 0.f, 0.f);
    glVertex3f( cx2, cy2, cz2); glVertex3f( cx2,-cy2, cz2);
    glVertex3f( cx2,-cy2,-cz2); glVertex3f( cx2, cy2,-cz2);
    glEnd();
  //
  glBegin(GL_LINE_STRIP);
    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f(-cx2,-cy2,-cz2); glVertex3f(-cx2,-cy2, cz2);
    glVertex3f(-cx2, cy2, cz2); glVertex3f(-cx2, cy2,-cz2);
    glEnd();
  } // void C3DShape::BoxPlanesMakeWired(GLfloat cx, GLfloat cy, GLfloat cz)
}
*/
