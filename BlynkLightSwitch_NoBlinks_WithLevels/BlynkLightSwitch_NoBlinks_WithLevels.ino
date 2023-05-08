#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN1        D8 // On Trinket or Gemma, suggest changing this to 1

#define NUMPIXELS 24 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels1(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS, D6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(NUMPIXELS, D3, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS, D8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIXELS, D6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUMPIXELS, D3, NEO_GRB + NEO_KHZ800);

#define BLYNK_TEMPLATE_ID "TMPL68y7Hm2yy"
#define BLYNK_TEMPLATE_NAME "ESP8266"
#define BLYNK_AUTH_TOKEN "p6ULOx8KvVCTCsObCfdZ1yyqufArBAPn"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define EspSerial Serial1

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Hotspot:
char ssid[] = "Milab2";
char pass[] = "12345678";

unsigned long elapsedTime = 0;
unsigned long startTime = 0;
int duration = 0;
int matrices = 1;

int pinValue = 0;
BLYNK_WRITE(V0)
{
  pinValue = param.asInt(); 
  if (pinValue == 1){
    matrices = 1;
    startTime = millis();
    elapsedTime = startTime;
  }   
}

int interval = 0;
BLYNK_WRITE(V1)
{
  interval = param.asInt() * 50;
}

int userIsInControl = 0;
BLYNK_WRITE(V2){
  userIsInControl = param.asInt();
}

int level = 0;
int mealTime = 0;
BLYNK_WRITE(V3)
{
  level = param.asInt();
  switch (level){
    case 1:
      mealTime = 360000;
      break;
    case 2:
      mealTime = 540000;
      break;
    case 3:
      mealTime = 900000;
      break;
    case 4:
      mealTime = 1260000;
      break;
  }
}  



void yellowBrighten(int duration, int numOfMatx) {
  uint16_t i, j;
  switch(numOfMatx){
    case 1:
      for (j = 1; j < 20; j++) { 
        for (i = 0; i < NUMPIXELS; i++) {
         strip1.setPixelColor(i, j*1.5, j, 0);
        }
        strip1.show();
        delay(duration);
      }
      delay(500);
      break;

    case 2 :
      for (j = 1; j < 20; j++) { 
        for (i = 0; i < NUMPIXELS; i++) {
         strip1.setPixelColor(i, j*1.5, j, 0);
         strip2.setPixelColor(i, j*1.5, j, 0);
        }
        strip1.show();
        strip2.show();
        delay(duration);
      }
      delay(500);
      break;

    case 3:
      for (j = 1; j < 20; j++) { 
        for (i = 0; i < NUMPIXELS; i++) {
         strip1.setPixelColor(i, j*1.5, j, 0);
         strip2.setPixelColor(i, j*1.5, j, 0);
         strip3.setPixelColor(i, j*1.5, j, 0);
        }
        strip1.show();
        strip2.show();
        strip3.show();
        delay(duration);
      }
      delay(500);
      break;
  }
}

void yellowDarken(int duration, int numOfMatx) {
  Serial.begin(9600);
  uint16_t i, j;
  switch(numOfMatx){
    case 1:
        for (j = 19; j > 0; j--) { 
          for (i = 0; i < strip1.numPixels(); i++) {
            strip1.setPixelColor(i, j*1.5, j, 0);
          }
        strip1.show();
        delay(duration);
        }
        delay(500);
        break;
        
    case 2:
      for (j = 19; j > 0; j--) { 
        for (i = 0; i < strip1.numPixels(); i++) {
          strip1.setPixelColor(i, j*1.5, j, 0);
          strip2.setPixelColor(i, j*1.5, j, 0);
        }
        strip1.show();
        strip2.show(); 
        delay(duration); 
        
       }
       delay(500);
      break;
  
    case 3:
      for (j = 19; j > 0; j--) { 
        for (i = 0; i < strip1.numPixels(); i++) {
          strip1.setPixelColor(i, j*1.5, j, 0);
          strip2.setPixelColor(i, j*1.5, j, 0);
          strip3.setPixelColor(i, j*1.5, j, 0);  
        }      
        strip1.show();
        strip2.show(); 
        strip3.show();   
        delay(duration); 
      }
      delay(500);
      break;
  }
}

void TurnOffNeopixels(){
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
      strip1.setPixelColor(i, pixels1.Color(0, 0, 0));
      strip1.show();   // Send the updated pixel colors to the hardware.
      strip2.setPixelColor(i, pixels2.Color(0, 0, 0));
      strip2.show();   // Send the updated pixel colors to the hardware.
      strip3.setPixelColor(i, pixels3.Color(0, 0, 0));
      strip3.show();   // Send the updated pixel colors to the hardware.      
    }
}



void setup()
{
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  strip1.begin();
  strip1.show();
  
  strip2.begin();
  strip2.show();
  
  strip3.begin();
  strip3.show();
  
  pixels1.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels1.clear();
  
  pixels2.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels2.clear();
  
  pixels3.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels3.clear();
  
  Serial.begin(115200);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  startTime = 0;
  elapsedTime = 0;
  
}

void loop()
{
  Blynk.run();
  if (pinValue == 1){
    if (elapsedTime - startTime <= mealTime / 3) {
      matrices = 1;
      if (userIsInControl){
        duration = interval;
      }
      else {
        duration = 75;
      }               
    }  
    else if (elapsedTime - startTime > mealTime / 3 && elapsedTime - startTime <= 2 * mealTime / 3) {  
      matrices = 2;
      if (userIsInControl){
        duration = interval;
      }
      else {
        duration = 150;
      }
    }
    else if (elapsedTime - startTime > 2 * mealTime / 3 && elapsedTime - startTime < mealTime){
      matrices = 3;
      if (userIsInControl){
        duration = interval;
      }
      else {
        duration = 250;
      }
    }
    else if (elapsedTime - startTime > mealTime){
      pinValue == 0;
      elapsedTime = 0;
      matrices = 1;
      Blynk.virtualWrite(V0, 0);
    }                       
    elapsedTime = millis();     
    yellowBrighten(duration, matrices);
    yellowDarken(duration, matrices);
    
  }

  else{
    void TurnOffNeopixels();
    elapsedTime = 0;
    matrices = 1;
  }
}

