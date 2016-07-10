/*
 *	File：2DAnimation.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：2Dアニメーションクラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
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
//				  C2DAnimation クラス
//*************************************************
/*
 *	コンストラクタ
 */
C2DAnimation :: C2DAnimation(unsigned int nPriority, unsigned int nAnimationNum):
m_nAnimationNum(nAnimationNum),
C2DSprite(nPriority),
m_nAnimationNo(0),
m_nChangeFrame(8),
m_nFrameCount(0),
m_bLoop(false),
m_bPlaying(true){
	
}

/*
 * クラス名：C2DAnimation
 * 関数名：Create()
 * 内容：インスタンス生成
 * 引数：pTexFileName			;使用テクスチャファイル名
 *		 pSize					;ポリゴンサイズ
 *		 nPriority				;描画優先度
 *		 nAnimationNum			;アニメーションの枚数
 */
C2DAnimation *C2DAnimation :: Create(const char *pTexFileName, const Vec2 *pSize, unsigned int nPriority, unsigned int nAnimationNum){
	C2DAnimation *p = new C2DAnimation(nPriority, nAnimationNum);
	p->Init(pTexFileName, pSize);
	return p;
}

/*
 * クラス名：C2DAnimation
 * 関数名：Create()
 * 内容：インスタンス生成
 * 引数：pTextureManager		;使用テクスチャのマネージャ
 *		 pSize					;ポリゴンサイズ
 *		 nPriority				;描画優先度
 *		 nAnimationNum			;アニメーションの枚数
 */
C2DAnimation *C2DAnimation :: Create(CTextureManager *pTextureManager, const Vec2 *pSize, unsigned int nPriority, unsigned int nAnimationNum){
	C2DAnimation *p = new C2DAnimation(nPriority, nAnimationNum);
	p->Init(pTextureManager, pSize);
	return p;
}

/*
 * クラス名：C2DAnimation
 * 関数名：Init()
 * 引数：pTextureManager        ;使用テクスチャのマネージャ
 *       pSize                  ;ポリゴンサイズ
 */
void C2DAnimation :: Init(CTextureManager *pTextureManager, const Vec2 *pSize){
	C2DSprite :: Init(pTextureManager, pSize);
	m_SingleSize = Vec2(0.125f, 1.0f / (float)(((m_nAnimationNum - 1) >> 3) + 1));
	Vec2 uv(0.0f, 0.0f);
	SetTexCoord(&uv, &m_SingleSize);
}

/*
 * クラス名：C2DAnimation
 * 関数名：Init()
 * 内容：初期化処理
 * 引数：pTexFileName      ;使用テクスチャファイル名
 *       pSize                 ;ポリゴンサイズ
 */
void C2DAnimation :: Init(const char *pTexFileName, const Vec2 *pSize){
	C2DSprite :: Init(pTexFileName, pSize);
	m_SingleSize = Vec2(0.125f, 1.0f / (float)(((m_nAnimationNum - 1) >> 3) + 1));
	Vec2 uv(0.0f, 0.0f);
	SetTexCoord(&uv, &m_SingleSize);
}

/*
 * クラス名：C2DAnimation
 * 関数名：IncrementFrame()
 * 内容：次のフレームへ移動する
 * 返却値：アニメーション終了で1, それ以外は0
 */
int C2DAnimation :: IncrementFrame(void){
	if(m_bPlaying == false){
		return 0;
	}
	
	++m_nFrameCount;
	
	if(!(m_nFrameCount %= m_nChangeFrame)){
		if(!(m_nAnimationNo = (m_nAnimationNo + 1) % m_nAnimationNum) && (m_bLoop == false)){
			m_bPlaying = false;
			C2DObject :: UnlinkList();
			return 1;
		}

		Vec2 uv;
		uv.x = (float)(m_nAnimationNo & 0x00000007) * 0.125f;
		uv.y = (float)(m_nAnimationNo >> 3) * m_SingleSize.y;

		SetTexCoord(&uv, &m_SingleSize);
	}

	return 0;
}