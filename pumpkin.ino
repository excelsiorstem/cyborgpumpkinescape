//pumpkin

#include <FastLED.h>
#define NUM_LEDS 60
#define DATA_PIN 11
enum Mode {CLOUD, OFF, ON, RED, GREEN, BLUE, FADE};
Mode mode = CLOUD;
Mode lastMode = CLOUD;
int fade_h;
int fade_direction = 1;
CRGB leds[NUM_LEDS];

#define NUM_LEDS_2 6
#define LED_TYPE_2 WS2812B
#define COLOR_ORDER_2 GRB
CRGB leds_2[NUM_LEDS_2];
const int NEO_2 = 6;

#include <Servo.h>
Servo pumbot;
const int pbp = 9;
const int p_out = 145;
const int p_in = 45;
int state;

void setup() {
  pumbot.attach(pbp);
  pumbot.write(p_in);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE_2, NEO_2, COLOR_ORDER_2>(leds_2, NUM_LEDS_2).setCorrection( TypicalLEDStrip );
  for (int y = 0; y < 6; y++) {
    pixel(0, 0, 255, y);
  }
}

void loop() {
//  for (int x = p_in; x < p_out; x++) {
     pumbot.write(p_in);
//     delay(10);
//  }
  for (int z = 0; z < 20; z++) {
    constant_lightning();
  }
//  for (int g = p_out; g > p_in; g--) {
    pumbot.write(p_out);
//    delay(10);
//  }
  for (int z = 0; z < 40; z++) {
    constant_lightning();
  }
}

void constant_lightning() {
  switch (random(1, 3)) {
    case 1:
      thunderburst();
      delay(random(10, 500));
      break;
    case 2:
      rolling();
      break;
    case 3:
      crack();
      delay(random(50, 250));
      break;
  }
}

void reset() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV( 0, 0, 0);
  }
  FastLED.show();
}

void rolling() {
  for (int r = 0; r < random(2, 10); r++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      if (random(0, 100) > 90) {
        leds[i] = CHSV( 0, 0, 255);
      }
      else {
        leds[i] = CHSV(0, 0, 0);
      }
    }
    FastLED.show();
    delay(random(5, 100));
    reset();
  }
}

void crack() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV( 0, 0, 255);
  }
  FastLED.show();
  delay(random(10, 100));
  reset();
}

void thunderburst() {
  int rs1 = random(0, NUM_LEDS / 2);
  int rl1 = random(10, 20);
  int rs2 = random(rs1 + rl1, NUM_LEDS);
  int rl2 = random(10, 20);
  for (int r = 0; r < random(3, 6); r++) {
    for (int i = 0; i < rl1; i++) {
      leds[i + rs1] = CHSV( 0, 0, 255);
    }
    if (rs2 + rl2 < NUM_LEDS) {
      for (int i = 0; i < rl2; i++) {
        leds[i + rs2] = CHSV( 0, 0, 255);
      }
    }
    FastLED.show();
    delay(random(10, 50));
    reset();
    delay(random(10, 50));
  }
}

void pixel(int r, int g, int b, int p) {
  leds_2[p] = CRGB (r, g, b);
  FastLED.show();
}
