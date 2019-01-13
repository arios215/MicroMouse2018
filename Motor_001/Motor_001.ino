/*
 * Motor Control
 * 
 * Current abilities:
 *  Speed
 *  Independent Wheel Turning
 *  Number of rotations
 */

#include <elapsedMillis.h>

//Pin Definitions
#define LIn1 A1     //Left Input 1 On Motor Driver (Left Side)
#define LIn2 A2     //Left Input 2 On MOtor Driver (Left Side)
#define LEnable 5   //Left Enable
#define LEA 2       //Left Encoder A
#define LEB A0      //Left Encoder B

#define RIn1 A3     //Right Input 3 On Motor Driver (Right Side)
#define RIn2 A4     //Right Input 4 On Motor Driver (Right Side)
#define REnable 6   //Right Enable
#define REA 3       //Right Encoder A
#define REB A5      //Right Encoder B

//Left Encoder
volatile int LEV;   //Left Encoder Value
bool LExit_Value;
elapsedMillis LExit_Time;

//Right Encoder
volatile int REV;   //Right Encoder Value
bool RExit_Value;
elapsedMillis RExit_Time;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Initialize baud rate to 9600

  //Input Pins
  pinMode(LIn1, OUTPUT);
  pinMode(LIn2, OUTPUT);
  pinMode(LEnable, OUTPUT);
  pinMode(RIn1, OUTPUT);
  pinMode(RIn2, OUTPUT);
  pinMode(REnable, OUTPUT);

  //Output Pins
  pinMode(LEA, INPUT);
  pinMode(LEB, INPUT);
  pinMode(REA, INPUT);
  pinMode(REB, INPUT);

  //Encoder
  attachInterrupt(digitalPinToInterrupt(LEA), LIF, RISING); //Inturupt
  attachInterrupt(digitalPinToInterrupt(REA), RIF, RISING); //Inturupt
  LEV = 0;
  LExit_Value = 0;
  LExit_Time = 0;
  REV = 0;
  RExit_Value = 0;
  RExit_Time = 0;


  RSPD(100);
  LSPD(100);  
  RET(-90);
  LET(-90);
  RET(90);
  LET(90);
  RSPD(255);
  LSPD(255);
  RET(1000);
  LET(1000);
  RET(-1000);
  LET(-1000);


}

void loop() {
  // put your main code here, to run repeatedly:

}

//Direction Functions
void FW( int RTurn_Amount)
{
  int LTurn_Amount = -1 * RTurn_Amount;
  while(1)
  {
    //Left
    if (LEV < LTurn_Amount)
    {
      LCW();
      LExit_Value = 0;
      LExit_Time = 0;
    }
    else if (LEV > LTurn_Amount)
    {
      LCCW();
      LExit_Value = 0;
      LExit_Time = 0;
    }
    else if (LEV == LTurn_Amount)
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

    //Right
    if (REV < RTurn_Amount)
    {
      RCW();
      RExit_Value = 0;
      RExit_Time = 0;
    }
    else if (REV > RTurn_Amount)
    {
      RCCW();
      RExit_Value = 0;
      RExit_Time = 0;
    }
    else if (REV == RTurn_Amount)
    {
      RSTP();
      if (RExit_Value = 0)
      {
        RExit_Time = 0;
        RExit_Value = 1;
      }
      else
      {
        if (RExit_Time < 500)
          continue;
        else
        {
          REV = 0;
          return;
        }
      }
    }
  }
  
}

void LSPD(int L_Enable_Value) //Left Speed, Enter Speed Between 50-255
{
 analogWrite(LEnable, L_Enable_Value);
}

void LET(int Turn_Amount)
/*Left Encoder Test
  Turns a certain amount, corrects it self, and waits for a certain amount of time and exits.
  Exit values will be 1 if LEV stays equaled to the Turn_Amount for the time set
  otherwise if it is not, LExit_Value will turn to a 0.
*/
{
  Turn_Amount = -1 * Turn_Amount;   //Making the turn amount negative for inverse wheel turning
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

void RSPD(int R_Enable_Value) //Right Speed, Enter Speed Between 50-255
{
 analogWrite(REnable, R_Enable_Value);
}

void RET(int Turn_Amount)  //Right Encoder Test
                           //Turns a certain amount, corrects it self, and waits for a certain amount of time and exits
{
  while (1)
  {
    if (REV < Turn_Amount)
    {
      RCW();
      RExit_Value = 0;
      RExit_Time = 0;
    }
    else if (REV > Turn_Amount)
    {
      RCCW();
      RExit_Value = 0;
      RExit_Time = 0;
    }
    else if (REV == Turn_Amount)
    {
      RSTP();
      if (RExit_Value = 0)
      {
        RExit_Time = 0;
        RExit_Value = 1;
      }
      else
      {
        if (RExit_Time < 500)
          continue;
        else
        {
          REV = 0;
          return;
        }
      }
    }
  }
}

void RIF()  //Right Inturrupt Function
{
  if (digitalRead(REB) == LOW)
    REV++;
  else
    REV--;
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

//Right Functions
void RCW()              //Right Clock Wise
{
  digitalWrite(RIn1, HIGH);
  digitalWrite(RIn2, LOW);
}
void RCCW()             //Right Counter Clock Wise
{
  digitalWrite(RIn1, LOW);
  digitalWrite(RIn2, HIGH);
}
void RSTP()             //Right Stop
{
  digitalWrite(RIn1, LOW);
  digitalWrite(RIn2, LOW);
}
