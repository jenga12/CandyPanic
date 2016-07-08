/*
 *	File：2DPolygon.cpp
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：2Dポリゴン処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "2DPolygon.h"


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
//				  C2DPolygon クラス
//*************************************************
/*
 *	コンストラクタ
 */
C2DPolygon :: C2DPolygon(unsigned int nVtxNum, unsigned int nPriority):
		m_pos(Vec2(0.0f, 0.0f)),
		m_fRot(0.0f),
		m_scl(1.0f, 1.0f),
		C2DObject(nPriority){
	m_VtxData.nVtxNum = nVtxNum;

}

/*
 * クラス名：C2DPolygon
 * 関数名：Create()
 * 内容：インスタンス生成
 * 引数：nVtxNum			;使用頂点数
 *		 pVtx				;初期頂点データ
 *		 nPriority			;描画優先度
 */
C2DPolygon *C2DPolygon :: Create(unsigned int nVtxNum, VERTEX_2D *pVtx, unsigned int nPriority){
	C2DPolygon *p = new C2DPolygon(nVtxNum, nPriority);

	p->m_VtxData.pClr = new Color_32[nVtxNum];
	p->m_VtxData.pPos = new Vec2[nVtxNum];

	for(unsigned int i = 0; i < nVtxNum; ++i){
		p->m_VtxData.pClr[i] = pVtx[i].clr;
		p->m_VtxData.pPos[i] = pVtx[i].pos;
	}

	return p;
}

/*
 * クラス名：C2DPolygon
 * 関数名：Init()
 * 内容：初期化処理
 * 引数：pVtx			;初期頂点データ
 */
int C2DPolygon :: Init(const VERTEX_2D *pVtx){

	m_VtxData.pClr = new Color_32[m_VtxData.nVtxNum];
	m_VtxData.pPos = new Vec2[m_VtxData.nVtxNum];

	for(unsigned int i = 0; i < m_VtxData.nVtxNum; ++i){
		m_VtxData.pClr[i] = pVtx[i].clr;
		m_VtxData.pPos[i] = pVtx[i].pos;
	}

	return 0;
}

/*
 * クラス名：C2DPolygon
 * 関数名：Destroy()
 * 内容：インスタンス破棄
 */
void C2DPolygon :: Destroy(void){
	delete[] m_VtxData.pClr;
	delete[] m_VtxData.pPos;
	delete this;
}

/*
 * クラス名：C2DPolygon
 * 関数名：Draw()
 * 内容：描画処理
 */
void C2DPolygon :: Draw(void){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(m_pos.x, m_pos.y, 0.0f);
	glRotatef(PI * 2.0f * (m_fRot / 360.0f), 0.0f, 0.0f, 1.0f);
	glScalef(m_scl.x, m_scl.y, 1.0f);

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, m_VtxData.pPos);
	glColorPointer(4, GL_FLOAT, 0, m_VtxData.pClr);

	glDrawArrays(GL_TRIANGLE_FAN, 0, m_VtxData.nVtxNum);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glPopMatrix();
}
