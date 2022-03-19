#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "pico/platform.h"

void initGPIO(uint gpio, bool out);

int main() {
    const uint trigPin = 27;
    const uint echoPin = 26;
    const uint led = 25;
    int width;
    const int timeout = 24000;

    stdio_init_all();

	gpio_init(trigPin);
	gpio_set_dir(trigPin, GPIO_OUT);
	gpio_put(trigPin, GPIO_IN);

    initGPIO(echoPin, GPIO_IN);
    initGPIO(led, GPIO_OUT);

    absolute_time_t startTime;
    absolute_time_t endTime;
    long difference;
    uint tiktok = 0;
    while(true){
        if(tiktok & 1){
            printf("- \n");
        }else{
            printf(" -\n");
        }
        tiktok++;
        sleep_us(2);
        gpio_put(trigPin, GPIO_OUT);
        sleep_us(10);
        gpio_put(trigPin, GPIO_IN);

        width = 0;
        while(gpio_get(echoPin) == 0){
            sleep_us(1);
            
            width++;
            if (width > timeout){
                break;
            }
        }
        startTime = get_absolute_time();

        width = 0;
        while(gpio_get(echoPin) == 1){
            sleep_us(1);
            
            width++;
            if (width > timeout){
                break;
            }
        }
        endTime = get_absolute_time();

        difference = (long)absolute_time_diff_us(startTime, endTime) * 0.0343 / 2;

        printf("%ld cm \n", difference);

        sleep_us(timeout);
    }
    

    return 0;
}

void initGPIO(uint gpio, bool out) {
	gpio_init(gpio);

	gpio_set_dir(gpio, out);

	gpio_put(gpio, out);
}
