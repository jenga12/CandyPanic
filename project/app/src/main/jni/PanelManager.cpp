/*
 *	File：PanelManager.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：パネル管理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "PanelManager.h"
#include "Framework/2DAnimation.h"
#include "Framework/TextureManager.h"
#include "panel.h"
#include "score.h"
#include "Framework/sound.h"
#include "Framework/MyMath.h"
#include "Framework/MainManager.h"
#include "player.h"
#include "attack.h"
#include "combo.h"
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
//					CPanelManager クラス
//*************************************************
/*
 *	コンストラクタ
 */
CPanelManager :: CPanelManager():
m_nSlideCount(0),
m_nCombo(0),
m_nGrayRemain(0){
	
}

/*
 * クラス名：CPanelManager
 * 関数名：Create()
 * 内容：インスタンス生成
 * 引数：pPlayer           ;プレイヤーオブジェクト
 *       pEnemy            ;敵オブジェクト
 */
CPanelManager *CPanelManager :: Create(CPlayer *pPlayer, CEnemy *pEnemy){
	CPanelManager *p = new CPanelManager();
	p->Init(pEnemy);
	p->m_pPlayer = pPlayer;
	return p;
}

/*
 * クラス名：CPanelManager
 * 関数名：Init()
 * 内容：初期化処理
 * 引数：pEnemy            ;敵オブジェクト
 */
int CPanelManager :: Init(CEnemy *pEnemy){
	ClearCheckFlag();
	
	/*** パネルテクスチャ ***/
	m_apTexPanel[PANEL_PINK] = CTextureManager :: Create("game/ball_pink.img", false);
	m_apTexPanel[PANEL_CYAN] = CTextureManager :: Create("game/ball_cyan.img", false);
	m_apTexPanel[PANEL_GREEN] = CTextureManager :: Create("game/ball_green.img", false);
	m_apTexPanel[PANEL_BLUE] = CTextureManager :: Create("game/ball_blue.img", false);
	m_apTexPanel[PANEL_ORANGE] = CTextureManager :: Create("game/ball_orange.img", false);
	m_pTexGray = CTextureManager :: Create("game/ball_gray.img", false);
	
	/*** エフェクトテクスチャ ***/
	m_apTexEffect[PANEL_PINK] = CTextureManager :: Create("game/pink_effect.img", false);
	m_apTexEffect[PANEL_CYAN] = CTextureManager :: Create("game/cyan_effect.img", false);
	m_apTexEffect[PANEL_BLUE] = CTextureManager :: Create("game/blue_effect.img", false);
	m_apTexEffect[PANEL_ORANGE] = CTextureManager :: Create("game/orange_effect.img", false);
	m_apTexEffect[PANEL_GREEN] = CTextureManager :: Create("game/green_effect.img", false);
	m_pTexGrayEffect = CTextureManager :: Create("game/gray_effect.img", false);
	
	/*** パネルとエフェクトの生成、マップの初期化 ***/
	for(int i = 0; i < FIELD_LINE; ++i){
		float y = LeftTopPanelPos.y + PANEL_INTERVAL * i;
		for(int j = 0; j < FIELD_ROW; ++j){
			Vec2 pos(LeftTopPanelPos.x + PANEL_INTERVAL * j, y);
			m_apPanel[j][i] =  CPanel :: Create(m_apTexPanel[PANEL_PINK], &pos);
			m_aField[j][i] = PANEL_NONE;
		}
	}
	
	/*** ブロックの配置 ***/
	m_aField[6][6] = PANEL_BLOCK;
	m_aField[6][7] = PANEL_BLOCK;
	m_aField[7][6] = PANEL_BLOCK;
	m_aField[7][7] = PANEL_BLOCK;

	m_pGyro = CGyro :: Create();
	m_pScore = CScore :: Create();

	for(int i = 0; i < ATTACK_EFFECT_MAX; ++i){
		m_apAttack[i] = CAttack :: Create(pEnemy);
	}

	m_apCombo[0] = CCombo :: Create();
	m_apCombo[1] = CCombo :: Create();
	m_apCombo[2] = CCombo :: Create();

	m_pEraseSE = CSound :: Create("erase.wav");
	m_pPaddingSE = CSound :: Create("padding.wav");
	m_pEnemyAttackSE = CSound :: Create("enemy_attack.wav");
}

/*
 * クラス名：CPanelManager
 * 関数名：Release()
 * 内容：インスタンス破棄
 */
