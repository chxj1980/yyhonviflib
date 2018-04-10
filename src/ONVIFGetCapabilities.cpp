#include "ONVIFGetCapabilities.h"
#include "ONVIFXAddrMap.h"
using namespace std; 
namespace yyhonviflib
{
	
ONVIFGetCapabilities::ONVIFGetCapabilities()
{
}
ONVIFGetCapabilities::~ONVIFGetCapabilities()
{
}
int ONVIFGetCapabilities::GetCapabilities(char ** XAddrMap, const char *DeviceXAddr, int _timeout)//PRE_AUTH 
{
	int result = 0;
    int len    = 0;
    struct soap *soap = NULL;
    string Empty = "NULL";
    _tds__GetCapabilities           Capabil_req;
    _tds__GetCapabilitiesResponse   Capabil_rep;
    soap = SoapInit.SoapInit(_timeout);
    if(soap == NULL)
    {
        SoapTool.SoapPerror(soap, "SoapInit");
        return -1;
    }
    result = soap_call___tds__GetCapabilities(soap, DeviceXAddr, NULL, &Capabil_req, Capabil_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "GetCapabilities");
    else
    {
        if(Capabil_rep.Capabilities->Analytics->XAddr.empty())
            memcpy(XAddrMap[ANALYTICS_XADDR], Empty.c_str(), 5);
        else
        {
            len = strlen((Capabil_rep.Capabilities->Analytics->XAddr).c_str());
            memcpy(XAddrMap[ANALYTICS_XADDR], (Capabil_rep.Capabilities->Analytics->XAddr).c_str(), len + 1);
        }
        if(Capabil_rep.Capabilities->Device->XAddr.empty())
            memcpy(XAddrMap[DEVICE_XADDR], Empty.c_str(), 5);
        else
        {
            len = strlen((Capabil_rep.Capabilities->Device->XAddr).c_str());
            memcpy(XAddrMap[DEVICE_XADDR], (Capabil_rep.Capabilities->Device->XAddr).c_str(), len + 1);
        }
        if(Capabil_rep.Capabilities->Events->XAddr.empty())
            memcpy(XAddrMap[EVENTS_XADDR], Empty.c_str(), 5);
        else
        {
            len = strlen((Capabil_rep.Capabilities->Events->XAddr).c_str());
            memcpy(XAddrMap[EVENTS_XADDR], (Capabil_rep.Capabilities->Events->XAddr).c_str(), len + 1);
        }
        if(Capabil_rep.Capabilities->Imaging->XAddr.empty())
            memcpy(XAddrMap[IMAGING_XADDR], Empty.c_str(), 5);
        else
        {
            len = strlen((Capabil_rep.Capabilities->Imaging->XAddr).c_str());
            memcpy(XAddrMap[IMAGING_XADDR], (Capabil_rep.Capabilities->Imaging->XAddr).c_str(), len + 1);
        }
        if(Capabil_rep.Capabilities->Media->XAddr.empty())
            memcpy(XAddrMap[MEDIA_XADDR], Empty.c_str(), 5);
        else
        {
            len = strlen((Capabil_rep.Capabilities->Media->XAddr).c_str());
            memcpy(XAddrMap[MEDIA_XADDR], (Capabil_rep.Capabilities->Media->XAddr).c_str(), len + 1);
        }
        if(Capabil_rep.Capabilities->PTZ->XAddr.empty())
            memcpy(XAddrMap[PTZ_XADDR], Empty.c_str(), 5);
        else
        {
            len = strlen((Capabil_rep.Capabilities->PTZ->XAddr).c_str());
            memcpy(XAddrMap[PTZ_XADDR], (Capabil_rep.Capabilities->PTZ->XAddr).c_str(), len + 1);
        }
        if(Capabil_rep.Capabilities->Extension->DeviceIO == NULL)
            memcpy(XAddrMap[DEVICEIO_XADDR], Empty.c_str(), 5);
        else
        {
            len = strlen((Capabil_rep.Capabilities->Extension->DeviceIO->XAddr).c_str());
            memcpy(XAddrMap[DEVICEIO_XADDR], (Capabil_rep.Capabilities->Extension->DeviceIO->XAddr).c_str(), len + 1);
        }
        
        if(Capabil_rep.Capabilities->Extension->Display == NULL)
            memcpy(XAddrMap[DISPLAY_XADDR], Empty.c_str(), 5);
        else
        {
            len = strlen((Capabil_rep.Capabilities->Extension->Display->XAddr).c_str());
            memcpy(XAddrMap[DISPLAY_XADDR], (Capabil_rep.Capabilities->Extension->Display->XAddr).c_str(), len + 1);
        }

        if(Capabil_rep.Capabilities->Extension->Recording == NULL)
            memcpy(XAddrMap[RECORDING_XADDR], Empty.c_str(), 5);
        else
        {
            len = strlen((Capabil_rep.Capabilities->Extension->Recording->XAddr).c_str());
            memcpy(XAddrMap[RECORDING_XADDR], (Capabil_rep.Capabilities->Extension->Recording->XAddr).c_str(), len + 1);
        }
        if(Capabil_rep.Capabilities->Extension->Search == NULL)
            memcpy(XAddrMap[SEARCH_XADDR], Empty.c_str(), 5);
        else
        {
            len = strlen((Capabil_rep.Capabilities->Extension->Search->XAddr).c_str());
            memcpy(XAddrMap[SEARCH_XADDR], (Capabil_rep.Capabilities->Extension->Search->XAddr).c_str(), len + 1);
        }
        if(Capabil_rep.Capabilities->Extension->Replay == NULL)
            memcpy(XAddrMap[REPLAY_XADDR], Empty.c_str(), 5);
        else
        {
            len = strlen((Capabil_rep.Capabilities->Extension->Replay->XAddr).c_str());
            memcpy(XAddrMap[REPLAY_XADDR], (Capabil_rep.Capabilities->Extension->Replay->XAddr).c_str(), len + 1);
        }
        if(Capabil_rep.Capabilities->Extension->Receiver == NULL)
            memcpy(XAddrMap[RECEIVER_XADDR], Empty.c_str(), 5);
        else
        {
            len = strlen((Capabil_rep.Capabilities->Extension->Receiver->XAddr).c_str());
            memcpy(XAddrMap[RECEIVER_XADDR], (Capabil_rep.Capabilities->Extension->Receiver->XAddr).c_str(), len + 1);
        }
        if(Capabil_rep.Capabilities->Extension->AnalyticsDevice == NULL)
            memcpy(XAddrMap[ANALYTICSDEVICE_XADDR], Empty.c_str(), 5);
        else
        {
            len = strlen((Capabil_rep.Capabilities->Extension->AnalyticsDevice->XAddr).c_str());
            memcpy(XAddrMap[ANALYTICSDEVICE_XADDR], (Capabil_rep.Capabilities->Extension->AnalyticsDevice->XAddr).c_str(), len + 1);
        }

    }
    SoapTool.SoapFree(soap); 
    return result;
}
} //end namespace