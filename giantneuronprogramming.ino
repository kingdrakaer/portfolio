#include<FastLED.h>
#define LED_PINexcite     9     //pin for excitatory led strip
#define LED_PINinhibit    10    //pin for inhibitory led strip
#define LED_PINap         11    //pin for action potential (shortest) led strip
#define LED_PINbodyclose  12    //pin for first neuron body
#define LED_PINbodyfar    8     //pin for second neuron body
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDSlong     73  //num leds for the two long led strips
#define NUM_LEDSshort    36  //num leds for action potential (shortest) led strip
#define NUM_LEDSmatrix   64  //num leds for the neuron body led matrices
#define SCROLL_SPEED 50

CRGBArray<NUM_LEDSlong> ledsexcite;
CRGBArray<NUM_LEDSlong> ledsinhibit;
CRGBArray<NUM_LEDSshort> ledsap;
CRGBArray<NUM_LEDSmatrix> ledsbodyclose;
CRGBArray<NUM_LEDSmatrix> ledsbodyfar;

//excitatory pedal pins
int INpin1 = 2;
int INpin2 = 3;
int INpin3 = 4;

//integers to hold the excitatory pedal values
int excite1 = 0;
int excite2 = 0;
int excite3 = 0;

//inhibitory pedal pins
int INpin4 = 5;
int INpin5 = 6;
int INpin6 = 7;

//integers to hold the inhibitory pedal values
int inhibit1 = 0;
int inhibit2 = 0;
int inhibit3 = 0;

//integer to keep track of summation of the pedals
int sum = 0;

unsigned long lastUpdate;
unsigned long lastUpdate2;
unsigned long lastUpdate3;
unsigned long lastUpdate4;

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PINexcite, COLOR_ORDER>(ledsexcite, NUM_LEDSlong).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PINinhibit, COLOR_ORDER>(ledsinhibit, NUM_LEDSlong).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PINap, COLOR_ORDER>(ledsap, NUM_LEDSshort).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PINbodyclose, COLOR_ORDER>(ledsbodyclose, NUM_LEDSmatrix).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PINbodyfar, COLOR_ORDER>(ledsbodyfar, NUM_LEDSmatrix).setCorrection( TypicalLEDStrip );
  
  pinMode(INpin1, INPUT);
  pinMode(INpin2, INPUT);
  pinMode(INpin3, INPUT);
  pinMode(INpin4, INPUT);
  pinMode(INpin5, INPUT);
  pinMode(INpin6, INPUT);
}

void loop() {

  excite1 = digitalRead(INpin1);
  excite2 = digitalRead(INpin2);
  excite3 = digitalRead(INpin3);
  inhibit1 = digitalRead(INpin4);
  inhibit2 = digitalRead(INpin5);
  inhibit3 = digitalRead(INpin6);
  
  if (excite1 == HIGH || excite2 == HIGH || excite3 == HIGH )
    ledsexcite[0] = CRGB::Blue;
  else
    ledsexcite[0] = CRGB::Black;

  if (millis() - lastUpdate > SCROLL_SPEED) {
    lastUpdate += SCROLL_SPEED;
    for (int i = NUM_LEDSlong - 1; i > 0; i--)
      ledsexcite[i] = ledsexcite[i - 1];
    FastLED.show();
  }
  
  if (inhibit1 == HIGH || inhibit2 == HIGH || inhibit3 == HIGH)
    ledsinhibit[0] = CRGB::Blue;
  else
    ledsinhibit[0] = CRGB::Black;
    
  if (millis() - lastUpdate2 > SCROLL_SPEED) {
    lastUpdate2 += SCROLL_SPEED;
    for (int i = NUM_LEDSlong - 1; i > 0; i--)
      ledsinhibit[i] = ledsinhibit[i - 1];
    FastLED.show();
  }   
  
  if(ledsexcite[72] == CRGB(CRGB::Blue) && ledsinhibit[72] == CRGB(CRGB::Black))
    ledsap[0] = CRGB::Blue;
  else
    ledsap[0] = CRGB::Black;
    
  if (millis() - lastUpdate3 > SCROLL_SPEED) {
    lastUpdate3 += SCROLL_SPEED;
    for (int i = NUM_LEDSshort - 1; i > 0; i--)
      ledsap[i] = ledsap[i - 1];
    FastLED.show();
  }
  if(ledsexcite[72] == CRGB(CRGB::Blue) && ledsinhibit[72] == CRGB(CRGB::Black))
    ledsbodyclose[0] = CRGB::Blue;
  else
    ledsbodyclose[0] = CRGB::Black;
  
  if (millis() - lastUpdate4 > SCROLL_SPEED) {
    lastUpdate4 += SCROLL_SPEED;
    for (int i = NUM_LEDSmatrix - 1; i > 0; i--)
      ledsbodyclose[i] = ledsbodyclose[i - 1];
    FastLED.show();
  }
}