void CPanelManager :: Release(void){
	/*** パネルとエフェクトの破棄 ***/
	for(int i = 0; i < FIELD_LINE; ++i){
		for(int j = 0; j < FIELD_ROW; ++j){
			m_apPanel[j][i]->Release();
			m_apPanel[j][i]->Destroy();			// テクスチャは勝手に破棄される
		}
	}
	
	/*** テクスチャの破棄 ***/
	for(int i = 0; i < PANEL_COLOR_NUM; ++i){
		m_apTexPanel[i]->Release(true);
		m_apTexEffect[i]->Release(true);
	}
	
	m_pTexGray->Release();
	m_pTexGrayEffect->Release();
	m_pScore->Release();
	m_pGyro->Release();

	for(int i = 0; i < ATTACK_EFFECT_MAX; ++i){
		m_apAttack[i]->Destroy();
	}

	m_apCombo[0]->Release();
	m_apCombo[1]->Release();
	m_apCombo[2]->Release();

	m_pPaddingSE->Release();
	m_pEraseSE->Release();
	m_pEnemyAttackSE->Release();
}

/*
 * クラス名：CPanelManager
 * 関数名：Update()
 * 内容：更新処理
 */
void CPanelManager :: Update(void) {
	m_pGyro->Update();

	/*** 消えているパネルがあるか調査 ***/
	bool bErase = false;
	for (int i = 0; i < FIELD_ROW; ++i) {
		for (int j = 0; j < FIELD_LINE; ++j) {
			if (m_apPanel[i][j]->IsErase()) {
				bErase = true;
				break;
			}
		}
	}

	/*** パネルの移動チェック ***/
	bool move = false;
	for (int i = 0; i < FIELD_ROW; ++i) {
		for (int j = 0; j < FIELD_LINE; ++j) {
			if (m_apPanel[i][j]->IsMove()) {
				move = true;
				break;
			}
		}
	}

	/*** パネルの消去処理 ***/
	if(!move){
		int EraseCount = 0;
		bool bFirst = true;
		Vec2 pos(0.0f, 0.0f);

		for (int i = 0; i < FIELD_ROW; ++i) {
			for (int j = 0; j < FIELD_LINE; ++j) {
				if ((m_aField[i][j] != PANEL_NONE) && (m_aField[i][j] != PANEL_BLOCK) &&
				    (m_aField[i][j] != PANEL_GRAY) && (!(m_apPanel[i][j]->IsMove()))) {
					ClearCheckFlag();
					m_bCheckFlag[i][j] = false;
					int count = PanelCount(i, j, m_aField[i][j], 1);

					if (count >= PANEL_ERASE_TERM) {
						EraseCount += count;
						ClearCheckFlag();
						m_bCheckFlag[i][j] = false;
						PanelErase(i, j, m_aField[i][j]);
						m_apPanel[i][j]->Erase(m_apTexEffect[m_aField[i][j]]);
						m_aField[i][j] = PANEL_NONE;
						pos = Vec2(LeftTopPanelPos.x + PANEL_INTERVAL * i,
						           LeftTopPanelPos.y + PANEL_INTERVAL * j);
						move = true;
						bErase = true;

						/*** コンボ処理 ***/
						if(bFirst){
							if (m_nSlideCount <= 1) {
								++m_nCombo;
							} else {
								m_nCombo = 1;
							}
							bFirst = false;

							for(int k = 0; k < 3; ++k){
								if(!(m_apCombo[k]->Use())){
									m_apCombo[k]->Pop(&pos, m_nCombo);
									break;
								}
							}

							m_pEraseSE->Play(true, false);
						}

						for(int k = 0; k < ATTACK_EFFECT_MAX; ++k){
							if(!(m_apAttack[k]->Use())){
								m_apAttack[k]->Start(&pos, (count * m_nCombo) / 3);
								break;
							}
						}
					}
				}
			}
		}

		/*** パネルが消された ***/
		if (pos.x != 0.0f) {
			m_pScore->AddScore((unsigned int)(EraseCount * 10.0 * pow(m_nCombo, 1.7)));
			m_nSlideCount = 0;
			m_pPlayer->SetPlayerFace(FACE_ANGRY, 60);
		}
	}

	if (!bErase) {
		GYRO_ANGLE angle = m_pGyro->GetGyro();
		const INPUT *pInput = CMainManager :: GetInput();

		/*** パネルの追加 ***/
		if (pInput[0].flag == 1) {
			switch (angle) {
				case GYRO_LEFT:
					PaddingLeft();
					m_pPaddingSE->Play(true, false);
					++m_nSlideCount;
					break;

				case GYRO_BOTTOM:
					PaddingDown();
					m_pPaddingSE->Play(true, false);
					++m_nSlideCount;
					break;

				case GYRO_TOP:
					PaddingUp();
					m_pPaddingSE->Play(true, false);
					++m_nSlideCount;
					break;

				case GYRO_RIGHT:
					PaddingRight();
					m_pPaddingSE->Play(true, false);
					++m_nSlideCount;
					break;
			}

			/*** パネルの移動 ***/
		} else if(!move){
			switch (angle) {
				case GYRO_LEFT:
					SlideLeft();
					++m_nSlideCount;
					break;

				case GYRO_BOTTOM:
					SlideDown();
					++m_nSlideCount;
					break;

				case GYRO_TOP:
					SlideUp();
					++m_nSlideCount;
					break;

				case GYRO_RIGHT:
					SlideRight();
					++m_nSlideCount;
					break;
			}
		}

		/*** おじゃまの追加 ***/
		if(m_nGrayRemain){
			if (angle == GYRO_HORIZON) {
				angle = (CMath::GetRand() % 4) + 1;
			}

			switch (angle) {
				case GYRO_LEFT:
					if (m_nGrayRemain > FIELD_LINE) {
						m_nGrayRemain -= FIELD_LINE;
						PaddingGrayLeft(m_nGrayRemain);
						m_pEnemyAttackSE->Play(true, false);
					} else {
						int nGrayRemain = m_nGrayRemain;
						m_nGrayRemain = 0;
						PaddingGrayLeft(nGrayRemain);
						m_pEnemyAttackSE->Play(true, false);
					}
					break;

				case GYRO_RIGHT:
					if (m_nGrayRemain > FIELD_LINE) {
						m_nGrayRemain -= FIELD_LINE;
						PaddingGrayRight(m_nGrayRemain);
						m_pEnemyAttackSE->Play(true, false);
					} else {
						int nGrayRemain = m_nGrayRemain;
						m_nGrayRemain = 0;
						PaddingGrayRight(nGrayRemain);
						m_pEnemyAttackSE->Play(true, false);
					}
					break;

				case GYRO_BOTTOM:
					if (m_nGrayRemain > FIELD_ROW) {
						m_nGrayRemain -= FIELD_ROW;
						PaddingGrayDown(m_nGrayRemain);
						m_pEnemyAttackSE->Play(true, false);
					} else {
						int nGrayRemain = m_nGrayRemain;
						m_nGrayRemain = 0;
						PaddingGrayDown(nGrayRemain);
						m_pEnemyAttackSE->Play(true, false);
					}
					break;

				case GYRO_TOP:
					if (m_nGrayRemain > FIELD_ROW) {
						m_nGrayRemain -= FIELD_ROW;
						PaddingGrayUp(m_nGrayRemain);
						m_pEnemyAttackSE->Play(true, false);
					} else {
						int nGrayRemain = m_nGrayRemain;
						m_nGrayRemain = 0;
						PaddingGrayUp(nGrayRemain);
						m_pEnemyAttackSE->Play(true, false);
					}

					break;


			}
		}
	}

	/*** パネルの更新 ***/
	for(int i = 0; i < FIELD_LINE; ++i){
		for(int j = 0; j < FIELD_ROW; ++j){
			m_apPanel[j][i]->Update();
		}
	}

	m_pScore->Update();

	/*** 密度を求める ***/
	int count = 0;
	for(int i = 0; i < FIELD_ROW; ++i) {
		for (int j = 0; j < FIELD_LINE; ++j) {
			if (m_aField[i][j] != PANEL_NONE) {
				++count;
			}
		}
	}

	/*** 攻撃エフェクトの更新 ***/
	for(int i = 0; i < ATTACK_EFFECT_MAX; ++i){
		m_apAttack[i]->Update();
	}

	/*** コンボ表記の更新 ***/
	for(int i = 0; i < 3; ++i){
		m_apCombo[i]->Update();
	}

	m_pPlayer->Update((float)count / (float)(FIELD_ROW * FIELD_LINE), bErase);
}

