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
  delete [] m_poTexture;
  delete [] m_poMaterial;

  } // C3DShape::~C3DShape()


bool C3DShape::IsTextured()
  {
  return m_poTexture != 0;
  } // BOOL C3DShape::IsTextured()

bool C3DShape::IsColored()
  {
  return true;
  } // BOOL C3DShape::IsColored()

bool C3DShape::IsTransparent()
  {
  return m_oColor.IsTransparent();
  } // BOOL C3DShape::IsTransparent()

bool C3DShape::IsMaterialed()
  {
  return m_poMaterial != 0;
  } // BOOL C3DShape::IsMaterialed()

bool C3DShape::IsShadowed()
  {
  return m_bReceivesShadow;
  } // bool C3DShape::IsShadowed()

bool C3DShape::IsMirror()
  {
  return m_bIsMirror;
  } // bool C3DShape::IsMirror()

long C3DShape::ShadowReceiveSet(bool bOn)
  {
  m_bReceivesShadow = bOn;
  return GL_TRUE;
  } // long C3DShape::ShadowReceiveSet(bool bOn)

long C3DShape::MirrorSet(bool bOn)
  {
  m_bIsMirror = bOn;
  return GL_TRUE;
  } // long C3DShape::MirrorSet(bool bOn)

long C3DShape::Select(bool bSelect)
  {
  if (m_bSelected != bSelect)
    {
    m_bSelected = bSelect;
    m_bChanged = true;
    }
  return GL_TRUE;
  } // long C3DShape::Select(BOOL bSelect = TRUE)

long C3DShape::DrawTransform()
  {
  GLTranslate();
  m_oAngle.GLRotate();
  m_oScale.GLScale();
  return GL_TRUE;
  } // long C3DShape::DrawTransform()

long C3DShape::DrawStart()
  {
  glPushMatrix();

  DrawTransform();

  if (GetRTTI() == C3DShape::s_RTTI)
    {
    m_oColor.AlphaSet(0.3f);
    }

  // FS_MATERIAL, FS_COLOR_PROFIL, FS_TEXTURE;
  // initialize flags, but dont delete FS_COLOR_PROFIL
  // FS_COLOR_PROFIL is a flag, set by the user, not by
  // the schema analyzer
  m_nFaceSpezials = FS_NONE | (m_nFaceSpezials & FS_COLOR_PROFIL);

  m_oColor.GLColor();
  if (IsMaterialed())
    {
    m_poMaterial->GLMaterial();
    m_nFaceSpezials |= FS_MATERIAL;
    }
  
  if (IsTextured())
    {
    m_nFaceSpezials |= FS_TEXTURE;
    m_poTexture->UseStart();
    }

  m_nChangedOptions = 0;
  if (IsTransparent())
    {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (glIsEnabled(GL_BLEND) == GL_FALSE)
      {
      m_nChangedOptions |= OPT_BLEND;
      glEnable(GL_BLEND);
//    glDisable(GL_DEPTH_TEST); // Turn Depth Testing Off

//      glAlphaFunc(GL_GREATER, 0.7f);
//      glEnable(GL_ALPHA_TEST);

      } // if (glIsEnabled(GL_BLEND) == GL_FALSE)

    if (glIsEnabled(OPT_CULL_FACE) == GL_FALSE)
      {
      m_nChangedOptions |= OPT_CULL_FACE;
      glEnable(GL_CULL_FACE);
      }
    } // if (m_oColor.IsTransparent())

  return GL_TRUE;
  } // long C3DShape::DrawStart()

long C3DShape::DrawFinish()
  {
  if (IsTransparent())
    {
    if ( (m_nChangedOptions & OPT_BLEND) == OPT_BLEND )
      {
      glDisable(GL_BLEND);
//				glEnable (GL_DEPTH_TEST);

//      glDisable(GL_ALPHA_TEST);
      }


    if ( (m_nChangedOptions & OPT_CULL_FACE) == OPT_CULL_FACE )
      {
      glDisable(GL_CULL_FACE);
      }

    } // if (m_oColor.IsTransparent())
  
  if (IsTextured())
    {
    m_poTexture->UseStop();
    }

  if (m_bSelected)
    {
    DrawSelection();
    }

  glPopMatrix();
  return GL_TRUE;
  } // 

