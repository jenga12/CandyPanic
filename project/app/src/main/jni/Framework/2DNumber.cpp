/*
 *	File：2DNumber.cpp
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：数字描画クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "2DNumber.h"
#include <math.h>


/******************************************************************************/
/*                               静的変数初期化                               */
/******************************************************************************/


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
//			   C2DSingleNumber クラス
//*************************************************
/*
 *	コンストラクタ
 */
C2DSingleNumber :: C2DSingleNumber(unsigned int nPriority) :
		C2DSprite(nPriority){

}

/*
 * クラス名：C2DSingleNumber
 * 関数名：Create()
 * 内容：インスタンス生成
 * 引数：pTexFileName			;使用テクスチャファイル名
 *		 pPos					;描画位置
 * 		 pSize					;描画サイズ
 *		 nPriority				;描画優先度
 */
C2DSingleNumber *C2DSingleNumber :: Create(const char *pTexFileName, const Vec2 *pPos, const Vec2 *pSize, unsigned int nPriority){
	C2DSingleNumber *p = new C2DSingleNumber(nPriority);

	p->Init(pTexFileName, pSize);
	p->LinkList(OBJECT_2D_NUMBER);
	p->SetPosition(pPos);

	Vec2 v1(0.0f, 0.0f);
	Vec2 v2(0.1f, 1.0f);
	p->SetTexCoord(&v1, &v2);

	return p;
}


//*************************************************
//			   		C2DNumber クラス
//*************************************************
/*
 *	コンストラクタ
 */
C2DNumber :: C2DNumber(bool bZero, bool bRight, int nDigit):
		m_bZero(bZero),
		m_bRight(bRight),
		m_nDigit(nDigit),
		m_nNumber(0){

}

/*
 * クラス名：C2DNumber
 * 関数名：Create()
 * 内容：インスタンス生成
 * 引数：pTexFileName			;使用テクスチャファイル名
 *		 pPos					;描画位置 (左上)
 *		 pDigitSize				;数字１桁の描画サイズ
 *		 fInterval              ;数字の配置間隔
 *		 nPriority				;描画優先度
 *		 nDigit					;描画桁数
 *		 bRight					;右詰めフラグ
 *		 bZero					;0詰めフラグ
 */
C2DNumber *C2DNumber :: Create(const char *pTexFileName, const Vec2 *pPos, const Vec2 *pDigitSize, float fInterval, unsigned int nPriority, int nDigit, bool bRight, bool bZero){
	C2DNumber *p = new C2DNumber(bZero, bRight, nDigit);
	p->Init(pTexFileName, pPos, pDigitSize, fInterval, nPriority);
	return p;
}

/*
 * クラス名：C2DNumber
 * 関数名：Init()
 * 内容：初期化処理
 * 引数：pTexFileName			;使用テクスチャファイル名
 *		 pPos					;描画位置 (左上)
 *		 pDigitSize				;数字１桁の描画サイズ
 *		 fInterval              ;数字の間隔
 *		 nPriority				;描画優先度
 * 返却値：	処理成功 -> 0
 *			処理失敗 -> -1
 */
int C2DNumber :: Init(const char *pTexFileName, const Vec2 *pPos, const Vec2 *pDigitSize, float fInterval, unsigned int nPriority){
	/*** ワークの確保 ***/
	m_pNumber = new char[m_nDigit];
	m_ppSingleNumber = new C2DSingleNumber*[m_nDigit];

	Vec2 pos(pPos->x + (pDigitSize->x * 0.5f), pPos->y + (pDigitSize->y * 0.5f));

	for(int i = 0; i < m_nDigit; ++i){
		m_ppSingleNumber[i] = C2DSingleNumber :: Create(pTexFileName, &pos, pDigitSize, nPriority);
		pos.x += fInterval;
		m_pNumber[i] = 0;
	}

	return 0;
}

/*
 * クラス名：C2DNumber
 * 関数名：Release()
 * 内容：インスタンス破棄
 */
void C2DNumber :: Release(void){
	delete[] m_pNumber;

	for(int i = 0; i < m_nDigit; ++i){
		m_ppSingleNumber[i]->Release();
	}

	delete[] m_ppSingleNumber;
	delete this;
}

/*
 * クラス名：C2DNumber
 * 関数名：SetNumber()
 * 内容：描画数字を設定する
 */
void C2DNumber :: SetNumber(unsigned int num){
	m_nNumber = num;

	/*** 配列に１桁ずつ格納する ***/
	int nDigit = NumberToArray(num);

	/*** 左詰め ***/
	if(!m_bRight){
		int count = 0;

		for(int i = m_nDigit - nDigit - 1; count <= nDigit; ++i, ++count){
			m_ppSingleNumber[count]->SetNumber(m_pNumber[i]);
		}
		for( ; count < m_nDigit; ++count){
			m_ppSingleNumber[count]->SetNumber(-1);
		}

		/*** 右詰め0詰め ***/
	} else if(m_bZero){
		for(int i = 0; i < m_nDigit; ++i){
			m_ppSingleNumber[i]->SetNumber(m_pNumber[i]);
		}

		/*** 右詰めのみ ***/
	} else {
		int count = 0;
		for(int i = 0; i < (m_nDigit - nDigit); ++i){
			m_ppSingleNumber[i]->SetNumber(-1);
		}
		for(int i = m_nDigit - nDigit - 1; i < m_nDigit; ++i){
			m_ppSingleNumber[i]->SetNumber(m_pNumber[i]);
		}
	}

}

/*
 * クラス名：C2DNumber
 * 関数名：NumberToArray()
 * 内容：設定された数字を配列に１桁ずつ格納
 * 返却値：実効桁数
 */
int C2DNumber :: NumberToArray(unsigned int num){
	int work = 0;
	int i;
	int result = 0;

	for(i = m_nDigit - 1; (i >= 0) && (work == 0); --i){
		work = (int)((double)num / pow(10.0, (double)i));
		work %= 10;
	}

	result = i + 1;

	for(i = 0; i < m_nDigit; ++i){
		work = (int)((double)num / pow(10.0, (double)(m_nDigit - i - 1)));
		work %= 10;
		m_pNumber[i] = work;
	}

	return result;
}