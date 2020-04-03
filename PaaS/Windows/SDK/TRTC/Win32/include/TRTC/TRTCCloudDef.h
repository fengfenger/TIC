/*
 * Module:   TRTC �ؼ����Ͷ���
 *
 * Function: �ֱ��ʡ������ȼ���ö�ٺͳ���ֵ�Ķ���
 *
 */

#ifndef __TRTCCLOUDDEF_H__
#define __TRTCCLOUDDEF_H__

#include "TXLiteAVBase.h"
#include <memory>

#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif // !_WINSOCKAPI_

#include <Windows.h>

/// @defgroup TRTCCloudDef_cplusplus �ؼ����Ͷ���
/// ��Ѷ����Ƶͨ�����ܵĹؼ����Ͷ���
/// @{
/////////////////////////////////////////////////////////////////////////////////
//
//                    ����һ����Ƶ���ö��ֵ���塿
//
/////////////////////////////////////////////////////////////////////////////////


/**
 * 1.1 ��Ƶ�ֱ���
 *
 * �˴�����������ֱ��ʣ�����ʹ�������ֱ��ʣ�����360 �� 640������Ҫͬʱָ�� TRTCVideoResolutionMode Ϊ Portrait��
 */
enum TRTCVideoResolution
{
    // ��߱�1:1
    TRTCVideoResolution_120_120   = 1,     ///< [C] ��������80kbps
    TRTCVideoResolution_160_160   = 3,     ///< [C] ��������100kbps
    TRTCVideoResolution_270_270   = 5,     ///< [C] ��������200kbps
    TRTCVideoResolution_480_480   = 7,     ///< [C] ��������350kbps

    // ��߱�4:3
    TRTCVideoResolution_160_120   = 50,    ///< [C] ��������100kbps
    TRTCVideoResolution_240_180   = 52,    ///< [C] ��������150kbps
    TRTCVideoResolution_280_210   = 54,    ///< [C] ��������200kbps
    TRTCVideoResolution_320_240   = 56,    ///< [C] ��������250kbps
    TRTCVideoResolution_400_300   = 58,    ///< [C] ��������300kbps
    TRTCVideoResolution_480_360   = 60,    ///< [C] ��������400kbps
    TRTCVideoResolution_640_480   = 62,    ///< [C] ��������600kbps
    TRTCVideoResolution_960_720   = 64,    ///< [C] ��������1000kbps

    // ��߱�16:9
    TRTCVideoResolution_160_90    = 100,   ///< [C] ��������150kbps
    TRTCVideoResolution_256_144   = 102,   ///< [C] ��������200kbps
    TRTCVideoResolution_320_180   = 104,   ///< [C] ��������250kbps
    TRTCVideoResolution_480_270   = 106,   ///< [C] ��������350kbps
    TRTCVideoResolution_640_360   = 108,   ///< [C] ��������550kbps
    TRTCVideoResolution_960_540   = 110,   ///< [C] ��������850kbps
    TRTCVideoResolution_1280_720  = 112,   ///< [C] ����ͷ�ɼ� - ��������1200kbps
                                           ///< [S] ��Ļ����   - �������ʣ����壺1000kbps ���壺1600kbps
    TRTCVideoResolution_1920_1080 = 114,   ///< [S] ��Ļ����   - ��������2000kbps
};

/**
 * 1.2 ��Ƶ�ֱ���ģʽ
 *
 * - �����ֱ��ʣ�TRTCVideoResolution_640_360 + TRTCVideoResolutionModeLandscape = 640 �� 360
 * - �����ֱ��ʣ�TRTCVideoResolution_640_360 + TRTCVideoResolutionModePortrait  = 360 �� 640
 */
enum TRTCVideoResolutionMode
{
    TRTCVideoResolutionModeLandscape = 0,               ///< �����ֱ���
    TRTCVideoResolutionModePortrait = 1,                ///< �����ֱ���
};

/**
 * 1.3 ��Ƶ������
 *
 * TRTC �ڲ������ֲ�ͬ������Ƶ�����ֱ�Ϊ��
 * - �����棺��õ�һ����·��һ��������������ͷ����Ƶ���ݡ�
 * - С���棺���������������ͬ�����Ƿֱ��ʺ����ʸ��͡�
 * - �������棺һ��������Ļ�����Զ�̲�Ƭ��������ʦ������Ƶ��ѧ���ۿ�����
 *
 * @note - ���������������������ܱȽϺã������ͬʱ�ͳ���С��·���档
 * @note - SDK ��֧�ֵ�������С���棬С�����������������������ڡ�
 */
enum TRTCVideoStreamType
{
    TRTCVideoStreamTypeBig = 0,                         ///< ��������Ƶ��
    TRTCVideoStreamTypeSmall = 1,                       ///< С������Ƶ��
    TRTCVideoStreamTypeSub = 2,                         ///< ��������Ļ����
};


/**
 * 1.4 ���ʼ���
 *
 * TRTC SDK �Ի��ʶ��������ֲ�ͬ�ļ���Excellent ��ʾ��ã�Down ��ʾ�����á�
 */
enum TRTCQuality
{
    TRTCQuality_Unknown   = 0,   ///< δ����
    TRTCQuality_Excellent = 1,   ///< ���
    TRTCQuality_Good      = 2,   ///< ��
    TRTCQuality_Poor      = 3,   ///< һ��
    TRTCQuality_Bad       = 4,   ///< ��
    TRTCQuality_Vbad      = 5,   ///< �ܲ�
    TRTCQuality_Down      = 6,   ///< ������
};

/**
 * 1.5 ��Ƶ�������ģʽ
 *
 * ����������ʾ�ֱ��ʲ����ڻ����ԭʼ�ֱ��ʣ�����Ҫ�����û�������ģʽ:
 * - TRTCVideoFillMode_Fill��ͼ��������Ļ��������ʾ�Ӵ�����Ƶ���ֽ����ü���������ʾ���ܲ�������
 * - TRTCVideoFillMode_Fit��ͼ�񳤱�������Ļ���̱�����ᱻ����ɫ������������ݿ϶��������ġ�
 */
enum TRTCVideoFillMode
{
    /// ͼ��������Ļ��������ʾ�Ӵ�����Ƶ���ֽ����ü�
    TRTCVideoFillMode_Fill = 0,
    /// ͼ�񳤱�������Ļ���̱�����ᱻ����ɫ
    TRTCVideoFillMode_Fit = 1,
};

/**
 * 1.6 ��Ƶ������ת����
 *
 * TRTC SDK �ṩ�˶Ա��غ�Զ�̻������ת�Ƕ����� API�����е���ת�Ƕȶ���ָ˳ʱ�뷽��ġ�
 *
 * �ö�������ڼ���ԭ�нӿڣ����嶨��μ� TXLiteAVBase.h �ļ�
 */
typedef LiteAVVideoRotation TRTCVideoRotation;
#define TRTCVideoRotation0 LiteAVVideoRotation0                                 ///< ˳ʱ����ת0��
#define TRTCVideoRotation90 LiteAVVideoRotation90                               ///< ˳ʱ����ת90��
#define TRTCVideoRotation180 LiteAVVideoRotation180                             ///< ˳ʱ����ת180��
#define TRTCVideoRotation270 LiteAVVideoRotation270                             ///< ˳ʱ����ת270��

/**
 * 1.7 ���գ�ĥƤ���㷨
 *
 * TRTC SDK ���ö��ֲ�ͬ��ĥƤ�㷨��������ѡ�����ʺ�����Ʒ��λ�ķ�����
 */
enum TRTCBeautyStyle
{
    TRTCBeautyStyleSmooth = 0,                         ///< �⻬����������Ů�㳡��Ч���Ƚ����ԡ�
    TRTCBeautyStyleNature = 1,                         ///< ��Ȼ��ĥƤ�㷨����ر������沿ϸ�ڣ����۸����ϻ������Ȼ��
};

/**
 * 1.8 ��Ƶ���ظ�ʽ
 *
 * TRTC SDK �ṩ�����Ƶ���Զ���ɼ����Զ�����Ⱦ���ܣ����Զ���ɼ������У�������������ö��ֵ�������ɼ�����Ƶ���ظ�ʽ��
 * ���Զ�����Ⱦ�����У�������ָ�������� SDK �ص�����Ƶ���ظ�ʽ��
 *
 * �ö�������ڼ���ԭ�нӿڣ����嶨��μ� TXLiteAVBase.h �ļ�
 */
typedef LiteAVVideoPixelFormat TRTCVideoPixelFormat;
#define TRTCVideoPixelFormat_Unknown LiteAVVideoPixelFormat_Unknown
#define TRTCVideoPixelFormat_I420 LiteAVVideoPixelFormat_I420                   ///< I420
#define TRTCVideoPixelFormat_Texture_2D LiteAVVideoPixelFormat_Texture_2D       ///< OpenGL 2D ����
#define TRTCVideoPixelFormat_BGRA32 LiteAVVideoPixelFormat_BGRA32               ///< BGRA32


/**
 * 1.9 ��Ƶ���ݰ�װ��ʽ
 *
 * �ö�������ڼ���ԭ�нӿڣ����嶨��μ� TXLiteAVBase.h �ļ�
 */
typedef LiteAVVideoBufferType TRTCVideoBufferType;
#define TRTCVideoBufferType_Unknown LiteAVVideoBufferType_Unknown
#define TRTCVideoBufferType_Buffer LiteAVVideoBufferType_Buffer                 ///< ������ Buffer ����
#define TRTCVideoBufferType_Texture LiteAVVideoBufferType_Texture               ///< ��������


/////////////////////////////////////////////////////////////////////////////////
//
//                    ���������������ö��ֵ���塿
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 2.1 Ӧ�ó���
 *
 * TRTC ��������Ƶ���������ֱ���ȶ���Ӧ�ó�������Բ�ͬ��Ӧ�ó�����TRTC SDK ���ڲ�����в�ͬ���Ż����ã�
 * - TRTCAppSceneVideoCall    ����Ƶͨ���������ʺ�[1��1��Ƶͨ��]��[300����Ƶ����]��[��������]��[��Ƶ����]��[Զ������]�ȡ�              
 * - TRTCAppSceneLIVE         ����Ƶ����ֱ�����ʺ�[��Ƶ����ʱֱ��]��[ʮ���˻�������]��[��Ƶֱ�� PK]��[��Ƶ���׷�]��[��������]��[Զ����ѵ]��[�����ͻ���]�ȡ�
 * - TRTCAppSceneAudioCall    ������ͨ���������ʺ�[1��1����ͨ��]��[300����������]��[��������]��[��������]��[��������ɱ]�ȡ�
 * - TRTCAppSceneVoiceChatRoom����������ֱ�����ʺϣ�[��������ʱֱ��]��[����ֱ������]��[���ķ�]��[K �跿]��[FM ��̨]�ȡ�
 */
enum TRTCAppScene
{
	/// ��Ƶͨ��������֧��720P��1080P���廭�ʣ������������֧��300��ͬʱ���ߣ����֧��50��ͬʱ���ԡ�<br>
	/// �ʺϣ�[1��1��Ƶͨ��]��[300����Ƶ����]��[��������]��[��Ƶ����]��[Զ������]�ȡ�
    TRTCAppSceneVideoCall     = 0,  
	
	/// ��Ƶ����ֱ����֧��ƽ���������л���������ȴ���������ʱС��300ms��֧��ʮ�򼶱����ͬʱ���ţ�������ʱ����1000ms��<br>
	/// �ʺϣ�[��Ƶ����ʱֱ��]��[ʮ���˻�������]��[��Ƶֱ�� PK]��[��Ƶ���׷�]��[��������]��[Զ����ѵ]��[�����ͻ���]�ȡ�<br>
	/// ע�⣺�˳����£�������ͨ�� TRTCParams �е� role �ֶ�ָ����ǰ�û��Ľ�ɫ��
    TRTCAppSceneLIVE          = 1,  
	
	/// ����ͨ��������֧�� 48kHz��֧��˫�����������������֧��300��ͬʱ���ߣ����֧��50��ͬʱ���ԡ�<br>
	/// �ʺϣ�[1��1����ͨ��]��[300����������]��[��������]��[��������]��[��������ɱ]�ȡ�
    TRTCAppSceneAudioCall     = 2,  
	
	/// ��������ֱ����֧��ƽ���������л���������ȴ���������ʱС��300ms��֧��ʮ�򼶱����ͬʱ���ţ�������ʱ����1000ms��<br>
    /// �ʺϣ�[��������ʱֱ��]��[����ֱ������]��[���ķ�]��[K �跿]��[FM ��̨]�ȡ�<br>
	/// ע�⣺�˳����£�������ͨ�� TRTCParams �е� role �ֶ�ָ����ǰ�û��Ľ�ɫ��
    TRTCAppSceneVoiceChatRoom = 3,  
};

/**
* 2.2 ��ɫ����������ֱ��������TRTCAppSceneLIVE �� TRTCAppSceneVoiceChatRoom��
*
* ��ֱ�������У������û���Ϊ���ڣ������û������������ֽ�ɫ���������� TRTC ���и��õĶ����Ż���
*
* - Anchor������������������Ƶ����Ƶ��һ�����������֧��50������ͬʱ��������Ƶ��
* - Audience�����ڣ�ֻ�ܹۿ�������������Ƶ����Ƶ��һ��������Ĺ�������û�����ޡ�
*/
enum TRTCRoleType
{
    TRTCRoleAnchor = 20,     ///< ����
    TRTCRoleAudience = 21,   ///< ����
};

/**
 * 2.3 ����ģʽ
 *
 * TRTC SDK �ڲ���Ҫʱ�̸���������������ڲ��ı������������ģ�飬�Ա��ܹ�������ı仯������Ӧ��
 * Ϊ��֧�ֿ����㷨������SDK �ڲ����������ֲ�ͬ������ģʽ��
 * - ModeServer���ƶ˿��ƣ�Ĭ��ģʽ���Ƽ�ѡ��
 * - ModeClient�����ؿ��ƣ����� SDK �����ڲ����ԣ��ͻ�����ʹ�á�
 *
 * @note �Ƽ���ʹ���ƶ˿��ƣ�����ÿ���������� Qos �㷨ʱ������������ SDK ����������õ�Ч����
 */
enum TRTCQosControlMode
{
    TRTCQosControlModeClient,                           ///< �ͻ��˿��ƣ����� SDK �����ڲ����ԣ��ͻ�����ʹ�ã�
    TRTCQosControlModeServer,                           ///< �ƶ˿��� ��Ĭ�ϣ�
};

/**
 * 2.4 ����ƫ��
 *
 * ָ�� TRTC SDK �����������绷��ʱ�������������������򡰱���������
 *
 * - Smooth�������±�����������������������ʱ����ȷ�����������������ȷ��ͣ��������ģ���һ��н϶������ˣ������Ա������������١�
 * - Clear�������±�����������������������ʱ������ᾡ���ܱ��������������ܻ�����׳��ֿ��١�
 */
enum TRTCVideoQosPreference
{
    TRTCVideoQosPreferenceSmooth = 1,                   ///< �����±�����
    TRTCVideoQosPreferenceClear = 2,                    ///< �����±�����
};


/////////////////////////////////////////////////////////////////////////////////
//
//                    ���������̳� TXLiteAVBase �Ķ��塿
//
/////////////////////////////////////////////////////////////////////////////////


/**
* 3.1 ��Ƶ֡�ĸ�ʽ
*
* �ö�������ڼ���ԭ�нӿڣ����嶨��μ� TXLiteAVBase.h �ļ�
*/
typedef LiteAVAudioFrameFormat TRTCAudioFrameFormat;
#define TRTCAudioFrameFormatNone LiteAVAudioFrameFormatNone
#define TRTCAudioFrameFormatPCM LiteAVAudioFrameFormatPCM

/**
 * 3.2 ��Ļ����Ŀ����Ϣ
 *
 * �ö�������ڼ���ԭ�нӿڣ����嶨��μ� TXLiteAVBase.h �ļ�
 */
typedef LiteAVScreenCaptureSourceType TRTCScreenCaptureSourceType;
#define TRTCScreenCaptureSourceTypeUnknown LiteAVScreenCaptureSourceTypeUnknown
#define TRTCScreenCaptureSourceTypeWindow  LiteAVScreenCaptureSourceTypeWindow
#define TRTCScreenCaptureSourceTypeScreen  LiteAVScreenCaptureSourceTypeScreen
#define TRTCScreenCaptureSourceTypeCustom  LiteAVScreenCaptureSourceTypeCustom

typedef LiteAVImageBuffer TRTCImageBuffer;
typedef LiteAVScreenCaptureSourceInfo TRTCScreenCaptureSourceInfo;
typedef ILiteAVScreenCaptureSourceList ITRTCScreenCaptureSourceList;


/**
 * 3.3 �豸�б�
 *
 * �ö�������ڼ���ԭ�нӿڣ����嶨��μ� TXLiteAVBase.h �ļ�
 */
typedef ILiteAVDeviceCollection ITRTCDeviceCollection;

/**
* 3.4 �豸 Item ��Ϣ
*
* �ö�������ڼ���ԭ�нӿڣ����嶨��μ� TXLiteAVBase.h �ļ�
*/
typedef ILiteAVDeviceInfo ITRTCDeviceInfo;

/////////////////////////////////////////////////////////////////////////////////
//
//                    �����ģ�����ö��ֵ���塿
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 4.1 Log ����
 */
enum TRTCLogLevel
{
    TRTCLogLevelVerbose   = 0,   ///< ������м���� Log
    TRTCLogLevelDebug     = 1,   ///< ��� DEBUG��INFO��WARNING��ERROR �� FATAL ����� Log
    TRTCLogLevelInfo      = 2,   ///< ��� INFO��WARNING��ERROR �� FATAL ����� Log
    TRTCLogLevelWarn      = 3,   ///< ֻ���WARNING��ERROR �� FATAL ����� Log
    TRTCLogLevelError     = 4,   ///< ֻ���ERROR �� FATAL ����� Log
    TRTCLogLevelFatal     = 5,   ///< ֻ��� FATAL ����� Log
    TRTCLogLevelNone      = 6,   ///< ������κ� SDK Log
};

/**
 * 4.2 �豸����
 */
enum TRTCDeviceState
{
    TRTCDeviceStateAdd    = 0,                          ///< ����豸
    TRTCDeviceStateRemove = 1,                          ///< �Ƴ��豸
    TRTCDeviceStateActive = 2,                          ///< �豸������
};


/**
 * 4.3 �豸����
 */
enum TRTCDeviceType
{
    TRTCDeviceTypeUnknow  = -1,
    TRTCDeviceTypeMic     = 0,                          ///< ��˷�
    TRTCDeviceTypeSpeaker = 1,                          ///< ������
    TRTCDeviceTypeCamera  = 2,                          ///< ����ͷ
};


/**
 * 4.4 ˮӡͼƬ��Դ����
 */
enum TRTCWaterMarkSrcType
{
    TRTCWaterMarkSrcTypeFile   = 0,                     ///< ͼƬ�ļ�·����֧�� BMP��GIF��JPEG��PNG��TIFF��Exif��WMF �� EMF �ļ���ʽ
    TRTCWaterMarkSrcTypeBGRA32 = 1,                     ///< BGRA32��ʽ�ڴ��
    TRTCWaterMarkSrcTypeRGBA32 = 2,                     ///< RGBA32��ʽ�ڴ��
};


/////////////////////////////////////////////////////////////////////////////////
//
//                      �����壩TRTC �������Ͷ��塿
//
/////////////////////////////////////////////////////////////////////////////////

/**
* 5.1 ������ز���
*
* ֻ�иò�����д��ȷ������˳������ enterRoom ���� roomId ��ָ��������Ƶ���䡣
*/
struct TRTCParams
{

    ///���ֶκ��塿Ӧ�ñ�ʶ���������Ѷ��Ƶ�ƻ��� sdkAppId ��ɼƷ�ͳ�ơ�
    ///���Ƽ�ȡֵ���� [ʵʱ����Ƶ����̨](https://console.cloud.tencent.com/rav/) ����Ӧ�ú�����ʺ���Ϣҳ���еõ��� ID��
    uint32_t sdkAppId;

    ///���ֶκ��塿�û���ʶ���������ǰ�û��� userId���൱���û�����ʹ�� UTF-8 ���롣
    ///���Ƽ�ȡֵ�����һ���û��������ʺ�ϵͳ�е� ID Ϊ��abc������ userId ��������Ϊ��abc����
    const char* userId;

    ///���ֶκ��塿�û�ǩ�����������ǰ userId ��Ӧ����֤ǩ�����൱�ڵ�¼���롣
    ///���Ƽ�ȡֵ��������㷽����μ� [��μ���UserSig](https://cloud.tencent.com/document/product/647/17275)��
    const char* userSig;

    ///���ֶκ��塿������루�������ͬһ�������ڵ��û����Կ����˴˲�������Ƶͨ����
    ///���Ƽ�ȡֵ���������Զ������øò���ֵ���������ظ�����������û��ʺ� ID ��userId��Ϊ�������ͣ���ֱ��ʹ�ô����ߵ��û� ID ��Ϊ roomId��
    uint32_t roomId;

    ///���ֶκ��塿ֱ�������µĽ�ɫ����������ֱ��������TRTCAppSceneLIVE �� TRTCAppSceneVoiceChatRoom������Ƶͨ��������ָ����Ч��
    ///���Ƽ�ȡֵ��Ĭ��ֵ��������TRTCRoleAnchor��
    TRTCRoleType role;

    ///���ֶκ��塿����Ѷ��ֱ�� CDN �� ID[�Ǳ���]������֮�����Ϳ�������Ѷ��ֱ�� CDN ��ͨ����׼ֱ��������FLV��HLS�����Ÿ��û�������Ƶ����
    ///���Ƽ�ȡֵ�����Ƴ���Ϊ64�ֽڣ����Բ���д��һ���Ƽ��ķ�����ʹ�� ��sdkappid_roomid_userid_main�� ��Ϊ streamid�������ȽϺñ����Ҳ��������Ķ��Ӧ���з�����ͻ��
	///������˵����Ҫʹ����Ѷ��ֱ�� CDN������Ҫ����[����̨](https://console.cloud.tencent.com/trtc/) �еĹ�������ҳ�����������Զ���·ֱ�������ء�
	///���ο��ĵ���[CDN ��·ֱ��](https://cloud.tencent.com/document/product/647/16826)��
    const char* streamId;

    ///���ֶκ��塿�����ƶ�¼����ɺ�Ļص���Ϣ�е� "userdefinerecordid"  �ֶ����ݣ��������������ʶ��¼�ƻص���        
    ///���Ƽ�ȡֵ�����Ƴ���Ϊ64�ֽڣ�ֻ���������СдӢ����ĸ��a-zA-Z�������֣�0-9�����»��ߺ����ʷ���
    ///���ο��ĵ���[�ƶ�¼��](https://cloud.tencent.com/document/product/647/16823)��
    const char* userDefineRecordId;

