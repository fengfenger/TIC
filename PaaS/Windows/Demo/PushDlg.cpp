#include "stdafx.h"
#include "TICDemo.h"
#include "PushDlg.h"
#include "resource.h"
#include "Config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CTICDemoApp theApp;

BEGIN_MESSAGE_MAP(CPushDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_ENABLE_DRAW, &CPushDlg::OnBnClickedChkEnableDraw)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_PUSH, &CPushDlg::OnBnClickedCheckEnablePush)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_LOCAL_RECORD, &CPushDlg::OnLvnItemchangedListLocalRecord)
	ON_BN_CLICKED(IDC_BTN_INIT, &CPushDlg::OnBnClickedBtnInit)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CPushDlg::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_PAUSE_RESUME2, &CPushDlg::OnBnClickedBtnPauseResume2)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_PAUSE, &CPushDlg::OnBnClickedCheckEnablePause)
	ON_BN_CLICKED(IDC_BTN_REFRESSH_RESULT, &CPushDlg::OnBnClickedBtnRefresshResult)
END_MESSAGE_MAP()

CPushDlg::CPushDlg(CWnd* pParent)
	: CDialogEx(IDD_PUSH_DIALOG, pParent)
{
	mLocalRecorder = TICLocalRecorder::GetInstance();
	mLivePlayer = createTXLivePlayer();
}

BOOL CPushDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mListRecord.InsertColumn(0, _T("文件名"), LVCFMT_LEFT, 100);
	mListRecord.InsertColumn(1, _T("录制人"), LVCFMT_LEFT, 80);
	mListRecord.InsertColumn(2, _T("时长"), LVCFMT_LEFT, 72);

	return TRUE;
}

void CPushDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK_ENABLE_PUSH, chkPushEnable_);
	DDX_Control(pDX, IDC_LIST_LOCAL_RECORD, mListRecord);
	DDX_Control(pDX, IDC_CHECK_ENABLE_PAUSE, checkPaused_);
}


void CPushDlg::OnBnClickedChkEnableDraw()
{
	
}

void CPushDlg::OnBnClickedCheckEnablePush()
{
	bool selected = (chkPushEnable_.GetCheck() == BST_CHECKED);

	if (selected) {
		startRecord();
	}
	else {
		stopRecord();
	}
}

void CPushDlg::StartPlay() {
	HWND playView = GetDlgItem(IDC_PLAYER_RENDER)->m_hWnd;
	mLivePlayer->setRenderFrame(playView);
	mLivePlayer->startPlay("http://29734.liveplay.myqcloud.com/live/seventest.flv", PLAY_TYPE_LIVE_FLV);
}

void CPushDlg::StopPlay() {
	mLivePlayer->setRenderFrame(NULL);
	mLivePlayer->stopPlay();
}


void CPushDlg::UpdateFileList()
{



}

void CPushDlg::initRecord(int appid, const std::string& user, const std::string& sig) {
	if (appid == 0 || user.empty() || sig.empty()) {
		AfxMessageBox(_T("初始参数有误!"), MB_OK);
		return;
	}

	TEduRecordAuthParam auth(appid, user, sig);

	std::weak_ptr< CPushDlg> weakSelf = this->shared_from_this();
	mLocalRecorder->init(auth, [this, weakSelf](TICModule module, int code, const char *desc) {
		std::shared_ptr<CPushDlg> self = weakSelf.lock();
		if (!self)
			return;

		if (code != 0) {
			AfxMessageBox(_T("认证失败!"), MB_OK);
		}
		else {
			self->mIsAuth = true;
		}
	});
}

void CPushDlg::exitRecord() {
	std::weak_ptr< CPushDlg> weakSelf = this->shared_from_this();
	mLocalRecorder->exit([this, weakSelf](TICModule module, int code, const char *desc) {
		std::shared_ptr<CPushDlg> self = weakSelf.lock();
		if (!self)
			return;

		if (code != 0) {
			//AfxMessageBox(_T("停止录制失败"), MB_OK);
		}
		else {
			self->mIsAuth = false;
		}
	});
}

void CPushDlg::startRecord() {
	std::weak_ptr< CPushDlg> weakSelf = this->shared_from_this();

	TEduRecordParam para;
	para.classId = theApp.getClassId();
	para.AppProc = "TICDemo.exe";
	mLocalRecorder->startLocalRecord(para, "E:\\test\\test.flv", [this, weakSelf](TICModule module, int code, const char *desc) {
		std::shared_ptr<CPushDlg> self = weakSelf.lock();
		if (!self)
			return;

		if (code != 0) {
			//AfxMessageBox(_T("开始录制失败"), MB_OK);
		}
		else {
			//AfxMessageBox(_T("开始录制"), MB_OK);
		}
	});
}

void CPushDlg::stopRecord() {
	std::weak_ptr< CPushDlg> weakSelf = this->shared_from_this();
	mLocalRecorder->stopLocalRecord([this, weakSelf](TICModule module, int code, const char *desc) {
		std::shared_ptr<CPushDlg> self = weakSelf.lock();
		if (!self)
			return;

		if (code != 0) {
			//AfxMessageBox(_T("停止录制失败"), MB_OK);
		}
		else {
			//AfxMessageBox(_T("停止录制"), MB_OK);
		}
	});
}


