/*
 *	File：panel.h
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：パネル処理クラス定義
 */

#pragma once
#ifndef _PANEL_H_
#define _PANEL_H_ 

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "Framework/2DSprite.h"


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
class C2DAnimation;

class CPanel : public C2DSprite {
	public:
		static CPanel *Create(CTextureManager *pTextureManager, const Vec2 *pPos);			// パネルの生成
		void Update(void);						// パネルの更新
		bool IsMove(void){						// 動きがあるかたずねる
			return m_bMove || m_bErase;
		}

		void SetPosition(const Vec2 *pPos){
			m_pos = *pPos;
		}
		
		void SetTarget(const Vec2 *pPos, const Vec2 *pMove){		// 移動目標地点を設定
			m_TargetPos = *pPos;
			m_Move = *pMove;
			m_bMove = true;
		}
		
		void Erase(CTextureManager *pPanelEffectTex);				// パネルを消去する
		
	private:
		CPanel();					// コンストラクタ
		~CPanel(){};				// デストラクタ
	
		bool m_bMove;				// 移動フラグ
		bool m_bErase;				// 削除フラグ
		Vec2 m_pos;					// 現在の表示位置
		Vec2 m_TargetPos;			// 目的の表示位置
		Vec2 m_Move;				// 移動量
		C2DAnimation *m_pEffect;	// エフェクト
		int m_nFrameCount;			// フレームカウンタ
};

/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif