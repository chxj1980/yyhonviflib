#include "ONVIFSoapInit.h"
#include "wsdd.nsmap"
#include "wsseapi.h" 

using namespace std; 
namespace yyhonviflib
{
ONVIFSoapInit::ONVIFSoapInit()
{
  
}
ONVIFSoapInit::~ONVIFSoapInit()
{

}
struct soap* ONVIFSoapInit::SoapDiscoveryInit(int _timeout)
{
    struct soap *soap = NULL;
    struct SOAP_ENV__Header *header = NULL;
    const char *wsa_To = "urn:schemas-xmlsoap-org:ws:2005:04:discovery";
    const char *wsa_Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe";
    int timeout;
    soap = soap_new();
    if(soap == NULL)
        SoapTool.SoapPerror(soap, "soap_new");
    soap_set_namespaces(soap, namespaces);
    if(_timeout > 0)
        timeout = _timeout;
    else
        timeout = TIMEOUT;
    soap->recv_timeout    = timeout;                                            
    soap->send_timeout    = timeout;
    soap->connect_timeout = timeout;
    soap_set_mode(soap, SOAP_C_UTFSTRING);
    header = (struct SOAP_ENV__Header *)SoapTool.SoapMalloc(soap, sizeof(struct SOAP_ENV__Header));
    soap_default_SOAP_ENV__Header(soap, header);
    header->wsa__MessageID = NewUuid();
    header->wsa__To        = (char*)SoapTool.SoapMalloc(soap, strlen(wsa_To) + 1);
    header->wsa__Action    = (char*)SoapTool.SoapMalloc(soap, strlen(wsa_Action) + 1);
    strcpy(header->wsa__To, wsa_To);
    strcpy(header->wsa__Action, wsa_Action);
    soap->header = header;
    return soap;
}
struct soap* ONVIFSoapInit::SoapInit(int _timeout)
{
    struct soap *soap = NULL;
    struct SOAP_ENV__Header *header = NULL;
    int timeout;
    soap = soap_new();
    if(soap == NULL)
    {
        SoapTool.SoapPerror(soap, "soap_new");
        return NULL;
    }
    soap_set_namespaces(soap, namespaces);
    if(_timeout > 0)
        timeout = _timeout;
    else
        timeout = TIMEOUT;
    soap->recv_timeout    = timeout;                                            
    soap->send_timeout    = timeout;
    soap->connect_timeout = timeout;
    soap_set_mode(soap, SOAP_C_UTFSTRING);
    header = (struct SOAP_ENV__Header *)SoapTool.SoapMalloc(soap, sizeof(struct SOAP_ENV__Header));
    soap_default_SOAP_ENV__Header(soap, header);
    return soap;
}

int ONVIFSoapInit::SetAuthInfo(struct soap *soap, const char *username, const char *password)
{
    int result = 0;
    result = soap_wsse_add_UsernameTokenDigest(soap, NULL, username, password);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "soap_wsse_add_UsernameTokenDigest");
    return result;
}
char* ONVIFSoapInit::NewUuid() 
{
    uuid_t uuid;
    uuid_generate(uuid);
    char* uuid_s = (char*)malloc(42);
    strcpy(uuid_s, "uuid:");
    uuid_unparse_lower(uuid, uuid_s + 5);
    return uuid_s;
}


} //end namespace
