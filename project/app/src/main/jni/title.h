/*
 *	File：title.h
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：タイトル処理クラス定義
 */

#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "Framework/state.h"
#include "Framework/phase.h"
#include "Framework/Vector2D.h"

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

class CTitlePhaseLogoAnim : public CPhase{
	public:
		CTitlePhaseLogoAnim(C2DSprite *pLogo):
				m_pLogo(pLogo),
				m_fScale(0.0f),
				m_fRot(0.0f),
				m_nFrameCount(0){

		}

		~CTitlePhaseLogoAnim(){}
		virtual int Update(void);            // 更新処理

	private:
		float m_fRot;                          // 向き
		float m_fScale;                        // 大きさ
		C2DSprite *m_pLogo;                     // タイトルロゴ
		unsigned int m_nFrameCount;           // フレームカウンタ
};

class CTitlePhaseTapWait : public CPhase{
	public:
		CTitlePhaseTapWait(C2DSprite *pTap):
				m_pTap(pTap),
				m_nFrameCount(0){

		};

		~CTitlePhaseTapWait(){};
		virtual int Update(void);

	private:
		C2DSprite *m_pTap;                                  // tap to start
		unsigned int m_nFrameCount;                       // フレームカウンタ
		static const unsigned int SWITCH_FRAME = 31;     // tap to start 表示切替時間
		static const unsigned int FRAME_RESET = 63;     // フレームカウンタリセット
};

class CTitlePhaseNext : public CPhase{
	public:
		CTitlePhaseNext(C2DSprite *pTap):
				m_pTap(pTap),
				m_nFrameCount(0){

		}

		~CTitlePhaseNext(){};
		virtual int Update(void);

	private:
		C2DSprite *m_pTap;                               // tap to start
		unsigned int m_nFrameCount;                    // フレームカウンタ
		static const unsigned int SWITCH_FRAME = 3;  // tap to start 表示切り替え時間
		static const unsigned int FRAME_RESET = 7;   // フレームカウンタリセット
};

class CTitle : public CState {
	public:
		CTitle();                        // コンストラクタ
		~CTitle() { };                    // デストラクタ

		virtual int Init(void);            // 初期化処理
		virtual void Final(void);        // 終了処理
		virtual void Update(void);        // 更新処理
		virtual void Pause(void);        // 中断処理
		virtual void Resume(void);        // 再開処理

	private:
		C2DSprite *m_pLogo;                 // タイトルロゴ
		C2DSprite *m_pTap;                  // tap to start
		C2DSprite *m_pBackground;           // 背景

		CPhase *m_pCurrentPhase;            // 現在のフェーズ
		CTitlePhaseLogoAnim *m_pLogoAnim;   // ロゴアニメーションフェーズ
		CTitlePhaseTapWait *m_pTapWait;     // タップ待ちフェーズ
		CTitlePhaseNext *m_pNext;           // ステート変更フェーズ
};

/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif