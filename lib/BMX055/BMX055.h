#ifndef BMX055_h
#define BMX055_h
#include "mbed.h"

class BMX055{
    private:
    const float freq = 100000;
	static constexpr uint8_t add_accl = 0x19;
	static constexpr uint8_t add_gyro = 0x69;
	static constexpr uint8_t add_mag  = 0x13;

    char setup_accl[6] = {
        0x0F,0x03,
        0x10,0x08,
        0x11,0x00
    };

    char setup_gyro[6] = {
        0x0F,0x04,
        0x10,0x07,
        0x11,0x00
    };

    char setup_mag[13] = {
        0x4B,0x83,
        0x4B,0x01,
        0x4C,0x00,
        0x4E,0x84,
        0x51,0x04,
        0x52,0x16
    };

	I2C bmx055;
	void Setup();
    
    public:
	BMX055(PinName SDA,PinName SCL);
	std::array<float,3> accl;
	std::array<float,3> gyro;
	std::array<float,3> mag;
	void get_accl();
	void get_gyro();
	void get_mag();
    void fig_show();

};

#endif
