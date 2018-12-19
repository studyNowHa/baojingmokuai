/*!
    \file  readme.txt
    \brief description of the the USB HID/CDC composite demo
    
    \version 2017-12-26, V1.0.0, firmware for GD32E10x
*/

/*
    Copyright (c) 2017, GigaDevice Semiconductor Inc.

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

  The demo provide a composite device.

  A composite device is one that has multiple interfaces controlled independently
of each other. Using composite device, multiple functions are combined into a single
device. In this Example the independent interfaces are : Custom HID (HID) and VCP (CDC).

  This demo was created by combining the code in the HID_custom and CDC ACM.

  The implementation of the composite HID-CDC device is done by creating a wrapping class 
(see folder hid_cdc_wrapper ) that makes calls to the separate HID and CDC class layer
handlers (files cdc_acm_core.c and custom_hid_core.c files).

  To test the demo, you can run Custom HID demo and at same time you can select the
GD32 virtual comport (you need to follow same steps as the CDC ACM example).

  To run this example, you will need to modify the following lines in the .inf file of the 
cdc driver: GDUSB2Ser.inf.

  The GDUSB2Ser.inf exists to assist in the loading of the proper USB serial drivers in the 
Windows OSs for the composite device to operate correctly as a virtual COM interface.

  The following Lines associates the CDC device with the OS usbser.sys driver file 
and causes the OS to load this driver during the enumeration process.

  The "MI" stands for Multiple Interface.

    ***********************************************
    ;VID/PID Settings
    ;------------------------------------------------------------------------------
    [DeviceList.NT]
    %DESCRIPTION%=DriverInstall,USB\VID_0x28E9&PID_0x028C&MI_01

    [DeviceList.NTamd64]
    %DESCRIPTION%=DriverInstall,USB\VID_0x28E9&PID_0x028C&MI_01

    ******************************************************
  When even one of the interface class of the device is changed, it should be handled
differently by Windows. However, it doesn't recognize the modification. To avoid conflict
on Windows, we suggest to assign another VID/PID to the device or delete device instance 
from device manager.
