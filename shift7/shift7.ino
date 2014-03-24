
// Pin connected to ST_CP of 74HC595
int latchPin = 8;
// Pin connected to SH_CP of 74HC595
int clockPin = 12;
// Pin connected to DS of 74HC595
int dataPin = 11;

// in my setup:
//  <2>
// ^   ^
// 3   1
// v   v
//  <4>
// ^   ^
// 6   7
// v   v
//  <0>  (5)
//
// so, eg, a 1 is bits 1 & 7; a 0 is bits 0, 1, 2, 3, 6, 7; etc.
int nums[16] = {B11001111, B10000010, B01010111, B10010111,
                B10011010, B10011101, B11011101, B10000110,
                B11011111, B10011110, B11111110, B11111001,
                B01101101, B11110011, B01111101, B01111100};

void setup() {
    //set pins to output so you can control the shift register
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}

void loop() {
    for (int i=0; i<16; i++) {
        // take the latchPin low so
        // the LEDs don't change while you're sending in bits:
        digitalWrite(latchPin, LOW);
        // shift out the bits:
        shiftOut(dataPin, clockPin, MSBFIRST, nums[i]);

        //take the latch pin high so the LEDs will light up:
        digitalWrite(latchPin, HIGH);
        // pause before next value:
        delay(1000);
    }
}

// Local Variables:
// mode: c
// c-file-style: "cc-mode"
// End:
