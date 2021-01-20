#include "main.h"
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

void init(void);

void main(void) {
    uint8_t com_flg = 0;
    bool o1_stand_flag = false;
    bool o2_stand_flag = false;
    bool o3_stand_flag = false;
    bool o4_stand_flag = false;
    bool o1_status = false;
    bool o2_status = false;
    bool o3_status = false;
    bool o4_status = false;
    bool o1_recent_status = false;
    bool o2_recent_status = false;
    bool o3_recent_status = false;
    bool o4_recent_status = false;
    uint32_t o1_error_count = 0;
    uint32_t o2_error_count = 0;
    uint32_t o3_error_count = 0;
    uint32_t o4_error_count = 0;

    init();

    while(true){

        if(I2C_ReceiveCheck()){
            if (com_flg == 0) com_flg = 1;
            if((rcv_data[0] & 0b10000000) >> 7 == 1){
                snd_data[0] |= 0b10000000;
                o1_stand_flag = true;
                o2_stand_flag = true;
                o3_stand_flag = true;
                o4_stand_flag = true;
            }else{
                snd_data[0] &= 0b01111111;
                o1_stand_flag = false;
                o2_stand_flag = false;
                o3_stand_flag = false;
                o4_stand_flag = false;
            }
            CLRWDT();
        }
        else if (com_flg == 0){
            CLRWDT();
        }

        if(o1_stand_flag){
            O1_LED = 1;
            O1_OUT = 1;
            o1_status = true;
        }
        if(!o1_stand_flag && O1_S_1 == 0){
            O1_LED = 0;
            O1_OUT = 0;
            O1_LED = 0;
            O1_OUT = 0;
            o1_status = false;
        }
        if(o1_recent_status != o1_status){
            o1_error_count = 0;
        }
        if(o1_status){
            if(O1_S_3 == 1){
                o1_error_count++;
            }else{
                o1_error_count = 0;
            }
        }else{
            if(O1_S_2 == 1){
                o1_error_count++;
            }else{
                o1_error_count = 0;
            }
        }
        if(o1_error_count >= ERROR_TIME_COUNT){
            //error_handle
        }
        o1_recent_status = o1_status;

        if(o2_stand_flag){
            O2_LED = 1;
            O2_OUT = 1;
            o2_status = true;
        }
        if(!o2_stand_flag && O2_S_1 == 0){
            O2_LED = 0;
            O2_OUT = 0;
            O2_LED = 0;
            O2_OUT = 0;
            o2_status = false;
        }
        if(o2_recent_status != o2_status){
            o2_error_count = 0;
        }
        if(o2_status){
            if(O2_S_3 == 1){
                o2_error_count++;
            }else{
                o2_error_count = 0;
            }
        }else{
            if(O2_S_2 == 1){
                o2_error_count++;
            }else{
                o2_error_count = 0;
            }
        }
        if(o2_error_count >= ERROR_TIME_COUNT){
            //error_handle
        }
        o2_recent_status = o2_status;

        if(o3_stand_flag){
            O3_LED = 1;
            O3_OUT = 1;
            o3_status = true;
        }
        if(!o3_stand_flag && O3_S_1 == 0){
            O3_LED = 0;
            O3_OUT = 0;
            O3_LED = 0;
            O3_OUT = 0;
            o3_status = false;
        }
        if(o3_recent_status != o3_status){
            o3_error_count = 0;
        }
        if(o3_status){
            if(O3_S_3 == 1){
                o3_error_count++;
            }else{
                o3_error_count = 0;
            }
        }else{
            if(O3_S_2 == 1){
                o3_error_count++;
            }else{
                o3_error_count = 0;
            }
        }
        if(o3_error_count >= ERROR_TIME_COUNT){
            //error_handle
        }
        o3_recent_status = o3_status;

        if(o4_stand_flag){
            O4_LED = 1;
            O4_OUT = 1;
            o4_status = true;
        }
        if(!o4_stand_flag && O4_S_1 == 0){
            O4_LED = 0;
            O4_OUT = 0;
            O4_LED = 0;
            O4_OUT = 0;
            o4_status = false;
        }
        if(o4_recent_status != o4_status){
            o4_error_count = 0;
        }
        if(o4_status){
            if(O4_S_3 == 1){
                o4_error_count++;
            }else{
                o4_error_count = 0;
            }
        }else{
            if(O4_S_2 == 1){
                o4_error_count++;
            }else{
                o4_error_count = 0;
            }
        }
        if(o4_error_count >= ERROR_TIME_COUNT){
            //error_handle
        }
        o4_recent_status = o4_status;
    }
}

void init(void){
    uint8_t addr = 0x10;

    // Set oscilation
    OSCCON = 0xF0; //PLL　Enable

    // Set pin mode
    ANSELA = 0x00;
    ANSELB = 0x00;
  
    TRISA = 0xFF;
    TRISB = 0x00;
    WPUB = 0x00;
    TRISCbits.TRISC0 = 1;
    TRISCbits.TRISC1 = 1;
    TRISCbits.TRISC2 = 1;
    TRISCbits.TRISC5 = 1;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;

    O1_LED = 0;
    O1_OUT = 0;
    O2_LED = 0;
    O2_OUT = 0;
    O3_LED = 0;
    O3_OUT = 0;
    O4_LED = 0;
    O4_OUT = 0;

    // Set watch dog
    WDTCON = 0x13;

    I2C_init(addr);//アドレス
}

void interrupt  HAND(void){
    Slave_Interrupt();
}
