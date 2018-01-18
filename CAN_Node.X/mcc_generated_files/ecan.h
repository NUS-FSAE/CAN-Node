/**
  ECAN Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    ecan.h

  @Summary
    This is the generated header file for the ECAN driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs 

  @Description
    This header file provides APIs for driver for ECAN.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs  - 1.45
        Device            :  PIC18F25K80
        Driver Version    :  1.00
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

#ifndef _ECAN_H
#define _ECAN_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**

Global Defines  

*/
typedef union {

    struct {
        unsigned char idType;
        unsigned long id;
        unsigned char dlc;
        unsigned char data0;
        unsigned char data1;
        unsigned char data2;
        unsigned char data3;
        unsigned char data4;
        unsigned char data5;
        unsigned char data6;
        unsigned char data7;
    } frame;
    unsigned char array[14];
} uCAN_MSG;

/**
 Defines
*/

#define dSTANDARD_CAN_MSG_ID_2_0B 1
#define dEXTENDED_CAN_MSG_ID_2_0B 2

/**
  Section: ECAN APIs
*/

/**
    @Summary
        Initializes the ECAN module. 

    @Description
        This routine sets all the set parameters to the ECAN module.

    @Preconditions 
        None

    @Param
        None
  
    @Returns
        None
 
    @Example
        <code>
        ECAN_Initialize();  
        </code>                                                                      
*/
void ECAN_Initialize(void);
/**
                                                                           
    @Summary
        CAN_sleep

    @Description
        Puts the CAN module to sleep

    @Param
        None 

    @Returns
        None   

    @Example
        <code>
        CAN_init();  
        </code> 
                                                                           
*/

void CAN_sleep(void);

/**
    @Summary
        CAN_transmit

    @Description
        Transmits out sCAN_MSG

    @Param
        Pointer to a sCAN_MSG

    @Returns
        True or False if message was loaded to transmit buffer 

    @Example
        <code>
        uCAN_MSG txMessage;
        CAN_transmit(&txMessage);  
        </code>                                                                             
*/
unsigned char CAN_transmit(uCAN_MSG *tempCanMsg);


/**

	@Summary
		CAN_receive

	@Description
		Receives CAN messages

	@Param
		Pointer to a sCAN_MSG

	@Returns
		True or False for a new message 
  
	@Example
		<code>
		uCAN_MSG rxMessage;
		CAN_receive(&rxMessage);  
		</code> 
                                                                             
*/
unsigned char CAN_receive(uCAN_MSG *tempCanMsg);

/**
 
	@Summary
		CAN_messagesInBuffer
 
	@Description
		Checks to see how many messages are in the buffer
	
	@Param
		None

	@Returns
		Returns total number of messages in the buffers

	@Example
		<code>
		unsigned char nrMsg;
		nrMsg = CAN_messagesInBuffer();  
		</code>                                                                            
*/
unsigned char CAN_messagesInBuffer(void);

/**

	@Summary
		CAN_isBusOff

	@Description
		Checks to see if module is busoff

	@Param
		None

	@Returns
		True if module is in Busoff, False is if it is not

	@Example
		<code>
		unsigned char busOff;
		busOff = CAN_isBusOff();  
		</code> 
                                                  
*/

unsigned char CAN_isBusOff(void);

/**

	@Summary
		CAN_isRXErrorPassive

	@Description
		Checks to see if module is RX Error Passive
        
	@Param
		None
 
	@Returns
 		True if module is in RX Error Passive, False is if it is not                                                    

 	@Example
		<code>
		unsigned char errRxPasive;
		errRxPasive = CAN_isRXErrorPassive();
		</code>     
                                                    
 */
 
unsigned char CAN_isRXErrorPassive(void);

/**

	@Summary
		CAN_isTXErrorPassive

	@Description
		Checks to see if module is TX Error Passive

	@Param
		None

	@Returns
		True if module is in TX Error Passive, False is if it is not

	@Example
		<code>
		unsigned char errTxPasive;
		errTxPasive = CAN_isTXErrorPassive();  
		</code>       

*/

unsigned char CAN_isTXErrorPassive(void);


#ifdef __cplusplus  // Provide C++ Compatibility
    }
#endif

#endif // _ECAN_H
/**
 End of File
*/

