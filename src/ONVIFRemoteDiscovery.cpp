#include "ONVIFRemoteDiscovery.h"

namespace yyhonviflib
{
ONVIFRemoteDiscovery::ONVIFRemoteDiscovery()
{
    soap_Endpoint = "soap.udp://239.255.255.250:3702";
    probe_Types   = "dn:NetworkVideoTransmitter";
    scope_Item    = "";
}
ONVIFRemoteDiscovery::~ONVIFRemoteDiscovery()
{

}
int ONVIFRemoteDiscovery::RemoteDiscovery(char **DeviceXAddr, int _timeout, int &DeviceCount)
{
    struct soap *soap = NULL;
    struct wsdd__ScopesType *scope = NULL; 
    int result = 0;
    struct wsdd__ProbeType reqProbe;
    struct __wsdd__ProbeMatches repProbe; 
    int i = 0;
    DeviceCount = 0;
    soap = SoapInit.SoapDiscoveryInit(_timeout);
    if(soap == NULL)
    {
        SoapTool.SoapPerror(soap, "SoapInit");
        return -1;
    }
    scope = (struct wsdd__ScopesType *)SoapTool.SoapMalloc(soap, sizeof(struct wsdd__ScopesType));
    soap_default_wsdd__ScopesType(soap, scope);
    scope->__item = (char*)SoapTool.SoapMalloc(soap, strlen(scope_Item) + 1);
    strcpy(scope->__item, scope_Item);

    memset(&reqProbe, 0x00, sizeof(struct wsdd__ProbeType));
    soap_default_wsdd__ProbeType(soap, &reqProbe);
    reqProbe.Scopes = scope;
    reqProbe.Types  = (char*)SoapTool.SoapMalloc(soap, strlen(probe_Types) + 1);     
    strcpy(reqProbe.Types, probe_Types);
    result = soap_send___wsdd__Probe(soap, soap_Endpoint, NULL, &reqProbe);
    if(result != SOAP_OK)
    {
        SoapTool.SoapPerror(soap, "soap_send___wsdd__Probe");
        SoapTool.SoapFree(soap);   
        return result;
    }

    while(result == SOAP_OK)
    {
        memset(&repProbe, 0x00, sizeof(repProbe));
        result = soap_recv___wsdd__ProbeMatches(soap, &repProbe);
        if(result != SOAP_OK)
            SoapTool.SoapPerror(soap, "soap_recv___wsdd__ProbeMatches");
        else
        {
            for(i = 0; i < repProbe.wsdd__ProbeMatches->__sizeProbeMatch; i++) 
            {
                DeviceCount++;
                strcpy(DeviceXAddr[i], repProbe.wsdd__ProbeMatches->ProbeMatch->XAddrs);
                cout<<"Target Service Address  : "<<repProbe.wsdd__ProbeMatches->ProbeMatch->XAddrs<<endl;  
                cout<<"Target EP Address       : "<<repProbe.wsdd__ProbeMatches->ProbeMatch->wsa__EndpointReference.Address<<endl;  
                cout<<"Target Type             : "<<repProbe.wsdd__ProbeMatches->ProbeMatch->Types<<endl;  
                cout<<"Target Metadata Version : "<<repProbe.wsdd__ProbeMatches->ProbeMatch->MetadataVersion<<endl;  
            }
        }
    }
    SoapTool.SoapFree(soap);   
    return result;
}
} //end namespace
