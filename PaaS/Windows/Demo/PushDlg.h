#pragma once

#include <memory>
#include <Live/ITXLivePlayer.h>
#include "..\SDK\TIC\localrecord\TICLocalRecord.h"

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

public:
	ITXLivePlayer* mLivePlayer;
	CButton chkPushEnable_;
	TICLocalRecorder* mLocalRecorder;
public:
	afx_msg void OnBnClickedChkEnableDraw();
	afx_msg void OnBnClickedCheckEnablePush();
};