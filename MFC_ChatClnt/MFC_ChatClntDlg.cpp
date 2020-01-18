
// MFC_ChatClntDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFC_ChatClnt.h"
#include "MFC_ChatClntDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "ClntSocket.h"


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCChatClntDlg dialog



CMFCChatClntDlg::CMFCChatClntDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_CHATCLNT_DIALOG, pParent), conn(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatClntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCChatClntDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMFCChatClntDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMFCChatClntDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CMFCChatClntDlg::OnBnClickedButtonDisconnect)
END_MESSAGE_MAP()


// CMFCChatClntDlg message handlers

BOOL CMFCChatClntDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_IPADDRESS)->SetWindowTextW(_T("127.0.0.1"));
	GetDlgItem(IDC_EDIT_PORT)->SetWindowTextW(_T("9091"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCChatClntDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCChatClntDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCChatClntDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatClntDlg::writeInList(const CString& _msg) {
	time = CTime::GetCurrentTime();
	CString msg = time.Format("%X ");
	msg += _msg;

	CListBox* list = (CListBox*)GetDlgItem(IDC_LIST_HISTORY);
	list->AddString(msg);

	UpdateData(FALSE);
}

void CMFCChatClntDlg::clearSendEdit() {
	GetDlgItem(IDC_EDIT_SEND)->SetWindowTextW(_T(""));
}

void CMFCChatClntDlg::OnBnClickedButtonSend() {
	// TODO: Add your control notification handler code here
	if (conn) {
		CString msg;
		GetDlgItemText(IDC_EDIT_SEND, msg);
		if (msg.GetLength()) {
			TRACE("发送消息\n");
			CT2A ascii(msg);
			writeInList(CString("我：") + msg);

			conn->Send(ascii.m_psz, msg.GetLength() * sizeof(TCHAR));
			clearSendEdit();
		}
	}
}


void CMFCChatClntDlg::OnBnClickedButtonConnect() {
	// TODO: Add your control notification handler code here
	conn = new ClntSocket();
	conn->Create();

	CString ipAddr;
	CString port;
	GetDlgItem(IDC_IPADDRESS)->GetWindowTextW(ipAddr);
	GetDlgItem(IDC_EDIT_PORT)->GetWindowTextW(port);

	if (conn->Connect((LPCTSTR)ipAddr, _ttoi(port)) != SOCKET_ERROR) {
		GetDlgItem(IDC_STATIC_STATUS)->SetWindowTextW(_T("已连接"));
		writeInList(_T("连接服务器成功！"));
		
		//UpdateData(FALSE);
	}

	
}


void CMFCChatClntDlg::OnBnClickedButtonDisconnect() {
	conn->Close();
	conn = NULL;
	GetDlgItem(IDC_STATIC_STATUS)->SetWindowTextW(_T("未连接"));
}
