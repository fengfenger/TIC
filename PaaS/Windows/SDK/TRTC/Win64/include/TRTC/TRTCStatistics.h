/*
* Module:   TRTC ͳ����Ϣ����
*
* Function: ͨ��������صĶ���
*
*/

#ifndef __TRTCSTATISTICS_H__
#define __TRTCSTATISTICS_H__

#include "TRTCCloudDef.h"

#include <stdint.h>

/// @defgroup TRTCCloudDef_cplusplus �ؼ����Ͷ���
/// @{

 /**
 * �Լ����ص�����Ƶͳ����Ϣ
 */
struct TRTCLocalStatistics
{
    uint32_t width;                                 ///< ��Ƶ���

    uint32_t height;                                ///< ��Ƶ�߶�

    uint32_t frameRate;                             ///< ֡�ʣ�fps��

    uint32_t videoBitrate;                          ///< ��Ƶ�������ʣ�Kbps��

    uint32_t audioSampleRate;                       ///< ��Ƶ�����ʣ�Hz��

    uint32_t audioBitrate;                          ///< ��Ƶ�������ʣ�Kbps��

    TRTCVideoStreamType streamType;                 ///< �����ͣ����� | С���� | ��·���棩
};

/**
* Զ�˳�Ա������Ƶͳ����Ϣ
*/
struct TRTCRemoteStatistics
{
    const char* userId;                                ///< �û� ID��ָ�����ĸ��û�����Ƶ��

    /** ����·���ܶ����ʣ�����
     *
     * ���ֵԽСԽ�ã����磬������Ϊ0��ʾ����ܺá�
     * �������Ǹ���·�� userId �����е��������ٵ����е��ܶ����ʡ�
     * ��� downLoss Ϊ0������ finalLoss ��Ϊ0��˵���� userId ����ʱ�������޷��ָ��Ķ�����
     */
    uint32_t finalLoss;                            

    uint32_t width;                                 ///< ��Ƶ���

    uint32_t height;                                ///< ��Ƶ�߶�

    uint32_t frameRate;                             ///< ����֡�ʣ�fps��

    uint32_t videoBitrate;                          ///< ��Ƶ���ʣ�Kbps��

    uint32_t audioSampleRate;                       ///< ��Ƶ�����ʣ�Hz��

    uint32_t audioBitrate;                          ///< ��Ƶ���ʣ�Kbps��

    TRTCVideoStreamType streamType;                 ///< �����ͣ����� | С���� | ��·���棩
};

/**
* ͳ������
*/
struct TRTCStatistics
{

    /** C -> S ���ж����ʣ�������
     * ��ֵԽСԽ�ã����磬������Ϊ0��ʾ����ܺã�
     * ������Ϊ30@%����ζ�� SDK ����������͵����ݰ��л���30@%��ʧ�����д����С�
     */
    uint32_t upLoss;         

    /** S -> C ���ж����ʣ�������
     * ��ֵԽСԽ�ã����磬������Ϊ0��ʾ����ܺã�
     * ������Ϊ30@%����ζ�� SDK ����������͵����ݰ��л���30@%��ʧ�����д����С�
     */
    uint32_t downLoss;                              

    ///��ǰ App �� CPU ʹ���ʣ�����
    uint32_t appCpu;

    /// ��ǰϵͳ�� CPU ʹ���ʣ�����
    uint32_t systemCpu;

    /// �ӳ٣����룩��
    /// ָ SDK ����Ѷ�Ʒ�������һ����������ʱ�䣬��ֵԽСԽ�á�
    /// һ�����50ms�� rtt ������룬������100ms�� rtt ������ϴ��ͨ����ʱ��
    /// �������������й���һ���������ӣ����� local �� remote �� rtt ��ͬ��
    uint32_t rtt;         

    /// �ܽ����ֽ������������������Ƶ��
    uint32_t receivedBytes;                  

    /// �ܷ����ֽ��������������������Ƶ��
    uint32_t sentBytes; 

    /// ���ص�����Ƶͳ����Ϣ�������������桢С�����Լ���·����ȶ�·������������һ������
    TRTCLocalStatistics* localStatisticsArray;     

    /// ���� localStatisticsArray �Ĵ�С
    uint32_t localStatisticsArraySize;              

    /// Զ�˳�Ա������Ƶͳ����Ϣ�������������桢С�����Լ���·����ȶ�·������������һ������
    TRTCRemoteStatistics* remoteStatisticsArray;    

    /// ���� remoteStatisticsArray �Ĵ�С
    uint32_t remoteStatisticsArraySize;             
};
/// @}

#endif /* __TRTCSTATISTICS_H__ */
