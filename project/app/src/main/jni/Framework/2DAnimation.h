/*
 *	File：2DAnimation.h
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：2Dアニメーション処理クラス定義
 */

#pragma once
#ifndef _2D_ANIMATION_H_
#define _2D_ANIMATION_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "2DObject.h"
#include "2DSprite.h"


/******************************************************************************/
/*                              ライブラリリンク                              */
/******************************************************************************/
#pragma comment(lib, "shlwapi.lib")

/******************************************************************************/
/*                              マクロ＆定数定義                              */
/******************************************************************************/


/******************************************************************************/
/*                                 構造体定義                                 */
/******************************************************************************/


/******************************************************************************/
/*                                 クラス定義                                 */
/******************************************************************************/
class C2DAnimation{
	public:
		/*** インスタンス生成 ***/
		static C2DAnimation *Create(const char *pTopTexFileName, const Vec2 *pSize, _2D_OBJECT objType, unsigned int nPriority);
		void Release(void);				// インスタンス破棄

		void SetChangeFrame(int nFrame){	// イメージ１枚が切り替わるまでのフレーム数指定
			m_nChangeFrame = nFrame;
		}

		void Seek(int nFrame){            // アニメーションをシーク
			m_nFrameCount = nFrame;
		}

		void Play(bool bReset = true){
			if(bReset){
				m_nFrameCount = 0;
			}
			m_bPlaying = true;
		}

		void Stop(void){
			m_bPlaying = false;
		}

		void IncrementFrame(void);			// 次フレームへ

		void SetLoop(bool bLoop){			// ループフラグ指定
			m_bLoop = bLoop;
		}

		void SetPosition(const Vec2 *pPos){
			for(unsigned int i = 0; i < m_nAnimationNum; ++i){
				m_ppAnimImage[i]->SetPosition(pPos);
			}
		}

		void SetRotation(float fRot){
			for(unsigned int i = 0; i < m_nAnimationNum; ++i){
				m_ppAnimImage[i]->SetRotation(fRot);
			}
		}

		void SetScaling(const Vec2 *pScl){
			for(unsigned int i = 0; i < m_nAnimationNum; ++i){
				m_ppAnimImage[i]->SetScaling(pScl);
			}
		}

		void SetColor(const Color_32 *pClr){
			for(unsigned int i = 0; i < m_nAnimationNum; ++i){
				m_ppAnimImage[i]->SetColor(pClr);
			}
		}

	protected:
		C2DAnimation(_2D_OBJECT objType);	// コンストラクタ
		~C2DAnimation(){};					// デストラクタ
		int Init(	const char *pTopTexFileName, const Vec2 *pSize, unsigned int nPriority);// 初期化処理

	private:
		int CountImage(const char *pTopTexFileName);	// アニメーション枚数をカウント
		unsigned int m_nAnimationNum;		// アニメーション枚数
		unsigned int m_nAnimationNo;		// 現在の画像番号
		unsigned int m_nChangeFrame;		// イメージ１枚が切り替わるまでのフレーム数
		unsigned int m_nFrameCount;		// フレームカウント
		C2DSprite **m_ppAnimImage;			// アニメーション連番画像
		bool m_bLoop;						// ループフラグ
		bool m_bPlaying;					// 再生フラグ
		_2D_OBJECT m_objType;				// オブジェクト種別
};


/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif