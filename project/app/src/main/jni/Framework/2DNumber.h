/*
 *	File：2DNumber.h
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：数字描画クラス定義
 */

#pragma once
#ifndef _2D_NUMBER_H_
#define _2D_NUMBER_H_

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
class C2DSingleNumber : public C2DSprite {
	public:
		/*** インスタンス生成 ***/
		static C2DSingleNumber *Create(	const char *pTexFileName, const Vec2 *pPos,
		                                   const Vec2 *pSize, unsigned int nPriority);

		/*** 描画数字を設定 ***/
		void SetNumber(int num){
			if(num < 0){
				Color_32 color(1.0f, 1.0f, 1.0f, 1.0f);
				C2DSprite :: SetColor(&color);
			} else {
				Color_32 color(1.0f, 1.0f, 1.0f, 1.0f);
				Vec2 v1((float)num / 10.0f, 0.0f);
				Vec2 v2(0.1f, 1.0f);
				C2DSprite :: SetColor(&color);
				C2DSprite :: SetTexCoord(&v1, &v2);
			}
		}

	protected:
		C2DSingleNumber(unsigned int nPriority);
		~C2DSingleNumber(){};



};

class C2DNumber {
	public:
		/*** インスタンス生成 ***/
		static C2DNumber *Create(	const char *pTexFileName, const Vec2 *pPos,
		                             const Vec2 *pDigitSize, unsigned int nPriority,
		                             int nDigit, bool bRight, bool bZero);
		void Release(void);					// インスタンス破棄
		void SetNumber(unsigned int num);		// 描画数字を設定する

	protected:
		C2DNumber(bool bZero, bool bRight, int nDigit);	// コンストラクタ
		~C2DNumber(){};										// デストラクタ

	private:
		/*** 初期化処理 ***/
		int Init(const char *pTexFileName, const Vec2 *pPos, const Vec2 *pDigitSize, unsigned int nPriority);

		int NumberToArray(unsigned int num);	// 設定された数字を配列に１桁ずつ格納

		char *m_pNumber;						// 数字を１桁ずつ取り出した配列
		int m_nDigit;							// 描画桁数
		unsigned int m_nNumber;				// 描画する数字
		C2DSingleNumber **m_ppSingleNumber;		// １桁描画クラスワーク
		bool m_bZero;							// ０詰めフラグ
		bool m_bRight;							// 右詰めフラグ
};

/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif