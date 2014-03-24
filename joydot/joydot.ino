// joystick dot mover for arduino 8x8 matrix led thingie

#define xPin 4
#define yPin 5

void setup() {
    int i;
    for (i=2; i<10; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
    for (i=10; i<18; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, HIGH);
    }
    Serial.begin(9600);
}

char delta(int pin) {
    int val = analogRead(pin) - 0x1ff;
    if (abs(val) < 0x1f) {
        return 0;
    }
    return val > 0 ? 1 : -1;
}

int x = 5;
int y = 5;

void loop() {
    x = constrain(x - delta(xPin), 0, 7);
    y = constrain(y + delta(yPin), 0, 7);

    digitalWrite(2+x, HIGH);
    digitalWrite(10+y, LOW);
    delay(20);
    digitalWrite(2+x, LOW);
    digitalWrite(10+y, HIGH);
}

// Local Variables:
// mode: c
// c-file-style: "cc-mode"
// End:
