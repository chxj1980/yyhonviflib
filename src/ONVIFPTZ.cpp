#include "ONVIFPTZ.h"
 
using namespace std; 
namespace yyhonviflib
{
	
ONVIFPTZ::ONVIFPTZ()
{
	memset(PanTiltSpace, 0, 200);
	memset(ZoomSpace, 0, 200);
	memset(ProfileToken, 0, 200);
	memset(PTZXAddr, 0, 200);
	PanTiltX = 0.0;
	PanTiltY = 0.0;
	ZoomX    = 0.0;
}
ONVIFPTZ::~ONVIFPTZ()
{
}
int ONVIFPTZ::SaveConfigurationOptions(_tptz__GetConfigurationOptionsResponse &GetCon_rep, const char *Path)
{
	int result = 0;
	FILE *fp = fopen(Path, "a+");
    char tmp[1024] = {0};
    snprintf(tmp, 1024, "ContinuousPanTiltVelocitySpace=%s\nContinuousPanTiltVelocitySpace_XRange=%f~%f\n"
    	                "ContinuousPanTiltVelocitySpace_YRange=%f~%f\nContinuousZoomVelocitySpace=%s\n"
    	                "ContinuousZoomVelocitySpace_XRange=%f~%f\nPTZTimeoutRange=%ld~%ld\n",
    	GetCon_rep.PTZConfigurationOptions->Spaces->ContinuousPanTiltVelocitySpace[0]->URI.data(),
    	GetCon_rep.PTZConfigurationOptions->Spaces->ContinuousPanTiltVelocitySpace[0]->XRange->Min,
    	GetCon_rep.PTZConfigurationOptions->Spaces->ContinuousPanTiltVelocitySpace[0]->XRange->Max,
    	GetCon_rep.PTZConfigurationOptions->Spaces->ContinuousPanTiltVelocitySpace[0]->YRange->Min,
    	GetCon_rep.PTZConfigurationOptions->Spaces->ContinuousPanTiltVelocitySpace[0]->YRange->Max,
    	GetCon_rep.PTZConfigurationOptions->Spaces->ContinuousZoomVelocitySpace[0]->URI.data(),
    	GetCon_rep.PTZConfigurationOptions->Spaces->ContinuousZoomVelocitySpace[0]->XRange->Min,
    	GetCon_rep.PTZConfigurationOptions->Spaces->ContinuousZoomVelocitySpace[0]->XRange->Max,
    	GetCon_rep.PTZConfigurationOptions->PTZTimeout->Min,GetCon_rep.PTZConfigurationOptions->PTZTimeout->Max
    	);
    fwrite(tmp, 1, strlen(tmp), fp);
    if(fp != NULL)
    	fclose(fp);
    return result;
}
int ONVIFPTZ::GetConfigurationOptions(const char *Path, char *ConfigurationToken, char *_PTZXAddr, int _timeout, const char *UserName, const char *PassWord)
{
	int result = 0;
    struct soap *soap = NULL;
	_tptz__GetConfigurationOptions              GetCon_req;
	_tptz__GetConfigurationOptionsResponse      GetCon_rep;

	GetCon_req.ConfigurationToken                   = ConfigurationToken;

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
	result = soap_call___tptz__GetConfigurationOptions(soap, _PTZXAddr, NULL, &GetCon_req, GetCon_rep);
	if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "tptz__GetConfigurationOptions");
    else
    {
        cout<<"tptz__GetConfigurationOptions OK"<<endl;
        SaveConfigurationOptions(GetCon_rep, Path);      
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFPTZ::ContinuousMove(int _timeout, const char *UserName, const char *PassWord)
{
	int result = 0;
    struct soap *soap = NULL;
	_tptz__ContinuousMove              ConM_req;
	_tptz__ContinuousMoveResponse      ConM_rep;
    cout<<ProfileToken<<endl;
    string s1 = PanTiltSpace;
    string s2 = ZoomSpace;
	ConM_req.ProfileToken                   = ProfileToken;
	tt__PTZSpeed Velocity;
    ConM_req.Velocity = &Velocity;
    tt__Vector2D PanTilt;
    tt__Vector1D Zoom;
    ConM_req.Velocity->PanTilt = &PanTilt;
    ConM_req.Velocity->Zoom = &Zoom;
    PanTilt.x     = PanTiltX;
    PanTilt.y     = PanTiltY;
    PanTilt.space = &s1;
    Zoom.x        = ZoomX;
    Zoom.space    = &s2;
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
	result = soap_call___tptz__ContinuousMove(soap, PTZXAddr, NULL, &ConM_req, ConM_rep);
	if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "tptz__ContinuousMove");
    else
    {
        cout<<"tptz__ContinuousMove OK"<<endl;    
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFPTZ::StopAll(int _timeout, const char *UserName, const char *PassWord)
{
	int result = 0;
    struct soap *soap = NULL;
	_tptz__Stop              Stop_req;
	_tptz__StopResponse      Stop_rep;
    bool stop_bool;
	Stop_req.ProfileToken                   = ProfileToken;

	stop_bool = true;
	Stop_req.PanTilt                        = &stop_bool;
	Stop_req.Zoom                           = &stop_bool;
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
	result = soap_call___tptz__Stop(soap, PTZXAddr, NULL, &Stop_req, Stop_rep);
	if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "tptz__Stop");
    else
    {
        cout<<"tptz__Stop OK"<<endl;    
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFPTZ::StopPanTilt(int _timeout, const char *UserName, const char *PassWord)
{
    int result = 0;
    struct soap *soap = NULL;
    _tptz__Stop              Stop_req;
    _tptz__StopResponse      Stop_rep;
    bool stop_bool;
    Stop_req.ProfileToken                   = ProfileToken;

    stop_bool = true;
    Stop_req.Zoom                           = &stop_bool;
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
    result = soap_call___tptz__Stop(soap, PTZXAddr, NULL, &Stop_req, Stop_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "tptz__Stop");
    else
    {
        cout<<"tptz__Stop OK"<<endl;    
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFPTZ::StopZoom(int _timeout, const char *UserName, const char *PassWord)
{
    int result = 0;
    struct soap *soap = NULL;
    _tptz__Stop              Stop_req;
    _tptz__StopResponse      Stop_rep;
    bool stop_bool;
    Stop_req.ProfileToken                   = ProfileToken;

    stop_bool = true;
    Stop_req.Zoom                           = &stop_bool;
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
    result = soap_call___tptz__Stop(soap, PTZXAddr, NULL, &Stop_req, Stop_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "tptz__Stop");
    else
    {
        cout<<"tptz__Stop OK"<<endl;    
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFPTZ::GetPresets(char *PresetName, char *PresetToken, int _timeout, const char *UserName, const char *PassWord)
{
	int result = 0;
    struct soap *soap = NULL;
	_tptz__GetPresets              GetPre_req;
	_tptz__GetPresetsResponse      GetPre_rep;
	
	GetPre_req.ProfileToken                 = ProfileToken;

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
	result = soap_call___tptz__GetPresets(soap, PTZXAddr, NULL, &GetPre_req, GetPre_rep);
	if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "tptz__GetPresets");
    else
    {
        cout<<"tptz__GetPresets OK"<<endl;
        result = 6000;
        for(unsigned int i=0; i<GetPre_rep.Preset.size(); i++)
            if(strstr(GetPre_rep.Preset[i]->token->c_str(), PresetToken))
                result = SOAP_OK;
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFPTZ::CreatePreset(char *PresetName, char *PresetToken, int _timeout, const char *UserName, const char *PassWord)
{
	int result = 0;
    struct soap *soap = NULL;
	_tptz__SetPreset              SetPre_req;
	_tptz__SetPresetResponse      SetPre_rep;
	
	string SName                            = PresetName;
	SetPre_req.ProfileToken                 = ProfileToken;
	SetPre_req.PresetName                   = &SName;

    
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
	result = soap_call___tptz__SetPreset(soap, PTZXAddr, NULL, &SetPre_req, SetPre_rep);
	if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "tptz__SetPreset");
    else
    {
        cout<<"tptz__CreatePreset OK"<<endl;
        sprintf(PresetToken, "%s", SetPre_rep.PresetToken.c_str());
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFPTZ::SetPreset(char *PresetName, char *PresetToken, int _timeout, const char *UserName, const char *PassWord)
{
	int result = 0;
    struct soap *soap = NULL;
	_tptz__SetPreset              SetPre_req;
	_tptz__SetPresetResponse      SetPre_rep;
	
	string SName                            = PresetName;
	string SToken                           = PresetToken;
	SetPre_req.ProfileToken                 = ProfileToken;
	SetPre_req.PresetName                   = &SName;
	SetPre_req.PresetToken                  = &SToken;
    
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
	result = soap_call___tptz__SetPreset(soap, PTZXAddr, NULL, &SetPre_req, SetPre_rep);
	if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "tptz__SetPreset");
    else
    {
        cout<<"tptz__SetPreset OK"<<endl;
        cout<<SetPre_rep.PresetToken<<endl;
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFPTZ::GotoPreset(char *PresetToken, int _timeout, const char *UserName, const char *PassWord)
{
	int result = 0;
    struct soap *soap = NULL;
	_tptz__GotoPreset              GotoPre_req;
	_tptz__GotoPresetResponse      GotoPre_rep;
	
	GotoPre_req.ProfileToken                 = ProfileToken;
	GotoPre_req.PresetToken                  = PresetToken;


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
	result = soap_call___tptz__GotoPreset(soap, PTZXAddr, NULL, &GotoPre_req, GotoPre_rep);
	if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "tptz__GotoPreset");
    else
    {
        cout<<"tptz__GotoPreset OK"<<endl;    
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFPTZ::RemovePreset(char *PresetToken, int _timeout, const char *UserName, const char *PassWord)
{
    int result = 0;
    struct soap *soap = NULL;
    _tptz__RemovePreset              RemvPre_req;
    _tptz__RemovePresetResponse      RemvPre_rep;
    
    RemvPre_req.ProfileToken                 = ProfileToken;
    RemvPre_req.PresetToken                  = PresetToken;


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
    result = soap_call___tptz__RemovePreset(soap, PTZXAddr, NULL, &RemvPre_req, RemvPre_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "tptz__RemovePreset");
    else
    {
        cout<<"tptz__RemovePreset OK"<<endl;    
    }
    SoapTool.SoapFree(soap);   
    return result;
}
} //end namespace