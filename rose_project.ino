  // KEREM DÖLEKSÖZ && HÜSNÜ SELİM SERDAR

#include 
//INITIALIZE - DO NOT EDIT
#define NUM_LEDS 15
#define LED_PIN 3
#define MIN_BRIGHTNESS 8
#define MAX_BRIGHTNESS 64
#define LED_TYPE NEOPIXEL
#define buttonPin 5
struct CRGB leds[NUM_LEDS];
int currentMode = -1;  //Between 0 and (HowManyMods - 1)
int k = 0;
int m = 30;
//INITIALIZE - DO NOT EDIT

//EDITABLE - AS THE SKETCH GETS BIGGER OR CHANGED
byte HowManyMods = 8;
//EDITABLE - AS THE SKETCH GETS BIGGER OR CHANGED

//TIMING ESSENTIALS - DO NOT EDIT
boolean buttonState = HIGH;
boolean lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

unsigned long millisAnchor = 0;
unsigned long millisTemp;
byte blinkState = 0;                          //Sets 0 in case of mod change
byte RedBreatheState = 0;                     //Sets 0 in case of mod change
int RedBreatheCounter = 0;                    //Sets 0 in case of mod change
unsigned long randomColorsDelaySelector = 0;  //Sets 0 in case of mod change
byte FireworksState = 0;                      //Sets 0 in case of mod change
int FireworksDelayHolder = 0;                 //Sets 0 in case of mod change
int OneByOneCounter = 0;                      //Sets 0 in case of mod change
byte OneByOneState = 0;                       //Sets 0 in case of mod change
byte HalfAndHalfState = 0;                    //Sets 0 in case of mod change
//TIMING ESSENTIALS - DO NOT EDIT

void setup() {
  pinMode(buttonPin, INPUT);

  FastLED.addLeds(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 20);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  millisTemp = millis();
  button();

  switch (currentMode) {
    case 0:
      standBy();
      break;

    case 1:
      Blink();
      break;

    case 2:
      RedBreatheEffect();
      break;

    case 3:
      RainbowBreatheEffect();
      break;

    default:
      break;
  }

  switch (currentMode) {
    case 4:
      RandomColors();
      break;

    case 5:
      OneByOne();
      break;

    case 6:
      Fireworks();
      break;

    case 7:
      HalfAndHalf();
      break;

    default:
      break;
  }
}


//*************************                      M O D S                      *****************************

void button() {
  boolean reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millisTemp;
  }

  if ((millisTemp - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        // Button is pressed, change mode
        currentMode = (currentMode + 1) % HowManyMods;  // Cycle through modes 0 to HowManyMods - 1
        switch (currentMode) {
          case 1:
            blinkState = 0;
            break;

          case 2:
            RedBreatheState = 0;
            RedBreatheCounter = 0;
            break;

          case 4:
            randomColorsDelaySelector = 0;
            break;

          case 5:
            OneByOneCounter = 0;
            OneByOneState = 0;
            FastLED.clear();
            break;

          case 6:
            FireworksState = 0;
            FireworksDelayHolder = 0;
            break;

          case 7:
            HalfAndHalfState = 0;
            break;

            //case 8:
            //break;

          default:
            break;
        }
      }
    }
  }
  lastButtonState = reading;
}


void HalfAndHalf() {
  int HalfAndHalfDelay = 700;

  for (int i = 0; i <= 14; i++) {
    leds[i] = CRGB(0, 0, 0);
  }

  if ((millisTemp - millisAnchor) >= HalfAndHalfDelay) {
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 20);
    if (HalfAndHalfState == 0) {
      //Top Half
      leds[6] = CRGB(218, 165, 32);
      leds[0] = CRGB(218, 165, 32);
      leds[4] = CRGB(218, 165, 32);
      leds[3] = CRGB(218, 165, 32);
      leds[5] = CRGB(218, 165, 32);

      //Top Leaf
      leds[10] = CRGB(0, 139, 139);
      leds[11] = CRGB(0, 139, 139);
      leds[12] = CRGB(0, 139, 139);
      // Bottom Half
      leds[7] = CRGB(0, 0, 0);
      leds[1] = CRGB(0, 0, 0);
      leds[8] = CRGB(0, 0, 0);
      leds[2] = CRGB(0, 0, 0);
      leds[9] = CRGB(0, 0, 0);
      FastLED.show();
      HalfAndHalfState = 1;
      millisAnchor = millisTemp;
    }

    else if (HalfAndHalfState = 1) {

      //Top Half
      leds[6] = CRGB(0, 0, 0);
      leds[0] = CRGB(0, 0, 0);
      leds[4] = CRGB(0, 0, 0);
      leds[3] = CRGB(0, 0, 0);
      leds[5] = CRGB(0, 0, 0);


      // Bottom Half
      leds[7] = CRGB(128, 0, 0);
      leds[1] = CRGB(128, 0, 0);
      leds[8] = CRGB(128, 0, 0);
      leds[2] = CRGB(128, 0, 0);
      leds[9] = CRGB(128, 0, 0);
      //Bottom Leaf
      leds[13] = CRGB(0, 100, 0);
      leds[14] = CRGB(0, 100, 0);
      FastLED.show();
      HalfAndHalfState = 0;
      millisAnchor = millisTemp;
    }
  }
}

