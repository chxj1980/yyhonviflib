#ifndef _ONVIFREMOTEDISCOVERY_H_
#define _ONVIFREMOTEDISCOVERY_H_

#include "ONVIFSoapInit.h"
#include "ONVIFSoapTool.h"

namespace yyhonviflib
{
class ONVIFRemoteDiscovery
{
public:
	ONVIFRemoteDiscovery();
	~ONVIFRemoteDiscovery();
	int RemoteDiscovery(char **DeviceXAddr, int _timeout, int &DeviceCount);
private:
	const int TIMEOUT = 2;
	const char *soap_Endpoint;
	const char *probe_Types;
	const char *scope_Item;
	ONVIFSoapInit SoapInit;
	ONVIFSoapTool SoapTool;
};
} //end namespace
#endif