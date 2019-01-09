

/////////////////
//  |LED/GRND   | LEFT/  
//  |           |
//  ------------
// | Blue/Black |
//  ------------
//  |           |
//  |           |

//adsfkjhadkjfhadsljf
int led = 5;
int led2 = 2;



int opt1;
int opt_sensor1;

int opt2;
int opt_sensor2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(led2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  opt1 = analogRead(A0);
  opt_sensor1 = map(opt1, 80, 2000, 0, 555);

   analogWrite(led,opt_sensor1);
  Serial.println(opt1);

  // Second led light up Sensor 2

    opt2 = analogRead(A1);
  opt_sensor2 = map(opt2, 80, 2000, 0, 555);
                                                                                        
   analogWrite(led2,opt_sensor2);
  Serial.println(opt2);

//  if(opt_sensor1 < 910)
//  {
//    analogWrite(led2,opt_sensor1);
//    Serial.println(opt1);
//  }
  
}
