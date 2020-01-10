#pragma once

#include <memory>
#include <Live/ITXLivePlayer.h>
#include "..\SDK\TIC\localrecord\TICLocalRecord.h"
#include "afxcmn.h"
#include "afxwin.h"

class CPushDlg
	: public CDialogEx
	, public std::enable_shared_from_this<CPushDlg>
{
	DECLARE_MESSAGE_MAP()
public:
	CPushDlg(CWnd* pParent = nullptr);

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PUSH_DIALOG };
#endif

private:
	void StartPlay(const std::string& url);
	void StopPlay();
	virtual BOOL OnInitDialog() override;
	virtual void DoDataExchange(CDataExchange* pDX) override;

	void initRecord(int appid, const std::string& user, const std::string& sig);
	void startRecord();
	void stopRecord();
	void pauseRecord();
	void resumeRecord();
	void getRecord();
	void exitRecord();

	void parseRecordInfos(const char *desc);
	void refreshRecordInfo();


	struct RecordInfo {
		uint32_t RoomId = 0;
		uint64_t SplicTime = 0;
		uint64_t StartTime = 0;
		uint64_t VideoOutputDuration = 0;
		uint64_t VideoOutputSize = 0;

		std::string TaskId;
		std::string UserId;
		std::string VideoOutputId;
		std::string VideoOutputType;
		std::string VideoOutputUrl;
	};

protected:
	ITXLivePlayer* mLivePlayer;
	CButton chkPushEnable_;
	CListCtrl mListRecord;
	TICLocalRecorder* mLocalRecorder;
	bool mIsAuth = false;
	CButton checkPaused_;
	std::vector<RecordInfo> mInfos;

public:
	afx_msg void OnBnClickedChkEnableDraw();
	afx_msg void OnBnClickedCheckEnablePush();
	afx_msg void OnLvnItemchangedLocalRecord(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkLocalRecord(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListLocalRecord(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnInit();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnPauseResume2();
	afx_msg void OnBnClickedCheckEnablePause();

	afx_msg void OnBnClickedBtnRefresshResult();
	afx_msg void OnNMDbClkListFile(NMHDR *pNMHDR, LRESULT *pResult);



};