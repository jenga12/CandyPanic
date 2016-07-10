/*
 *	File：gyro.h
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：ジャイロセンサー判定クラス定義
 */

#pragma once
#ifndef _GYRO_H_
#define _GYRO_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/


/******************************************************************************/
/*                              ライブラリリンク                              */
/******************************************************************************/


/******************************************************************************/
/*                              マクロ＆定数定義                              */
/******************************************************************************/
typedef unsigned char GYRO_ANGLE;
static const GYRO_ANGLE GYRO_HORIZON = 0;	// 水平状態
static const GYRO_ANGLE GYRO_LEFT = 1;		// 左に傾けた状態
static const GYRO_ANGLE GYRO_RIGHT = 2;		// 右に傾けた状態
static const GYRO_ANGLE GYRO_TOP = 3;		// 上に傾けた状態
static const GYRO_ANGLE GYRO_BOTTOM = 4;	// 下に傾けた状態


/******************************************************************************/
/*                                 構造体定義                                 */
/******************************************************************************/


/******************************************************************************/
/*                                 クラス定義                                 */
/******************************************************************************/
class CGyro {
	public:
		static CGyro *Create(void);    // インスタンス生成
		void Release(void);            // インスタンス破棄
		
		void Update(void);             // 更新処理
		GYRO_ANGLE GetGyro(void){       // 端末の向き
			return m_angle;
		}
		
	private:
		CGyro();
		~CGyro(){};
		GYRO_ANGLE m_angle;				// 端末の傾いている方向
		static const float THRESHOLD;	// 判定値
};

/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif