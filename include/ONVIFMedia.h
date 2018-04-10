#ifndef _ONVIFMEDIA_H_
#define _ONVIFMEDIA_H_

#include "ONVIFSoapInit.h"
#include "ONVIFSoapTool.h"

namespace yyhonviflib
{
class ONVIFMedia
{
public:
	ONVIFMedia();
	~ONVIFMedia();
	int SaveProfiles(vector<tt__Profile *> Profiles, const char *Path);
	int GetProfiles(const char *Path, char *MediaXAddr, 
                            int _timeout, const char *UserName, const char *PassWord);
	int GetStreamUri(char *StreamUri, char *ProfileToken, char *MediaXAddr, int _timeout, const char *UserName, const char *PassWord);
	int GetSnapshotUri(char *SnapshotUri, char *ProfileToken, char *MediaXAddr, int _timeout, const char *UserName, const char *PassWord);
	int SaveConfigurationOptions(char ConfigurationOptions[][20], 
                                         vector<tt__VideoResolution *> ResolutionsAvailable, 
                                         int type, const char *Path);
	int GetVideoEncoderConfigurationOptions(const char *Path, int type, char *ConfigurationToken, 
                                 char *MediaXAddr, int _timeout, 
                                 const char *UserName, const char *PassWord);
	int SetVideoEncoderConfiguration(char *ConfigurationToken, char *MediaXAddr, int _timeout, 
                                             const char *UserName, const char *PassWord);

	int GetOSDs(char *MediaXAddr, int _timeout, const char *UserName, const char *PassWord);
	int SetOSD(char *Text, char *MediaXAddr, int _timeout, const char *UserName, const char *PassWord);

	int ResolutionWidth;
	int ResolutionHeight;
	int H264GovLength;
	int RateControlFrameRateLimit;
	int RateControlBitrateLimit;
private:
	ONVIFSoapInit SoapInit;
	ONVIFSoapTool SoapTool;
};
} //end namespace
#endif