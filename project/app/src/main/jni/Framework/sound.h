/*
 *	File：sound.h
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：サウンド処理クラス定義
 */

#pragma once
#ifndef _SOUND_H_
#define _SOUND_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>


/******************************************************************************/
/*                              ライブラリリンク                              */
/******************************************************************************/


/******************************************************************************/
/*                              マクロ＆定数定義                              */
/******************************************************************************/
static const unsigned int WAVE_BUFFER_SIZE = 48000 * 2;


/******************************************************************************/
/*                                 構造体定義                                 */
/******************************************************************************/
struct WAVE_HEADER {
	char riff[4];
	unsigned int total_size;
	char fmt[8];
	unsigned int fmt_size;
	unsigned short format;
	unsigned short channel;
	unsigned int rate;
	unsigned int avgbyte;
	unsigned short block;
	unsigned short bit;
	char data[4];
	unsigned short data_size;
};

/******************************************************************************/
/*                                 クラス定義                                 */
/******************************************************************************/
class CSound {
	public:
	    static void Initialize(void);                   // 全体初期化
	    static void Finalize(void);                     // 全体終了
		static void DevicePause(void);                  // 中断
		static void Resume(void);                       // 再開
	    static CSound *Create(const char *pFileName);   // インスタンス生成
	    void Release(void);                              // インスタンス破棄
	    void Play(bool bReset = true, bool bLoop = false);  // 再生開始
	    void Pause(void);                                // 再生を中断
	    void Seek(unsigned int time);                   // 指定再生位置へシーク
		void SetLoopPoint(float second){                 // ループポイントを設定する (秒単位)
			m_nLoopPoint = (unsigned long long)((m_WavHeader.bit * m_WavHeader.rate * m_WavHeader.channel) * second);
		}

		bool IsPlaying(void){                            // 再生中であるか調べる
			SLuint32 state;
			(*m_bqPlayerPlay)->GetPlayState(m_bqPlayerPlay, &state);
			return (state == SL_PLAYSTATE_PLAYING) ? true : false;
		}

		void Callback(void);                            // コールバック関数
														 // (外部で呼び出さないでください)

	private:
	    CSound();                                         // コンストラクタ
	    ~CSound(){};                                      // デストラクタ
	    void Init(const char *pFileName);              // 初期化処理
		void Enqueue(void);                             // サウンドキューに波形データを追加する

	    bool m_bLoop;                   // ループフラグ
		bool m_bEnd;                    // 終端まで読み込んだ
	    unsigned long long m_nSoundSize;     // サウンドサイズ
		unsigned long long m_nLoopPoint;     // ループポイント
	    unsigned long long m_nPosition;      // 再生位置
	    WAVE_HEADER m_WavHeader;        // WAVEヘッダ
	    unsigned char *m_pBuff[2];    // バッファ
		unsigned char m_nAddBuffNo;
		char m_aFileName[256];          // サウンドファイル名
	    SLObjectItf m_OutputMixObject;   // 出力オブジェクト
	    SLObjectItf m_bqPlayerObject;    // プレイヤーオブジェクト
        SLPlayItf m_bqPlayerPlay;        // インターフェース
        SLAndroidSimpleBufferQueueItf m_bqPlayerBufferQueue;        // バッファキューインターフェース
        SLVolumeItf m_bqPlayerVolume;       // 音量インターフェース

		static bool m_bPause;               // ポーズフラグ
        static SLObjectItf m_EngineObject;  // エンジンオブジェクト
        static SLEngineItf m_EngineEngine;  // インターフェース
};

/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif