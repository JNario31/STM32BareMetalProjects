#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "adxl345.h"
#include "print.h"

int16_t accel_x, accel_y, accel_z;
double accel_x_g, accel_y_g, accel_z_g;

uint8_t data_buffer[6];

int main(void)
{
    uart_init();

    adxl_init();

    uint8_t dev;
    adxl_read(ADXL345_REG_DEVID, &dev);
    printf_uart("DEVID = %u\r\n", dev);


    while(1)
    {
        //Read accelerometer data
        adxl_read(ADXL345_REG_DATA_START, data_buffer);

        //Combine high and low bytes to form accelerometer data
        accel_x = (int16_t)((data_buffer[1] << 8) | data_buffer[0]);
        accel_y = (int16_t)((data_buffer[3] << 8) | data_buffer[2]);
        accel_z = (int16_t)((data_buffer[5] << 8) | data_buffer[4]);

        // Convert raw data to g values
        // accel_x_g = accel_x * 0.0078;
        // accel_y_g = accel_y * 0.0078;
        // accel_z_g = accel_z * 0.0078;
        
        printf_uart("accel_x: %d  accel_y: %d  accel_z: %d\r\n",
            accel_x, accel_y, accel_z);

        //printf_uart("Sensor Value: \r\n");
       // printf_uart("accel_x : %d accel_y : %d accel_z : %d\r\n",accel_x,accel_y,accel_z);
    }
}