void CPushDlg::pauseRecord() {
	std::weak_ptr< CPushDlg> weakSelf = this->shared_from_this();
	mLocalRecorder->pauseLocalRecord([this, weakSelf](TICModule module, int code, const char *desc) {
		std::shared_ptr<CPushDlg> self = weakSelf.lock();
		if (!self)
			return;

		if (code != 0) {
			//AfxMessageBox(_T("暂停录制失败"), MB_OK);
		}
		else {
			//AfxMessageBox(_T("暂停录制"), MB_OK);
		}
	});
}

void CPushDlg::resumeRecord() {
	std::weak_ptr< CPushDlg> weakSelf = this->shared_from_this();
	mLocalRecorder->resumeLocalRecord([this, weakSelf](TICModule module, int code, const char *desc) {
		std::shared_ptr<CPushDlg> self = weakSelf.lock();
		if (!self)
			return;

		if (code != 0) {
			//AfxMessageBox(_T("暂停录制失败"), MB_OK);
		}
		else {
			//AfxMessageBox(_T("暂停录制"), MB_OK);
		}
	});
}

void  CPushDlg::getRecord() {
	int appid = Config::GetInstance().SdkAppId();
	std::string userid = theApp.getUserId();
	const RecordKey key = RecordKey(appid, 0, std::string(""), std::string(""));
	std::weak_ptr< CPushDlg> weakSelf = this->shared_from_this();
	mLocalRecorder->getRecordResult(key, [this, weakSelf](TICModule module, int code, const char *desc) {
		std::shared_ptr<CPushDlg> self = weakSelf.lock();
		if (!self)
			return;

		if (code == 0) {
			self->parseRecordInfos(desc);
			self->refreshRecordInfo();
		}
	});
}

void CPushDlg::parseRecordInfos(const char *desc) {
	std::string rspBuf = desc;
	Json::Value Val;
	Json::Reader reader;
	if (!reader.parse(rspBuf.c_str(), rspBuf.c_str() + rspBuf.size(), Val)) { //从ifs中读取数据到jsonRoot
		return;
	}
	mInfos.clear();
	if (Val.isMember("record_info_list")) {
		auto record_info_list = Val["record_info_list"];
		if (record_info_list.isArray()) {

			int size = record_info_list.size();

			for (int i = 0; i < size; i++) {
				RecordInfo info;
				auto record = record_info_list[i];
				if (record.isMember("RoomId")) {
					info.RoomId = record["RoomId"].asLargestUInt();
				}

				if (record.isMember("StartTime")) {
					info.StartTime = record["StartTime"].asLargestUInt();
				}

				if (record.isMember("UserId")) {
					info.UserId = record["UserId"].asString();
				}

				if (record.isMember("VideoOutputDuration")) {
					info.VideoOutputDuration = record["VideoOutputDuration"].asLargestUInt();
				}

				if (record.isMember("VideoOutputUrl")) {
					info.VideoOutputUrl = record["VideoOutputUrl"].asString();
				}

				if (record.isMember("VideoOutputSize")) {
					info.VideoOutputSize = record["VideoOutputSize"].asLargestUInt();
				}

				mInfos.push_back(info);
			}
		}
	}
}

void CPushDlg::refreshRecordInfo() {
	mListRecord.SetRedraw(FALSE);
	mListRecord.DeleteAllItems();
	
	int size = mInfos.size();
	for (uint32_t i = 0; i < size; ++i)
	{
		RecordInfo fileInfo = mInfos[i];
		mListRecord.InsertItem(i, _T(""));
		mListRecord.SetItemText(i, 0, a2w(fileInfo.VideoOutputUrl.c_str(), CP_UTF8).c_str());
		mListRecord.SetItemText(i, 1, a2w(fileInfo.UserId.c_str(), CP_UTF8).c_str());
		mListRecord.SetItemText(i, 2, a2w(std::to_string(fileInfo.VideoOutputDuration/60).c_str(), CP_UTF8).c_str());
	}
	if (size > 0) // 选中当前文件
	{
		mListRecord.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		mListRecord.SetFocus();
	}
	mListRecord.SetRedraw(TRUE);
}

void CPushDlg::OnLvnItemchangedLocalRecord(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	*pResult = 0;
}


void CPushDlg::OnNMDblclkLocalRecord(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	*pResult = 0;
}


void CPushDlg::OnLvnItemchangedListLocalRecord(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CPushDlg::OnBnClickedBtnInit()
{
	int appid = Config::GetInstance().SdkAppId();
	const std::string uid = theApp.getUserId();
	const std::string sig = theApp.getUserSig();
	initRecord(appid, uid, sig);
}


void CPushDlg::OnBnClickedBtnExit()
{
	exitRecord();
}

void CPushDlg::OnBnClickedBtnPauseResume2()
{
	
}


void CPushDlg::OnBnClickedCheckEnablePause()
{
	bool selected = (checkPaused_.GetCheck() == BST_CHECKED);

	if (selected) {
		pauseRecord();
	}
	else {
		resumeRecord();
	}
}


void CPushDlg::OnBnClickedBtnRefresshResult()
{
	getRecord();
}
