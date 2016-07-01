#include "AvCapture/AvManCapture.h"
#include "AvDevice/AvDevice.h"
#include "AvConfigs/AvConfigCapture.h"

SINGLETON_IMPLEMENT(CManCapture)
CManCapture::CManCapture()
{

}
CManCapture::~CManCapture()
{

}
av_bool CManCapture::Initialize()
{
	C_DspCaps DspCaps;
	CAvDevice::GetDspCaps(DspCaps);
	int i = 0;
	Capture *pCapture = NULL;
	for (; i < DspCaps.nMaxEncodeChannel; i++){
		pCapture = new CAvDevCapture;
		pCapture->Initialize((av_int)i);
		m_ManCaptureMap.insert(std::pair<av_int, Capture*>(i, pCapture));
	}

	for (; i < DspCaps.nMaxDecodeChannel; i++){
		pCapture = new CAvNetCapture;
		pCapture->Initialize((av_int)i);
		m_ManCaptureMap.insert(std::pair<av_int, Capture*>(i, pCapture));
	}

	return av_true;
}
Capture *CManCapture::GetAvCaptureInstance(av_int iChannel)
{
	return m_ManCaptureMap[iChannel];
}
