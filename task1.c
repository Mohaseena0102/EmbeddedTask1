#include <LPC214x.h> // Include header file for LPC2148 (ARM7)

#define LED0 (1<<10) // P0.10
#define LED1 (1<<11) // P0.11
#define LED2 (1<<12) // P0.12

void led_init() {
  PINSEL0 &= ~(0x3 << 20); // Configure P0.10 as GPIO
  PINSEL0 &= ~(0x3 << 22); // Configure P0.11 as GPIO
  PINSEL0 &= ~(0x3 << 24); // Configure P0.12 as GPIO
  IODIR0 |= (LED0 | LED1 | LED2); // Set LEDs as output
}

void led_on(int led_no) {
  if (led_no == 0) IOSET0 = LED0;
  else if (led_no == 1) IOSET0 = LED1;
  else if (led_no == 2) IOSET0 = LED2;
}

void led_off(int led_no) {
  if (led_no == 0) IOCLR0 = LED0;
  else if (led_no == 1) IOCLR0 = LED1;
  else if (led_no == 2) IOCLR0 = LED2;
}

void delay_ms(int ms) {
  int i, j;
  for (i = 0; i < ms; i++) {
    for (j = 0; j < 12000; j++);
  }
}

void sos_signal() {
  // SOS Morse Code: ...---...
  led_on(0); delay_ms(100); led_off(0); delay_ms(100);
  led_on(0); delay_ms(100); led_off(0); delay_ms(100);
  led_on(0); delay_ms(100); led_off(0); delay_ms(300);
  led_on(0); delay_ms(300); led_off(0); delay_ms(300);
  led_on(0); delay_ms(300); led_off(0); delay_ms(300);
  led_on(0); delay_ms(100); led_off(0); delay_ms(100);
  led_on(0); delay_ms(100); led_off(0); delay_ms(100);
  led_on(0); delay_ms(100); led_off(0);
}

void binary_counter() {
  int i, j;
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 3; j++) {
      if ((i >> j) & 1) {
        if (j == 0) led_on(0);
        else if (j == 1) led_on(1);
        else if (j == 2) led_on(2);
      } else {
        if (j == 0) led_off(0);
        else if (j == 1) led_off(1);
        else if (j == 2) led_off(2);
      }
    }
    delay_ms(500);
  }
}

void night_rider_effect() {
  int i;
  for (i = 0; i < 3; i++) {
    if (i == 0) { led_on(0); delay_ms(100); led_off(0); }
    else if (i == 1) { led_on(1); delay_ms(100); led_off(1); }
    else if (i == 2) { led_on(2); delay_ms(100); led_off(2); }
  }
  for (i = 2; i >= 0; i--) {
    if (i == 0) { led_on(0); delay_ms(100); led_off(0); }
    else if (i == 1) { led_on(1); delay_ms(100); led_off(1); }
    else if (i == 2) { led_on(2); delay_ms(100); led_off(2); }
  }
}

int main() {
  led_init();
  while (1) {
    sos_signal();
    delay_ms(1000);
    binary_counter();
    delay_ms(1000);
    night_rider_effect();
    delay_ms(1000);
  }
//  return 0;
}
