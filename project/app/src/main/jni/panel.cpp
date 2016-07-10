/*
 *	File：panel.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：パネル処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "panel.h"
#include "PanelManager.h"
#include "Framework/2DAnimation.h"


/******************************************************************************/
/*                               静的変数初期化                               */
/******************************************************************************/


/******************************************************************************/
/*                                  定数定義                                  */
/******************************************************************************/


/******************************************************************************/
/*                               グローバル変数                               */
/******************************************************************************/
static const unsigned char PANEL_ERASE_START_TIME = 10;
static const float PANEL_EFFECT_SCALE_TABLE[PANEL_ERASE_START_TIME] = {1.0f, 1.16f, 1.33f, 1.5f, 1.66f, 1.83f, 2.0f, 1.5f, 1.0f, 0.5f};



/******************************************************************************/
/*                                 クラス実装                                 */
/******************************************************************************/
//*************************************************
//					CPanel クラス
//*************************************************
/*
 *	コンストラクタ
 */
CPanel :: CPanel():
C2DSprite(9),
m_bErase(false),
m_bMove(false){
	
}

/*
 * クラス名：CPanel
 * 関数名：Create()
 * 内容：インスタンス生成
 * 引数：pTextureManager			;使用テクスチャ(読み込み済み)
 *		 pPos						;初期座標
 */
CPanel *CPanel :: Create(CTextureManager *pTextureManager, const Vec2 *pPos){
	CPanel *p = new CPanel();
	p->Init(pTextureManager, &PanelSize);
	p->m_pos = *pPos;
	p->m_TargetPos = *pPos;

	Vec2 size(64.0f, 64.0f);
	p->m_pEffect = C2DAnimation :: Create(pTextureManager, &size, 4, 8);
	p->m_pEffect->SetChangeFrame(4);
	return p;
}

/*
 * クラス名：CPanel
 * 関数名：Update()
 * 内容：パネルの更新処理
 */
void CPanel :: Update(void){
	if(m_bMove){
		if(((int)m_pos.x == (int)m_TargetPos.x) && ((int)m_pos.y == (int)m_TargetPos.y)){
			m_bMove = false;
			m_pos = m_TargetPos;
			return;
		}
		
		m_pos += m_Move;
		C2DSprite :: SetPosition(&m_pos);
	}
	
	if(m_bErase){
		if(m_nFrameCount < PANEL_ERASE_START_TIME){
			Vec2 scl(PANEL_EFFECT_SCALE_TABLE[m_nFrameCount], PANEL_EFFECT_SCALE_TABLE[m_nFrameCount]);
			C2DSprite :: SetScaling(&scl);
		} else if(m_nFrameCount == PANEL_ERASE_START_TIME){
			C2DObject :: UnlinkList();
			
			m_pEffect->LinkList(OBJECT_2D_PANEL_EFFECT);
			m_pEffect->Play();
			
		}
		
		if(m_pEffect->IncrementFrame()){	// アニメーション終了で1が返却される
			Vec2 scl(1.0f, 1.0f);
			SetScaling(&scl);
			m_bErase = false;
		}
		
		++m_nFrameCount;
	}
}

/*
 * クラス名：CPanel
 * 関数名：Erase()
 * 内容：パネルを消去する
 * 引数：pPanelEffectTex			;パネル消去に使用するエフェクトテクスチャ
 */
void CPanel :: Erase(CTextureManager *pPanelEffectTex){
	m_bErase = true;
	m_nFrameCount = 0;

	m_pEffect->SetTextureManager(pPanelEffectTex);
	m_pEffect->SetPosition(&m_pos);
	m_pEffect->Seek(0);
}