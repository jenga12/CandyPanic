/*
 *	File：2DSprite.h
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：2Dテクスチャ付きポリゴン処理クラス定義
 */

#pragma once
#ifndef _2D_SPRITE_H_
#define _2D_SPRITE_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "2DObject.h"
#include "Vertex2D.h"


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
class CTextureManager;

class C2DSprite : public C2DObject{
	public:
		/*** インスタンス生成 ***/
		static C2DSprite *Create(const char *pTexFileName, const Vec2 *pSize, unsigned int nPriority);
		static C2DSprite *Create(CTextureManager *pTextureManager, const Vec2 *pSize, unsigned int nPriority);

		void SetTextureManager(CTextureManager *pTextureManager){
			m_pTextureManager = pTextureManager;
		}

		void SetColor(const Color_32 *pColor){							    // 頂点カラー設定
			for(int i = 0; i < 4; ++i){
				m_VtxData.pClr[i] = *pColor;
			}
		}

		void SetTexCoord(const Vec2 *pTexUV, const Vec2 *pTexSize){		// テクスチャ座標設定
			m_VtxData.pTex[0] = Vec2(pTexUV->x, pTexUV->y + pTexSize->y);
			m_VtxData.pTex[1] = *pTexUV;
			m_VtxData.pTex[2] = *pTexUV + *pTexSize;
			m_VtxData.pTex[3] = Vec2(pTexUV->x + pTexSize->x, pTexUV->y);
		}


		void SetPosition(const Vec2 *pPos){	// 位置設定
			m_pos = *pPos;
		}

		void SetRotation(float fRot){		    // 回転設定
			m_fRot = fRot;
		}

		void SetScaling(const Vec2 *pScl){	    // 拡大縮小設定
			m_scl = *pScl;
		}

		Vec2 GetPosition(void)
		{
			return m_pos;
		}


		void Destroy(void);					// インスタンス破棄

	protected:
		C2DSprite(unsigned int nPriority);	// コンストラクタ
		~C2DSprite(){};						// デストラクタ
		int Init(const char *pTexFileName, const Vec2 *pSize);			// 初期化処理
		int Init(CTextureManager *pTextureManager, const Vec2 *pSize);	    // 初期化処理

	private:
		void Draw(void);					// 描画処理

		CTextureManager *m_pTextureManager;	// テクスチャ管理クラス
		MODEL_2D m_VtxData;					// 頂点データ
		Vec2 m_pos;							// 位置
		float m_fRot;						// 向き
		Vec2 m_scl;							// 大きさ
};

/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif