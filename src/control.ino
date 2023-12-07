/* This is the Arduino C++ script that runs on the ESP32 side.
The functions of this Arduino are as follows:
1. Define the output pins of ESP32.
2. Define motors to control with specific pins.
3. Control the AIN, BIN, PWMA, PWMB pins of H-bridges.
4. Change the values of PWM to vary motor speeds for different cases.
5. When Serial communication is available, switch to the state given by Raspberry Pi.
*/

#include <SparkFun_TB6612_4.h>
// define output pins
#define Ain1 32
#define Ain2 33
#define Bin1 26
#define Bin2 27

#define Ain3 23
#define Ain4 22
#define Bin3 19
#define Bin4 18

#define Ain5 17
#define Ain6 16
#define Bin5 0
#define Bin6 2

#define PWMA1 25
#define PWMB1 14
#define PWMA2 13
#define PWMB2 5
#define PWMA3 4
#define PWMB3 15

// define default values for constants
int speed = 200;
int flag = 0;

const int offset = 1;

bool COUNTERCLOCKWISE = true;

// define motors
Motor motor1 = Motor(Ain1, Ain2, PWMA1, offset); //back-right wheel
Motor motor2 = Motor(Bin1, Bin2, PWMB1, offset); //back-left wheel
Motor motor3 = Motor(Ain3, Ain4, PWMA2, offset); //front-right wheel
Motor motor4 = Motor(Bin3, Bin4, PWMB2, offset); //front-left wheel

Motor motor5 = Motor(Ain5, Ain6, PWMA3, offset); //motor 5 for robotic arm
Motor motor6 = Motor(Bin5, Bin6, PWMB3, offset); //motor 6 for robotic claw


void setup() {
  // set the speed of serial data transmission
  Serial.begin(115200);
  pinMode(Ain1, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(Bin2, OUTPUT);
  
  pinMode(Ain3, OUTPUT);
  pinMode(Ain4, OUTPUT);
  pinMode(Bin3, OUTPUT);
  pinMode(Bin4, OUTPUT);
  
  pinMode(Ain5, OUTPUT);
  pinMode(Ain6, OUTPUT);
  pinMode(Bin5, OUTPUT);
  pinMode(Bin6, OUTPUT);
}

void loop() {
  // establish Serial communication and print the received commands
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.print("mcu receive from pi: ");
    Serial.println(data);
    int state = data.toInt();
    // define states of motor's movement
    switch(state){
      case 0: //brake
        motor1.brake();
        motor2.brake();
        motor3.brake();
        motor4.brake();
        motor5.brake();
        motor6.brake();
         
        break;
        
      case 1: //forward
        motor1.brake();
        motor2.brake();
        motor3.brake();
        motor4.brake();
        motor5.brake();
        motor6.brake();

        motor1.drive(speed);
        motor2.drive(speed);
        motor3.drive(speed);
        motor4.drive(speed);
        
        break;
        
      case 2: //backward
        motor1.brake();
        motor2.brake();
        motor3.brake();
        motor4.brake();
        motor5.brake();
        motor6.brake();

        motor1.drive(-speed);
        motor2.drive(-speed);
        motor3.drive(-speed);
        motor4.drive(-speed);
        break;
        
      case 3: //forward left
        motor1.brake();
        motor2.brake();
        motor3.brake();
        motor4.brake();
        motor5.brake();
        motor6.brake();

         motor1.drive(255);
         motor3.drive(255);
//         motor2.drive(-155);
         motor4.drive(-155);
        
        if (flag == 1){
          delay(200);
          motor1.brake();
          motor2.brake();
          motor3.brake();
          motor4.brake();
          delay(100);
        }
              
        break;
        
      case 4: //forward right
        motor1.brake();
        motor2.brake();
        motor3.brake();
        motor4.brake();
        motor5.brake();
        motor6.brake();
        
         motor2.drive(255);
         motor4.drive(255);
//         motor1.drive(-155);
         motor3.drive(-155);
        
        if (flag == 1){
          delay(200);
          motor1.brake();
          motor2.brake();
          motor3.brake();
          motor4.brake();
          delay(100);
        }
        
        break;
        
      case 5://backward left
        motor1.brake();
        motor2.brake();
        motor3.brake();
        motor4.brake();
        motor5.brake();
        motor6.brake();
        
         motor1.drive(-255);
         motor3.drive(-255);
//         motor4.drive(155);
         motor2.drive(155);
        
        if (flag == 1){
          delay(200);
          motor1.brake();
          motor2.brake();
          motor3.brake();
          motor4.brake();
          delay(100);
        }

        break;

        
      case 6://backward right
        motor1.brake();
        motor2.brake();
        motor3.brake();
        motor4.brake();
        motor5.brake();
        motor6.brake();
        
        motor2.drive(-255);
        motor4.drive(-255);
//        motor3.drive(155);
        motor1.drive(155);

        if (flag == 1){
          delay(200);
          motor1.brake();
          motor2.brake();
          motor3.brake();
          motor4.brake();
          delay(100);
        }
        
        break;
        
        
      case 7: //hand
        motor1.brake();
        motor2.brake();
        motor3.brake();
        motor4.brake();
        
        motor5.brake();
        motor6.brake();
        motor5.drive(200);
        break;
        
      case 8: //hand
        motor1.brake();
        motor2.brake();
        motor3.brake();
        motor4.brake();
        
        motor5.brake();
        motor6.brake();
        motor5.drive(-200);
        break;
         
      case 9: //arm down
        motor1.brake();
        motor2.brake();
        motor3.brake();
        motor4.brake();
        motor5.brake();
        
        motor6.brake();
        motor6.drive(100);
        break;
        
      case 10: //arm up
        motor1.brake();
        motor2.brake();
        motor3.brake();
        motor4.brake();
        motor5.brake();
        
        motor6.brake();
        motor6.drive(-230);
        break;

      case 14: //speed up
        speed = 200;
        flag = 0;
        break;

      case 12: //speed down
        speed = 150;
        flag = 1;
        break;
      // default state that all the motors stand still 
      default:
        motor1.brake();
        motor2.brake();
        motor3.brake();
        motor4.brake();
        motor5.brake();
        motor6.brake();
        break;
        
    }
  }
}
