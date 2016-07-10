/*
 *	File：gyro.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：ジャイロセンサー判定処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "gyro.h"
#include "Framework/MainManager.h"
#include <math.h>


/******************************************************************************/
/*                               静的変数初期化                               */
/******************************************************************************/
const float CGyro :: THRESHOLD = 1.0f;

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
//					CGyro クラス
//*************************************************
/*
 *	コンストラクタ
 */
CGyro :: CGyro():
		m_angle(GYRO_HORIZON) {
	
}

/*
 * クラス名：CGyro
 * 関数名：Create()
 * 内容：インスタンス生成
 */
CGyro *CGyro :: Create(void){
	CGyro *p = new CGyro();
	
	return p;
}

/*
 * クラス名：CGyro
 * 関数名：Release()
 * 内容：インスタンス破棄
 */
void CGyro :: Release(void){
	delete this;
}

/*
 * クラス名：CGyro
 * 関数名：Update()
 * 内容：更新処理
 */
void CGyro :: Update(void){
	const Vec3 *pSensor = CMainManager :: GetSensor();
	
	m_angle = GYRO_HORIZON;
	
	/*** 上に傾けた ***/
	if(pSensor->x > THRESHOLD){
		m_angle = GYRO_TOP;
	
	/*** 下に傾けた ***/
	} else if(pSensor->x < -THRESHOLD){
		m_angle = GYRO_BOTTOM;
	}
	
	/*** 左に傾けた ***/
	if(pSensor->z < -THRESHOLD){
		/*** より傾きが大きい方を適用する ***/
		if(m_angle != GYRO_HORIZON){
			if(fabs(pSensor->z) > fabs(pSensor->x)){
				m_angle = GYRO_LEFT;
			}
		} else {
			m_angle = GYRO_LEFT;
		}
		
	/*** 右に傾けた ***/
	} else if(pSensor->z > THRESHOLD){
		if(m_angle != GYRO_HORIZON){
			/*** より傾きが大きい方を適用する ***/
			if(fabs(pSensor->z) > fabs(pSensor->x)){
				m_angle = GYRO_RIGHT;
			}
		} else {
			m_angle = GYRO_RIGHT;
		}
	}
}