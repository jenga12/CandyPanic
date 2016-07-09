/*
 *	File：StateManager.h
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：ステート管理クラス定義
 */

#pragma once
#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "2DFade.h"
#include "state.h"


/******************************************************************************/
/*                              ライブラリリンク                              */
/******************************************************************************/


/******************************************************************************/
/*                              マクロ＆定数定義                              */
/******************************************************************************/
static const unsigned char STATE_CHANGE_FADE_FRAME = 30;

enum STATE_NAME {
	STATE_UNKNOWN = 0,		// よくわからないステート
	STATE_TITLE,			// タイトル画面
	STATE_GAME,			// ゲーム画面
	STATE_MAX
};


/******************************************************************************/
/*                                 構造体定義                                 */
/******************************************************************************/


/******************************************************************************/
/*                                 クラス定義                                 */
/******************************************************************************/
class CStateManager {
	public:
		static CStateManager *Create(STATE_NAME DefaultState);	// インスタンス生成
		void Release(void);		// インスタンス破棄
		void Update(void);		// 更新処理
		void Pause(void){		// 中断処理
			m_pCurrentState->Pause();
		}
	
		void Resume(void){		// 再開処理
			m_pCurrentState->Resume();
		}

		/*** 画面遷移の実行 (次ステート設定) ***/
		static void SetNextState(CState *pNextState){
			if(m_pCurrentState == m_pNextState){
				m_pNextState = pNextState;
				m_pFade->Start(FADE_OUT, STATE_CHANGE_FADE_FRAME);
			}
		}

	private:
		CStateManager();				    	// コンストラクタ
		~CStateManager(){};					    // デストラクタ

		CState *CreateState(STATE_NAME state);	// ステート生成

		static C2DFade *m_pFade;			    // フェード処理クラス
		static CState *m_pCurrentState;		// 現在のステート
		static CState *m_pNextState;		    // 次のステート
};

/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif