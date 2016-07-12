/*
 *	File：enemy.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：敵処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "enemy.h"
#include "Framework/2DSprite.h"
#include "Framework/2DPolygon.h"
#include "PanelManager.h"
#include "Framework/MyMath.h"


/******************************************************************************/
/*                               静的変数初期化                               */
/******************************************************************************/


/******************************************************************************/
/*                                  定数定義                                  */
/******************************************************************************/


/******************************************************************************/
/*                               グローバル変数                               */
/******************************************************************************/
static const Color_32 g_ColorCyan[5] = {
	Color_32(1.0f, 1.0f, 1.0f, 1.0f),
    Color_32(1.0f, 1.0f, 1.0f, 1.0f),
    Color_32(0.2f, 1.0f, 1.0f, 1.0f),
    Color_32(0.2f, 1.0f, 1.0f, 1.0f),
    Color_32(0.6f, 1.0f, 1.0f, 1.0f)
};

static const Color_32 g_ColorYellow[5] = {
	Color_32(1.0f, 1.0f, 1.0f, 1.0f),
    Color_32(1.0f, 1.0f, 1.0f, 1.0f),
    Color_32(1.0f, 1.0f, 0.2f, 1.0f),
    Color_32(1.0f, 1.0f, 0.2f, 1.0f),
    Color_32(1.0f, 1.0f, 0.6f, 1.0f)
};

static const Color_32 g_ColorRed[5] = {
	Color_32(1.0f, 1.0f, 1.0f, 1.0f),
    Color_32(1.0f, 1.0f, 1.0f, 1.0f),
    Color_32(1.0f, 0.2f, 0.2f, 1.0f),
    Color_32(1.0f, 0.2f, 0.2f, 1.0f),
    Color_32(1.0f, 0.6f, 0.6f, 1.0f)
};


/******************************************************************************/
/*                                 クラス実装                                 */
/******************************************************************************/
//*************************************************
//					CEnemy クラス
//*************************************************
/*
 *	コンストラクタ
 */
CEnemy :: CEnemy():
m_nFrameCount(0),
m_nFaceFrameCount(0),
m_nCombo(2),
m_nLife(250*LIFE_SCALE),
m_nAttackInterval(ATTACK_INTERVAL_AVERAGE),
m_nCurrentFace(FACE_SMILE){
	
}

/*
 * クラス名：CEnemy
 * 関数名：Create()
 * 内容：インスタンス生成
 */
CEnemy *CEnemy :: Create(void){
	CEnemy *p = new CEnemy();
	p->Init();
	return p;
}

/*
 * クラス名：CEnemy
 * 関数名：Init()
 * 内容：初期化処理
 */
void CEnemy :: Init(void){
	Vec2 size(128.0f, 128.0f);
	Vec2 pos(1135.0f, 120.0f);
	Vec2 TexSize(0.25f, 0.5f);
	m_pIcon = C2DSprite :: Create("game/enemy.img", &size, 6);
	m_pIcon->SetPosition(&pos);
	m_pIcon->SetTexCoord(&g_FaceUV[FACE_SMILE], &TexSize);
	m_pIcon->LinkList(OBJECT_2D_ENEMY_ICON);
	
	VERTEX_2D aVtx[5];
	aVtx[0].pos = Vec2(-105.0f, -19.0f);
    aVtx[1].pos = Vec2(125.0f, -19.0f);
    aVtx[2].pos = Vec2(125.0f, 19.0f);
    aVtx[3].pos = Vec2(-105.0f, 19.0f);
    aVtx[4].pos = Vec2(-125.0f, 0.0f);
    aVtx[0].clr = Color_32(1.0f, 1.0f, 1.0f, 1.0f);
    aVtx[1].clr = Color_32(1.0f, 1.0f, 1.0f, 1.0f);
    aVtx[2].clr = Color_32(0.2f, 1.0f, 1.0f, 1.0f);
    aVtx[3].clr = Color_32(0.2f, 1.0f, 1.0f, 1.0f);
    aVtx[4].clr = Color_32(0.6f, 1.0f, 1.0f, 1.0f);
	
	pos = Vec2(1135.0f, 300.0f);
	m_pLife = C2DPolygon :: Create(5, aVtx, 9);
	m_pLife->SetPosition(&pos);
	m_pLife->LinkList(OBJECT_2D_GAGE);
	
	pos = Vec2(1135.0f + 250.0f, 431.0f);
	m_pAttack = C2DPolygon :: Create(5, aVtx, 9);
	m_pAttack->SetPosition(&pos);
	m_pAttack->LinkList(OBJECT_2D_GAGE);
}

/*
 * クラス名：CEnemy
 * 関数名：Release()
 * 内容：インスタンス破棄
 */
void CEnemy :: Release(void){
	m_pAttack->Release();
	m_pLife->Release();
	m_pIcon->Release();
	
	delete this;
}

/*
 * クラス名：CEnemy
 * 関数名：Update()
 * 内容：更新処理
 */
void CEnemy :: Update(void){
	/*** 体力ゲージの色分け ***/
	if(m_nLife >= 125.0f * LIFE_SCALE){
		m_pLife->SetColor(g_ColorCyan);
		m_nCurrentFace = FACE_SMILE;
		
		if(m_nFaceFrameCount == 0){
			Vec2 TexSize(0.25f, 0.5f);
			m_pIcon->SetTexCoord(&g_FaceUV[m_nCurrentFace], &TexSize);
		}
		
	} else if(m_nLife >= 63.0f * LIFE_SCALE){
		m_pLife->SetColor(g_ColorYellow);
		m_nCurrentFace = FACE_NORMAL;
		
		if(m_nFaceFrameCount == 0){
			Vec2 TexSize(0.25f, 0.5f);
			m_pIcon->SetTexCoord(&g_FaceUV[m_nCurrentFace], &TexSize);
		}
		
	} else {
		m_pLife->SetColor(g_ColorRed);
		m_nCurrentFace = FACE_BAD;
		
		if(m_nFaceFrameCount == 0){
			Vec2 TexSize(0.25f, 0.5f);
			m_pIcon->SetTexCoord(&g_FaceUV[m_nCurrentFace], &TexSize);
		}
	}
	
	/*** 攻撃開始 ***/
	if(m_nFrameCount == m_nAttackInterval){
		--m_nCombo;
		if(m_nCombo == 0){
			m_nCombo = (CMath :: GetRand() % 3) + 1;	// コンボ数の設定
			m_nAttackInterval = (CMath :: GetRand() % 120) - 60 + ATTACK_INTERVAL_AVERAGE;
			
		} else {
			m_nAttackInterval = 100;
		}
		
		m_nFrameCount = 0;
		m_nFaceFrameCount = 1;
		
		Vec2 TexSize(0.25f, 0.5f);
		m_pIcon->SetTexCoord(&g_FaceUV[FACE_ANGRY], &TexSize);
		m_pPM->PaddingGray((CMath :: GetRand() % 7) + 7);
	}
	
	/*** 攻撃表情の変化判定 ***/
	if(m_nFaceFrameCount){
		if(++m_nFaceFrameCount == 60){
			Vec2 TexSize(0.25f, 0.5f);
			m_pIcon->SetTexCoord(&g_FaceUV[m_nCurrentFace], &TexSize);
			m_nFaceFrameCount = 0;
		}
	}
	
	/*** 攻撃ゲージの色分け ***/
	++m_nFrameCount;
	float fAttackGage = (float)m_nFrameCount / (float)m_nAttackInterval;
	
	if(fAttackGage > 0.9f){
		m_pAttack->SetColor(g_ColorRed);
	} else if(fAttackGage > 0.6f){
		m_pAttack->SetColor(g_ColorYellow);
	} else {
		m_pAttack->SetColor(g_ColorCyan);
	}

	/*** 攻撃ゲージの更新 ***/
	Vec2 pos(1385.0f - fAttackGage * 250.0f, 431.0f);
	m_pAttack->SetPosition(&pos);

	/*** 体力ゲージの更新 ***/
	pos = Vec2(1385.0f - (m_nLife / LIFE_SCALE), 300.0f);
	m_pLife->SetPosition(&pos);
}

/*
 * クラス名：CEnemy
 * 関数名：Damage()
 * 内容：ダメージ処理
 * 引数：num			;与えるダメージ量
 * 返却値：倒したら1, そうでなければ0
 */
int CEnemy :: Damage(int num){
	m_nFaceFrameCount = 1;
	m_nLife -= num;
	
	Vec2 TexSize(0.25f, 0.5f);
	m_pIcon->SetTexCoord(&g_FaceUV[FACE_BAD], &TexSize);
	
	if(m_nLife > (250 * LIFE_SCALE)){
		return 1;
	}
	
	return 0;
}

/*
 * クラス名：CEnemy
 * 関数名：SetEnemyFace()
 * 内容：敵の表情を変更
 */
void CEnemy :: SetEnemyFace(FACE_TYPE face){
	Vec2 TexSize(0.25f, 0.5f);
	m_pIcon->SetTexCoord(&g_FaceUV[face], &TexSize);
}