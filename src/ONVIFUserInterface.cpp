#include "ONVIFUserInterface.h"
namespace yyhonviflib
{
    
ONVIFUserInterface::ONVIFUserInterface()
{   
}
ONVIFUserInterface::~ONVIFUserInterface()
{
}
int ONVIFUserInterface::GetOSDs()
{
    ONVIFMedia MyONVIFMedia;
    char MediaXAddr[200] = {0};
    MyONVIFIni.ReadIni(Path, "XAddrMap", "MEDIA_XADDR",  MediaXAddr);
    return MyONVIFMedia.GetOSDs(MediaXAddr, Timeout, User, Password);
}
int ONVIFUserInterface::SetOSD(char *Text)
{
    ONVIFMedia MyONVIFMedia;
    char MediaXAddr[200] = {0};
    MyONVIFIni.ReadIni(Path, "XAddrMap", "MEDIA_XADDR",  MediaXAddr);
    return MyONVIFMedia.SetOSD(Text, MediaXAddr, Timeout, User, Password);
}
int ONVIFUserInterface::PTZGetPreset(char *PresetToken)
{
    return MyONVIFPTZ.GetPresets("11", PresetToken, Timeout, User, Password);
}
int ONVIFUserInterface::PTZSetPreset(char *PresetName, char *PresetToken)
{
    return MyONVIFPTZ.SetPreset(PresetName, PresetToken, Timeout, User, Password);
}
int ONVIFUserInterface::PTZGotoPreset(char *PresetToken)
{
    return MyONVIFPTZ.GotoPreset(PresetToken, Timeout, User, Password);
}
int ONVIFUserInterface::PTZRemovePreset(char *PresetToken)
{
    return MyONVIFPTZ.RemovePreset(PresetToken, Timeout, User, Password);
}
int ONVIFUserInterface::PTZInit(void)
{
    char PanTiltSpace[200]   = {0};
    char ZoomSpace[200]      = {0};
    char ProfileToken[20] = {0};
    char PTZXAddr[200]       = {0};
    MyONVIFIni.ReadIni(Path, "mainStream", "token",  ProfileToken);
    MyONVIFIni.ReadIni(Path, "XAddrMap", "PTZ_XADDR",  PTZXAddr);
    MyONVIFIni.ReadIni(Path, "PTZ", "ContinuousPanTiltVelocitySpace",  PanTiltSpace);
    MyONVIFIni.ReadIni(Path, "PTZ", "ContinuousZoomVelocitySpace",  ZoomSpace);
    memcpy(MyONVIFPTZ.PanTiltSpace, PanTiltSpace, 200);
    memcpy(MyONVIFPTZ.ZoomSpace, ZoomSpace, 200);
    memcpy(MyONVIFPTZ.ProfileToken, ProfileToken, 20);
    memcpy(MyONVIFPTZ.PTZXAddr, PTZXAddr, 200);
    return 0;
}
int ONVIFUserInterface::PTZMoveX(float XSpeed)
{
    MyONVIFPTZ.PanTiltX = XSpeed;
    MyONVIFPTZ.PanTiltY = 0;
    MyONVIFPTZ.ZoomX    = 0;
    return MyONVIFPTZ.ContinuousMove(Timeout, User, Password);
}
int ONVIFUserInterface::PTZMoveY(float YSpeed)
{
    MyONVIFPTZ.PanTiltX = 0;
    MyONVIFPTZ.PanTiltY = YSpeed;
    MyONVIFPTZ.ZoomX    = 0;
    return MyONVIFPTZ.ContinuousMove(Timeout, User, Password);
}
int ONVIFUserInterface::PTZMoveXY(float XSpeed, float YSpeed)
{
    MyONVIFPTZ.PanTiltX = XSpeed;
    MyONVIFPTZ.PanTiltY = YSpeed;
    MyONVIFPTZ.ZoomX    = 0;
    return MyONVIFPTZ.ContinuousMove(Timeout, User, Password);
}
int ONVIFUserInterface::PTZZoom(float ZOOMSpeed)
{
    MyONVIFPTZ.PanTiltX = 0;
    MyONVIFPTZ.PanTiltY = 0;
    MyONVIFPTZ.ZoomX    = ZOOMSpeed;
    return MyONVIFPTZ.ContinuousMove(Timeout, User, Password);
}
int ONVIFUserInterface::PTZStopAll(void)
{
    return MyONVIFPTZ.StopAll(Timeout, User, Password);
}
int ONVIFUserInterface::PTZStopPanTilt(void)
{
    return MyONVIFPTZ.StopPanTilt(Timeout, User, Password);
}
int ONVIFUserInterface::PTZStopZoom(void)
{
    return MyONVIFPTZ.StopZoom(Timeout, User, Password);
}
int ONVIFUserInterface::SetVideoEncoderConfiguration(int Type, int Width, int Height, int GovLength, int FrameRateLimit, int BitrateLimit)
{
    int result = 0;
    ONVIFMedia MyONVIFMedia;
    MyONVIFMedia.ResolutionWidth           = Width;
    MyONVIFMedia.ResolutionHeight          = Height;
    MyONVIFMedia.H264GovLength             = GovLength;
    MyONVIFMedia.RateControlFrameRateLimit = FrameRateLimit;
    MyONVIFMedia.RateControlBitrateLimit   = BitrateLimit;
    char ConfigurationToken[20] = {0};
    if(Type == 1)
        MyONVIFIni.ReadIni(Path, "mainStream", "v_encoder_ConfigurationToken",  ConfigurationToken);
    else if(Type == 2)
        MyONVIFIni.ReadIni(Path, "subStream", "v_encoder_ConfigurationToken",  ConfigurationToken);
    else
        return -1;
    char MediaXAddr[200] = {0};
    MyONVIFIni.ReadIni(Path, "XAddrMap", "MEDIA_XADDR",  MediaXAddr);
    result = MyONVIFMedia.SetVideoEncoderConfiguration(ConfigurationToken, MediaXAddr, Timeout, User, Password);
    return result;
}
int ONVIFUserInterface::SetDeviceTime(void)
{
    char DeviceXAddr[200] = {0};
    ONVIFOptDeviceTime MyONVIFOptDeviceTime;
    MyONVIFIni.ReadIni(Path, "XAddrMap", "DEVICE_XADDR",  DeviceXAddr);
    MyONVIFOptDeviceTime.SetDeviceTime(DeviceXAddr, Timeout, User, Password);
    MyONVIFOptDeviceTime.GetDeviceTime(DeviceXAddr, Timeout);//PRE_AUTH
    return 0;
}
int ONVIFUserInterface::ReadDeviceConfig(void)
{
    int result = 0;
    if(access(Path ,F_OK) == 0)
        unlink(Path);
    FILE *fp = fopen(Path, "a+");
    char tmp[1024] = {0};
    //Find device
	ONVIFRemoteDiscovery MyONVIFRemoteDiscovery;
    char **DeviceXAddr=new char*[MAXDeviceCount];
    int DeviceCount = 0;
    int i = 0;
    for(i = 0; i < MAXDeviceCount; i++)
        DeviceXAddr[i]=new char[200];
    MyONVIFRemoteDiscovery.RemoteDiscovery(DeviceXAddr, Timeout, DeviceCount);
    if(DeviceCount == 0)
    {
        cout<<"NO DEVICE FIND"<<endl;
        if(fp != NULL)
            fclose(fp);
        for(i = 0; i < MAXDeviceCount; i++)
            delete []DeviceXAddr[i];
        delete []DeviceXAddr;
        return -1;
    }

    //Get device information. We just need "SerialNumber"
	ONVIFGetDeviceInformation MyONVIFGetDeviceInformation;
    char SerialNumber[50];
    memset(SerialNumber, 0, 50); 
    result = MyONVIFGetDeviceInformation.GetDeviceInformation(SerialNumber, DeviceXAddr[0], Timeout, User, Password);
    if(result != 0)
    {
        if(fp != NULL)
            fclose(fp);
        for(i = 0; i < MAXDeviceCount; i++)
            delete []DeviceXAddr[i];
        delete []DeviceXAddr;
        return result;
    }
    cout<<SerialNumber<<endl;
    memset(tmp, 0, 1024);
    snprintf(tmp, 1024, "[ID]\nSerialNumber=%s\n", SerialNumber);
    fwrite(tmp, 1, strlen(tmp), fp);
    //Get Capabilities
    ONVIFGetCapabilities MyONVIFGetCapabilities;
    char **XAddrMap   =new char*[MAXXAddrMapCount];
    for(i = 0; i < MAXXAddrMapCount; i++)
        XAddrMap[i]=new char[200];
    result = MyONVIFGetCapabilities.GetCapabilities(XAddrMap, DeviceXAddr[0], Timeout);//PRE_AUTH
    if(result != 0)
    {
        if(fp != NULL)
            fclose(fp);
        for(i = 0; i < MAXDeviceCount; i++)
            delete []DeviceXAddr[i];
        delete []DeviceXAddr;
        for(i = 0; i < MAXXAddrMapCount; i++)
            delete []XAddrMap[i];
        delete []XAddrMap; 
        return result;
    }
    cout<<"0 :"<<XAddrMap[ANALYTICS_XADDR]<<endl;
    cout<<"1 :"<<XAddrMap[DEVICE_XADDR]<<endl;
    cout<<"2 :"<<XAddrMap[EVENTS_XADDR]<<endl;
    cout<<"3 :"<<XAddrMap[MEDIA_XADDR]<<endl;
    cout<<"4 :"<<XAddrMap[IMAGING_XADDR]<<endl;
    cout<<"5 :"<<XAddrMap[PTZ_XADDR]<<endl;
    cout<<"6 :"<<XAddrMap[DEVICEIO_XADDR]<<endl;
    cout<<"7 :"<<XAddrMap[DISPLAY_XADDR]<<endl;
    cout<<"8 :"<<XAddrMap[RECORDING_XADDR]<<endl;
    cout<<"9 :"<<XAddrMap[SEARCH_XADDR]<<endl;
    cout<<"10:"<<XAddrMap[REPLAY_XADDR]<<endl;
    cout<<"11:"<<XAddrMap[RECEIVER_XADDR]<<endl;
    cout<<"12:"<<XAddrMap[ANALYTICSDEVICE_XADDR]<<endl;
    memset(tmp, 0, 1024);
    snprintf(tmp, 1024, "[XAddrMap]\nDEVICE_XADDR=%s\nMEDIA_XADDR=%s\nIMAGING_XADDR=%s\nPTZ_XADDR=%s\nDEVICEIO_XADDR=%s\n", 
                        XAddrMap[DEVICE_XADDR], XAddrMap[MEDIA_XADDR],
                        XAddrMap[IMAGING_XADDR], XAddrMap[PTZ_XADDR],
                        XAddrMap[DEVICEIO_XADDR]);
    fwrite(tmp, 1, strlen(tmp), fp);
    if(fp != NULL)
        fclose(fp);//must close in here. Because we need open fp when Get Profiles

    //Get Profiles
    ONVIFMedia MyONVIFMedia;
    result = MyONVIFMedia.GetProfiles(Path, XAddrMap[MEDIA_XADDR], Timeout, User, Password);
    if(result != 0)
    {
        cout<<"GetProfiles failed"<<endl;
        for(i = 0; i < MAXDeviceCount; i++)
            delete []DeviceXAddr[i];
        delete []DeviceXAddr;
        for(i = 0; i < MAXXAddrMapCount; i++)
            delete []XAddrMap[i];
        delete []XAddrMap; 
        return result;
    }

    //Get StreamUri and SnapshotUri
    char MainProfileToken[20] = {0};
    char SubProfileToken[20] = {0};
    char MainStreamUri[200] = {0};
    char SubStreamUri[200] = {0};
    char MainSnapshotUri[200] = {0};
    char SubSnapshotUri[200] = {0};
    MyONVIFIni.ReadIni(Path, "mainStream", "token",  MainProfileToken);
    result = MyONVIFMedia.GetStreamUri(MainStreamUri, MainProfileToken, XAddrMap[MEDIA_XADDR], Timeout, User, Password);
    if(result != 0)
    {
        cout<<"GetStreamUri failed"<<endl;
        for(i = 0; i < MAXDeviceCount; i++)
            delete []DeviceXAddr[i];
        delete []DeviceXAddr;
        for(i = 0; i < MAXXAddrMapCount; i++)
            delete []XAddrMap[i];
        delete []XAddrMap; 
        return result;
    }
    result = MyONVIFMedia.GetSnapshotUri(MainSnapshotUri, MainProfileToken, XAddrMap[MEDIA_XADDR], Timeout, User, Password);
    if(result != 0)
    {
        cout<<"GetSnapshotUri failed"<<endl;
        for(i = 0; i < MAXDeviceCount; i++)
            delete []DeviceXAddr[i];
        delete []DeviceXAddr;
        for(i = 0; i < MAXXAddrMapCount; i++)
            delete []XAddrMap[i];
        delete []XAddrMap; 
        return result;
    }
    MyONVIFIni.WriteIni(Path, "mainStream", "StreamUri", MainStreamUri);
    MyONVIFIni.WriteIni(Path, "mainStream", "SnapshotUri", MainSnapshotUri);

    MyONVIFIni.ReadIni(Path, "subStream", "token",  SubProfileToken);
    result = MyONVIFMedia.GetStreamUri(SubStreamUri, SubProfileToken, XAddrMap[MEDIA_XADDR], Timeout, User, Password);
    if(result != 0)
    {
        cout<<"GetStreamUri failed"<<endl;
        for(i = 0; i < MAXDeviceCount; i++)
            delete []DeviceXAddr[i];
        delete []DeviceXAddr;
        for(i = 0; i < MAXXAddrMapCount; i++)
            delete []XAddrMap[i];
        delete []XAddrMap; 
        return result;
    }
    result = MyONVIFMedia.GetSnapshotUri(SubSnapshotUri, SubProfileToken, XAddrMap[MEDIA_XADDR], Timeout, User, Password);
    if(result != 0)
    {
        cout<<"GetSnapshotUri failed"<<endl;
        for(i = 0; i < MAXDeviceCount; i++)
            delete []DeviceXAddr[i];
        delete []DeviceXAddr;
        for(i = 0; i < MAXXAddrMapCount; i++)
            delete []XAddrMap[i];
        delete []XAddrMap; 
        return result;
    }
    MyONVIFIni.WriteIni(Path, "subStream", "StreamUri", SubStreamUri);
    MyONVIFIni.WriteIni(Path, "subStream", "SnapshotUri", SubSnapshotUri);
    
    //GetVideoEncoderConfigurationOptions
    char MainConfigurationToken[20] = {0};
    MyONVIFIni.ReadIni(Path, "mainStream", "v_encoder_ConfigurationToken",  MainConfigurationToken);
    char SubConfigurationToken[20] = {0};
    MyONVIFIni.ReadIni(Path, "subStream", "v_encoder_ConfigurationToken",  SubConfigurationToken);

    result = MyONVIFMedia.GetVideoEncoderConfigurationOptions(Path, 1, MainConfigurationToken, 
                                        XAddrMap[MEDIA_XADDR], Timeout, User, Password);
    if(result != 0)
    {
        cout<<"GetVideoEncoderConfigurationOptions failed"<<endl;
        for(i = 0; i < MAXDeviceCount; i++)
            delete []DeviceXAddr[i];
        delete []DeviceXAddr;
        for(i = 0; i < MAXXAddrMapCount; i++)
            delete []XAddrMap[i];
        delete []XAddrMap; 
        return result;
    }
    result = MyONVIFMedia.GetVideoEncoderConfigurationOptions(Path, 2, SubConfigurationToken, 
                                        XAddrMap[MEDIA_XADDR], Timeout, User, Password);
    if(result != 0)
    {
        cout<<"GetVideoEncoderConfigurationOptions failed"<<endl;
        for(i = 0; i < MAXDeviceCount; i++)
            delete []DeviceXAddr[i];
        delete []DeviceXAddr;
        for(i = 0; i < MAXXAddrMapCount; i++)
            delete []XAddrMap[i];
        delete []XAddrMap; 
        return result;
    }
    //PTZGetConfigurationOptions
    char PTZConfigurationToken[20];
    memset(PTZConfigurationToken, 0, 20);
    MyONVIFIni.ReadIni(Path, "PTZ", "PTZ_ConfigurationToken",  PTZConfigurationToken);
    result = MyONVIFPTZ.GetConfigurationOptions(Path, PTZConfigurationToken, XAddrMap[PTZ_XADDR], Timeout, User, Password);
    if(result != 0)
    {
        cout<<"PTZGetConfigurationOptions failed"<<endl;
        for(i = 0; i < MAXDeviceCount; i++)
            delete []DeviceXAddr[i];
        delete []DeviceXAddr;
        for(i = 0; i < MAXXAddrMapCount; i++)
            delete []XAddrMap[i];
        delete []XAddrMap; 
        return result;
    }

    //DeviceIO
    ONVIFDeviceIO MyONVIFDeviceIO;
    result = MyONVIFDeviceIO.GetRelayOutputs(Path, XAddrMap[DEVICEIO_XADDR], Timeout, User, Password);
    
    for(i = 0; i < MAXDeviceCount; i++)
        delete []DeviceXAddr[i];
    delete []DeviceXAddr;
    for(i = 0; i < MAXXAddrMapCount; i++)
        delete []XAddrMap[i];
    delete []XAddrMap; 
    return result;        
}
} //end namespace