#include "sbus.h"
#include "mbed.h"
static UnbufferedSerial serial(PA_9,PA_10);

void SbusRx::Setup(){
    serial.baud(baud_rate);
    serial.format(
        8,
        SerialBase::Even,
        2
    );
}

bool SbusRx::Read(){
    new_data = false;

    do{
        if (Parse()){
            new_data = true;
        }
    }while (serial.readable());

    if (new_data){
        ch_[0]  = static_cast<int16_t>(buf_[1]       | buf_[2]  << 8 & 0x07FF);
        ch_[1]  = static_cast<int16_t>(buf_[2]  >> 3 | buf_[3]  << 5 & 0x07FF);
        ch_[2]  = static_cast<int16_t>(buf_[3]  >> 6 | buf_[4]  << 2  |
                                       buf_[5] << 10 & 0x07FF);
        ch_[3]  = static_cast<int16_t>(buf_[5]  >> 1 | buf_[6]  << 7 & 0x07FF);
        ch_[4]  = static_cast<int16_t>(buf_[6]  >> 4 | buf_[7]  << 4 & 0x07FF);
        ch_[5]  = static_cast<int16_t>(buf_[7]  >> 7 | buf_[8]  << 1  |
                                       buf_[9] << 9 & 0x07FF);
        ch_[6]  = static_cast<int16_t>(buf_[9]  >> 2 | buf_[10] << 6 & 0x07FF);
        ch_[7]  = static_cast<int16_t>(buf_[10] >> 5 | buf_[11] << 3 & 0x07FF);
        ch_[8]  = static_cast<int16_t>(buf_[12]      | buf_[13] << 8 & 0x07FF);
        ch_[9]  = static_cast<int16_t>(buf_[13] >> 3 | buf_[14] << 5 & 0x07FF);
        ch_[10] = static_cast<int16_t>(buf_[14] >> 6 | buf_[15] << 2  |
                                       buf_[16] << 10 & 0x07FF);
        ch_[11] = static_cast<int16_t>(buf_[16] >> 1 | buf_[17] << 7 & 0x07FF);
        ch_[12] = static_cast<int16_t>(buf_[17] >> 4 | buf_[18] << 4 & 0x07FF);
        ch_[13] = static_cast<int16_t>(buf_[18] >> 7 | buf_[19] << 1  |
                                       buf_[20] << 9 & 0x07FF);
        ch_[14] = static_cast<int16_t>(buf_[20] >> 2 | buf_[21] << 6 & 0x07FF);
        ch_[15] = static_cast<int16_t>(buf_[21] >> 5 | buf_[22] << 3 & 0x07FF);
    
        ch17_ = buf_[23] & Ch_17_Mask;
    
        ch18_ = buf_[23] & ch_18_Mask;
    
        lost_frame_ = buf_[23] & Lost_Frame_Mask;
    
        failsafe_ = buf_[23] & Failsafe_Mask;

    }
    return new_data;
}

bool SbusRx::Parse(){
    char c;
    while (serial.readable()){
        cur_byte = serial.read(&c,1);
        if (state == 0){
            if ((cur_byte == header) && ((prev_byte == footer) || ((prev_byte & 0x0F) == Lost_Frame_Mask))){
                buf_[state++] = cur_byte;
            }else{
                state = 0;
            }
        }else{
            state = 0;
            if ((buf_[buf_len - 1] == footer) || ((buf_[buf_len - 1] & 0x0F) == Lost_Frame_Mask)){
                return true;
            }else{
                return false;
            }
        }
        prev_byte = cur_byte;
    }
    return false;
}

