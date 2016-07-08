/*
 *	File：TextureManager.h
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：テクスチャ管理クラス定義
 */

#pragma once
#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "define.h"


/******************************************************************************/
/*                              ライブラリリンク                              */
/******************************************************************************/


/******************************************************************************/
/*                              マクロ＆定数定義                              */
/******************************************************************************/


/******************************************************************************/
/*                                 構造体定義                                 */
/******************************************************************************/


/******************************************************************************/
/*                                 クラス定義                                 */
/******************************************************************************/
class CTextureManager {
	public:
		static CTextureManager *Create(const char *pTexFileName, bool bAutoDelete = true);	// インスタンス生成
		virtual void Release(bool bDelete = false);	// インスタンス破棄
		virtual void SetTexture(void){				// テクスチャをOpenGLにセットする
			glBindTexture(GL_TEXTURE_2D, m_nTexID);
		}
	
		static void RegistAll(void);					// テクスチャを全て登録しなおす
		static void UnregistAll(void);				// テクスチャの登録を全て解除する

	protected:
		CTextureManager(bool bAutoDelete = true);		// コンストラクタ
		~CTextureManager();								// デストラクタ

	private:
		void LoadImage(const char *pTexFileName);		// テクスチャを読み込む
		void RegistTexture(void);						// テクスチャをOpenGLに登録する
		void UnregistTexture(void);					// OpenGLに登録したテクスチャを破棄
	
		unsigned char *m_pTex;						// テクスチャデータ
		unsigned short m_nWidth;						// 画像幅
		unsigned short m_nHeight;						// 画像高さ
		unsigned int m_nTexID;							// テクスチャID
		unsigned int m_nUse;							// 参照オブジェクト数
		int m_nColorType;								// カラーフォーマット
		bool m_bAutoDelete;								// 参照オブジェクトが０になった場合に自動的にテクスチャを破棄するかどうか
		unsigned int m_nCRC;							// CRCチェック値
		static CTextureManager *m_pFirst;				// リストの先頭の要素
		static CTextureManager *m_pLast;				// リストの末尾の要素
		CTextureManager *m_pPrev;						// リストの前の要素
		CTextureManager *m_pNext;						// リストの次の要素

};

/*
 *	テクスチャ管理クラス NULLver
 */
class CNullTextureManager : public CTextureManager{
	public:
		void SetTexture(void){					// テクスチャを設定
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Release(bool bDelete = false){	// インスタンス破棄
			delete this;
		}

		CNullTextureManager(){};				// コンストラクタ
		~CNullTextureManager(){};				// デストラクタ
};

/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif