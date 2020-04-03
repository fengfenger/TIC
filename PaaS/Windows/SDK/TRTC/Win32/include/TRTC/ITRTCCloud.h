#ifndef __ITRTCCLOUD_H__
#define __ITRTCCLOUD_H__
/*
 * Module:   ITRTCCloud @ TXLiteAVSDK
 *
 * SDK VERSION 6.0
 *
 * Function: ��Ѷ����Ƶͨ�����ܵ���Ҫ�ӿ���
 *
 * Nouns[1]: ���� - TRTC �������ͷ��һ·�Ļ��������������������·�����档
 * Nouns[2]: ����(substream) - TRTC �����Ļ������߲�Ƭ��һ·�Ļ������������������·�����档
 * Nouns[3]: ��Ƭ(vodplay) - TRTC �� Windows �汾֧�ֽ����ص�һ����Ƶ�ļ������ȥ��������ܳ�Ϊ����Ƭ����
 *
 * ����/ʹ��/���� ITRTCCloud �����ʾ�����룺
 * <pre>
 *     ITRTCCloud *trtcCloud = getTRTCShareInstance();
 *     if(trtcCloud)
 *     {
 *         std::string version(trtcCloud->getSDKVersion());
 *     }
 *     //--------------------------------------------------
 *     destroyTRTCShareInstance();
 *     trtcCloud = NULL;
 * </pre>
 */

#include "TRTCCloudCallback.h"
#include "TRTCCloudDef.h"
#include <windows.h>

class ITRTCCloud;

/// @defgroup ITRTCCloud_cplusplus ITRTCCloud
/// ��Ѷ����Ƶͨ�����ܵ���Ҫ�ӿ���
/// @{
extern "C" {
    /// @name ���������� ITRTCCloud ����
    /// @{
    /**
    * \brief ���ڶ�̬���� dll ʱ����ȡ ITRTCCloud ����ָ�롣
    *
    * \return ���� ITRTCCloud ���������ָ�룬ע�⣺delete ITRTCCloud*����������Ҫ���� destroyTRTCCloud �ͷŵ���ָ�����
    */
    LITEAV_API ITRTCCloud* getTRTCShareInstance();

    /**
    * \brief �ͷ� ITRTCCloud ��������
    */
    LITEAV_API void destroyTRTCShareInstance();
    /// @}
}

class ITRTCCloud
{
protected:
    virtual ~ITRTCCloud() {};

public:
    /////////////////////////////////////////////////////////////////////////////////
    //
    //                       ���� TRTCCloudCallback �ص�
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name ���� TRTCCloudCallback �ص�
    /// @{
    /**
    * ���ûص��ӿ� ITRTCCloudCallback
    *
    * ������ͨ�� ITRTCCloudCallback ������� SDK �ĸ���״̬֪ͨ����� ITRTCCloudCallback.h �еĶ���
    *
    * @param callback �¼��ص�ָ��
    */
    virtual void addCallback(ITRTCCloudCallback* callback) = 0;

    /**
    * �Ƴ��¼��ص�
    *
    * @param callback �¼��ص�ָ��
    */
    virtual void removeCallback(ITRTCCloudCallback* callback) = 0;
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ��һ��������ؽӿں���
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name ������ؽӿں���
    /// @{
    /**
    * 1.1 ���뷿��
    *
    * ���ýӿں������յ����� TRTCCloudCallback �е� onEnterRoom(result) �ص�:
    * - �������ɹ���result ����һ��������result > 0������ʾ���뷿���ʱ�����ģ���λ�Ǻ��루ms����
    * - �������ʧ�ܣ�result ����һ��������result < 0������ʾ����ʧ�ܵĴ����롣
    *
    * ����ʧ�ܵĴ����뺬����μ�[������](https://cloud.tencent.com/document/product/647/32257)��
    *
    *  - {@link TRTCAppSceneVideoCall}��<br>
    *           ��Ƶͨ��������֧��720P��1080P���廭�ʣ������������֧��300��ͬʱ���ߣ����֧��50��ͬʱ���ԡ�<br>
    *           �ʺϣ�[1��1��Ƶͨ��]��[300����Ƶ����]��[��������]��[��Ƶ����]��[Զ������]�ȡ�<br>
    *  - {@link TRTCAppSceneAudioCall}��<br>
    *           ����ͨ��������֧�� 48kHz��֧��˫�����������������֧��300��ͬʱ���ߣ����֧��50��ͬʱ���ԡ�<br>
    *           �ʺϣ�[1��1����ͨ��]��[300����������]��[��������]��[��������]��[��������ɱ]�ȡ�<br>
    *  - {@link TRTCAppSceneLIVE}��<br>
    *           ��Ƶ����ֱ����֧��ƽ���������л���������ȴ���������ʱС��300ms��֧��ʮ�򼶱����ͬʱ���ţ�������ʱ����1000ms��<br>
    *           �ʺϣ�[��Ƶ����ʱֱ��]��[ʮ���˻�������]��[��Ƶֱ�� PK]��[��Ƶ���׷�]��[��������]��[Զ����ѵ]��[�����ͻ���]�ȡ�<br>
    *  - {@link TRTCAppSceneVoiceChatRoom}��<br>
    *           ��������ֱ����֧��ƽ���������л���������ȴ���������ʱС��300ms��֧��ʮ�򼶱����ͬʱ���ţ�������ʱ����1000ms��<br>
    *           �ʺϣ�[��������ʱֱ��]��[����ֱ������]��[���ķ�]��[K �跿]��[FM ��̨]�ȡ�<br>
    *
    * @param param ������������ο� TRTCParams
    * @param scene Ӧ�ó�����Ŀǰ֧����Ƶͨ����VideoCall��������ֱ����Live��������ͨ����AudioCall�������������ң�VoiceChatRoom�����ֳ�����
    *
    * @note
    *  1. �� scene ѡ��Ϊ TRTCAppSceneLIVE �� TRTCAppSceneVoiceChatRoom ʱ��������ͨ�� TRTCParams �е� role �ֶ�ָ����ǰ�û��Ľ�ɫ��<br>
    *  2. ���ܽ����Ƿ�ɹ���enterRoom �������� exitRoom ���ʹ�ã��ڵ��� exitRoom ǰ�ٴε��� enterRoom �����ᵼ�²���Ԥ�ڵĴ������⡣
    */
    virtual void enterRoom(const TRTCParams& params, TRTCAppScene scene) = 0;

    /**
    * 1.2 �뿪����
    *
    * ���� exitRoom() �ӿڻ�ִ���˳����������߼��������ͷ�����Ƶ�豸��Դ�ͱ��������Դ�ȡ�
    * ����Դ�ͷ���ϣ�SDK ��ͨ�� TRTCCloudCallback �е� onExitRoom() �ص�֪ͨ����
    *
    * �����Ҫ�ٴε��� enterRoom() �����л�������������Ƶ SDK����ȴ� onExitRoom() �ص���������ִ����ز�����
    * ������ܻ�����������ͷ����˷��豸��ǿռ�ȸ����쳣���⡣
    */
    virtual void exitRoom() = 0;

    /**
    * 1.3 �л���ɫ����������ֱ��������TRTCAppSceneLIVE �� TRTCAppSceneVoiceChatRoom��
    *
    * ��ֱ�������£�һ���û�������Ҫ�ڡ����ڡ��͡�������֮�������л���
    * �������ڽ���ǰͨ�� TRTCParams �е� role �ֶ�ȷ����ɫ��Ҳ����ͨ�� switchRole �ڽ������л���ɫ��
    *
    * @param role Ŀ���ɫ��Ĭ��Ϊ������
    *  - {@link TRTCRoleAnchor} ����������������Ƶ����Ƶ��һ�����������֧��50������ͬʱ��������Ƶ��
    *  - {@link TRTCRoleAudience} ���ڣ�ֻ�ܹۿ�������������Ƶ����Ƶ��һ��������Ĺ�������û�����ޡ�
    */
    virtual void switchRole(TRTCRoleType role) = 0;

    /**
    * 1.4 ����緿ͨ�������� PK��
    *
    * TRTC ��������ͬ����Ƶ�����е�����������ͨ�����緿ͨ����������ͨ����ͨ�����ܡ�ʹ�ô˹���ʱ��
    * �������������˳�����ԭ����ֱ���伴�ɽ��С����� PK����
    *
    * ���磺�����䡰001���е����� A ͨ�� connectOtherRoom() �����䡰002���е����� B ��ͨ�緿ͨ����
    * ���䡰001���е��û������յ����� B �� onUserEnter(B) �ص��� onUserVideoAvailable(B,true) �ص���
    * ���䡰002���е��û������յ����� A �� onUserEnter(A) �ص��� onUserVideoAvailable(A,true) �ص���
    *
    * ����֮���緿ͨ���ı��ʣ����ǰ�������ͬ�����е������໥������ÿ��������Ĺ��ڶ��ܿ�������������
    *
    * <pre>
    *                 ���� 001                     ���� 002
    *               -------------               ------------
    *  �緿ͨ��ǰ��| ���� A      |             | ���� B     |
    *              | ���� U V W  |             | ���� X Y Z |
    *               -------------               ------------
    *
    *                 ���� 001                     ���� 002
    *               -------------               ------------
    *  �緿ͨ����| ���� A B    |             | ���� B A   |
    *              | ���� U V W  |             | ���� X Y Z |
    *               -------------               ------------
    * </pre>
    *
    * �緿ͨ���Ĳ������ǵ�������չ�ֶεļ��������⣬��ʱ������ JSON ��ʽ�Ĳ�����Ҫ�����ٰ��������ֶΣ�
    * - roomId�����䡰001���е����� A Ҫ�����䡰002���е����� B �������� A ���� connectOtherRoom() ʱ roomId Ӧָ��Ϊ��002����
    * - userId�����䡰001���е����� A Ҫ�����䡰002���е����� B �������� A ���� connectOtherRoom() ʱ userId Ӧָ��Ϊ B �� userId��
    *
    * �緿ͨ������������ͨ�� TRTCCloudCallback �е� onConnectOtherRoom() �ص�֪ͨ������
    *
    * <pre>
    *   //�˴��õ� jsoncpp ������ʽ�� JSON �ַ���
    *   Json::Value jsonObj;
    *   jsonObj["roomId"] = 002;
    *   jsonObj["userId"] = "userB";
    *   Json::FastWriter writer;
    *   std::string params = writer.write(jsonObj);
    *   trtc.ConnectOtherRoom(params.c_str());
    * </pre>
    *
    * @param params JSON �ַ������������roomId ����Ŀ�귿��ţ�userId ����Ŀ���û� ID��
    *
    **/
    virtual void connectOtherRoom(const char* params) = 0;

    /**
    * 1.5 �رտ緿����
    *
    * �緿ͨ�����˳������ͨ�� TRTCCloudCallback �е� onDisconnectOtherRoom() �ص�֪ͨ������
    */
    virtual void disconnectOtherRoom() = 0;

    /**
    * 1.6 ��������Ƶ���ݽ���ģʽ����Ҫ�ڽ���ǰ���ò�����Ч��
    *
    * Ϊʵ�ֽ����뿪�ľ������飬SDK Ĭ�Ͻ������Զ���������Ƶ�������������ɹ���ͬʱ�����������յ�Զ�������û�������Ƶ���ݡ�
    * ����û�е��� startRemoteView����Ƶ���ݽ��Զ���ʱȡ����
    * ������Ҫ�������������û���Զ�������Ƶ��������ĳ����������Ը���ʵ������ѡ�����ģʽ��
    *
    * \param autoRecvAudio true���Զ�������Ƶ���ݣ�false����Ҫ���� muteRemoteAudio ���������ȡ����Ĭ��ֵ��true
    * \param autoRecvVideo true���Զ�������Ƶ���ݣ�false����Ҫ���� startRemoteView/stopRemoteView ���������ȡ����Ĭ��ֵ��true
    *
    * \note ��Ҫ�ڽ���ǰ���ò�����Ч��
    **/
    virtual void setDefaultStreamRecvMode(bool autoRecvAudio, bool autoRecvVideo) = 0;
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ������CDN ��ؽӿں���
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name CDN ��ؽӿں���
    /// @{

    /**
    * 2.1 ��ʼ����Ѷ�Ƶ�ֱ�� CDN ����
    *
    * �ýӿڻ�ָ����ǰ�û�������Ƶ������Ѷ�� CDN ����Ӧ�� StreamId����������ָ����ǰ�û��� CDN ���ŵ�ַ��
    *
    * ���磺������ǲ������´������õ�ǰ�û��������� StreamId Ϊ user_stream_001����ô���û��������Ӧ�� CDN ���ŵ�ַΪ��
    * ��http://yourdomain/live/user_stream_001.flv�������� yourdomain Ϊ���Լ������Ĳ���������
    * ��������ֱ��[����̨](https://console.cloud.tencent.com/live) �������Ĳ�����������Ѷ�Ʋ��ṩĬ�ϵĲ���������
    *
    * <pre>
    *  ITRTCCloud *trtcCloud = getTRTCShareInstance();
    *  trtcCloud->enterRoom(params, TRTCAppSceneLIVE);
    *  trtcCloud->startLocalPreview(HWND);
    *  trtcCloud->startLocalAudio();
    *  trtcCloud->startPublishing("user_stream_001", TRTCVideoStreamTypeBig);
    * </pre>
    *
    * ��Ҳ���������� enterRoom �Ĳ��� TRTCParams ʱָ�� streamId, �������Ǹ��Ƽ����������ַ�����
    *
    * @param streamId �Զ����� Id��
    * @param type ��֧�� TRTCVideoStreamTypeBig �� TRTCVideoStreamTypeSub��
    * @note ����Ҫ����ʵʱ����Ƶ [����̨](https://console.cloud.tencent.com/rav/) �еĹ�������ҳ�����������Զ���·ֱ����������Ч��
    */
    virtual void startPublishing(const char* streamId, TRTCVideoStreamType type) = 0;
    
    /**
    * 2.2 ֹͣ����Ѷ�Ƶ�ֱ�� CDN ����
    */
    virtual void stopPublishing() = 0;

    /**
    * 2.3 ��ʼ�������Ƶ�ֱ�� CDN ת��
    *
    * �ýӿڸ� startPublishing() ���ƣ��� startPublishCDNStream() ֧�������Ѷ�Ƶ�ֱ�� CDN ת�ơ�
    * ʹ�� startPublishing() ����Ѷ��ֱ�� CDN ����ȡ����ķ��á�
    * ʹ�� startPublishCDNStream() �󶨷���Ѷ��ֱ�� CDN ��Ҫ��ȡת�Ʒ��ã�����Ҫͨ��������ϵ���ǿ�ͨ��
    * 
    * @param param ת�Ʋ���
    */
    virtual void startPublishCDNStream(const TRTCPublishCDNParam& param) = 0;

    /**
    * 2.4 ֹͣ�����Ѷ�Ƶ�ַת��
    */
    virtual void stopPublishCDNStream() = 0;

    /**
    * 2.5 �����ƶ˵Ļ���ת�����
    *
    * �������ʵʱ����Ƶ [����̨](https://console.cloud.tencent.com/trtc/) �еĹ�������ҳ�����ˡ������Զ���·ֱ�������ܣ�
    * �������ÿһ·���涼����һ��Ĭ�ϵ�ֱ�� [CDN ��ַ](https://cloud.tencent.com/document/product/647/16826)��
    *
    * һ��ֱ�����п����в�ֹһλ����������ÿ�����������Լ��Ļ���������������� CDN ������˵������ֻ��Ҫһ·ֱ������
    * ��������Ҫ����·����Ƶ�����һ·��׼��ֱ�����������Ҫ����ת�롣
    *
    * �������� setMixTranscodingConfig() �ӿ�ʱ��SDK ������Ѷ�Ƶ�ת�����������һ��ָ�Ŀ���ǽ�������Ķ�·����Ƶ�����Ϊһ·,
    * ������ͨ�� mixUsers ����������ÿһ·�����λ�ã��Լ��Ƿ�ֻ���������Ҳ����ͨ�� videoWidth��videoHeight��videoBitrate �Ȳ������ƻ������Ƶ���ı��������
    *
    * <pre>
    * ������1��=> ���� ====> \
    *                         \
    * ������2��=> ���� =>  ������ => ���� => ����Ϻ�Ļ��桿
    *                         /
    * ������3��=> ���� ====> /
    *
    * ������1��=> ���� ====> \
    *                         \
    * ������2��=> ���� =>  ������� => ���� => ����Ϻ��������
    *                         /
    * ������3��=> ���� ====> /
    * </pre>
    *
    * �ο��ĵ���[�ƶ˻���ת��](https://cloud.tencent.com/document/product/647/16827)��
    *
    * @param config ��ο� TRTCCloudDef.h �й��� TRTCTranscodingConfig �Ľ��ܡ�������� nil ��ȡ���ƶ˻���ת�롣
    * @note �����ƶ˻�����ע�����
    *  - �ƶ�ת�������һ���� CDN �ۿ���ʱ����Ż�����1 - 2�롣
    *  - ���øú������û����Ὣ�����еĶ�·�����ϵ��Լ���ǰ��·�����С�
    */
    virtual void setMixTranscodingConfig(TRTCTranscodingConfig* config) = 0;
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ��������Ƶ��ؽӿں���
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name  ��Ƶ��ؽӿں���
    /// @{
    /**
    * 3.1 ����������Ƶ��Ԥ������
    *
    * ����ӿڻ�����Ĭ�ϵ�����ͷ������ͨ�� setCurrentCameraDevice �ӿ�ѡ����������ͷ
    * ����ʼ��Ⱦ��֡����ͷ����ʱ�������յ� TRTCCloudCallback �е� onFirstVideoFrame(null) �ص���
    *
    * @param rendHwnd ����Ԥ������� HWND
    */
    virtual void startLocalPreview(HWND rendHwnd) = 0;

    /**
    * 3.2 ֹͣ������Ƶ�ɼ���Ԥ��
    */
    virtual void stopLocalPreview() = 0;

    /**
    * 3.3 �Ƿ������Լ�����Ƶ����
    *
    * ��ֹͣ���ͱ�����Ƶ�󣬷������������Ա�����յ� onUserVideoAvailable �ص�֪ͨ
    * @param mute true�����Σ�false��������Ĭ��ֵ��false
    */
    virtual void muteLocalVideo(bool mute) = 0;

    /**
    * 3.4 ��ʼ��ʾԶ����Ƶ����
    *
    * ���յ� SDK �� onUserVideoAvailable(userId, true) ֪ͨʱ�����Ի�֪��Զ���û���������Ƶ��
    * �˺���� startRemoteView(userId) �ӿڼ��ظ��û���Զ�̻���ʱ�������� loading �����Ż����ع����еĵȴ����顣
    * �����û�����֡���濪ʼ��ʾʱ�������յ� onFirstVideoFrame(userId) �¼��ص���
    *
    * @param userId   �Է����û���ʶ
    * @param rendHwnd ����Ԥ������Ĵ��ھ��
    */
    virtual void startRemoteView(const char* userId, HWND rendHwnd) = 0;

    /**
    * 3.5 ֹͣ��ʾԶ����Ƶ���棬ͬʱ������ȡ��Զ���û�����Ƶ������
    *
    * ���ô˽ӿں�SDK ��ֹͣ���ո��û���Զ����Ƶ����ͬʱ��������ص���Ƶ��ʾ��Դ��
    *
    * @param userId �Է����û���ʶ
    */
    virtual void stopRemoteView(const char* userId) = 0;

    /**
    * 3.6 ֹͣ��ʾ����Զ����Ƶ���棬ͬʱ������ȡԶ���û�����Ƶ������
    *
    * @note �������Ļ����Ļ�������ʾ������Ļ����Ļ���Ҳ��һ�����رա�
    */
    virtual void stopAllRemoteView() = 0;

    /**
    * 3.7 ��ͣ����ָ����Զ����Ƶ��
    *
    * �ýӿڽ�ֹͣ����Զ���û�����Ƶ�����������ͷ���ʾ��Դ��������Ƶ����ᶳ���� mute ǰ�����һ֡��
    *
    * @param userId �Է����û���ʶ
    * @param mute  �Ƿ�ֹͣ����
    */
    virtual void muteRemoteVideoStream(const char* userId, bool mute) = 0;

    /**
    * 3.8 ֹͣ��������Զ����Ƶ��
    *
    * @param mute �Ƿ�ֹͣ����
    */
    virtual void muteAllRemoteVideoStreams(bool mute) = 0;

    /**
    * 3.9 ������Ƶ��������ز���
    *
    * �����þ�����Զ���û������Ļ���������ͬʱҲ���ƶ�¼�Ƴ�����Ƶ�ļ��Ļ���������
    *
    * @param params ��Ƶ���������������ο� TRTCCloudDef.h �е� TRTCVideoEncParam ����
    */
    virtual void setVideoEncoderParam(const TRTCVideoEncParam& params) = 0;

    /**
    * 3.10 ��������������ز���
    *
    * �����þ����� SDK �ڸ������绷���µĵ��ز��ԣ������������ǡ������������ǡ�����������
    *
    * @param params �������ز�����������ο� TRTCCloudDef.h �е� TRTCNetworkQosParam ����
    */
    virtual void setNetworkQosParam(const TRTCNetworkQosParam& params) = 0;

    /**
    * 3.11 ���ñ���ͼ�����Ⱦģʽ
    *
    * @param mode ��䣨������ܻᱻ����ü�������Ӧ��������ܻ��кڱߣ���Ĭ��ֵ��TRTCVideoFillMode_Fit
    */
    virtual void setLocalViewFillMode(TRTCVideoFillMode mode) = 0;

    /**
    * 3.12 ����Զ��ͼ�����Ⱦģʽ
    *
    * @param userId �û� ID
    * @param mode ��䣨������ܻᱻ����ü�������Ӧ��������ܻ��кڱߣ���Ĭ��ֵ��TRTCVideoFillMode_Fit
    */
    virtual void setRemoteViewFillMode(const char* userId, TRTCVideoFillMode mode) = 0;

    /**
    * 3.13 ���ñ���ͼ���˳ʱ����ת�Ƕ�
    *
    * @param rotation ֧�� TRTCVideoRotation90 �� TRTCVideoRotation180 �Լ� TRTCVideoRotation270 ��ת�Ƕȣ�Ĭ��ֵ��TRTCVideoRotation0
    */
    virtual void setLocalViewRotation(TRTCVideoRotation rotation) = 0;

    /**
    * 3.14 ����Զ��ͼ���˳ʱ����ת�Ƕ�
    *
    * @param userId �û� ID
    * @param rotation ֧�� TRTCVideoRotation90 �� TRTCVideoRotation180 �Լ� TRTCVideoRotation270 ��ת�Ƕȣ�Ĭ��ֵ��TRTCVideoRotation0
    */
    virtual void setRemoteViewRotation(const char* userId, TRTCVideoRotation rotation) = 0;

    /**
    * 3.15 ������Ƶ��������ģ�Ҳ����Զ���û��ۿ����ģ��Լ�������¼�������ģ����淽��
    *
    * @param rotation Ŀǰ֧�� TRTCVideoRotation0 �� TRTCVideoRotation180 ��ת�Ƕȣ�Ĭ��ֵ��TRTCVideoRotation0
    */
    virtual void setVideoEncoderRotation(TRTCVideoRotation rotation) = 0;

    /**
    * 3.16 ���ñ�������ͷԤ������ľ���ģʽ
    *
    * @param mirror ����ģʽ��Ĭ��ֵ��false���Ǿ���ģʽ��
    */
    virtual void setLocalViewMirror(bool mirror) = 0;

    /**
    * 3.17 ���ñ���������Ļ��澵��ģʽ
    *
    * �ýӿڲ��ı䱾������ͷ��Ԥ�����棬����ı���һ���û������ģ��Լ�������¼�Ƶģ�����Ч����
    *
    * @param mirror �Ƿ���Զ�˾���, true��Զ�˻��澵��false��Զ�˻���Ǿ���Ĭ��ֵ��false
    */
    virtual void setVideoEncoderMirror(bool mirror) = 0;

    /**
    * 3.18 ������С����˫·����ģʽ
    *
    * �����ǰ�û��Ƿ����е���Ҫ��ɫ��������������ʦ�������˵ȣ�������ʹ�� PC ���� Mac ���������Կ�����ģʽ��
    * ������ģʽ�󣬵�ǰ�û���ͬʱ��������塿�͡����塿��·��Ƶ������ֻ��һ·��Ƶ������
    * ���ڿ�����ģʽ�ĵ�ǰ�û�����ռ�ø��������������һ�������� CPU ������Դ��
    *
    * ����ͬһ�����Զ�̹��ڶ��ԣ�
    * - ����û�����������ܺã�����ѡ��ۿ������塿����
    * - ����û�����������ϲ����ѡ��ۿ������塿����
    *
    * @param enable �Ƿ���С������룬Ĭ��ֵ��false
    * @param smallVideoParam С������Ƶ����
    */
    virtual void enableSmallVideoStream(bool enable, const TRTCVideoEncParam& smallVideoParam) = 0;

    /**
    * 3.19 ѡ���ۿ�ָ�� userId �Ĵ��滹��С����
    *
    * �˹�����Ҫ�� userId ͨ�� enableEncSmallVideoStream ��ǰ����˫·����ģʽ��
    * ����� userId û�п���˫·����ģʽ����˲�����Ч��
    *
    * @param userId �û� ID
    * @param type ��Ƶ�����ͣ���ѡ�񿴴��滹��С���棬Ĭ��Ϊ TRTCVideoStreamTypeBig
    */
    virtual void setRemoteVideoStreamType(const char* userId, TRTCVideoStreamType type) = 0;

    /**
    * 3.20 �趨�ۿ�������ѡ�����Ƶ����
    *
    * �Ͷ��豸�Ƽ�����ѡ��������ȵ�С���档
    * ����Է�û�п���˫·��Ƶģʽ����˲�����Ч��
    *
    * @param type Ĭ�Ϲۿ����滹��С���棬Ĭ��Ϊ TRTCVideoStreamTypeBig
    */
    virtual void setPriorRemoteVideoStreamType(TRTCVideoStreamType type) = 0;
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ���ģ���Ƶ��ؽӿں���
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name ��Ƶ��ؽӿں���
    /// @{

    /**
    * 4.1 ����������Ƶ�Ĳɼ�������
    *
    * �ú�����������˷�ɼ���������Ƶ���ݴ����������������û���
    * SDK ������Ĭ�Ͽ������ص���Ƶ���У�Ҳ��˵����������������������������������û�������������������
    *
    * @note TRTC SDK ������Ĭ�ϴ򿪱��ص���˷�ɼ���
    */
    virtual void startLocalAudio() = 0;

    /**
    * 4.2 �رձ�����Ƶ�Ĳɼ�������
    *
    * ���رձ�����Ƶ�Ĳɼ������У��������������Ա���յ� onUserAudioAvailable(false) �ص�֪ͨ��
    */
    virtual void stopLocalAudio() = 0;

    /**
    * 4.3 �������ص���Ƶ
    *
    * ������������Ƶ�󣬷������������Ա���յ� onUserAudioAvailable(false) �ص�֪ͨ��
    * �� stopLocalAudio ��֮ͬ�����ڣ�muteLocalAudio ������ֹͣ��������Ƶ���ݣ����ǻ�����������ʼ��͵ľ�������
    * �ڶ�¼������Ҫ��ܸߵĳ����У�ѡ�� muteLocalAudio �Ǹ��õ�ѡ����¼�Ƴ������Ը��õ� MP4 �ļ���
    * �������� MP4 ����Ƶ�ļ���ʽ��������Ƶ����������Ҫ��ܸߵģ��򵥴ֱ��� stopLocalAudio �ᵼ��¼�Ƴ��� MP4 ���ײ��š�
    *
    * @param mute true�����Σ�false��������Ĭ��ֵ��false
    */
    virtual void muteLocalAudio(bool mute) = 0;

    /**
    * 4.4 ����ĳһ���û���������ͬʱ������ȡ��Զ���û�����Ƶ������
    *
    * @param userId �û� ID
    * @param mute true��������false���Ǿ���
    */
    virtual void muteRemoteAudio(const char* userId, bool mute) = 0;

    /**
    * 4.5 ���������û���������ͬʱ������ȡԶ���û�����Ƶ������
    *
    * @param mute true��������false���Ǿ���
    */
    virtual void muteAllRemoteAudio(bool mute) = 0;

    /**
    * 4.6 ���� SDK �ɼ�������
    *
    * @param volume ������С��ȡֵ0 - 100��Ĭ��ֵΪ100
    */
    virtual void setAudioCaptureVolume(int volume) = 0;

    /**
    * 4.7 ��ȡ SDK �ɼ�����
    */
    virtual int getAudioCaptureVolume() = 0;

    /**
    * 4.8 ���� SDK ����������
    *
    * @note �ú�����������ս���ϵͳ���ŵ�������������Ӱ��¼�Ʊ�����Ƶ�ļ���������С��������Ӱ�����������
    *
    * @param volume ������С��ȡֵ0 - 100��Ĭ��ֵΪ100
    */
    virtual void setAudioPlayoutVolume(int volume) = 0;

    /**
    * 4.9 ��ȡ SDK ��������
    */
    virtual int getAudioPlayoutVolume() = 0;

    /**
    * 4.10 ���û�ر�������С��ʾ
    *
    * �����˹��ܺ�SDK ���� onUserVoiceVolume() �з�����ÿһ·����������Сֵ��������
    * ������ Demo ����һ��������С����ʾ�������ǻ�������ӿ�ʵ�ֵġ�
    * ��ϣ���򿪴˹��ܣ����� startLocalAudio() ֮ǰ���á�
    *
    * @param interval ���� onUserVoiceVolume �ص��Ĵ����������λΪms����С���Ϊ100ms�����С�ڵ���0���رջص�����������Ϊ300ms
    */
    virtual void enableAudioVolumeEvaluation(uint32_t interval) = 0;

    /**
     * 4.11 ��ʼ¼��
     *
     * �÷������ú� SDK �Ὣͨ�������е�������Ƶ(����������Ƶ��Զ����Ƶ��BGM��)¼�Ƶ�һ���ļ��
     * �����Ƿ���������øýӿڶ���Ч��
     * ������� exitRoom ʱ����¼����¼�����Զ�ֹͣ��
     *
     * @param audioRecordingParams ¼����������ο�TRTCAudioRecordingParams
     * @return 0���ɹ���-1��¼���ѿ�ʼ��-2���ļ���Ŀ¼����ʧ�ܣ�-3����׺ָ������Ƶ��ʽ��֧��
     */
    virtual int startAudioRecording(const TRTCAudioRecordingParams& audioRecordingParams) = 0;

    /**
     * 4.12 ֹͣ¼��
     *
     * ������� exitRoom ʱ����¼����¼�����Զ�ֹͣ��
     */
    virtual void stopAudioRecording() = 0;
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ���壩����ͷ��ؽӿں���
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name ����ͷ��ؽӿں���
    /// @{
    /**
    * 5.1 ��ȡ����ͷ�豸�б�
    *
    * ʾ�����룺
    * <pre>
    *  ITRTCDeviceCollection * pDevice = m_pCloud->getCameraDevicesList();
    *  for (int i = 0; i < pDevice->getCount(); i++)
    *  {
    *      std::wstring name = UTF82Wide(pDevice->getDeviceName(i));
    *  }
    *  pDevice->release();
    *  pDevice = null;
    * </pre>
    *
    * @note ��� delete ITRTCDeviceCollection*ָ���������SDK ά�� ITRTCDeviceCollection ������������ڡ�
    * @return ����ͷ����������ָ�� ITRTCDeviceCollection*
    */
    virtual ITRTCDeviceCollection* getCameraDevicesList() = 0;

    /**
    * 5.2 ����Ҫʹ�õ�����ͷ
    *
    * @param deviceId �� getCameraDevicesList �еõ����豸 ID
    */
    virtual void setCurrentCameraDevice(const char* deviceId) = 0;

    /**
    * 5.3 ��ȡ��ǰʹ�õ�����ͷ
    *
    * @return ITRTCDeviceInfo �豸��Ϣ���ܻ�ȡ�豸 ID ���豸����
    */
    virtual ITRTCDeviceInfo* getCurrentCameraDevice() = 0;
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ��������Ƶ�豸��ؽӿں���
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name ��Ƶ�豸��ؽӿں���
    /// @{
    /**
    * 6.1 ��ȡ��˷��豸�б�
    *
    *  ʾ�����룺
    * <pre>
    *  ITRTCDeviceCollection * pDevice = m_pCloud->getMicDevicesList();
    *  for (int i = 0; i < pDevice->getCount(); i++)
    *  {
    *      std::wstring name = UTF82Wide(pDevice->getDeviceName(i));
    *  }
    *  pDevice->release();
    *  pDevice = null;
    * </pre>
    *
    * @return ��˷����������ָ�� ITRTCDeviceCollection*
    * @note ��� delete ITRTCDeviceCollection* ָ���������SDK ά�� ITRTCDeviceCollection ������������ڡ�
    */
    virtual ITRTCDeviceCollection* getMicDevicesList() = 0;

    /**
    * 6.2 ��ȡ��ǰѡ�����˷�
    *
    * @return ITRTCDeviceInfo �豸��Ϣ���ܻ�ȡ�豸 ID ���豸����
    */
    virtual ITRTCDeviceInfo* getCurrentMicDevice() = 0;

    /**
    * 6.3 ����Ҫʹ�õ���˷�
    *
    * ѡ��ָ������˷���Ϊ¼���豸�������øýӿ�ʱ��Ĭ��ѡ������Ϊ0����˷�
    *
    * @param micId �� getMicDevicesList �еõ����豸 ID
    */
    virtual void setCurrentMicDevice(const char* micId) = 0;

    /**
    * 6.4 ��ȡϵͳ��ǰ��˷��豸����
    *
    * @note ��ѯ����ϵͳӲ��������С��
    *
    * @return ����ֵ����Χ��0 - 100
    */
    virtual uint32_t getCurrentMicDeviceVolume() = 0;

    /**
    * 6.5 ����ϵͳ��ǰ��˷��豸������
    *
    * @note �ýӿڵĹ����ǵ���ϵͳ�ɼ�����������û�ֱ�ӵ��� WIN ϵͳ���õĲɼ�����ʱ���ýӿڵ����ý���ᱻ�û��Ĳ��������ǡ�
    *
    * @param volume ��˷�����ֵ����Χ0 - 100
    */
    virtual void setCurrentMicDeviceVolume(uint32_t volume) = 0;

    /**
    * 6.6 ��ȡ�������豸�б�
    *
    *  ʾ�����룺
    * <pre>
    *  ITRTCDeviceCollection * pDevice = m_pCloud->getSpeakerDevicesList();
    *  for (int i = 0; i < pDevice->getCount(); i++)
    *  {
    *      std::wstring name = UTF82Wide(pDevice->getDeviceName(i));
    *  }
    *  pDevice->release();
    *  pDevice = null;
    * </pre>
    *
    * @return ����������������ָ�� ITRTCDeviceCollection*
    * @note ��� delete ITRTCDeviceCollection* ָ���������SDK ά�� ITRTCDeviceCollection ������������ڡ�
    */
    virtual ITRTCDeviceCollection* getSpeakerDevicesList() = 0;

    /**
    * 6.7 ��ȡ��ǰ���������豸
    *
    * @return ITRTCDeviceInfo �豸��Ϣ���ܻ�ȡ�豸 ID ���豸����
    */
    virtual ITRTCDeviceInfo* getCurrentSpeakerDevice() = 0;

    /**
    * 6.8 ����Ҫʹ�õ�������
    *
    * @param speakerId �� getSpeakerDevicesList �еõ����豸 ID
    */
    virtual void setCurrentSpeakerDevice(const char* speakerId) = 0;

    /**
    * 6.9 ��ȡϵͳ��ǰ�������豸����
    *
    * @note ��ѯ����ϵͳӲ��������С��
    *
    * @return ��������������Χ0 - 100
    */
    virtual uint32_t getCurrentSpeakerVolume() = 0;

    /**
    * 6.10 ����ϵͳ��ǰ�������豸����
    *
    * @note �ýӿڵĹ����ǵ���ϵͳ��������������û�ֱ�ӵ��� WIN ϵͳ���õĲ�������ʱ���ýӿڵ����ý���ᱻ�û��Ĳ��������ǡ�
    *
    * @param volume ���õ���������������Χ0 - 100
    */
    virtual void setCurrentSpeakerVolume(uint32_t volume) = 0;
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ���ߣ�ͼ��ǰ������ؽӿں���
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name ������ؽӿں���
    /// @{
    /**
    * 7.1 �������ա����ס�����Ч������
    *
    * SDK �ڲ����������׷��ͬ��ĥƤ�㷨��һ������ȡ���С��⻬������������Ů�㳡��Ч���Ƚ����ԡ�
    * ��һ������ȡ������Ȼ����ĥƤ�㷨����ر������沿ϸ�ڣ����۸����ϻ������Ȼ��
    *
    * @param style     ���շ�񣬹⻬������Ȼ���⻬���ĥƤ�������ԣ��ʺ����ֳ�����
    * @param beauty    ���ռ���ȡֵ��Χ0 - 9��0��ʾ�رգ�1 - 9ֵԽ��Ч��Խ����
    * @param white     ���׼���ȡֵ��Χ0 - 9��0��ʾ�رգ�1 - 9ֵԽ��Ч��Խ����
    * @param ruddiness ���󼶱�ȡֵ��Χ0 - 9��0��ʾ�رգ�1 - 9ֵԽ��Ч��Խ���ԣ��ò�����δ��Ч
    */
    virtual void setBeautyStyle(TRTCBeautyStyle style, uint32_t beauty, uint32_t white, uint32_t ruddiness) = 0;

    /**
    * 7.2 ����ˮӡ
    *
    * ˮӡ��λ����ͨ�� xOffset, yOffset, fWidthRatio ��ָ���ġ�
    * - xOffset��ˮӡ�����꣬ȡֵ��ΧΪ0 - 1�ĸ�������
    * - yOffset��ˮӡ�����꣬ȡֵ��ΧΪ0 - 1�ĸ�������
    * - fWidthRatio��ˮӡ�Ĵ�С������ȡֵ��ΧΪ0 - 1�ĸ�������
    *
    * @param streamType Ҫ����ˮӡ��������(TRTCVideoStreamTypeBig��TRTCVideoStreamTypeSub)
    * @param srcData    ˮӡͼƬԴ���ݣ��� NULL ��ʾȥ��ˮӡ��
    * @param srcType    ˮӡͼƬԴ�������ͣ��� NULL ʱ���Ըò�����
    * @param nWidth     ˮӡͼƬ���ؿ�ȣ�Դ����Ϊ�ļ�·��ʱ���Ըò�����
    * @param nHeight    ˮӡͼƬ���ظ߶ȣ�Դ����Ϊ�ļ�·��ʱ���Ըò�����
    * @param xOffset    ˮӡ��ʾ�����Ͻ� x ��ƫ��
    * @param yOffset    ˮӡ��ʾ�����Ͻ� y ��ƫ��
    * @param fWidthRatio ˮӡ��ʾ�Ŀ��ռ�����ȱ�����ˮӡ���ò����ȱ���������ʾ��
    * @note ֻ֧����·��Ƶ��
    */
    virtual void setWaterMark(TRTCVideoStreamType streamType, const char* srcData, TRTCWaterMarkSrcType srcType, uint32_t nWidth, uint32_t nHeight, float xOffset, float yOffset, float fWidthRatio) = 0;

    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ���ˣ�������ؽӿں�������Ļ������Ƭ�ȣ�
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name ������ؽӿں���
    /// @{
    /**
    * 8.1 ��ʼ��ȾԶ���û���������
    *
    * ��Ӧ�� startRemoteView() ������ʾ�����棬�ýӿ�ֻ��������ʾ��·����Ļ����Զ�̲�Ƭ�����档
    *
    * @param userId  �Է����û���ʶ
    * @param rendHwnd ��Ⱦ����� HWND
    * @note ���� onUserSubStreamAvailable �ص����ٵ�������ӿڡ�
    */
    virtual void startRemoteSubStreamView(const char* userId, HWND rendHwnd) = 0;

    /**
    * 8.2 ֹͣ��ʾԶ���û�����Ļ�����档
    * @param userId �Է����û���ʶ
    */
    virtual void stopRemoteSubStreamView(const char* userId) = 0;

    /**
    * 8.3 ���ø����������Ⱦģʽ
    *
    * ��Ӧ�� setRemoteViewFillMode() ������Զ�˵���·���棬�ýӿ���������Զ�˵ĸ�·����Ļ����Զ�̲�Ƭ�����档
    *
    * @param userId �û��� ID
    * @param mode ��䣨������ܻᱻ����ü�������Ӧ��������ܻ��кڱߣ���Ĭ��ֵ��TRTCVideoFillMode_Fit
    */
    virtual void setRemoteSubStreamViewFillMode(const char* userId, TRTCVideoFillMode mode) = 0;

    /**
    * 8.4 ������Ļ�������˳ʱ����ת�Ƕ�
    *
    * ��Ӧ�� setRemoteViewRotation() �����������������ת�Ƕȣ��ýӿ���������Զ�˵ĸ�·����Ļ����Զ�̲�Ƭ�����档
    *
    * @param userId �û� ID
    * @param rotation ֧��90��180��270��ת�Ƕ�
    */
    virtual void setRemoteSubStreamViewRotation(const char* userId, TRTCVideoRotation rotation) = 0;

    /**
    * 8.5 ö�ٿɹ���Ĵ����б�
    *
    * �����Ҫ������ App ������Ļ�����ܣ�һ����Ҫ����ʾһ������ѡ����棬�����û�����ѡ��ϣ������Ĵ��ڡ�
    * ͨ�����º����������Ի�ÿɷ����ڵ� ID�����͡����������Լ�����ͼ��
    * �õ���Щ��Ϣ�����Ϳ���ʵ��һ������ѡ����棬��Ȼ����Ҳ����ʹ�������� Demo Դ�����Ѿ�ʵ�ֺõ�һ�����档
    *
    * @note ���ص��б��а�����Ļ��Ӧ�ô��ڣ���Ļ�����б��ǰ�漸��Ԫ���С�
    * @note ��� delete ITRTCScreenCaptureSourceList*ָ���������SDK ά�� ITRTCScreenCaptureSourceList ������������ڡ�
    *
    * @param thumbSize ָ��Ҫ��ȡ�Ĵ�������ͼ��С������ͼ�����ڻ����ڴ���ѡ�������
    * @param iconSize  ָ��Ҫ��ȡ�Ĵ���ͼ���С
    *
    * @return �����б������Ļ
    */
    virtual ITRTCScreenCaptureSourceList* getScreenCaptureSources(const SIZE &thumbSize, const SIZE &iconSize) = 0;

    /**
    * 8.6 ������Ļ����������÷�������Ļ���������Ҳ���Ե���
    *
    * �������������Ļ����Ĺ����У��л���Ҫ����Ĵ��ڣ������ٴε����������������Ҫ���¿�����Ļ����
    *
    * ֧���������������
    * - ����������Ļ��sourceInfoList �� type Ϊ Screen �� source��captureRect ��Ϊ { 0, 0, 0, 0 }
    * - ����ָ������sourceInfoList �� type Ϊ Screen �� source��captureRect ��Ϊ�� NULL������ { 100, 100, 300, 300 }
    * - �����������ڣ�sourceInfoList �� type Ϊ Window �� source��captureRect ��Ϊ { 0, 0, 0, 0 }
    * - ����������sourceInfoList �� type Ϊ Window �� source��captureRect ��Ϊ�� NULL������ { 100, 100, 300, 300 }
    *
    *
    * @param source            ָ������Դ
    * @param captureRect       ָ�����������
    * @param captureMouse      ָ���Ƿ񲶻����ָ��
    * @param highlightWindow   ָ���Ƿ�������ڹ���Ĵ��ڣ��Լ�������ͼ���ڵ�ʱ�����ڵ�������ʾ�û������ڵ�
    *
    */
    virtual void selectScreenCaptureTarget(const TRTCScreenCaptureSourceInfo &source, const RECT& captureRect, bool captureMouse = true, bool highlightWindow = true) = 0;

    /**
    * 8.7 ������Ļ����
    * @param rendHwnd ����Ԥ������� HWND
    */
    virtual void startScreenCapture(HWND rendHwnd) = 0;

    /**
    * 8.8 ��ͣ��Ļ����
    */
    virtual void pauseScreenCapture() = 0;

    /**
    * 8.9 �ָ���Ļ����
    */
    virtual void resumeScreenCapture() = 0;

    /**
    * 8.10 ֹͣ��Ļ�ɼ�
    */
    virtual void stopScreenCapture() = 0;

    /**
    * 8.11 ������Ļ����ı���������
    *
    * ��Ӧ�� setVideoEncoderParam() ������·����ı����������ú������������ø�·����Ļ����Զ�̲�Ƭ���ı��������
    * �����þ�����Զ���û������Ļ���������ͬʱҲ���ƶ�¼�Ƴ�����Ƶ�ļ��Ļ���������
    *
    * @param params   �������������������ο� TRTCCloudDef.h �е� TRTCVideoEncParam ����
    */
    virtual void setSubStreamEncoderParam(const TRTCVideoEncParam& params) = 0;

    /**
    * 8.12 ���ø����Ļ���������С
    *
    * �����ֵԽ�ߣ���·������ռ�Ⱦ�Լ�ߣ���˷�����ռ�Ⱦ�ԽС�����Բ��Ƽ����õ�̫�󣬷�����˷�������ͱ�ѹ���ˡ�
    *
    * @param volume ���õĻ���������С����Χ0 - 100
    */
    virtual void setSubStreamMixVolume(uint32_t volume) = 0;

    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ���ţ��Զ���ɼ�����Ⱦ
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name �Զ���ɼ�����Ⱦ
    /// @{

    /**
    * 9.1 ������Ƶ�Զ���ɼ�ģʽ
    *
    * ������ģʽ��SDK ��������ԭ�е���Ƶ�ɼ����̣�ֻ��������ͷ���������
    * ����Ҫ�� sendCustomVideoData() ���ϵ��� SDK �����Լ��ɼ�����Ƶ���档
    *
    * @param enable �Ƿ����ã�Ĭ��ֵ��false
    */
    virtual void enableCustomVideoCapture(bool enable) = 0;

    /**
    * 9.2 �� SDK Ͷ���Լ��ɼ�����Ƶ����
    *
    * TRTCVideoFrame �Ƽ�������д��ʽ�������ֶβ���Ҫ��д����
    * - pixelFormat����֧�� LiteAVVideoPixelFormat_I420��
    * - bufferType����֧�� LiteAVVideoBufferType_Buffer��
    * - data����Ƶ֡ buffer��
    * - length����Ƶ֡���ݳ��ȣ�I420 ��ʽ�£���ֵ���ڣ�width �� height �� 3 / 2��
    * - width����Ƶͼ�񳤶ȡ�
    * - height����Ƶͼ���ȡ�
    * - timestamp����� timestamp ��������ȣ�������Ӱ������ͬ����¼�Ƴ��� MP4 ������
    *
    * �ο��ĵ���[�Զ���ɼ�����Ⱦ](https://cloud.tencent.com/document/product/647/34066)��
    *
    * @param frame ��Ƶ���ݣ�֧�� I420 ��ʽ���ݡ�
    * @note - SDK �ڲ���֡�ʿ����߼���Ŀ��֡�������� setVideoEncoderParam �����õ�Ϊ׼��̫����Զ���֡��̫������Զ���֡��
    * @note - �������� frame �е� timestamp Ϊ 0���൱���� SDK �Լ�����ʱ��������롰���ȡ��ؿ��� sendCustomVideoData �ĵ��ü��������ᵼ����Ƶ֡�ʲ��ȶ���
    */
    virtual void sendCustomVideoData(TRTCVideoFrame* frame) = 0;

    /**
    * 9.3 ������Ƶ�Զ���ɼ�ģʽ
    * ������ģʽ��SDK ֹͣ����ԭ�е���Ƶ�ɼ����̣�ֻ��������ͷ���������
    * ����Ҫ�� sendCustomAudioData() ���ϵ��� SDK �����Լ��ɼ�����Ƶ���ݡ�
    *
    * @param enable �Ƿ����ã�Ĭ��ֵ��false
    */
    virtual void enableCustomAudioCapture(bool enable) = 0;

    /**
    * 9.4 �� SDK Ͷ���Լ��ɼ�����Ƶ����
    *
    * TRTCAudioFrame �Ƽ�������д��ʽ�������ֶβ���Ҫ��д����
    * - audioFormat����֧�� LiteAVAudioFrameFormatPCM��
    * - data����Ƶ֡ buffer��
    * - length����Ƶ֡���ݳ��ȣ��Ƽ�ÿ֡20ms����������PCM��ʽ��48000�����ʡ���������֡���ȣ�48000 �� 0.02s �� 1 �� 16bit = 15360bit = 1920�ֽڡ���
    * - sampleRate�������ʣ���֧��48000��
    * - channel��Ƶ��������������������������ǽ���ģ�����������1�� ˫������2��
    * - timestamp����� timestamp ��������ȣ�������Ӱ������ͬ����¼�Ƴ��� MP4 ������
    *
    * �ο��ĵ���[�Զ���ɼ�����Ⱦ](https://cloud.tencent.com/document/product/647/34066)��
    *
    * @param frame ��Ƶ֡����֧�� LiteAVAudioFrameFormatPCM ��ʽ��Ŀǰֻ֧�ֵ���������֧��48K�����ʣ�LiteAVAudioFrameFormatPCM ��ʽ��
    * @note �������� frame �е� timestamp Ϊ 0���൱���� SDK �Լ�����ʱ��������롰���ȡ��ؿ��� sendCustomAudioData �ĵ��ü��������ᵼ�������϶�������
    */
    virtual void sendCustomAudioData(TRTCAudioFrame* frame) = 0;

    /**
    * 9.5 ���ñ�����Ƶ�Զ�����Ⱦ
    *
    * @note              ���ô˷�����SDK �ڲ���Ѳɼ��������ݻص�������SDK ���� HWND ��Ⱦ�߼�
                         ���� setLocalVideoRenderCallback(TRTCVideoPixelFormat_Unknown, TRTCVideoBufferType_Unknown, nullptr) ֹͣ�ص�
    * @param pixelFormat ָ���ص������ظ�ʽ
    * @param bufferType  ָ����Ƶ���ݽṹ����
    * @param callback    �Զ�����Ⱦ�ص�
    * @return 0���ɹ���<0������
    */
    virtual int setLocalVideoRenderCallback(TRTCVideoPixelFormat pixelFormat, TRTCVideoBufferType bufferType, ITRTCVideoRenderCallback* callback) = 0;

    /**
    * 9.6 ����Զ����Ƶ�Զ�����Ⱦ
    *
    * �˷���ͬ setLocalVideoRenderDelegate����������һ���Ǳ��ػ������Ⱦ�ص��� һ����Զ�̻������Ⱦ�ص���
    *
    * @note              ���ô˷�����SDK �ڲ����Զ�˵����ݽ����ص�������SDK ���� HWND ��Ⱦ�߼�
                         ���� setRemoteVideoRenderCallback(userId, TRTCVideoPixelFormat_Unknown,  TRTCVideoBufferType_Unknown, nullptr) ֹͣ�ص���
    * @param userId      �û���ʶ
    * @param pixelFormat ָ���ص������ظ�ʽ
    * @param bufferType  ָ����Ƶ���ݽṹ����
    * @param callback    �Զ�����Ⱦ�ص�
    * @return 0���ɹ���<0������
    */
    virtual int setRemoteVideoRenderCallback(const char* userId, TRTCVideoPixelFormat pixelFormat, TRTCVideoBufferType bufferType, ITRTCVideoRenderCallback* callback) = 0;

    /**
    * 9.7 ������Ƶ���ݻص�
    *
    * ���ô˷�����SDK �ڲ��������ģ������ݣ�PCM ��ʽ���ص�������������
    * - onCapturedAudioFrame��������˷�ɼ�������Ƶ����
    * - onPlayAudioFrame������ǰ��ÿһ·Զ���û�����Ƶ����
    * - onMixedPlayAudioFrame����·��Ƶ���ݻ�Ϻ��������������ŵ���Ƶ����
    *
    * @param callback  ����֡���ݣ�PCM ��ʽ���Ļص���callback = nullptr ��ֹͣ�ص�����
    * @return 0���ɹ���<0������
    */
    virtual int setAudioFrameCallback(ITRTCAudioFrameCallback* callback) = 0;

    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ��ʮ���Զ�����Ϣ����
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name �Զ�����Ϣ����
    /// @{
    /**
    * 10.1 �����Զ�����Ϣ�������������û�
    *
    * �ýӿڿ��Խ�������Ƶ����ͨ����ǰ������������û��㲥���Զ�������ݣ�����Ϊ����������Ƶ����ͨ����
    * ������ϸ�����Զ�����Ϣ�ķ���Ƶ�ʺ���Ϣ��Ĵ�С�������Ӱ������Ƶ���ݵ����������߼�����ɲ�ȷ���Ե����⡣
    *
    * @param cmdId    ��Ϣ ID��ȡֵ��ΧΪ1 - 10
    * @param data     �����͵���Ϣ�����֧��1KB��1000�ֽڣ������ݴ�С
    * @param dataSize �����͵����ݴ�С
    * @param reliable �Ƿ�ɿ����ͣ��ɿ����͵Ĵ����ǻ�����һ������ʱ����Ϊ���ն�Ҫ�ݴ�һ��ʱ����������ȴ��ش�
    * @param ordered  �Ƿ�Ҫ�����򣬼��Ƿ�Ҫ����ն˽��յ�����˳��ͷ��Ͷ˷��͵�˳��һ�£�������һ���Ľ�����ʱ����Ϊ�ڽ��ն���Ҫ�ݴ沢������Щ��Ϣ
    * @return true����Ϣ�Ѿ�������false����Ϣ����ʧ��
    *
    * @note ���ӿ����������ƣ�
    *       - ������Ϣ�������������û���ÿ������ܷ���30����Ϣ��
    *       - ÿ�������Ϊ1KB����������п��ܻᱻ�м�·�������߷�����������
    *       - ÿ���ͻ���ÿ������ܷ����ܼ�8KB���ݡ�
    *       - �� reliable �� ordered ͬʱ����Ϊ true �� false���ݲ�֧�ֽ������á�
    *       - ǿ�ҽ��鲻ͬ���͵���Ϣʹ�ò�ͬ�� cmdID������������Ҫ�����������¼�С��Ϣʱ�ӡ�
    */
    virtual bool sendCustomCmdMsg(uint32_t cmdId, const uint8_t* data, uint32_t dataSize, bool reliable, bool ordered) = 0;

    /**
    * 10.2 ��С���������Զ�������Ƕ����Ƶ֡��
    *
    * �� sendCustomCmdMsg ��ԭ��ͬ��sendSEIMsg �ǽ�����ֱ��������Ƶ����ͷ�С���ˣ���ʹ��Ƶ֡����·����ֱ�� CDN �ϣ�
    * ��Щ����Ҳ��һֱ���ڡ���������Ҫ������Ƕ����Ƶ֡�У��������ݱ�����̫���Ƽ������ֽھͺá�
    *
    * ������÷��ǰ��Զ����ʱ�����timstamp���� sendSEIMsg Ƕ����Ƶ֡�У����ַ��������ô����ǿ���ʵ����Ϣ�ͻ�����������롣
    *
    * @param data          �����͵����ݣ����֧��1kb��1000�ֽڣ������ݴ�С
    * @param dataSize      �����͵����ݴ�С
    * @param repeatCount   �������ݴ���
    * @return true����Ϣ��ͨ�����ƣ��ȴ�������Ƶ֡���ͣ�false:��Ϣ�����Ʒ���
    *
    * @note ���ӿ����������ƣ�
    *       - �����ڽӿڵ�����󲻻ᱻ��ʱ���ͳ�ȥ�����Ǵ���һ֡��Ƶ֡��ʼ������Ƶ֡�з��͡�
    *       - ������Ϣ�������������û���ÿ������ܷ���30����Ϣ���� sendCustomCmdMsg �������ƣ���
    *       - ÿ�������Ϊ1KB�������ʹ������ݣ��ᵼ����Ƶ�������󣬿��ܵ�����Ƶ�����½��������٣��� sendCustomCmdMsg �������ƣ���
    *       - ÿ���ͻ���ÿ������ܷ����ܼ�8KB���ݣ��� sendCustomCmdMsg �������ƣ���
    *       - ��ָ����η��ͣ�repeatCount>1���������ݻᱻ���ں��������� repeatCount ����Ƶ֡�з��ͳ�ȥ��ͬ���ᵼ����Ƶ��������
    *       - ��� repeatCount>1����η��ͣ�������Ϣ onRecvSEIMsg �ص�Ҳ���ܻ��յ������ͬ����Ϣ����Ҫȥ�ء�
    */
    virtual bool sendSEIMsg(const uint8_t* data, uint32_t dataSize, int32_t repeatCount) = 0;
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ��ʮһ������������ؽӿں���
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name ����������ؽӿں���
    /// @{
    /**
    * 11.1 �������ű�������
    *
    * @param path �����ļ�·����֧�ֵ��ļ���ʽ��aac, mp3��
    */
    virtual void playBGM(const char* path) = 0;

    /**
    * 11.2 ֹͣ���ű�������
    */
    virtual void stopBGM() = 0;

    /**
    * 11.3 ��ͣ���ű�������
    */
    virtual void pauseBGM() = 0;

    /**
    * 11.4 �������ű�������
    */
    virtual void resumeBGM() = 0;

    /**
    * 11.5 ��ȡ�����ļ���ʱ������λ����
    *
    * @param path �����ļ�·������� path Ϊ�գ���ô���ص�ǰ���ڲ��ŵ� music ʱ��
    * @return     �ɹ�����ʱ����ʧ�ܷ���-1
    */
    virtual uint32_t getBGMDuration(const char* path) = 0;

    /**
    * 11.6 ���� BGM ���Ž���
    *
    * @param pos ��λ����
    */
    virtual void setBGMPosition(uint32_t pos) = 0;

    /**
    * 11.7 ���ñ������ֲ��������Ĵ�С
    *
    * ���ű������ֻ���ʱʹ�ã��������Ʊ������ֲ��������Ĵ�С��
    * �ýӿڻ�ͬʱ����Զ�˲��������Ĵ�С�ͱ��ز��������Ĵ�С��
    * ��˵��øýӿں�setBGMPlayoutVolume��setBGMPublishVolume���õ�����ֵ�ᱻ����
    *
    * @param volume ������С��100Ϊ����������ȡֵ��ΧΪ0 - 100��Ĭ��ֵ��100
    */
    virtual void setBGMVolume(uint32_t volume) = 0;

    /**
    * 11.8 ���ñ������ֱ��ز��������Ĵ�С
    *
    * ���ű������ֻ���ʱʹ�ã��������Ʊ��������ڱ��ز���ʱ��������С��
    *
    * @param volume ������С��100Ϊ����������ȡֵ��ΧΪ0 - 100��Ĭ��ֵ��100
    */
    virtual void setBGMPlayoutVolume(uint32_t volume) = 0;

    /**
    * 11.9 ���ñ�������Զ�˲��������Ĵ�С
    *
    * ���ű������ֻ���ʱʹ�ã��������Ʊ���������Զ�˲���ʱ��������С��
    *
    * @param volume ������С��100Ϊ����������ȡֵ��ΧΪ0 - 100��Ĭ��ֵ��100
    */
    virtual void setBGMPublishVolume(uint32_t volume) = 0;

#ifndef _WIN64
    /**
    * 11.10 ��ϵͳ�����ɼ���64λ SDK �в�֧��ϵͳ����������
    *
    * ��������Բɼ���������ϵͳ�Ĳ���������path Ϊ�գ���ĳһ����������path ��Ϊ�գ���������
    * ��������뵽��ǰ��˷�ɼ���������һ���͵��ƶˡ�
    *
    * @param path
    *    - path Ϊ�գ�����ɼ���������ϵͳ��������
    *    - path ��д exe ������ QQ���֣����ڵ�·�������������˳���ֻ�ɼ��˳����������
    *
    */
    virtual void startSystemAudioLoopback(const char* path = nullptr) = 0;

