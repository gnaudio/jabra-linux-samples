# BT link quality and battery sample for Jabra Link 380 and connected headsets
This code sample uses the Jabra Linux SDK to get link quality and battery updates from the Jabra Link 380 BT dongle and a connected Jabra headset. The sample is provided "as is" with no guarantee that it will work correctly in all cases. The sample was built on Ubuntu 22.04 using Visual Studio Code. 
For more information in general on the Jabra Linux SDK please visit the [Jabra Developer Zone](https://developer.jabra.com/site/global/sdk/linux/index.gsp)

## How to build and run the code sample
Before trying to build the project in Visual Studio Code you need to create 2 symbolic links to the libjabra.so.1.12.2.0 file:
```
ln -s libjabra.so.1.12.2.0 libjabra.so.1
ln -s libjabra.so.1.12.2.0 libjabra.so
```
To be able to communicate with Jabra devices with non-root privileges it is required to create a udev rule for Jabra devices. Place the udev rule in /etc/udev/rules.d with a name that respect the order by which rules are processed (in lexicographical order). By example:
```
sudo <your-favorite-text-editor> /etc/udev/rules.d/99-jabra.rules
```
The content of the file is:
```
ATTRS{idVendor}=="0b0e", MODE="0666", GROUP="users"
```
After creating the udev file (as root), reload the udev rules using:
```
sudo udevadm control --reload
```
Reattach your Jabra device in order to get new permissions assigned.

Now re-launch VS Code, select the .cpp file and it should compile and debug correctly. 

## Questions and requests for support
While we do invite for collaboration on the code samples from the community here (please do make a pull-request if you want to help improve it), questions are best asked at the Jabra Developer Zone by opening a ticket there: [Jabra Developer Zone support](https://developer.jabra.com/site/global/support/index.gsp)