long C3DShape::DrawSelection()
  {
  glColor3f(1,1,1);

  GLfloat cx = m_oBoundingBox.x/2; GLfloat cy = m_oBoundingBox.y/2;
  GLfloat cz = m_oBoundingBox.z/2;

  GLfloat fWidthHandleX = .05f / m_oScale.x;
  GLfloat fWidthHandleY = .05f / m_oScale.y;
  GLfloat fWidthHandleZ = .05f / m_oScale.z;

  for (int u = 0; u < 8; u++)
    {
    glPushMatrix();
    switch (u)
      {
      case 0: glTranslatef(-cx,-cy, cz); break;
      case 1: glTranslatef( cx,-cy, cz); break;
      case 2: glTranslatef( cx, cy, cz); break;
      case 3: glTranslatef(-cx, cy, cz); break;
      case 4: glTranslatef(-cx,-cy,-cz); break;
      case 5: glTranslatef( cx,-cy,-cz); break;
      case 6: glTranslatef( cx, cy,-cz); break;
      case 7: glTranslatef(-cx, cy,-cz); break;
      } // switch (u)

    BoxPlanesMake(fWidthHandleX, fWidthHandleY, fWidthHandleZ);

    glPopMatrix();
    }
  return GL_TRUE;
  } // long C3DShape::DrawSelection()

long C3DShape::DisplayListsAllocate()
  {
  if (glIsList(m_nIdDisplayList) == GL_FALSE)
    {
    m_nIdDisplayList      = glGenLists(2);
    if (glIsList(m_nIdDisplayList) == GL_TRUE)
      {
      m_nIdDisplayListQuick = m_nIdDisplayList+1;
      } // if (glIsList(m_nIdDisplayList) == GL_FALSE)
    else
      {
      m_nIdDisplayList = -1;
      }
    } // if (glIsList(m_nIdDisplayList) == GL_FALSE)
  return m_nIdDisplayList != -1;
  }

long C3DShape::Draw(bool bQuick)
  {
  if ( DrawStart() == 1 )
    {
    if ( m_bChanged )
      {
      DisplayListMake();
      }
    if ( m_nIdDisplayList >= 0 )
      {
      glCallList( bQuick ? m_nIdDisplayListQuick : m_nIdDisplayList );
      }
    else // if ( m_nIdDisplayList >= 0 )
      {
      if (bQuick)
        {
        DrawQuick();
        }
      else // if (bQuick)
        {
        DrawNormal();
        } // else if (bQuick)
      } // if ( m_nIdDisplayList >= 0 )
    DrawFinish();
    } // if ( DrawStart() == 1 )
    DrawSelection();
    DrawNormal();
  return GL_TRUE;
  } // long C3DShape::Draw()

long C3DShape::DrawNormal()
  {
  BoxPlanesMake(m_oBoundingBox.x, m_oBoundingBox.y, m_oBoundingBox.z);
  return GL_TRUE;
  } // long C3DShape::DrawNormal()

long C3DShape::DrawQuick()
  {
  BoxPlanesMakeWired(m_oBoundingBox.x, m_oBoundingBox.y, m_oBoundingBox.z);
  return GL_TRUE;
  } // long C3DShape::DrawQuick()

long C3DShape::DisplayListMake()
  {
  if (m_bChanged == false)         return 1;
  if (DisplayListsAllocate() == 0) return 0;

  glNewList(m_nIdDisplayList, GL_COMPILE);
  BoxPlanesMake(m_oBoundingBox.x, m_oBoundingBox.y, m_oBoundingBox.z);
  glEndList();

  glNewList(m_nIdDisplayListQuick, GL_COMPILE);
  BoxPlanesMakeWired(m_oBoundingBox.x, m_oBoundingBox.y, m_oBoundingBox.z);
  glEndList();

  m_bChanged = false;

  return GL_TRUE;
  } // long C3DShape::DisplayListMake()

long C3DShape::Scale(const C3DPoint &roScale)
  {
  if ( *const_cast<C3DPoint*>(&roScale) != 1.f )
    {
    m_bChanged = true;
    m_oScale *= roScale;
    }
  return GL_TRUE;
  } // long C3DShape::Scale(C3DPoint &roScale)

long C3DShape::Scale(GLfloat fScaleX, GLfloat fScaleY, GLfloat fScaleZ)
  {
  return Scale( C3DPoint(fScaleX, fScaleY, fScaleZ) );
  } // long C3DShape::Scale(GLfloat fScaleX, GLfloat fScaleY, GLfloat fScaleZ)

long C3DShape::ScaleTo(const C3DPoint &roScale)
  {
  if (m_oScale != roScale)
    {
    m_bChanged = true;
    m_oScale   = roScale;
    }
  return GL_TRUE;
  } // long C3DShape::ScaleTo(C3DPoint &roScale)

long C3DShape::ScaleTo(GLfloat fScaleX, GLfloat fScaleY, GLfloat fScaleZ)
  {
  return ScaleTo( C3DPoint(fScaleX, fScaleY, fScaleZ) );
  } // long C3DShape::ScaleTo(GLfloat fScaleX, GLfloat fScaleY, GLfloat fScaleZ)

long C3DShape::Rotate(const C3DPoint &roAngle)
  {
  if ( *const_cast<C3DPoint*>(&roAngle) != 0.0f)
    {
    m_bChanged = true;
    m_oAngle += roAngle;
    }
  return GL_TRUE;
  } // long C3DShape::Rotate(C3DPoint &roAngle)

long C3DShape::Rotate(GLfloat fAngleX, GLfloat fAngleY, GLfloat fAngleZ)
  {
  return Rotate( C3DPoint(fAngleX, fAngleY, fAngleZ) );
  } // long C3DShape::Rotate(GLfloat fAngleX, GLfloat fAngleY, GLfloat fAngleZ)

long C3DShape::RotateTo(const C3DPoint &roAngle)
  {
  if (m_oAngle != roAngle)
    {
    m_bChanged = true;
    m_oAngle = roAngle;
    }
  return GL_TRUE;
  } // long C3DShape::RotateTo(C3DPoint &roAngle)

long C3DShape::RotateTo(GLfloat fAngleX, GLfloat fAngleY, GLfloat fAngleZ)
  {
  return RotateTo( C3DPoint(fAngleX, fAngleY, fAngleZ) );
  } // long C3DShape::RotateTo(GLfloat fAngleX, GLfloat fAngleY, GLfloat fAngleZ)

long C3DShape::RotateX(GLfloat fAngle)
  {
  return Rotate( C3DPoint(fAngle, 0, 0) );
  }  // long C3DShape::RotateX(GLfloat fAngle)

long C3DShape::RotateY(GLfloat fAngle)
  {
  return Rotate( C3DPoint(0, fAngle, 0) );
  }  // long C3DShape::RotateY(GLfloat fAngle)

long C3DShape::RotateZ(GLfloat fAngle)
  {
  return Rotate( C3DPoint(0, 0, fAngle) );
  }  // long C3DShape::RotateZ(GLfloat fAngle)

long C3DShape::RotateXTo(GLfloat fAngle)
  {
  return m_oAngle.XSet(fAngle);
  }  // long C3DShape::RotateXTo(GLfloat fAngle)

long C3DShape::RotateYTo(GLfloat fAngle)
  {
  return m_oAngle.YSet(fAngle);
  }  // long C3DShape::RotateYTo(GLfloat fAngle)

long C3DShape::RotateZTo(GLfloat fAngle)
  {
  return m_oAngle.ZSet(fAngle);
  }  // long C3DShape::RotateZTo(GLfloat fAngle)

const C3DPoint& C3DShape::RotateGet()
  {
  return m_oAngle;
  } // const C3DPoint& C3DShape::RotateGet()

long C3DShape::AlphaSet(GLfloat nA)
  {
  if (m_oColor.A != nA)
    {
    m_bChanged = true;
    return m_oColor.AlphaSet(nA);
    }
  return GL_TRUE;
  } // long C3DShape::AlphaSet(GLfloat nA)

long C3DShape::AlphaOff()
  {
  m_oColor.A = SHAPE_ALPHA_SOLID;
  return GL_TRUE;
  } // long C3DShape::AlphaOff()

GLfloat C3DShape::AlphaGet()
  {
  return m_oColor.AlphaGet();
  } // GLfloat C3DShape::AlphaGet()

long C3DShape::ColorSet(const C3DColor &roColor)
  {
  if (m_oColor != roColor)
    {
    m_bChanged = true;
    m_oColor = roColor;
    }
  return GL_TRUE;
  } // long C3DShape::ColorSet(const C3DColor &roColor)

long C3DShape::ColorSet(GLfloat nColor)
  {
  if ( m_oColor != nColor )
    {
    m_bChanged = true;
    m_oColor   = nColor;
    }
  return GL_TRUE;
  }

#ifdef WIN32
long C3DShape::ColorSet(COLORREF stColor)
  {
  return ColorSet( C3DColor((GLfloat)GetRValue(stColor)/255, (GLfloat)GetGValue(stColor)/255, (GLfloat)GetBValue(stColor)/255) );
  }
#endif // WIN32

long C3DShape::ColorSet(GLfloat nColorR, GLfloat nColorG,GLfloat nColorB, GLfloat nColorA )
  {
  return ColorSet( C3DColor(nColorR, nColorG, nColorB, nColorA) );
  }

const C3DColor& C3DShape::ColorGet()
  {
  return m_oColor;
  } // const C3DColor& C3DShape::ColorGet()

long C3DShape::MaterialSet(const C3DMaterial& roMaterial)
  {
  if (m_poMaterial == 0)
    {
    m_poMaterial = new C3DMaterial;
    }
  *m_poMaterial = roMaterial;
  return GL_TRUE;
  } // long C3DShape::MaterialSet(const C3DMaterial& roMaterial)

long C3DShape::MaterialSet(GLenum eProperty, GLfloat p1, GLfloat p2, GLfloat p3, GLfloat p4)
  {
  if (m_poMaterial == 0)
    {
    m_poMaterial = new C3DMaterial;
    }
  m_poMaterial->PropertySet(eProperty, p1, p2, p3, p4);
  return GL_TRUE;
  } // long C3DShape::MaterialSet(GLenum eProperty, GLfloat p1, GLfloat p2, GLfloat p3, GLfloat p4)

const GLfloat* C3DShape::MaterialGet(GLenum eProperty)
  {
  if (m_poMaterial == 0)
    {
    return 0;
    }
  return m_poMaterial->PropertyGet(eProperty);
  } // const GLfloat* C3DShape::MaterialSet(GLenum eProperty)

const C3DMaterial* C3DShape::MaterialGet()
  {
  return m_poMaterial;
  } // const C3DMaterial& C3DShape::MaterialSet()

long C3DShape::MaterialFaceSet(GLenum eFace)
  {
  if (m_poMaterial == 0)
    {
    return GL_FALSE;
    }
  m_poMaterial->FaceSet(eFace);
  return GL_TRUE;
  } // long C3DShape::FaceGet(GLenum eFace)

GLenum C3DShape::MaterialFaceGet()
  {
  if (m_poMaterial == 0)
    {
    return GL_NONE;
    }
  return m_poMaterial->FaceGet();
  } // GLenum C3DShape::FaceGet()

long C3DShape::TextureUse(const string& pszImageFileName)
  {
  if (m_poTexture == 0)
    {
    m_poTexture = new C3DTexture;
    }
  return m_poTexture->LoadImage(pszImageFileName);
  } // long C3DShape::TextureUse(const string& pszImageFileName)

long C3DShape::TextureEnvironmentModeSet(bool bEnvironment)
  {
  return m_poTexture->EnvironmentModeSet(bEnvironment);
  }

long C3DShape::ColorProfileSet(bool bOn)
  {
  if (bOn == true)
    {
    m_nFaceSpezials |=  FS_COLOR_PROFIL;
    }
  else
    {
    m_nFaceSpezials &= ~FS_COLOR_PROFIL;
    }
  return GL_TRUE;
  } // long C3DShape::ColorProfileSet(bool bOn)

long C3DShape::Scale(GLfloat n)
  {
  if (n != 1)
    {
    m_bChanged = true;
    m_oScale  *= n;
    }
  return GL_TRUE;
  } // long C3DShape::Scale(GLfloat n)

long C3DShape::ScaleTo(GLfloat n)
  {
  if (m_oScale != n)
    {
    m_bChanged = true;
    m_oScale   = n;
    }
  return GL_TRUE;
  } // long C3DShape::ScaleTo(GLfloat n)

const C3DPoint& C3DShape::ScaleGet()
  {
  return m_oScale;
  } // const C3DPoint& C3DShape::ScaleGet()

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

void C3DShape::TextureRepeatSet(GLfloat xr, GLfloat yr)
{
	m_fTextureRepeatX = xr;
	m_fTextureRepeatY = yr;
}

GLfloat C3DShape::TextureRepeatXGet()
{
	return m_fTextureRepeatX;
}

GLfloat C3DShape::TextureRepeatYGet()
{
	return m_fTextureRepeatY;
}
