// note: you need to set your serial monitor to 115200 to get correct values

int segment[4][7];//LCD segment data stored here
int measuredSpeed, oldSpeed;//converted data to speed
int n=0;
int button;
int t=76;

#include <Adafruit_NeoPixel.h>
 
#define PIN      28 // LED Stuff
#define N_LEDS 131

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup(){
  Serial.begin(115200);
  strip.begin();

  int segment[4][7];//LCD segment data stored here
  int measuredSpeed, oldSpeed;//converted data to speed
  int n=0;
  int button;
  int t=76;

  pinMode(52, OUTPUT);
  pinMode(22, INPUT); // button input
  pinMode(24, OUTPUT); //button led
  pinMode(25, OUTPUT); // car/ped sign output ... high is red car, low is person, was 38

}

void readSpeed(){
  digitalWrite(52, LOW);
  delay(200);
  digitalWrite(52, HIGH);
}


void readSpeedPressed(){
  strip.fill(strip.Color(255,0,0),0,131);
  strip.show();
  digitalWrite(24, HIGH); // button led on
  digitalWrite(52, LOW); // speed gun off
  delay(200);
  digitalWrite(24, LOW); // button led off
  digitalWrite(52, HIGH); // speed gun on
  strip.clear();
  strip.show();
}

void loop(){
  Serial.print(digitalRead(25));
  readSpeed();
  digitalWrite(24, HIGH); // set LED on button to high when not pressed

  button = digitalRead(22); // button reads from pin 22
  if(button == HIGH){ // restarts the count if button is pressed again
    t=0;
  }
  if (t<50){ // counter for if button is pressed. Total time is t * .5 seconds. t = 75 runs for 38 seconds CHANGE THIS VALUE FOR TOTAL TIME OF FUNCTION AFTER BUTTON PRESSED
    t++;
    readSpeedPressed();
  
    unsigned long scanTimeStart = millis();//timeout for scanning LCD
  
    while (millis() - scanTimeStart < 100) {//jump in and scan the LCD!
      for (int i = 7; i < 11; i++) { //sweep the common pins
       // Serial.println(analogRead(i));
        if (analogRead(i) < 10) {// LOW
          for (int j = 0; j < 7; j++) {//sweep the segments after we find an enabled common
            if (analogRead(j) > 600) {//HIGH
              segment[i - 7][j] = 1;//set the segment to a 1
            }
          }
        }
      }
    }
  
    measuredSpeed = 0;//clear the speed, and we'll set it now based on the segment data
  
    /*
        ONES POSITION
    */
  
    //     3,5
    // 3,4     2,5
    //     2,4
    // 1,4     1,5
    //     0,5
  
    //Zero - Ones
    if (segment[3][4] == 1 && segment[3][5] == 1 && segment[2][5] == 1 && segment[2][4] == 0 && segment[1][4] == 1 && segment[1][5] == 1 && segment[0][5] == 1) {
      measuredSpeed = 0;
    }
    //One - Ones
    if (segment[3][4] == 0 && segment[3][5] == 0 && segment[2][5] == 1 && segment[2][4] == 0 && segment[1][4] == 0 && segment[1][5] == 1 && segment[0][5] == 0) {
      measuredSpeed = 1;
    }
    //Two - Ones
    if (segment[3][4] == 0 && segment[3][5] == 1 && segment[2][5] == 1 && segment[2][4] == 1 && segment[1][4] == 1 && segment[1][5] == 0 && segment[0][5] == 1) {
      measuredSpeed = 2;
    }
    //Three - Ones
    if (segment[3][4] == 0 && segment[3][5] == 1 && segment[2][5] == 1 && segment[2][4] == 1 && segment[1][4] == 0 && segment[1][5] == 1 && segment[0][5] == 1) {
      measuredSpeed = 3;
    }
    //Four - Ones
    if (segment[3][4] == 1 && segment[3][5] == 0 && segment[2][5] == 1 && segment[2][4] == 1 && segment[1][4] == 0 && segment[1][5] == 1 && segment[0][5] == 0) {
      measuredSpeed = 4;
    }
    //Five - Ones
    if (segment[3][4] == 1 && segment[3][5] == 1 && segment[2][5] == 0 && segment[2][4] == 1 && segment[1][4] == 0 && segment[1][5] == 1 && segment[0][5] == 1) {
      measuredSpeed = 5;
    }
    //Six - Ones
    if (segment[3][4] == 1 && segment[3][5] == 1 && segment[2][5] == 0 && segment[2][4] == 1 && segment[1][4] == 1 && segment[1][5] == 1 && segment[0][5] == 1) {
      measuredSpeed = 6;
    }
    //Seven - Ones
    if (segment[3][4] == 0 && segment[3][5] == 1 && segment[2][5] == 1 && segment[2][4] == 0 && segment[1][4] == 0 && segment[1][5] == 1 && segment[0][5] == 0) {
      measuredSpeed = 7;
    }
    //Eight - Ones
    if (segment[3][4] == 1 && segment[3][5] == 1 && segment[2][5] == 1 && segment[2][4] == 1 && segment[1][4] == 1 && segment[1][5] == 1 && segment[0][5] == 1) {
      measuredSpeed = 8;
    }
    //Nine - Ones
    if (segment[3][4] == 1 && segment[3][5] == 1 && segment[2][5] == 1 && segment[2][4] == 1 && segment[1][4] == 0 && segment[1][5] == 1 && segment[0][5] == 1) {
      measuredSpeed = 9;
    }
  
  
    /*
       TENS POSITION
    */
    //     3,3
    // 3,2     2,3
    //     2,2
    // 1,2     1,3
    //     0,3
  
    //One - Tens
    if (segment[3][2] == 0 && segment[2][2] == 0 && segment[2][3] == 1 && segment[3][3] == 0 && segment[1][2] == 0 && segment[1][3] == 1 && segment[0][3] == 0) {
      measuredSpeed = measuredSpeed + (1 * 10);
    }
    //Two - Tens
    if (segment[3][2] == 0 && segment[2][2] == 1 && segment[2][3] == 1 && segment[3][3] == 1 && segment[1][2] == 1 && segment[1][3] == 0 && segment[0][3] == 1) {
      measuredSpeed = measuredSpeed + (2 * 10);
    }
    //Three - Tens
    if (segment[3][2] == 0 && segment[2][2] == 1 && segment[2][3] == 1 && segment[3][3] == 1 && segment[1][2] == 0 && segment[1][3] == 1 && segment[0][3] == 1) {
      measuredSpeed = measuredSpeed + (3 * 10);
    }
    //Four - Tens
    if (segment[3][2] == 1 && segment[2][2] == 1 && segment[2][3] == 1 && segment[3][3] == 0 && segment[1][2] == 0 && segment[1][3] == 1 && segment[0][3] == 0) {
      measuredSpeed = measuredSpeed + (4 * 10);
    }
    //Five - Tens
    if (segment[3][2] == 1 && segment[2][2] == 1 && segment[2][3] == 0 && segment[3][3] == 1 && segment[1][2] == 0 && segment[1][3] == 1 && segment[0][3] == 1) {
      measuredSpeed = measuredSpeed + (5 * 10);
    }
    //Six - Tens
    if (segment[3][2] == 1 && segment[2][2] == 1 && segment[2][3] == 0 && segment[3][3] == 1 && segment[1][2] == 1 && segment[1][3] == 1 && segment[0][3] == 1) {
      measuredSpeed = measuredSpeed + (6 * 10);
    }
    //Seven - Tens
    if (segment[3][2] == 0 && segment[2][2] == 0 && segment[2][3] == 1 && segment[3][3] == 1 && segment[1][2] == 0 && segment[1][3] == 1 && segment[0][3] == 0) {
      measuredSpeed = measuredSpeed + (7 * 10);
    }
    //Eight - Tens
    if (segment[3][2] == 1 && segment[2][2] == 1 && segment[2][3] == 1 && segment[3][3] == 1 && segment[1][2] == 1 && segment[1][3] == 1 && segment[0][3] == 1) {
      measuredSpeed = measuredSpeed + (8 * 10);
    }
    //Nine - Tens
    if (segment[3][2] == 1 && segment[2][2] == 1 && segment[2][3] == 1 && segment[3][3] == 1 && segment[1][2] == 0 && segment[1][3] == 1 && segment[0][3] == 1) {
      measuredSpeed = measuredSpeed + (9 * 10);
    }
  
    /*
       HUNDREDS
    */
    //     3,1
    // 3,0     2,1
    //     2,0
    // 1,0     1,1
    //     0,1
    //One - Hundreds
    if (segment[3][1] == 0 && segment[3][0] == 0 && segment[2][1] == 1 && segment[2][0] == 0 && segment[1][0] == 0 && segment[1][1] == 1 && segment[0][1] == 0) {
      measuredSpeed = measuredSpeed + (1 * 100);
    }
    if (segment[3][1] == 1 && segment[3][0] == 0 && segment[2][1] == 1 && segment[2][0] == 1 && segment[1][0] == 1 && segment[1][1] == 0 && segment[0][1] == 1) {
      measuredSpeed = measuredSpeed + (2 * 100);
    }
  
    /*for(int x=0;x<=3;x++){
      for(int y=0;y<=3;y++){
        Serial.println(segment[x][y]);
      }
    }*/
   
   if (oldSpeed != measuredSpeed) {//ony print speed if it's new
      Serial.print("Speed ");
      Serial.println(measuredSpeed);
      Serial.println(" mph");
      oldSpeed = measuredSpeed;
      n=0;
      Serial.println(" Don't Walk"); // if its a new speed then dont walk
      digitalWrite(25, HIGH); // red car
    }
  
   if (oldSpeed == 0){
    n++;
    if (n>6){ // waits for driver to come to complete stop and make sure its safe CHANGE THIS VALUE FOR DELAY IN SHOWING WALK
      Serial.println(" Walk");
      digitalWrite(25, LOW); // man crossing
    }
   }
  
    for (int i = 0; i < 4; i++) {//for degugging and clearing segment data
    //  Serial.print(i);
    //  Serial.print(": ");
      for (int j = 0; j < 7; j++) {
    //    Serial.print(segment[i][j]);
    //    Serial.print(",");
        segment[i][j] = 0;
      }
      Serial.println("  ");
    }
  }
 if (t >= 50) {
  digitalWrite(25, HIGH);
 }

}
