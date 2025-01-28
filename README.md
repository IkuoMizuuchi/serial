# serial communication program in C

## how to use with WSL2
+ install USBIPD https://learn.microsoft.com/ja-jp/windows/wsl/connect-usb
+ connect a USB serial device (such as Arduino)
+ start Windows Power Shell with administrator account
  + usbipd list
  + usbipd bind --busid \<BUSID of the USB device shown in the list above\> 
  + usbipd attach --busid \<BUSID\> --wsl Ubuntu-24.04
+ start WSL2 (Ubuntu-24.04)
  + $ lsusb
  + $ ./serial /dev/ttyACM0
+ to use the serial (such as for modifying the Arduino sketch)
  + In Windows Power Shell
    + usbipd detach --busid \<BUSID\>
  + In Windows
    + Upload the firmware to Arduino
  + In Windows Power Shell
    + usbipd attach --busid \<BUSID\> --wsl Ubuntu-24.04
