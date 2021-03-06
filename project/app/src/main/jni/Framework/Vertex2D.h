/*
 *	File：
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：
 */

#pragma once
#ifndef _VERTEX_2D_H_
#define _VERTEX_2D_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "Vector2D.h"
#include "color.h"


/******************************************************************************/
/*                              ライブラリリンク                              */
/******************************************************************************/


/******************************************************************************/
/*                              マクロ＆定数定義                              */
/******************************************************************************/


/******************************************************************************/
/*                                 構造体定義                                 */
/******************************************************************************/

/*** 2D頂点情報 ***/
struct VERTEX_2D {
	Vec2 pos;		// 頂点座標
	Color_32 clr;	// 頂点カラー
	Vec2 tex;		// テクスチャ座標
};

struct MODEL_2D{
	Vec2 *pPos;				// 頂点座標
	Color_32 *pClr;			// 頂点カラー
	Vec2 *pTex;				// テクスチャ座標
	unsigned int nVtxNum;	// 頂点数
};

/*** 2Dワールド変換用情報 ***/
struct TRANSFORM_2D {
	Vec2 pos;		// 平行移動
	float rot;		// 回転
	Vec2 scl;		// 拡大縮小
};


/******************************************************************************/
/*                                 クラス定義                                 */
/******************************************************************************/


/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif