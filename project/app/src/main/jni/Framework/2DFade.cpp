/*
 *	File：2DFade.cpp
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：フェード処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "2DFade.h"
#include "../main.h"


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
//					C2DFade クラス
//*************************************************
/*
 *	コンストラクタ
 */
C2DFade :: C2DFade():
		C2DPolygon(4, 0),
		m_nFrameCount(0),
		m_Color(Color_32(1.0f, 1.0f, 1.0f, 0.0f)),
		m_nState(FADE_NONE){

}

/*
 * クラス名：C2DFade
 * 関数名：Create()
 * 内容：インスタンス生成
 */
C2DFade *C2DFade :: Create(void){
	C2DFade *p = new C2DFade();

	VERTEX_2D aVtx[4];

	aVtx[0].pos = Vec2(0.0f, 0.0f);
	aVtx[1].pos = Vec2(APP_WIDTH, 0.0f);
	aVtx[2].pos = Vec2(APP_WIDTH, APP_HEIGHT);
	aVtx[3].pos = Vec2(0.0f, APP_HEIGHT);
	aVtx[0].clr = Color_32(1.0f, 1.0f, 1.0f, 0.0f);
	aVtx[1].clr = Color_32(1.0f, 1.0f, 1.0f, 0.0f);
	aVtx[2].clr = Color_32(1.0f, 1.0f, 1.0f, 0.0f);
	aVtx[3].clr = Color_32(1.0f, 1.0f, 1.0f, 0.0f);

	p->Init(aVtx);
	p->LinkList(OBJECT_2D_FADE);

	return p;
}

/*
 * クラス名：C2DFade
 * 関数名：Update()
 * 内容：更新処理
 */
void C2DFade :: Update(void){
	switch(m_nState){
		case FADE_IN:
			++m_nFrameCount;
			m_Color.a = 1.0f - ((float)m_nFrameCount / (float)m_nFrame);

			if(m_nFrameCount == m_nFrame){
				m_nState = FADE_END;
				m_Color.a = 0.0f;
				m_nFrameCount = 0;
			}

			break;


		case FADE_OUT:
			++m_nFrameCount;
			m_Color.a = (float)m_nFrameCount / (float)m_nFrame;

			if(m_nFrameCount == m_nFrame){
				m_nState = FADE_END;
				m_Color.a = 1.0f;
				m_nFrameCount = 0;
			}

			break;
	}

	Color_32 aClr[4] = {
			Color_32(m_Color.r, m_Color.g, m_Color.b, m_Color.a),
			Color_32(m_Color.r, m_Color.g, m_Color.b, m_Color.a),
			Color_32(m_Color.r, m_Color.g, m_Color.b, m_Color.a),
			Color_32(m_Color.r, m_Color.g, m_Color.b, m_Color.a)
	};

	C2DPolygon :: SetColor(aClr);
}
