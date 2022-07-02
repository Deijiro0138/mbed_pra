#include <mbed.h>
#include <sbus.h>

SbusRx sbus_rx;
std::array<int16_t,sbus_rx.num_ch()> sbus_data;


int main() {
  sbus_rx.Setup();
  while(1) {
    if (sbus_rx.Read()){
      sbus_data = sbus_rx.ch();

      for (int8_t i = 0; i < 16; i++){
        printf("%d",sbus_data[i]);
      }
      printf("%d",sbus_rx.lost_frame());
      printf("%d",sbus_rx.failsafe());
    }
    wait_us(500000);
  }
}