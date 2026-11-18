#include <Audio.h>   // only here to confirm the Audio Library is installed
#include <unistd.h>

#define POT1 A0
#define POT2 A1
#define POT3 A2
#define BUFFER_SIZE 8

int buffer[BUFFER_SIZE] = {0};
int buffer_index = 0;
int buffer_sum = 0;
float buffer_avg = 0;

void printb(int val){
  uint32_t mask = 0b10000000000000000000000000000000;
  for (int i = 0 ; i < 32 ; i ++){
    Serial.printf("%s", ((mask >> i) & val) ? "1" : "0");
  }
  Serial.printf("\n");
}

void setup() {
  pinMode(POT1, INPUT);
  pinMode(POT2, INPUT);
  pinMode(POT3, INPUT);
  Serial.begin(115200);           // USB serial; the baud rate is ignored
}

void loop() {
  //Read and store
  int t = analogRead(POT1);
  int diff = t - buffer[buffer_index];
  buffer_sum += diff;
  buffer_avg = buffer_sum / (float)BUFFER_SIZE;
  buffer[buffer_index] = t;
  buffer_index++;
  buffer_index = (buffer_index >= BUFFER_SIZE) ? 0 : buffer_index;
  Serial.printf("%.3f\n", buffer_avg);
  delay(10);

  tone(10, buffer_avg * 2);
}