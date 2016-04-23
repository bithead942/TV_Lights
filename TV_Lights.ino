/*
  TV RGB Light
 
 For use with Arduino UNO
 Requires Xbee Shield with Xbee Radio
 Requires RGB Shield with 12V power
 
 
 When new serial data arrives, this sketch adds it to a String.
 The expected string format is:
 
 "r=###,b=###,g=###"
 It is terminated with an '\n' character (ASCII 10)
 
 The valid number range for each parameter is 0 to 255
 
 Upon receipt, the sketch updates the lights using the RGB shield using Pulse Width Modulation (PWM)
 
 PINS USED:
    Xbee Shield
      Tx       0
      Rx       1
    
    RBG Shield
      Red      3
      Green    5
      Blue     6
 
 */
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(2, 3); // RX, TX

String inString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int red = 3;    // RED LED connected to PWM pin 3
int green = 5;    // GREEN LED connected to PWM pin 5
int blue = 6;    // BLUE LED connected to PWM pin 6
int r=255; 
int g=255; 
int b=255;

char colorArr[5];
String temp="";
int Pos_r;
int Pos_g;
int Pos_b;
int Pos_End;

unsigned int iCounter = 0;
const int LIGHTTIME = 10000;  //10 seconds
boolean bCount;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  
  
  // initialize serial:
  Serial.begin(9600);
  //mySerial.begin(9600);
  // reserve 200 bytes for the inputString:
  inString.reserve(20);
  inString = "";
  
  rgb(255,255,255);
  delay(500);
  rgb(0,0,0);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) 
  {
    //Check for valid command
    //Serial.println("Validating...");
    temp="";
    Pos_r = inString.indexOf("r");
    Pos_g = inString.indexOf("g");
    Pos_b = inString.indexOf("b");
    Pos_End = inString.indexOf("\n");
    
      if(Pos_r>=0)
      {
         temp=inString.substring((Pos_r+2), (Pos_g-1));
         temp.toCharArray(colorArr, 5);
         r=(atoi(colorArr));
         //Serial.print("red: ");
         //Serial.println(r);
      }
      if(Pos_g>=0)
      {
         temp=inString.substring((Pos_g+2), (Pos_b-1));
         temp.toCharArray(colorArr, 5);
         g=(atoi(colorArr));
         //Serial.print("green: ");
         //Serial.println(g);
      }         
      if(Pos_b>=0)
      {
         temp=inString.substring((Pos_b+2), (Pos_End-1));
         temp.toCharArray(colorArr, 5);
         b=(atoi(colorArr));
         //Serial.print("blue: ");
         //Serial.println(b);
      }      
      
      if ((Pos_r>=0)&&(Pos_g>=0)&&(Pos_b>=0)) 
      {
         iCounter = 0;
         bCount = true;
         rgb(r,g,b);
      }
    
    // clear the string:
    inString = "";
    stringComplete = false;
  }
  
   if (iCounter >= LIGHTTIME)
      {
      rgb(0,0,0);
      iCounter = LIGHTTIME; 
      bCount = false;
      }
      
   if (bCount) iCounter++;
   delay(1);
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) 
  {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    //Serial.println(inChar, DEC);
    // add it to the inputString:
    inString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == 16 or inChar == 10)   //HEX 10 = DEC 16
    {
      //Serial.print("*"); 
      stringComplete = true; 
    } 
  }
}

void rgb(int r, int g, int b)
{

  /*Serial.print("RGB: ");
  Serial.print(r);
  Serial.print(" ");
  Serial.print(g);
  Serial.print(" ");
  Serial.print(b); */
  if (r>255) r=255;
  if (g>255) g=255;
  if (b>255) b=255;
  if (r<0) r=0;
  if (g<0) g=0;
  if (b<0) b=0;

  analogWrite(red, r);
  analogWrite(green, g);
  analogWrite(blue, b);
}

