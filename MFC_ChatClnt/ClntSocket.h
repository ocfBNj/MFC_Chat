#pragma once

#include <afxsock.h>

class ClntSocket : public CAsyncSocket {
	
public:
	virtual void OnConnect(int nErrorCode);
};

