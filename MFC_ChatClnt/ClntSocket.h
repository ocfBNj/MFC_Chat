#pragma once

#include <afxsock.h>

class ClntSocket : public CAsyncSocket {
public:
	virtual void OnConnect(int nErrorCode) override;
	virtual void OnReceive(int nErrorCode) override;
	virtual void OnClose(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnSend(int nErrorCode);
};

