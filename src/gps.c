/*
 * gps.c
 *
 *  Created on: Apr 18, 2017
 *      Author: Ryan Domres
 */

#include "stm32f10x.h"
#include "main.h"
#include "gps.h"

void initGPS() {
	/* USART1 Peripheral clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1, ENABLE);

	/* Enable the USART1 Pin's Software Remapping */
	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

	/* Configure USART1 Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPS_RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPS_PORT, &GPIO_InitStructure);

	/* Configure USART1 Tx as alternate function push pull */
	GPIO_InitStructure.GPIO_Pin = GPS_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPS_PORT, &GPIO_InitStructure);

	/* USART1 configuration ------------------------------------------------------*/
	/* USART1 configured as follow:
		- BaudRate = 9600 baud
		- Word Length = 8 Bits
		- One Stop Bit
		- No parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USART1 */
	USART_Init(GPS_USART, &USART_InitStructure);

	/* Enable USART1 */
	USART_Cmd(GPS_USART, ENABLE);

//	configureGPS(settingsArray);
}

void getGPS() {
	uint8_t c[6];
	uint8_t done = 0;
	while (!done) { // Search for $GNGGA sentence
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
		if (USART_ReceiveData(USART1) == '$') {
			while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
			if (USART_ReceiveData(USART1) == 'G') {
				while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
				if (USART_ReceiveData(USART1) == 'N') {
					while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
					if (USART_ReceiveData(USART1) == 'G') {
						while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
						if (USART_ReceiveData(USART1) == 'G') {
							while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
							if (USART_ReceiveData(USART1) == 'A') {
								done = 1;
							}
						}
					}
				}
			}
		}
//		while (USART_ReceiveData(USART1) != '$');
//		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
//		c[0] = USART_ReceiveData(USART1);
////		USART_SendData(USART2, c[0]);
//		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
//		c[1] = USART_ReceiveData(USART1);
////		USART_SendData(USART2, c[1]);
//		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
//		c[2] = USART_ReceiveData(USART1);
////		USART_SendData(USART2, c[2]);
//		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
//		c[3] = USART_ReceiveData(USART1);
////		USART_SendData(USART2, c[3]);
//		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
//		c[4] = USART_ReceiveData(USART1);
//		//USART_SendData(USART2, c[4]);
//		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
//		c[5] = USART_ReceiveData(USART1);
//		//USART_SendData(USART2, c[5]);
//		if ((c[5] == 'A') && (c[4] == 'G') && (c[3] == 'G')) {
//			break; // GGA sentence match
//		}
	}
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	c[0] = USART_ReceiveData(USART1); // Discard comma
	gpsTime = 0;
	for (uint8_t i = 0; i < 6; i++) {
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
		gpsTime *= 10;
		c[0] = USART_ReceiveData(USART1);
		gpsTime += (c[0] - 48);
//		USART_SendData(USART2, c[0]);
	}
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	c[0] = USART_ReceiveData(USART1); // Discard decimal
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	c[0] = USART_ReceiveData(USART1); // Discard zero
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	c[0] = USART_ReceiveData(USART1); // Discard zero
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	c[0] = USART_ReceiveData(USART1); // Discard comma
	gpsLat = 0;
	for (uint8_t i = 0; i < 9; i++) {
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
		c[0] = USART_ReceiveData(USART1);
		if (i != 4) {
			gpsLat *= 10;
			gpsLat += (c[0] - 48);
//			USART_SendData(USART2, c[0]);
		}
	}
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	c[0] = USART_ReceiveData(USART1); // Discard final digit of Latitude
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	c[0] = USART_ReceiveData(USART1); // Discard comma
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	c[0] = USART_ReceiveData(USART1); // Discard N/S indicator
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	c[0] = USART_ReceiveData(USART1); // Discard comma
	gpsLong = 0;
	for (uint8_t i = 0; i < 10; i++) {
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
		c[0] = USART_ReceiveData(USART1);
		if (i != 5) {
			gpsLong *= 10;
			gpsLong += (c[0] - 48);
//			USART_SendData(USART2, c[0]);
		}
	}
}

//void configureGPS(uint8_t *settingsArrayPointer) {
//	uint8_t gpsSetSuccess = 0;
////	Serial.println("Configuring u-Blox GPS initial state...");
//
//	//Generate the configuration string for Navigation Mode
//	uint8_t setNav[] = {0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, *settingsArrayPointer, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA, 0x00, 0x64, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//	calcChecksum(&setNav[2], sizeof(setNav) - 4);
//
//	//Generate the configuration string for Data Rate
//	uint8_t setDataRate[] = {0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, settingsArrayPointer[1], settingsArrayPointer[2], 0x01, 0x00, 0x01, 0x00, 0x00, 0x00};
//	calcChecksum(&setDataRate[2], sizeof(setDataRate) - 4);
//
//	//Generate the configuration string for Baud Rate
//	uint8_t setPortRate[] = {0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, settingsArrayPointer[3], settingsArrayPointer[4], settingsArrayPointer[5], 0x00, 0x07, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//	calcChecksum(&setPortRate[2], sizeof(setPortRate) - 4);
//
//	uint8_t setGLL[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x2B};
//	uint8_t setGSA[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x32};
//	uint8_t setGSV[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x39};
//	uint8_t setRMC[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x40};
//	uint8_t setVTG[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x46};
//
//	delay(2500);
//
//	while(gpsSetSuccess < 3)
//	{
////		Serial.print("Setting Navigation Mode... ");
//		sendUBX(&setNav[0], sizeof(setNav));  //Send UBX Packet
//		gpsSetSuccess += 10; //Passes Class ID and Message ID to the ACK Receive function
//		if (gpsSetSuccess == 5) {
//			gpsSetSuccess -= 4;
//			delay(1500);
//			uint8_t lowerPortRate[] = {0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x80, 0x25, 0x00, 0x00, 0x07, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA2, 0xB5};
//			sendUBX(lowerPortRate, sizeof(lowerPortRate));
//			delay(2000);
//		}
//		if(gpsSetSuccess == 6) gpsSetSuccess -= 4;
//		if (gpsSetSuccess == 10) gpsStatus[0] = 1;
//	}
////  if (gpsSetSuccess == 3) Serial.println("Navigation mode configuration failed.");
//  gpsSetSuccess = 0;
//  while(gpsSetSuccess < 3) {
////    Serial.print("Setting Data Update Rate... ");
//    sendUBX(&setDataRate[0], sizeof(setDataRate));  //Send UBX Packet
//    gpsSetSuccess += 10; //Passes Class ID and Message ID to the ACK Receive function
//    if (gpsSetSuccess == 10) gpsStatus[1] = 1;
//    if (gpsSetSuccess == 5 | gpsSetSuccess == 6) gpsSetSuccess -= 4;
//  }
////  if (gpsSetSuccess == 3) Serial.println("Data update mode configuration failed.");
//  gpsSetSuccess = 0;
//
//
//  while(gpsSetSuccess < 3 && settingsArrayPointer[6] == 0x00) {
////    Serial.print("Deactivating NMEA GLL Messages ");
//    sendUBX(setGLL, sizeof(setGLL));
//    gpsSetSuccess += 10;
//    if (gpsSetSuccess == 10) gpsStatus[2] = 1;
//    if (gpsSetSuccess == 5 | gpsSetSuccess == 6) gpsSetSuccess -= 4;
//  }
////  if (gpsSetSuccess == 3) Serial.println("NMEA GLL Message Deactivation Failed!");
//  gpsSetSuccess = 0;
//
//  while(gpsSetSuccess < 3 && settingsArrayPointer[7] == 0x00) {
////    Serial.print("Deactivating NMEA GSA Messages ");
//    sendUBX(setGSA, sizeof(setGSA));
//    gpsSetSuccess += 10;
//    if (gpsSetSuccess == 10) gpsStatus[3] = 1;
//    if (gpsSetSuccess == 5 | gpsSetSuccess == 6) gpsSetSuccess -= 4;
//  }
////  if (gpsSetSuccess == 3) Serial.println("NMEA GSA Message Deactivation Failed!");
//  gpsSetSuccess = 0;
//
//  while(gpsSetSuccess < 3 && settingsArrayPointer[8] == 0x00) {
////    Serial.print("Deactivating NMEA GSV Messages ");
//    sendUBX(setGSV, sizeof(setGSV));
//    gpsSetSuccess += 10;
//    if (gpsSetSuccess == 10) gpsStatus[4] = 1;
//    if (gpsSetSuccess == 5 | gpsSetSuccess == 6) gpsSetSuccess -= 4;
//  }
////  if (gpsSetSuccess == 3) Serial.println("NMEA GSV Message Deactivation Failed!");
//  gpsSetSuccess = 0;
//
//  while(gpsSetSuccess < 3 && settingsArrayPointer[9] == 0x00) {
////    Serial.print("Deactivating NMEA RMC Messages ");
//    sendUBX(setRMC, sizeof(setRMC));
//    gpsSetSuccess += 10;
//    if (gpsSetSuccess == 10) gpsStatus[5] = 1;
//    if (gpsSetSuccess == 5 | gpsSetSuccess == 6) gpsSetSuccess -= 4;
//  }
////  if (gpsSetSuccess == 3) Serial.println("NMEA RMC Message Deactivation Failed!");
//  gpsSetSuccess = 0;
//
//  while(gpsSetSuccess < 3 && settingsArrayPointer[10] == 0x00) {
////    Serial.print("Deactivating NMEA VTG Messages ");
//    sendUBX(setVTG, sizeof(setVTG));
//    gpsSetSuccess += 10;
//    if (gpsSetSuccess == 10) gpsStatus[6] = 1;
//    if (gpsSetSuccess == 5 | gpsSetSuccess == 6) gpsSetSuccess -= 4;
//  }
////  if (gpsSetSuccess == 3) Serial.println("NMEA VTG Message Deactivation Failed!");
//
//  gpsSetSuccess = 0;
//  if (settingsArrayPointer[4] != 0x25) {
////    Serial.print("Setting Port Baud Rate... ");
//    sendUBX(&setPortRate[0], sizeof(setPortRate));
////    Serial.println("Success!");
//    delay(500);
//  }
//}

void sendUBX(uint8_t *UBXmsg, uint8_t msgLength) {
	for(int i = 0; i < msgLength; i++) {
		USART_SendData(GPS_USART, UBXmsg[i]);
		delay(2400);
	}
	USART_SendData(GPS_USART, 0x0A);
	delay(2400);
	USART_SendData(GPS_USART, 0x0D);
	delay(2400);
}

void calcChecksum(uint8_t *checksumPayload, uint8_t payloadSize) {
	uint8_t CK_A = 0, CK_B = 0;
	for (int i = 0; i < payloadSize ;i++) {
		CK_A = CK_A + *checksumPayload;
		CK_B = CK_B + CK_A;
		checksumPayload++;
	}
	*checksumPayload = CK_A;
	checksumPayload++;
	*checksumPayload = CK_B;
}
