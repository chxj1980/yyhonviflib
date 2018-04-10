#include "ONVIFGetDeviceInformation.h"

using namespace std; 
namespace yyhonviflib
{
	
ONVIFGetDeviceInformation::ONVIFGetDeviceInformation()
{
}
ONVIFGetDeviceInformation::~ONVIFGetDeviceInformation()
{
}
int ONVIFGetDeviceInformation::GetDeviceInformation(char *SerialNumber, const char *DeviceXAddr, int _timeout, const char *UserName, const char *PassWord)
{
	int result = 0;
    struct soap *soap = NULL;
    _tds__GetDeviceInformation           devinfo_req;
    _tds__GetDeviceInformationResponse   devinfo_rep;
    soap = SoapInit.SoapInit(_timeout);
    if(soap == NULL)
    {
        SoapTool.SoapPerror(soap, "SoapInit");
        return -1;
    }
    result = SoapInit.SetAuthInfo(soap, UserName, PassWord);
    if(result != SOAP_OK)
    {
        SoapTool.SoapPerror(soap, "SetAuthInfo");
        SoapTool.SoapFree(soap);   
        return result;
    }
    result = soap_call___tds__GetDeviceInformation(soap, DeviceXAddr, NULL, &devinfo_req, devinfo_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "GetDeviceInformation");
    else
    {
        cout<<"Manufacturer   :"<<devinfo_rep.Manufacturer<<endl;
        cout<<"Model          :"<<devinfo_rep.Model<<endl;
        cout<<"FirmwareVersion:"<<devinfo_rep.FirmwareVersion<<endl;
        cout<<"SerialNumber   :"<<devinfo_rep.SerialNumber<<endl;
        cout<<"HardwareId     :"<<devinfo_rep.HardwareId<<endl;
        memcpy(SerialNumber, (devinfo_rep.SerialNumber).c_str(), strlen((devinfo_rep.SerialNumber).c_str()));
    }
    SoapTool.SoapFree(soap);   
    return result;
}
} //end namespace