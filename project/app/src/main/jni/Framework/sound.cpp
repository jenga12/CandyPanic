/*
 *	File：sound.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：サウンド処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "sound.h"
#include "MainManager.h"
#include <string.h>
#include <stdio.h>

/******************************************************************************/
/*                               静的変数初期化                               */
/******************************************************************************/
SLObjectItf CSound :: m_EngineObject = NULL;
SLEngineItf CSound :: m_EngineEngine;
bool CSound :: m_bPause = false;


/******************************************************************************/
/*                                  定数定義                                  */
/******************************************************************************/


/******************************************************************************/
/*                                 構造体定義                                 */
/******************************************************************************/


/******************************************************************************/
/*                               グローバル変数                               */
/******************************************************************************/


/******************************************************************************/
/*                                サブルーチン                                */
/******************************************************************************/
void CallbackWAV(SLAndroidSimpleBufferQueueItf a, void *context){
	((CSound*)context)->Callback();
}


/******************************************************************************/
/*                                 クラス実装                                 */
/******************************************************************************/
//*************************************************
//			        CSound クラス
//*************************************************
/*
 *  コンストラクタ
 */
CSound :: CSound():
m_bLoop(false),
m_nPosition(0),
m_bEnd(false),
m_nLoopPoint(0),
m_nAddBuffNo(0){

}

/*
 * クラス名：CSound
 * 関数名：Initialize()
 * 内容：全体初期化
 */
void CSound :: Initialize(void){
    SLresult result;

    result = slCreateEngine(&m_EngineObject, 0, NULL, 0, NULL, NULL);
    result = (*m_EngineObject)->Realize(m_EngineObject, SL_BOOLEAN_FALSE);
    result = (*m_EngineObject)->GetInterface(m_EngineObject, SL_IID_ENGINE, &m_EngineEngine);
}

/*
 * クラス名：CSound
 * 関数名：Finalize()
 * 内容：全体終了
 */
void CSound :: Finalize(void){
    if(m_EngineObject){
        (*m_EngineObject)->Destroy(m_EngineObject);
        m_EngineObject = NULL;
    }
}

/*
 * クラス名：CSound
 * 関数名：Create()
 * 内容：インスタンス生成
 * 引数：pFileName             ;使用WAVファイル名
 */
CSound *CSound :: Create(const char *pFileName){
    CSound *p = new CSound();
    p->Init(pFileName);
    return p;
}

/*
 * クラス名：CSound
 * 関数名：Init()
 * 内容：初期化処理
 * 引数：pFileName             ;使用WAVファイル名
 */
