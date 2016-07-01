/*******************************************************************
|  Copyright(c) 2015-2016 Graceport Technology Development Co.,Ltd
|  All rights reserved.
|
|  版本: 1.0
|  作者: Knight [knight@graceport.cn]
|  日期: 2016年6月6日
|  说明:
|
|  版本: 1.1
|  作者:
|  日期:
|  说明:
******************************************************************/
#ifndef _AV_DEVCAPTURE_H_
#define _AV_DEVCAPTURE_H_
#include "AvCapture/AvCapture.h"
#include "AvConfigs/AvConfigCapture.h"

class CAvDevCapture:public Capture
{
public:
	CAvDevCapture();
	~CAvDevCapture();
public:
	av_bool Initialize(av_int Channel);
	av_bool Start(av_int Slave);
	av_bool Stop(av_int Slave);

	av_bool Start(av_int Slave, CAvObject *obj, SIG_PROC_ONDATA pOnData);
	av_bool Stop(av_int Slave, CAvObject *obj, SIG_PROC_ONDATA pOnData);

	av_bool SetProfile(av_int Slave, C_EncodeFormats &Formats);
	av_bool GetProfile(av_int Slave, C_EncodeFormats &Fromats);
	av_bool GetCaps(C_EncodeCaps &Caps);

	av_bool SetTime(av_timeval &atv);
	av_bool SetIFrame(av_int Slave = CHL_MAIN_T);


private:
	av_int m_Channel;
	E_CaptureSynchronizeStat m_LastCaptureSyncStat;

public:
	av_bool CaptureCreate();
	av_bool CaptureDestroy();

	av_bool CaptureStart(av_uchar Slave);
	av_bool CaptureStop(av_uchar Slave);
public:
	av_bool LoadConfigs();


private:
	TSignal3<av_int, av_int, CAvPacket *> m_StreamSignal[CHL_NR_T];
private:
	void ThreadProc();

	
private:
	av_void OnConfigEncodeModify(CAvConfigEncode *ConfigEncode, int &result);
	av_void OnConfigImageModify(CAvConfigImage *ConfigImage, int &result);
	av_void OnConfigCoverModify(CAvConfigCover *ConfigCover, int &result);
	av_void OnConfigWaterMarkingModify(CAvConfigWaterMarking *ConfigWaterMarking, int &result);
	av_void OnConfigCaptureModify(CAvConfigCapture *ConfigCapture, int &result);
	av_void OnTest(void *args, int &result);
private:
	CAvConfigEncode			m_ConfigEncode;
	CAvConfigImage			m_ConfigImage;
	CAvConfigCover			m_ConfigCover;
	CAvConfigWaterMarking	m_ConfigWaterMark;
	CAvConfigCapture		m_ConfigCapture;

};









#endif


