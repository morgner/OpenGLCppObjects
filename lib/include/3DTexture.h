/***************************************************************************
                          3DTexture.h  -  description
                             -------------------
    begin                : Sun Jan 30 2000
    copyright            : (C) 2000 by Manfred Morgner
    email                : manfred@morgner.com
 ***************************************************************************/

#ifndef _3DTexture_H
#define _3DTexture_H

#include <GL/gl.h>



#ifndef GL_BGR_EXT
#define GL_BGR_EXT 0x80E0
#endif

// STL
#include <map>
#include <string>

using namespace std;
namespace N3DCpp
  {

  class C3DTexture
    {
    protected:
      class CBitmapData
        {
        protected:
           CBitmapData();
        public:
           CBitmapData(int nWidth, int nHeight, GLubyte* pBits)
             : m_nWidth (nWidth),
               m_nHeight(nHeight),
               m_pBits  (pBits)
             {}
          ~CBitmapData()
            {
            delete m_pBits;
            }
                int      Width () { return m_nWidth;  }
                int      Height() { return m_nHeight; }
          const GLubyte* Bits  () { return m_pBits;   }
        protected:
          int      m_nWidth;
          int      m_nHeight;
          GLubyte* m_pBits;
        };

//      class CMapFileName2BitmapData : public map<string, CBitmapData*>
      class CMapFileName2BitmapData : public map<string, void*>
        {
        public:
          ~CMapFileName2BitmapData()
            {
            for (iterator it = begin(); it != end(); ++it)
              {
              delete (CBitmapData*) it->second;
              }
            } // ~CMapFileName2BitmapData()
        }; // class CMapFileName2BitmapData : public CMapStringToPtr

      static CMapFileName2BitmapData s_moTextures;

    public:
               C3DTexture();
               C3DTexture(const string & sImageFileName, bool bIsDIB);
      virtual ~C3DTexture();

      long LoadImage(const string & sImageFileName);

      long EnvironmentModeSet(bool bEnvironment);
      bool EnvironmentModeGet();

      long UseStart();
      long UseStop();

    protected:
      void InitBasics();

      CBitmapData* BitmapLoad(const string& rsFileName);

      long UseEnvironment();
      long UsePlain();

      void FreeTexture();

    protected:
      string       m_sImageFileName;
  	  CBitmapData* m_poBitmapData;
      GLuint       m_nID;

      bool         m_bEnvironmentMode;
      GLuint       m_nDimensions;

    }; // class C3DTexture

  } // namespace N3Cpp

#endif // _3DTexture_H
