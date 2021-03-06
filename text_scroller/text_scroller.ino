// message scroller for arduino 8x8 matrix led thingie

#define MSG_LEN 100
// add two chars at the end of your message
char message[MSG_LEN+3] = "...";

// from X11 misc 5x8 pcf file. via:
// pcf2bdf /usr/share/fonts/X11/misc/5x8.pcf.gz | perl -00 -wne \\
// 'if (/^STARTCHAR (\w+).*BITMAP.(.*)ENDCHAR/ms) {$n=$1; $b=$2;
//  print("  {", join(", ", map("0x$_", $b =~ /(\w+)/g)), "}, // $n\n")}'
byte ascii[][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // space
    {0x00, 0x20, 0x20, 0x20, 0x20, 0x00, 0x20, 0x00}, // exclam
    {0x00, 0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00}, // quotedbl
    {0x50, 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x50, 0x00}, // numbersign
    {0x20, 0x70, 0xA0, 0x70, 0x28, 0x70, 0x20, 0x00}, // dollar
    {0x00, 0x40, 0x50, 0x20, 0x50, 0x10, 0x00, 0x00}, // percent
    {0x40, 0xA0, 0xA0, 0x40, 0xA0, 0xA0, 0x50, 0x00}, // ampersand
    {0x00, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00}, // quotesingle
    {0x00, 0x20, 0x40, 0x40, 0x40, 0x40, 0x20, 0x00}, // parenleft
    {0x00, 0x40, 0x20, 0x20, 0x20, 0x20, 0x40, 0x00}, // parenright
    {0x00, 0x00, 0x90, 0x60, 0xF0, 0x60, 0x90, 0x00}, // asterisk
    {0x00, 0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00}, // plus
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x20, 0x40}, // comma
    {0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00}, // hyphen
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0x20}, // period
    {0x00, 0x10, 0x10, 0x20, 0x40, 0x80, 0x80, 0x00}, // slash
    {0x00, 0x20, 0x50, 0x50, 0x50, 0x50, 0x20, 0x00}, // zero
    {0x00, 0x20, 0x60, 0x20, 0x20, 0x20, 0x70, 0x00}, // one
    {0x00, 0x60, 0x90, 0x10, 0x60, 0x80, 0xF0, 0x00}, // two
    {0x00, 0xF0, 0x20, 0x60, 0x10, 0x90, 0x60, 0x00}, // three
    {0x00, 0x20, 0x60, 0xA0, 0xF0, 0x20, 0x20, 0x00}, // four
    {0x00, 0xF0, 0x80, 0xE0, 0x10, 0x90, 0x60, 0x00}, // five
    {0x00, 0x60, 0x80, 0xE0, 0x90, 0x90, 0x60, 0x00}, // six
    {0x00, 0xF0, 0x10, 0x20, 0x20, 0x40, 0x40, 0x00}, // seven
    {0x00, 0x60, 0x90, 0x60, 0x90, 0x90, 0x60, 0x00}, // eight
    {0x00, 0x60, 0x90, 0x90, 0x70, 0x10, 0x60, 0x00}, // nine
    {0x00, 0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x00}, // colon
    {0x00, 0x00, 0x30, 0x30, 0x00, 0x30, 0x20, 0x40}, // semicolon
    {0x00, 0x10, 0x20, 0x40, 0x40, 0x20, 0x10, 0x00}, // less
    {0x00, 0x00, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0x00}, // equal
    {0x00, 0x40, 0x20, 0x10, 0x10, 0x20, 0x40, 0x00}, // greater
    {0x00, 0x20, 0x50, 0x10, 0x20, 0x00, 0x20, 0x00}, // question
    {0x30, 0x48, 0x98, 0xA8, 0xA8, 0x90, 0x40, 0x30}, // at
    {0x00, 0x60, 0x90, 0x90, 0xF0, 0x90, 0x90, 0x00}, // A
    {0x00, 0xE0, 0x90, 0xE0, 0x90, 0x90, 0xE0, 0x00}, // B
    {0x00, 0x60, 0x90, 0x80, 0x80, 0x90, 0x60, 0x00}, // C
    {0x00, 0xE0, 0x90, 0x90, 0x90, 0x90, 0xE0, 0x00}, // D
    {0x00, 0xF0, 0x80, 0xE0, 0x80, 0x80, 0xF0, 0x00}, // E
    {0x00, 0xF0, 0x80, 0xE0, 0x80, 0x80, 0x80, 0x00}, // F
    {0x00, 0x60, 0x90, 0x80, 0xB0, 0x90, 0x60, 0x00}, // G
    {0x00, 0x90, 0x90, 0xF0, 0x90, 0x90, 0x90, 0x00}, // H
    {0x00, 0x70, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00}, // I
    {0x00, 0x70, 0x20, 0x20, 0x20, 0xA0, 0x40, 0x00}, // J
    {0x00, 0x90, 0xA0, 0xC0, 0xA0, 0xA0, 0x90, 0x00}, // K
    {0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF0, 0x00}, // L
    {0x00, 0x90, 0xF0, 0xF0, 0x90, 0x90, 0x90, 0x00}, // M
    {0x00, 0x90, 0xD0, 0xF0, 0xB0, 0xB0, 0x90, 0x00}, // N
    {0x00, 0x60, 0x90, 0x90, 0x90, 0x90, 0x60, 0x00}, // O
    {0x00, 0xE0, 0x90, 0x90, 0xE0, 0x80, 0x80, 0x00}, // P
    {0x00, 0x60, 0x90, 0x90, 0xD0, 0xB0, 0x60, 0x10}, // Q
    {0x00, 0xE0, 0x90, 0x90, 0xE0, 0x90, 0x90, 0x00}, // R
    {0x00, 0x60, 0x90, 0x40, 0x20, 0x90, 0x60, 0x00}, // S
    {0x00, 0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00}, // T
    {0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x60, 0x00}, // U
    {0x00, 0x90, 0x90, 0x90, 0x90, 0x60, 0x60, 0x00}, // V
    {0x00, 0x90, 0x90, 0x90, 0xF0, 0xF0, 0x90, 0x00}, // W
    {0x00, 0x90, 0x90, 0x60, 0x60, 0x90, 0x90, 0x00}, // X
    {0x00, 0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x00}, // Y
    {0x00, 0xF0, 0x10, 0x20, 0x40, 0x80, 0xF0, 0x00}, // Z
    {0x00, 0x70, 0x40, 0x40, 0x40, 0x40, 0x70, 0x00}, // bracketleft
    {0x00, 0x80, 0x80, 0x40, 0x20, 0x10, 0x10, 0x00}, // backslash
    {0x00, 0x70, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00}, // bracketright
    {0x00, 0x20, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00}, // asciicircum
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0}, // underscore
    {0x00, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00}, // grave
    {0x00, 0x00, 0x00, 0x70, 0x90, 0x90, 0x70, 0x00}, // a
    {0x00, 0x80, 0x80, 0xE0, 0x90, 0x90, 0xE0, 0x00}, // b
    {0x00, 0x00, 0x00, 0x30, 0x40, 0x40, 0x30, 0x00}, // c
    {0x00, 0x10, 0x10, 0x70, 0x90, 0x90, 0x70, 0x00}, // d
    {0x00, 0x00, 0x00, 0x60, 0xB0, 0xC0, 0x60, 0x00}, // e
    {0x00, 0x20, 0x50, 0x40, 0xE0, 0x40, 0x40, 0x00}, // f
    {0x00, 0x00, 0x00, 0x60, 0x90, 0x70, 0x10, 0x60}, // g
    {0x00, 0x80, 0x80, 0xE0, 0x90, 0x90, 0x90, 0x00}, // h
    {0x00, 0x20, 0x00, 0x60, 0x20, 0x20, 0x70, 0x00}, // i
    {0x00, 0x10, 0x00, 0x10, 0x10, 0x10, 0x50, 0x20}, // j
    {0x00, 0x80, 0x80, 0x90, 0xE0, 0x90, 0x90, 0x00}, // k
    {0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00}, // l
    {0x00, 0x00, 0x00, 0xD0, 0xA8, 0xA8, 0xA8, 0x00}, // m
    {0x00, 0x00, 0x00, 0xE0, 0x90, 0x90, 0x90, 0x00}, // n
    {0x00, 0x00, 0x00, 0x60, 0x90, 0x90, 0x60, 0x00}, // o
    {0x00, 0x00, 0x00, 0xE0, 0x90, 0xE0, 0x80, 0x80}, // p
    {0x00, 0x00, 0x00, 0x70, 0x90, 0x70, 0x10, 0x10}, // q
    {0x00, 0x00, 0x00, 0xA0, 0xD0, 0x80, 0x80, 0x00}, // r
    {0x00, 0x00, 0x00, 0x30, 0x60, 0x10, 0x60, 0x00}, // s
    {0x00, 0x40, 0x40, 0xE0, 0x40, 0x50, 0x20, 0x00}, // t
    {0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x70, 0x00}, // u
    {0x00, 0x00, 0x00, 0x50, 0x50, 0x50, 0x20, 0x00}, // v
    {0x00, 0x00, 0x00, 0x88, 0xA8, 0xA8, 0x50, 0x00}, // w
    {0x00, 0x00, 0x00, 0x90, 0x60, 0x60, 0x90, 0x00}, // x
    {0x00, 0x00, 0x00, 0x90, 0x90, 0x70, 0x90, 0x60}, // y
    {0x00, 0x00, 0x00, 0xF0, 0x20, 0x40, 0xF0, 0x00}, // z
    {0x30, 0x40, 0x20, 0xC0, 0x20, 0x40, 0x30, 0x00}, // braceleft
    {0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00}, // bar
    {0xC0, 0x20, 0x40, 0x30, 0x40, 0x20, 0xC0, 0x00}, // braceright
    {0x00, 0x50, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00}, // asciitilde
};

