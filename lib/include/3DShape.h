/***************************************************************************
                          3DShape.h  -  description
                             -------------------
    begin                : Sun Jan 30 2000
    copyright            : (C) 2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/

#ifndef _3DShape_H
#define _3DShape_H

#include <GL/gl.h>
#include <GL/glu.h>

//#include "3DPoint.h"
#include "3DColor.h"
#include "3DMaterial.h"
#include "3DTexture.h"

// STL
#include <vector>


typedef struct XYZ S3DFactor;
typedef struct XYZ S3DSummand;

typedef struct XYZ {
        GLfloat X;
        GLfloat Y;
        GLfloat Z;

        XYZ operator += (XYZ const & crPoint){ X+=crPoint.X; Y+=crPoint.Y, Z+=crPoint.Z; return *this; }
        XYZ operator -= (XYZ const & crPoint){ X-=crPoint.X;  Y-=crPoint.Y,  Z-=crPoint.Z;  return *this; }
        XYZ operator *= (XYZ const & crPoint) { X*=crPoint.X;  Y*=crPoint.Y,  Z*=crPoint.Z;  return *this; }
        XYZ operator /= (XYZ const & crPoint){ X/=crPoint.X;  Y/=crPoint.Y,  Z/=crPoint.Z;  return *this; }

        bool operator == (XYZ const & crPoint){ return ( X==crPoint.X & Y==crPoint.Y & Z==crPoint.Z ); }
        bool operator != (XYZ const & crPoint){ return not ( *this == crPoint );}
        
        } S3DScale, S3DSize, S3DGeometry, S3DPosition, S3DRotation;

/*
// glIsEnabled(?)
#define OPT_DEPTH_TEST      0x00000001L
#define OPT_AUTO_NORMAL     0x00000002L
#define OPT_NORMALIZE       0x00000004L
#define OPT_LINE_SMOOTH     0x00000008L
#define OPT_CULL_FACE       0x00000010L
#define OPT_COLOR_MATERIAL  0x00000020L
#define OPT_LIGHT0          0x00000040L
#define OPT_LIGHTING        0x00000080L
#define OPT_BLEND           0x00000100L

// face specials
#define FS_NONE             0x0000
#define FS_COLOR_PROFIL     0x0001
#define FS_TEXTURE          0x0002
#define FS_MATERIAL         0x0004

#define SHAPE_MODIFY_SIZE     0
#define SHAPE_MODIFY_POSITION 1
#define SHAPE_MODIFY_ANGLE    2

#define SHAPE_ALPHA_SOLID 1.f
*/

namespace N3DCpp
  {
  class C3DShape;

  using PShape = C3DShape*;
  using CVectorShapes = std::vector<C3DShape*>; 

  class C3DShape
    {
    protected:
//      static GLUquadricObj *s_pGluQuadricObj;
      GLuint m_uDisplayList{0};
      
          
    public:
        S3DGeometry m_fGeometry{1.f, 1.f, 1.f};
        S3DPosition m_fPosition{0.f, 0.f, 0.f};
        S3DRotation m_fRotation{0.f, 0.f, 0.f};

    public:
               C3DShape(); // = default;
               C3DShape(S3DGeometry const & crGeometry, S3DPosition const & crPosition, S3DRotation const & crRotation)
                    : m_fGeometry(crGeometry), m_fPosition(crPosition), m_fRotation(crRotation)
                    {}
      virtual ~C3DShape();

      virtual void  Draw();

    S3DRotation & Rotate  (S3DRotation const & crRotation){m_fRotation += crRotation; return m_fRotation;}
    S3DRotation & RotateTo(S3DRotation const & crRotation){m_fRotation  = crRotation; return m_fRotation;}

    S3DPosition & Move    (S3DPosition const & crPosition){m_fPosition += crPosition; return m_fPosition;}
    S3DPosition & MoveTo  (S3DPosition const & crPosition){m_fPosition  = crPosition; return m_fPosition;}

    S3DGeometry & Scale       (S3DScale const & crScale){m_fGeometry *= crScale; return m_fGeometry;}
    S3DGeometry & ResizeTo    (S3DSize const & crSize){m_fGeometry = crSize; return m_fGeometry;}

     void BoxPlanesMakeTextured(GLfloat cx, GLfloat  cy, GLfloat cz);

    protected:
      bool m_bNormals{ false };
      bool NormalsMake()
        {
        if (m_bNormals) return true;
        
        return true;
        }

      S3DGeometry           m_oBoundingBox{1.f, 1.f, 1.f}; 
      bool                  m_bChanged{true};
      int                   m_nIdDisplayList{ -1 };
      int                   m_nIdDisplayListQuick{ -1};
      C3DTexture            m_oTexture{ };
      C3DMaterial           m_oMaterial{ };
      short                 m_nFaceSpezials{ 0 /* FS_NONE*/ };
      bool                  m_bReceivesShadow{ false };
      GLfloat               m_fTextureRepeatX{ 1.f };//RS
      GLfloat               m_fTextureRepeatY{ 1.f };//RS
      C3DColor              m_oColor{255, 255, 255};
      long                  m_nChangedOptions{ 0 };
      bool                  m_bSelected{ true };
      bool                  m_bIsMirror{ false };

    }; // class C3DBox
  } // namespace 3DCpp

#endif // _3DBox_H


/*
    public:
      virtual bool IsTextured();
      virtual bool IsColored();
      virtual bool IsTransparent();
      virtual bool IsMaterialed();
      virtual bool IsShadowed();
      virtual bool IsMirror();


      virtual long Select(bool bSelect = true);
      virtual long Draw(bool bQuick = false);
    protected:
      virtual long DisplayListsAllocate();
      virtual long DrawNormal();
      virtual long DrawQuick();
      virtual long DrawSelection();

      virtual void BoxPlanesMake        (GLfloat cx, GLfloat cy, GLfloat cz);
      virtual void BoxPlanesMakeTextured(GLfloat cx, GLfloat cy, GLfloat cz);
      virtual void BoxPlanesMakeWired   (GLfloat cx, GLfloat cy, GLfloat cz);

		GLfloat TextureRepeatXGet ();//RS
		GLfloat TextureRepeatYGet ();//RS
		GLfloat m_fTextureRepeatX;//
		GLfloat m_fTextureRepeatY;

    public:
      virtual long            ColorSet(const S3DColor & roColor);

      virtual long    AlphaSet(GLfloat nA);
      virtual long    AlphaOff();
      virtual GLfloat AlphaGet();

      virtual       long         MaterialSet(const C3DMaterial& roMaterial);
      virtual       long         MaterialSet(GLenum eProperty, GLfloat p1, GLfloat p2 = 0.f, GLfloat p3 = 0.f, GLfloat p4 = 0.f);
      virtual const GLfloat*     MaterialGet(GLenum eProperty);
      virtual const C3DMaterial* MaterialGet();
      virtual       long         MaterialFaceSet(GLenum eFace);
      virtual       GLenum       MaterialFaceGet();

      virtual long  TextureUse(const string& pszImageFileName);
      virtual long  TextureEnvironmentModeSet(bool bEnvironment);
      virtual long  ColorProfileSet(bool bOn = true);

      virtual long  ShadowReceiveSet(bool bOn = true);
      virtual long  MirrorSet       (bool bOn = true);

    protected:
      virtual long DisplayListMake();

    }; // class C3DShape

  } // namespace N3DCpp

#endif // _3DShape_H

*/
