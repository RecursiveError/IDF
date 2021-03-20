#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

unsigned long int c;

#define D1 27
#define D2 26
#define D3 25
#define D4 33


void send(int value);
void Dispwrite(int disp, int value);
void DispUpdate();

static int V1, V2, V3, V4, disp;

const int portas[] = {23, 22, 21, 19, 18,5, 4, 2}; 
//simbolos pre-definidos para o disĺay
const int values[] = {0xd7, 0x11, 0XCD, 0X5D, 0X1B, 0X5E, 0XDE, 0X15, 0XDF, 0x5f, 0X9F, 0XDA,
0XC6, 0XD9, 0XCE, 0xC2 };
void app_main() {
    for(int i = 0; i<8; i++){    
    gpio_set_direction(portas[i], GPIO_MODE_DEF_OUTPUT);
    }
    gpio_set_direction(D1, GPIO_MODE_DEF_OUTPUT);
    gpio_set_direction(D2, GPIO_MODE_DEF_OUTPUT);
    gpio_set_direction(D3, GPIO_MODE_DEF_OUTPUT);
    gpio_set_direction(D4, GPIO_MODE_DEF_OUTPUT);
    for(;;){
        Dispwrite(1, (c/100)%10);
        Dispwrite(2, 0);
        Dispwrite(3, 15);
        Dispwrite(4, 10);
        DispUpdate();
        c++;
       for(unsigned long int i = 0; i<100000; i++);
    }
}




void Dispwrite(int dips, int value){
    switch(dips){
        case 1: V1 = value; break;
        case 2: V2 = value; break;
        case 3: V3 = value; break;
        case 4: V4 = value; break;

    };

}

void send(int value){
    for(int i = 0; i < 8; i++){
        if((value & (1 << i))){
            gpio_set_level(portas[i], 1);
        }else{
            gpio_set_level(portas[i], 0);
        }
    }
}

void DispUpdate(){
    gpio_set_level(D1, 0);
    gpio_set_level(D2, 0);
    gpio_set_level(D3, 0);
    gpio_set_level(D4, 0);

    switch(disp){
        case 0:
        send(values[V1]);
        gpio_set_level(D1, 1);
        disp = 1;
        break;

        case 1:
        send(values[V2]);
        gpio_set_level(D2, 1);
        disp = 2;
        break;

        case 2:
        send(values[V3]);
        gpio_set_level(D3, 1);
        disp = 3;
        break;

        case 3:
        send(values[V4]);
        gpio_set_level(D4, 1);
        disp = 0;
        break;

        default:
        disp = 0;
        break;
    };

}