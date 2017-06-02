Texas Instruments, Inc.

ZAP-MSP430 Release Notes

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

Version 1.0.4
July 25, 2011


Notices:
 - ZAP-MSP430 supports ZigBee Application Processor (ZAP) development
   on Texas Instruments EXP5438 and MSP2618 platforms. ZAP devices
   communicate with ZigBee Network Processor (ZNP) devices to form a
   "host + wireless modem" solution using ZigBee technology.

 - ZAP project files have been built and tested with EW430 version 5.20.4
   (5.20.4.50259) of the IAR Embedded Workbench toolset.

 - Z-Stack has been built and tested with IAR's CLIB library, which provides
   a light-weight C library which does not support Embedded C++. Use of
   DLIB is not recommended since Z-Stack is not tested with that library.

 - When programming a target for the first time release, make sure to
   select the "Erase main memory" option in the Debugger->FET Debugger
   category of IAR project options. When programming completes, select
   "Retain unchanged memory" so that NV items are retained during later
   re-programming of the device.


Changes:
 - Minor updates to the "Z-Stack User's Guide for CC2530 ZigBee-PRO
   Network Processor - Sample Applications" document.

 - The CC2530ZNP hex files in this release have been rebuilt to utilize
   improvements incorporated in the ZStack-CC2530-2.5.0 release.


Bug Fixes:
 - None.


Known Issues:
 - None.

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
