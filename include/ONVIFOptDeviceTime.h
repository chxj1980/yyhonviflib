#ifndef _ONVIFOPTDEVICETIME_H_
#define _ONVIFOPTDEVICETIME_H_

#include "ONVIFSoapInit.h"
#include "ONVIFSoapTool.h"

namespace yyhonviflib
{
class ONVIFOptDeviceTime
{
public:
	ONVIFOptDeviceTime();
	~ONVIFOptDeviceTime();
	int GetDeviceTime(const char *DeviceXAddr, int _timeout);//PRE_AUTH
	int SetDeviceTime(const char *DeviceXAddr, int _timeout, const char *UserName, const char *PassWord);
private:
	void GetHostTZ(char *TZ, unsigned int sizeTZ);
	ONVIFSoapInit SoapInit;
	ONVIFSoapTool SoapTool;
};
} //end namespace
#endif