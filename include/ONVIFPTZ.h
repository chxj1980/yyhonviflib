#ifndef _ONVIFPTZ_H_
#define _ONVIFPTZ_H_

#include "ONVIFSoapInit.h"
#include "ONVIFSoapTool.h"

namespace yyhonviflib
{
class ONVIFPTZ
{
public:
	ONVIFPTZ();
	~ONVIFPTZ();
	int SaveConfigurationOptions(_tptz__GetConfigurationOptionsResponse &GetCon_rep, const char *Path);
	int GetConfigurationOptions(const char *Path, char *ConfigurationToken, char *_PTZXAddr, int _timeout, const char *UserName, const char *PassWord);


    int ContinuousMove(int _timeout, const char *UserName, const char *PassWord);
    int StopAll(int _timeout, const char *UserName, const char *PassWord);
    int StopPanTilt(int _timeout, const char *UserName, const char *PassWord);
    int StopZoom(int _timeout, const char *UserName, const char *PassWord);

    int CreatePreset(char *PresetName, char *PresetToken, int _timeout, const char *UserName, const char *PassWord);
    int GetPresets(char *PresetName, char *PresetToken, int _timeout, const char *UserName, const char *PassWord);
    int SetPreset(char *PresetName, char *PresetToken, int _timeout, const char *UserName, const char *PassWord);
    int GotoPreset(char *PresetToken, int _timeout, const char *UserName, const char *PassWord);
    int RemovePreset(char *PresetToken, int _timeout, const char *UserName, const char *PassWord);
    float  PanTiltX;
    float  PanTiltY;
    char   PanTiltSpace[200];
    float  ZoomX;
    char   ZoomSpace[200];
    char   ProfileToken[20];
    char   PTZXAddr[200];
private:
	ONVIFSoapInit SoapInit;
	ONVIFSoapTool SoapTool;
};
} //end namespace
#endif