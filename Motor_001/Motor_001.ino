#include <elapsedMillis.h>


#define LIn1 A1      //Left Input 1
#define LIn2 A2      //Left Input 2
#define LEnable 5  //Left Enable
#define LEA 2       //Left Encoder A
#define LEB A0      //Left Encoder B

volatile int LEV;   //Left Encoder Value
bool LExit_Value;
elapsedMillis LExit_Time;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Initialize baud rate to 9600

  //Input Pins
  pinMode(LIn1, OUTPUT);
  pinMode(LIn2, OUTPUT);
  pinMode(LEnable, OUTPUT);

  //Output Pins
  pinMode(LEA, INPUT);
  pinMode(LEB, INPUT);

  //Encoder
  attachInterrupt(digitalPinToInterrupt(LEA), LIF, RISING); //Inturupt
  LEV = 0;
  LExit_Value = 0;
  LExit_Time = 0;

  //Left Enable
  digitalWrite(LEnable, HIGH);

  LSPD(50);
  LET(-90);
  LET(90);
  LSPD(200);
  LET(1000);
  LET(-1000);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void LSPD(int L_Enable_Value) //Left Speed, Enter Speed Between 50-255
{
 analogWrite(LEnable, L_Enable_Value);
}

void LET(int Turn_Amount)  //Left Encoder Test
                           //Turns a certain amount, corrects it self, and waits for a certain amount of time and exits
{
  while (1)
  {
    if (LEV < Turn_Amount)
    {
      LCW();
      LExit_Value = 0;
      LExit_Time = 0;
    }
    else if (LEV > Turn_Amount)
    {
      LCCW();
      LExit_Value = 0;
      LExit_Time = 0;
    }
    else if (LEV == Turn_Amount)
    {
      LSTP();
      if (LExit_Value = 0)
      {
        LExit_Time = 0;
        LExit_Value = 1;
      }
      else
      {
        if (LExit_Time < 500)
          continue;
        else
        {
          LEV = 0;
          return;
        }
      }
    }
  }
}

void LIF()  //Left Inturrupt Function
{
  if (digitalRead(LEB) == LOW)
    LEV++;
  else
    LEV--;
}

////Turning Fucntions
//void LT() //Left Turn
//{
//  LCCW();
//  RCW();
//}
//void RT() //Right Turn
//{
//  RCCW();
//  LCW();
//}
//void FW() //Foward
//{
//  LCW();
//  RCW();
//}
//void BW() //Backwards
//{
//  LCCW();
//  RCCW();
//}
//void STP() //Stop
//{
//  LSTP();
//  RSTP();
//}

//Wheel Functions

//Left Functions
void LCW()               //Left Clock Wise
{
  digitalWrite(LIn1, HIGH);
  digitalWrite(LIn2, LOW);
}
void LCCW()              //Left Counter Clock Wise
{
  digitalWrite(LIn1, LOW);
  digitalWrite(LIn2, HIGH);
}
void LSTP()              //Left Stop
{
  digitalWrite(LIn1, LOW);
  digitalWrite(LIn2, LOW);
}

////Right Functions
//void RCW()              //Right Clock Wise
//{
//  digitalWrite(D3, HIGH);
//  digitalWrite(D4, LOW);
//}
//void RCCW()             //Right Counter Clock Wise
//{
//  digitalWrite(D3, LOW);
//  digitalWrite(D4, HIGH);
//}
//void RSTP()             //Right Stop
//{
//  digitalWrite(D3, LOW);
//  digitalWrite(D4, LOW);
//}


