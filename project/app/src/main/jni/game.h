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
#include "Framework/phase.h"
#include "Framework/StateManager.h"


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
class CTimer;
class CPlayer;
class CEnemy;
class CSound;

class CGamePhaseCountDown : public CPhase {
	public:
		CGamePhaseCountDown(C2DSprite **ppCountDown, CSound *pSECountDown):
		m_ppCountDown(ppCountDown),
		m_pSECountDown(pSECountDown),
		m_nFrameCount(0){};				// コンストラクタ
		~CGamePhaseCountDown(){};		// デストラクタ
		
		virtual int Update(void);		// 更新処理
		
	private:
		C2DSprite **m_ppCountDown;		// カウントダウンスプライト
		CSound *m_pSECountDown;			// カウントダウンSE
		unsigned int m_nFrameCount;		// フレームカウンタ
};

class CGamePhaseMain : public CPhase {
	public:
		CGamePhaseMain(CPanelManager *pPM, CTimer *pTimer, CPlayer *pPlayer, CEnemy *pEnemy):
		m_pPanelManager(pPM),
		m_pTimer(pTimer),
		m_pPlayer(pPlayer),
		m_pEnemy(pEnemy){}					// コンストラクタ
		~CGamePhaseMain(){};				// デストラクタ
		
		virtual int Update(void);			// 更新処理
		
	private:
		CPanelManager *m_pPanelManager;		// パネル処理クラス
		CTimer *m_pTimer;					// タイマー処理クラス
		CEnemy *m_pEnemy;					// 敵処理クラス	
		CPlayer *m_pPlayer;					// プレイヤー処理クラス
};

class CGamePhaseWin : public CPhase{
	public:
		CGamePhaseWin(C2DSprite *pWin, C2DSprite *pFinish, CPanelManager *pPM, CPlayer *pPlayer, CEnemy *pEnemy, CSound *pWhistle, CSound *pSuccess):
		m_pPanelManager(pPM),
		m_pPlayer(pPlayer),
		m_pWin(pWin),
		m_nFrameCount(0),
		m_pFinish(pFinish),
		m_pSuccess(pSuccess),
		m_pWhistle(pWhistle),
		m_pos(Vec2(640.0f, -250.0f)),
		m_fMove(-20.0f),
		m_pEnemy(pEnemy){};					// コンストラクタ
		~CGamePhaseWin(){};					// デストラクタ
		
		virtual int Update(void);			// 更新処理
		
	private:
		C2DSprite *m_pFinish;				// FINISH!
		C2DSprite *m_pWin;					// WIN!
		CPanelManager *m_pPanelManager;		// パネル管理クラス
		CPlayer *m_pPlayer;					// プレイヤー処理クラス
		CEnemy *m_pEnemy;					// 敵処理クラス
		CSound *m_pWhistle;                 // ホイッスルSE
		CSound *m_pSuccess;                 // 勝利ME

		float m_fMove;						// 移動量
		Vec2 m_pos;							// WIN!表示位置
		unsigned int m_nFrameCount;			// フレームカウンタ
};

class CGamePhaseLose : public CPhase{
	public:
		CGamePhaseLose(C2DSprite *pLose, C2DSprite *pFinish, CPanelManager *pPM, CPlayer *pPlayer, CEnemy *pEnemy, CSound *pWhistle, CSound *pFailed):
		m_pPanelManager(pPM),
		m_pLose(pLose),
		m_pFinish(pFinish),
		m_pPlayer(pPlayer),
		m_nFrameCount(0),
		m_pWhistle(pWhistle),
		m_pFailed(pFailed),
		m_pos(Vec2(640.0f, -250.0f)),
		m_pEnemy(pEnemy){}						// コンストラクタ
		~CGamePhaseLose(){};					// デストラクタ
		
		virtual int Update(void);				// 更新処理
		
	private:
		C2DSprite *m_pLose;						// Lose...
		C2DSprite *m_pFinish;					// FINISH!
		CPanelManager *m_pPanelManager;			// パネル管理クラス
		CPlayer *m_pPlayer;						// プレイヤー処理クラス
		CEnemy *m_pEnemy;						// 敵処理クラス
		CSound *m_pFailed;                      // 敗北ME
		CSound *m_pWhistle;                     // ホイッスルSE
		Vec2 m_pos;								// Lose...描画位置
		unsigned int m_nFrameCount;				// フレームカウンタ
};

class CGame : public CState{
	public:
		CGame();						// コンストラクタ
		~CGame(){};						// デストラクタ
		
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
		CTimer *m_pTimer;                   // タイマー
		CPlayer *m_pPlayer;                 // プレイヤー
		CEnemy *m_pEnemy;                   // 敵
	
		C2DSprite *m_apCountDown[4];		// カウントダウン用スプライト
		C2DSprite *m_pFinish;				// FINISH!
		C2DSprite *m_pWin;					// WIN!
		C2DSprite *m_pLose;					// LOSE!
	
		CPhase *m_pCurrentPhase;			// 現在のフェーズ
		CGamePhaseCountDown *m_pPhaseCountDown;		// カウントダウンフェーズ
		CGamePhaseMain *m_pPhaseMain;				// ゲームメインフェーズ
		CGamePhaseWin *m_pPhaseWin;					// 勝ったときのゲーム終了フェーズ
		CGamePhaseLose *m_pPhaseLose;				// 負けたときのゲーム終了フェーズ

		CSound *m_pBGM;                             // BGM
		CSound *m_pFailedME;                        // 敗北時ME
		CSound *m_pSuccessME;                       // 勝利時ME
		CSound *m_pWhistleSE;                       // ホイッスルSE
		CSound *m_pSECountDown;						// カウントダウンSE
};


/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif