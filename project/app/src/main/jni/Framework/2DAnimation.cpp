/*
 *	File：2DAnimation.cpp
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：2Dアニメーション処理
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include <math.h>
#include <stdio.h>
#include "MainManager.h"
#include <stdlib.h>
#include "2DAnimation.h"


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
//				 C2DAnimation クラス
//*************************************************
/*
 *	コンストラクタ
 */
C2DAnimation :: C2DAnimation(_2D_OBJECT objType):
		m_bLoop(false),
		m_nFrameCount(0),
		m_nChangeFrame(8),
		m_nAnimationNo(0),
		m_bPlaying(false),
		m_objType(objType){

}

/*
 * クラス名：C2DAnimation
 * 関数名：Create()
 * 内容：インスタンス生成
 * 引数：pTopTexFileName			;アニメーション連番画像の先頭の画像ファイル名
 *		 pSize						;描画サイズ
 *		 objType					;オブジェクト種別
 *		 nPriority					;描画優先度
 */
C2DAnimation *C2DAnimation :: Create(const char *pTopTexFileName, const Vec2 *pSize, _2D_OBJECT objType, unsigned int nPriority){
	C2DAnimation *p = new C2DAnimation(objType);
	p->Init(pTopTexFileName, pSize, nPriority);
	return p;
}

/*
 * クラス名：C2DAnimation
 * 関数名：Init()
 * 内容：初期化処理
 * 引数：pTopTexFileName			;アニメーション連番画像の先頭の画像ファイル名
 *		 pSize						;描画サイズ
 *		 nPriority					;描画優先度
 */
int C2DAnimation :: Init(const char *pTopTexFileName, const Vec2 *pSize, unsigned int nPriority){
	/*** 連番部分と拡張子部分を取り除いたファイル名を作成 ***/
	char filename[256];
	unsigned int i;
	for(i = 0; (i < 256) && (pTopTexFileName[i] != '.') && (pTopTexFileName[i] != '\0'); ++i){
		filename[i] = pTopTexFileName[i];
	}
	--i;
	while((0x30 <= filename[i]) && (filename[i] <= 0x39)){
		--i;
	}
	filename[i + 1] = '\0';

	m_nAnimationNum = CountImage(filename);

	m_ppAnimImage = new C2DSprite*[m_nAnimationNum];

	char path[256];
	for(i = 0; i < m_nAnimationNum; ++i){
		sprintf(path, "%s%05d%s", filename, i, ".img");
		m_ppAnimImage[i] = C2DSprite :: Create(path, pSize, nPriority);
	}

	return 0;
}

/*
 * クラス名：C2DAnimation
 * 関数名：Release()
 * 内容：インスタンス破棄
 */
void C2DAnimation :: Release(void){
	for(unsigned int i = 0; i < m_nAnimationNum; ++i){
		(m_ppAnimImage[i])->Destroy();
	}

	delete[] m_ppAnimImage;
	delete this;
}

/*
 * クラス名：C2DAnimation
 * 関数名：CountImage()
 * 内容：アニメーション枚数をカウントする
 * 引数：pTopTexFileName			;アニメーション連番画像の先頭の画像ファイル名
 * 返却値：アニメーションの枚数
 */
int C2DAnimation :: CountImage(const char *pTopTexFileName){
	int nLoop = (int)pow(10.0f, 5);
	char path[256];
	int i;

	AAssetManager *pAsset = CMainManager :: GetAssetManager();

	for(i = 0; i < nLoop; ++i){
		sprintf(path, "%s%05d%s", pTopTexFileName, i, ".img");
		AAsset *fp= AAssetManager_open(pAsset, path, AASSET_MODE_UNKNOWN);

		if(fp == NULL){
			break;
		}

		AAsset_close(fp);
	}

	return i;
}

/*
 * クラス名：C2DAnimation
 * 関数名：IncrementFrame()
 * 内容：次フレームへ
 */
void C2DAnimation :: IncrementFrame(void){
	if(m_bPlaying) {
		++m_nFrameCount;

		if (!(m_nFrameCount %= m_nChangeFrame)) {

			m_ppAnimImage[m_nAnimationNo]->UnlinkList();

			if ((!(m_nAnimationNo = (m_nAnimationNo + 1) % m_nAnimationNum)) &&
				(m_bLoop == false)) {
				//Release();
				m_bPlaying = false;
				return;
			}

			m_ppAnimImage[m_nAnimationNo]->LinkList(m_objType);
		}
	}
}
