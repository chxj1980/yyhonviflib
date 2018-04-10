#ifndef _ONVIFDEVICEIO_H_
#define _ONVIFDEVICEIO_H_

#include "ONVIFSoapInit.h"
#include "ONVIFSoapTool.h"

namespace yyhonviflib
{
class ONVIFDeviceIO
{
public:
	ONVIFDeviceIO();
	~ONVIFDeviceIO();
    int SaveRelayOutputs(_tds__GetRelayOutputsResponse &GetRel_rep, const char *Path);
	int GetRelayOutputs(const char *Path, char *DeviceIOXAddr, int _timeout, const char *UserName, const char *PassWord);
    int SetRelayOutputState(int RelayState, char *RelayOutputToken, char *DeviceIOXAddr, int _timeout, const char *UserName, const char *PassWord);
private:
	ONVIFSoapInit SoapInit;
	ONVIFSoapTool SoapTool;
};
} //end namespace
#endif