#include "pch.h"
#include "ClntSocket.h"
#include "MFC_ChatClntDlg.h"


void ClntSocket::OnConnect(int nErrorCode) {
	// TODO: Add your specialized code here and/or call the base class
	TRACE("ClntSocket::OnConnect");

	CAsyncSocket::OnConnect(nErrorCode);
}


void ClntSocket::OnReceive(int nErrorCode) {
	// TODO: Add your specialized code here and/or call the base class
	CMFCChatClntDlg* dlg =(CMFCChatClntDlg*)AfxGetApp()->GetMainWnd();

	char buf[64];
	int size = dlg->conn->Receive(buf, sizeof(buf) - 1);
	buf[size] = 0;
	TRACE("接受到: %s\n", buf);
	dlg->writeInList(CString(_T("服务器：")) + CString(buf));

	CAsyncSocket::OnReceive(nErrorCode);
}
