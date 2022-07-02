#include "BMX055.h"
#include "mbed.h"
#include "stdio.h"

BMX055::BMX055(PinName SDA, PinName SCL) : bmx055(SDA,SCL){
    bmx055.frequency(freq);
    Setup();
}

void BMX055::Setup(){
    char buf[2];

    //accel setting
    wait_us(2000);
    for (int i = 0; i < 3; i++){
        buf[0] = setup_accl[2*i];
        buf[1] = setup_accl[2*i+1];
        bmx055.write(add_accl,buf,2);
    }
    wait_us(2000);

    //gyroscope setting
    for (int i = 0; i < 3; i++){
        buf[0] = setup_gyro[2*i];
        buf[1] = setup_gyro[2*i+1];
        bmx055.write(add_gyro,buf,2);
    }
    wait_us(2000);


    //magnet setting
    for (int i = 0; i < 6; i++){
        buf[0] = setup_mag[2*i];
        buf[1] = setup_mag[2*i+1];
        bmx055.write(add_mag,buf,2);
    }
    wait_us(2000);
}

void BMX055::get_accl(){
    uint8_t data[6] = {0};
    char send[1];
    send[0] = (char)2;
    bmx055.write(add_accl, send, 1, true);
    bmx055.read(add_accl, (char*)data, 6);

    for (int i = 0; i < 3; i++){
        accl[i] = (int16_t) (((int16_t)data[2*i+1] << 8) | data[2*i]) >> 4;
        if(accl[i] > 2047) accl[i] -= 4096;
    }
}

void BMX055::get_gyro(){
    int data[6] = {0};
    char send[1], get[1];

    for (int i = 0; i < 6; i++){
        send[0] = (char)2+i;
        bmx055.write(add_gyro, send, 1);
        bmx055.read(add_gyro, get, 1);
        data[i] = get[0];
    }

    for (int i = 0; i < 3; i++){
        gyro[i] = (int16_t) (((int16_t)data[2*i+1] <<8) | data[2*i]) >> 4;
        if (gyro[i] >32767) gyro[i] -= 65536;
    }
}

void BMX055::get_mag(){
    int data[8] = {0};
    char send[1],get[1];
    char temp;

    for (int i = 0; i < 8; i++){
        send[0] = (char)(0x42+i);
        bmx055.write(add_mag, send, 1);
        bmx055.read(add_mag, get, 1);
        temp = get[0];
        data[i] = temp;
    }

    for (int i = 0; i < 3; i++){
        if (i != 2) mag[i] = (uint16_t) (((uint16_t)data[2*i+1] << 8) | data[2*i]) >> 3;
        else mag[i] = (uint16_t) (((uint16_t)data[2*i+1] << 8) | data[2*i]) >> 1;
        if (i == 2 && mag[i] > 16383) mag[i] -= 32768;
        else if (i != 2 && mag[i] > 4095) mag[i] -= 8092;
    }
}

void BMX055::fig_show(){
    get_accl();
    get_gyro();
    get_mag();
    printf("------accel------\n");
    printf("x:%g,y:%g,z:%g\n",accl[0],accl[1],accl[2]);
    printf("----gyroscope----\n");
    printf("x:%g,y:%g,z:%g\n",gyro[0],gyro[1],gyro[2]);
    printf("------magnet-----\n");
    printf("x:%g,y:%g,z:%g\n",mag[0],mag[1],mag[2]);
    wait_us(500000);
    
    
}