void CSound :: Init(const char *pFileName){
    /*** WAVファイル読み込み ***/
    AAsset *fp = AAssetManager_open(CMainManager :: GetAssetManager(), pFileName, AASSET_MODE_UNKNOWN);
    size_t filesize = AAsset_getLength(fp);     // ファイルサイズを取得
    AAsset_read(fp, &m_WavHeader, sizeof(WAVE_HEADER));

    /*** OpenSLの準備 ***/
    SLresult result;
    result = (*m_EngineEngine)->CreateOutputMix(m_EngineEngine, &m_OutputMixObject, 0, NULL, NULL);
    result = (*m_OutputMixObject)->Realize(m_OutputMixObject, SL_BOOLEAN_FALSE);
    SLDataLocator_AndroidSimpleBufferQueue LocBQ = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    SLDataFormat_PCM FormatPCM;
    SLDataSource AudioSrc = {&LocBQ, &FormatPCM};

    /*** 音声ファイル情報の設定 ***/
    FormatPCM.formatType = SL_DATAFORMAT_PCM;
    FormatPCM.numChannels = (SLuint32)m_WavHeader.channel;
    FormatPCM.samplesPerSec = (SLuint32)m_WavHeader.rate*1000.0;
    FormatPCM.bitsPerSample = (SLuint32)m_WavHeader.bit;
    FormatPCM.containerSize = (SLuint32)m_WavHeader.bit;
    FormatPCM.channelMask = (m_WavHeader.channel == 1) ? SL_SPEAKER_FRONT_CENTER : SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
    FormatPCM.endianness = SL_BYTEORDER_LITTLEENDIAN;
	m_nSoundSize = filesize - sizeof(WAVE_HEADER);

    /*** ミキサー設定 ***/
    SLDataLocator_OutputMix LocOutMix = {SL_DATALOCATOR_OUTPUTMIX, m_OutputMixObject};
    SLDataSink AudioSnk = {&LocOutMix, NULL};

    /*** インターフェースを生成/取得 ***/
    const SLInterfaceID idx[3] = {SL_IID_PLAY, SL_IID_BUFFERQUEUE, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    result = (*m_EngineEngine)->CreateAudioPlayer(m_EngineEngine, &m_bqPlayerObject, &AudioSrc, &AudioSnk, 3, idx, req);
    (*m_bqPlayerObject)->Realize(m_bqPlayerObject, SL_BOOLEAN_FALSE);
    (*m_bqPlayerObject)->GetInterface(m_bqPlayerObject, SL_IID_PLAY, &m_bqPlayerPlay);
    (*m_bqPlayerObject)->GetInterface(m_bqPlayerObject, SL_IID_BUFFERQUEUE, &m_bqPlayerBufferQueue);
	(*m_bqPlayerObject)->GetInterface(m_bqPlayerObject, SL_IID_VOLUME, &m_bqPlayerVolume);

	/*** コールバック設定 ***/
	(*m_bqPlayerBufferQueue)->RegisterCallback(m_bqPlayerBufferQueue, CallbackWAV, this);

	/*** バッファの確保 ***/
	for(int i = 0; i < 2; ++i){
		m_pBuff[i] = new unsigned char[WAVE_BUFFER_SIZE];
	}

	strcpy(m_aFileName, pFileName);

	Enqueue();
	Enqueue();
}

/*
 * クラス名：CSound
 * 関数名：Release()
 * 内容：インスタンス破棄
 */
void CSound :: Release(void){
	(*m_bqPlayerPlay)->SetPlayState(m_bqPlayerPlay, SL_PLAYSTATE_STOPPED);
	(*m_bqPlayerBufferQueue)->Clear(m_bqPlayerBufferQueue);
    (*m_OutputMixObject)->Destroy(m_OutputMixObject);

	delete[] m_pBuff[1];
	delete[] m_pBuff[0];

    delete this;
}

/*
 * クラス名：CSound
 * 関数名：Enqueue()
 * 内容：サウンドキューに波形データを追加する
 */
void CSound :: Enqueue(void){
	AAsset *fp = AAssetManager_open(CMainManager :: GetAssetManager(), m_aFileName, AASSET_MODE_UNKNOWN);
	AAsset_seek(fp, m_nPosition + sizeof(WAVE_HEADER), SEEK_SET);
	int ReadSize = AAsset_read(fp, m_pBuff[m_nAddBuffNo], WAVE_BUFFER_SIZE);

	if(ReadSize <= 0){
		if(m_bLoop == true){
			m_nPosition = m_nLoopPoint;
			AAsset_seek(fp, m_nPosition + sizeof(WAVE_HEADER), SEEK_SET);
			ReadSize = AAsset_read(fp, m_pBuff[m_nAddBuffNo], WAVE_BUFFER_SIZE);

			(*m_bqPlayerBufferQueue)->Enqueue(m_bqPlayerBufferQueue, m_pBuff[m_nAddBuffNo], (SLuint32)ReadSize);
			m_nPosition += ReadSize;

			/*** 0の時1, 1の時0に ***/
			m_nAddBuffNo = 1 - m_nAddBuffNo;

		} else {
			m_bEnd = true;
		}
	} else {
		(*m_bqPlayerBufferQueue)->Enqueue(m_bqPlayerBufferQueue, m_pBuff[m_nAddBuffNo], (SLuint32)ReadSize);
		m_nPosition += ReadSize;

		/*** 0の時1, 1の時0に ***/
		m_nAddBuffNo = 1 - m_nAddBuffNo;
	}

	AAsset_close(fp);
}

/*
 * クラス名：CSound
 * 関数名：Play()
 * 内容：再生処理
 * 引数：bReset            ;ファイルの最初から再生するか
 *       bLoop             ;再生をループするか
 */
void CSound :: Play(bool bReset, bool bLoop){
	if(bReset){
		Seek(0);
	}

    m_bLoop = bLoop;
    (*m_bqPlayerPlay)->SetPlayState(m_bqPlayerPlay, SL_PLAYSTATE_PLAYING);
}

/*
 * クラス名：CSound
 * 関数名：Pause()
 * 内容：再生の中断
 */
void CSound :: Pause(void){
    (*m_bqPlayerPlay)->SetPlayState(m_bqPlayerPlay, SL_PLAYSTATE_PAUSED);
}

/*
 * クラス名：CSound
 * 関数名：Seek()
 * 内容：指定再生位置までシークする
 * 引数：time              ;シーク位置
 */
void CSound :: Seek(unsigned int time){
    m_nPosition = time;
	Pause();
	(*m_bqPlayerBufferQueue)->Clear(m_bqPlayerBufferQueue);
	Enqueue();
	Enqueue();
}

/*
 * クラス名：CSound
 * 関数名：Callback()
 * 内容：コールバック関数
 */
void CSound :: Callback(void){
	if(m_bEnd){
		Seek(0);
		m_bEnd = false;
		return;
	}

	Enqueue();
}