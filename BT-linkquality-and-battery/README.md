# BT link quality and battery sample for Jabra Link 380 and connected headsets
This code sample uses the Jabra Linux SDK to get link quality and battery updates from the Jabra Link 380 BT dongle and a connected Jabra headset. The sample is provided "as is" with no guarantee that it will work correctly in all cases. 

## How to build and run the code sample
Before trying to build the project in Visual Studio Code you need to create 2 symbolic links to the libjabra.so.1.12.2.0 files:
```
ln -s libjabra.so.1.12.2.0 libjabra.so.1
ln -s libjabra.so.1.12.2.0 libjabra.so
```
