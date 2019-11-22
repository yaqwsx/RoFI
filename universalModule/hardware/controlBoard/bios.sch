EESchema Schematic File Version 4
LIBS:controlBoard-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 6
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R R?
U 1 1 5E2D4CCB
P 1900 6050
AR Path="/5E080FD6/5E2D4CCB" Ref="R?"  Part="1" 
AR Path="/5E2C3773/5E2D4CCB" Ref="R38"  Part="1" 
F 0 "R38" H 1970 6096 50  0000 L CNN
F 1 "2k2" H 1970 6005 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1830 6050 50  0001 C CNN
F 3 "~" H 1900 6050 50  0001 C CNN
F 4 "RR0510P-222-D" H 1900 6050 50  0001 C CNN "#manf"
	1    1900 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E2D4CD1
P 2300 6050
AR Path="/5E080FD6/5E2D4CD1" Ref="R?"  Part="1" 
AR Path="/5E2C3773/5E2D4CD1" Ref="R40"  Part="1" 
F 0 "R40" H 2370 6096 50  0000 L CNN
F 1 "2k2" H 2370 6005 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2230 6050 50  0001 C CNN
F 3 "~" H 2300 6050 50  0001 C CNN
F 4 "RR0510P-222-D" H 2300 6050 50  0001 C CNN "#manf"
	1    2300 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E2D4CD7
P 1900 6550
AR Path="/5E080FD6/5E2D4CD7" Ref="R?"  Part="1" 
AR Path="/5E2C3773/5E2D4CD7" Ref="R39"  Part="1" 
F 0 "R39" H 1970 6596 50  0000 L CNN
F 1 "10k" H 1970 6505 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1830 6550 50  0001 C CNN
F 3 "~" H 1900 6550 50  0001 C CNN
F 4 "RT0402FRE0710KL" H 1900 6550 50  0001 C CNN "#manf"
	1    1900 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E2D4CDD
P 2300 6550
AR Path="/5E080FD6/5E2D4CDD" Ref="R?"  Part="1" 
AR Path="/5E2C3773/5E2D4CDD" Ref="R41"  Part="1" 
F 0 "R41" H 2370 6596 50  0000 L CNN
F 1 "10k" H 2370 6505 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2230 6550 50  0001 C CNN
F 3 "~" H 2300 6550 50  0001 C CNN
F 4 "RT0402FRE0710KL" H 2300 6550 50  0001 C CNN "#manf"
	1    2300 6550
	1    0    0    -1  
$EndComp
Text GLabel 2500 6300 2    50   Input ~ 0
USB_C_D+
Text GLabel 1800 6300 0    50   Input ~ 0
USB_C_D-
Wire Wire Line
	2300 6200 2300 6300
Wire Wire Line
	2300 6300 2500 6300
Connection ~ 2300 6300
Wire Wire Line
	2300 6300 2300 6400
Wire Wire Line
	1900 6200 1900 6300
Wire Wire Line
	1900 6300 1800 6300
Wire Wire Line
	1900 6300 1900 6400
Connection ~ 1900 6300
Wire Wire Line
	1900 5900 1900 5800
Wire Wire Line
	1900 5800 1850 5800
Wire Wire Line
	2300 5900 2300 5800
Wire Wire Line
	2300 5800 2350 5800
Wire Wire Line
	2300 6700 2300 6900
Wire Wire Line
	2300 6900 2350 6900
Wire Wire Line
	1900 6700 1900 6900
Wire Wire Line
	1900 6900 1850 6900
Text GLabel 1850 5800 0    50   Input ~ 0
QC_2_M
Text GLabel 1850 6900 0    50   Input ~ 0
QC_10_N
Text GLabel 2350 6900 2    50   Input ~ 0
QC_10_P
Text GLabel 2350 5800 2    50   Input ~ 0
QC_2_P
Text Notes 1850 5650 0    50   ~ 0
QuickCharge 3
Text Notes 1400 7200 0    50   ~ 0
https://github.com/Crypter/QC3Client/\nhttp://blog.deconinck.info/post/2017/08/09/Turning-a-Quick-Charge-3.0-charger-into-a-variable-voltage-power-supply
Text GLabel 3550 3300 0    50   Input ~ 0
BIOS_SDA
Text GLabel 3550 3200 0    50   Input ~ 0
BIOS_SCL
Text GLabel 4750 2600 2    50   Input ~ 0
BATT_VOLTAGE
Text GLabel 4750 3500 2    50   Input ~ 0
BIOS_TX
Text GLabel 4750 3600 2    50   Input ~ 0
BIOS_RX
Text GLabel 3550 4100 0    50   Input ~ 0
QC_2_M
Text GLabel 3550 4000 0    50   Input ~ 0
QC_10_N
Text GLabel 3550 3900 0    50   Input ~ 0
QC_2_P
Text GLabel 3550 3800 0    50   Input ~ 0
QC_10_P
Text GLabel 3550 3700 0    50   Input ~ 0
USB_BRIDGE_EN
Text GLabel 3550 3400 0    50   Input ~ 0
SW_SHUTDOWN
Text GLabel 3550 1300 0    50   Input ~ 0
SWRST
Wire Wire Line
	4050 4300 4050 4400
Wire Wire Line
	4050 4400 4150 4400
Wire Wire Line
	4150 4400 4150 4300
Wire Wire Line
	4250 4300 4250 4400
Wire Wire Line
	4250 4400 4150 4400
Connection ~ 4150 4400
$Comp
L power:GND #PWR0163
U 1 1 5E31885C
P 4150 4500
F 0 "#PWR0163" H 4150 4250 50  0001 C CNN
F 1 "GND" H 4155 4327 50  0000 C CNN
F 2 "" H 4150 4500 50  0001 C CNN
F 3 "" H 4150 4500 50  0001 C CNN
	1    4150 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 4500 4150 4400
Text GLabel 3550 3500 0    50   Input ~ 0
CHG_EN
Text GLabel 3550 3000 0    50   Input ~ 0
BATT_TO_BUS_EN
Text GLabel 3550 3100 0    50   Input ~ 0
USB_TO_BUS_EN
NoConn ~ 3550 1500
$Comp
L Device:R R42
U 1 1 5E461392
P 6600 1200
F 0 "R42" H 6670 1246 50  0000 L CNN
F 1 "68k" H 6670 1155 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6530 1200 50  0001 C CNN
F 3 "~" H 6600 1200 50  0001 C CNN
F 4 "RR0510P-683-D" H 6600 1200 50  0001 C CNN "#manf"
	1    6600 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R43
U 1 1 5E4619AD
P 6600 1600
F 0 "R43" H 6670 1646 50  0000 L CNN
F 1 "10k" H 6670 1555 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6530 1600 50  0001 C CNN
F 3 "~" H 6600 1600 50  0001 C CNN
F 4 "RT0402FRE0710KL" H 6600 1600 50  0001 C CNN "#manf"
	1    6600 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR035
U 1 1 5E462349
P 6600 1750
F 0 "#PWR035" H 6600 1500 50  0001 C CNN
F 1 "GND" H 6605 1577 50  0000 C CNN
F 2 "" H 6600 1750 50  0001 C CNN
F 3 "" H 6600 1750 50  0001 C CNN
	1    6600 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 1350 6600 1400
Wire Wire Line
	6600 1400 7150 1400
Connection ~ 6600 1400
Wire Wire Line
	6600 1400 6600 1450
Text GLabel 6450 1000 0    50   Input ~ 0
USB_C_VDD
Text GLabel 7150 1400 2    50   Input ~ 0
USB_VOLTAGE
Text GLabel 4750 2700 2    50   Input ~ 0
USB_VOLTAGE
$Comp
L Device:R R44
U 1 1 5E466449
P 6600 2700
F 0 "R44" H 6670 2746 50  0000 L CNN
F 1 "68k" H 6670 2655 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6530 2700 50  0001 C CNN
F 3 "~" H 6600 2700 50  0001 C CNN
F 4 "RR0510P-683-D" H 6600 2700 50  0001 C CNN "#manf"
	1    6600 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R45
U 1 1 5E466EEE
P 6600 3150
F 0 "R45" H 6670 3196 50  0000 L CNN
F 1 "10k" H 6670 3105 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6530 3150 50  0001 C CNN
F 3 "~" H 6600 3150 50  0001 C CNN
F 4 "RT0402FRE0710KL" H 6600 3150 50  0001 C CNN "#manf"
	1    6600 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 1000 6600 1000
Wire Wire Line
	6600 1000 6600 1050
$Comp
L power:+12V #PWR034
U 1 1 5E469280
P 6350 2550
F 0 "#PWR034" H 6350 2400 50  0001 C CNN
F 1 "+12V" V 6365 2678 50  0000 L CNN
F 2 "" H 6350 2550 50  0001 C CNN
F 3 "" H 6350 2550 50  0001 C CNN
	1    6350 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6350 2550 6600 2550
