// include the library code for LCD use:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// the pin that your button is connected to
const int buttonPin = 7;
// to see if your button has changed state
int buttonState = 0;
// to trigger your jump count
bool jump = true;
// to keep count ofhow many frames you are jumping
int jumpCnt = 0;
// basically frame rate
int delaytime = 300;
// the score through the game
int score = 0;
// position of cactus 
int cPos = 15;
// position of bird
int bPos = 6;
// position of dino
int dPos = 1;

// make some custom characters:
byte dino[8] = {
  0b00000,
  0b00111,
  0b00111,
  0b10110,
  0b11111,
  0b01010,
  0b01010,
  0b00000,
  
};

byte cactus[8] = {
  0b00100,
  0b00101,
  0b10101,
  0b10101,
  0b10101,
  0b10111,
  0b11100,
  0b00100
};
byte empty[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte bird[8] = {
  0b00000,
  0b00100,
  0b01100,
  0b11110,
  0b00111,
  0b00110,
  0b00100,
  0b00000
};
void setup() {
  // initialize LCD and set up the number of columns and rows:
  lcd.begin(16, 2);
  // create a new character
  lcd.createChar(0, dino);
  // create a new character
  lcd.createChar(1, cactus);
  // create a new character
  lcd.createChar(2, empty);
  // create a new character
  lcd.createChar(3, bird);
  // bring the LCD cursor the the corect spot to draw dino  
  lcd.setCursor(1, 1);
  // print the dino
  lcd.write(byte(0));
  // define the button as an input
  pinMode(buttonPin, INPUT);
  
}

void loop() {
  // each frame of the game make the game faster for difficulty
  delaytime -= 1;
  // bring cursor to top right corner
  lcd.setCursor(6,0);
  // print the score
  lcd.print("score: ");
  lcd.setCursor(13,0);
  lcd.print(score);
  // each frame of the game add 5 to score
  score += 5;
  // read the state of the button
  buttonState = digitalRead(buttonPin);
  // colision dection for dino and cactus
  
  if (dPos == 1 && cPos == 1)
  {
    // reset score, speed, and erase the score numbers
    score = 0;
    delaytime = 300;
    lcd.setCursor(13,0);
    lcd.write(2);
    lcd.setCursor(14,0);
    lcd.write(2);
    lcd.setCursor(15,0);
    lcd.write(2);
  }
  // buttonpress code
  if (buttonState == HIGH) {
    // bring the dino up
    dPos = 0;
    // start the jump counter
    jump = true;
    // erase the bottom dino
    lcd.setCursor(1,1);
    lcd.write(2);
  }
  // if the jumpcounter is on add on to the jumpcount
  if (jump){
    jumpCnt += 1;
    }
  // if counter has reached max stop the jump
  if (jumpCnt == 4){
    jump = false;
    jumpCnt = 0;
    // bring the dino down and erase the upper dino
    dPos = 1;
    lcd.setCursor(1,0);
    lcd.write(2);
    }
// the code to make the cactus "move" and draw the dino
  lcd.setCursor(0,1);
  lcd.write(2);
  //draw dino
  lcd.setCursor(1,dPos);
  lcd.write(byte(0));  
  //draw the cactus and erase the block behind and infront of it
  lcd.setCursor(cPos - 1,1);
  lcd.write(2);
  lcd.setCursor(cPos + 1,1);
  lcd.write(2);  
  lcd.setCursor(cPos, 1);
  lcd.write(1);
  // change the X value of the cactus every frame, if it is at the end teleport it to the begining
  if (cPos >= 0)
  {
    cPos -= 1;
  }else{
    cPos = 16;
  }
  // delay for visibility
  delay(delaytime);
}
