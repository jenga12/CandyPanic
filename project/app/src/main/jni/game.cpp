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
#include "timer.h"


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
    /*** ゲーム画面のレイアウトを構成 ***/
    Vec2 size(1024.0f, 1024.0f);
    Vec2 pos(640.0f, 360.0f);
    m_pBackground = C2DSprite :: Create("game/area_back.img", &size, 10);
    m_pBackground->SetPosition(&pos);
    m_pBackground->LinkList(OBJECT_2D_GAME_BACKGROUND);

    size = Vec2(2048.0f, 1024.0f);
    m_pLayout = C2DSprite :: Create("game/game_layout.img", &size, 6);
    m_pLayout->SetPosition(&pos);
    m_pLayout->LinkList(OBJECT_2D_GAME_LAYOUT);

    size = Vec2(256.0f, 256.0f);
    pos = Vec2(145.0f, 120.0f);
    m_apFrame[0] = C2DSprite :: Create("game/player_frame.img", &size, 5);
    m_apFrame[0]->SetPosition(&pos);
    m_apFrame[0]->LinkList(OBJECT_2D_GAME_LAYOUT);

    pos = Vec2(1135.0f, 120.0f);
    m_apFrame[1] = C2DSprite :: Create("game/enemy_frame.img", &size, 5);
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
    m_apBackgage[0] = C2DPolygon :: Create(5, aVtx, 8);
    m_apBackgage[0]->SetPosition(&pos);
    m_apBackgage[0]->LinkList(OBJECT_2D_GAME_BACKGROUND);

    pos = Vec2(145.0f, 431.0f);
    m_apBackgage[1] = C2DPolygon :: Create(5, aVtx, 8);
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
    m_apBackgage[2] = C2DPolygon :: Create(5, aVtx, 8);
    m_apBackgage[2]->SetPosition(&pos);
    m_apBackgage[2]->LinkList(OBJECT_2D_GAME_BACKGROUND);

    pos = Vec2(1135.0f, 431.0f);
    m_apBackgage[3] = C2DPolygon :: Create(5, aVtx, 8);
    m_apBackgage[3]->SetPosition(&pos);
    m_apBackgage[3]->LinkList(OBJECT_2D_GAME_BACKGROUND);


    m_pPanelManager = CPanelManager :: Create();
    m_pTimer = CTimer :: Create();

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
}

/*
 * クラス名：CGame
 * 関数名：Update()
 * 内容：更新処理
 */
void CGame :: Update(void){
    static unsigned int nFrameCount = 0;

    ++nFrameCount;

    if(nFrameCount == 60){
        m_pPanelManager->PaddingGray(5);
    }

    m_pPanelManager->Update();
    m_pTimer->Update();
}

/*
 * クラス名：CGame
 * 関数名：Pause()
 * 内容：中断処理
 */
void CGame :: Pause(void){
	
}

/*
 * クラス名：CGame
 * 関数名：Resume()
 * 内容：再開処理
 */
void CGame :: Resume(void){
	
}