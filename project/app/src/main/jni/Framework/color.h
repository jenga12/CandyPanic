/*
 *	File：color.h
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：色情報構造体
 */

#pragma once
#ifndef _COLOR_H_
#define _COLOR_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/


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
struct Color_32;
struct Color_8{
	public:
		/*** コンストラクタ ***/
		Color_8(){r = 255; g = 255; b = 255; a = 255;};
		Color_8(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha){
			r = red; g = green; b = blue; a = alpha;
		};

		/*** 32bit色情報からの代入 ***/
		Color_8& operator = (const Color_32& color32);

		unsigned char r, g, b, a;		// 色情報
};

struct Color_32{
	public:
		/*** コンストラクタ ***/
		Color_32(){r = 1.0f; g = 1.0f; b = 1.0f; a = 1.0f;};
		Color_32(float red, float green, float blue, float alpha){
			r = red; g = green; b = blue; a = alpha;
		};

		/*** 8bit色情報からの代入 ***/
		Color_32& operator = (const Color_8& color8);

		float r, g, b, a;
};


/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif