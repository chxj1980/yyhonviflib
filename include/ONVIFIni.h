#ifndef _ONVIFINI_H_
#define _ONVIFINI_H_

#include <map> 
#include <string> 
namespace yyhonviflib
{
class ONVIFIni
{
public:
	ONVIFIni();
	virtual ~ONVIFIni();
	int ReadIni(const char *Path, char *Root, char *Key, char *Value);
	int WriteIni(const char *Path, char *Root, char *Key, char *Value);
};
} //end namespace
#endif