#include "ONVIFDeviceIO.h"
 
using namespace std; 
namespace yyhonviflib
{
	
ONVIFDeviceIO::ONVIFDeviceIO()
{
}
ONVIFDeviceIO::~ONVIFDeviceIO()
{
}
int ONVIFDeviceIO::SaveRelayOutputs(_tds__GetRelayOutputsResponse &GetRel_rep, const char *Path)
{
    int result = 0;
    FILE *fp = fopen(Path, "a+");
    string s = "[DeviceIO]\n";
    char temp[5];
    char state[5];
    string sTemp;
    string sState;
    for(unsigned int i=0; i<GetRel_rep.RelayOutputs.size(); i++)
    {
        memset(temp, 0, 5);
        memset(state, 0, 5);
        snprintf(temp, 5, "%d", i);
        snprintf(state, 5, "%d", GetRel_rep.RelayOutputs[i]->Properties->IdleState);
        sTemp  = temp;
        sState = state;
        s += "Token" + sTemp + "=" + GetRel_rep.RelayOutputs[i]->token + "\n" + "IdleState" + sTemp + "=" + sState + "\n";
    }
    fwrite(s.data(), 1, strlen(s.data()), fp);
    if(fp != NULL)
        fclose(fp);
    return result;
}

int ONVIFDeviceIO::GetRelayOutputs(const char *Path, char *DeviceIOXAddr, int _timeout, const char *UserName, const char *PassWord)
{
	int result = 0;
    struct soap *soap = NULL;
	_tds__GetRelayOutputs              GetRel_req;
	_tds__GetRelayOutputsResponse      GetRel_rep;

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
	result = soap_call___tds__GetRelayOutputs(soap, DeviceIOXAddr, NULL, &GetRel_req, GetRel_rep);
	if(result != SOAP_OK)
    {
        if(result == 200)
        {
            cout<<"result"<<result<<endl;
            result = SOAP_OK;
        }
        else
            SoapTool.SoapPerror(soap, "GetRelayOutputs");
    }
    else
    {
        cout<<"GetRelayOutputs OK"<<endl;
        SaveRelayOutputs(GetRel_rep, Path);      
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFDeviceIO::SetRelayOutputState(int RelayState, char *RelayOutputToken, char *DeviceIOXAddr, int _timeout, const char *UserName, const char *PassWord)
{
    int result = 0;
    struct soap *soap = NULL;
    _tds__SetRelayOutputState              SetRel_req;
    _tds__SetRelayOutputStateResponse      SetRel_rep;
    
    SetRel_req.RelayOutputToken       = RelayOutputToken;
    if(RelayState == 0)
        SetRel_req.LogicalState           = tt__RelayLogicalState__active;
    else
        SetRel_req.LogicalState           = tt__RelayLogicalState__inactive;
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
    result = soap_call___tds__SetRelayOutputState(soap, DeviceIOXAddr, NULL, &SetRel_req, SetRel_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "SetRelayOutputState");
    else
    {
        cout<<"SetRelayOutputState OK"<<endl;     
    }
    SoapTool.SoapFree(soap);   
    return result;
}
} //end namespace