// FIXME: the 5x8ness of the font permeates the logic below.

byte msg[8] =  {0, 0, 0, 0, 0, 0, 0, 0};
int pos = 0; // char position in message
int message_len = 3;
byte off = 0; // column offset in char
byte tick = 0;

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

void loop() {
    if (Serial.available()) {
        // readBytesUntil takes an int to specify how much to read,
        //     and returns a byte of how much it read.
        // >head asplode<
        int n = Serial.readBytesUntil('\n', message, MSG_LEN);
        // n *should* be >0 here. Doesn't hurt to make sure.
        if (n) {
            message[n] = message[0];
            message[n+1] = message[1];
            message[n+2] = 0;
            // and reset the scroller:
            tick = 0;
            pos = 0;
            off = 0;
            message_len = strlen(message);
        }
    }
    int i, j;
    if (!tick) {
        for (i=0; i<8; i++) {
            msg[7-i] = ((ascii[message[pos  ]-' '][i] << off) & 255)
                + (ascii[message[pos+1]-' '][i] >> (5-off))
                + (ascii[message[pos+2]-' '][i] >> (10-off));
        }
        off++;
        if (off > 4) {
            pos++;
            off=0;
            if (pos >= message_len - 2) {
                pos = 0;
            }
        }
    }
    for (i=2; i<10; i++) {
        for (j=10; j<18; j++) {
            if ((msg[i-2] & (1<<(j-10))) != 0) {
                digitalWrite(j, LOW);
            } else {
                digitalWrite(j, HIGH);
            }
        }
        digitalWrite(i, HIGH);
        delay(2);
        digitalWrite(i, LOW);
    }
    tick = (tick+1) % 5;
}

// Local Variables:
// mode: c
// c-file-style: "cc-mode"
// End:
