#ifndef SBUS_H
#define SBUS_H
#include "mbed.h"
#include "stm32f303x8.h"


class SbusRx{
    private:
    static constexpr uint32_t baud_rate = 100000;
    static constexpr int8_t buf_len = 25;
    static constexpr int8_t buf_ch_num = 16;
    static constexpr uint8_t header = 0x0F;
    static constexpr uint8_t footer = 0x00;
    static constexpr uint8_t Lost_Frame_Mask = 0x04;
    static constexpr uint8_t Ch_17_Mask = 0x01;
    static constexpr uint8_t ch_18_Mask = 0x02;
    static constexpr uint8_t Failsafe_Mask = 0x08;

    int8_t state = 0;
    uint8_t buf_[buf_len];
    uint8_t prev_byte = footer;
    uint8_t cur_byte;
    bool new_data;
    std::array<int16_t,buf_ch_num> ch_;
    bool failsafe_ = false, lost_frame_ = false, ch17_ = false, ch18_ = false;
    bool Parse();

    public:
    SbusRx();
    void Setup();
    bool Read();
    static constexpr int8_t num_ch() {return buf_ch_num;};
    inline std::array<int16_t,buf_ch_num> ch() const {return ch_;}
    inline bool failsafe() const {return failsafe_;}
    inline bool lost_frame() const{return lost_frame_;}
    inline bool ch17() const {return ch17_;}
    inline bool ch18() const {return ch18_;}

};

class SbusTx{
    private:
    static constexpr uint32_t baud_rate = 100000;
    static constexpr int8_t buf_len = 25;
    static constexpr int8_t buf_ch_num = 16;
    static constexpr uint8_t header = 0x0F;
    static constexpr uint8_t footer = 0x00;
    static constexpr uint8_t Lost_Frame_Mask = 0x04;
    static constexpr uint8_t Ch_17_Mask = 0x01;
    static constexpr uint8_t ch_18_Mask = 0x02;
    static constexpr uint8_t Failsafe_Mask = 0x08;

    uint8_t buf_[buf_len];
    std::array<int16_t,buf_ch_num> ch_;
    bool failsafe_ = false, lost_frame_ = false, ch17_ = false, ch18_ = false;
    
    public:
    UART_HandleTypeDef huart;
    SbusTx();
    void Setup(UART_HandleTypeDef huart_);

    void Write();
    static constexpr int8_t num_ch() {return buf_ch_num;}
    inline void failsafe(const bool val) {failsafe_=val;}
    inline void lost_frame(const bool val) {lost_frame_=val;}
    inline void ch17(const bool val) {ch17_=val;}
    inline void ch18(const bool val) {ch18_=val;}
    inline void ch(const std::array<int16_t,buf_ch_num> &cmd) {ch_=cmd;}
    inline std::array<int16_t,buf_ch_num> ch() const {return ch_;}
    inline bool failsafe() const {return failsafe_;}
    inline bool lost_frame() const {return lost_frame_;}
    inline bool ch17() const {return ch17_;}
    inline bool ch18() const {return ch18_;}
};


#endif