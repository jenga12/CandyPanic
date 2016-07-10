/*
 *	File：timer.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：タイマー処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "timer.h"
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
//					CTimer クラス
//*************************************************
/*
 *	コンストラクタ
 */
CTimer :: CTimer():
m_nFrameCount(0){
	
}

/*
 * クラス名：CTimer
 * 関数名：Create()
 * 内容：インスタンス生成
 */
CTimer *CTimer :: Create(void){
	CTimer *p = new CTimer();
	
	Vec2 pos(1089.0f, 638.0f);
	Vec2 size(30.0f, 75.0f);
	p->m_pMinite = C2DNumber :: Create("game/number.img", &pos, &size, 30.0f, 4, 1, true, true);
	p->m_pMinite->SetNumber(0);

	pos = Vec2(1146.0f, 638.0f);
	p->m_pSecond = C2DNumber :: Create("game/number.img", &pos, &size, 26.0f, 5, 2, true, true);
	p->m_pSecond->SetNumber(0);
	
	return p;
}

/*
 * クラス名：CTimer
 * 関数名：Release()
 * 内容：インスタンス破棄
 */
void CTimer :: Release(void){
	m_pMinite->Release();
	m_pSecond->Release();
	delete this;
}

/*
 * クラス名：CTimer
 * 関数名：Update()
 * 内容：更新処理
 */
void CTimer :: Update(void){
	++m_nFrameCount;
	
	if(!(m_nFrameCount % 60)){
		int minite = m_nFrameCount / 3600;
		int second = (m_nFrameCount / 60) % 60;
		
		if(minite > 9){
			minite = 9;
			second = 59;
		}
		
		m_pMinite->SetNumber(minite);
		m_pSecond->SetNumber(second);
	}
}