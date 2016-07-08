/*
 *	File：renderer.cpp
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：レンダリング処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "define.h"
#include "MainManager.h"
#include "renderer.h"
#include "2DObject.h"


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
//					CRenderer クラス
//*************************************************
/*
 *	コンストラクタ
 */
CRenderer :: CRenderer(){
}

/*
 * クラス名：CRenderer
 * 関数名：Create()
 * 内容：インスタンス生成
 */
CRenderer *CRenderer :: Create(void){
	CRenderer *p = new CRenderer();
	return p;
}

/*
 * クラス名：CRenderer
 * 関数名：Release()
 * 内容：インスタンス破棄
 */
void CRenderer :: Release(void){
	delete this;
}

/*
 * クラス名：CRenderer
 * 関数名：Draw()
 * 内容：描画処理
 */
void CRenderer :: Draw(void){
	InitFrame();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*** 2D描画 ***/
	Setup2D();
	C2DObject :: DrawAll();
	End2D();
}

/*
 * クラス名：CRenderer
 * 関数名：InitFrame()
 * 内容：フレーム描画の初期化
 */
void CRenderer :: InitFrame(void){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/*** テクスチャを有効にする ***/
	glEnable(GL_TEXTURE_2D);

	/*** 深度バッファを有効にする ***/
	//glEnable(GL_DEPTH_TEST);

	/*** αブレンドを有効にする ***/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*** 頂点配列の各属性を有効にする ***/
	glEnableClientState(GL_VERTEX_ARRAY);           // 頂点座標
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);   // テクスチャ座標
	glEnableClientState(GL_COLOR_ARRAY);            // 頂点カラー
}

/*
 * クラス名：CRenderer
 * 関数名：Setup2D()
 * 内容：2Dオブジェクト描画準備
 */
void CRenderer :: Setup2D(void){
	glViewport(0, 0, CMainManager::GetScreenWidth(), CMainManager::GetScreenHeight());

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrthof(0.0f, APP_WIDTH, APP_HEIGHT, 0.0f, 0.0f, 1.0f);

	/*** ビュー行列スタックを操作対象に ***/
	glMatrixMode(GL_MODELVIEW);

	/*** ビュー行列に単位行列を設定 ***/
	glPushMatrix();
	glLoadIdentity();
}

/*
 * クラス名：CRenderer
 * 関数名：End2D()
 * 内容：2Dオブジェクト描画終了
 */
void CRenderer :: End2D(void){
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}