# serial communication program in C

## how to use with WSL2
+ install USBIPD https://learn.microsoft.com/ja-jp/windows/wsl/connect-usb
+ connect a USB serial device (such as Arduino)
+ start Windows Power Shell with administrator account
- > usbpid list
- > usbipd attach --busid <BUSID of the USB device shown in the list above> --wsl Ubuntu-24.04
+ start WSL2 (Ubuntu-24.04)
- $ lsusb
+ $ ./serial /dev/ttyACM0