/*
 * クラス名：CPanelManager
 * 関数名：Fall()
 * 内容：パネルを全てフィールドから落とす
 */
void CPanelManager :: Fall(void){
	for(int i = 0; i < FIELD_ROW; ++i){
		for(int j = 0; j < FIELD_LINE; ++j){
			Vec2 pos(CMath :: GetRand() % 1280, -600.0f - (CMath :: GetRand() % 2000));
			Vec2 target(pos.x, 900);
			Vec2 move(0.0f, 25.0f);
			m_apPanel[i][j]->SetPosition(&pos);
			m_apPanel[i][j]->SetTarget(&target, &move);

			if(!(m_apPanel[i][j]->IsList())){
				m_apPanel[i][j]->LinkList(OBJECT_2D_PANEL);
			}

			m_apPanel[i][j]->End();
			m_apPanel[i][j]->SetPriority(2);
		}
	}
}
/*
 * クラス名：CPanelManager
 * 関数名：ClearAll()
 * 内容：すべてのパネルを消す
 */
void CPanelManager :: ClearAll(void){
	for(int i = 0; i < FIELD_ROW; ++i){
		for(int j = 0; j < FIELD_LINE; ++j) {
			if(m_aField[i][j] == PANEL_GRAY){
				m_apPanel[i][j]->Erase(m_pTexGrayEffect);
			} else if((m_aField[i][j] != PANEL_NONE) && (m_aField[i][j] != PANEL_BLOCK)){
				m_apPanel[i][j]->Erase(m_apTexEffect[m_aField[i][j]]);
			}
		}
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：UpdateWin()
 * 内容：勝利時の更新処理
 */
void CPanelManager :: UpdateWin(void){
	for(int i = 0; i < FIELD_ROW; ++i){
		for(int j = 0; j < FIELD_LINE; ++j){
			m_apPanel[i][j]->Update();
		}
	}

	for(int i = 0; i < ATTACK_EFFECT_MAX; ++i){
		m_apAttack[i]->Update();
	}

	for(int i = 0; i < 3; ++i){
		m_apCombo[i]->Update();
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：PaddingLeft()
 * 内容：左方向にパネルを敷き詰める
 */
void CPanelManager :: PaddingLeft(void){
	int i, j;
	
	for(i = 0; i < FIELD_LINE; ++i){
		for(j = FIELD_ROW - 1; j >= 0; --j){
			if(m_aField[j][i] != PANEL_NONE){
				break;
			}
		}

		if(++j < FIELD_ROW){
			CreatePanel(j, i);
			Vec2 pos(LeftTopPanelPos.x + FIELD_ROW * PANEL_INTERVAL,LeftTopPanelPos.y + i * PANEL_INTERVAL);
			m_apPanel[j][i]->SetPosition(
				&pos
			);
				
			Vec2 target(LeftTopPanelPos.x + PANEL_INTERVAL * j, LeftTopPanelPos.y + PANEL_INTERVAL * i);
			Vec2 move(-PANEL_MOVE_SPEED, 0.0f);
			m_apPanel[j][i]->SetTarget(
				&target,
				&move
			);

			m_apPanel[j][i]->LinkList(OBJECT_2D_PANEL);
		}
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：PaddingRight()
 * 内容：右方向にパネルを敷き詰める
 */
void CPanelManager :: PaddingRight(void){
	int i, j;
	for(i = 0; i < FIELD_LINE; ++i){
		for(j = 0; j < FIELD_ROW; ++j){
			if(m_aField[j][i] != PANEL_NONE){
				break;
			}
		}

		if(--j >= 0){
			CreatePanel(j, i);

			Vec2 pos(LeftTopPanelPos.x + -1 * PANEL_INTERVAL, LeftTopPanelPos.y + i * PANEL_INTERVAL);
			m_apPanel[j][i]->SetPosition(&pos);

			Vec2 target(LeftTopPanelPos.x + PANEL_INTERVAL * j, LeftTopPanelPos.y + PANEL_INTERVAL * i);
			Vec2 move(PANEL_MOVE_SPEED, 0.0f);

			m_apPanel[j][i]->SetTarget(&target, &move);
			m_apPanel[j][i]->LinkList(OBJECT_2D_PANEL);
		}
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：PaddingDown()
 * 内容：下方向にパネルを敷き詰める
 */
void CPanelManager :: PaddingDown(void){
	int i, j;
	for(j = 0; j < FIELD_ROW; ++j){
		for(i = 0; i < FIELD_LINE; ++i){
			if(m_aField[j][i] != PANEL_NONE){
				break;
			}
		}

		if(--i >= 0){
			CreatePanel(j, i);
			Vec2 pos(LeftTopPanelPos.x + PANEL_INTERVAL * j, LeftTopPanelPos.y + PANEL_INTERVAL * -1);
			m_apPanel[j][i]->SetPosition(&pos);

			Vec2 target(LeftTopPanelPos.x + PANEL_INTERVAL * j, LeftTopPanelPos.y + PANEL_INTERVAL * i);
			Vec2 move(0.0f, PANEL_MOVE_SPEED);
			m_apPanel[j][i]->SetTarget(&target, &move);

			m_apPanel[j][i]->LinkList(OBJECT_2D_PANEL);
		}
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：PaddingUp()
 * 内容：上方向にパネルを敷き詰める
 */
void CPanelManager :: PaddingUp(void){
	int i, j;

	for(j = 0; j < FIELD_ROW; ++j){
		for(i = FIELD_LINE - 1; i >= 0; --i){
			if(m_aField[j][i] != PANEL_NONE){
				break;
			}
		}

		if(++i < FIELD_LINE){
			CreatePanel(j, i);

			Vec2 pos(LeftTopPanelPos.x + PANEL_INTERVAL * j, LeftTopPanelPos.y + PANEL_INTERVAL * FIELD_LINE);
			m_apPanel[j][i]->SetPosition(&pos);

			Vec2 target(LeftTopPanelPos.x + PANEL_INTERVAL * j, LeftTopPanelPos.y + PANEL_INTERVAL * i);
			Vec2 move(0.0f, -PANEL_MOVE_SPEED);
			m_apPanel[j][i]->SetTarget(&target, &move);

			m_apPanel[j][i]->LinkList(OBJECT_2D_PANEL);
		}
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：PaddingGray()
 * 内容：おじゃまを発生させる
 * 引数：num               ;おじゃまの数
 */
void CPanelManager :: PaddingGray(int num){
	m_nGrayRemain += num;
}

/*
 * クラス名：CPanelManager
 * 関数名：PaddingGrayLeft()
 * 内容：左方向におじゃまパネルを敷き詰める
 * 引数：num				;おじゃまパネルの数
 */
void CPanelManager :: PaddingGrayLeft(int num){
	int i, j;
	
	/*** 配列の初期化 ***/
	int array[FIELD_LINE];
	for(i = 0; i < FIELD_LINE; ++i){
		array[i] = i;
	}
	
	/*** 配列のシャッフル ***/
	for(i = 0; i < FIELD_LINE; ++i){
		int swap = array[i];
		int rnd = CMath :: GetRand() % FIELD_LINE;
		array[i] = array[rnd];
		array[rnd] = swap;
	}
	
	for(int idx = 0; idx < num; ++idx){
		i = array[idx];
		
		for(j = FIELD_ROW - 1; j >= 0; --j){
			if(m_aField[j][i] != PANEL_NONE){
				break;
			}
		}

		if(++j < FIELD_ROW){
			m_aField[j][i] = PANEL_GRAY;
			m_apPanel[j][i]->SetTextureManager(m_pTexGray);
			
			Vec2 pos(LeftTopPanelPos.x + FIELD_ROW * PANEL_INTERVAL,LeftTopPanelPos.y + i * PANEL_INTERVAL);
			m_apPanel[j][i]->SetPosition(&pos);
				
			Vec2 target(LeftTopPanelPos.x + PANEL_INTERVAL * j, LeftTopPanelPos.y + PANEL_INTERVAL * i);
			Vec2 move(-PANEL_MOVE_SPEED, 0.0f);
			m_apPanel[j][i]->SetTarget(&target, &move);

			m_apPanel[j][i]->LinkList(OBJECT_2D_PANEL);
		} else {
			++m_nGrayRemain;
		}
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：PaddingGrayRight()
 * 内容：右方向におじゃまパネルを敷き詰める
 * 引数：num				;おじゃまパネルの数
 */
void CPanelManager :: PaddingGrayRight(int num){
	int i, j;
	
	/*** 配列の初期化 ***/
	int array[FIELD_LINE];
	for(i = 0; i < FIELD_LINE; ++i){
		array[i] = i;
	}
	
	/*** 配列のシャッフル ***/
	for(i = 0; i < FIELD_LINE; ++i){
		int swap = array[i];
		int rnd = CMath :: GetRand() % FIELD_LINE;
		array[i] = array[rnd];
		array[rnd] = swap;
	}
	
	for(int idx = 0; idx < num; ++idx){
		i = array[idx];
		
		for(j = 0; j < FIELD_ROW; ++j){
			if(m_aField[j][i] != PANEL_NONE){
				break;
			}
		}

		if(--j >= 0){
			m_aField[j][i] = PANEL_GRAY;
			m_apPanel[j][i]->SetTextureManager(m_pTexGray);
			
			Vec2 pos(LeftTopPanelPos.x + -1 * PANEL_INTERVAL,LeftTopPanelPos.y + i * PANEL_INTERVAL);
			m_apPanel[j][i]->SetPosition(&pos);
				
			Vec2 target(LeftTopPanelPos.x + PANEL_INTERVAL * j, LeftTopPanelPos.y + PANEL_INTERVAL * i);
			Vec2 move(PANEL_MOVE_SPEED, 0.0f);
			m_apPanel[j][i]->SetTarget(&target, &move);

			m_apPanel[j][i]->LinkList(OBJECT_2D_PANEL);
		} else {
			++m_nGrayRemain;
		}
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：PaddingGrayUp()
 * 内容：上方向におじゃまパネルを敷き詰める
 * 引数：num				;おじゃまパネルの数
 */
void CPanelManager :: PaddingGrayUp(int num){
	int i, j;
	
	/*** 配列の初期化 ***/
	int array[FIELD_ROW];
	for(i = 0; i < FIELD_ROW; ++i){
		array[i] = i;
	}
	
	/*** 配列のシャッフル ***/
	for(i = 0; i < FIELD_ROW; ++i){
		int swap = array[i];
		int rnd = CMath :: GetRand() % FIELD_ROW;
		array[i] = array[rnd];
		array[rnd] = swap;
	}

	
	for(int idx = 0; idx < num; ++idx){
		j = array[idx];
		
		for(i = FIELD_LINE - 1; i >= 0; --i){
			if(m_aField[j][i] != PANEL_NONE){
				break;
			}
		}

		if(++i < FIELD_LINE){
			m_aField[j][i] = PANEL_GRAY;
			m_apPanel[j][i]->SetTextureManager(m_pTexGray);

			Vec2 pos(LeftTopPanelPos.x + PANEL_INTERVAL * j, LeftTopPanelPos.y + PANEL_INTERVAL * FIELD_LINE);
			m_apPanel[j][i]->SetPosition(&pos);

			Vec2 target(LeftTopPanelPos.x + PANEL_INTERVAL * j, LeftTopPanelPos.y + PANEL_INTERVAL * i);
			Vec2 move(0.0f, -PANEL_MOVE_SPEED);
			m_apPanel[j][i]->SetTarget(&target, &move);

			m_apPanel[j][i]->LinkList(OBJECT_2D_PANEL);
		} else {
			++m_nGrayRemain;
		}
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：PaddingGrayDown()
 * 内容：下方向におじゃまパネルを敷き詰める
 * 引数：num					;おじゃまパネルの数
 */
void CPanelManager :: PaddingGrayDown(int num){
	int i, j;
	
	/*** 配列の初期化 ***/
	int array[FIELD_ROW];
	for(i = 0; i < FIELD_ROW; ++i){
		array[i] = i;
	}
	
	/*** 配列のシャッフル ***/
	for(i = 0; i < FIELD_ROW; ++i){
		int swap = array[i];
		int rnd = CMath :: GetRand() % FIELD_ROW;
		array[i] = array[rnd];
		array[rnd] = swap;
	}

	
	for(int idx = 0; idx < num; ++idx){
		j = array[idx];
		
		for(i = 0; i < FIELD_LINE; ++i){
			if(m_aField[j][i] != PANEL_NONE){
				break;
			}
		}

		if(--i >= 0){
			m_aField[j][i] = PANEL_GRAY;
			m_apPanel[j][i]->SetTextureManager(m_pTexGray);

			Vec2 pos(LeftTopPanelPos.x + PANEL_INTERVAL * j, LeftTopPanelPos.y + PANEL_INTERVAL * -1);
			m_apPanel[j][i]->SetPosition(&pos);

			Vec2 target(LeftTopPanelPos.x + PANEL_INTERVAL * j, LeftTopPanelPos.y + PANEL_INTERVAL * i);
			Vec2 move(0.0f, PANEL_MOVE_SPEED);
			m_apPanel[j][i]->SetTarget(&target, &move);

			m_apPanel[j][i]->LinkList(OBJECT_2D_PANEL);
		} else {
			++m_nGrayRemain;
		}
	}
}


/*
 * クラス名：CPanelManager
 * 関数名：SlideLeft()
 * 内容：左方向にパネルをスライドさせる
 */
void CPanelManager :: SlideLeft(void){
	for(int i = 0; i < FIELD_LINE; ++i){
		for(int j = 0; j < FIELD_ROW; ++j){
			if((m_aField[j][i] != PANEL_NONE) && (m_aField[j][i] != PANEL_BLOCK)){
				int k;
				for(k = j - 1; k >= 0; --k){
					if(m_aField[k][i] != PANEL_NONE){
						break;
					}
				}

				if((++k < FIELD_ROW) && (k != j) && (!m_apPanel[j][i]->IsMove())){
					m_aField[k][i] = m_aField[j][i];
					m_aField[j][i] = PANEL_NONE;

					CPanel *swap;
					swap = m_apPanel[k][i];
					m_apPanel[k][i] = m_apPanel[j][i];
					m_apPanel[j][i] = swap;

					Vec2 target(LeftTopPanelPos.x + PANEL_INTERVAL * k, LeftTopPanelPos.y + PANEL_INTERVAL * i);
					Vec2 move(-PANEL_MOVE_SPEED, 0.0f);
					m_apPanel[k][i]->SetTarget(&target, &move);
				}
			}
		}
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：SlideRight() 
 * 内容：右方向にパネルをスライドさせる
 */
void CPanelManager :: SlideRight(void){
	for(int i = 0; i < FIELD_LINE; ++i){
		for(int j = FIELD_ROW - 2; j >= 0; --j){
			if((m_aField[j][i] != PANEL_NONE) && (m_aField[j][i] != PANEL_BLOCK)){
				int k;
				for(k = j + 1; k < FIELD_ROW; ++k){
					if(m_aField[k][i] != PANEL_NONE){
						break;
					}
				}

				if((--k >= 0) && (k != j) && (!m_apPanel[j][i]->IsMove())){
					m_aField[k][i] = m_aField[j][i];
					m_aField[j][i] = PANEL_NONE;

					CPanel *swap;
					swap = m_apPanel[k][i];
					m_apPanel[k][i] = m_apPanel[j][i];
					m_apPanel[j][i] = swap;

					Vec2 target(LeftTopPanelPos.x + PANEL_INTERVAL * k, LeftTopPanelPos.y + PANEL_INTERVAL * i);
					Vec2 move(PANEL_MOVE_SPEED, 0.0f);
					m_apPanel[k][i]->SetTarget(&target, &move);
				}
			}
		}
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：SlideDown()
 * 内容：下方向にパネルをスライドさせる
 */
void CPanelManager :: SlideDown(void){
	for(int j = 0; j < FIELD_ROW; ++j){
		for(int i = FIELD_LINE - 2; i >= 0; --i){
			if((m_aField[j][i] != PANEL_NONE) && (m_aField[j][i] != PANEL_BLOCK)){
				int k;
				for(k = i + 1; k < FIELD_LINE; ++k){
					if(m_aField[j][k] != PANEL_NONE){
						break;
					}
				}
				
				if((--k >= 0) && (k != i) && (!m_apPanel[j][i]->IsMove())){
					m_aField[j][k] = m_aField[j][i];
					m_aField[j][i] = PANEL_NONE;
					
					CPanel *swap;
					swap = m_apPanel[j][k];
					m_apPanel[j][k] = m_apPanel[j][i];
					m_apPanel[j][i] = swap;

					Vec2 target(LeftTopPanelPos.x + PANEL_INTERVAL * j, LeftTopPanelPos.y + PANEL_INTERVAL * k);
					Vec2 move(0.0f, PANEL_MOVE_SPEED);
					m_apPanel[j][k]->SetTarget(&target, &move);
				}
			}
		}
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：SlideUp()
 * 内容：上方向にパネルをスライドさせる
 */
void CPanelManager :: SlideUp(void){
	for(int j = 0; j < FIELD_ROW; ++j){
		for(int i = 1; i < FIELD_LINE; ++i){
			if((m_aField[j][i] != PANEL_NONE) && (m_aField[j][i] != PANEL_BLOCK)){
				int k;
				
				for(k = i - 1; k >= 0; --k){
					if(m_aField[j][k] != PANEL_NONE){
						break;
					}
				}
				
				if((++k < FIELD_LINE) && (k != i) && (!m_apPanel[j][i]->IsMove())){
					m_aField[j][k] = m_aField[j][i];
					m_aField[j][i] = PANEL_NONE;
					
					CPanel *swap;
					swap = m_apPanel[j][k];
					m_apPanel[j][k] = m_apPanel[j][i];
					m_apPanel[j][i] = swap;

					Vec2 target(LeftTopPanelPos.x + PANEL_INTERVAL * j, LeftTopPanelPos.y + PANEL_INTERVAL * k);
					Vec2 move(0.0f, -PANEL_MOVE_SPEED);
					m_apPanel[j][k]->SetTarget(&target, &move);
				}
			}
		}
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：PanelCount()
 * 内容：繋がっているパネルの数を数える
 * 引数：x				;チェックする座標x
 *		 y				;チェックする座標y
 *		 color			;チェックするパネルの色
 *		 count			;つながっているパネルの数 (初回呼び出し時には1を指定)
 * 返却値：繋がっているパネルの数
 */
int CPanelManager :: PanelCount(int x, int y, PANEL_COLOR color, int count){
	/*** 左側が同じ色ならば再帰呼び出し ***/
	if((x > 0) && m_bCheckFlag[x-1][y] && (!(m_apPanel[x-1][y]->IsMove())) && (m_aField[x-1][y] == color)){
		++count;
		m_bCheckFlag[x-1][y] = false;
		count = PanelCount(x-1, y, color, count);
	}
	
	/*** 右側が同じ色ならば再帰呼び出し ***/
	if(((x + 1) < FIELD_ROW) && m_bCheckFlag[x+1][y] && (!(m_apPanel[x+1][y]->IsMove())) && (m_aField[x+1][y] == color)){
		++count;
		m_bCheckFlag[x+1][y] = false;
		count = PanelCount(x+1, y, color, count);
	}
	
	/*** 上側が同じ色ならば再帰呼び出し ***/
	if((y > 0) && m_bCheckFlag[x][y-1] && (!(m_apPanel[x][y-1]->IsMove())) && (m_aField[x][y-1] == color)){
		++count;
		m_bCheckFlag[x][y-1] = false;
		count = PanelCount(x, y-1, color, count);
	}
	
	/*** 下側が同じ色ならば再帰呼び出し ***/
	if(((y + 1) < FIELD_LINE) && m_bCheckFlag[x][y+1] && (!(m_apPanel[x][y+1]->IsMove())) && (m_aField[x][y+1] == color)){
		++count;
		m_bCheckFlag[x][y+1] = false;
		count = PanelCount(x, y+1, color, count);
	}
	
	
	return count;
}

/*
 * クラス名：CPanelManager
 * 関数名：PanelErase()
 * 内容：繋がっているパネルを消す
 * 引数：x				;消すパネルの座標x
 *		 y				;消すパネルの座標y
 *		 color			;消すパネルの色
 */
void CPanelManager :: PanelErase(int x, int y, PANEL_COLOR color){
	/*** 左側のパネルを判定するか ***/
	if((x > 0) && m_bCheckFlag[x-1][y] && (!(m_apPanel[x-1][y]->IsMove()))){
		
		/*** 左側のパネルが同じ色 ***/
		if(m_aField[x-1][y] == color){
			m_bCheckFlag[x-1][y] = false;
			m_apPanel[x-1][y]->Erase(m_apTexEffect[color]);
			m_aField[x-1][y] = PANEL_NONE;
			PanelErase(x-1, y, color);
			
		/*** 左側のパネルがおじゃま ***/
		} else if(m_aField[x-1][y] == PANEL_GRAY){
			m_bCheckFlag[x-1][y] = false;
			m_apPanel[x-1][y]->Erase(m_pTexGrayEffect);
			m_aField[x-1][y] = PANEL_NONE;
		}
	}
	
	/*** 右側のパネルを判定するか ***/
	if(((x + 1) < FIELD_ROW) && m_bCheckFlag[x+1][y] && (!(m_apPanel[x+1][y]->IsMove()))){
		
		/*** 右側のパネルが同じ色 ***/
		if(m_aField[x+1][y] == color){
			m_bCheckFlag[x+1][y] = false;
			m_apPanel[x+1][y]->Erase(m_apTexEffect[color]);
			m_aField[x+1][y] = PANEL_NONE;
			PanelErase(x+1, y, color);
			
		/*** 右側のパネルがおじゃま ***/
		} else if(m_aField[x+1][y] == PANEL_GRAY){
			m_bCheckFlag[x+1][y] = false;
			m_apPanel[x+1][y]->Erase(m_pTexGrayEffect);
			m_aField[x+1][y] = PANEL_NONE;
		}
	}
	
	/*** 上側のパネルを判定するか ***/
	if((y > 0) && m_bCheckFlag[x][y-1] && (!(m_apPanel[x][y-1]->IsMove()))){
		
		/*** 上側のパネルが同じ色 ***/
		if(m_aField[x][y-1] == color){
			m_bCheckFlag[x][y-1] = false;
			m_apPanel[x][y-1]->Erase(m_apTexEffect[color]);
			m_aField[x][y-1] = PANEL_NONE;
			PanelErase(x, y-1, color);
			
		/*** 上側のパネルがおじゃま ***/
		} else if(m_aField[x][y-1] == PANEL_GRAY){
			m_bCheckFlag[x][y-1] = false;
			m_apPanel[x][y-1]->Erase(m_pTexGrayEffect);
			m_aField[x][y-1] = PANEL_NONE;
		}
	}
	
	/*** 下側が同じ色ならば再帰呼び出し ***/
	if(((y + 1) < FIELD_LINE) && m_bCheckFlag[x][y+1] && (!(m_apPanel[x][y+1]->IsMove()))){
		
		/*** 下側のパネルが同じ色 ***/
		if(m_aField[x][y+1] == color){
			m_bCheckFlag[x][y+1] = false;
			m_apPanel[x][y+1]->Erase(m_apTexEffect[color]);
			m_aField[x][y+1] = PANEL_NONE;
			PanelErase(x, y+1, color);
			
		/*** 下側のパネルがおじゃま ***/
		} else if(m_aField[x][y+1] == PANEL_GRAY){
			m_bCheckFlag[x][y+1] = false;
			m_apPanel[x][y+1]->Erase(m_pTexGrayEffect);
			m_aField[x][y+1] = PANEL_NONE;
		}
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：ClearCheckFlag()
 * 内容：チェックフラグをリセットする
 */
void CPanelManager :: ClearCheckFlag(void){
	for(int i = 0; i < FIELD_ROW; ++i){
		for(int j = 0; j < FIELD_LINE; ++j){
			m_bCheckFlag[i][j] = true;
		}
	}
}

/*
 * クラス名：CPanelManager
 * 関数名：CreatePanel()
 * 内容：指定位置にパネルを生成
 * 引数：x, y			;パネル生成位置
 */
void CPanelManager :: CreatePanel(int x, int y){
	char PanelColor = CMath :: GetRand() % PANEL_COLOR_NUM;
	m_aField[x][y] = PanelColor;
	m_apPanel[x][y]->SetTextureManager(m_apTexPanel[PanelColor]);
}