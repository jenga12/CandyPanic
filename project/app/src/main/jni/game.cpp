/*
 *	File：game.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：ゲーム処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "game.h"
#include "Framework/2DSprite.h"
#include "Framework/2DPolygon.h"
#include "PanelManager.h"
#include "Framework/MyMath.h"
#include "Framework/sound.h"
#include "timer.h"
#include "player.h"
#include "enemy.h"
#include "Framework/MainManager.h"
#include "title.h"


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
//					CGame クラス
//*************************************************
/*
 *	コンストラクタ
 */
CGame :: CGame(){
	
}

/*
 * クラス名：CGame
* 関数名：Init()
* 内容：初期化処理
*/
int CGame :: Init(void){
    /*** ゲーム画面で使用するオブジェクトを全て生成 ***/
    Vec2 size(1024.0f, 1024.0f);
    Vec2 pos(640.0f, 360.0f);
    m_pBackground = C2DSprite :: Create("game/area_back.img", &size, 12);
    m_pBackground->SetPosition(&pos);
    m_pBackground->LinkList(OBJECT_2D_GAME_BACKGROUND);

    size = Vec2(2048.0f, 1024.0f);
    m_pLayout = C2DSprite :: Create("game/game_layout.img", &size, 8);
    m_pLayout->SetPosition(&pos);
    m_pLayout->LinkList(OBJECT_2D_GAME_LAYOUT);

    size = Vec2(256.0f, 256.0f);
    pos = Vec2(145.0f, 120.0f);
    m_apFrame[0] = C2DSprite :: Create("game/player_frame.img", &size, 7);
    m_apFrame[0]->SetPosition(&pos);
    m_apFrame[0]->LinkList(OBJECT_2D_GAME_LAYOUT);

    pos = Vec2(1135.0f, 120.0f);
    m_apFrame[1] = C2DSprite :: Create("game/enemy_frame.img", &size, 7);
    m_apFrame[1]->SetPosition(&pos);
    m_apFrame[1]->LinkList(OBJECT_2D_GAME_LAYOUT);

    VERTEX_2D aVtx[5];
    aVtx[0].pos = Vec2(-125.0f, -19.0f);
    aVtx[1].pos = Vec2(105.0f, -19.0f);
    aVtx[2].pos = Vec2(125.0f, 0.0f);
    aVtx[3].pos = Vec2(105.0f, 19.0f);
    aVtx[4].pos = Vec2(-125.0f, 19.0f);
    aVtx[0].clr = Color_32(1.0f, 1.0f, 1.0f, 1.0f);
    aVtx[1].clr = Color_32(1.0f, 1.0f, 1.0f, 1.0f);
    aVtx[2].clr = Color_32(0.6f, 0.6f, 0.6f, 1.0f);
    aVtx[3].clr = Color_32(0.2f, 0.2f, 0.2f, 1.0f);
    aVtx[4].clr = Color_32(0.2f, 0.2f, 0.2f, 1.0f);

    pos = Vec2(145.0f, 300.0f);
    m_apBackgage[0] = C2DPolygon :: Create(5, aVtx, 10);
    m_apBackgage[0]->SetPosition(&pos);
    m_apBackgage[0]->LinkList(OBJECT_2D_GAME_BACKGROUND);

    pos = Vec2(145.0f, 431.0f);
    m_apBackgage[1] = C2DPolygon :: Create(5, aVtx, 10);
    m_apBackgage[1]->SetPosition(&pos);
    m_apBackgage[1]->LinkList(OBJECT_2D_GAME_BACKGROUND);

    aVtx[0].pos = Vec2(-105.0f, -19.0f);
    aVtx[1].pos = Vec2(125.0f, -19.0f);
    aVtx[2].pos = Vec2(125.0f, 19.0f);
    aVtx[3].pos = Vec2(-105.0f, 19.0f);
    aVtx[4].pos = Vec2(-125.0f, 0.0f);
    aVtx[0].clr = Color_32(1.0f, 1.0f, 1.0f, 1.0f);
    aVtx[1].clr = Color_32(1.0f, 1.0f, 1.0f, 1.0f);
    aVtx[2].clr = Color_32(0.2f, 0.2f, 0.2f, 1.0f);
    aVtx[3].clr = Color_32(0.2f, 0.2f, 0.2f, 1.0f);
    aVtx[4].clr = Color_32(0.6f, 0.6f, 0.6f, 1.0f);

    pos = Vec2(1135.0f, 300.0f);
    m_apBackgage[2] = C2DPolygon :: Create(5, aVtx, 10);
    m_apBackgage[2]->SetPosition(&pos);
    m_apBackgage[2]->LinkList(OBJECT_2D_GAME_BACKGROUND);

    pos = Vec2(1135.0f, 431.0f);
    m_apBackgage[3] = C2DPolygon :: Create(5, aVtx, 10);
    m_apBackgage[3]->SetPosition(&pos);
    m_apBackgage[3]->LinkList(OBJECT_2D_GAME_BACKGROUND);

    m_pPlayer = CPlayer :: Create();
    m_pEnemy = CEnemy :: Create();
    m_pPanelManager = CPanelManager :: Create(m_pPlayer, m_pEnemy);
    m_pEnemy->SetPanelManager(m_pPanelManager);
    m_pTimer = CTimer :: Create();

	size = Vec2(128.0f, 256.0f);
	pos = Vec2(640.0f, 360.0f);
	m_apCountDown[0] = C2DSprite :: Create("game/3.img", &size, 1);
	m_apCountDown[0]->SetPosition(&pos);
	m_apCountDown[1] = C2DSprite :: Create("game/2.img", &size, 1);
	m_apCountDown[1]->SetPosition(&pos);
	m_apCountDown[2] = C2DSprite :: Create("game/1.img", &size, 1);
	m_apCountDown[2]->SetPosition(&pos);
	size = Vec2(1024.0f, 256.0f);
	m_apCountDown[3] = C2DSprite :: Create("game/start.img", &size, 1);
	m_apCountDown[3]->SetPosition(&pos);
	
	m_pFinish = C2DSprite :: Create("game/finish.img", &size, 1);
	m_pFinish->SetPosition(&pos);
	m_pLose = C2DSprite :: Create("game/lose.img", &size, 1);
	m_pLose->SetPosition(&pos);
	
	size = Vec2(512.0f, 256.0f);
	m_pWin = C2DSprite :: Create("game/win.img", &size, 1);
	m_pWin->SetPosition(&pos);

	m_pBGM = CSound :: Create("strawberry.wav");
	m_pBGM->Play(true, true);

	m_pFailedME = CSound :: Create("failed.wav");
	m_pSuccessME = CSound :: Create("success.wav");
	m_pWhistleSE = CSound :: Create("whistle.wav");
	m_pSECountDown = CSound :: Create("countdown.wav");

	
	m_pPhaseCountDown = new CGamePhaseCountDown(m_apCountDown, m_pSECountDown);
	m_pPhaseMain = new CGamePhaseMain(m_pPanelManager, m_pTimer, m_pPlayer, m_pEnemy);
	m_pPhaseWin = new CGamePhaseWin(m_pWin, m_pFinish, m_pPanelManager, m_pPlayer, m_pEnemy, m_pWhistleSE, m_pSuccessME);
	m_pPhaseLose = new CGamePhaseLose(m_pLose, m_pFinish, m_pPanelManager, m_pPlayer, m_pEnemy, m_pWhistleSE, m_pFailedME);
	
	m_pCurrentPhase = m_pPhaseCountDown;
	return 0;
}

/*
 * クラス名：CGame
 * 関数名：Final()
 * 内容：終了処理
 */
void CGame :: Final(void){
    m_apFrame[0]->Release();
    m_apFrame[1]->Release();
    m_pLayout->Release();
    m_pBackground->Release();
    m_apBackgage[0]->Release();
    m_apBackgage[1]->Release();
    m_apBackgage[2]->Release();
    m_apBackgage[3]->Release();
    m_pPanelManager->Release();
    m_pTimer->Release();

    m_pEnemy->Release();
    m_pPlayer->Release();
	
	m_apCountDown[0]->Destroy();
	m_apCountDown[1]->Destroy();
	m_apCountDown[2]->Destroy();
	m_apCountDown[3]->Destroy();
	m_pFinish->Destroy();
	m_pWin->Destroy();
	m_pLose->Destroy();

	m_pBGM->Pause();
	m_pBGM->Release();
	m_pSuccessME->Release();
	m_pFailedME->Release();
	m_pWhistleSE->Release();
	m_pSECountDown->Release();
	
	delete m_pPhaseCountDown;
	delete m_pPhaseMain;
	delete m_pPhaseWin;
	delete m_pPhaseLose;
}

/*
 * クラス名：CGame
 * 関数名：Update()
 * 内容：更新処理
 */
void CGame :: Update(void){
	int result = m_pCurrentPhase->Update();
	
	switch(result){
		case 1:
			m_pCurrentPhase = m_pPhaseMain;
			break;
		case 2:
		    m_pBGM->Pause();
			m_pCurrentPhase = m_pPhaseWin;
			break;
		case 3:
	        m_pBGM->Pause();
			m_pCurrentPhase = m_pPhaseLose;
			break;
	}
}

/*
 * クラス名：CGame
 * 関数名：Pause()
 * 内容：中断処理
 */
void CGame :: Pause(void){
	m_pBGM->Pause();
}

/*
 * クラス名：CGame
 * 関数名：Resume()
 * 内容：再開処理
 */
void CGame :: Resume(void){
	m_pBGM->Play(false, true);
}

//*************************************************
//			 各フェーズクラスの更新処理
//*************************************************
int CGamePhaseCountDown :: Update(void){
	
	if(m_nFrameCount == 0){
		m_ppCountDown[0]->LinkList(OBJECT_2D_COUNTDOWN);
		m_pSECountDown->Play();
	}
	
	++m_nFrameCount;
	
	if(m_nFrameCount == 240){
		m_ppCountDown[3]->UnlinkList();
		return 1;
	}
	
	if((m_nFrameCount % 60) == 0){
		m_ppCountDown[(m_nFrameCount/60) - 1]->UnlinkList();
		m_ppCountDown[m_nFrameCount/60]->LinkList(OBJECT_2D_COUNTDOWN);
	}
	
	return 0;
}

int CGamePhaseMain :: Update(void){
	m_pPanelManager->Update();
	m_pTimer->Update();
	m_pEnemy->Update();
	
	/*** 負けた ***/
	if(m_pPlayer->IsLife0()){
		return 3;
	}
	
	/*** 勝った ***/
	if(m_pEnemy->IsLife0()){
		return 2;
	}
	
	return 0;
}

int CGamePhaseWin :: Update(void){
	if(m_nFrameCount == 0){
		m_pFinish->LinkList(OBJECT_2D_LOGO);
		m_pPanelManager->ClearAll();
		m_pWhistle->Play(true, false);
	}
	
	if(m_nFrameCount == 120){
		m_pFinish->UnlinkList();
		m_pPlayer->SetPlayerFace(FACE_SMILE, 9999999);
		m_pEnemy->SetEnemyFace(FACE_BAD);
		m_pSuccess->Play(true, false);
	}
	
	if((120 <= m_nFrameCount) && (m_nFrameCount < 135)){
		m_pos.y += 30.0f;
	} else {
		m_fMove += 1.0f;
		m_pos.y += m_fMove;
		if((int)m_fMove == 20){
			m_fMove = -21.0f;
		}
	}
	
	if(m_nFrameCount == 120){
		m_pPanelManager->Fall();
		m_pWin->LinkList(OBJECT_2D_LOGO);
		
	}

	m_pPanelManager->UpdateWin();
	m_pWin->SetPosition(&m_pos);
	
	++m_nFrameCount;

	if(m_nFrameCount > 300) {
		const INPUT *pInput = CMainManager::GetInput();
		if (pInput[0].flag == 1) {
			CStateManager::SetNextState(new CTitle());
		}
	}
	
	return 0;
}

int CGamePhaseLose :: Update(void){
	if(m_nFrameCount == 0){
		m_pFinish->LinkList(OBJECT_2D_LOGO);
		m_pWhistle->Play(true, false);
	}
	
	if(m_nFrameCount == 120){
		m_pFinish->UnlinkList();
		m_pLose->LinkList(OBJECT_2D_LOGO);
		m_pPlayer->SetPlayerFace(FACE_BAD, 9999999);
		m_pEnemy->SetEnemyFace(FACE_SMILE);
		m_pFailed->Play(true, false);
	}
	
	if((120 <= m_nFrameCount) && (m_nFrameCount < 135)){
		m_pos.y += 30.0f;
	}
	
	m_pLose->SetPosition(&m_pos);
	
	++m_nFrameCount;

	if(m_nFrameCount > 300) {
		const INPUT *pInput = CMainManager::GetInput();
		if (pInput[0].flag == 1) {
			CStateManager::SetNextState(new CTitle());
		}
	}
	
	return 0;
}