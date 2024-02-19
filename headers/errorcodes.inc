//Note to Jabra SDK developers:  Define new Jabra_ErrorStatus values here. Please do NOT change the order, but add at the end

DEFINE_CODE(NoError, "No Error")
DEFINE_CODE(SSLError, "SSL Handshake failed. Please contact your administrator")
DEFINE_CODE(CertError, "Failed to Authenticate Server Certificate. Please contact your administrator")
DEFINE_CODE(NetworkError, "Unable to download the files. Please check Internet connection and reconnect the device")
DEFINE_CODE(DownloadError, "Setting files download failed. Please contact your administrator")
DEFINE_CODE(ParseError, "Unable to retrieve device settings. Please reconnect device")
DEFINE_CODE(OtherError, "Unknown error. Please contact your administrator")
DEFINE_CODE(DeviceInfoError, "Unable to retrieve device information. Please reconnect device")
DEFINE_CODE(FileNotAccessible, "File is not accessible")
DEFINE_CODE(FileNotCompatible, "File is not compatible for the device")
DEFINE_CODE(Device_NotFound, "The specified device is not found")
DEFINE_CODE(Parameter_fail, "Incorrect parameters")
DEFINE_CODE(Authorization_failed, "Authorization failed")
DEFINE_CODE(FileNotAvailable,"Files are not available for the device. Please check internet connection and reconnect the device")
DEFINE_CODE(ConfigParseError, "Config XML parse error")
DEFINE_CODE(SetSettings_Fail, "Error in applying settings")
DEFINE_CODE(Device_Reboot, "Device will reboot due to change in the settings")
DEFINE_CODE(Device_ReadFail,"Unable to read settings from the device")
DEFINE_CODE(Device_NotReady, "The device is not ready")
DEFINE_CODE(FilePartiallyCompatible, "Partial Settings loaded")
DEFINE_CODE(SdkTooOldForFwUpdateError, "The Jabra SDK is too old to update the selected firmware")
DEFINE_CODE(UpdateIsNotReady, "The resource is not yet ready to be updated")