    ///���ֶκ��塿����ǩ�����Ǳ��������ϣ��ĳ������ֻ�����ض��� userId ����ʱ����Ҫʹ�� privateMapKey ����Ȩ�ޱ�����
    ///���Ƽ�ȡֵ���������и߼���ȫ����Ŀͻ�ʹ�ã�����������μ� [����Ȩ�ޱ���](https://cloud.tencent.com/document/product/647/32240)��
    const char* privateMapKey;

    ///���ֶκ��塿ҵ�����ݣ��Ǳ�������ָ߼����Բ���Ҫʹ�ø��ֶΡ�
    ///���Ƽ�ȡֵ��������ʹ��
    const char* businessInfo;


    TRTCParams()
        : sdkAppId(0)
        , roomId(0)
        , userId(NULL)
        , userSig(NULL)
        , role(TRTCRoleAnchor)
        , privateMapKey(NULL)
        , businessInfo(NULL)
        , userDefineRecordId(NULL)
        , streamId(NULL)
    {

    }
};

/**
* 5.2 ��Ƶ�������
*
* �����þ�����Զ���û������Ļ���������ͬʱҲ���ƶ�¼�Ƴ�����Ƶ�ļ��Ļ�����������
*/
struct TRTCVideoEncParam
{
    ///���ֶκ��塿 ��Ƶ�ֱ���
    ///���Ƽ�ȡֵ�� 
	///    - ��Ƶͨ������ѡ��360 �� 640�����·ֱ��ʣ�resMode ѡ�� Portrait��
    ///    - �ֻ�ֱ������ѡ��540 �� 960��resMode ѡ�� Portrait��
    ///    - Window �� iMac ����ѡ��640 �� 360�����Ϸֱ��ʣ�resMode ѡ�� Landscape��
    ///���ر�˵���� 
	///    TRTCVideoResolution Ĭ��ֻ�ܺ���ģʽ�ķֱ��ʣ�����640 �� 360��
    ///    ����ʹ�������ֱ��ʣ���ָ�� resMode Ϊ Portrait������640 �� 360��� Portrait ��Ϊ360 �� 640��
    TRTCVideoResolution videoResolution;

    ///���ֶκ��塿�ֱ���ģʽ�������ֱ��� - �����ֱ��ʣ�
    ///���Ƽ�ȡֵ���ֻ�ֱ������ѡ�� Portrait��Window �� Mac ����ѡ�� Landscape��
    ///���ر�˵������� videoResolution ָ���ֱ��� 640 �� 360��resMode ָ��ģʽΪ Portrait�������ձ�����ķֱ���Ϊ360 �� 640��
    TRTCVideoResolutionMode resMode;

    ///���ֶκ��塿��Ƶ�ɼ�֡��
    ///���Ƽ�ȡֵ��15fps �� 20fps��5fps���£����ٸ����ԡ�10fps���£�������΢���ٸС�20fps���ϣ�������˷ѣ���Ӱ��֡��Ϊ24fps����
    ///���ر�˵�����ܶ� Android �ֻ���ǰ������ͷ����֧��15fps���ϵĲɼ�֡�ʣ����ֹ���ͻ�����չ��ܵ� Android �ֻ�ǰ������ͷ�Ĳɼ�֡�ʿ��ܵ���10fps��
    uint32_t videoFps;

    ///���ֶκ��塿��Ƶ��������
    ///���Ƽ�ȡֵ���Ƽ�������ο����ļ�ǰ�벿�� TRTCVideoResolution ���崦��ע��˵��
    ///���ر�˵��������̫�ͻᵼ����Ƶ�г��ִ���������
    uint32_t videoBitrate;

    ///���ֶκ��塿�Ƿ���������ֱ���
    ///���Ƽ�ȡֵ�� 
	///     - �ֻ�ֱ������ѡ�� false��
    ///     - ��Ƶͨ��ģʽ��������ע�����ԣ�����ѡ�� true����ʱ�������������޵�������SDK ���Զ����ͷֱ����Ա��ϸ��õ������ȣ������ TRTCVideoStreamTypeBig ��Ч����
    ///     - Ĭ��ֵ��false��
    ///���ر�˵��������¼������ѡ�� true ʱ����ȷ��ͨ�������У������ֱ��ʲ���Ӱ������¼��Ч����
    bool enableAdjustRes;

    TRTCVideoEncParam()
        : videoResolution(TRTCVideoResolution_640_360)
        , resMode(TRTCVideoResolutionModeLandscape)
        , videoFps(15)
        , videoBitrate(550)
        , enableAdjustRes(false)
    {

    }
};

/**
* 5.3 ����������ز���
*
* ����������ز����������þ�����SDK�ڸ������绷���µĵ��ط��򣨱����������ǡ����������򡰱���������
*/
struct TRTCNetworkQosParam
{
    ///���ֶκ��塿�������ǡ����������򡰱�������
    ///���ر�˵����
    ///   - �����±���������������������ʱ���������ģ�����ҳ��ֽ϶������ˣ������Ա������������١�
    ///   - �����±���������������������ʱ������ᾡ���ܱ������������������׳��ֿ���
    TRTCVideoQosPreference preference;

    ///���ֶκ��塿��Ƶ�ֱ��ʣ��ƶ˿��� - �ͻ��˿��ƣ�
    ///���Ƽ�ȡֵ���ƶ˿���
    ///���ر�˵����
    ///   - Server ģʽ��Ĭ�ϣ����ƶ˿���ģʽ����������ԭ����ֱ��ʹ�ø�ģʽ
    ///   - Client ģʽ���ͻ��˿���ģʽ������ SDK �����ڲ����ԣ��ͻ�����ʹ��
    TRTCQosControlMode controlMode;

    TRTCNetworkQosParam()
        : preference(TRTCVideoQosPreferenceClear)
        , controlMode(TRTCQosControlModeServer)
    {

    }
};