void standBy() {
  int standByDelay = 100;
  if ((millisTemp - millisAnchor) >= standByDelay) {
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 20);
    for (int i = 0; i <= 9; i++) {
      leds[i] = CRGB(255, 0, 0);
      FastLED.show();
    }

    for (int i = 10; i <= 14; i++) {
      leds[i] = CRGB(0, 255, 0);
      FastLED.show();
    }
    millisAnchor = millisTemp;
  }
}

void Blink() {
  int blinkDelay = 1000;

  if ((millisTemp - millisAnchor) >= blinkDelay) {
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 20);
    if (blinkState == 0) {
      for (int i = 0; i <= 14; i++) {
        leds[i] = CRGB(0, 0, 0);
      }
      FastLED.show();
      blinkState = 1;
      millisAnchor = millisTemp;
    } else if (blinkState == 1) {
      for (int i = 0; i <= 9; i++) {
        leds[i] = CRGB(255, 0, 0);
      }
      for (int i = 10; i <= 14; i++) {
        leds[i] = CRGB(0, 255, 0);
      }
      FastLED.show();
      blinkState = 0;
      millisAnchor = millisTemp;
    }
  }
}

void RedBreatheEffect() {
  int RedBreatheDelay = 5;
  float BrightnessUpperLimit = 40;

  if ((millisTemp - millisAnchor) >= RedBreatheDelay) {
    if (RedBreatheState == 0) {
      FastLED.setMaxPowerInVoltsAndMilliamps(5, BrightnessUpperLimit);
      for (int i = 0; i <= 10; i++) {
        leds[i] = CRGB(255, 0, 0);
      }
      for (int i = 10; i <= 15; i++) {
        leds[i] = CRGB(0, 255, 0);
      }
      FastLED.show();
      millisAnchor = millisTemp;
      RedBreatheState = 1;
      RedBreatheCounter = BrightnessUpperLimit * 10;
    } else if (RedBreatheState == 1) {
      float brghtnss = RedBreatheCounter * 0.1;
      FastLED.setMaxPowerInVoltsAndMilliamps(5, brghtnss);
      FastLED.show();
      millisAnchor = millisTemp;
      RedBreatheCounter--;
      if (RedBreatheCounter < 0) {
        RedBreatheState = 2;
        RedBreatheCounter = 0;
      }
    } else if (RedBreatheState == 2) {
      float brghtnss = RedBreatheCounter * 0.1;
      FastLED.setMaxPowerInVoltsAndMilliamps(5, brghtnss);
      FastLED.show();
      millisAnchor = millisTemp;
      RedBreatheCounter++;
      if (RedBreatheCounter > BrightnessUpperLimit * 10) {
        RedBreatheState = 0;
        RedBreatheCounter = BrightnessUpperLimit * 10;
      }
    }
  }
}

void RainbowBreatheEffect() {
  int RainbowBreatheDelay = 3;

  if ((millisTemp - millisAnchor) >= RainbowBreatheDelay) {
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 20);
    struct CRGB ledTemp[15];
    float breath = (exp(sin(millis() / 5000.0 * PI)) - 0.36787944) * 108.0;
    breath = map(breath, 0, 255, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
    FastLED.setBrightness(breath);
    fill_rainbow(ledTemp, 15, (k++ / m));  // Use ledTemp array for fill_rainbow

    // Define the mapping array for the LED order
    int ledMap[] = { 14, 13, 12, 11, 10, 8, 7, 9, 1, 2, 6, 0, 3, 4, 5 };

    // Copy values from ledTemp to the desired positions in leds
    for (int i = 0; i < 15; i++) {
      leds[ledMap[14 - i]] = ledTemp[i];
    }

    if (k == (255 * m)) {
      k = 0;
    }
    FastLED.show();
    millisAnchor = millisTemp;
  }
}

void RandomColors() {
  int randomColorsCaseZeroDelay = 300;
  int randomColorsCaseOneDelay = 100;

  if ((millisTemp - millisAnchor) >= randomColorsDelaySelector) {
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 20);
    for (byte i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(random(0, 255), random(0, 255), random(0, 255));
    }

    byte pattern = random(0, 1);

    switch (pattern) {
      case 0:
        FastLED.show();
        randomColorsDelaySelector = randomColorsCaseZeroDelay;
        break;
      case 1:  //EFFECT FOR RANDOMCOLORS - twinkleEffect
        int randomLed = random(NUM_LEDS);
        leds[randomLed].fadeToBlackBy(20);
        FastLED.show();
        randomColorsDelaySelector = randomColorsCaseOneDelay;
        break;
    }
    millisAnchor = millisTemp;
  }
}

void OneByOne() {
  int OneByOneDelayONE = 200;
  int OneByOneDelayTWO = 150;

  int OneByOneDelayHolder = OneByOneDelayONE;

  if (OneByOneState == 2) {
    OneByOneDelayHolder = OneByOneDelayTWO;
  }

  if ((millisTemp - millisAnchor) >= OneByOneDelayHolder) {
    if (OneByOneState == 0) {
      FastLED.setMaxPowerInVoltsAndMilliamps(5, 20);
      leds[OneByOneCounter] = CRGB(255, 0, 0);
      FastLED.show();
      millisAnchor = millisTemp;
      OneByOneCounter++;
      if (OneByOneCounter > 9) {
        OneByOneState = 1;
      }
    } else if (OneByOneState == 1) {
      leds[OneByOneCounter] = CRGB(0, 255, 0);
      FastLED.show();
      millisAnchor = millisTemp;
      OneByOneCounter++;
      if (OneByOneCounter > 14) {
        OneByOneState = 2;
        OneByOneCounter = 14;
      }
    } else if (OneByOneState == 2) {
      leds[OneByOneCounter] = CRGB(0, 0, 0);
      FastLED.show();
      millisAnchor = millisTemp;
      OneByOneCounter--;
      if (OneByOneCounter < 0) {
        OneByOneState = 0;
        OneByOneCounter = 0;
      }
    }
  }
}

void Fireworks() {
  if ((millisTemp - millisAnchor) >= FireworksDelayHolder) {
    if (FireworksState == 0) {
      FastLED.setMaxPowerInVoltsAndMilliamps(5, 20);
      for (int i = 0; i <= 14; i++) {
        leds[i] = CRGB(0, 0, 0);
      }
      // GREEN
      leds[14] = CRGB(0, 100, 0);
      FastLED.show();
      FireworksDelayHolder = 200;
      millisAnchor = millisTemp;
      FireworksState = 1;
    } else if (FireworksState == 1) {
      leds[13] = CRGB(0, 128, 0);
      FastLED.show();
      FireworksDelayHolder = 200;
      millisAnchor = millisTemp;
      FireworksState = 2;
    } else if (FireworksState == 2) {
      leds[12] = CRGB(0, 255, 0);
      FastLED.show();
      FireworksDelayHolder = 200;
      millisAnchor = millisTemp;
      FireworksState = 3;
    } else if (FireworksState == 3) {
      leds[11] = CRGB(34, 139, 34);
      FastLED.show();
      FireworksDelayHolder = 200;
      millisAnchor = millisTemp;
      FireworksState = 4;
    } else if (FireworksState == 4) {
      leds[10] = CRGB(50, 205, 50);
      FastLED.show();
      FireworksDelayHolder = 200;
      millisAnchor = millisTemp;
      FireworksState = 5;
    } else if (FireworksState == 5) {
      //RED
      leds[8] = CRGB(139, 0, 0);
      FastLED.show();
      FireworksDelayHolder = 400;
      millisAnchor = millisTemp;
      FireworksState = 6;
    } else if (FireworksState == 6) {
      leds[2] = CRGB(255, 0, 0);
      FastLED.show();
      FireworksDelayHolder = 400;
      millisAnchor = millisTemp;
      FireworksState = 7;
    } else if (FireworksState == 7) {
      leds[4] = CRGB(255, 0, 0);
      FastLED.show();
      FireworksDelayHolder = 400;
      millisAnchor = millisTemp;
      FireworksState = 8;
    } else if (FireworksState == 8) {
      leds[0] = CRGB(205, 92, 92);
      leds[1] = CRGB(205, 92, 92);
      leds[3] = CRGB(205, 92, 92);
      leds[5] = CRGB(205, 92, 92);
      FastLED.show();
      FireworksDelayHolder = 400;
      millisAnchor = millisTemp;
      FireworksState = 9;
    } else if (FireworksState == 9) {
      leds[6] = CRGB(255, 105, 180);
      leds[7] = CRGB(255, 105, 180);
      leds[8] = CRGB(255, 105, 180);
      leds[9] = CRGB(255, 105, 180);
      FastLED.show();
      FireworksDelayHolder = 600;
      millisAnchor = millisTemp;
      FireworksState = 0;
    }
  }
}
    }
  