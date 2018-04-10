#include "ONVIFOptDeviceTime.h"
#include <time.h>
namespace yyhonviflib
{
ONVIFOptDeviceTime::ONVIFOptDeviceTime()
{
}
ONVIFOptDeviceTime::~ONVIFOptDeviceTime()
{
}

int ONVIFOptDeviceTime::GetDeviceTime(const char *DeviceXAddr, int _timeout)//PRE_AUTH
{
    int result = 0;
    struct soap *soap = NULL;
    _tds__GetSystemDateAndTime         GetTm_req;
    _tds__GetSystemDateAndTimeResponse GetTm_rep;

    soap = SoapInit.SoapInit(_timeout);
    if(soap == NULL)
    {
        SoapTool.SoapPerror(soap, "SoapInit");
        return -1;
    }
    result = soap_call___tds__GetSystemDateAndTime(soap, DeviceXAddr, NULL, &GetTm_req, GetTm_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "GetDeviceTime");
    else
    {
        cout<<"SystemDateAndTime->TimeZone->TZ   :"<<GetTm_rep.SystemDateAndTime->TimeZone->TZ<<endl;
        cout<<"SystemDateAndTime->DateTimeType   :"<<GetTm_rep.SystemDateAndTime->DateTimeType<<endl;
        cout<<"SystemDateAndTime->LocalDateTime->Time->Hour      :"<<GetTm_rep.SystemDateAndTime->LocalDateTime->Time->Hour<<endl;
        cout<<"SystemDateAndTime->LocalDateTime->Time->Minute    :"<<GetTm_rep.SystemDateAndTime->LocalDateTime->Time->Minute<<endl;
        cout<<"SystemDateAndTime->LocalDateTime->Time->Second    :"<<GetTm_rep.SystemDateAndTime->LocalDateTime->Time->Second<<endl;
        cout<<"SystemDateAndTime->LocalDateTime->Date->Year      :"<<GetTm_rep.SystemDateAndTime->LocalDateTime->Date->Year<<endl;
        cout<<"SystemDateAndTime->LocalDateTime->Date->Month     :"<<GetTm_rep.SystemDateAndTime->LocalDateTime->Date->Month<<endl;
        cout<<"SystemDateAndTime->LocalDateTime->Date->Day       :"<<GetTm_rep.SystemDateAndTime->LocalDateTime->Date->Day<<endl;
    }
    SoapTool.SoapFree(soap);   
    return result;
}

int ONVIFOptDeviceTime::SetDeviceTime(const char *DeviceXAddr, int _timeout, const char *UserName, const char *PassWord)
{
    int result = 0;
    struct soap *soap = NULL;

    _tds__SetSystemDateAndTime         SetTm_req;
    _tds__SetSystemDateAndTimeResponse SetTm_rep;

    char *TZ;                                                                
    time_t t;                                                                   
    struct tm tm;
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
    TZ = (char *)SoapTool.SoapMalloc(soap, 20);
    GetHostTZ(TZ, 20);
    t = time(NULL);
    gmtime_r(&t, &tm);
    
    tt__TimeZone TimeZone;
    tt__DateTime DateTime;
    tt__Date     Date;
    tt__Time     Time;
    

    SetTm_req.TimeZone    = &TimeZone;
    SetTm_req.UTCDateTime = &DateTime;
    DateTime.Date         = &Date;
    DateTime.Time         = &Time;
   
    SetTm_req.DateTimeType              = tt__SetDateTimeType__Manual;
    SetTm_req.DaylightSavings           = false;
    SetTm_req.TimeZone->TZ              = TZ;
    SetTm_req.UTCDateTime->Date->Year   = tm.tm_year + 1900;                    
    SetTm_req.UTCDateTime->Date->Month  = tm.tm_mon + 1;
    SetTm_req.UTCDateTime->Date->Day    = tm.tm_mday;
    SetTm_req.UTCDateTime->Time->Hour   = tm.tm_hour;
    SetTm_req.UTCDateTime->Time->Minute = tm.tm_min;
    SetTm_req.UTCDateTime->Time->Second = tm.tm_sec;

    result = soap_call___tds__SetSystemDateAndTime(soap, DeviceXAddr, NULL, &SetTm_req, SetTm_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "SetDeviceTime");
    else
        cout<<"SetDeviceTime OK"<<endl;
    SoapTool.SoapFree(soap);   
    return result;
}
void ONVIFOptDeviceTime::GetHostTZ(char *TZ, unsigned int sizeTZ)
{
    char timezone[20] = {0};

    FILE *fp = NULL;
    char time_fmt[32] = {0};

    fp = popen("date +%z", "r");
    fread(time_fmt, sizeof(time_fmt), 1, fp);
    pclose(fp);

    if( ((time_fmt[0] == '+') || (time_fmt[0] == '-')) &&
        isdigit(time_fmt[1]) && isdigit(time_fmt[2]) && isdigit(time_fmt[3]) && isdigit(time_fmt[4]) ) 
    {
            sprintf(timezone, "CST-%c%c:%c%c", time_fmt[1], time_fmt[2], time_fmt[3], time_fmt[4]);
    } 
    else 
    {
        strcpy(timezone, "CST-08:00");
    }

    if (sizeTZ > strlen(timezone)) 
    {
        strcpy(TZ, timezone);
    }
}
} //end namespace
