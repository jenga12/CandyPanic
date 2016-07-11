/*
 *	File：combo.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：コンボ処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "combo.h"
#include "Framework/2DSprite.h"
#include "Framework/2DNumber.h"


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
//					CCombo クラス
//*************************************************
/*
 *	コンストラクタ
 */
CCombo :: CCombo():
m_bUse(false){
	
}

/*
 * クラス名：CCombo
 * 関数名：Create()
 * 内容：インスタンス生成
 */
CCombo *CCombo :: Create(void){
	CCombo *p = new CCombo();
	p->Init();
	return p;
}

/*
 * クラス名：CCombo 
 * 関数名：Init()
 * 内容：初期化処理
 */
void CCombo :: Init(void){
	Vec2 pos(0.0f, 0.0f);
	Vec2 size(36.0f, 90.0f);
	m_pNumber = C2DNumber :: Create("game/number.img", &pos, &size, 32.0f, 2, 2, true, false);
	//m_pNumber->SetNumber(0);
	
	size = Vec2(256.0f, 64.0f);
	m_pCombo = C2DSprite :: Create("game/combo.img", &size, 2);
}

/*
 * クラス名：CCombo
 * 関数名：Release()
 * 内容：インスタンス破棄
 */
void CCombo :: Release(void){
	m_pCombo->Release();
	m_pNumber->Release();
	delete this;
}

/*
 * クラス名：CCombo
 * 関数名：Update()
 * 内容：更新処理
 */
void CCombo :: Update(void){
	if(!m_bUse){
		return;
	}
	
	if(m_nFrameCount == 100){
		m_bUse = false;
		m_pNumber->UnlinkList();
		m_pCombo->UnlinkList();
	}
	
	m_pos.y -= 1.0f;
	m_fAlpha -= 0.01f;
	Vec2 pos(m_pos.x - 161.0f, m_pos.y - 44.0f);
	Color_32 color(1.0f, 1.0f, 1.0f, m_fAlpha);

	m_pNumber->SetPosition(&pos);
	m_pNumber->SetColor(&color);
	m_pCombo->SetPosition(&m_pos);
	m_pCombo->SetColor(&color);
	
	++m_nFrameCount;
}

/*
 * クラス名：CCombo
 * 関数名：Pop()
 * 内容：コンボ数を表示する
 * 引数：pPos			;位置
 *		 combo			;コンボ数
 */
void CCombo :: Pop(const Vec2 *pPos, int combo){
	Vec2 pos(pPos->x - 161.0f, pPos->y - 44.0f);
	Color_32 color(1.0f, 1.0f, 1.0f, 1.0f);
	m_pNumber->SetPosition(&pos);
	m_pNumber->SetColor(&color);
	m_pNumber->SetNumber(combo);
	m_pNumber->LinkList();
	
	m_pos = *pPos;

	m_pCombo->SetPosition(pPos);
	m_pCombo->LinkList(OBJECT_2D_COMBO);
	m_pCombo->SetColor(&color);
	
	m_bUse = true;
	m_fAlpha = 1.0f;
	m_nFrameCount = 0;
}