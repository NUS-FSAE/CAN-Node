#include "mcc_generated_files/mcc.h"

uCAN_MSG canMessage;
bool send = false;
uint8_t data = 0;
    
void transmit(unsigned long id);

void updateData() {
    INTERRUPT_GlobalInterruptDisable();
    INTERRUPT_PeripheralInterruptDisable();
    data = (data+1)%127;
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
}

void time_to_send() {
    INTERRUPT_GlobalInterruptDisable();
    INTERRUPT_PeripheralInterruptDisable();
    send = true;
}

void main(void)
{

    // Initialize the device
    SYSTEM_Initialize();
    CIOCONbits.CLKSEL = 1;
    CIOCONbits.ENDRHI = 1;
    
    RXB0CONbits.RXM0 = 1;
    RXB0CONbits.RXM1 = 0;
    RXB0CONbits.RB0DBEN = 0;
    RXB0CONbits.FILHIT0 = 0;
    
    TMR0_SetInterruptHandler(&updateData);
    TMR1_SetInterruptHandler(&time_to_send);

    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    while (1) {
        if(send) {
            transmit(0x640);
            transmit(0x642);
            transmit(0x641);
            send = false;
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
        }
    }
}

void transmit(unsigned long id) {
        canMessage.frame.data0 = data;
        canMessage.frame.data1 = data;
        canMessage.frame.data2 = data;
        canMessage.frame.data3 = data;
        canMessage.frame.data4 = data;
        canMessage.frame.data5 = data;
        canMessage.frame.data6 = data;
        canMessage.frame.data7 = data;
        canMessage.frame.id = id;
        canMessage.frame.dlc = 8;
        canMessage.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
        CAN_transmit(&canMessage);
}
/**
 End of File
*/