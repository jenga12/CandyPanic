/*
 *	File：2DAnimation.h
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：2Dアニメーション処理クラス定義
 */

#pragma once
#ifndef _2D_ANIMATION_H_
#define _2D_ANIMATION_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "2DSprite.h"


/******************************************************************************/
/*                              ライブラリリンク                              */
/******************************************************************************/


/******************************************************************************/
/*                              マクロ＆定数定義                              */
/******************************************************************************/


/******************************************************************************/
/*                                 構造体定義                                 */
/******************************************************************************/


/******************************************************************************/
/*                                 クラス定義                                 */
/******************************************************************************/
class C2DAnimation : public C2DSprite{
	public:
		/*** インスタンス生成 ***/
		static C2DAnimation *Create(const char *pTexFileName, const Vec2 *pSize, unsigned int nPriority, unsigned int nAnimationNum);
		static C2DAnimation *Create(CTextureManager *pTextureManager, const Vec2 *pSize, unsigned int nPriority, unsigned int nAnimationNum);
		
		void SetChangeFrame(int nFrame){	// イメージ１枚が切り替わるまでのフレーム数指定
			m_nChangeFrame = nFrame;
		}
		
		int IncrementFrame(void);			// 次のフレームへ
		
		void SetLoop(bool bLoop){			// ループフラグの設定{
			m_bLoop = bLoop;
		}
	
		void Seek(unsigned int nFrame){		// 指定フレームへシークする
			m_nFrameCount = nFrame;
		}

		void Stop(void){
			m_bPlaying = false;
		}

		void Play(void){
			m_bPlaying = true;
		}
		
	protected:
		C2DAnimation(unsigned int nPriority, unsigned int nAnimationNum);		// コンストラクタ
		~C2DAnimation(){};					// デストラクタ

		void Init(const char *pTexFileName, const Vec2 *pSize);
		void Init(CTextureManager *pTextureManager, const Vec2 *pSize);
		
	private:
		unsigned int m_nAnimationNum;		// アニメーション枚数
		unsigned int m_nAnimationNo;		// 現在の画像番号
		unsigned int m_nChangeFrame;		// イメージ１枚が切り替わるまでのフレーム数
		unsigned int m_nFrameCount;			// フレームカウンタ
		bool m_bLoop;						// ループフラグ
		bool m_bPlaying;					// アニメーションフラグ
		Vec2 m_SingleSize;					// アニメーション１枚のサイズ
};


/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif