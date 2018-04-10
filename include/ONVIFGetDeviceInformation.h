#ifndef _ONVIFGETDEVICEINFORMATION_H_
#define _ONVIFGETDEVICEINFORMATION_H_

#include "ONVIFSoapInit.h"
#include "ONVIFSoapTool.h"

namespace yyhonviflib
{
class ONVIFGetDeviceInformation
{
public:
	ONVIFGetDeviceInformation();
	~ONVIFGetDeviceInformation();
	int GetDeviceInformation(char *SerialNumber, const char *DeviceXAddr, int _timeout, const char *UserName, const char *PassWord);
private:
	ONVIFSoapInit SoapInit;
	ONVIFSoapTool SoapTool;
};
} //end namespace
#endif