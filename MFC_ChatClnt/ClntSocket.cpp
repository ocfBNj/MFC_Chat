#include "pch.h"
#include "ClntSocket.h"
#include "MFC_ChatClntDlg.h"


void ClntSocket::OnConnect(int nErrorCode) {
	// TODO: Add your specialized code here and/or call the base class
	TRACE("%s\n", __func__);

	if (!nErrorCode) {
		TRACE("%ls\n", L"OK");
	}

	CAsyncSocket::OnConnect(nErrorCode);
}


void ClntSocket::OnReceive(int nErrorCode) {
	// TODO: Add your specialized code here and/or call the base class
	TRACE("%s\n", __func__);

	CMFCChatClntDlg* dlg =(CMFCChatClntDlg*)AfxGetApp()->GetMainWnd();

	char buf[64];
	int size = dlg->conn->Receive(buf, sizeof(buf) - 1);
	buf[size] = 0;
	dlg->writeInList(CString(_T("·þÎñÆ÷£º")) + CString(buf));

	CAsyncSocket::OnReceive(nErrorCode);
}


void ClntSocket::OnClose(int nErrorCode) {
	// TODO: Add your specialized code here and/or call the base class
	TRACE("%s\n", __func__);
	CAsyncSocket::OnClose(nErrorCode);
}


void ClntSocket::OnAccept(int nErrorCode) {
	// TODO: Add your specialized code here and/or call the base class
	TRACE("%s\n", __func__);
	CAsyncSocket::OnAccept(nErrorCode);
}


void ClntSocket::OnOutOfBandData(int nErrorCode) {
	// TODO: Add your specialized code here and/or call the base class
	TRACE("%s\n", __func__);
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}


void ClntSocket::OnSend(int nErrorCode) {
	// TODO: Add your specialized code here and/or call the base class
	TRACE("%s\n", __func__);
	CAsyncSocket::OnSend(nErrorCode);
}
