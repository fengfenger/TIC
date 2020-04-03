#ifndef __TXLITEAVCODE_H__
#define __TXLITEAVCODE_H__

/////////////////////////////////////////////////////////////////////////////////
//
//                     ������
//
/////////////////////////////////////////////////////////////////////////////////

typedef enum TXLiteAVError
{
    /////////////////////////////////////////////////////////////////////////////////
    //
    //       ����������
    //
    /////////////////////////////////////////////////////////////////////////////////
    ERR_NULL                                        = 0,        ///< �޴���

    /////////////////////////////////////////////////////////////////////////////////
    //
    //       ������enterRoom����ش�����
    //       NOTE: ͨ���ص����� TRTCCloudDelegate##onEnterRoom() �� TRTCCloudDelegate##OnError() ֪ͨ
    //
    /////////////////////////////////////////////////////////////////////////////////
    ERR_ROOM_ENTER_FAIL                             = -3301,    ///< ���뷿��ʧ��
    ERR_ENTER_ROOM_PARAM_NULL                       = -3316,    ///< ��������Ϊ�գ����� enterRoom:appScene: �ӿڵ����Ƿ�����Ч�� param
    ERR_SDK_APPID_INVALID                           = -3317,    ///< �������� sdkAppId ����
    ERR_ROOM_ID_INVALID                             = -3318,    ///< �������� roomId ����
    ERR_USER_ID_INVALID                             = -3319,    ///< �������� userID ����ȷ
    ERR_USER_SIG_INVALID                            = -3320,    ///< �������� userSig ����ȷ
    ERR_ROOM_REQUEST_ENTER_ROOM_TIMEOUT             = -3308,    ///< ���������ʱ����������
    ERR_SERVER_INFO_SERVICE_SUSPENDED               = -100013,  ///< ���񲻿��á����飺�ײͰ�ʣ��������Ƿ����0����Ѷ���˺��Ƿ�Ƿ��


    /////////////////////////////////////////////////////////////////////////////////
    //
    //       �˷���exitRoom����ش�����
    //       NOTE: ͨ���ص����� TRTCCloudDelegate##OnError() ֪ͨ
    //
    /////////////////////////////////////////////////////////////////////////////////
    ERR_ROOM_REQUEST_QUIT_ROOM_TIMEOUT              = -3325,    ///< �����˷���ʱ


    /////////////////////////////////////////////////////////////////////////////////
    //
    //       �豸������ͷ����˷硢����������ش�����
    //       NOTE: ͨ���ص����� TRTCCloudDelegate##OnError() ֪ͨ
    //
    /////////////////////////////////////////////////////////////////////////////////
    ERR_CAMERA_START_FAIL                           = -1301,    ///< ������ͷʧ�ܣ������� Windows �� Mac �豸������ͷ�����ó������������쳣�����ú����������豸�������������������߸������ó���
    ERR_CAMERA_NOT_AUTHORIZED                       = -1314,    ///< ����ͷ�豸δ��Ȩ��ͨ�����ƶ��豸���֣�������Ȩ�ޱ��û��ܾ���
    ERR_CAMERA_SET_PARAM_FAIL                       = -1315,    ///< ����ͷ�������ó���������֧�ֻ�������
    ERR_CAMERA_OCCUPY                               = -1316,    ///< ����ͷ���ڱ�ռ���У��ɳ��Դ���������ͷ
    ERR_MIC_START_FAIL                              = -1302,    ///< ����˷�ʧ�ܣ������� Windows �� Mac �豸����˷�����ó������������쳣�����ú����������豸�������������������߸������ó���
    ERR_MIC_NOT_AUTHORIZED                          = -1317,    ///< ��˷��豸δ��Ȩ��ͨ�����ƶ��豸���֣�������Ȩ�ޱ��û��ܾ���
    ERR_MIC_SET_PARAM_FAIL                          = -1318,    ///< ��˷����ò���ʧ��
    ERR_MIC_OCCUPY                                  = -1319,    ///< ��˷����ڱ�ռ���У������ƶ��豸����ͨ��ʱ������˷��ʧ��
    ERR_MIC_STOP_FAIL                               = -1320,    ///< ֹͣ��˷�ʧ��
    ERR_SPEAKER_START_FAIL                          = -1321,    ///< ��������ʧ�ܣ������� Windows �� Mac �豸�������������ó������������쳣�����ú����������豸�������������������߸������ó���
    ERR_SPEAKER_SET_PARAM_FAIL                      = -1322,    ///< ���������ò���ʧ��
    ERR_SPEAKER_STOP_FAIL                           = -1323,    ///< ֹͣ������ʧ��


    /////////////////////////////////////////////////////////////////////////////////
    //
    //       ��Ļ������ش�����
    //       NOTE: ͨ���ص����� TRTCCloudDelegate##OnError() ֪ͨ
    //
    /////////////////////////////////////////////////////////////////////////////////
    ERR_SCREEN_CAPTURE_START_FAIL                   = -1308,    ///< ��ʼ¼��ʧ�ܣ�������ƶ��豸���֣�������Ȩ�ޱ��û��ܾ��ˣ������ Windows �� Mac ϵͳ���豸���֣�����¼���ӿڵĲ����Ƿ����Ҫ��
    ERR_SCREEN_CAPTURE_UNSURPORT                    = -1309,    ///< ¼��ʧ�ܣ��� Android ƽ̨����Ҫ5.0���ϵ�ϵͳ
    ERR_SERVER_CENTER_NO_PRIVILEDGE_PUSH_SUB_VIDEO  = -102015,  ///< û��Ȩ�����и�·
    ERR_SERVER_CENTER_ANOTHER_USER_PUSH_SUB_VIDEO   = -102016,  ///< �����û��������и�·

    
    /////////////////////////////////////////////////////////////////////////////////
    //
    //       �������ش�����
    //       NOTE: ͨ���ص����� TRTCCloudDelegate##OnError() ֪ͨ
    //
    /////////////////////////////////////////////////////////////////////////////////
    ERR_VIDEO_ENCODE_FAIL                           = -1303,    ///< ��Ƶ֡����ʧ�ܣ����� iOS �豸�л�������Ӧ��ʱ��Ӳ���������ܱ�ϵͳ�ͷţ����л�����ʱ��Ӳ����������ǰ�����ܻ��׳�
    ERR_UNSUPPORTED_RESOLUTION                      = -1305,    ///< ��֧�ֵ���Ƶ�ֱ���
    ERR_AUDIO_ENCODE_FAIL                           = -1304,    ///< ��Ƶ֡����ʧ�ܣ����紫���Զ�����Ƶ���ݣ�SDK �޷�����
    ERR_UNSUPPORTED_SAMPLERATE                      = -1306,    ///< ��֧�ֵ���Ƶ������
    

    /////////////////////////////////////////////////////////////////////////////////
    //
    //       �Զ���ɼ���ش�����
    //       NOTE: ͨ���ص����� TRTCCloudDelegate##OnError() ֪ͨ
    //
    /////////////////////////////////////////////////////////////////////////////////
    ERR_PIXEL_FORMAT_UNSUPPORTED                    = -1327,    ///< ���õ� pixel format ��֧��
    ERR_BUFFER_TYPE_UNSUPPORTED                     = -1328,    ///< ���õ� buffer type ��֧��


    /////////////////////////////////////////////////////////////////////////////////
    //
    //       CDN �󶨺ͻ�����ش�����
    //       NOTE: ͨ���ص����� TRTCCloudDelegate##onStartPublishing() ��  TRTCCloudDelegate##onSetMixTranscodingConfig ֪ͨ��
    //
    /////////////////////////////////////////////////////////////////////////////////
    ERR_PUBLISH_CDN_STREAM_REQUEST_TIME_OUT         = -3321,    ///< ��·ת������ʱ
    ERR_CLOUD_MIX_TRANSCODING_REQUEST_TIME_OUT      = -3322,    ///< �ƶ˻�������ʱ
    ERR_PUBLISH_CDN_STREAM_SERVER_FAILED            = -3323,    ///< ��·ת�ƻذ��쳣
    ERR_CLOUD_MIX_TRANSCODING_SERVER_FAILED         = -3324,    ///< �ƶ˻����ذ��쳣
    ERR_ROOM_REQUEST_START_PUBLISHING_TIMEOUT       = -3333,    ///< ��ʼ����Ѷ�Ƶ�ֱ�� CDN �������ʱ
    ERR_ROOM_REQUEST_START_PUBLISHING_ERROR         = -3334,    ///< ��ʼ����Ѷ�Ƶ�ֱ�� CDN ���������쳣
    ERR_ROOM_REQUEST_STOP_PUBLISHING_TIMEOUT        = -3335,    ///< ֹͣ����Ѷ�Ƶ�ֱ�� CDN �������ʱ
    ERR_ROOM_REQUEST_STOP_PUBLISHING_ERROR          = -3336,    ///< ֹͣ����Ѷ�Ƶ�ֱ�� CDN ���������쳣
    

    /////////////////////////////////////////////////////////////////////////////////
    //
    //       �緿����ConnectOtherRoom����ش�����
    //       NOTE: ͨ���ص����� TRTCCloudDelegate##onConnectOtherRoom() ֪ͨ��
    //
    /////////////////////////////////////////////////////////////////////////////////
    ERR_ROOM_REQUEST_CONN_ROOM_TIMEOUT              = -3326,    ///< ��������ʱ
    ERR_ROOM_REQUEST_DISCONN_ROOM_TIMEOUT           = -3327,    ///< �����˳�����ʱ
    ERR_ROOM_REQUEST_CONN_ROOM_INVALID_PARAM        = -3328,    ///< ��Ч����
    ERR_CONNECT_OTHER_ROOM_AS_AUDIENCE              = -3330,    ///< ��ǰ�ǹ��ڽ�ɫ�����������Ͽ��緿������Ҫ�� switchRole() ������
    ERR_SERVER_CENTER_CONN_ROOM_NOT_SUPPORT         = -102031,  ///< ��֧�ֿ緿������
    ERR_SERVER_CENTER_CONN_ROOM_REACH_MAX_NUM       = -102032,  ///< �ﵽ�緿����������
    ERR_SERVER_CENTER_CONN_ROOM_REACH_MAX_RETRY_TIMES   = -102033,  ///< �緿���������Դ����ľ�
    ERR_SERVER_CENTER_CONN_ROOM_REQ_TIMEOUT         = -102034,  ///< �緿����������ʱ
    ERR_SERVER_CENTER_CONN_ROOM_REQ                 = -102035,  ///< �緿�����������ʽ����
    ERR_SERVER_CENTER_CONN_ROOM_NO_SIG              = -102036,  ///< �緿��������ǩ��
    ERR_SERVER_CENTER_CONN_ROOM_DECRYPT_SIG         = -102037,  ///< �緿������ǩ������ʧ��
    ERR_SERVER_CENTER_CONN_ROOM_NO_KEY              = -102038,  ///< δ�ҵ��緿������ǩ��������Կ
    ERR_SERVER_CENTER_CONN_ROOM_PARSE_SIG           = -102039,  ///< �緿������ǩ����������
    ERR_SERVER_CENTER_CONN_ROOM_INVALID_SIG_TIME    = -102040,  ///< �緿������ǩ��ʱ�������
    ERR_SERVER_CENTER_CONN_ROOM_SIG_GROUPID         = -102041,  ///< �緿������ǩ����ƥ��
    ERR_SERVER_CENTER_CONN_ROOM_NOT_CONNED          = -102042,  ///< ������������
    ERR_SERVER_CENTER_CONN_ROOM_USER_NOT_CONNED     = -102043,  ///< ���û�δ��������
    ERR_SERVER_CENTER_CONN_ROOM_FAILED              = -102044,  ///< �緿������ʧ��
    ERR_SERVER_CENTER_CONN_ROOM_CANCEL_FAILED       = -102045,  ///< ȡ���緿������ʧ��
    ERR_SERVER_CENTER_CONN_ROOM_CONNED_ROOM_NOT_EXIST   = -102046,  ///< �����󷿼䲻����
    ERR_SERVER_CENTER_CONN_ROOM_CONNED_REACH_MAX_ROOM   = -102047,  ///< �����󷿼�ﵽ��������
    ERR_SERVER_CENTER_CONN_ROOM_CONNED_USER_NOT_EXIST   = -102048,  ///< �������û�������
    ERR_SERVER_CENTER_CONN_ROOM_CONNED_USER_DELETED     = -102049,  ///< �������û��ѱ�ɾ��
    ERR_SERVER_CENTER_CONN_ROOM_CONNED_USER_FULL        = -102050,  ///< �������û��ﵽ��Դ����
    ERR_SERVER_CENTER_CONN_ROOM_INVALID_SEQ             = -102051,  ///< ����������Ŵ���
    
    
    /////////////////////////////////////////////////////////////////////////////////
    //
    //       �ͻ�������ĵ��ڲ�������
    //
    /////////////////////////////////////////////////////////////////////////////////

    // - Remove From Head
    ERR_RTMP_PUSH_NET_DISCONNECT                    = -1307,    ///< ֱ����������������Ͽ����Ҿ�����������޷��ָ�
    ERR_RTMP_PUSH_INVALID_ADDRESS                   = -1313,    ///< ֱ����������ַ�Ƿ������粻�� RTMP Э��ĵ�ַ
    ERR_RTMP_PUSH_NET_ALLADDRESS_FAIL               = -1324,    ///< ֱ������������������ʧ�ܣ���֧������ѡ·��IP ȫ��ʧ�ܣ�
    ERR_RTMP_PUSH_NO_NETWORK                        = -1325,    ///< ֱ�������粻���ã���ȷ�� Wi-Fi���ƶ����ݻ������������Ƿ�����
    ERR_RTMP_PUSH_SERVER_REFUSE                     = -1326,    ///< ֱ�����������ܾ��������󣬿����Ǹ�������ַ�Ѿ���ռ�ã����� TXSecret У��ʧ�ܣ������ǹ����ˣ�������Ƿ����
    
    ERR_PLAY_LIVE_STREAM_NET_DISCONNECT             = -2301,    ///< ֱ��������������Ҿ��������������Ч�����Է������ƣ�����������������������
    ERR_GET_RTMP_ACC_URL_FAIL                       = -2302,    ///< ֱ������ȡ���������ĵ�ַʧ��
    ERR_FILE_NOT_FOUND                              = -2303,    ///< ���ŵ��ļ�������
    ERR_HEVC_DECODE_FAIL                            = -2304,    ///< H265 ����ʧ��
    ERR_VOD_DECRYPT_FAIL                            = -2305,    ///< �㲥������Ƶ������ʧ��
    ERR_GET_VODFILE_MEDIAINFO_FAIL                  = -2306,    ///< �㲥����ȡ�㲥�ļ���Ϣʧ��
    ERR_PLAY_LIVE_STREAM_SWITCH_FAIL                = -2307,    ///< ֱ��������ʧ�ܣ��������Բ��Ų�ͬ�����С����Ƶ��
    ERR_PLAY_LIVE_STREAM_SERVER_REFUSE              = -2308,    ///< ֱ�����������ܾ���������
    ERR_RTMP_ACC_FETCH_STREAM_FAIL                  = -2309,    ///< ֱ����RTMPACC ����ʱ����ʧ�ܣ��Ҿ�����������޷��ָ�

    ERR_ROOM_HEARTBEAT_FAIL                         = -3302,    ///< ����ʧ�ܣ��ͻ��˶�ʱ��������������ݰ������߷������Լ����ţ��������ͨ���Ƿ�����ʱ
    ERR_ROOM_REQUEST_IP_FAIL                        = -3303,    ///< ��ȡ�ӿڻ���������ַʧ��
    ERR_ROOM_CONNECT_FAIL                           = -3304,    ///< ���ӽӿڻ�������ʧ��
    ERR_ROOM_REQUEST_AVSEAT_FAIL                    = -3305,    ///< ������Ƶλʧ��
    ERR_ROOM_REQUEST_TOKEN_HTTPS_TIMEOUT            = -3306,    ///< ���� token HTTPS ��ʱ�����������Ƿ����������������ǽ�Ƿ���� HTTPS ���� official.opensso.tencent-cloud.com:443
    ERR_ROOM_REQUEST_IP_TIMEOUT                     = -3307,    ///< ���� IP �� sig ��ʱ�����������Ƿ����������������ǽ�Ƿ���� UDP �������� IP ������ query.tencent-cloud.com:8000 162.14.23.140:8000 162.14.7.49:8000
    ERR_ROOM_REQUEST_VIDEO_FLAG_TIMEOUT             = -3309,    ///< ������Ƶλ��ʱ
    ERR_ROOM_REQUEST_VIDEO_DATA_ROOM_TIMEOUT        = -3310,    ///< ������Ƶ���ݳ�ʱ
    ERR_ROOM_REQUEST_CHANGE_ABILITY_TIMEOUT         = -3311,    ///< �����޸���Ƶ�����ʱ
    ERR_ROOM_REQUEST_STATUS_REPORT_TIMEOUT          = -3312,    ///< ����״̬�ϱ���ʱ
    ERR_ROOM_REQUEST_CLOSE_VIDEO_TIMEOUT            = -3313,    ///< ����ر���Ƶ��ʱ
    ERR_ROOM_REQUEST_SET_RECEIVE_TIMEOUT            = -3314,    ///< ���������Ƶ�ʱ
    ERR_ROOM_REQUEST_TOKEN_INVALID_PARAMETER        = -3315,    ///< ���� token ��Ч���������� TRTCParams.userSig �Ƿ���д��ȷ

    ERR_ROOM_REQUEST_AES_TOKEN_RETURN_ERROR         = -3329,    ///< ���� AES TOKEN ʱ��server ���ص������ǿյ�
    ERR_ACCIP_LIST_EMPTY                            = -3331,    ///< ����ӿڻ� IP ���ص��б�Ϊ�յ�
    ERR_ROOM_REQUEST_SEND_JSON_CMD_TIMEOUT          = -3332,    ///< ������Json ���ʱ
    
    // Info ����������ѯ�ӿڻ� IP��, �����������룬��ֵ��Χ[-100000, -110000]
    ERR_SERVER_INFO_UNPACKING_ERROR                 = -100000,  ///< server ������󣬿����������ݱ��۸�
    ERR_SERVER_INFO_TOKEN_ERROR                     = -100001,  ///< TOKEN ����
    ERR_SERVER_INFO_ALLOCATE_ACCESS_FAILED          = -100002,  ///< ����ӿڻ�����
    ERR_SERVER_INFO_GENERATE_SIGN_FAILED            = -100003,  ///< ����ǩ������
    ERR_SERVER_INFO_TOKEN_TIMEOUT                   = -100004,  ///< HTTPS token ��ʱ
    ERR_SERVER_INFO_INVALID_COMMAND                 = -100005,  ///< ��Ч��������
    ERR_SERVER_INFO_PRIVILEGE_FLAG_ERROR            = -100006,  ///< Ȩ��λУ��ʧ��
    ERR_SERVER_INFO_GENERATE_KEN_ERROR              = -100007,  ///< HTTPS ����ʱ�����ɼ��� key ����
    ERR_SERVER_INFO_GENERATE_TOKEN_ERROR            = -100008,  ///< HTTPS ����ʱ������ token ����
    ERR_SERVER_INFO_DATABASE                        = -100009,  ///< ���ݿ��ѯʧ�ܣ�������ش洢��Ϣ��
    ERR_SERVER_INFO_BAD_ROOMID                      = -100010,  ///< ����Ŵ���
    ERR_SERVER_INFO_BAD_SCENE_OR_ROLE               = -100011,  ///< �������ɫ����
    ERR_SERVER_INFO_ROOMID_EXCHANGE_FAILED          = -100012,  ///< �����ת������
    ERR_SERVER_INFO_STRGROUP_HAS_INVALID_CHARS      = -100014,  ///< ����ŷǷ�
    ERR_SERVER_INFO_LACK_SDKAPPID                   = -100015,  ///< �Ƿ�SDKAppid
    ERR_SERVER_INFO_INVALID                         = -100016,  ///< ��Ч����, ����ӿڻ�ʧ��
    ERR_SERVER_INFO_ECDH_GET_KEY                    = -100017,  ///< ���ɹ�Կʧ��
    ERR_SERVER_INFO_ECDH_GET_TINYID                 = -100018,  ///< userSig У��ʧ�ܣ����� TRTCParams.userSig �Ƿ���д��ȷ
    
    // Access �ӿڻ�
    ERR_SERVER_ACC_TOKEN_TIMEOUT                    = -101000,  ///< token ����
    ERR_SERVER_ACC_SIGN_ERROR                       = -101001,  ///< ǩ������
    ERR_SERVER_ACC_SIGN_TIMEOUT                     = -101002,  ///< ǩ����ʱ
    ERR_SERVER_ACC_ROOM_NOT_EXIST                   = -101003,  ///< ���䲻����
    ERR_SERVER_ACC_ROOMID                           = -101004,  ///< ��̨�����ʶ roomId ����
    ERR_SERVER_ACC_LOCATIONID                       = -101005,  ///< ��̨�û�λ�ñ�ʶ locationId ����
    ERR_SERVER_ACC_TOKEN_EORROR                     = -101006,  ///< token�����tinyid�ͽ�������tinyid��ͬ ���� ��������û��token

    // Center ����������������ش��������
    ERR_SERVER_CENTER_SYSTEM_ERROR                  = -102000,  ///< ��̨����
    
    ERR_SERVER_CENTER_INVALID_ROOMID                = -102001,  ///< ��Ч�ķ��� Id
    ERR_SERVER_CENTER_CREATE_ROOM_FAILED            = -102002,  ///< ��������ʧ��
    ERR_SERVER_CENTER_SIGN_ERROR                    = -102003,  ///< ǩ������
    ERR_SERVER_CENTER_SIGN_TIMEOUT                  = -102004,  ///< ǩ������
    ERR_SERVER_CENTER_ROOM_NOT_EXIST                = -102005,  ///< ���䲻����
    ERR_SERVER_CENTER_ADD_USER_FAILED               = -102006,  ///< ��������û�ʧ��
    ERR_SERVER_CENTER_FIND_USER_FAILED              = -102007,  ///< �����û�ʧ��
    ERR_SERVER_CENTER_SWITCH_TERMINATION_FREQUENTLY = -102008,  ///< Ƶ���л��ն�
    ERR_SERVER_CENTER_LOCATION_NOT_EXIST            = -102009,  ///< locationid ����
    ERR_SERVER_CENTER_NO_PRIVILEDGE_CREATE_ROOM     = -102010,  ///< û��Ȩ�޴�������
    ERR_SERVER_CENTER_NO_PRIVILEDGE_ENTER_ROOM      = -102011,  ///< û��Ȩ�޽��뷿��
    ERR_SERVER_CENTER_INVALID_PARAMETER_SUB_VIDEO   = -102012,  ///< ��·����Ƶλ�����븨·�������Ͳ�������
    ERR_SERVER_CENTER_NO_PRIVILEDGE_PUSH_VIDEO      = -102013,  ///< û��Ȩ������Ƶ
    ERR_SERVER_CENTER_ROUTE_TABLE_ERROR             = -102014,  ///< û�п���·�ɱ�
    ERR_SERVER_CENTER_NOT_PUSH_SUB_VIDEO            = -102017,  ///< ��ǰ�û�û�����и�·
    ERR_SERVER_CENTER_USER_WAS_DELETED              = -102018,  ///< �û���ɾ��״̬
    ERR_SERVER_CENTER_NO_PRIVILEDGE_REQUEST_VIDEO   = -102019,  ///< û��Ȩ��������Ƶ
    ERR_SERVER_CENTER_INVALID_PARAMETER             = -102023,  ///< �������� bussInfo ����
    ERR_SERVER_CENTER_I_FRAME_UNKNOW_TYPE           = -102024,  ///< ���� I ֡δ֪ opType
    ERR_SERVER_CENTER_I_FRAME_INVALID_PACKET        = -102025,  ///< ���� I ֡����ʽ����
    ERR_SERVER_CENTER_I_FRAME_DEST_USER_NOT_EXIST   = -102026,  ///< ���� I ֡Ŀ���û�������
    ERR_SERVER_CENTER_I_FRAME_ROOM_TOO_BIG          = -102027,  ///< ���� I ֡�����û�̫��
    ERR_SERVER_CENTER_I_FRAME_RPS_INVALID_PARAMETER = -102028,  ///< ���� I ֡��������
    ERR_SERVER_CENTER_INVALID_ROOM_ID               = -102029,  ///< ����ŷǷ�
    ERR_SERVER_CENTER_ROOM_ID_TOO_LONG              = -102030,  ///< ����ų�������
    ERR_SERVER_CENTER_ROOM_FULL                         = -102052,  ///< ������Ա
    ERR_SERVER_CENTER_DECODE_JSON_FAIL                  = -102053,  ///< JSON ������ʧ��
    ERR_SERVER_CENTER_UNKNOWN_SUB_CMD                   = -102054,  ///< δ����������
    ERR_SERVER_CENTER_INVALID_ROLE                      = -102055,  ///< δ�����ɫ
    ERR_SERVER_CENTER_REACH_PROXY_MAX                   = -102056,  ///< �������������
    ERR_SERVER_CENTER_RECORDID_STORE                = -102057,  ///< �޷������û��Զ��� recordId
    ERR_SERVER_CENTER_PB_SERIALIZE                  = -102058,  ///< Protobuf ���л�����
    
    ERR_SERVER_SSO_SIG_EXPIRED                      = -70001,   ///< sig ���ڣ��볢���������ɡ�����Ǹ����ɣ��͹��ڣ�������Ч����д���Ƿ��С��������� 0
    ERR_SERVER_SSO_SIG_VERIFICATION_FAILED_1        = -70003,   ///< sig У��ʧ�ܣ���ȷ���� sig �����Ƿ񱻽ضϣ��绺�������Ȳ������µ����ݽض�
    ERR_SERVER_SSO_SIG_VERIFICATION_FAILED_2        = -70004,   ///< sig У��ʧ�ܣ���ȷ���� sig �����Ƿ񱻽ضϣ��绺�������Ȳ������µ����ݽض�
    ERR_SERVER_SSO_SIG_VERIFICATION_FAILED_3        = -70005,   ///< sig У��ʧ�ܣ����ù���������֤���ɵ� sig �Ƿ���ȷ
    ERR_SERVER_SSO_SIG_VERIFICATION_FAILED_4        = -70006,   ///< sig У��ʧ�ܣ����ù���������֤���ɵ� sig �Ƿ���ȷ
    ERR_SERVER_SSO_SIG_VERIFICATION_FAILED_5        = -70007,   ///< sig У��ʧ�ܣ����ù���������֤���ɵ� sig �Ƿ���ȷ
    ERR_SERVER_SSO_SIG_VERIFICATION_FAILED_6        = -70008,   ///< sig У��ʧ�ܣ����ù���������֤���ɵ� sig �Ƿ���ȷ
    ERR_SERVER_SSO_SIG_VERIFICATION_FAILED_7        = -70009,   ///< ��ҵ��Կ��֤ sig ʧ�ܣ���ȷ�����ɵ� usersig ʹ�õ�˽Կ�� sdkAppId �Ƿ��Ӧ
    ERR_SERVER_SSO_SIG_VERIFICATION_FAILED_8        = -70010,   ///< sig У��ʧ�ܣ����ù���������֤���ɵ� sig �Ƿ���ȷ
    ERR_SERVER_SSO_SIG_VERIFICATION_ID_NOT_MATCH    = -70013,   ///< sig �� identifier ������ʱ�� identifier ��ƥ�䣬�����¼ʱ��д�� identifier �� sig �е��Ƿ�һ��
    ERR_SERVER_SSO_APPID_NOT_MATCH                  = -70014,   ///< sig �� sdkAppId ������ʱ�� sdkAppId ��ƥ�䣬�����¼ʱ��д�� sdkAppId �� sig �е��Ƿ�һ��
    ERR_SERVER_SSO_VERIFICATION_EXPIRED             = -70017,   ///< �ڲ�������Ʊ����֤��ʱ�������ԣ��������Բ��ɹ�����@TLS �ʺ�֧�֣�QQ 3268519604
    ERR_SERVER_SSO_VERIFICATION_FAILED              = -70018,   ///< �ڲ�������Ʊ����֤��ʱ�������ԣ��������Բ��ɹ�����@TLS �ʺ�֧�֣�QQ 3268519604

    ERR_SERVER_SSO_APPID_NOT_FOUND                  = -70020,   ///< sdkAppId δ�ҵ�����ȷ���Ƿ��Ѿ�����Ѷ��������
    ERR_SERVER_SSO_ACCOUNT_IN_BLACKLIST             = -70051,   ///< �ʺ��ѱ����������������ϵ TLS �ʺ�֧�� QQ 3268519604
    ERR_SERVER_SSO_SIG_INVALID                      = -70052,   ///< usersig �Ѿ�ʧЧ�����������ɣ��ٴγ���
    ERR_SERVER_SSO_LIMITED_BY_SECURITY              = -70114,   ///< ��ȫԭ������
    ERR_SERVER_SSO_INVALID_LOGIN_STATUS             = -70221,   ///< ��¼״̬��Ч����ʹ�� usersig ���¼�Ȩ
    ERR_SERVER_SSO_APPID_ERROR                      = -70252,   ///< sdkAppId ��д����
    ERR_SERVER_SSO_TICKET_VERIFICATION_FAILED       = -70346,   ///< Ʊ��У��ʧ�ܣ������������Ƿ���ȷ
    ERR_SERVER_SSO_TICKET_EXPIRED                   = -70347,   ///< Ʊ�������ԭ��У��ʧ��
    ERR_SERVER_SSO_ACCOUNT_EXCEED_PURCHASES         = -70398,   ///< �����˺����������ѹ���Ԥ������������
    ERR_SERVER_SSO_INTERNAL_ERROR                   = -70500,   ///< �������ڲ�����������
    // - /Remove From Head
} TXLiteAVError;

/////////////////////////////////////////////////////////////////////////////////
//
//                     ������
//
//> ����Ҫ�ر��ע���������Ը�������ĳЩ����Ȥ�ľ����룬�Ե�ǰ�û�������Ӧ����ʾ
//
/////////////////////////////////////////////////////////////////////////////////

typedef enum TXLiteAVWarning
{
    WARNING_HW_ENCODER_START_FAIL                   = 1103,     ///< Ӳ���������������⣬�Զ��л��������
    WARNING_VIDEO_ENCODER_SW_TO_HW                  = 1107,     ///<  ��ǰ CPU ʹ����̫�ߣ��޷�����������������Զ��л���Ӳ������
    WARNING_INSUFFICIENT_CAPTURE_FPS                = 1108,     ///<  ����ͷ�ɼ�֡�ʲ��㣬�����Դ������㷨�� Android �ֻ��ϻ����
    WARNING_SW_ENCODER_START_FAIL                   = 1109,     ///<  ���������ʧ��
    WARNING_REDUCE_CAPTURE_RESOLUTION               = 1110,     ///<  ����ͷ�ɼ��ֱ��ʱ����ͣ������㵱ǰ֡�ʺ��������Ž⡣
    WARNING_VIDEO_FRAME_DECODE_FAIL                 = 2101,     ///<  ��ǰ��Ƶ֡����ʧ��
    WARNING_AUDIO_FRAME_DECODE_FAIL                 = 2102,     ///<  ��ǰ��Ƶ֡����ʧ��
    WARNING_VIDEO_PLAY_LAG                          = 2105,     ///<  ��ǰ��Ƶ���ų��ֿ���
    WARNING_HW_DECODER_START_FAIL                   = 2106,     ///<  Ӳ������ʧ�ܣ����������
    WARNING_VIDEO_DECODER_HW_TO_SW                  = 2108,     ///<  ��ǰ��Ӳ���һ�� I ֡ʧ�ܣ�SDK �Զ������
    WARNING_SW_DECODER_START_FAIL                   = 2109,     ///<  �����������ʧ��
    WARNING_VIDEO_RENDER_FAIL                       = 2110,     ///<  ��Ƶ��Ⱦʧ��
    WARNING_AUDIO_RECORDING_WRITE_FAIL              = 7001,     ///<  ��Ƶ¼��д���ļ�ʧ��
    WARNING_ROOM_DISCONNECT                         = 5101,     ///<  ����Ͽ�����
    WARNING_IGNORE_UPSTREAM_FOR_AUDIENCE            = 6001,     ///<  ��ǰ�ǹ��ڽ�ɫ��������������Ƶ����
    
    // - Remove From Head
    WARNING_NET_BUSY                                = 1101,     ///< ����״�����ѣ����д���̫С���ϴ���������
    WARNING_RTMP_SERVER_RECONNECT                   = 1102,     ///<  ֱ�����������, �������Զ��������Զ���������ʧ�ܳ������λ������
    WARNING_LIVE_STREAM_SERVER_RECONNECT            = 2103,     ///<  ֱ�����������, �������Զ��������Զ���������ʧ�ܳ������λ������
    WARNING_RECV_DATA_LAG                           = 2104,     ///<  �����������ȣ����������д����㣬�����������˳���������
    WARNING_RTMP_DNS_FAIL                           = 3001,     ///<  ֱ����DNS ����ʧ��
    WARNING_RTMP_SEVER_CONN_FAIL                    = 3002,     ///<  ֱ��������������ʧ��
    WARNING_RTMP_SHAKE_FAIL                         = 3003,     ///<  ֱ������ RTMP ����������ʧ��
    WARNING_RTMP_SERVER_BREAK_CONNECT               = 3004,     ///<  ֱ���������������Ͽ�
    WARNING_RTMP_READ_WRITE_FAIL                    = 3005,     ///<  ֱ����RTMP ��/дʧ�ܣ�����Ͽ�����
    WARNING_RTMP_WRITE_FAIL                         = 3006,     ///<  ֱ����RTMP дʧ�ܣ�SDK �ڲ������룬��������׳���
    WARNING_RTMP_READ_FAIL                          = 3007,     ///<  ֱ����RTMP ��ʧ�ܣ�SDK �ڲ������룬��������׳���
    WARNING_RTMP_NO_DATA                            = 3008,     ///<  ֱ��������30s û�����ݷ��ͣ������Ͽ�����
    WARNING_PLAY_LIVE_STREAM_INFO_CONNECT_FAIL      = 3009,     ///<  ֱ����connect ����������ʧ�ܣ�SDK �ڲ������룬��������׳���
    WARNING_NO_STEAM_SOURCE_FAIL                    = 3010,     ///<  ֱ��������ʧ�ܣ�������ַ����Ƶ��SDK �ڲ������룬��������׳���
    WARNING_ROOM_RECONNECT                          = 5102,     ///<  ����������������Զ�����
    WARNING_ROOM_NET_BUSY                           = 5103,     ///<  ����״�����ѣ����д���̫С���ϴ���������
    // - /Remove From Head
} TXLiteAVWarning;

// - Remove From Head
/////////////////////////////////////////////////////////////////////////////////
//
//                     �������¼��б�
//
/////////////////////////////////////////////////////////////////////////////////

typedef enum TXLiteAVEvent
{
    EVT_RTMP_PUSH_CONNECT_SUCC                      = 1001,     ///<  ֱ�����Ѿ����� RTMP ����������
    EVT_RTMP_PUSH_BEGIN                             = 1002,     ///<  ֱ�����Ѿ��� RTMP ������������ϣ���ʼ����
    EVT_CAMERA_START_SUCC                           = 1003,     ///<  ������ͷ�ɹ�
    EVT_SCREEN_CAPTURE_SUCC                         = 1004,     ///<  ¼�������ɹ�
    EVT_UP_CHANGE_RESOLUTION                        = 1005,     ///<  ���ж�̬�����ֱ���
    EVT_UP_CHANGE_BITRATE                           = 1006,     ///<  ���ʶ�̬����
    EVT_FIRST_FRAME_AVAILABLE                       = 1007,     ///<  ��֡����ɼ����
    EVT_START_VIDEO_ENCODER                         = 1008,     ///<  �����������ɹ�
    EVT_SNAPSHOT_COMPLETE                           = 1022,     ///<  һ֡��ͼ���
    EVT_CAMERA_REMOVED                              = 1023,     ///<  ����ͷ�豸�ѱ��Ƴ���Windows �� Mac �� SDK ʹ�ã�
    EVT_CAMERA_AVAILABLE                            = 1024,     ///<  ����ͷ�豸���¿��ã�Windows �� Mac �� SDK ʹ�ã�
    EVT_CAMERA_CLOSE                                = 1025,     ///<  �ر�����ͷ��ɣ�Windows �� Mac �� SDK ʹ�ã�
    EVT_RTMP_PUSH_PUBLISH_START                     = 1026,     ///<  ֱ������ RTMP ���������Ӻ��յ� NetStream.Publish.Start ��Ϣ�������������ɹ���SDK �ڲ��¼�����������׳���
    EVT_HW_ENCODER_START_SUCC                       = 1027,     ///<  Ӳ�����������ɹ�
    EVT_SW_ENCODER_START_SUCC                       = 1028,     ///<  ������������ɹ�
    EVT_LOCAL_RECORD_RESULT                         = 1029,     ///<  ����¼�ƽ��
    EVT_LOCAL_RECORD_PROGRESS                       = 1030,     ///<  ����¼��״̬֪ͨ

    EVT_PLAY_LIVE_STREAM_CONNECT_SUCC               = 2001,     ///<  ֱ�����Ѿ����� RTMP ����������
    EVT_PLAY_LIVE_STREAM_BEGIN                      = 2002,     ///<  ֱ�����Ѿ��� RTMP ������������ϣ���ʼ����
    EVT_RENDER_FIRST_I_FRAME                        = 2003,     ///<  ��Ⱦ�׸���Ƶ���ݰ���IDR��
    EVT_VIDEO_PLAY_BEGIN                            = 2004,     ///<  ��Ƶ���ſ�ʼ
    EVT_VIDEO_PLAY_PROGRESS                         = 2005,     ///<  ��Ƶ���Ž���
    EVT_VIDEO_PLAY_END                              = 2006,     ///<  ��Ƶ���Ž���
    EVT_VIDEO_PLAY_LOADING                          = 2007,     ///<  ��Ƶ���� loading
    EVT_START_VIDEO_DECODER                         = 2008,     ///<  ����������
    EVT_DOWN_CHANGE_RESOLUTION                      = 2009,     ///<  ������Ƶ�ֱ��ʸı�
    EVT_GET_VODFILE_MEDIAINFO_SUCC                  = 2010,     ///<  �㲥����ȡ�㲥�ļ���Ϣ�ɹ�
    EVT_VIDEO_CHANGE_ROTATION                       = 2011,     ///<  ��Ƶ��ת�Ƕȷ����ı�
    EVT_PLAY_GET_MESSAGE                            = 2012,     ///<  ��Ϣ�¼�
    EVT_VOD_PLAY_PREPARED                           = 2013,     ///<  �㲥����Ƶ�������
    EVT_VOD_PLAY_LOADING_END                        = 2014,     ///<  �㲥��loading ����
    EVT_PLAY_LIVE_STREAM_SWITCH_SUCC                = 2015,     ///<  ֱ���������ɹ����������Բ��Ų�ͬ�����С����Ƶ��
    EVT_VOD_PLAY_TCP_CONNECT_SUCC                   = 2016,     ///<  �㲥��TCP ���ӳɹ���SDK �ڲ��¼�����������׳���
    EVT_VOD_PLAY_FIRST_VIDEO_PACKET                 = 2017,     ///<  �㲥���յ���֡���ݣ�SDK �ڲ��¼�����������׳���
    EVT_VOD_PLAY_DNS_RESOLVED                       = 2018,     ///<  �㲥��DNS ������ɣ�SDK �ڲ��¼�����������׳���
    EVT_VOD_PLAY_SEEK_COMPLETE                      = 2019,     ///<  �㲥����Ƶ���� Seek ��ɣ�SDK �ڲ��¼�����������׳���
    EVT_VIDEO_DECODER_CACHE_TOO_MANY_FRAMES         = 2020,     ///<  ��Ƶ����������֡�����࣬����40֡��SDK �ڲ��¼�����������׳���
    EVT_HW_DECODER_START_SUCC                       = 2021,     ///<  Ӳ�����������ɹ���SDK �ڲ��¼�����������׳���
    EVT_SW_DECODER_START_SUCC                       = 2022,     ///<  ������������ɹ���SDK �ڲ��¼�����������׳���
    EVT_AUDIO_JITTER_STATE_FIRST_LOADING            = 2023,     ///<  ��Ƶ�״μ��أ�SDK �ڲ��¼�����������׳���
    EVT_AUDIO_JITTER_STATE_LOADING                  = 2024,     ///<  ��Ƶ���ڼ��أ�SDK �ڲ��¼�����������׳���
    EVT_AUDIO_JITTER_STATE_PLAYING                  = 2025,     ///<  ��Ƶ���ڲ��ţ�SDK �ڲ��¼�����������׳���
    EVT_AUDIO_JITTER_STATE_FIRST_PLAY               = 2026,     ///<  ��Ƶ�״β��ţ�SDK �ڲ��¼�����������׳���
    EVT_MIC_START_SUCC                              = 2027,     ///<  ��˷������ɹ�
    EVT_PLAY_GET_METADATA                           = 2028,     ///<  ��Ƶ��MetaData�¼�
    EVT_MIC_RELEASE_SUCC                            = 2029,     ///<  �ͷ���˷�ռ��

    EVT_ROOM_ENTER                                  = 1018,     ///<  ���뷿��ɹ�
    EVT_ROOM_EXIT                                   = 1019,     ///<  �˳�����
    EVT_ROOM_USERLIST                               = 1020,     ///<  �·������Ա�б��������Լ���
    EVT_ROOM_NEED_REENTER                           = 1021,     ///<  WiFi �л���4G �ᴥ��������������ʱ��Ҫ���½��뷿�䣨��ȡ���ŵķ�������ַ��
    EVT_ROOM_ENTER_FAILED                           = 1022,     ///<  �Լ����뷿��ʧ��
    EVT_ROOM_USER_ENTER                             = 1031,     ///<  ����֪ͨ
    EVT_ROOM_USER_EXIT                              = 1032,     ///<  �˷�֪ͨ
    EVT_ROOM_USER_VIDEO_STATE                       = 1033,     ///<  ��Ƶ״̬λ�仯֪ͨ
    EVT_ROOM_USER_AUDIO_STATE                       = 1034,     ///<  ��Ƶ״̬λ�仯֪ͨ
    
    EVT_ROOM_REQUEST_IP_SUCC                        = 8001,     ///<  ��ȡ�ӿڻ���������ַ�ɹ�
    EVT_ROOM_CONNECT_SUCC                           = 8002,     ///<  ���ӽӿڻ��������ɹ�
    EVT_ROOM_REQUEST_AVSEAT_SUCC                    = 8003,     ///<  ������Ƶλ�ɹ�
} TXLiteAVEvent;
// - /Remove From Head

#endif /* __TXLITEAVCODE_H__ */
