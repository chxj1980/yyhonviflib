#ifndef _ONVIFUSERINTERFACE_H_
#define _ONVIFUSERINTERFACE_H_

#include "ONVIFRemoteDiscovery.h"
#include "ONVIFGetDeviceInformation.h"
#include "ONVIFGetCapabilities.h"
#include "ONVIFOptDeviceTime.h"
#include "ONVIFXAddrMap.h"
#include "ONVIFMedia.h"
#include "ONVIFIni.h" 
#include "ONVIFPTZ.h"
#include "ONVIFDeviceIO.h"
#include <iostream>
#include <unistd.h>
using namespace std;
void CallHandleProfiles(vector<tt__Profile *> Profiles, const char *Path, char *SerialNumber);
void CallHandleConfigurationOptions(char** ConfigurationOptions, vector<tt__VideoResolution *> ResolutionsAvailable, int type);
namespace yyhonviflib
{
class ONVIFUserInterface
{
public:
	ONVIFUserInterface();
	~ONVIFUserInterface();
	int GetOSDs();
	int SetOSD(char *Text);

	int ReadDeviceConfig(void);
	int SetDeviceTime(void);
	int SetVideoEncoderConfiguration(int Type, int Width, int Height, int GovLength, int FrameRateLimit, int BitrateLimit);
	//auth
	const char *Path;
	const char *User;
	const char *Password;
	int Timeout;
	//PTZ
	int PTZInit(void);
	int PTZMoveX(float XSpeed);
	int PTZMoveY(float YSpeed);
	int PTZMoveXY(float XSpeed, float YSpeed);
	int PTZZoom(float ZOOMSpeed);
	int PTZStopAll(void);
	int PTZStopPanTilt(void);
	int PTZStopZoom(void);

	int PTZGetPreset(char *PresetToken);
	int PTZSetPreset(char *PresetName, char *PresetToken);
	int PTZGotoPreset(char *PresetToken);
	int PTZRemovePreset(char *PresetToken);
	ONVIFPTZ   MyONVIFPTZ;
    //ini
    ONVIFIni   MyONVIFIni;
private:
	const int MAXDeviceCount = 1;
    const int MAXXAddrMapCount = 13;	
};
} //end namespace
#endif