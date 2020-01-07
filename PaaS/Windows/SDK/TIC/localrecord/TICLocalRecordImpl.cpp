
#include<windows.h>
#include<stdio.h>
#include "TICLocalRecordImpl.h"
#include "../jsoncpp/json.h"

const std::string RecordExe = "TXCloudRecord.exe";
const std::string URL = "http://127.0.0.1:37604/localrecord/v1/";

TICLocalRecorderImpl::TICLocalRecorderImpl() {
}

TICLocalRecorderImpl::TICLocalRecorderImpl(std::weak_ptr<TEduRecordCallback>  callback) : mCallback(callback) {
}

TICLocalRecorderImpl::~TICLocalRecorderImpl() {
}


int TICLocalRecorderImpl::startService() {
	BOOL ret = FALSE;

	std::string cmd = "";

	char szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	(strrchr(szFilePath, '\\'))[0] = 0;
	std::string path = szFilePath;
	path.append("\\..\\..\\SDK\\TIC\\localrecord\\lib\\");
	path.append(RecordExe);
	//path.append("../");

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

	startService();

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
	if (mAuth.appId == 0 || mAuth.userId.empty() || mAuth.userSig.empty()) {
		printf("user info error");
		return -1;
	}

	const char* URL = "https://yun.tim.qq.com/v4/ilvb_edusaas/v1/localrecord/query?sdkappid=%d&user_id=%s&token=%s&random=%d";
	char httpsUrl[1024] = { 0 };
	int random = std::rand();
	sprintf(httpsUrl, URL, mAuth.appId, mAuth.userId.c_str(), mAuth.userSig.c_str(), random);

	Json::Value value;
	if (key.class_id != 0) {
		value["class_id"] = key.class_id;
	}
	if (!key.user_id.empty()) {
		value["user_id"] = key.user_id;
	}
	if (!key.task_id.empty()) {
		value["task_id"] = key.task_id;
	}
	
	Json::FastWriter writer;
	std::string msg = writer.write(value);

	sendRequest(HttpClient::a2w(httpsUrl), msg, callback);

	return 0;
}

void TICLocalRecorderImpl::sendCmd(const std::string& cmd, const std::string& content, const TICCallback callback) {
	sendRequest(HttpClient::a2w(URL + cmd), content, callback);
}

void TICLocalRecorderImpl::sendRequest(const std::wstring& url, const std::string& reqBody, const TICCallback callback) {
	if (!url.empty()) {
		//std::weak_ptr<TICLocalRecorderImpl> weakThis = this->shared_from_this();
		http.asynPost(url, reqBody, [=](int code, const HttpHeaders& rspHeaders, const std::string& rspBuf) {
			//auto _this = weakThis.lock();
			//if (!_this) return;

			int result = 0;
			std::string msg = "succ";

			if (code != 0) {
				result = code;
				msg = std::string("http request error :") ;
				goto myEXIT;
			}


			{//解析回包
				Json::Value Val;
				Json::Reader reader;
				if (!reader.parse(rspBuf.c_str(), rspBuf.c_str() + rspBuf.size(), Val)) { //从ifs中读取数据到jsonRoot
					msg = std::string("parse json error :");
					result = -1;
					goto myEXIT;
				}

				if (Val.isMember("Response")) {
					auto Response = Val["Response"];

					if (Response.isMember("Error")) { //失败，错误返回
						auto error = Response["Error"];
						if (error.isMember("Code")) {
							result = error["Code"].asInt();
						}
						if (error.isMember("Message")) {
							msg = error["Message"].asString();
						}
					}
					else {
						msg = rspBuf;
					}
				}
			}

		myEXIT:
			if (callback) {
				callback(TICMODULE_RECORD, result, msg.c_str());
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
