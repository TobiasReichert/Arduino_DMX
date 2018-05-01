#include <DmxSimple.h>

/**
 * Radio
 */
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(7,8);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
const int max_payload_size = 32;
char receive_payload[max_payload_size+1];



#define cycle_time 50

static int tasterPin = 4;
static int motionPin = 5;

int state = 1; // s_on = s_on

#define s_red_to_green 1
#define s_green_to_blue 2
#define s_blue_to_red 3
int color_state = s_red_to_green;
int r = 255;
int g = 0;
int b = 0;
float master = 1.0;
bool blink = true;

void setup() {
  Serial.begin(38400); 
  Serial.println("--- Start Serial Monitor ---");
  
  DmxSimple.usePin(3);
  DmxSimple.maxChannel(255);

  pinMode(tasterPin, INPUT_PULLUP);
  pinMode(motionPin, INPUT);

  radio.begin();
  radio.enableDynamicPayloads();
  radio.setRetries(5,15);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();

}

void loop() {

  /**
   * statemachine
   */
  statemachine();
  
  /**
   * Radio
   */
  if(radio.available()){
    // Fetch the payload, and see if this was the last one.
    uint8_t len = radio.getDynamicPayloadSize();
    
    // If a corrupt dynamic payload is received, it will be flushed
    if(radio.getDynamicPayloadSize() < 1){
      goto radio_error; 
    }
    
    radio.read( receive_payload, len );
 
    // Put a zero at the end for easy printing
    receive_payload[len] = 0;
    Serial.println(String(receive_payload));
    if(String("DMXon").equals(String(receive_payload))){
      state = 1;
    }else if(String("DMXoff").equals(String(receive_payload))){
      state = 0;
    }
  }
radio_error:

  /**
   * next color
   */
  if(color_state == s_red_to_green){
    r--;
    g++;
    if(r == 0){
      color_state = s_green_to_blue;
    }
  } else if(color_state == s_green_to_blue){
    g--;
    b++;
    if(g == 0){
      color_state = s_blue_to_red;
    }
  } else if(color_state == s_blue_to_red){
    b--;
    r++;
    if(b == 0){
      color_state = s_red_to_green;
    }
  }


  dmx_set();

  delay(cycle_time);

}
