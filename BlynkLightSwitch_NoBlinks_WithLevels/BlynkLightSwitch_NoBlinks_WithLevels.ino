#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN        D8 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 64 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, PIN, NEO_GRB + NEO_KHZ800);

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

int pinValue = 0;
BLYNK_WRITE(V0)
{
  pinValue = param.asInt(); 
}

int interval = 0;
BLYNK_WRITE(V1)
{
  interval = param.asInt() * 10;
}

int fixed_times = 0;
BLYNK_WRITE(V2){
  fixed_times = param.asInt();
}

int blinkInterval = 0;
BLYNK_WRITE(V3)
{
  blinkInterval = param.asInt() * 1000;
}

unsigned long elapsedTime = 0;
unsigned long previousTime = 0;
int randomNumber;

void yellowBrighten() {
  uint16_t i, j;
  for (j = 1; j < 20; j++) { 
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, j*1.5, j, 0);
    }
    strip.show();
    delay(interval);
  }
  delay(500);
}

void yellowDarken() {
  Serial.begin(9600);
  uint16_t i, j;
  for (j = 19; j > 0; j--) { 
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, j*1.5, j, 0);
    }
    strip.show();
    delay(interval);
  }
  delay(500);
}

void yellowBlink(){
  Serial.begin(9600);
  uint16_t i;
    for (i = 0; i < strip.numPixels(); i++) {
     strip.setPixelColor(i, 43, 40, 0);
    }
    strip.show();
    delay(500);
    pixels.clear();
}

void TurnOffNeopixels(){
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }
}

void setup()
{
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.show();
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();
  Serial.begin(115200);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{

  Blynk.run();
  if (pinValue == 1){
    yellowBrighten();
    yellowDarken();
  }

  else{
    void TurnOffNeopixels();
  }
}

