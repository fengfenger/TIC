
#include<windows.h>
#include<stdio.h>
#include "TICLocalRecordImpl.h"
#include "../jsoncpp/json.h"
#include "md5.h"
#include <strstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <time.h>


const std::string RecordExe = "TXCloudRecord.exe";
const std::string URL = "http://127.0.0.1:37604/localrecord/v1/";

struct BaseCallback{
	BaseCallback(const TICCallback callback) { this->callback = callback; }
	virtual void parse(const std::string& response, TICLocalRecorderImpl::Result& result) const {};
	TICCallback callback;
};

class CmdCallback : public BaseCallback {
public:
	CmdCallback(const TICCallback callback) : BaseCallback(callback){ }
	virtual void parse(const std::string& response, TICLocalRecorderImpl::Result& result) const override {
		std::string rspBuf = response;
		Json::Value Val;
		Json::Reader reader;
		if (!reader.parse(rspBuf.c_str(), rspBuf.c_str() + rspBuf.size(), Val)) { //从ifs中读取数据到jsonRoot
			result.msg = std::string("parse json error :");
			result.code = -1;
			return;
		}

		if (Val.isMember("Response")) {
			auto Response = Val["Response"];

			if (Response.isMember("Error")) { //失败，错误返回
				auto error = Response["Error"];
				if (error.isMember("Code")) {
					result.code = error["Code"].asInt();
				}
				if (error.isMember("Message")) {
					result.msg = error["Message"].asString();
				}
			}
			else {
				result.code = 0;
				result.msg = response;
			}
		}
		else {
			result.msg = std::string("invalid response");
			result.code = -1;
		}
	}
};

class ServerCallback : public BaseCallback {
public:
	ServerCallback(const TICCallback callback) : BaseCallback(callback) { }

	virtual void parse(const std::string& response, TICLocalRecorderImpl::Result& result) const override {
		result.code = 0;
		result.msg = response;
	}
};

std::string getMD5(std::string src)
{
	unsigned char fingerPrintStableMD5[MD5_RESULT_LEN] = { 0 };
	char* stableStr = const_cast<char*>(src.c_str());
	TenMd5(reinterpret_cast<unsigned char*>(stableStr), src.size(), fingerPrintStableMD5);

	std::strstream sstream;
	for (int i = 0; i < MD5_RESULT_LEN; ++i)
	{
		sstream << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << static_cast<int>(fingerPrintStableMD5[i]);
	}

	std::string result;
	sstream >> result;

	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

/**
*单位：毫秒
*/
uint64_t txf_getutctick() {
#if defined(_WIN32)
	return (uint64_t)std::chrono::system_clock::now().time_since_epoch().count() / 10000;  // Windows要求除10000（神奇）
#else
	return (uint64_t)std::chrono::system_clock::now().time_since_epoch().count() / 1000;
#endif
}

TICLocalRecorderImpl::TICLocalRecorderImpl() {
}

TICLocalRecorderImpl::TICLocalRecorderImpl(std::weak_ptr<TEduRecordCallback>  callback) : mCallback(callback) {
}

TICLocalRecorderImpl::~TICLocalRecorderImpl() {
}


bool TICLocalRecorderImpl::startService(const std::string& path) {
	BOOL ret = FALSE;
	std::string cmd = "";

	SHELLEXECUTEINFOA sei = { 0 };
	sei.cbSize = sizeof(SHELLEXECUTEINFOA);
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.hwnd = NULL;
	sei.lpVerb = "open";
	sei.lpFile = path.c_str();
	sei.lpParameters = cmd.c_str();
	sei.lpDirectory = NULL;
	sei.nShow = SW_HIDE;
	sei.hInstApp = NULL;
	sei.lpIDList = NULL;
	sei.lpClass = NULL;
	sei.hkeyClass = NULL;
	sei.dwHotKey = NULL;
	sei.hIcon = NULL;
	sei.hProcess = NULL;

	ret = ::ShellExecuteExA(&sei);

	return ret;
}

int TICLocalRecorderImpl::init(const TEduRecordAuthParam& authParam, TICCallback callback) {
	mAuth = authParam;

	char szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	(strrchr(szFilePath, '\\'))[0] = 0;
	std::string path = szFilePath;
	path.append("\\..\\..\\SDK\\TIC\\localrecord\\lib\\");
	path.append(RecordExe);

	startService(path);

	Json::Value value;
	value["SdkAppId"] = authParam.appId;
	value["UserId"] = authParam.userId;
	value["UserSig"] = authParam.userSig;

	Json::FastWriter writer;
	std::string msg = writer.write(value);

	sendCmd("Init", msg, callback);
	return 0;
}


int TICLocalRecorderImpl::startLocalRecord(const TEduRecordParam& para, const char * szRecordPath, TICCallback callback) {

	if (szRecordPath != NULL && strlen(szRecordPath) > 0) {
		Json::Value value;
		value["AppProc"] = para.AppProc;
		value["Wnd"] = para.Wnd;
		value["x"] = para.x;
		value["y"] = para.y;
		value["Width"] = para.width;
		value["Height"] = para.Height;
		value["VideoFps"] = para.videoFps;
		value["VideoBps"] = para.videoBps;
		value["EnableAudio"] = para.enableAudio;
		value["DstPath"] = szRecordPath;
		value["ClassId"] = para.classId;

		Json::FastWriter writer;
		std::string msg = writer.write(value);

		sendCmd("StartRecord", msg, callback);
		StartTimer();

		return 0;
	}

	return -1;
}

int TICLocalRecorderImpl::stopLocalRecord(TICCallback callback) {
	sendCmd("StopRecord", std::string(), callback);
	StopTimer();
	return 0;
}

int TICLocalRecorderImpl::pauseLocalRecord(TICCallback callback) {
	sendCmd("PauseRecord", std::string(), callback);
	return 0;
}

int TICLocalRecorderImpl::resumeLocalRecord(TICCallback callback) {
	sendCmd("ResumeRecord", std::string(), callback);
	return 0;
}

int TICLocalRecorderImpl::exit(TICCallback callback) {
	sendCmd("Exit", std::string(), callback);
	return 0;
}

int TICLocalRecorderImpl::getState(TICCallback callback) {
	sendCmd("GetState", std::string(), callback);
	return 0;
}

int TICLocalRecorderImpl::getRecordResult(const RecordKey& key, TICCallback callback) {
	if (key.appid == 0) {
		printf("user info error");
		return -1;
	}


	char httpsUrl[1024] = { 0 };
	
	/* 
	//服务器端正式的使用方式，如下
	const char* URL = "https://iclass.api.qcloud.com/paas/v1/localrecord/query?sdkappid=%d&sign=%s&expire_time=%d&random=%d";
	int random = std::rand();
	uint64_t expire_time = txf_getutctick() / 1000 + 60 * 5; //
	const std::string TICKey = "XXXXXXXXXXXXXXXXXXXX";
	std::string sign = getMD5("TICKey" + std::to_string(expire_time));
	sprintf(httpsUrl, URL, key.appid, sign.c_str(), expire_time, random);
	*/

	//为了对TIC KEY的保护，我们在客户端采取临时方式
	const char* URL = "https://service-cmgleh9m-1257307760.gz.apigw.tencentcs.com/release/board_forward?sdkappid=%d";
	sprintf(httpsUrl, URL, key.appid);

	Json::Value value;
	//if (key.class_id != 0) {
		value["class_id"] =13582;
//	}
//	if (!key.user_id.empty()) {
		value["user_id"] = key.user_id;
//	}
//	if (!key.task_id.empty()) {
		value["task_id"] = key.task_id;
//	}

		value["Index"] = 0;
	
		value["size"] = 10;

	Json::FastWriter writer;
	std::string msg = writer.write(value);

	ServerCallback* servercallback = new ServerCallback(callback);
	sendRequest(HttpClient::a2w(httpsUrl), msg, servercallback);

	return 0;
}

void TICLocalRecorderImpl::sendCmd(const std::string& cmd, const std::string& content, const TICCallback callback) {
	CmdCallback* cmdcallbck = new CmdCallback(callback);
	sendRequest(HttpClient::a2w(URL + cmd), content, cmdcallbck);
}



void TICLocalRecorderImpl::sendRequest(const std::wstring& url, const std::string& reqBody, BaseCallback* mycallback) {
	if (!url.empty()) {

		http.asynPost(url, reqBody, [=](int code, const HttpHeaders& rspHeaders, const std::string& rspBuf) {
			Result res(0, "succ");

			if (code != 0) {
				res.code = code;
				res.msg = std::string("http request error ") ;
				goto myEXIT;
			}

			if (mycallback) {
				mycallback->parse(std::string(rspBuf), res);
			}

		myEXIT:
			if (mycallback) {
				if (mycallback->callback) {
					mycallback->callback(TICMODULE_RECORD, res.code, res.msg.c_str());
				}
				delete mycallback;
			}
		});
	}
}

void TICLocalRecorderImpl::StartTimer()
{
	StopTimer();
	syncTimer_ = ::SetTimer(NULL, 0, 5000, [](HWND hwnd, UINT msg, UINT_PTR timerid, DWORD dwTime) {
		TICLocalRecorderImpl* pThis = static_cast<TICLocalRecorderImpl*>(TICLocalRecorder::GetInstance());
		if (pThis) pThis->onTimer();
	});
}

void TICLocalRecorderImpl::StopTimer()
{
	if (syncTimer_ != 0)
	{
		::KillTimer(0, syncTimer_);
		syncTimer_ = 0;
	}
}

void TICLocalRecorderImpl::onTimer() {
	//std::weak_ptr< TICLocalRecorderImpl> weakSelf = this->shared_from_this();
	getState([this](TICModule module, int code, const char *desc) {
		//std::shared_ptr<TICLocalRecorderImpl> self = weakSelf.lock();
		//if (!self)
		//	return;

		if (code == 0) {
			printf(" getState: %s",  desc);

			Json::Value Val;
			Json::Reader reader;
			if (!reader.parse(desc, strlen(desc) + desc, Val)) { //从ifs中读取数据到jsonRoot
				return;
			}
			if (Val.isMember("Response")) {
				auto Response = Val["Response"];

				if (Response.isMember("Upload")) {
					auto uploads = Response["Upload"];
					if (uploads.isArray()) {
						int size = uploads.size();
						for (int i = 0; i < size; ++i) {
							auto up = uploads[i];
							std::string id;
							int total = 0, duration = 0;
							if (up.isMember("Id")) {
								id = up["Id"].asString();
							}

							if (up.isMember("Total")) {
								total = up["Total"].asInt();
							}

							if (up.isMember("Duration")) {
								duration = up["Duration"].asInt();
							}

						}
					}
				}
			}
			
		}
	});
}
