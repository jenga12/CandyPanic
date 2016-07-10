/*
 *	File：Vector4D.h
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：4次元ベクトルライブラリ
 */

#pragma once
#ifndef _VECTOR_4D_H_
#define _VECTOR_4D_H_

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
struct Vec4{
	public:
		Vec4(){x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f;};
		Vec4(float x2, float y2, float z2, float w2){
			x = x2; y = y2; z = z2; w = w2;
		}

		Vec4 operator + (const Vec4& v) const{
			return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
		}

		Vec4 operator - (const Vec4& v) const{
			return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
		}

		Vec4 operator * (float s) const{
			return Vec4(x * s, y * s, z * s, w * s);
		}

		Vec4 operator / (float s) const{
			float fInv = 1.0f / s;
			return Vec4(x * fInv, y * fInv, z * fInv, w * fInv);
		}

		Vec4& operator += (const Vec4& v){
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
			return *this;
		}

		Vec4& operator -= (const Vec4& v){
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
			return *this;
		}

		Vec4& operator *= (float s){
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return *this;
		}

		Vec4& operator /= (float s){
			float fInv = 1.0f / s;
			x *= fInv;
			y *= fInv;
			z *= fInv;
			w *= fInv;
			return *this;
		}

		Vec4 operator - () const{
			return Vec4(-x, -y, -z, -w);
		}

		float x, y, z, w;
};


/******************************************************************************/
/*                                 クラス定義                                 */
/******************************************************************************/


/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif