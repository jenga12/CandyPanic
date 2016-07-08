/*
 *	File：matrix.h
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：行列演算ライブラリ
 */

#pragma once
#ifndef _MATRIX_H_
#define _MATRIX_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include <math.h>


/******************************************************************************/
/*                              ライブラリリンク                              */
/******************************************************************************/


/******************************************************************************/
/*                              マクロ＆定数定義                              */
/******************************************************************************/


/******************************************************************************/
/*                                 構造体定義                                 */
/******************************************************************************/
struct MTX {
	public:
		MTX(){};								// コンストラクタ

		/*** 乗算 ***/
		MTX operator * (const MTX& a) const{
			MTX ans;
			int i, j, k;
			for(i = 0; i < 16; ++i){
				ans.array1[i] = 0.0f;
			}

			for(i = 0; i < 4; ++i){
				for(j = 0; j < 4; ++j){
					for(k = 0; k < 4; ++k){
						ans.array2[i][j] += this->array2[i][k] * a.array2[k][j];
					}
				}
			}

			return ans;
		};

		/*** 乗算代入 ***/
		MTX& operator *= (const MTX& a){
			MTX ans;
			int i, j, k;
			for(i = 0; i < 16; ++i){
				ans.array1[i] = 0.0f;
			}

			for(i = 0; i < 4; ++i){
				for(j = 0; j < 4; ++j){
					for(k = 0; k < 4; ++k){
						ans.array2[i][j] += this->array2[i][k] * a.array2[k][j];
					}
				}
			}

			*this = ans;
			return *this;
		};

		/*** 単位行列化 ***/
		void Identity(void){
			array1[ 0] = 1.0f; array1[ 1] = 0.0f; array1[ 2] = 0.0f; array1[ 3] = 0.0f;
			array1[ 4] = 0.0f; array1[ 5] = 1.0f; array1[ 6] = 0.0f; array1[ 7] = 0.0f;
			array1[ 8] = 0.0f; array1[ 9] = 0.0f; array1[10] = 1.0f; array1[11] = 0.0f;
			array1[12] = 0.0f; array1[13] = 0.0f; array1[14] = 0.0f; array1[15] = 1.0f;
		}

		/*** 平行移動行列化 ***/
		void Translation(float x, float y, float z){
			array1[ 0] = 1.0f; array1[ 1] = 0.0f; array1[ 2] = 0.0f; array1[ 3] = 0.0f;
			array1[ 4] = 0.0f; array1[ 5] = 1.0f; array1[ 6] = 0.0f; array1[ 7] = 0.0f;
			array1[ 8] = 0.0f; array1[ 9] = 0.0f; array1[10] = 1.0f; array1[11] = 0.0f;
			array1[12] =    x; array1[13] =    y; array1[14] =    z; array1[15] = 1.0f;
		}

		/*** 拡大縮小行列化 ***/
		void Scaling(float x, float y, float z){
			array1[ 0] = x;    array1[ 1] = 0.0f; array1[ 2] = 0.0f; array1[ 3] = 0.0f;
			array1[ 4] = 0.0f; array1[ 5] = y;    array1[ 6] = 0.0f; array1[ 7] = 0.0f;
			array1[ 8] = 0.0f; array1[ 9] = 0.0f; array1[10] = z;    array1[11] = 0.0f;
			array1[12] = 0.0f; array1[13] = 0.0f; array1[14] = 0.0f; array1[15] = 1.0f;
		}

		/*** X軸回転行列 ***/
		void RotationX(float rad){
			array1[ 0] = 1.0f;		array1[ 1] = 0.0f;		array1[ 2] = 0.0f;		array1[ 3] = 0.0f;
			array1[ 4] = 0.0f;		array1[ 5] = cosf(rad);	array1[ 6] = -sinf(rad);array1[ 7] = 0.0f;
			array1[ 8] = 0.0f;		array1[ 9] = sinf(rad);	array1[10] = cosf(rad);	array1[11] = 0.0f;
			array1[12] = 0.0f;		array1[13] = 0.0f;		array1[14] = 0.0f;		array1[15] = 1.0f;
		}

		/*** Y軸回転行列 ***/
		void RotationY(float rad){
			array1[ 0] = cosf(rad);	array1[ 1] = 0.0f;		array1[ 2] = sinf(rad);	array1[ 3] = 0.0f;
			array1[ 4] = 0.0f;		array1[ 5] = 1.0f;		array1[ 6] = 0.0f;		array1[ 7] = 0.0f;
			array1[ 8] = -sinf(rad);array1[ 9] = 0.0f;		array1[10] = cosf(rad); array1[11] = 0.0f;
			array1[12] = 0.0f;		array1[13] = 0.0f;		array1[14] = 0.0f;		array1[15] = 1.0f;
		}

		/*** Z軸回転行列 ***/
		void RotationZ(float rad){
			array1[ 0] = cosf(rad);	array1[ 1] = -sinf(rad);array1[ 2] = 0.0f;		array1[ 3] = 0.0f;
			array1[ 4] = sinf(rad);	array1[ 5] = cosf(rad);	array1[ 6] = 0.0f;		array1[ 7] = 0.0f;
			array1[ 8] = 0.0f;		array1[ 9] = 0.0f;		array1[10] = 1.0f;		array1[11] = 0.0f;
			array1[12] = 0.0f;		array1[13] = 0.0f;		array1[14] = 0.0f;		array1[15] = 1.0f;
		}

		/*** 回転行列化 ***/
		void Rotation3D(float x, float y, float z){
			MTX rotX, rotY, rotZ;
			rotX.RotationX(x);
			rotY.RotationY(y);
			rotZ.RotationZ(z);
			*this = rotX * rotY * rotZ;
		}

		void Vec3Transform(Vec3 *pOut, const Vec3 *pVec){
			MTX vtxMtx;
			vtxMtx.Identity();
			vtxMtx.array2[0][0] = pVec->x;
			vtxMtx.array2[0][1] = pVec->y;
			vtxMtx.array2[0][2] = pVec->z;
			vtxMtx.array2[0][3] = 1.0f;

			vtxMtx *= *this;
			pOut->x = vtxMtx.array2[0][0];
			pOut->y = vtxMtx.array2[0][1];
			pOut->z = vtxMtx.array2[0][2];
		}

		union{
			float array2[4][4];		// 2次元配列
			float array1[16];		// 1次元配列
		};
};

/******************************************************************************/
/*                                 クラス定義                                 */
/******************************************************************************/


/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif