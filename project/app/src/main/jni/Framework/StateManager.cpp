/*
 *	File：StateManager.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：ステート管理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "StateManager.h"
#include "../title.h"
#include "../game.h"
#include "2DFade.h"


/******************************************************************************/
/*                               静的変数初期化                               */
/******************************************************************************/
C2DFade *CStateManager :: m_pFade = NULL;
CState *CStateManager :: m_pCurrentState = NULL;
CState *CStateManager :: m_pNextState = NULL;


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
//				CStateManager クラス
//*************************************************
/*
 *	コンストラクタ
 */
CStateManager :: CStateManager(){

}

/*
 * クラス名：CStateManager
 * 関数名：Create()
 * 内容：インスタンス生成
 * 引数：DefaultState			;初期ステート
 */
CStateManager *CStateManager :: Create(STATE_NAME DefaultState){
	CStateManager *p = new CStateManager();
	p->m_pCurrentState = p->CreateState(DefaultState);
	p->m_pNextState = p->m_pCurrentState;
	p->m_pFade = C2DFade :: Create();
	return p;
}

/*
 * クラス名：CStateManager
 * 関数名：Release()
 * 内容：インスタンス破棄
 */
void CStateManager :: Release(void){
	m_pFade->Release();

	if(m_pCurrentState == m_pNextState){
		m_pCurrentState->Final();
		delete m_pCurrentState;
	} else {
		m_pCurrentState->Final();
		delete m_pCurrentState;
		m_pNextState->Final();
		delete m_pNextState;
	}

	delete this;
}

/*
 * クラス名：CStateManager
 * 関数名：Update()
 * 内容：更新処理
 */
void CStateManager :: Update(void){
	if(m_pCurrentState != m_pNextState){
		if(!(m_pFade->IsExecFade())){
			m_pCurrentState->Final();
			delete m_pCurrentState;
			m_pCurrentState = m_pNextState;
			m_pCurrentState->Init();
			m_pFade->Start(FADE_IN, STATE_CHANGE_FADE_FRAME);
		}
	}

	m_pCurrentState->Update();
	m_pFade->Update();
}

/*
 * クラス名：CStateManager
 * 関数名：CreateState()
 * 内容：ステートの生成
 * 引数：state			;生成するステート名
 */
CState *CStateManager :: CreateState(STATE_NAME state){
	CState *p;

	switch(state){
		case STATE_TITLE:
			p = new CTitle();
			break;

		case STATE_GAME:
			p = new CGame();
			break;
	}

	p->Init();
	return p;
}