#include "pch.h"
#include "ClntSocket.h"


void ClntSocket::OnConnect(int nErrorCode) {
	// TODO: Add your specialized code here and/or call the base class
	TRACE("ClntSocket::OnConnect");

	CAsyncSocket::OnConnect(nErrorCode);
}
