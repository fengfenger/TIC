/**
* Module:   TXLiteAVBase @ liteav
*
* Function: SDK ��������ͷ�ļ�
*
*/

#ifndef __TXLITEAVBASE_H__
#define __TXLITEAVBASE_H__

#include <stdint.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

#ifdef LITEAV_EXPORTS
#define LITEAV_API __declspec(dllexport)
#else
#define LITEAV_API __declspec(dllimport)
#endif

extern "C" {
    /// @name SDK �����������ܽӿ�
    /// @{
    /**
    * \brief ��ȡ SDK �汾��
    *
    * \return ���� UTF-8 ����İ汾�š�
    */
    LITEAV_API const char* getLiteAvSDKVersion();
    /// @}
}

/// @addtogroup TRTCCloudDef_cplusplus
/// @{

/**
* ��Ƶ���ݽṹ����
*/
enum LiteAVVideoBufferType
{
    LiteAVVideoBufferType_Unknown = 0,
    LiteAVVideoBufferType_Buffer = 1,       ///< ������Buffer����
    LiteAVVideoBufferType_Texture = 3,      ///< ��������
};

/**
* ��Ƶ֡�ĸ�ʽ
*/
enum LiteAVVideoPixelFormat
{
    LiteAVVideoPixelFormat_Unknown = 0,
    LiteAVVideoPixelFormat_I420 = 1,        ///< I420
    LiteAVVideoPixelFormat_Texture_2D = 2,  ///< OpenGL 2D ����
    LiteAVVideoPixelFormat_BGRA32 = 3,      ///< BGRA32
};

/**
* ��Ƶ֡�ĸ�ʽ
*/
enum LiteAVAudioFrameFormat
{
    LiteAVAudioFrameFormatNone = 0,
    LiteAVAudioFrameFormatPCM,              ///< PCM��ÿ��������ռ16bit��������
};

/**
* ��Ƶ������ת����
*/
enum LiteAVVideoRotation
{
    LiteAVVideoRotation0 = 0,             ///< ˳ʱ����ת0��
    LiteAVVideoRotation90 = 1,             ///< ˳ʱ����ת90��
    LiteAVVideoRotation180 = 2,             ///< ˳ʱ����ת180��
    LiteAVVideoRotation270 = 3,             ///< ˳ʱ����ת270��
};

/*************************************************************************************************************************************************************************/

/**
* ��Ƶ֡����
*/
struct LiteAVVideoFrame
{
    LiteAVVideoPixelFormat videoFormat;     ///< ��Ƶ֡�ĸ�ʽ
    LiteAVVideoBufferType bufferType;       ///< ��Ƶ���ݽṹ����
    char* data;                             ///< ��Ƶ���ݣ��ֶ�bufferType��LiteAVVideoBufferType_Bufferʱ��Ч
    int textureId;                          ///< ��Ƶ����ID���ֶ�bufferType��LiteAVVideoBufferType_Textureʱ��Ч
    uint32_t length;                        ///< ��Ƶ���ݵĳ��ȣ���λ���ֽڣ�����i420���ԣ� length = width * height * 3 / 2������BGRA32���ԣ� length = width * height * 4
    uint32_t width;                         ///< ����Ŀ��
    uint32_t height;                        ///< ����ĸ߶�
    uint64_t timestamp;                     ///< ʱ�������λms
    LiteAVVideoRotation rotation;           ///< ������ת�Ƕ�

    LiteAVVideoFrame()
        : videoFormat(LiteAVVideoPixelFormat_Unknown)
        , data(NULL)
        , textureId(-1)
        , length(0)
        , width(640)
        , height(360)
        , timestamp(0)
        , rotation(LiteAVVideoRotation0)
    {

    }
};

/**
* ��Ƶ֡����
*/
struct LiteAVAudioFrame
{
    LiteAVAudioFrameFormat audioFormat;     ///< ��Ƶ֡�ĸ�ʽ
    char* data;                             ///< ��Ƶ����
    uint32_t length;                        ///< ��Ƶ���ݵĳ���
    uint32_t sampleRate;                    ///< ������
    uint32_t channel;                       ///< ������
    uint64_t timestamp;                     ///< ʱ�������λms

