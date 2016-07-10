/*
 *	File：score.h
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：スコア処理クラス定義
 */

#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "Framework/2DNumber.h"


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
class CScore {
	public:
		static CScore *Create(void);	// インスタンス生成
		void Release(void);				// インスタンス破棄
		void Update(void);                 // 更新処理
		void AddScore(unsigned int num){  // スコア加算
			m_nScore += num;
			
			if(m_nScore > 9999999){
				m_nScore = 9999999;
			}
		}
		
	private:
		CScore();					// コンストラクタ
		~CScore(){};				// デストラクタ
	
		C2DNumber *m_pScore;		// スコア
		unsigned int m_nDrawScore;	// 描画スコア
		unsigned int m_nScore;    // 現在のスコア
};

/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif