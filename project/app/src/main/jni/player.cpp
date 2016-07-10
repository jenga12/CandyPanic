/*
 *	File：player.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：プレイヤー処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "player.h"
#include "Framework/2DPolygon.h"
#include "Framework/2DSprite.h"


/******************************************************************************/
/*                               静的変数初期化                               */
/******************************************************************************/


/******************************************************************************/
/*                                  定数定義                                  */
/******************************************************************************/


/******************************************************************************/
/*                               グローバル変数                               */
/******************************************************************************/
static Color_32 g_ColorCyan[5] = {
	Color_32(1.0f, 1.0f, 1.0f, 1.0f),
	Color_32(1.0f, 1.0f, 1.0f, 1.0f),
	Color_32(0.5f, 1.0f, 1.0f, 1.0f),
	Color_32(0.0f, 1.0f, 1.0f, 1.0f),
	Color_32(0.0f, 1.0f, 1.0f, 1.0f)
};

static Color_32 g_ColorYellow[5] = {
	Color_32(1.0f, 1.0f, 1.0f, 1.0f),
	Color_32(1.0f, 1.0f, 1.0f, 1.0f),
	Color_32(1.0f, 1.0f, 0.5f, 1.0f),
	Color_32(1.0f, 1.0f, 0.0f, 1.0f),
	Color_32(1.0f, 1.0f, 0.0f, 1.0f)
};

static Color_32 g_ColorRed[5] = {
	Color_32(1.0f, 1.0f, 1.0f, 1.0f),
	Color_32(1.0f, 1.0f, 1.0f, 1.0f),
	Color_32(1.0f, 0.5f, 0.5f, 1.0f),
	Color_32(1.0f, 0.0f, 0.0f, 1.0f),
	Color_32(1.0f, 0.0f, 0.0f, 1.0f)
};

/******************************************************************************/
/*                                 クラス実装                                 */
/******************************************************************************/
//*************************************************
//					CPlayer クラス
//*************************************************
/*
 *	コンストラクタ
 */
CPlayer :: CPlayer():
m_nLife(250*LIFE_SCALE),
m_nFrameCount(0),
m_nCurrentFace(FACE_SMILE){
	
}

/*
 * クラス名：CPlayer
 * 関数名：Create()
 * 内容：インスタンス生成
 */
CPlayer *CPlayer :: Create(void){
	CPlayer *p = new CPlayer();
	p->Init();
	return p;
}

/*
 * クラス名：CPlayer
 * 関数名：Init()
 * 内容：初期化処理
 */
void CPlayer :: Init(void){
	Vec2 pos(145.0f, 120.0f);
	Vec2 size(128.0f, 128.0f);
	Vec2 uv(0.0f, 0.0f);
	Vec2 TexSize(0.25f, 0.5f);
	
	m_pIcon = C2DSprite :: Create("game/player.img", &size, 6);
	m_pIcon->SetPosition(&pos);
	m_pIcon->SetTexCoord(&uv, &TexSize);
	m_pIcon->LinkList(OBJECT_2D_PLAYER_ICON);
	
	VERTEX_2D aVtx[5];
	aVtx[0].pos = Vec2(-125.0f, -19.0f);
    aVtx[1].pos = Vec2(105.0f, -19.0f);
    aVtx[2].pos = Vec2(125.0f, 0.0f);
    aVtx[3].pos = Vec2(105.0f, 19.0f);
    aVtx[4].pos = Vec2(-125.0f, 19.0f);
    aVtx[0].clr = Color_32(1.0f, 1.0f, 1.0f, 1.0f);
    aVtx[1].clr = Color_32(1.0f, 1.0f, 1.0f, 1.0f);
    aVtx[2].clr = Color_32(0.5f, 1.0f, 1.0f, 1.0f);
    aVtx[3].clr = Color_32(0.0f, 1.0f, 1.0f, 1.0f);
    aVtx[4].clr = Color_32(0.0f, 1.0f, 1.0f, 1.0f);
	
	pos = Vec2(145.0f, 300.0f);
	m_pLife = C2DPolygon :: Create(5, aVtx, 9);
	m_pLife->SetPosition(&pos);
	m_pLife->LinkList(OBJECT_2D_GAGE);
	
	pos = Vec2(-105.0f, 431.0f);
	m_pDensity = C2DPolygon :: Create(5, aVtx, 9);
	m_pDensity->SetPosition(&pos);
	m_pDensity->LinkList(OBJECT_2D_GAGE);
}

/*
 * クラス名：CPlayer
 * 関数名：Release()
 * 内容：インスタンス破棄
 */
void CPlayer :: Release(void){
	m_pIcon->Release();
	m_pLife->Release();
	m_pDensity->Release();
	delete this;
}

/*
 * クラス名：CPlayer
 * 関数名：Update()
 * 内容：更新処理
 * 引数：fDensity			;密度
 *       bErase             ;パネル消しフラグ
 * 返却値：ライフ0で1, それ以外は0
 */
int CPlayer :: Update(float fDensity, bool bErase) {
	int nDensity = (int) (250.0f * fDensity);

	/*** 密度ゲージの色分け ***/
	if(fDensity >= 0.99f){
		m_pDensity->SetColor(g_ColorRed);
		if(!bErase) {
			m_nLife -= 50;
		}
	} else if(fDensity >= 0.95f) {
		m_pDensity->SetColor(g_ColorRed);
		if(!bErase) {
			m_nLife -= 2;
		}

	} else if(fDensity >= 0.85f) {
		m_pDensity->SetColor(g_ColorRed);
		if(!bErase) {
			--m_nLife;
		}
	} else if(fDensity >= 0.8f){
		m_pDensity->SetColor(g_ColorRed);
		
	} else if(fDensity >= 0.6f){		
		m_pDensity->SetColor(g_ColorYellow);
		
	} else {
		m_pDensity->SetColor(g_ColorCyan);
	}

	if(m_nLife > LIFE_SCALE * 250){
		m_nLife = 0;
		return 1;
	}
	
	Vec2 pos(-105.0f + nDensity, 431.0f);
	m_pDensity->SetPosition(&pos);
	
	/*** 体力ゲージの色分け ***/
	if(m_nLife >= 125 * LIFE_SCALE){
		m_pLife->SetColor(g_ColorCyan);
		m_nCurrentFace = FACE_SMILE;

		if(m_nFrameCount == 0){
			Vec2 size(0.25f, 0.5f);
			m_pIcon->SetTexCoord(&g_FaceUV[m_nCurrentFace], &size);
		}
		
	} else if(m_nLife >= 63 * LIFE_SCALE){
		m_pLife->SetColor(g_ColorYellow);
		m_nCurrentFace = FACE_NORMAL;

		if(m_nFrameCount == 0){
			Vec2 size(0.25f, 0.5f);
			m_pIcon->SetTexCoord(&g_FaceUV[m_nCurrentFace], &size);
		}
	} else {
		m_pLife->SetColor(g_ColorRed);
		m_nCurrentFace = FACE_BAD;

		if(m_nFrameCount == 0){
			Vec2 size(0.25f, 0.5f);
			m_pIcon->SetTexCoord(&g_FaceUV[m_nCurrentFace], &size);
		}
	}
	
	pos = Vec2(-105.0f + (m_nLife / LIFE_SCALE), 300.0f);
	m_pLife->SetPosition(&pos);
	
	if(m_nFrameCount){
		++m_nFrameCount;
		if(m_nFrameCount == m_nFrame){
			m_nFrameCount = 0;
			Vec2 size(0.25f, 0.5f);
			m_pIcon->SetTexCoord(&g_FaceUV[m_nCurrentFace], &size);
		}
	}

	return 0;
}

/*
 * クラス名：CPlayer
 * 関数名：SetPlayerFace()
 * 内容：表情を変える
 * 引数：face			;表情番号
 *		 frame			;フレーム数
 */
void CPlayer :: SetPlayerFace(FACE_TYPE face, int frame){
	Vec2 size(0.25f, 0.5f);
	m_pIcon->SetTexCoord(&g_FaceUV[face], &size);
	m_nFrameCount = 1;
	m_nFrame = frame;
}