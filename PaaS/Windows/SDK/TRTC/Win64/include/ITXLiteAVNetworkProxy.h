#ifndef __ITXLITEAVNETWORKPROXY_H__
#define __ITXLITEAVNETWORKPROXY_H__

#include "TXLiteAVBase.h"
class ITXNetworkProxy;

extern "C" {
    /**
    * ���ڶ�̬����dllʱ������TXNetworkProxy C++����
    *
    * @return TXNetworkProxy����ָ�룬ע�⣺delete ITXNetworkProxy*����������Ҫ����destroyTXNetworkProxy�ͷš�
    */
    LITEAV_API ITXNetworkProxy* createTXNetworkProxy();

    /**
    * ����ITXNetworkProxy����
    *
    * @param pTXNetworkProxy ������Ҫ�ͷŵĶ���ָ���ַ
    */
    LITEAV_API void destroyTXNetworkProxy(ITXNetworkProxy** pTXNetworkProxy);
}

class ITXNetworkProxy
{
protected:
    virtual ~ITXNetworkProxy() {};
    
public:

    /////////////////////////////////////////////////////////////////////////////////
    //   
    //              SDK �����ܽӿ�
    //
    /////////////////////////////////////////////////////////////////////////////////
    /*
    * TRTCCloud ��������
    *
    * socks5 ����ģʽ������ socks5 tcp/udp ��������� ip �� port��
    * ���ô˽ӿں�������������������ʹ�ý�����������������Ƶ������Զ������Ƶ���˷��ȹ���
    * ϸ����ο�TRTC ������<http://trtc-1252463788.file.myqcloud.com/proxy/proxy_server_deploy.zip>

    *
    * @param ip ����������� ip ��ַ
    * @param port ����������Ķ˿�
    *
    * @note ���ӿ����������ƣ�
    *       - �˽ӿڱ����� getTRTCShareInstance ֮ǰ����,���Ҳ�֧�ֶ�̬���ã���ȷ���ڲ����� tcp/udp ���ݶ��ߴ����������
    *       - �����ֻ���� TRTCCloud����ֻ��Ҫ����Sock5����ӿڡ�
    */
    virtual void setSocks5Proxy(const char * ip, unsigned short port) = 0;

    /*
    * TXLivePusher/TXLivePlayer ��������
    *
    * nat�˿�ת������ģʽ������NAT�˿�ת������������� ip �� port��
    *
    * ITXLivePusher/ITXLivePlayer ʹ�ô˴���ģʽ���д�͸�����������ʹ�� ITRTCCloud ������Ҫ���ô˽ӿڡ�
    *
    * @param ip ����������� ip ��ַ
    * @param port ����������Ķ˿�
    *
    * @note ���ӿ����������ƣ�
    *       - �˽ӿڱ����� createTXLivePlayer/createTXLivePusher ֮ǰ���ã���ȷ���ڲ��������ݶ��ߴ����������
    *       - �����ֻ����ֱ�� SDK �Ĺ��ܣ���ֻ��Ҫ����NAT����ӿڡ�
    */
    virtual void setNATProxy(const char * ip, unsigned short port) = 0;
};

#endif //__ITXLITEAVNETWORKPROXY_H__