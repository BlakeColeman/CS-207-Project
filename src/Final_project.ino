#include <IRremote.h>

const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
float curButton = HIGH;
float lastButton = HIGH;
int potValue;
unsigned long previousMillis = 0;
unsigned long currentMillis = millis();
const int potPin = A1;
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;
const int buttonPin = 4;
float hue = 0, s = 1, v = 1;
float r,g,b;
int maxTime = 100;
int minTime = 10;
bool off = true;

void setup() 
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinSetup();
}

void loop() {
  RemoteButtons();
  button();
  if (off != true)
  {
    currentMillis = millis();
    if (currentMillis - previousMillis >= getDelayFromPot()) 
    {
    RemoteButtons();
    LightOn();
    }
  }
  else
  {
    analogWrite(redPin, 0);
    analogWrite(greenPin,0);
    analogWrite(bluePin,0);
  }
}

int getDelayFromPot() 
{
  potValue = analogRead(potPin);
  int delayTime = potValue / 1023.0 * (maxTime - minTime) + minTime;
  return delayTime;
}

void pinSetup()
{
  pinMode(potPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void RemoteButtons()
{
   if (irrecv.decode(&results))
      {
        Serial.println(hue);
        Serial.println(results.value, HEX);
        irrecv.resume();
      switch(results.value){
          case 0xFFB04F:
          Serial.println("Power");
          if (off == true)
          {
            off=false;
          }
          else
          {
            off=true;
          }
          break;
          case 0xFF32CD:
          Serial.println("Button1");
          hue=100;
          break;
          case 0xFF708F:
          Serial.println("Button2");
          hue=200;
          break;
          case 0xFFB24D:
          Serial.println("Button3");
          hue=300;
          break;
      }
    }      
  }

void button()
{
  lastButton = curButton;
  curButton = digitalRead(buttonPin);
  if (lastButton == LOW && curButton == HIGH)
  {
    if (off == true)
    {
      off = false;
    }
    else
    {
      off = true;
      //Serial.println("Turning OFF");
    }
  }
}

void hsv2rgb(float h, float s, float v, float &r, float &g, float &b)
{
  v = constrain(v, 0, 1);
  s = constrain(s, 0, 1);
  float c = v*s;
  float hprime = h/60.0f;
  float x = c * ( 1 - abs(hprime - ((int)hprime/2)*2 - 1));
  if (h < 0 || h > 360)
  {
    r = g = b = 0;
  }
  else if ( 0 <= hprime && hprime < 1)
  {
    r = c;
    g = x;
    b = 0;
  }
    else if ( 1 <= hprime && hprime < 2)
  {
    r = x;
    g = c;
    b = 0;
  }
    else if ( 2 <= hprime && hprime < 3)
  {
    r = 0;
    g = c;
    b = x;
  }
    else if ( 3 <= hprime && hprime < 4)
  {
    r = 0;
    g = x;
    b = c;
  }
    else if ( 4 <= hprime && hprime < 5)
  {
    r = x;
    g = 0;
    b = c;
  }
    else if ( 5 <= hprime && hprime < 6)
  {
    r = c;
    g = 0;
    b = x;
  } 
  float m = v - c;
  r += m;
  g += m;
  b += m;
  r *= 255;
  g *= 255;
  b *= 255;
}

void LightOn()
{
    previousMillis = currentMillis;
    hue++;
    if (hue == 110)
    {
      hue = 120;
    }
    if (hue == 230)
    {
       hue = 250;
    }
    //make hue wrap around the color wheel
    if (hue < 0 || hue > 359)
    {
     hue = 0;
    }
    hsv2rgb(hue,s,v,r,g,b);  
    //write the color to the RGB LED
    analogWrite(redPin, r);
    analogWrite(greenPin, g);
    analogWrite(bluePin, b);
    }
