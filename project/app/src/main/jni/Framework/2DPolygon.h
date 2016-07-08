/*
 *	File：2DPolygon.h
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：2Dポリゴン処理クラス定義
 */

#pragma once
#ifndef _2D_POLYGON_H_
#define _2D_POLYGON_H_

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
class C2DPolygon : public C2DObject{
	public:
		static C2DPolygon *Create(unsigned int nVtxNum, VERTEX_2D *pVtx, unsigned int nPriority);	// インスタンス生成

		void SetVertex(VERTEX_2D *pVtx){		// 頂点データ設定
			for(unsigned int i = 0; i < m_VtxData.nVtxNum; ++i){
				m_VtxData.pClr[i] = pVtx[i].clr;
				m_VtxData.pPos[i] = pVtx[i].pos;
				m_VtxData.pTex[i] = pVtx[i].tex;
			}
		}

		void SetColor(const Color_32 *pColor){	// 頂点カラー設定
			for(unsigned int i = 0; i < m_VtxData.nVtxNum; ++i){
				m_VtxData.pClr[i] = pColor[i];
			}
		}

		void SetPosition(const Vec2 *pPos){    // 位置設定
			m_pos = *pPos;
		}

		void SetRotation(float fRot){			// 回転設定
			m_fRot = fRot;
		}

		void SetScaling(const Vec2 *pScl){		// 拡大縮小設定
			m_scl = *pScl;
		}

		void Destroy(void);					// インスタンス破棄

	protected:
		C2DPolygon(unsigned int nVtxNum, unsigned int nPriority);	// コンストラクタ
		~C2DPolygon(){};						// デストラクタ
		int Init(const VERTEX_2D *pVtx);		// 初期化処理

	private:
		void Draw(void);						// 描画処理

		MODEL_2D m_VtxData;						// 頂点データ
		Vec2 m_pos;								// 位置
		float m_fRot;							// 向き
		Vec2 m_scl;								// 大きさ
};

/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif