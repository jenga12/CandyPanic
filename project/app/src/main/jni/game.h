/*
 *	File：game.h
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：ゲーム処理クラス定義
 */

#pragma once
#ifndef _GAME_H_
#define _GAME_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "Framework/state.h"


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
class C2DSprite;
class C2DPolygon;
class CPanelManager;

class CGame : public CState{
	public:
		CGame();						// コンストラクタ
		~CGame(){};					// デストラクタ
		
		virtual int Init(void);			// 初期化処理
		virtual void Final(void);		// 終了処理
		virtual void Update(void);		// 更新処理
		virtual void Pause(void);		// 中断処理
		virtual void Resume(void);		// 再開処理

	private:
	    C2DSprite *m_pBackground;           // エリア背景
	    C2DPolygon *m_apBackgage[4];        // ゲージ背景
	    C2DSprite *m_pLayout;               // ゲーム画面レイアウト
	    C2DSprite *m_apFrame[2];            // キャラ枠

		CPanelManager *m_pPanelManager;     // パネル管理クラス
};


/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif