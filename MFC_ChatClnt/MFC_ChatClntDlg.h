
// MFC_ChatClntDlg.h : header file
//

#pragma once

class ClntSocket;
// CMFCChatClntDlg dialog
class CMFCChatClntDlg : public CDialogEx
{
// Construction
public:
	CMFCChatClntDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CHATCLNT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CTime time;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	ClntSocket* conn;

	void writeInList(const CString& msg);
	void clearSendEdit();

public:
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonChangeName();
	virtual void OnOK();
};
