/***************************************************************************
                          3DTexture.cpp  -  description
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


#include "3DTexture.h"

#include <fstream>

#include <cstring> //memset


using namespace N3DCpp;
using namespace std;

C3DTexture::CMapFileName2BitmapData C3DTexture::s_moTextures;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DTexture::C3DTexture()
  {
  InitBasics();
  }
/*
C3DTexture::C3DTexture(const string & sImageFileName, bool bIsDIB)
  {
  InitBasics();
  LoadImage(sImageFileName);
  }
*/
C3DTexture::~C3DTexture()
  {
  FreeTexture();
  }

void C3DTexture::InitBasics()
  {
  m_poBitmapData     = 0;
  m_sImageFileName   = "";
  m_nID              = 0;
  m_bEnvironmentMode = false;
  m_nDimensions      = 0;
  } // void C3DTexture::InitBasics()

void C3DTexture::FreeTexture()
  {

  glDeleteTextures(1, &m_nID);

  m_sImageFileName = "";
  m_poBitmapData   = 0;
  m_nID            = 0;
  } // void C3DTexture::FreeImageMemory()

long C3DTexture::LoadImage(const string & sImageFileName)
  {
  CMapFileName2BitmapData::iterator it = s_moTextures.find(sImageFileName);

  if (it != s_moTextures.end() )
    {
    m_poBitmapData = (CBitmapData*) it->second;
    }
  else // if (it != s_moTextures.end() )
    {
    m_sImageFileName = sImageFileName;
  	m_poBitmapData = BitmapLoad(sImageFileName);
    if (m_poBitmapData != 0)
      {
      s_moTextures[m_sImageFileName] = m_poBitmapData;
      }
    } // if (it != s_moTextures.end() )

  if ( m_poBitmapData != 0 )
    {
    glGenTextures(1, &m_nID);
  	return 1;
    }

  return 0;
  } // long C3DTexture::LoadDIB()

long C3DTexture::EnvironmentModeSet(bool bEnvironment)
  {
  m_bEnvironmentMode = bEnvironment;
  return 1;
  } // 

bool C3DTexture::EnvironmentModeGet()
  {
  return m_bEnvironmentMode;
  } // 

long C3DTexture::UseStart()
  {
  if (m_bEnvironmentMode == true)
    {
    return UseEnvironment();
    }
  return UsePlain();
  } // long C3DTexture::UseStart(bool bEnvironment)

long C3DTexture::UseStop()
  {
  glDisable(GL_TEXTURE_2D);
  return 0;
  }

long C3DTexture::UseEnvironment()
  {
  if ( m_poBitmapData == 0 )
    {
    return 0;
    }
  glBindTexture(GL_TEXTURE_2D, m_nID);


    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

	
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
/*
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
*/
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_poBitmapData->Width(), m_poBitmapData->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_poBitmapData->Bits());
//GL_BGR_EXT ersetzt da Bitmaps unter Win im BGR Farbcode vorliegen 6-04-09 RS
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_poBitmapData->Width(), m_poBitmapData->Height(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_poBitmapData->Bits());

  // ENV:
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);

  glEnable(GL_TEXTURE_2D);

  return 1;
  } // long C3DTexture::UseEnvironment()


long C3DTexture::UsePlain()
  {
  if ( m_poBitmapData == 0 )
    {
    return 0;
    }

	// Create Texture
	glBindTexture(GL_TEXTURE_2D, m_nID);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_poBitmapData->Width(), m_poBitmapData->Height(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_poBitmapData->Bits());

  // NOT ENV
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  
  //glEnable(GL_TEXTURE_GEN_S);
  //glEnable(GL_TEXTURE_GEN_T);

  glEnable(GL_TEXTURE_2D);

  return 1;
  } // long C3DTexture::UsePlain()


/*
      if (envMap)
        {
        glBindTexture(GL_TEXTURE_2D, texId2);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        }
      else
        {
        glBindTexture(GL_TEXTURE_2D, texId1);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        }
*/


C3DTexture::CBitmapData* C3DTexture::BitmapLoad(const string& rsFileName)
  {
  CBitmapData* poBitmapData = 0;

  try
    {
    ifstream oFile(rsFileName.c_str(), ios::in | ios::binary);

    short as[0x0c];
    memset(as, 0x00, sizeof(as));
    oFile.read( (char*)as, sizeof(as) );


    if (as[0x00] != 0x4d42)
      {
      // not a bitmap file
      return 0;
      }

//    oFile.seekg(0x24);
    oFile.seekg(*(char*)&as[0x01]);
    oFile.seekg(36);
    
    long x = as[0x09];
    long y = as[0x0b];

    GLubyte* pbBits = new GLubyte[x*y*3];

    oFile.read( (char*)pbBits, x*y*3 );

    return new CBitmapData(x, y, pbBits);
    }
  catch(...)
    {
    // GPF, eof or anything else
    }

  return poBitmapData;
  } // CBitmapData* C3DTexture::BitmapLoad(sImageFileName)
