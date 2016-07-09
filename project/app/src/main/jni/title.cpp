/*
 *	File：title.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：タイトル処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "title.h"
#include "Framework/2DSprite.h"
#include "Framework/MainManager.h"
#include "game.h"
#include <math.h>


/******************************************************************************/
/*                               静的変数初期化                               */
/******************************************************************************/


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
//					CTitle クラス
//*************************************************
/*
 *	コンストラクタ
 */
CTitle :: CTitle(){
	
}

/*
 * クラス名：CTitle
* 関数名：Init()
* 内容：初期化処理
*/
int CTitle :: Init(void){
	/*** タイトルで使用する各オブジェクトの生成 ***/
	Vec2 size(2048.0f, 1024.0f);
	Vec2 pos(640.0f, 360.0f);
	m_pBackground = C2DSprite :: Create("title/title_bg.img", &size, 10000);
	m_pBackground->SetPosition(&pos);
	m_pBackground->LinkList(OBJECT_2D_TITLE_BACKGROUND);

	size = Vec2(512.0f, 128.0f);
	pos = Vec2(640.0f, 620.0f);
	m_pTap = C2DSprite :: Create("title/tap.img", &size, 2);
	m_pTap->SetPosition(&pos);

	size = Vec2(1024.0f, 256.0f);
	pos = Vec2(640.0f, 200.0f);
	Vec2 scl(0.0f, 0.0f);
	m_pLogo = C2DSprite :: Create("title/logo.img", &size, 1);
	m_pLogo->SetPosition(&pos);
	m_pLogo->SetScaling(&scl);
	m_pLogo->LinkList(OBJECT_2D_TITLE_BACKGROUND);

	/*** フェーズ処理クラス生成 ***/
	m_pLogoAnim = new CTitlePhaseLogoAnim(m_pLogo);
	m_pTapWait = new CTitlePhaseTapWait(m_pTap);
	m_pNext = new CTitlePhaseNext(m_pTap);

	m_pCurrentPhase = m_pLogoAnim;

	return 0;
}

/*
 * クラス名：CTitle
 * 関数名：Final()
 * 内容：終了処理
 */
void CTitle :: Final(void){
	delete m_pLogoAnim;
	delete m_pTapWait;
	delete m_pNext;
	m_pLogo->Release();
	m_pTap->Release();
	m_pBackground->Release();
}

/*
 * クラス名：CTitle
 * 関数名：Update()
 * 内容：更新処理
 */
void CTitle :: Update(void){
	int result = m_pCurrentPhase->Update();

	switch(result){
		case 1:
			m_pCurrentPhase = m_pTapWait;
			break;
		case 2:
			m_pCurrentPhase = m_pNext;
			break;
	}
}

/*
 * クラス名：CTitle
 * 関数名：Pause()
 * 内容：中断処理
 */
void CTitle :: Pause(void){
	
}

/*
 * クラス名：CTitle
 * 関数名：Resume()
 * 内容：再開処理
 */
void CTitle :: Resume(void){
	
}

//*************************************************
//					各フェーズクラス
//*************************************************
/*
 * クラス名：CTitlePhaseLogoAnim
 * 関数名：Update()
 * 内容：更新処理
 */
int CTitlePhaseLogoAnim :: Update(void){
	/*** 一定時間で次のフェーズへ ***/
	if(++m_nFrameCount == 61){
		Vec2 org(1.0f, 1.0f);
		m_pLogo->SetRotation(0.0f);
		m_pLogo->SetScaling(&org);
		return 1;
	}

	/*** タッチされたら次のフェーズへ ***/
	const INPUT *pInput = CMainManager :: GetInput();
	if(pInput[0].flag == 1){
		Vec2 org(1.0f, 1.0f);
		m_pLogo->SetRotation(0.0f);
		m_pLogo->SetScaling(&org);
		return 1;
	}

	/*** ロゴアニメーション処理 ***/
	m_fRot += 0.33f;
	m_pLogo->SetRotation(m_fRot);
	if(m_fScale < 1.0f){
		m_fScale += 0.016f;
	}
	Vec2 scl(m_fScale, m_fScale);
	m_pLogo->SetScaling(&scl);

	return 0;
}

/*
 * クラス名：CTitlePhaseTapWait
 * 関数名：Update()
 * 内容：更新処理
 */
int CTitlePhaseTapWait :: Update(void){
	/*** タップされたら次のフェーズへ ***/
	const INPUT *pInput = CMainManager :: GetInput();
	if(pInput[0].flag == 1){

		return 2;
	}

	/*** フレームで点滅させる ***/
	if((m_nFrameCount & FRAME_RESET) == 0){
		m_nFrameCount = 0;
		m_pTap->LinkList(OBJECT_2D_TAP);
	} else if((m_nFrameCount & SWITCH_FRAME) == 0){
		m_pTap->UnlinkList();
	}

	++m_nFrameCount;

	return 0;
}

/*
 * クラス名：CTitlePhaseNext
 * 関数名：Update()
 * 内容：更新処理
 */
int CTitlePhaseNext :: Update(void){
	/*** 一定時間経過で次のステートへ ***/
	if(m_nFrameCount > 90){
		CStateManager :: SetNextState(new CGame());
	}

	/*** フレームで点滅させる ***/
	++m_nFrameCount;
	if((m_nFrameCount & FRAME_RESET) == 0){
		m_pTap->LinkList(OBJECT_2D_TAP);
	} else if((m_nFrameCount & SWITCH_FRAME) == 0){
		m_pTap->UnlinkList();
	}

	return 0;
}