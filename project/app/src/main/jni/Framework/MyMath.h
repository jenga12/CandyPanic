/*
 * 	File：MyMath.h
 *	Make：FHALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline:算術関数定義
 */

#pragma once
#ifndef _MY_MATH_H_
#define _MY_MATH_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "Vector2D.h"
#include "Vector3D.h"
#include "MyRand.h"


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
class CMath {
	public:
		static float Vec2Dot(const Vec2 *pVec1, const Vec2 *pVec2);					// 2次元ベクトルの内積を計算
		static float Vec3Dot(const Vec3 *pVec1, const Vec3 *pVec2);					// 3次元ベクトルの内積を計算
		static float Vec2Cross(const Vec2 *pVec1, const Vec2 *pVec2);				// 2次元ベクトルの外積を計算
		static void Vec3Cross(Vec3 *pOut, const Vec3 *pVec1, const Vec3 *pVec2);	// 3次元ベクトルの外積を計算
		static float Vec2Length(const Vec2 *pVec);									// 2次元ベクトルの長さを計算
		static float Vec3Length(const Vec3 *pVec);									// 3次元ベクトルの長さを計算
		static void Vec2Normalize(Vec2 *pOut, const Vec2 *pVec);					 // 2次元ベクトルを正規化
		static void Vec3Normalize(Vec3 *pOut, const Vec3 *pVec);					// 3次元ベクトルを正規化
		static unsigned int GetCRC32(const char *pStr);								// 文字列からCRC32ハッシュ値を取得
		static float Bezier(float start, float end, float c1, float c2, float t); // ベジェ曲線計算
		static unsigned long GetRand(void){                                         // 64bit符号なし値取得
			return genrand_int32();
		};
};
/******************************************************************************/

#endif