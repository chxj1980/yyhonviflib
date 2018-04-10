#include "ONVIFMedia.h"
#include "ONVIFIni.h" 
using namespace std; 
namespace yyhonviflib
{
	
ONVIFMedia::ONVIFMedia()
{
}
ONVIFMedia::~ONVIFMedia()
{
}
int ONVIFMedia::SaveProfiles(vector<tt__Profile *> Profiles, const char *Path)
{
    char tmp[1024] = {0};
    FILE *fp = fopen(Path, "a+");
    for(unsigned int i = 0; i < 2; i++)
    {
        memset(tmp, 0, 1024);  
        snprintf(tmp, 1024, "[%s]\ntoken=%s\nv_encoder_width=%d\nv_encoder_height=%d\n"
            "v_encoder_FrameRateLimit=%d\nv_encoder_BitrateLimit=%d\n"
            "v_encoder_GovLength=%d\nv_encoder_ConfigurationToken=%s\nStreamUri=\nSnapshotUri=\nH264GovLengthRange=\n"
            "H264FrameRateRange=\nResolutionsAvailable=\n",
            (Profiles[i]->Name).data(),
            (Profiles[i]->token).data(),
            Profiles[i]->VideoEncoderConfiguration->Resolution->Width,
            Profiles[i]->VideoEncoderConfiguration->Resolution->Height, 
            Profiles[i]->VideoEncoderConfiguration->RateControl->FrameRateLimit,
            Profiles[i]->VideoEncoderConfiguration->RateControl->BitrateLimit,
            Profiles[i]->VideoEncoderConfiguration->H264->GovLength,
            (Profiles[i]->VideoEncoderConfiguration->token).data());
        fwrite(tmp, 1, strlen(tmp), fp);
    }
    memset(tmp, 0, 1024);
    snprintf(tmp, 1024, "[PTZ]\nPTZ_ConfigurationToken=%s\n",
             (Profiles[0]->PTZConfiguration->token).data());
    fwrite(tmp, 1, strlen(tmp), fp);
    if(fp != NULL)
        fclose(fp);
    return 0;
}
int ONVIFMedia::GetProfiles(const char *Path, char *MediaXAddr, 
                            int _timeout, const char *UserName, const char *PassWord)
{
    vector<tt__Profile *> Profiles;
    int result = 0;
    struct soap *soap = NULL;
    _trt__GetProfiles              GetProf_req;
    _trt__GetProfilesResponse      GetProf_rep;
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
    result = soap_call___trt__GetProfiles(soap, MediaXAddr, NULL, &GetProf_req, GetProf_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "GetProfiles");
    else
    {
        Profiles = GetProf_rep.Profiles;
        SaveProfiles(Profiles, Path);    
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFMedia::GetStreamUri(char *StreamUri, char *ProfileToken, char *MediaXAddr, int _timeout, const char *UserName, const char *PassWord)
{
	int result = 0;
    struct soap *soap = NULL;
    _trt__GetStreamUri              GetStrm_req;
    _trt__GetStreamUriResponse      GetStrm_rep;
    tt__StreamSetup                 StreamSetup;
    tt__Transport                   Transport;

    GetStrm_req.StreamSetup = &StreamSetup;
    StreamSetup.Transport   = &Transport;

    GetStrm_req.ProfileToken                     = ProfileToken;
    GetStrm_req.StreamSetup->Stream              = tt__StreamType__RTP_Unicast;
    GetStrm_req.StreamSetup->Transport->Protocol = tt__TransportProtocol__RTSP;
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
    result = soap_call___trt__GetStreamUri(soap, MediaXAddr, NULL, &GetStrm_req, GetStrm_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "GetStreamUri");
    else
    {
        cout<<GetStrm_rep.MediaUri->Uri<<endl;
        memcpy(StreamUri, GetStrm_rep.MediaUri->Uri.c_str(),strlen(GetStrm_rep.MediaUri->Uri.c_str()));
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFMedia::GetSnapshotUri(char *SnapshotUri, char *ProfileToken, char *MediaXAddr, int _timeout, const char *UserName, const char *PassWord)
{
    int result = 0;
    struct soap *soap = NULL;
    _trt__GetSnapshotUri              GetSnap_req;
    _trt__GetSnapshotUriResponse      GetSnap_rep;


    GetSnap_req.ProfileToken                     = ProfileToken;
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
    result = soap_call___trt__GetSnapshotUri(soap, MediaXAddr, NULL, &GetSnap_req, GetSnap_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "GetSnapshotUri");
    else
    {
        cout<<GetSnap_rep.MediaUri->Uri<<endl;
        memcpy(SnapshotUri, GetSnap_rep.MediaUri->Uri.c_str(),strlen(GetSnap_rep.MediaUri->Uri.c_str()));
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFMedia::SaveConfigurationOptions(char ConfigurationOptions[][20], 
                                         vector<tt__VideoResolution *> ResolutionsAvailable, 
                                         int type, const char *Path)
{
    ONVIFIni MyONVIFIni;
    char root[20] = {0};
    if(type == 1)
        snprintf(root, 20, "mainStream");
    else if(type == 2)
        snprintf(root, 20, "subStream");
    MyONVIFIni.WriteIni(Path, root, "H264GovLengthRange", ConfigurationOptions[0]);
    MyONVIFIni.WriteIni(Path, root, "H264FrameRateRange", ConfigurationOptions[1]);
    string s;
    for(unsigned int i=0; i<ResolutionsAvailable.size(); i++)
    {
        s += to_string(ResolutionsAvailable[i]->Width) + "*" + to_string(ResolutionsAvailable[i]->Height) + " ";
    }
    MyONVIFIni.WriteIni(Path, root, "ResolutionsAvailable", const_cast<char*>(s.c_str()));
    return 0;
}
int ONVIFMedia::GetVideoEncoderConfigurationOptions(const char *Path, int type, char *ConfigurationToken, 
                                 char *MediaXAddr, int _timeout, 
                                 const char *UserName, const char *PassWord)
{
    int result = 0;
    struct soap *soap = NULL;
    _trt__GetVideoEncoderConfigurationOptions              GetVECO_req;
    _trt__GetVideoEncoderConfigurationOptionsResponse      GetVECO_rep;
    string s = ConfigurationToken;
    GetVECO_req.ConfigurationToken                    = &s;
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
    result = soap_call___trt__GetVideoEncoderConfigurationOptions(soap, MediaXAddr, NULL, &GetVECO_req, GetVECO_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "GetVideoEncoderConfigurationOptions");
    else
    {
        char ConfigurationOptions[2][20] = {0};
        vector<tt__VideoResolution *> ResolutionsAvailable;
        memset(ConfigurationOptions[0], 0, 20);
        snprintf(ConfigurationOptions[0], 20, "%d~%d", GetVECO_rep.Options->H264->GovLengthRange->Min, 
                                                       GetVECO_rep.Options->H264->GovLengthRange->Max);
        memset(ConfigurationOptions[1], 0, 20);
        snprintf(ConfigurationOptions[1], 20, "%d~%d", GetVECO_rep.Options->H264->FrameRateRange->Min, 
                                                       GetVECO_rep.Options->H264->FrameRateRange->Max);
        ResolutionsAvailable = GetVECO_rep.Options->H264->ResolutionsAvailable;
        cout<<"GetVideoEncoderConfigurationOptions OK"<<endl;
        SaveConfigurationOptions(ConfigurationOptions, ResolutionsAvailable, type, Path);
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFMedia::SetVideoEncoderConfiguration(char *ConfigurationToken, char *MediaXAddr, int _timeout, 
                                             const char *UserName, const char *PassWord)
{
    int result = 0;
    struct soap *soap = NULL;

    _trt__GetVideoEncoderConfiguration              GetVEC_req;
    _trt__GetVideoEncoderConfigurationResponse      GetVEC_rep;

    _trt__SetVideoEncoderConfiguration              SetVEC_req;
    _trt__SetVideoEncoderConfigurationResponse      SetVEC_rep;
    GetVEC_req.ConfigurationToken                   = ConfigurationToken;
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
    result = soap_call___trt__GetVideoEncoderConfiguration(soap, MediaXAddr, NULL, &GetVEC_req, GetVEC_rep);
    if(result != SOAP_OK)
    {
        SoapTool.SoapPerror(soap, "GetVideoEncoderConfiguration");
        SoapTool.SoapFree(soap);   
        return result;
    }
    else
    {
        SetVEC_req.ForcePersistence                             = true;
        SetVEC_req.Configuration                                = GetVEC_rep.Configuration;
        SetVEC_req.Configuration->Resolution->Width             = ResolutionWidth;
        SetVEC_req.Configuration->Resolution->Height            = ResolutionHeight;
        SetVEC_req.Configuration->RateControl->FrameRateLimit   = RateControlFrameRateLimit;
        SetVEC_req.Configuration->RateControl->BitrateLimit     = RateControlBitrateLimit;
        SetVEC_req.Configuration->H264->GovLength               = H264GovLength;
    }
    result = SoapInit.SetAuthInfo(soap, UserName, PassWord);
    if(result != SOAP_OK)
    {
        SoapTool.SoapPerror(soap, "SetAuthInfo");
        SoapTool.SoapFree(soap);   
        return result;
    }
    result = soap_call___trt__SetVideoEncoderConfiguration(soap, MediaXAddr, NULL, &SetVEC_req, SetVEC_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "SetVideoEncoderConfiguration");
    else
    {
        cout<<"SetVideoEncoderConfiguration OK."<<endl;
    }
    SoapTool.SoapFree(soap);   
    return result;
}

int ONVIFMedia::GetOSDs(char *MediaXAddr, int _timeout, const char *UserName, const char *PassWord)
{
    int result = 0;
    struct soap *soap = NULL;
    _trt__GetOSDs              GetOSDs_req;
    _trt__GetOSDsResponse      GetOSDs_rep;
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
    result = soap_call___trt__GetOSDs(soap, MediaXAddr, NULL, &GetOSDs_req, GetOSDs_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "GetOSDs");
    else
    {
        for(unsigned int i=0; i<GetOSDs_rep.OSDs.size(); i++)
        {
            cout<<"GetOSDs OK"<<endl;
            cout<<GetOSDs_rep.OSDs[i]->Type<<endl;
            cout<<GetOSDs_rep.OSDs[i]->VideoSourceConfigurationToken->__item<<endl;
            cout<<GetOSDs_rep.OSDs[i]->token<<endl;
            cout<<GetOSDs_rep.OSDs[i]->TextString->Type<<endl;
         //   cout<<GetOSDs_rep.OSDs[i]->TextString->PlainText<<endl;
        } 
    }
    SoapTool.SoapFree(soap);   
    return result;
}
int ONVIFMedia::SetOSD(char *Text, char *MediaXAddr, int _timeout, const char *UserName, const char *PassWord)
{
    int result = 0;
    struct soap *soap = NULL;
    _trt__SetOSD              SetOSD_req;
    _trt__SetOSDResponse      SetOSD_rep;

    tt__OSDConfiguration  _OSD;
    SetOSD_req.OSD = &_OSD;
    tt__OSDReference   _VideoSourceConfigurationToken;
    SetOSD_req.OSD->VideoSourceConfigurationToken = &_VideoSourceConfigurationToken;
    SetOSD_req.OSD->Type  = tt__OSDType__Text;
    SetOSD_req.OSD->token = "OsdToken_102";
    SetOSD_req.OSD->VideoSourceConfigurationToken->__item = "VideoSourceToken";
    tt__OSDTextConfiguration _TextString;
    SetOSD_req.OSD->TextString = &_TextString;
    string PlainText = Text;
    SetOSD_req.OSD->TextString->Type = "Plain";
    SetOSD_req.OSD->TextString->PlainText = &PlainText;
    tt__OSDPosConfiguration _Position;
    SetOSD_req.OSD->Position = &_Position;
    SetOSD_req.OSD->Position->Type = "UpperLeft";
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
    result = soap_call___trt__SetOSD(soap, MediaXAddr, NULL, &SetOSD_req, SetOSD_rep);
    if(result != SOAP_OK)
        SoapTool.SoapPerror(soap, "SetOSD");
    else
    {
    }
    SoapTool.SoapFree(soap);   
    return result;
}
} //end namespace