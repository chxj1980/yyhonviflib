#include "ONVIFSoapTool.h"

                          
namespace yyhonviflib
{
ONVIFSoapTool::ONVIFSoapTool()
{

}
ONVIFSoapTool::~ONVIFSoapTool()
{

}
void ONVIFSoapTool::SoapPerror(struct soap *soap, const char *str)
{
    if (NULL == str) 
    {
        printf("[soap] error: %d, %s, %s\n", soap->error, *soap_faultcode(soap), *soap_faultstring(soap));
    } 
    else 
    {
        printf("[soap] %s error: %d, %s, %s\n", str, soap->error, *soap_faultcode(soap), *soap_faultstring(soap));
    }
    return;
}
void* ONVIFSoapTool::SoapMalloc(struct soap *soap, unsigned int n)
{
    void *p = NULL;

    if (n > 0) 
    {
        p = soap_malloc(soap, n);
        assert(NULL != p);
        memset(p, 0x00 ,n);
    }
    return p;
}
void ONVIFSoapTool::SoapFree(struct soap *soap)
{
    if(soap != NULL)
    {
        soap_destroy(soap);  
        soap_end(soap);  
        soap_done(soap);
        soap_free(soap);
    }   
}

} //end namespace
