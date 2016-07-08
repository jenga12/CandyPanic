/*
 *	File：TextureManager.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：テクスチャ管理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include <stdio.h>
#include "MainManager.h"
#include "TextureManager.h"
#include "MyMath.h"


/******************************************************************************/
/*                               静的変数初期化                               */
/******************************************************************************/
CTextureManager *CTextureManager :: m_pFirst = NULL;
CTextureManager *CTextureManager :: m_pLast = NULL;


/******************************************************************************/
/*                                  定数定義                                  */
/******************************************************************************/


/******************************************************************************/
/*                               グローバル変数                               */
/******************************************************************************/


/******************************************************************************/
/*                                 クラス実装                                 */
/******************************************************************************/
//*************************************************
//				 CTextureManager クラス
//*************************************************
/*
 *	コンストラクタ
 */
CTextureManager :: CTextureManager(bool bAutoDelete):
		m_pNext(NULL),
		m_nUse(1),
		m_bAutoDelete(bAutoDelete){
	if(m_pFirst == NULL){
		m_pFirst = this;
		m_pLast = this;
		m_pPrev = NULL;
	} else {
		m_pLast->m_pNext = this;
		m_pPrev = m_pLast;
		m_pLast = this;
	}
}

/*
 *	デストラクタ
 */
CTextureManager :: ~CTextureManager(){
	if(m_pFirst == this){
		m_pFirst = m_pNext;

		if(m_pFirst == NULL){
			m_pLast = NULL;
		} else {
			m_pFirst->m_pPrev = NULL;
		}

	} else if(m_pLast == this){
		m_pLast = m_pPrev;
		m_pLast->m_pNext = NULL;

	} else {
		m_pNext->m_pPrev = m_pPrev;
		m_pPrev->m_pNext = m_pNext;
	}
}

/*
 * クラス名：CTextureManager
 * 関数名：Create()
 * 内容：インスタンス生成
 * 引数：pTexFileName				;テクスチャファイル名
 *		 bAutoDelete				;参照オブジェクトがなくなった場合に自動的にテクスチャを削除するか
 */
CTextureManager *CTextureManager :: Create(const char *pTexFileName, bool bAutoDelete){
	CTextureManager *p;

	for(p = m_pFirst; p != NULL; p = p->m_pNext){
		if(p->m_nCRC == CMath::GetCRC32(pTexFileName)){
			++(p->m_nUse);
			return p;
		}
	}

	p = new CTextureManager(bAutoDelete);

	p->LoadImage(pTexFileName);
	p->RegistTexture();

	p->m_nCRC = CMath::GetCRC32(pTexFileName);

	return p;
}

/*
 * クラス名：CTextureManager
 * 関数名：Release()
 * 内容：インスタンス破棄
 * 引数：bDelete				;テクスチャを破棄するか (参照オブジェクトがない場合のみ有効)
 */
void CTextureManager :: Release(bool bDelete){
	if(--m_nUse == 0){
		if(bDelete || m_bAutoDelete){
			glDeleteTextures(1, &m_nTexID);
			delete[] m_pTex;
			delete this;
		}
	}
}

/*
 * クラス名：CTextureManager
 * 関数名：LoadImage()
 * 内容：テクスチャ読み込み
 * 引数：pTexFileName			;テクスチャファイル名
 */
void CTextureManager :: LoadImage(const char *pTexFileName){
	AAsset *fp = AAssetManager_open(CMainManager::GetAssetManager(), pTexFileName, AASSET_MODE_UNKNOWN);

	AAsset_read(fp, &m_nWidth, 4);
	AAsset_read(fp, &m_nHeight, 4);
	AAsset_read(fp, &m_nColorType, 4);

	unsigned int nReadSize = m_nWidth * m_nHeight * m_nColorType;
	m_pTex = new unsigned char[nReadSize];

	AAsset_read(fp, m_pTex, nReadSize);

	AAsset_close(fp);
}

/*
 * クラス名：CTextureManager
 * 関数名：RegistTexture()
 * 内容：テクスチャをOpenGLに登録する
 */
void CTextureManager :: RegistTexture(void){
	glGenTextures(1, &m_nTexID);
	glBindTexture(GL_TEXTURE_2D, m_nTexID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if(m_nColorType == 4){
		glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RGBA,
				m_nWidth, m_nHeight,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				m_pTex
		);
	} else {
		glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RGB,
				m_nWidth, m_nHeight,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				m_pTex
		);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

/*
 * クラス名：CTextureManager
 * 関数名：UnregistTexture()
 * 内容：テクスチャの登録解除
 */
void CTextureManager :: UnregistTexture(void){
	glDeleteTextures(1, &m_nTexID);
}

/*
 * クラス名：CTextureManager
 * 関数名：RegistAll()
 * 内容：全テクスチャの登録のし直し
 */
void CTextureManager :: RegistAll(void){
	for(CTextureManager *p = m_pFirst; p != NULL; p = p->m_pNext){
		p->RegistTexture();
	}
}

/*
 * クラス名：CTextureManager
 * 関数名：UnregistAll()
 * 内容：全テクスチャの登録解除
 */
void CTextureManager :: UnregistAll(void){
	for(CTextureManager *p = m_pFirst; p != NULL; p = p->m_pNext){
		p->UnregistTexture();
	}
}