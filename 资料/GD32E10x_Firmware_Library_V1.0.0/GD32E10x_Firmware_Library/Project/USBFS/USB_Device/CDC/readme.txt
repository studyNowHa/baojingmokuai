/*!
    \file  readme.txt
    \brief description of the the USB CDC demo
    
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

  This demo is based on the GD32E10x-EVAL board,it provides a description of 
how to use the USBFS.

  It illustrates an implementation of the CDC class following the PSTN subprotocol.

  The VCP example allows the GD32 device to behave as a USB-to-RS232 bridge:

  - On one side, the GD32 communicates with host (PC) through USB interface in
    Device mode.

  - On the other side, the GD32 communicates with other devices(same host,other
    host,other devices) through the USART interface (RS232).

  The support of the VCP interface is managed through the GD Virtual Com Port driver
available for download from www.gd32mcu.21ic.com.

  When the VCP application starts,the USB device is enumerated as serial communication
port and can be configured in the same way(baudrate,data format,parity,stop bit length).

  To test the demo, you can use one of the following configurations:

  - Configuration 1: Connect USB cable to host and USART (RS232) to a different host
    (PC or other device) or to the same host. In this case, you can open two hyperterminal-like
    terminals to send/receive data from/to host to/from device.

  - Configuration 2: Connect USB cable to Host and connect USART TX pin to USART
    RX pin on the evaluation board (Loopback mode). In this case, you can open one
    terminal (relative to USB com port or USART com port) and all data sent from this
    terminal will be received by the same terminal in loopback mode. This mode is useful
    for test and performance measurements.

  When transferring a big file (USB OUT transfer) user has to adapt the size
of IN buffer, for more details refer to usbd_conf.h file (APP_RX_DATA_SIZE constant). 
This CDC Demo provides the firmware examples for the GD32E10x families.