/**
 * 5.4 ��Ƶ����
 *
 * ��ʾ��Ƶ�����ĺû���ͨ�������ֵ���������� UI ��������ͼ����� userId ��ͨ����·����
 */
struct TRTCQualityInfo
{
    const char* userId;                     ///< �û���ʶ
    TRTCQuality quality;                    ///< ��Ƶ����

    TRTCQualityInfo()
        : userId(NULL)
        , quality(TRTCQuality_Unknown)
    {

    }
};

/**
 * 5.5 ������С
 *
 * ��ʾ����������������С��ͨ�������ֵ���������� UI ��������ͼ����� userId �Ƿ�����˵����
 */
struct TRTCVolumeInfo
{
    /// ˵���ߵ� userId���ַ������ʽΪ UTF-8
    const char* userId;
    /// ˵���ߵ������� ȡֵ��Χ0 - 100
    uint32_t volume;

    TRTCVolumeInfo()
        : userId(NULL)
        , volume(0)
    {

    }
};


/**
 * 5.6 ��Ƶ֡����
 *
 * �ö�������ڼ���ԭ�нӿڣ����嶨��μ� TXLiteAVBase.h �ļ�
 */
typedef LiteAVVideoFrame TRTCVideoFrame;

/**
 * 5.7 ��Ƶ֡����
 *
 * �ö�������ڼ���ԭ�нӿڣ����嶨��μ� TXLiteAVBase.h �ļ�
 */
typedef LiteAVAudioFrame TRTCAudioFrame;


/**
 * 5.8 ������ٽ��
 *
 * ���������û����뷿��ǰͨ�� TRTCCloud �� startSpeedTest �ӿڽ��в��� ��ע�⣺�벻Ҫ��ͨ���е��ã���
 * ���ٽ����ÿ2 - 3���ӷ���һ�Σ�ÿ�η���һ�� IP ��ַ�Ĳ��Խ����
 *
 * @note - quality ���ڲ�ͨ�������㷨�����������������loss Խ�ͣ�rtt ԽС���÷ֱ�Խ�ߡ�
 * @note - upLostRate ��ָ���ж����ʡ����磬0.3��ʾÿ�����������10�����ݰ����ܻ�����;��ʧ3����
 * @note - downLostRate ��ָ���ж����ʡ����磬0.2��ʾÿ�ӷ�������ȡ10�����ݰ����ܻ�����;��ʧ2����
 * @note - rtt ��ָ��ǰ�豸����Ѷ�Ʒ�������һ����������ʱ�䣬��ֵԽСԽ�ã�������ֵ��Χ��10ms - 100ms
 */
struct TRTCSpeedTestResult
{
    /// ������ IP ��ַ
    const char* ip;

    /// �����������ڲ�ͨ�������㷨�����������������loss Խ�ͣ�rtt ԽС���÷ֱ�Խ��
    TRTCQuality quality;

    /// ���ж����ʣ���Χ��0 - 1.0�����磬0.3��ʾÿ�����������10�����ݰ����ܻ�����;��ʧ3����
    float upLostRate;

    /// ���ж����ʣ���Χ��0 - 1.0�����磬0.2��ʾÿ�ӷ�������ȡ10�����ݰ����ܻ�����;��ʧ2����
    float downLostRate;

    /// �ӳ٣����룩��ָ��ǰ�豸����Ѷ�Ʒ�������һ����������ʱ�䣬��ֵԽСԽ�ã�������ֵ��Χ��10ms - 100ms
    int rtt;

    TRTCSpeedTestResult()
        : ip(NULL)
        , upLostRate(0.0f)
        , downLostRate(0.0f)
        , rtt(0)
    {

    }
};

/**
* 5.9 �ƶ˻�����ÿһ·�ӻ����λ����Ϣ
*
* TRTCMixUser ����ָ��ÿһ·����ÿһ�� userId����Ƶ����ľ���ڷ�λ��
*/
struct TRTCMixUser
{
    /// ��������� userId
    const char* userId;

    /// ��������� roomId���緿�������ʵ�� roomId����ǰ���������� roomId = NULL
    const char* roomId;

    /// ͼ��λ�������Լ���С�����Ͻ�Ϊ����ԭ��(0,0) ����������ֵ��
    RECT rect;

    /// ͼ���Σ�1 - 15�������ظ�
    int zOrder;

    /// ���û��ǲ���ֻ��������Ƶ
    bool pureAudio;

    /// �����ϵ�����·���棨TRTCVideoStreamTypeBig������Ļ����TRTCVideoStreamTypeSub������
    TRTCVideoStreamType streamType;

    TRTCMixUser()
        : userId(NULL)
        , roomId(NULL)
        , rect()
        , zOrder(0)
        , pureAudio(false)
        , streamType(TRTCVideoStreamTypeBig)
    {
        rect.left = 0;
        rect.top = 0;
        rect.right = 0;
        rect.bottom = 0;
    }
};

/**
 * 5.10 ������������ģʽ
 *
 */
enum TRTCTranscodingConfigMode {
    /// �Ƿ�ֵ
    TRTCTranscodingConfigMode_Unknown = 0,

    /// ȫ�ֶ�ģʽ���������ߣ�����������ϳ����ֻ�������������������
    /// ��ģʽ�£�����Ҫ��д TRTCTranscodingConfig �е����в���������Ҫ���� TRTCCloudDelegate �е� onUserVideoAvailable() �� onUserAudioAvailable() �ص���
    /// �Ա���ݵ�ǰ�����и��������û�������Ƶ״̬���ϵص��� mixUsers ����������ᵼ�»���ʧ�ܡ�
    TRTCTranscodingConfigMode_Manual = 1,

