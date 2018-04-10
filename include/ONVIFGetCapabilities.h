#ifndef _ONVIFGETCAPABILITIES_H_
#define _ONVIFGETCAPABILITIES_H_

#include "ONVIFSoapInit.h"
#include "ONVIFSoapTool.h"

namespace yyhonviflib
{
class ONVIFGetCapabilities
{
public:
	ONVIFGetCapabilities();
	~ONVIFGetCapabilities();
	int GetCapabilities(char ** XAddrMap, const char *DeviceXAddr, int _timeout);//PRE_AUTH
private:
	ONVIFSoapInit SoapInit;
	ONVIFSoapTool SoapTool;
};
} //end namespace
#endif