Wire Wire Line
	6600 2850 6600 2900
$Comp
L power:GND #PWR036
U 1 1 5E469DC2
P 6600 3300
F 0 "#PWR036" H 6600 3050 50  0001 C CNN
F 1 "GND" H 6605 3127 50  0000 C CNN
F 2 "" H 6600 3300 50  0001 C CNN
F 3 "" H 6600 3300 50  0001 C CNN
	1    6600 3300
	1    0    0    -1  
$EndComp
Text GLabel 6950 2900 2    50   Input ~ 0
BUS_VOLTAGE
Wire Wire Line
	6950 2900 6600 2900
Connection ~ 6600 2900
Wire Wire Line
	6600 2900 6600 3000
Text GLabel 4750 2800 2    50   Input ~ 0
BUS_VOLTAGE
$Comp
L Connector:TestPoint TP8
U 1 1 5E49E83C
P 6600 1000
F 0 "TP8" H 6658 1118 50  0000 L CNN
F 1 "TP_USB_VDD" H 6658 1027 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 6800 1000 50  0001 C CNN
F 3 "~" H 6800 1000 50  0001 C CNN
	1    6600 1000
	1    0    0    -1  
$EndComp
Connection ~ 6600 1000
$Comp
L Connector:TestPoint TP9
U 1 1 5E4A1435
P 6600 2550
F 0 "TP9" H 6658 2668 50  0000 L CNN
F 1 "TP_BUS" H 6658 2577 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 6800 2550 50  0001 C CNN
F 3 "~" H 6800 2550 50  0001 C CNN
	1    6600 2550
	1    0    0    -1  
$EndComp
Connection ~ 6600 2550
$Comp
L Device:R R?
U 1 1 5E4BE615
P 6600 4300
AR Path="/5DFADF1E/5E4BE615" Ref="R?"  Part="1" 
AR Path="/5E2C3773/5E4BE615" Ref="R46"  Part="1" 
F 0 "R46" H 6670 4346 50  0000 L CNN
F 1 "20k" H 6670 4255 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6530 4300 50  0001 C CNN
F 3 "~" H 6600 4300 50  0001 C CNN
F 4 "RR0510P-203-D" H 6600 4300 50  0001 C CNN "#manf"
	1    6600 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E4BE61B
P 6600 4600
AR Path="/5DFADF1E/5E4BE61B" Ref="R?"  Part="1" 
AR Path="/5E2C3773/5E4BE61B" Ref="R47"  Part="1" 
F 0 "R47" H 6670 4646 50  0000 L CNN
F 1 "10k" H 6670 4555 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6530 4600 50  0001 C CNN
F 3 "~" H 6600 4600 50  0001 C CNN
F 4 "RT0402FRE0710KL" H 6600 4600 50  0001 C CNN "#manf"
	1    6600 4600
	1    0    0    -1  
$EndComp
Text GLabel 6500 4000 0    50   Input ~ 0
BAT+
Wire Wire Line
	6600 4450 7250 4450
Connection ~ 6600 4450
Text GLabel 7250 4450 2    50   Input ~ 0
BATT_VOLTAGE
$Comp
L power:GND #PWR?
U 1 1 5E4BE625
P 6600 4750
AR Path="/5DFADF1E/5E4BE625" Ref="#PWR?"  Part="1" 
AR Path="/5E2C3773/5E4BE625" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 6600 4500 50  0001 C CNN
F 1 "GND" H 6605 4577 50  0000 C CNN
F 2 "" H 6600 4750 50  0001 C CNN
F 3 "" H 6600 4750 50  0001 C CNN
	1    6600 4750
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5E4BE62C
P 6600 4000
AR Path="/5DFADF1E/5E4BE62C" Ref="TP?"  Part="1" 
AR Path="/5E2C3773/5E4BE62C" Ref="TP10"  Part="1" 
F 0 "TP10" H 6658 4118 50  0000 L CNN
F 1 "TP_BAT" H 6658 4027 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 6800 4000 50  0001 C CNN
F 3 "~" H 6800 4000 50  0001 C CNN
	1    6600 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 4000 6600 4000
Wire Wire Line
	6600 4000 6600 4150
Connection ~ 6600 4000
$Comp
L Connector:USB_C_Plug_USB2.0 P1
U 1 1 5E51FEBE
P 1300 2050
F 0 "P1" H 1407 2917 50  0000 C CNN
F 1 "USB_C_Plug_USB2.0" H 1407 2826 50  0000 C CNN
F 2 "rofi:USB_C_Female-6Pin" H 1450 2050 50  0001 C CNN
F 3 "https://www.usb.org/sites/default/files/documents/usb_type-c.zip" H 1450 2050 50  0001 C CNN
	1    1300 2050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR030
U 1 1 5E523893
P 1300 2950
F 0 "#PWR030" H 1300 2700 50  0001 C CNN
F 1 "GND" H 1305 2777 50  0000 C CNN
F 2 "" H 1300 2950 50  0001 C CNN
F 3 "" H 1300 2950 50  0001 C CNN
	1    1300 2950
	1    0    0    -1  
$EndComp
Connection ~ 1300 2950
Text GLabel 1900 2150 2    50   Input ~ 0
USB_C_D+
Text GLabel 1900 1950 2    50   Input ~ 0
USB_C_D-
NoConn ~ 1900 1750
Text GLabel 2200 1450 2    50   Input ~ 0
USB_C_VDD
NoConn ~ 1900 1650
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 5E52BC10
P 1050 3700
F 0 "J3" H 968 3275 50  0000 C CNN
F 1 "USB_ALT" H 968 3366 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 1050 3700 50  0001 C CNN
F 3 "~" H 1050 3700 50  0001 C CNN
	1    1050 3700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR029
U 1 1 5E52E29E
P 1250 3800
F 0 "#PWR029" H 1250 3550 50  0001 C CNN
F 1 "GND" H 1255 3627 50  0000 C CNN
F 2 "" H 1250 3800 50  0001 C CNN
F 3 "" H 1250 3800 50  0001 C CNN
	1    1250 3800
	1    0    0    -1  
$EndComp
Text GLabel 1250 3600 2    50   Input ~ 0
USB_C_D+
Text GLabel 1250 3700 2    50   Input ~ 0
USB_C_D-
Text GLabel 1250 3500 2    50   Input ~ 0
USB_C_VDD
Wire Wire Line
	1000 2950 1300 2950
Wire Wire Line
	4050 1100 4050 1000
Wire Wire Line
	4050 1000 4150 1000
Wire Wire Line
	4150 1000 4150 1100
Wire Wire Line
	4150 1000 4250 1000
Wire Wire Line
	4250 1000 4250 1100
Connection ~ 4150 1000
Wire Wire Line
	4250 1000 4350 1000
Wire Wire Line
	4350 1000 4350 1100
Connection ~ 4250 1000
Wire Wire Line
	4050 1000 3850 1000
Wire Wire Line
	3850 1000 3850 900 
Connection ~ 4050 1000
$Comp
L power:+3V3 #PWR031
U 1 1 5E5597B0
P 3850 900
F 0 "#PWR031" H 3850 750 50  0001 C CNN
F 1 "+3V3" H 3865 1073 50  0000 C CNN
F 2 "" H 3850 900 50  0001 C CNN
F 3 "" H 3850 900 50  0001 C CNN
	1    3850 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1000 5000 1000
Connection ~ 4350 1000
$Comp
L Device:C C51
U 1 1 5E55A60F
P 5000 1150
F 0 "C51" H 5115 1196 50  0000 L CNN
F 1 "22u" H 5115 1105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5038 1000 50  0001 C CNN
F 3 "~" H 5000 1150 50  0001 C CNN
F 4 "GRM21BR61C226ME44L" H 5000 1150 50  0001 C CNN "#manf"
	1    5000 1150
	1    0    0    -1  
$EndComp
Connection ~ 5000 1000
Wire Wire Line
	5000 1000 5400 1000
$Comp
L Device:C C52
U 1 1 5E55BC62
P 5400 1150
F 0 "C52" H 5515 1196 50  0000 L CNN
F 1 "470n" H 5515 1105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5438 1000 50  0001 C CNN
F 3 "~" H 5400 1150 50  0001 C CNN
F 4 "JMK105BJ474KV-F" H 5400 1150 50  0001 C CNN "#manf"
	1    5400 1150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR033
U 1 1 5E55D85D
P 5400 1300
F 0 "#PWR033" H 5400 1050 50  0001 C CNN
F 1 "GND" H 5405 1127 50  0000 C CNN
F 2 "" H 5400 1300 50  0001 C CNN
F 3 "" H 5400 1300 50  0001 C CNN
	1    5400 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR032
U 1 1 5E55DAC6
P 5000 1300
F 0 "#PWR032" H 5000 1050 50  0001 C CNN
F 1 "GND" H 5005 1127 50  0000 C CNN
F 2 "" H 5000 1300 50  0001 C CNN
F 3 "" H 5000 1300 50  0001 C CNN
	1    5000 1300
	1    0    0    -1  
$EndComp
Text GLabel 8600 1100 0    50   Input ~ 0
BATT_VDD
$Comp
L Device:R R48
U 1 1 5E561484
P 8900 1100
F 0 "R48" V 8693 1100 50  0000 C CNN
F 1 "1k" V 8784 1100 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8830 1100 50  0001 C CNN
F 3 "~" H 8900 1100 50  0001 C CNN
F 4 "RR0510P-102-D" H 8900 1100 50  0001 C CNN "#manf"
	1    8900 1100
	0    1    1    0   
$EndComp
$Comp
L Device:LED D11
U 1 1 5E561C55
P 9300 1100
F 0 "D11" H 9293 845 50  0000 C CNN
F 1 "GREEN" H 9293 936 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 9300 1100 50  0001 C CNN
F 3 "~" H 9300 1100 50  0001 C CNN
	1    9300 1100
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR040
U 1 1 5E562097
P 9650 1100
F 0 "#PWR040" H 9650 850 50  0001 C CNN
F 1 "GND" V 9655 972 50  0000 R CNN
F 2 "" H 9650 1100 50  0001 C CNN
F 3 "" H 9650 1100 50  0001 C CNN
	1    9650 1100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9650 1100 9450 1100
Wire Wire Line
	9150 1100 9050 1100
Wire Wire Line
	8750 1100 8600 1100
$Comp
L power:+3V3 #PWR038
U 1 1 5E563DF5
P 8550 1600
F 0 "#PWR038" H 8550 1450 50  0001 C CNN
F 1 "+3V3" V 8565 1728 50  0000 L CNN
F 2 "" H 8550 1600 50  0001 C CNN
F 3 "" H 8550 1600 50  0001 C CNN
	1    8550 1600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R49
U 1 1 5E5643A0
P 8900 1600
F 0 "R49" V 8693 1600 50  0000 C CNN
F 1 "1k" V 8784 1600 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8830 1600 50  0001 C CNN
F 3 "~" H 8900 1600 50  0001 C CNN
F 4 "RR0510P-102-D" H 8900 1600 50  0001 C CNN "#manf"
	1    8900 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	8550 1600 8750 1600
$Comp
L Device:LED D12
U 1 1 5E565AD1
P 9300 1600
F 0 "D12" H 9293 1345 50  0000 C CNN
F 1 "GREEN" H 9293 1436 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 9300 1600 50  0001 C CNN
F 3 "~" H 9300 1600 50  0001 C CNN
	1    9300 1600
	-1   0    0    1   
$EndComp
Wire Wire Line
	9150 1600 9050 1600
$Comp
L power:GND #PWR041
U 1 1 5E566804
P 9650 1600
F 0 "#PWR041" H 9650 1350 50  0001 C CNN
F 1 "GND" V 9655 1472 50  0000 R CNN
F 2 "" H 9650 1600 50  0001 C CNN
F 3 "" H 9650 1600 50  0001 C CNN
	1    9650 1600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9650 1600 9450 1600
$Comp
L Device:R R50
U 1 1 5E56CB68
P 8900 2050
F 0 "R50" V 8693 2050 50  0000 C CNN
F 1 "1k" V 8784 2050 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8830 2050 50  0001 C CNN
F 3 "~" H 8900 2050 50  0001 C CNN
F 4 "RR0510P-102-D" H 8900 2050 50  0001 C CNN "#manf"
	1    8900 2050
	0    1    1    0   
$EndComp
Wire Wire Line
	8550 2050 8750 2050
$Comp
L Device:LED D13
U 1 1 5E56CB73
P 9300 2050
F 0 "D13" H 9293 1795 50  0000 C CNN
F 1 "GREEN" H 9293 1886 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 9300 2050 50  0001 C CNN
F 3 "~" H 9300 2050 50  0001 C CNN
	1    9300 2050
	-1   0    0    1   
$EndComp
Wire Wire Line
	9150 2050 9050 2050
$Comp
L power:GND #PWR042
U 1 1 5E56CB7E
P 9650 2050
F 0 "#PWR042" H 9650 1800 50  0001 C CNN
F 1 "GND" V 9655 1922 50  0000 R CNN
F 2 "" H 9650 2050 50  0001 C CNN
F 3 "" H 9650 2050 50  0001 C CNN
	1    9650 2050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9650 2050 9450 2050
$Comp
L power:+12V #PWR039
U 1 1 5E571594
P 8550 2050
F 0 "#PWR039" H 8550 1900 50  0001 C CNN
F 1 "+12V" V 8565 2178 50  0000 L CNN
F 2 "" H 8550 2050 50  0001 C CNN
F 3 "" H 8550 2050 50  0001 C CNN
	1    8550 2050
	0    -1   -1   0   
$EndComp
Text GLabel 4750 3800 2    50   Input ~ 0
SW_UP
$Comp
L MCU_ST_STM32F0:STM32F030C8Tx U9
U 1 1 5E2C5D19
P 4150 2700
F 0 "U9" H 4550 4250 50  0000 C CNN
F 1 "STM32F030C8Tx" H 4300 3750 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 3650 1200 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00088500.pdf" H 4150 2700 50  0001 C CNN
F 4 "STM32F030C8T6TR" H 4150 2700 50  0001 C CNN "#manf"
	1    4150 2700
	1    0    0    -1  
$EndComp
Text GLabel 4750 3700 2    50   Input ~ 0
SW_DOWN
Text GLabel 4750 4100 2    50   Input ~ 0
SW_MID
Text GLabel 3550 2900 0    50   Input ~ 0
SW_LEFT
Text GLabel 3550 2800 0    50   Input ~ 0
SW_RIGHT
Wire Wire Line
	2200 1450 2050 1450
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5E92975E
P 2050 1450
F 0 "#FLG0101" H 2050 1525 50  0001 C CNN
F 1 "PWR_FLAG" H 2050 1623 50  0000 C CNN
F 2 "" H 2050 1450 50  0001 C CNN
F 3 "~" H 2050 1450 50  0001 C CNN
	1    2050 1450
	1    0    0    -1  
$EndComp
Connection ~ 2050 1450
Wire Wire Line
	2050 1450 1900 1450
NoConn ~ 3550 1700
NoConn ~ 3550 1800
NoConn ~ 3550 1900
NoConn ~ 3550 2000
NoConn ~ 3550 2200
NoConn ~ 3550 2300
NoConn ~ 3550 2400
NoConn ~ 4750 2900
NoConn ~ 4750 3000
NoConn ~ 4750 3400
NoConn ~ 4750 3300
NoConn ~ 4750 3200
NoConn ~ 4750 3100
Text GLabel 4750 4000 2    50   Input ~ 0
SWCLK
Text GLabel 4750 3900 2    50   Input ~ 0
SWDIO
$Comp
L Connector_Generic:Conn_01x05 J8
U 1 1 5E94226A
P 5400 5100
F 0 "J8" H 5480 5142 50  0000 L CNN
F 1 "BIOS_SWD" H 5480 5051 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 5400 5100 50  0001 C CNN
F 3 "~" H 5400 5100 50  0001 C CNN
	1    5400 5100
	1    0    0    -1  
$EndComp
Text GLabel 5200 5100 0    50   Input ~ 0
SWRST
Text GLabel 5200 4900 0    50   Input ~ 0
SWCLK
Text GLabel 5200 5000 0    50   Input ~ 0
SWDIO
$Comp
L power:GND #PWR0147
U 1 1 5E946757
P 5150 5350
F 0 "#PWR0147" H 5150 5100 50  0001 C CNN
F 1 "GND" H 5155 5177 50  0000 C CNN
F 2 "" H 5150 5350 50  0001 C CNN
F 3 "" H 5150 5350 50  0001 C CNN
	1    5150 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 5350 5150 5300
Wire Wire Line
	5150 5300 5200 5300
$Comp
L power:+3V3 #PWR0149
U 1 1 5E9482B0
P 4850 5200
F 0 "#PWR0149" H 4850 5050 50  0001 C CNN
F 1 "+3V3" V 4865 5328 50  0000 L CNN
F 2 "" H 4850 5200 50  0001 C CNN
F 3 "" H 4850 5200 50  0001 C CNN
	1    4850 5200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4850 5200 5200 5200
Text GLabel 3550 3600 0    50   Input ~ 0
CHG_OK
Text GLabel 3550 2700 0    50   Input ~ 0
USB_CLK
Text GLabel 3550 2600 0    50   Input ~ 0
USB_SUSPEND
$EndSCHEMATC