    /// ����Ƶģʽ������������ͨ����AudioCall�������������ң�VoiceChatRoom���ȴ���Ƶ������
    /// ֻ��Ҫ�ڽ�����ͨ�� setMixTranscodingConfig() �ӿ�����һ�Σ�֮�� SDK �ͻ��Զ��ѷ��������������û���������������ǰ�û���ֱ�����ϡ�
    /// ��ģʽ�£����������� TRTCTranscodingConfig �е� mixUsers ������ֻ������ audioSampleRate��audioBitrate �� audioChannels �Ȳ�����
    TRTCTranscodingConfigMode_Template_PureAudio = 2,

    /// Ԥ�Ű�ģʽ��ͨ��ռλ����ǰ�Ը�·��������Ų�
    /// ��ģʽ�£�����Ȼ��Ҫ���� mixUsers �����������Խ� userId ����Ϊռλ������ѡ��ռλ���У�
    /// - "$PLACE_HOLDER_REMOTE$"     :  ָ��Զ���û��Ļ��棬�������ö����
    /// - "$PLACE_HOLDER_LOCAL_MAIN$" �� ָ����������ͷ���棬ֻ��������һ����
    /// - "$PLACE_HOLDER_LOCAL_SUB$"  :  ָ��������Ļ�����棬ֻ��������һ����
    /// ���������Բ���Ҫ���� TRTCCloudDelegate �е� onUserVideoAvailable() �� onUserAudioAvailable() �ص�����ʵʱ������
    /// ֻ��Ҫ�ڽ����ɹ������һ�� setMixTranscodingConfig() ���ɣ�֮�� SDK ���Զ�����ʵ�� userId ��λ�������õ�ռλ���ϡ�
    TRTCTranscodingConfigMode_Template_PresetLayout = 3,
    
    /// ��Ļ����ģʽ�����������߽�������������Ļ����Ϊ����Ӧ�ó�������֧�� Windows �� Mac ����ƽ̨�� SDK��
    /// SDK ���ȸ�������ͨ�� videoWidth �� videoHeight ���������õ�Ŀ��ֱ��ʹ���һ�Ż�����
    /// ����ʦδ������Ļ����ʱ��SDK �Ὣ����ͷ����ȱ���������Ƶ��û����ϣ�����ʦ������Ļ����֮��SDK �Ὣ��Ļ��������Ƶ�ͬ���Ļ����ϡ�
    /// ����������Ŀ����Ϊ��ȷ������ģ�������ֱ���һ�£�����γ̻طź���ҳ�ۿ��Ļ������⣨��ҳ��������֧�ֿɱ�ֱ��ʣ���
    ///
    /// ���ڽ�ѧģʽ�µ���Ƶ��������Ļ����Ϊ�������ͬʱ��������ͷ�������Ļ�������Ƿǳ��˷Ѵ���ġ�
    /// �Ƽ���������ֱ�ӽ�����ͷ����ͨ�� setLocalVideoRenderCallback �ӿ��Զ�����Ƶ���ǰ��Ļ�ϡ�
    /// �ڸ�ģʽ�£����������� TRTCTranscodingConfig �е� mixUsers ������SDK ������ѧ���Ļ��棬���������Ļ�����Ч����
    ///
    /// �����Խ� TRTCTranscodingConfig �е� width �� height ��Ϊ 0px �� 0px��SDK ���Զ������û���ǰ��Ļ�Ŀ�߱ȼ����һ�����ʵķֱ��ʣ�
    /// - �����ʦ��ǰ��Ļ��� <= 1920px��SDK ��ʹ����ʦ��ǰ��Ļ��ʵ�ʷֱ��ʡ�
    /// - �����ʦ��ǰ��Ļ��� > 1920px��SDK ����ݵ�ǰ��Ļ��߱ȣ�ѡ�� 1920x1080(16:9)��1920x1200(16:10)��1920x1440(4:3) ���ֱַ����е�һ�֡�
    TRTCTranscodingConfigMode_Template_ScreenSharing = 4,
};

/**
* 5.11 �ƶ˻�����ת�룩����
*
* �������ձ��������͸�·����İڷ�λ��
*/
struct TRTCTranscodingConfig
{
    ///���ֶκ��塿ת�� config ģʽ
    TRTCTranscodingConfigMode mode;

    ///���ֶκ��塿��Ѷ��ֱ�� AppID
    ///���Ƽ�ȡֵ������ [ʵʱ����Ƶ����̨](https://console.cloud.tencent.com/rav) ѡ���Ѿ�������Ӧ�ã��������ʺ���Ϣ�����ڡ�ֱ����Ϣ���л�ȡ
    uint32_t appId;

    ///���ֶκ��塿��Ѷ��ֱ�� bizid
    ///���Ƽ�ȡֵ������ [ʵʱ����Ƶ����̨](https://console.cloud.tencent.com/rav) ѡ���Ѿ�������Ӧ�ã��������ʺ���Ϣ�����ڡ�ֱ����Ϣ���л�ȡ
    uint32_t bizId;

    ///���ֶκ��塿����ת������Ƶ�ֱ��ʵĿ�ȡ�
    ///���Ƽ�ȡֵ���Ƽ�ֵ��360px ��������Ǵ���Ƶ�������뽫 width �� height ��Ϊ 0px �� 0px������������Я��һ��������������Ƶ����
    uint32_t videoWidth;

    ///���ֶκ��塿����ת������Ƶ�ֱ��ʵĸ߶ȡ�
    ///���Ƽ�ȡֵ���Ƽ�ֵ��640px ��������Ǵ���Ƶ�������뽫 width �� height ��Ϊ 0px �� 0px������������Я��һ��������������Ƶ����
    uint32_t videoHeight;

    ///���ֶκ��塿����ת������Ƶ�ֱ��ʵ����ʣ�kbps����
    ///���Ƽ�ȡֵ�������0����̨�����videoWidth��videoHeight���������ʣ���Ҳ���Բο�ö�ٶ���TRTCVideoResolution_640_480��ע�͡�
    uint32_t videoBitrate;

