#ifndef _ONVIFSOAPTOOL_H_
#define _ONVIFSOAPTOOL_H_

#include "soapH.h"
#include <assert.h>


namespace yyhonviflib
{
class ONVIFSoapTool
{
public:
	ONVIFSoapTool();
	~ONVIFSoapTool();
	void* SoapMalloc(struct soap *soap, unsigned int n);
	void SoapPerror(struct soap *soap, const char *str);
	void SoapFree(struct soap *soap);
private:
};
} //end namespace
#endif