    /**
    * 11.11 �ر�ϵͳ�����ɼ���
    */
    virtual void stopSystemAudioLoopback() = 0;

    /**
    * 11.12 ����ϵͳ�����ɼ���������
    *
    * @param volume ������С��ȡֵ��ΧΪ0 - 100��
    */
    virtual void setSystemAudioLoopbackVolume(uint32_t volume) = 0;
#endif
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ��ʮ������Ч��ؽӿں���
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name ��Ч��ؽӿں���
    /// @{
    /**
    * 12.1 ������Ч
    *
    * ÿ����Ч����Ҫ��ָ������� ID��������ͨ���� ID ����Ч�Ŀ�ʼ��ֹͣ�������Ƚ������á�
    * ֧�ֵ��ļ���ʽ��aac, mp3��
    *
    * @note ������ͬʱ���Ŷ����Ч������䲻ͬ�� ID ���в��š���Ϊʹ��ͬһ�� ID ���Ų�ͬ��Ч��SDK ����ֹͣ��һ�� ID ��Ӧ����Ч���ţ��������µ���Ч���š�
    *
    * @param effect ��Ч
    */
    virtual void playAudioEffect(TRTCAudioEffectParam* effect) = 0;

    /**
    * 12.2 ������Ч����
    *
    * @note �Ḳ��ͨ�� setAllAudioEffectsVolume ָ����������Ч������
    *
    * @param effectId ��Ч ID
    * @param volume   ������С��ȡֵ��ΧΪ0 - 100��Ĭ��ֵ��100
    */
    virtual void setAudioEffectVolume(int effectId, int volume) = 0;

    /**
    * 12.3 ֹͣ��Ч
    *
    * @param effectId ��Ч ID
    */
    virtual void stopAudioEffect(int effectId) = 0;

    /**
    * 12.4 ֹͣ������Ч
    */
    virtual void stopAllAudioEffects() = 0;

    /**
    * 12.5 ����������Ч������
    *
    * @note �ò����Ḳ��ͨ�� setAudioEffectVolume ָ���ĵ�����Ч������
    *
    * @param volume ������С��ȡֵ��ΧΪ0 - 100��Ĭ��ֵ��100
    */
    virtual void setAllAudioEffectsVolume(int volume) = 0;

    /**
    * 12.6 ��ͣ��Ч
    *
    * @param effectId ��Ч Id
    */
    virtual void pauseAudioEffect(int effectId) = 0;

    /**
    * 12.7 �ָ���Ч
    *
    * @param effectId ��Ч Id
    */
    virtual void resumeAudioEffect(int effectId) = 0;
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ��ʮ�����豸���������
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name �豸���������
    /// @{
    /**
    * 13.1 ��ʼ����������٣���Ƶͨ���ڼ�������ԣ�����Ӱ��ͨ��������
    *
    * ���ٽ�����������Ż� SDK �������ķ�����ѡ����ԣ�����Ƽ������û��״�ͨ��ǰ�Ƚ���һ�β��٣��⽫����������ѡ����ѵķ�������
    * ͬʱ��������Խ���ǳ������룬������ͨ����Ŀ�� UI ��ʾ�û�ѡ����õ����硣
    *
    * @note ���ٱ��������һ��������������Ҳ���������������������á�
    *
    * @param sdkAppId Ӧ�ñ�ʶ
    * @param userId �û���ʶ
    * @param userSig �û�ǩ��
    */
    virtual void startSpeedTest(uint32_t sdkAppId, const char* userId, const char* userSig) = 0;

    /**
    * 13.2 ֹͣ�������
    */
    virtual void stopSpeedTest() = 0;

    /**
    * 13.3 ��ʼ��������ͷ����
    *
    * �ᴥ�� onFirstVideoFrame �ص��ӿ�
    *
    * @note �ڲ��Թ����п���ʹ�� setCurrentCameraDevice �ӿ��л�����ͷ��
    * @param rendHwnd ����Ԥ������� HWND
    */
    virtual void startCameraDeviceTest(HWND rendHwnd) = 0;

    /**
    * 13.4 ֹͣ����ͷ����
    */
    virtual void stopCameraDeviceTest() = 0;

    /**
    * 13.5 ������˷����
    *
    * �ص��ӿ� onTestMicVolume ��ȡ��������
    *
    * �÷���������˷��Ƿ�������������volume ��ȡֵ��ΧΪ0 - 100��
    *
    * @param interval ����������ʾ��ʱ������ms�����������õ����� 200 ����
    */
    virtual void startMicDeviceTest(uint32_t interval) = 0;

    /**
    * 13.6 ֹͣ��˷����
    */
    virtual void stopMicDeviceTest() = 0;

    /**
    * 13.7 ��������������
    *
    * �ص��ӿ� onTestSpeakerVolume ��ȡ��������
    *
    * �÷�������ָ������Ƶ�ļ����Բ����豸�Ƿ����������������������������˵�������豸������������
    *
    * @param testAudioFilePath ��Ƶ�ļ��ľ���·����·���ַ���ʹ�� UTF-8 �����ʽ��֧���ļ���ʽ��WAV��MP3
    */
    virtual void startSpeakerDeviceTest(const char* testAudioFilePath) = 0;

    /**
    * 13.8 ֹͣ����������
    */
    virtual void stopSpeakerDeviceTest() = 0;
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ��ʮ�ģ�LOG ��ؽӿں���
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name LOG ��ؽӿں���
    /// @{
    /**
    * 14.1 ��ȡ SDK �汾��Ϣ
    *
    * @return UTF-8 ����İ汾�š�
    */
    virtual const char* getSDKVersion() = 0;

    /**
    * 14.2 ���� Log �������
    *
    * @param level �μ� TRTCLogLevel��Ĭ��ֵ��TRTCLogLevelNone
    */
    virtual void setLogLevel(TRTCLogLevel level) = 0;

    /**
    * 14.3 ���û���ÿ���̨��־��ӡ
    *
    * @param enabled ָ���Ƿ����ã�Ĭ��Ϊ��ֹ״̬
    */
    virtual void setConsoleEnabled(bool enabled) = 0;

    /**
    * 14.4 ���û���� Log �ı���ѹ��
    *
    *  ����ѹ����Log �洢������Լ�С������Ҫ��Ѷ���ṩ�� Python �ű���ѹ������Ķ���
    *  ����ѹ����Log �������Ĵ洢������ֱ���ü��±����Ķ�����ռ�ÿռ�ϴ�
    *
    * @param enabled ָ���Ƿ����ã�Ĭ��Ϊ��ֹ״̬
    */
    virtual void setLogCompressEnabled(bool enabled) = 0;

    /**
    * 14.5 ������־����·��
    *
    * @note ��־�ļ�Ĭ�ϱ����� C:/Users/[ϵͳ�û���]/AppData/Roaming/Tencent/liteav/log���� %appdata%/Tencent/liteav/log �£������޸ģ����������з���ǰ���á�
    * @param path �洢��־���ļ��У����� "D:\\Log"��UTF-8 ����
    */
    virtual void setLogDirPath(const char* path) = 0;

    /**
    * 14.6 ������־�ص�
    *
    * @param callback ��־�ص�
    */
    virtual void setLogCallback(ITRTCLogCallback* callback) = 0;

    /**
    * 14.7 ��ʾ�Ǳ���
    *
    * �Ǳ�����״̬ͳ�ƺ��¼���Ϣ���� view��������ԡ�
    *
    * @param showType 0������ʾ��1����ʾ����棻2����ʾȫ���棬Ĭ��Ϊ����ʾ
    */
    virtual void showDebugView(int showType) = 0;

    /**
    * 14.8 ����ʵ���� API �ӿ�
    *
    * @note �ýӿ����ڵ���һЩʵ���Թ���
    * @param jsonStr �ӿڼ����������� JSON �ַ���
    */
    virtual void callExperimentalAPI(const char *jsonStr) = 0;
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      ��ʮ�壩 ���ýӿں���
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name ���ýӿں���
    /// @{

    /**
    * @deprecated �� v6.9 �汾��ʼ����
    * @note ʹ�� setAudioCaptureVolume �ӿ������ 
    */
    virtual __declspec(deprecated("warning :setMicVolumeOnMixing is deprecated, use setAudioCaptureVolume instead.")) \
        void setMicVolumeOnMixing(uint32_t volume) {};
    /// @}
};
/// @}

#endif /* __ITRTCCLOUD_H__ */
