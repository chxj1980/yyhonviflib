#ifndef _ONVIFSOAPINIT_H_
#define _ONVIFSOAPINIT_H_

#include "ONVIFSoapTool.h"
#include "soapH.h"
#include <iostream>
#include <assert.h>
#include "uuid/uuid.h"

using namespace std;
namespace yyhonviflib
{
class ONVIFSoapInit
{
public:
	ONVIFSoapInit();
	~ONVIFSoapInit();
	struct soap* SoapDiscoveryInit(int _timeout);
	struct soap* SoapInit(int _timeout);
	int SetAuthInfo(struct soap *soap, const char *username, const char *password);
	char* NewUuid(); 
private:
	int TIMEOUT = 2;
	ONVIFSoapTool SoapTool;
};
} //end namespace
#endif
