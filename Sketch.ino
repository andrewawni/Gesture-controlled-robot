#include <Wire.h>
#include <Servo.h>
#include <MPU6050.h>


//initialize the sensor
MPU6050 sensor ;            
int16_t ax, ay, az ;
int16_t gx, gy, gz;
 

//initialize the two servo motors
Servo servoV;
Servo servoH; 

const int servoVpin = 6;
const int servoHpin = 10;


//initialize the two DC motors with the drive


int enB = 3;
//in3 controls +ve pole of R motor and -ve pole of L motor
int in3 = 5;
//in4 controls -ve pole of R motor and +ve pole of L motor
int in4 = 4;


//initialize the switch
const int buttonPin = 12;
int buttonState = 0;

void setup()
{
  
  Wire.begin ( );
  Serial.begin(9600);
  sensor.initialize( );
  
 
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //pinMode(buttonPin, INPUT);

  servoV.attach(servoVpin);
  servoH.attach(servoHpin);
}


  
  

void loop()
{
    //getting the accelerometer reading in x and y axes
    sensor.getMotion6 (&ax, &ay, &az, &gx, &gy, &gz);
    ax = map (ax, -17000, 17000, 0, 180) ;
    ay = map (ay, -17000, 17000, 0, 180) ;
    
    //if the button is on, it controls the car
    //if the button is off, it controls the arm

  buttonState = digitalRead(buttonPin);

   if(buttonState == HIGH)
   {
     Serial.println("ON");
      //ON

      if(ay<110 && ay>70)
        {
          digitalWrite(in3,  LOW);
          digitalWrite(in4, LOW);
         
          
        }
         else if(ay<=70 && ay >=0)
        {
          //move forward

          digitalWrite(in3, HIGH);
          digitalWrite(in4, LOW);
          
          //digitalWrite(in1, HIGH);
        //  digitalWrite(in2, LOW);
        }
        else if(ay<=180 && ay >=110)
        {
          //move backward
          digitalWrite(in3, LOW);
          digitalWrite(in4, HIGH);
         // digitalWrite(in1, LOW);
         // digitalWrite(in2, HIGH);
        }

     
        analogWrite(enB, 150);
      
   }
    else 
   {
     //OFF
      Serial.println("OFF");
   
   
      if(ax>=110 || ax<=70)
      {
        servoH.write(ax);
      }
      if(ay>=110 || ay<=70)
      {
        servoV.write(ay);
      }

    }
      


}





