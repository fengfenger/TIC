#pragma once

#include <memory>
#include <Live/ITXLivePlayer.h>
#include "..\SDK\TIC\localrecord\TICLocalRecord.h"
#include "afxcmn.h"

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
	void StartPlay();
	void StopPlay();
	virtual BOOL OnInitDialog() override;
	virtual void DoDataExchange(CDataExchange* pDX) override;
	void UpdateFileList();

	void initRecord();
	void startRecord();
	void stopRecord();
	void pauseRecord();
	void resumeRecord();
	void getRecord();
	void exitRecord();

public:
	ITXLivePlayer* mLivePlayer;
	CButton chkPushEnable_;
	CListCtrl mListRecord;
	TICLocalRecorder* mLocalRecorder;
public:
	afx_msg void OnBnClickedChkEnableDraw();
	afx_msg void OnBnClickedCheckEnablePush();
	afx_msg void OnLvnItemchangedLocalRecord(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkLocalRecord(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListLocalRecord(NMHDR *pNMHDR, LRESULT *pResult);
};