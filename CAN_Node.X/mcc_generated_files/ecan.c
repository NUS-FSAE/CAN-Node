/**
  ECAN Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ecan.c

  @Summary
    This is the generated driver implementation file for the ECAN driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs 

  @Description
    This source file provides APIs for ECAN.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs  - 1.45
        Device            :  PIC18F25K80
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "ecan.h"

/**
    Local Functions
*/  
unsigned long convertReg2ExtendedCANid(unsigned char tempRXBn_EIDH, unsigned char tempRXBn_EIDL, unsigned char tempRXBn_SIDH, unsigned char tempRXBn_SIDL);
unsigned long convertReg2StandardCANid(unsigned char tempRXBn_SIDH, unsigned char tempRXBn_SIDL);
void convertCANid2Reg(unsigned long tempPassedInID, unsigned char canIdType, unsigned char *passedInEIDH, unsigned char *passedInEIDL, unsigned char *passedInSIDH, unsigned char *passedInSIDL);




void ECAN_Initialize(void)
{
    CANCON = 0x80;
    while (0x80 != (CANSTAT & 0xE0)); // wait until ECAN is in config mode
    
    /**
    Mode 0
    */
    ECANCON = 0x00;

/**
Mask and Filter definitions
........................................................
CAN ID		Mask		Filter		Buffer
........................................................
0x640		Acceptance Mask 0		Filter 0	RXB0
........................................................
*/
    
/**    
    Initialize Receive Masks
*/    

    RXM0EIDH = 0xFF;
    RXM0EIDL = 0xFF;
    RXM0SIDH = 0xFF;
    RXM0SIDL = 0xFF;

    RXM1EIDH = 0xFF;
    RXM1EIDL = 0xFF;
    RXM1SIDH = 0xFF;
    RXM1SIDL = 0xFF;
    
    /**
    Initialize Receive Filters
    */   

    RXF0EIDH = 0x00;
    RXF0EIDL = 0x00;
    RXF0SIDH = 0xC8;
    RXF0SIDL = 0x00;

    RXF1EIDH = 0x00;
    RXF1EIDL = 0x00;
    RXF1SIDH = 0x00;
    RXF1SIDL = 0x00;

    RXF2EIDH = 0x00;
    RXF2EIDL = 0x00;
    RXF2SIDH = 0x00;
    RXF2SIDL = 0x00;

    RXF3EIDH = 0x00;
    RXF3EIDL = 0x00;
    RXF3SIDH = 0x00;
    RXF3SIDL = 0x00;

    RXF4EIDH = 0x00;
    RXF4EIDL = 0x00;
    RXF4SIDH = 0x00;
    RXF4SIDL = 0x00;

    RXF5EIDH = 0x00; 
    RXF5EIDL = 0x00;
    RXF5SIDH = 0x00;
    RXF5SIDL = 0x00;

    /**
    Initialize CAN Timings
    */

	/**
	Baud rate: 1Mbps
	System frequency: 16000000 Hz
	Time quanta: 8
	Sample point: 1-1-4-2
	Sample point: 75.00%
	*/

    
    BRGCON1 = 0x00; 
    BRGCON2 = 0x98;
    BRGCON3 = 0x01;   
    
    CANCON = 0x00;
    while (0x00 != (CANSTAT & 0xE0)); // wait until ECAN is in Normal mode
    

}
/**
  Section: ECAN APIs
*/

void CAN_sleep(void) {

    PIR5bits.WAKIF = 0; // clear CAN bus wakeup interrupt
    PIE5bits.WAKIE = 1; // Enable CAN bus activity wakeup
    CANCON = 0x20; // request disable mode
    while ((CANSTAT & 0xE0) != 0x20); // wait until ECAN is in disable mode   
    //Wake up from sleep should set the CAN module straight into Normal mode
}

unsigned char CAN_transmit(uCAN_MSG *tempCanMsg) {
    unsigned char tempEIDH = 0;
    unsigned char tempEIDL = 0;
    unsigned char tempSIDH = 0;
    unsigned char tempSIDL = 0;

    unsigned char returnValue = 0;

    if (TXB0CONbits.TXREQ != 1) {

        convertCANid2Reg(tempCanMsg->frame.id, tempCanMsg->frame.idType, &tempEIDH, &tempEIDL, &tempSIDH, &tempSIDL);

        TXB0EIDH = tempEIDH;
        TXB0EIDL = tempEIDL;
        TXB0SIDH = tempSIDH;
        TXB0SIDL = tempSIDL;
        TXB0DLC = tempCanMsg->frame.dlc;
        TXB0D0 = tempCanMsg->frame.data0;
        TXB0D1 = tempCanMsg->frame.data1;
        TXB0D2 = tempCanMsg->frame.data2;
        TXB0D3 = tempCanMsg->frame.data3;
        TXB0D4 = tempCanMsg->frame.data4;
        TXB0D5 = tempCanMsg->frame.data5;
        TXB0D6 = tempCanMsg->frame.data6;
        TXB0D7 = tempCanMsg->frame.data7;

        TXB0CONbits.TXREQ = 1; //Set the buffer to transmit		
        returnValue = 1;
    } else if (TXB1CONbits.TXREQ != 1) {

        convertCANid2Reg(tempCanMsg->frame.id, tempCanMsg->frame.idType, &tempEIDH, &tempEIDL, &tempSIDH, &tempSIDL);

        TXB1EIDH = tempEIDH;
        TXB1EIDL = tempEIDL;
        TXB1SIDH = tempSIDH;
        TXB1SIDL = tempSIDL;
        TXB1DLC = tempCanMsg->frame.dlc;
        TXB1D0 = tempCanMsg->frame.data0;
        TXB1D1 = tempCanMsg->frame.data1;
        TXB1D2 = tempCanMsg->frame.data2;
        TXB1D3 = tempCanMsg->frame.data3;
        TXB1D4 = tempCanMsg->frame.data4;
        TXB1D5 = tempCanMsg->frame.data5;
        TXB1D6 = tempCanMsg->frame.data6;
        TXB1D7 = tempCanMsg->frame.data7;

        TXB1CONbits.TXREQ = 1; //Set the buffer to transmit		
        returnValue = 1;
    } else if (TXB2CONbits.TXREQ != 1) {

        convertCANid2Reg(tempCanMsg->frame.id, tempCanMsg->frame.idType, &tempEIDH, &tempEIDL, &tempSIDH, &tempSIDL);

        TXB2EIDH = tempEIDH;
        TXB2EIDL = tempEIDL;
        TXB2SIDH = tempSIDH;
        TXB2SIDL = tempSIDL;
        TXB2DLC = tempCanMsg->frame.dlc;
        TXB2D0 = tempCanMsg->frame.data0;
        TXB2D1 = tempCanMsg->frame.data1;
        TXB2D2 = tempCanMsg->frame.data2;
        TXB2D3 = tempCanMsg->frame.data3;
        TXB2D4 = tempCanMsg->frame.data4;
        TXB2D5 = tempCanMsg->frame.data5;
        TXB2D6 = tempCanMsg->frame.data6;
        TXB2D7 = tempCanMsg->frame.data7;

        TXB2CONbits.TXREQ = 1; //Set the buffer to transmit		
        returnValue = 1;
    }


    ///////////////////////////////////	
    return (returnValue);
}

unsigned char CAN_receive(uCAN_MSG *tempCanMsg) {
    unsigned char returnValue = 0;

    //check to see if we received a CAN message
//    if (PIR5bits.RXB1IF == 1)
    {

        //check which buffer the CAN message is in
        if (RXB0CONbits.RXFUL != 0) //CheckRXB0
        {
            if ((RXB0SIDL & 0x08) == 0x08) //If Extended Message
            {
                //message is extended
                tempCanMsg->frame.idType = (unsigned char) dEXTENDED_CAN_MSG_ID_2_0B;
                tempCanMsg->frame.id = convertReg2ExtendedCANid(RXB0EIDH, RXB0EIDL, RXB0SIDH, RXB0SIDL);
            } else {
                //message is standard
                tempCanMsg->frame.idType = (unsigned char) dSTANDARD_CAN_MSG_ID_2_0B;
                tempCanMsg->frame.id = convertReg2StandardCANid(RXB0SIDH, RXB0SIDL);
            }

            tempCanMsg->frame.dlc = RXB0DLC;
            tempCanMsg->frame.data0 = RXB0D0;
            tempCanMsg->frame.data1 = RXB0D1;
            tempCanMsg->frame.data2 = RXB0D2;
            tempCanMsg->frame.data3 = RXB0D3;
            tempCanMsg->frame.data4 = RXB0D4;
            tempCanMsg->frame.data5 = RXB0D5;
            tempCanMsg->frame.data6 = RXB0D6;
            tempCanMsg->frame.data7 = RXB0D7;
            RXB0CONbits.RXFUL = 0;
            returnValue = 1;
        } else if (RXB1CONbits.RXFUL != 0) //CheckRXB1
        {
            if ((RXB1SIDL & 0x08) == 0x08) //If Extended Message
            {
                //message is extended
                tempCanMsg->frame.idType = (unsigned char) dEXTENDED_CAN_MSG_ID_2_0B;
                tempCanMsg->frame.id = convertReg2ExtendedCANid(RXB1EIDH, RXB1EIDL, RXB1SIDH, RXB1SIDL);
            }
			else
			{
                //message is standard
                tempCanMsg->frame.idType = (unsigned char) dSTANDARD_CAN_MSG_ID_2_0B;
                tempCanMsg->frame.id = convertReg2StandardCANid(RXB1SIDH, RXB1SIDL);
            }

            tempCanMsg->frame.dlc = RXB1DLC;
            tempCanMsg->frame.data0 = RXB1D0;
            tempCanMsg->frame.data1 = RXB1D1;
            tempCanMsg->frame.data2 = RXB1D2;
            tempCanMsg->frame.data3 = RXB1D3;
            tempCanMsg->frame.data4 = RXB1D4;
            tempCanMsg->frame.data5 = RXB1D5;
            tempCanMsg->frame.data6 = RXB1D6;
            tempCanMsg->frame.data7 = RXB1D7;
            RXB1CONbits.RXFUL = 0;
            returnValue = 1;
        }


        PIR5bits.RXB1IF = 0;    
    }


    return (returnValue);
}

unsigned char CAN_messagesInBuffer(void) {
    unsigned char messageCount = 0;
    if (RXB0CONbits.RXFUL != 0) //CheckRXB0
    {
        messageCount++;
    }
    if (RXB1CONbits.RXFUL != 0) //CheckRXB1
    {
        messageCount++;
    }

    return (messageCount);
}

unsigned char CAN_isBusOff(void) {
    unsigned char returnValue = 0;

    //COMSTAT bit 5 TXBO: Transmitter Bus-Off bit
    //1 = Transmit error counter > 255
    //0 = Transmit error counter less then or equal to 255

    if (COMSTATbits.TXBO == 1) {
        returnValue = 1;
    }
    return (returnValue);
}

unsigned char CAN_isRXErrorPassive(void) {
    unsigned char returnValue = 0;

    //COMSTAT bit 3 RXBP: Receiver Bus Passive bit
    //1 = Receive error counter > 127
    //0 = Receive error counter less then or equal to 127

    if (COMSTATbits.RXBP == 1) {
        returnValue = 1;
    }
    return (returnValue);
}

unsigned char CAN_isTXErrorPassive(void) {
    unsigned char returnValue = 0;

    //COMSTAT bit 4 TXBP: Transmitter Bus Passive bit
    //1 = Transmit error counter > 127
    //0 = Transmit error counter less then or equal to 127

    if (COMSTATbits.TXBP == 1) {
        returnValue = 1;
    }
    return (returnValue);
}

/**
Internal functions
*/


unsigned long convertReg2ExtendedCANid(unsigned char tempRXBn_EIDH, unsigned char tempRXBn_EIDL, unsigned char tempRXBn_SIDH, unsigned char tempRXBn_SIDL) {
    unsigned long returnValue = 0;
    unsigned long ConvertedID = 0;
    unsigned char CAN_standardLo_ID_lo2bits;
    unsigned char CAN_standardLo_ID_hi3bits;

    CAN_standardLo_ID_lo2bits = (tempRXBn_SIDL & 0x03);
    CAN_standardLo_ID_hi3bits = (tempRXBn_SIDL >> 5);
    ConvertedID = (tempRXBn_SIDH << 3);
    ConvertedID = ConvertedID + CAN_standardLo_ID_hi3bits;
    ConvertedID = (ConvertedID << 2);
    ConvertedID = ConvertedID + CAN_standardLo_ID_lo2bits;
    ConvertedID = (ConvertedID << 8);
    ConvertedID = ConvertedID + tempRXBn_EIDH;
    ConvertedID = (ConvertedID << 8);
    ConvertedID = ConvertedID + tempRXBn_EIDL;
    returnValue = ConvertedID;    
    return (returnValue);
}

unsigned long convertReg2StandardCANid(unsigned char tempRXBn_SIDH, unsigned char tempRXBn_SIDL) {
    unsigned long returnValue = 0;
    unsigned long ConvertedID;
    //if standard message (11 bits)
    //EIDH = 0 + EIDL = 0 + SIDH + upper three bits SIDL (3rd bit needs to be clear)
    //1111 1111 111
    ConvertedID = (tempRXBn_SIDH << 3);
    ConvertedID = ConvertedID + (tempRXBn_SIDL >> 5);
    returnValue = ConvertedID;
    return (returnValue);
}

void convertCANid2Reg(unsigned long tempPassedInID, unsigned char canIdType, unsigned char *passedInEIDH, unsigned char *passedInEIDL, unsigned char *passedInSIDH, unsigned char *passedInSIDL) {
    unsigned char wipSIDL = 0;

    if (canIdType == dEXTENDED_CAN_MSG_ID_2_0B) {

        //EIDL
        *passedInEIDL = 0xFF & tempPassedInID; //CAN_extendedLo_ID_TX1 = &HFF And CAN_UserEnter_ID_TX1
        tempPassedInID = tempPassedInID >> 8; //CAN_UserEnter_ID_TX1 = CAN_UserEnter_ID_TX1 >> 8

        //EIDH
        *passedInEIDH = 0xFF & tempPassedInID; //CAN_extendedHi_ID_TX1 = &HFF And CAN_UserEnter_ID_TX1
        tempPassedInID = tempPassedInID >> 8; //CAN_UserEnter_ID_TX1 = CAN_UserEnter_ID_TX1 >> 8

        //SIDL
        //push back 5 and or it
        wipSIDL = 0x03 & tempPassedInID;
        tempPassedInID = tempPassedInID << 3; //CAN_UserEnter_ID_TX1 = CAN_UserEnter_ID_TX1 << 3
        wipSIDL = (0xE0 & tempPassedInID) + wipSIDL;
        wipSIDL = wipSIDL + 0x08; // TEMP_CAN_standardLo_ID_TX1 = TEMP_CAN_standardLo_ID_TX1 + &H8
        *passedInSIDL = 0xEB & wipSIDL; //CAN_standardLo_ID_TX1 = &HEB And TEMP_CAN_standardLo_ID_TX1

        //SIDH
        tempPassedInID = tempPassedInID >> 8;
        *passedInSIDH = 0xFF & tempPassedInID;
    } else //(canIdType == dSTANDARD_CAN_MSG_ID_2_0B)
    {
        *passedInEIDH = 0;
        *passedInEIDL = 0;
        tempPassedInID = tempPassedInID << 5;
        *passedInSIDL = 0xFF & tempPassedInID;
        tempPassedInID = tempPassedInID >> 8;
        *passedInSIDH = 0xFF & tempPassedInID;
    }
}





/**
 End of File
*/ 



