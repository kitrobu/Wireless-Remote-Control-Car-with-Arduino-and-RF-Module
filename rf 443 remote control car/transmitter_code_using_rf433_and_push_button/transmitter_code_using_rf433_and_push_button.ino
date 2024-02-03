#include <RH_ASK.h>
#include <SPI.h>

const int forward_switch = 2, reverse_switch = 3, left_switch = 4, right_switch = 5;
int state = 0;
char *msg;
RH_ASK driver;

void setup()
{
  driver.init();
  pinMode(forward_switch, INPUT);
  pinMode(reverse_switch, INPUT);
  pinMode(left_switch, INPUT);
  pinMode(right_switch, INPUT);
}

void loop()
{
  while (digitalRead(forward_switch) == HIGH && digitalRead(left_switch) == LOW
         && digitalRead(right_switch) == LOW) {
    msg = "forward";
    transmit(msg);
  }
  while (digitalRead(reverse_switch) == HIGH  && digitalRead(left_switch) == LOW
         && digitalRead(right_switch) == LOW) {
    msg = "reverse";
    transmit(msg);
  }
  while (digitalRead(forward_switch) == HIGH && digitalRead(left_switch) == HIGH) {
    msg = "forward_left";
    transmit(msg);
  }
  while (digitalRead(forward_switch) == HIGH && digitalRead(right_switch) == HIGH) {
    msg = "forward_right";
    transmit(msg);
  }
  while (digitalRead(reverse_switch) == HIGH && digitalRead(left_switch) == HIGH) {
    msg = "reverse_left";
    transmit(msg);
  }
  while (digitalRead(reverse_switch) == HIGH && digitalRead(right_switch) == HIGH) {
    msg = "reverse_right";
    transmit(msg);
  }
}
void transmit(char* msg) {
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  delay(100);
}
