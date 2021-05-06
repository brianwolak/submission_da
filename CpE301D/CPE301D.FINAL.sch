EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Atmega 328pb CPE301D Final Project"
Date "May 5th 2021"
Rev ""
Comp "Brian Wolak"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 8950 1450 1    60   ~ 0
Vin
Text Label 9350 1450 1    60   ~ 0
Vcc
Text Label 8900 2500 0    60   ~ 0
PC0
Text Label 8900 2600 0    60   ~ 0
PC1
Text Label 8900 2700 0    60   ~ 0
PC2
Text Label 8900 2800 0    60   ~ 0
PC3
Text Label 8900 2900 0    60   ~ 0
PC4
Text Label 8900 3000 0    60   ~ 0
PC5
Text Label 10550 3000 0    60   ~ 0
PD0(TX)
Text Label 10550 2800 0    60   ~ 0
PD2
Text Label 10550 2900 0    60   ~ 0
PD1(RX)
Text Label 10550 2700 0    60   ~ 0
PD3
Text Label 10550 2600 0    60   ~ 0
PD4
Text Label 10550 2500 0    60   ~ 0
PD5
Text Label 10550 2400 0    60   ~ 0
PD6
Text Label 10550 2300 0    60   ~ 0
PD7
Text Label 10550 2100 0    60   ~ 0
PB0
Text Label 10550 2000 0    60   ~ 0
PB1
Text Label 10550 1900 0    60   ~ 0
PB2
Text Label 10550 1800 0    60   ~ 0
PB3
Text Label 10550 1700 0    60   ~ 0
PB4
Text Label 10550 1600 0    60   ~ 0
PB5
Text Label 10550 1400 0    60   ~ 0
AREF
NoConn ~ 9400 1600
Text Label 10550 1300 0    60   ~ 0
PC4(an)
Text Label 10550 1200 0    60   ~ 0
PC5(an)
Text Notes 8500 750  0    60   ~ 0
Atmega 328pb Shield \nArduino Footprint Header Pins
$Comp
L Connector_Generic:Conn_01x08 P1
U 1 1 56D70129
P 9600 1900
F 0 "P1" H 9600 2350 50  0000 C CNN
F 1 "Power" V 9700 1900 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 9750 1900 20  0000 C CNN
F 3 "" H 9600 1900 50  0000 C CNN
	1    9600 1900
	1    0    0    -1  
$EndComp
Text Label 8650 1800 0    60   ~ 0
Reset
$Comp
L power:+3.3V #PWR01
U 1 1 56D70538
P 9150 1450
F 0 "#PWR01" H 9150 1300 50  0001 C CNN
F 1 "+3.3V" V 9150 1700 50  0000 C CNN
F 2 "" H 9150 1450 50  0000 C CNN
F 3 "" H 9150 1450 50  0000 C CNN
	1    9150 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 56D707BB
P 9050 1350
F 0 "#PWR02" H 9050 1200 50  0001 C CNN
F 1 "+5V" V 9050 1550 50  0000 C CNN
F 2 "" H 9050 1350 50  0000 C CNN
F 3 "" H 9050 1350 50  0000 C CNN
	1    9050 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 56D70CC2
P 9300 3150
F 0 "#PWR03" H 9300 2900 50  0001 C CNN
F 1 "GND" H 9300 3000 50  0000 C CNN
F 2 "" H 9300 3150 50  0000 C CNN
F 3 "" H 9300 3150 50  0000 C CNN
	1    9300 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 56D70CFF
P 10300 3150
F 0 "#PWR04" H 10300 2900 50  0001 C CNN
F 1 "GND" H 10300 3000 50  0000 C CNN
F 2 "" H 10300 3150 50  0000 C CNN
F 3 "" H 10300 3150 50  0000 C CNN
	1    10300 3150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 P2
U 1 1 56D70DD8
P 9600 2700
F 0 "P2" H 9600 2300 50  0000 C CNN
F 1 "PC Ports" V 9700 2700 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x06" V 9750 2750 20  0000 C CNN
F 3 "" H 9600 2700 50  0000 C CNN
	1    9600 2700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 P4
U 1 1 56D7164F
P 10000 2600
F 0 "P4" H 10000 2100 50  0000 C CNN
F 1 "PD Ports" V 10100 2600 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 10150 2550 20  0000 C CNN
F 3 "" H 10000 2600 50  0000 C CNN
	1    10000 2600
	-1   0    0    -1  
$EndComp
Wire Notes Line
	8525 825  9925 825 
Wire Notes Line
	9925 825  9925 475 
Wire Wire Line
	9350 1450 9350 1700
Wire Wire Line
	9350 1700 9400 1700
Wire Wire Line
	9400 1900 9150 1900
Wire Wire Line
	9400 2000 9050 2000
Wire Wire Line
	9400 2300 8950 2300
Wire Wire Line
	9400 2100 9300 2100
Wire Wire Line
	9400 2200 9300 2200
Connection ~ 9300 2200
Wire Wire Line
	8950 2300 8950 1450
Wire Wire Line
	9050 2000 9050 1350
Wire Wire Line
	9150 1900 9150 1450
Wire Wire Line
	9400 2500 8900 2500
Wire Wire Line
	9400 2600 8900 2600
Wire Wire Line
	9400 2700 8900 2700
Wire Wire Line
	9400 2800 8900 2800
Wire Wire Line
	9400 2900 8900 2900
Wire Wire Line
	9400 3000 8900 3000
$Comp
L Connector_Generic:Conn_01x10 P3
U 1 1 56D721E0
P 10000 1600
F 0 "P3" H 10000 2150 50  0000 C CNN
F 1 "PB Ports" V 10100 1600 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x10" V 10150 1600 20  0000 C CNN
F 3 "" H 10000 1600 50  0000 C CNN
	1    10000 1600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10200 2100 10550 2100
Wire Wire Line
	10200 2000 10550 2000
Wire Wire Line
	10200 1900 10550 1900
Wire Wire Line
	10200 1800 10550 1800
Wire Wire Line
	10200 1700 10550 1700
Wire Wire Line
	10200 1600 10550 1600
Wire Wire Line
	10200 1400 10550 1400
Wire Wire Line
	10200 1300 10550 1300
Wire Wire Line
	10200 1200 10550 1200
Wire Wire Line
	10200 3000 10550 3000
Wire Wire Line
	10200 2900 10550 2900
Wire Wire Line
	10200 2800 10550 2800
Wire Wire Line
	10200 2700 10550 2700
Wire Wire Line
	10200 2600 10550 2600
Wire Wire Line
	10200 2500 10550 2500
Wire Wire Line
	10200 2400 10550 2400
Wire Wire Line
	10200 2300 10550 2300
Wire Wire Line
	10200 1500 10300 1500
Wire Wire Line
	10300 1500 10300 3150
Wire Wire Line
	9300 2100 9300 2200
Wire Wire Line
	9300 2200 9300 3150
Wire Notes Line
	8500 500  8500 3450
Wire Notes Line
	8500 3450 11200 3450
Wire Wire Line
	9400 1800 8650 1800
Text Notes 9700 1600 0    60   ~ 0
1
$Comp
L Device:LED D1
U 1 1 6094035D
P 6750 1600
F 0 "D1" H 6743 1817 50  0000 C CNN
F 1 "LED" H 6743 1726 50  0000 C CNN
F 2 "LED_SMD:LED_1206_3216Metric" H 6750 1600 50  0001 C CNN
F 3 "~" H 6750 1600 50  0001 C CNN
	1    6750 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 60941252
P 6750 2050
F 0 "D2" H 6743 2267 50  0000 C CNN
F 1 "LED" H 6743 2176 50  0000 C CNN
F 2 "LED_SMD:LED_1206_3216Metric" H 6750 2050 50  0001 C CNN
F 3 "~" H 6750 2050 50  0001 C CNN
	1    6750 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 60941B34
P 6350 1850
F 0 "R3" H 6420 1896 50  0000 L CNN
F 1 "200" H 6420 1805 50  0000 L CNN
F 2 "Resistor_SMD:R_2010_5025Metric" V 6280 1850 50  0001 C CNN
F 3 "~" H 6350 1850 50  0001 C CNN
	1    6350 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 60942C71
P 6500 2400
F 0 "R4" H 6570 2446 50  0000 L CNN
F 1 "200" H 6570 2355 50  0000 L CNN
F 2 "Resistor_SMD:R_2010_5025Metric" V 6430 2400 50  0001 C CNN
F 3 "~" H 6500 2400 50  0001 C CNN
	1    6500 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 1600 6350 1600
Wire Wire Line
	6350 1600 6350 1700
Wire Wire Line
	6900 1600 7150 1600
Wire Wire Line
	6900 2050 7150 2050
Wire Wire Line
	6600 2050 6500 2050
Wire Wire Line
	6500 2050 6500 2250
Wire Wire Line
	6350 2000 6350 2600
Wire Wire Line
	6350 2600 6500 2600
Wire Wire Line
	6500 2600 6500 2550
Wire Wire Line
	6350 2600 6350 2700
Connection ~ 6350 2600
$Comp
L power:GND #PWR0101
U 1 1 60948607
P 6350 2700
F 0 "#PWR0101" H 6350 2450 50  0001 C CNN
F 1 "GND" H 6355 2527 50  0000 C CNN
F 2 "" H 6350 2700 50  0001 C CNN
F 3 "" H 6350 2700 50  0001 C CNN
	1    6350 2700
	1    0    0    -1  
$EndComp
Text Label 7150 1600 0    50   ~ 0
PD6
Text Label 7150 2050 0    50   ~ 0
PD5
Text Notes 5950 1250 0    59   ~ 0
PORT D LEDS\nSMD Mounting
$Comp
L Switch:SW_Push SW1
U 1 1 6094B6F4
P 5450 4100
F 0 "SW1" H 5450 4385 50  0000 C CNN
F 1 "SW_Push" H 5450 4294 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_B3U-1000P" H 5450 4300 50  0001 C CNN
F 3 "~" H 5450 4300 50  0001 C CNN
	1    5450 4100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 6094CB40
P 5450 4900
F 0 "SW2" H 5450 5185 50  0000 C CNN
F 1 "SW_Push" H 5450 5094 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_B3U-1000P" H 5450 5100 50  0001 C CNN
F 3 "~" H 5450 5100 50  0001 C CNN
	1    5450 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 4100 5100 4100
Wire Wire Line
	5100 4900 5250 4900
Connection ~ 5100 4900
Wire Wire Line
	5750 4550 5750 4450
Wire Wire Line
	5650 4900 5750 4900
$Comp
L Device:R R1
U 1 1 609524BF
P 5750 4300
F 0 "R1" H 5820 4346 50  0000 L CNN
F 1 "10K" H 5820 4255 50  0000 L CNN
F 2 "Resistor_SMD:R_2010_5025Metric" V 5680 4300 50  0001 C CNN
F 3 "~" H 5750 4300 50  0001 C CNN
	1    5750 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 60953A80
P 5750 5150
F 0 "R2" H 5680 5104 50  0000 R CNN
F 1 "10K" H 5680 5195 50  0000 R CNN
F 2 "Resistor_SMD:R_2010_5025Metric" V 5680 5150 50  0001 C CNN
F 3 "~" H 5750 5150 50  0001 C CNN
	1    5750 5150
	-1   0    0    1   
$EndComp
Wire Wire Line
	5750 4900 5750 5000
Wire Wire Line
	5750 5300 5750 5400
Wire Wire Line
	5100 4900 5100 5400
Wire Wire Line
	5750 4900 6050 4900
Connection ~ 5750 4900
$Comp
L power:GND #PWR0102
U 1 1 6095F88E
P 5750 5400
F 0 "#PWR0102" H 5750 5150 50  0001 C CNN
F 1 "GND" H 5755 5227 50  0000 C CNN
F 2 "" H 5750 5400 50  0001 C CNN
F 3 "" H 5750 5400 50  0001 C CNN
	1    5750 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 6096015B
P 5100 5400
F 0 "#PWR0103" H 5100 5150 50  0001 C CNN
F 1 "GND" H 5105 5227 50  0000 C CNN
F 2 "" H 5100 5400 50  0001 C CNN
F 3 "" H 5100 5400 50  0001 C CNN
	1    5100 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 60960FE6
P 5750 4550
F 0 "#PWR0104" H 5750 4300 50  0001 C CNN
F 1 "GND" H 5755 4377 50  0000 C CNN
F 2 "" H 5750 4550 50  0001 C CNN
F 3 "" H 5750 4550 50  0001 C CNN
	1    5750 4550
	1    0    0    -1  
$EndComp
Text Label 6050 4100 0    50   ~ 0
PD3
Text Label 6050 4900 0    50   ~ 0
PD2
Wire Wire Line
	5650 4100 5750 4100
Wire Wire Line
	5750 4100 5750 4150
Connection ~ 5750 4100
Wire Wire Line
	5750 4100 6050 4100
Wire Wire Line
	5100 4100 5100 4900
$Comp
L Device:R_POT RV1
U 1 1 60974B4E
P 2650 6450
F 0 "RV1" H 2581 6496 50  0000 R CNN
F 1 "10K" H 2581 6405 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296Y_Vertical" H 2650 6450 50  0001 C CNN
F 3 "~" H 2650 6450 50  0001 C CNN
	1    2650 6450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 60977699
P 2650 6850
F 0 "#PWR0105" H 2650 6600 50  0001 C CNN
F 1 "GND" H 2655 6677 50  0000 C CNN
F 2 "" H 2650 6850 50  0001 C CNN
F 3 "" H 2650 6850 50  0001 C CNN
	1    2650 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 6450 3150 6450
Wire Wire Line
	2650 6600 2650 6850
$Comp
L power:+5V #PWR0107
U 1 1 6098259A
P 2650 6050
F 0 "#PWR0107" H 2650 5900 50  0001 C CNN
F 1 "+5V" V 2650 6250 50  0000 C CNN
F 2 "" H 2650 6050 50  0000 C CNN
F 3 "" H 2650 6050 50  0000 C CNN
	1    2650 6050
	1    0    0    -1  
$EndComp
Text Label 3150 6450 0    50   ~ 0
PC0
Text Notes 1200 5700 0    59   ~ 0
PORTC 10K Potentiometer\nw/ Capacitor Filter Circuit
Text Notes 4650 3600 0    59   ~ 0
PORT D Push Buttons\nw/ internal pull-up
$Comp
L Connector_Generic:Conn_01x03 P10
U 1 1 60943075
P 9050 5200
F 0 "P10" H 8968 4785 50  0000 C CNN
F 1 "LM34/35" H 8968 4876 50  0000 C CNN
F 2 "Connector_PinSocket_2.00mm:PinSocket_1x03_P2.00mm_Vertical" H 8968 4967 50  0000 C CNN
F 3 "~" H 9050 5200 50  0001 C CNN
	1    9050 5200
	-1   0    0    1   
$EndComp
Wire Wire Line
	9250 5100 9500 5100
Wire Wire Line
	9250 5200 9500 5200
Wire Wire Line
	9250 5300 9400 5300
Wire Wire Line
	9400 5300 9400 5400
Text Label 9500 5200 0    50   ~ 0
PC1
$Comp
L power:GND #PWR0108
U 1 1 6094A4F2
P 9400 5400
F 0 "#PWR0108" H 9400 5150 50  0001 C CNN
F 1 "GND" H 9400 5250 50  0000 C CNN
F 2 "" H 9400 5400 50  0000 C CNN
F 3 "" H 9400 5400 50  0000 C CNN
	1    9400 5400
	1    0    0    -1  
$EndComp
Text Notes 7900 4400 0    59   ~ 0
LM34/35 Temp Sensor\nFemale Header Pin Connections
$Comp
L Connector_Generic:Conn_01x08 P9
U 1 1 60955C31
P 1800 4350
F 0 "P9" H 1800 3850 50  0000 C CNN
F 1 "SPI / i2C" V 1900 4350 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 1950 4300 20  0000 C CNN
F 3 "" H 1800 4350 50  0000 C CNN
	1    1800 4350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2000 3950 2200 3950
Wire Wire Line
	2000 4050 2200 4050
Wire Wire Line
	2000 4150 2200 4150
Wire Wire Line
	2000 4250 2200 4250
Wire Wire Line
	2000 4350 2200 4350
Wire Wire Line
	2000 4450 2200 4450
Wire Wire Line
	2000 4550 2200 4550
Wire Wire Line
	2000 4650 2100 4650
Wire Wire Line
	2100 4650 2100 4750
$Comp
L power:GND #PWR0109
U 1 1 6096B1F7
P 2100 4750
F 0 "#PWR0109" H 2100 4500 50  0001 C CNN
F 1 "GND" H 2100 4600 50  0000 C CNN
F 2 "" H 2100 4750 50  0000 C CNN
F 3 "" H 2100 4750 50  0000 C CNN
	1    2100 4750
	1    0    0    -1  
$EndComp
Text Label 2200 3950 0    50   ~ 0
Vcc
Text Label 2200 4050 0    50   ~ 0
PB2
Text Label 2200 4150 0    50   ~ 0
PB3
Text Label 2200 4250 0    50   ~ 0
PB4
Text Label 2200 4350 0    50   ~ 0
PB5
Text Label 2200 4550 0    50   ~ 0
PC4
Text Label 2200 4450 0    50   ~ 0
PC5
Text Notes 1200 3600 0    59   ~ 0
ICM - 20948 Sensor\nSPI / i2C Female Header Pin Connections
$Comp
L Connector_Generic:Conn_01x08 P11
U 1 1 60977356
P 2350 2200
F 0 "P11" H 2350 1700 50  0000 C CNN
F 1 "Motor Driver Port 1" V 2450 2200 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 2500 2150 20  0000 C CNN
F 3 "" H 2350 2200 50  0000 C CNN
	1    2350 2200
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x08 P12
U 1 1 60978488
P 2950 2200
F 0 "P12" H 2950 1700 50  0000 C CNN
F 1 "Motor Driver Port 2" V 3050 2200 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 3100 2150 20  0000 C CNN
F 3 "" H 2950 2200 50  0000 C CNN
	1    2950 2200
	-1   0    0    1   
$EndComp
Wire Wire Line
	3150 1800 3350 1800
Wire Wire Line
	3150 1900 3350 1900
Wire Wire Line
	3150 2400 3350 2400
Wire Wire Line
	3150 2500 3350 2500
Wire Wire Line
	2150 1800 1900 1800
Wire Wire Line
	2150 1900 1900 1900
Wire Wire Line
	2150 2000 1900 2000
Wire Wire Line
	2150 2100 1900 2100
Wire Wire Line
	2150 2200 1900 2200
Wire Wire Line
	2150 2300 1900 2300
Wire Wire Line
	2150 2400 1900 2400
Wire Wire Line
	2150 2500 1900 2500
Wire Wire Line
	3150 2000 3700 2000
Wire Wire Line
	3150 2100 3700 2100
Wire Wire Line
	3150 2200 3700 2200
Wire Wire Line
	3150 2300 3700 2300
NoConn ~ 3350 2400
NoConn ~ 3350 2500
NoConn ~ 1900 2400
NoConn ~ 1900 2500
NoConn ~ 1900 1900
$Comp
L power:GND #PWR0110
U 1 1 60A1573E
P 1900 1800
F 0 "#PWR0110" H 1900 1550 50  0001 C CNN
F 1 "GND" V 1905 1672 50  0000 R CNN
F 2 "" H 1900 1800 50  0001 C CNN
F 3 "" H 1900 1800 50  0001 C CNN
	1    1900 1800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 60A19C5C
P 3350 1800
F 0 "#PWR0111" H 3350 1550 50  0001 C CNN
F 1 "GND" V 3355 1672 50  0000 R CNN
F 2 "" H 3350 1800 50  0001 C CNN
F 3 "" H 3350 1800 50  0001 C CNN
	1    3350 1800
	0    -1   -1   0   
$EndComp
Text Label 3350 1900 0    50   ~ 0
Vcc
Text Label 1900 2000 2    50   ~ 0
PB1
Text Label 1900 2100 2    50   ~ 0
PC2
Text Label 1900 2200 2    50   ~ 0
PC3
Text Label 1900 2300 2    50   ~ 0
PD0
Text Notes 2450 1200 2    59   ~ 0
DRV8833 Dual Motor Driver\nFemale Header Connections
Text Label 9500 5100 0    50   ~ 0
Vcc
Connection ~ 2650 6250
Wire Wire Line
	2650 6250 2650 6050
Wire Wire Line
	2650 6300 2650 6250
Wire Wire Line
	2050 6650 2050 6850
Wire Wire Line
	2050 6250 2050 6350
Wire Wire Line
	2650 6250 2050 6250
$Comp
L power:GND #PWR0106
U 1 1 6097CCAF
P 2050 6850
F 0 "#PWR0106" H 2050 6600 50  0001 C CNN
F 1 "GND" H 2055 6677 50  0000 C CNN
F 2 "" H 2050 6850 50  0001 C CNN
F 3 "" H 2050 6850 50  0001 C CNN
	1    2050 6850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 6097B77A
P 2050 6500
F 0 "C1" H 2165 6546 50  0000 L CNN
F 1 "0.1uF" H 2165 6455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2088 6350 50  0001 C CNN
F 3 "~" H 2050 6500 50  0001 C CNN
	1    2050 6500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 60A2ECC8
P 3900 2000
F 0 "J1" H 3980 1992 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 3980 1901 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-3-2-5.08_1x02_P5.08mm_Horizontal" H 3900 2000 50  0001 C CNN
F 3 "~" H 3900 2000 50  0001 C CNN
	1    3900 2000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 60A2F114
P 3900 2200
F 0 "J2" H 3980 2192 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 3980 2101 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-3-2-5.08_1x02_P5.08mm_Horizontal" H 3900 2200 50  0001 C CNN
F 3 "~" H 3900 2200 50  0001 C CNN
	1    3900 2200
	1    0    0    -1  
$EndComp
$EndSCHEMATC