    ///���ֶκ��塿����ת������Ƶ�ֱ��ʵ�֡�ʣ�FPS����
    ///���Ƽ�ȡֵ��Ĭ��ֵ��15fps��ȡֵ��Χ�� (0,30]��
    uint32_t videoFramerate;

    ///���ֶκ��塿����ת������Ƶ�ֱ��ʵĹؼ�֡������ֳ�Ϊ GOP����
    ///���Ƽ�ȡֵ��Ĭ��ֵ��2����λΪ�룬ȡֵ��Χ�� [1,8]��
    uint32_t videoGOP;

    ///���ֶκ��塿��Ϻ���ĵ�ɫ��ɫ��Ĭ��Ϊ��ɫ����ʽΪʮ���������֣����磺��0x61B9F1�� ���� RGB �ֱ�Ϊ(97,158,241)��
    ///���Ƽ�ȡֵ��Ĭ��ֵ��0x000000����ɫ
    uint32_t backgroundColor;

    ///���ֶκ��塿����ת������Ƶ�����ʡ�
    ///���Ƽ�ȡֵ��Ĭ��ֵ��48000Hz��֧��12000HZ��16000HZ��22050HZ��24000HZ��32000HZ��44100HZ��48000HZ��
    uint32_t audioSampleRate;

    ///���ֶκ��塿����ת������Ƶ���ʡ�
    ///���Ƽ�ȡֵ��Ĭ��ֵ��64kbps��ȡֵ��Χ�� [32��192]��
    uint32_t audioBitrate;

    ///���ֶκ��塿����ת������Ƶ������
    ///���Ƽ�ȡֵ��Ĭ��ֵ��1��ȡֵ��ΧΪ [1,2] �е����͡�
    uint32_t audioChannels;

    ///���ֶκ��塿ÿһ·�ӻ����λ����Ϣ
    TRTCMixUser* mixUsersArray;

    ///���ֶκ��塿 ���� mixUsersArray �Ĵ�С
    uint32_t mixUsersArraySize;

    TRTCTranscodingConfig()
        : mode(TRTCTranscodingConfigMode_Unknown)
        , videoWidth(0)
        , videoHeight(0)
        , videoBitrate(0)
        , videoFramerate(15)
        , videoGOP(2)
        , audioSampleRate(64)
        , audioBitrate(48000)
        , audioChannels(1)
        , mixUsersArray(nullptr)
        , mixUsersArraySize(0)
        , backgroundColor(0)
    {}
};

/**
 * 5.12 CDN ��·��������
 */
struct TRTCPublishCDNParam
{
    /// ��Ѷ�� AppID������ [ʵʱ����Ƶ����̨](https://console.cloud.tencent.com/rav) ѡ���Ѿ�������Ӧ�ã��������ʺ���Ϣ�����ڡ�ֱ����Ϣ���л�ȡ
    uint32_t appId;

    /// ��Ѷ��ֱ�� bizid������ [ʵʱ����Ƶ����̨](https://console.cloud.tencent.com/rav) ѡ���Ѿ�������Ӧ�ã��������ʺ���Ϣ�����ڡ�ֱ����Ϣ���л�ȡ
    uint32_t bizId;

    /// ��·ת�Ƶ� URL
    const char* url;

    TRTCPublishCDNParam()
        : url(NULL)
        , appId(0)
        , bizId(0)
    {

    }
};

/**
* 5.13 ¼������
*
* ����ȷ��д������ȷ��¼���ļ�˳�����ɡ�
*/
struct TRTCAudioRecordingParams {

    ///���ֶκ��塿�ļ�·���������¼���ļ��ı���·������·����Ҫ�û�����ָ������ȷ��·�������ҿ�д��
    ///���ر�˵������·���辫ȷ���ļ�������ʽ��׺����ʽ��׺����¼���ļ��ĸ�ʽ��Ŀǰ֧�ֵĸ�ʽ�� PCM��WAV �� AAC��
    ///          ���磬ָ��·��Ϊ path/to/audio.aac���������һ�� AAC ��ʽ���ļ���
    ///          ��ָ��һ���ж�дȨ�޵ĺϷ�·��������¼���ļ��޷����ɡ�
    const char * filePath;

    TRTCAudioRecordingParams()
        : filePath(nullptr)
    {

    }
};


/**
* 5.14 ��Ч
*
*/
struct TRTCAudioEffectParam {

    ///���ֶκ��塿��Ч ID��
    ///������˵����SDK �����Ŷ�·��Ч�������Ҫ��Ч ID ���б�ǣ����ڿ�����Ч�Ŀ�ʼ��ֹͣ��������
    int effectId;

    ///���ֶκ��塿��Ч·����֧�ֵ��ļ���ʽ��aac, mp3��
    const char * path;

    ///���ֶκ��塿ѭ�����Ŵ���
    ///���Ƽ�ȡֵ��ȡֵ��ΧΪ0 - ������������Ĭ��ֵ��0��0��ʾ������Чһ�Σ�1��ʾ������Ч���Σ��Դ�����
    int loopCount;

    ///���ֶκ��塿��Ч�Ƿ�����
    ///���Ƽ�ȡֵ��YES����Ч�ڱ��ز��ŵ�ͬʱ�����������ƶˣ����Զ���û�Ҳ����������Ч��NO����Ч�����������ƶˣ����ֻ���ڱ�����������Ч��Ĭ��ֵ��NO
    bool publish;

    ///���ֶκ��塿��Ч����
    ///���Ƽ�ȡֵ��ȡֵ��ΧΪ0 - 100��Ĭ��ֵ��100
    int volume;

    TRTCAudioEffectParam(const int _effectId, const char *_path)
        : loopCount(0)
        , publish(false)
        , volume(100)
    {
        effectId = _effectId;
        path = _path;
    }
};
/// @}

#endif /* __TRTCCLOUDDEF_H__ */
