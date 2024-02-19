#include <iostream>
#include <vector>
#include <string>
#include "headers/JabraDeviceConfig.h"
#include "headers/JabraNativeHid.h"

using namespace std;

int Link380deviceID;
bool Link380Found = false;
int BTheadsetId;
bool BTheadsetFound = false; 
void outputToConsole(string outputString)
{
    cout << outputString << endl;
}

string boolToString(bool value) {
    if (value) { return "true"; } else { return "false" ;}
}

void LinkQualityFunc(unsigned short deviceID, const LinkQuality status)
{
    string statusString;
    switch (status)
    {
    case LINKQUALITY_HIGH:
        statusString = "High";
        break;
    case LINKQUALITY_LOW:
        statusString = "Low";
        break;
    case LINKQUALITY_OFF:
        statusString = "Off";
        break;
    default:
        statusString = "SHOULD NEVER HAPPEN!";
    }
    outputToConsole("BT Link quality: " + statusString);
}

void batteryStatusCallback(unsigned short deviceID, Jabra_BatteryStatus* batteryStatus) {
    if (BTheadsetFound && (BTheadsetId==deviceID)) {
        outputToConsole("Battery status callback - level: " + to_string((*batteryStatus).levelInPercent) + " % - Battery low: " + boolToString((*batteryStatus).batteryLow) + " - Battery charging: " + boolToString((*batteryStatus).charging));;
        Jabra_FreeBatteryStatus(batteryStatus);
    }
}
void DeviceAttachedFunc(Jabra_DeviceInfo deviceInfo)
{
    string deviceName = deviceInfo.deviceName;
    char buffer[32];
    Jabra_GetFirmwareVersion(deviceInfo.deviceID, buffer, static_cast<int>(sizeof(buffer)));
    outputToConsole("Device attached: " + deviceName + " - FW version: " + string(buffer));
    if (deviceName == "Jabra Link 380")
    {
        Link380deviceID = deviceInfo.deviceID;
        Link380Found = true; 
    }
    if (deviceInfo.deviceconnection == BT) {
        BTheadsetId=deviceInfo.deviceID;
        BTheadsetFound=true;
        // subscribe to battery state changes
        Jabra_RegisterBatteryStatusUpdateCallbackV2(batteryStatusCallback);
    }
}

void DeviceRemovedFunc(unsigned short deviceId)
{
    if(deviceId==Link380deviceID) {
        Link380Found=false;
        outputToConsole("Link 380 with id (" + (to_string(deviceId)) + ") has been removed");
    }
    if (deviceId==BTheadsetId) {
        BTheadsetFound=false;
        outputToConsole("Attached headset with id (" + (to_string(deviceId)) + ") has been removed or turned off");
    }

}

void JabraTranslatedButtonFunc(unsigned short deviceID, Jabra_HidInput hidinput, bool value)
{
    if (Link380Found && (Link380deviceID == deviceID))
    {
        if (hidinput == Online)
        {
            string valueString;
            if (value) { valueString="true"; } else { valueString="false"; }
            // Note: This is informational only - radio link quality only provides quality updates when the microphone is active and this event
            // does not guarantee that. The radio link can also be active when receiving any kind of audio (music, notification sounds, etc.) without the microphone being open. 
            outputToConsole("Headset radio link active: " + valueString);
        }
        if (hidinput == HeadsetConnection)
        {
            if (value == true)
            {
                outputToConsole("Headset connected to Link 380 - starting BT Link Quality listener");
                // start listening for BT Link quality.
                Jabra_ReturnCode retval = Jabra_SetLinkQualityStatusListener(deviceID, LinkQualityFunc);
                if (retval == Return_Ok)
                {
                    outputToConsole("BT Link Quality listener active");
                }
                else
                {
                    outputToConsole("Did it stop the BT Link quality listener?");
                }
            }
            else
            {
                outputToConsole("Headset disconnected from Link 380");
            }
        }
    }
}

int main()
{
    outputToConsole("Welcome to Peters c++ Jabra SDK sample app for getting BT Link quality and battery level from Jabra Link 380 and an attached headset");
    outputToConsole("Type exit, offhook, onhook or battery and hit ENTER");
    
    Jabra_SetAppID("Peters random appID");
    char buffer[32];
    Jabra_ReturnCode retval = Jabra_GetVersion(buffer, static_cast<int>(sizeof(buffer)));
    outputToConsole("Jabra SDK version: " + (retval == Return_Ok ? string(buffer) : "unknown"));

    if (!Jabra_InitializeV2(nullptr, DeviceAttachedFunc, DeviceRemovedFunc, nullptr, JabraTranslatedButtonFunc, true, nullptr))
    {
        outputToConsole("Unable to initialize library, please check the application ID");
    }
    string inputstring;

    while (true) {
        cin >> inputstring;
        if (inputstring == "offhook")
        {
            if (Link380Found) {
                Jabra_ReturnCode retval = Jabra_SetOffHook(Link380deviceID, true);
                if (retval == Return_Ok)
                {
                    outputToConsole("Sent offhook to Link 380");
                }
                else
                {
                    outputToConsole("Couldn't offhook Link 380");
                }
            } else {
                outputToConsole("No Link 380 dongle present - can't offhook");
            }
            
        }
        if (inputstring == "onhook") {
            if (Link380Found) {
                Jabra_ReturnCode retval = Jabra_SetOffHook(Link380deviceID, false);
                if (retval == Return_Ok)
                {
                    outputToConsole("Sent onhook to Link 380");
                }
                else
                {
                    outputToConsole("Couldn't onhook Link 380");
                }
            } else {
                outputToConsole("No Link 380 dongle present - can't onhook");
            }
            
        }
        if (inputstring == "battery") {
            Jabra_BatteryStatus* batteryStatus;
            Jabra_BatteryStatus** pointerTo_batteryStatus = &batteryStatus;

            Jabra_ReturnCode retval = Jabra_GetBatteryStatusV2(BTheadsetId, pointerTo_batteryStatus);
            if (retval==Return_Ok) {
                outputToConsole("Battery level: " + to_string((**pointerTo_batteryStatus).levelInPercent) + " % - Battery low: " + boolToString((*batteryStatus).batteryLow) + " - Battery charging: " + boolToString((*batteryStatus).charging));
            }
            Jabra_FreeBatteryStatus(batteryStatus);
        }
        if (inputstring == "exit") {
            outputToConsole("Exiting program");
            return 0;
        }
    }
}
