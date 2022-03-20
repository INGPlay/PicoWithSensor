 #include <stdio.h>
 #include "pico/stdlib.h"
 #include "hardware/adc.h"

void initGPIO(uint gpio, bool dirOut, bool putOut);
void initADC(uint gpio, uint adc);

int main() {
    const uint a0 = 26;
    const uint led = 25;

    stdio_init_all();
    adc_init();

    initGPIO(led, GPIO_OUT, GPIO_OUT);
    initADC(26, 0);

    const uint delay = 100; // 1s delay

    uint16_t result;
    while(true) {
        result = adc_read();
        printf("%d \n", result);
        sleep_ms(delay);
    }

    return 0;
}

void initGPIO(uint gpio, bool dirOut, bool putOut) {
	gpio_init(gpio);

	gpio_set_dir(gpio, dirOut);

	gpio_put(gpio, putOut);
}

void initADC(uint gpio, uint adc) {
    adc_gpio_init(gpio);
    adc_select_input(adc);
}