    LiteAVAudioFrame()
        : audioFormat(LiteAVAudioFrameFormatNone)
        , data(NULL)
        , length(0)
        , sampleRate(48000)
        , channel(1)
        , timestamp(0)
    {

    }
};




/////////////////////////////////////////////////////////////////////////////////
/// \brief����Ļ��������Ϣ TRTCScreenCaptureSourceInfo��
///
/// \desc ������ͨ�� getScreenCaptureSources() ö�ٿɹ���Ĵ����б��б�ͨ�� ITRTCScreenCaptureSourceList ����
/////////////////////////////////////////////////////////////////////////////////
enum LiteAVScreenCaptureSourceType
{
    LiteAVScreenCaptureSourceTypeUnknown = -1,
    LiteAVScreenCaptureSourceTypeWindow = 0,   ///< �÷���Ŀ����ĳһ��Windows����
    LiteAVScreenCaptureSourceTypeScreen = 1,   ///< �÷���Ŀ��������Windows����
    LiteAVScreenCaptureSourceTypeCustom = 2,
};

struct LiteAVImageBuffer
{
    const char* buffer;      ///< ͼ����
    uint32_t length;         ///< ͼ�����С
    uint32_t width;          ///< ͼ��
    uint32_t height;         ///< ͼ��
    LiteAVImageBuffer()
        : buffer(NULL)
        , length(0)
        , width(0)
        , height(0)
    {};
};

struct LiteAVScreenCaptureSourceInfo {
    LiteAVScreenCaptureSourceType type;              ///< �ɼ�Դ����
    HWND            sourceId;                        ///< �ɼ�ԴID�����ڴ��ڣ����ֶ�ָʾ���ھ����������Ļ�����ֶ�ָʾ��ĻID
    const char*     sourceName;                      ///< �ɼ�Դ���ƣ�UTF8����
    LiteAVImageBuffer thumbBGRA;                     ///< ����ͼ����
    LiteAVImageBuffer iconBGRA;                      ///< ͼ������
    LiteAVScreenCaptureSourceInfo()
        : type(LiteAVScreenCaptureSourceTypeUnknown)
        , sourceId(0)
        , sourceName(NULL)
    {};
};

class ILiteAVScreenCaptureSourceList
{
protected:
    virtual ~ILiteAVScreenCaptureSourceList() {}
public:
    /**
    * \return ���ڸ���
    */
    virtual uint32_t getCount() = 0;
    /**
    * \return ������Ϣ
    */
    virtual LiteAVScreenCaptureSourceInfo getSourceInfo(uint32_t index) = 0;
    /**
    * \brief �����괰���б�󣬵���release�ͷ���Դ��
    */
    virtual void release() = 0;
};

/////////////////////////////////////////////////////////////////////////////////
/// \brief����ȡSDK��ǰʹ���豸��Ϣ ILiteAVDeviceInfo��
///
/// \desc ������ͨ�� setCurrentCameraDevice()/getCurrentMicDevice()/getCurrentSpeakerDevice ��ȡ��ǰʹ���豸��
/////////////////////////////////////////////////////////////////////////////////
class ILiteAVDeviceInfo
{
protected:
    virtual ~ILiteAVDeviceInfo() {}
public:
    /**
    * \return �豸���ƣ��ַ������ʽ��UTF-8
    */
    virtual const char* getDeviceName() = 0;

    /**
    * \return �豸PID���ַ������ʽ��UTF-8
    */
    virtual const char* getDevicePID() = 0;

    /**
    * \brief ��ȡ���豸��Ϣ�󣬵���release�ͷ���Դ��
    */
    virtual void release() = 0;
};

/////////////////////////////////////////////////////////////////////////////////
/// \brief����ȡSDK�豸��Ϣ�ӿ� ITRTCDeviceCollection��
///
/// \desc ������ͨ�� getMicDevicesList()/getSpeakerDevicesList()/getMicDevicesList ö��Ӳ���豸�б��б�ͨ�� ITRTCDeviceCollection ����
/////////////////////////////////////////////////////////////////////////////////
class ILiteAVDeviceCollection
{
protected:
    virtual ~ILiteAVDeviceCollection() {}
public:
    /**
    * \return �豸����
    */
    virtual uint32_t getCount() = 0;

    /**
    * \return �豸���ƣ��ַ������ʽ��UTF-8
    */
    virtual const char* getDeviceName(uint32_t index) = 0;

    /**
    * \return �豸PID���ַ������ʽ��UTF-8
    */
    virtual const char* getDevicePID(uint32_t index) = 0;

    /**
    * \brief �������豸�󣬵���release�ͷ���Դ��
    */
    virtual void release() = 0;
};



/*************************************************************************************************************************************************************************/

class ILiteAVStreamDataSource
{
public:
    /**
    * \brief SDK�ڳɹ�������Ƶλ�����ø÷�����֪ͨ����Դ��ʼ����
    */
    virtual void onStart() = 0;

    /**
    * \brief SDK�ڲ�����Ҫ�õ�������Դ��ʱ�����ø÷�����֪ͨ����Դֹͣ����
    */
    virtual void onStop() = 0;

    /**
    * \brief SDK����Ҫ��Ƶ֡ʱ���ø÷�����������Ƶ֡
    *
    * \param frame ���ڴ�����󵽵���Ƶ֡������
    *                   bufferType      ��Ч����ʱֻ֧��LiteAVVideoBufferType_Buffer����
    *                   videoFormat     ����
    *                   data            SDK�Ѵ�����buffer������Դ��������Ƶ���ݿ�������
    *                   textureId       ��Ч
    *                   length          �����ʼֵָʾdata�ֶο��ÿռ��С������дΪ�������ݴ�С
    *                   width           ����
    *                   height          ����
    *                   timestamp       ��ѡ
    *                   rotation        ��ѡ
    *
    * \return �������ݴ�С��<0 ��ʾ����
    */
    virtual int onRequestVideoFrame(LiteAVVideoFrame &frame) = 0;

    /**
    * \brief SDK����Ҫ��Ƶ֡ʱ���ø÷�����������Ƶ֡
    *
    * \param frame ���ڴ�����󵽵���Ƶ֡������
    *                   audioFormat     ��Ч����ʱֻ֧��LiteAVAudioFrameFormatPCM����
    *                   data            SDK�Ѵ�����buffer������Դ��������Ƶ���ݿ�������
    *                   length          �����ʼֵָʾdata�ֶο��ÿռ��С������дΪ�������ݴ�С
    *                   sampleRate      ����
    *                   channel         ����
    *                   timestamp       ��ѡ
    *
    * \return �������ݴ�С��<0 ��ʾ����
    */
    virtual int onRequestAudioFrame(LiteAVAudioFrame &frame) = 0;

public:
    typedef void(*OnDestoryCallback)(void*);

    ILiteAVStreamDataSource()
    {
        m_hOnDestoryCallbackMutex = CreateMutex(nullptr, FALSE, nullptr);
    }

    virtual ~ILiteAVStreamDataSource()
    {
        WaitForSingleObject(m_hOnDestoryCallbackMutex, INFINITE);
        if (m_pOnDestoryCallback)
        {
            m_pOnDestoryCallback(m_pOnDestoryCallbackParam);
        }
        ReleaseMutex(m_hOnDestoryCallbackMutex);
        CloseHandle(m_hOnDestoryCallbackMutex);
    }

    void setOnDestoryCallback(OnDestoryCallback callback, void* param)
    {
        WaitForSingleObject(m_hOnDestoryCallbackMutex, INFINITE);
        m_pOnDestoryCallback = callback;
        m_pOnDestoryCallbackParam = param;
        ReleaseMutex(m_hOnDestoryCallbackMutex);
    }
private:
    HANDLE m_hOnDestoryCallbackMutex = nullptr;
    OnDestoryCallback m_pOnDestoryCallback = nullptr;
    void *m_pOnDestoryCallbackParam = nullptr;

};
/// @}

#endif /* __TXLITEAVBASE_H__ */