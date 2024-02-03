#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;
const int motor_1a = 2, motor_1b = 3, motor_2a = 4, motor_2b = 5;
char receive[32];
unsigned long last = 0;

void setup()
{
  driver.init();
  pinMode(motor_1a, OUTPUT);
  pinMode(motor_1b, OUTPUT);
  pinMode(motor_2a, OUTPUT);
  pinMode(motor_2b, OUTPUT);
}

void loop()
{
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen))
  {
    last = millis();
    memset(receive, 0, sizeof(receive));
    for (int i = 0; i < buflen; i++) {
      receive[i] = buf[i];
    }
    if (strcmp(receive, "forward") == 0) {
      forward();
    }
    else if (strcmp(receive, "reverse") == 0) {
      reverse();
    }
    else if (strcmp(receive, "forward_left") == 0) {
      forward_left();
    }
    else if (strcmp(receive, "forward_right") == 0) {
      forward_right();
    }
    else if (strcmp(receive, "reverse_left") == 0) {
      reverse_left();
    }
    else if (strcmp(receive, "reverse_right") == 0) {
      reverse_right();
    }
  }
  if ((millis() - last) > 300) {
    brake();
  }
}

void forward() {
  digitalWrite(motor_1a, HIGH);
  digitalWrite(motor_1b, LOW);
  digitalWrite(motor_2a, HIGH);
  digitalWrite(motor_2b, LOW);
}
void reverse() {
  digitalWrite(motor_1a, LOW);
  digitalWrite(motor_1b, HIGH);
  digitalWrite(motor_2a, LOW);
  digitalWrite(motor_2b, HIGH);
}
void forward_left() {
  digitalWrite(motor_1a, LOW);
  digitalWrite(motor_1b, LOW);
  digitalWrite(motor_2a, HIGH);
  digitalWrite(motor_2b, LOW);
}
void forward_right() {
  digitalWrite(motor_1a, HIGH);
  digitalWrite(motor_1b, LOW);
  digitalWrite(motor_2a, LOW);
  digitalWrite(motor_2b, LOW);
}
void reverse_left() {
  digitalWrite(motor_1a, LOW);
  digitalWrite(motor_1b, LOW);
  digitalWrite(motor_2a, LOW);
  digitalWrite(motor_2b, HIGH);
}
void reverse_right() {
  digitalWrite(motor_1a, LOW);
  digitalWrite(motor_1b, HIGH);
  digitalWrite(motor_2a, LOW);
  digitalWrite(motor_2b, LOW);
}
void brake() {
  digitalWrite(motor_1a, LOW);
  digitalWrite(motor_1b, LOW);
  digitalWrite(motor_2a, LOW);
  digitalWrite(motor_2b, LOW);
}
