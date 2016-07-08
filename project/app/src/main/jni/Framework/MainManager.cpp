/*
 *	File：MainManager.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：メイン管理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "MainManager.h"
#include "2DObject.h"
#include "renderer.h""
#include <time.h>
#include "StateManager.h"


/******************************************************************************/
/*                               静的変数初期化                               */
/******************************************************************************/
unsigned short CMainManager :: SCREEN_WIDTH = 1280;
unsigned short CMainManager :: SCREEN_HEIGHT = 720;
AAssetManager *CMainManager :: m_AssetManager = NULL;
INPUT CMainManager :: m_aInput[1];
Vec3 CMainManager :: m_sensor;
CRenderer *CMainManager :: m_pRenderer = NULL;
CStateManager *CMainManager :: m_pStateManager = NULL;


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
//				  CMainManager クラス
//*************************************************
/*
 *  コンストラクタ
 */
CMainManager :: CMainManager(){

}

/*
 * クラス名：CMainManager
 * 関数名：Create()TITLE
 * 内容：インスタンス生成
 * 引数：ScreenWidth           ;スクリーン幅
 *       ScreenHeight          ;スクリーン高さ
 *       env                   ;JNI環境
 *       AssetObject           ;アセット
 */
CMainManager *CMainManager :: Create(unsigned short ScreenWidth, unsigned short ScreenHeight, JNIEnv *env, jobject AssetObject){
	CMainManager :: SCREEN_WIDTH = ScreenWidth;
	CMainManager :: SCREEN_HEIGHT = ScreenHeight;
	CMainManager *p = new CMainManager();

	p->m_AssetManager = AAssetManager_fromJava(env, AssetObject);
	p->m_pRenderer = CRenderer::Create();
	p->m_pStateManager = CStateManager :: Create(STATE_TITLE);

	return p;
}

/*
 * クラス名：CMainManager
 * 関数名：Release()
 * 内容：インスタンス破棄
 */
void CMainManager :: Release(void){
	m_pStateManager->Release();
	m_pRenderer->Release();
	delete this;
}

/*
 * クラス名：CMainManager
 * 関数名：Update()
 * 内容：更新処理
 * 引数：position          ;タッチ座標
 *       sensor            ;端末の傾き
 */
int CMainManager :: Update(int *position, float *sensor){
	/*** 入力値のコピー ***/
	m_aInput[0].pos.x = position[0];
	m_aInput[0].pos.y = position[1];
	m_aInput[0].flag = position[2];
	m_sensor.x = sensor[0];
	m_sensor.y = sensor[1];
	m_sensor.z = sensor[2];

	//******************** 更新処理エリア *************************
	m_pStateManager->Update();

	//**************************************************************

	/*** 全てのオブジェクトの削除フラグをチェックする ***/
	C2DObject::ReleaseCheckAll();

	return 0;
}

/*
 * クラス名：CMainManager
 * 関数名：Draw()
 * 内容：描画処理
 */
void CMainManager :: Draw(void){
	m_pRenderer->Draw();
}