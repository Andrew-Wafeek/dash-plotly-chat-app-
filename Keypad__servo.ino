#include <Keypad.h>
#include <Servo.h>


const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

Servo myservo_1;  // create servo object to control a servo
Servo myservo_2;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position

void setup(){
    pinMode(interruptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin), stop, CHANGE);
  Serial.begin(9600);
   myservo_1.attach(9);  // attaches the servo on pin 9 to the servo object
   myservo_2.attach(10);  // attaches the servo on pin 9 to the servo object
  myservo_1.write(0);              // tell servo to go to position in variable 'pos'
    myservo_2.write(0);
}

void loop(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
  }
   
       switch(key)
       {
          case '1':
            myservo_1.write(60);              // tell servo to go to position in variable 'pos'
            pos=60;
            delay(15); break;
          
           case '2':
           if(pos==60)
           { myservo_1.write(120);              // tell servo to go to position in variable 'pos'
              pos=120;
              delay(15); 
           }break;
          
            case '3':
            if(pos==120)
            { myservo_1.write(180);              // tell servo to go to position in variable 'pos'
              pos=180;
              delay(15);} break;

          case '4':
            myservo_2.write(60);              // tell servo to go to position in variable 'pos'
            pos=60;
            delay(15); break;
          
           case '5':
           if(pos==60)
           { myservo_2.write(120);              // tell servo to go to position in variable 'pos'
             pos=120;
             delay(15); }break;
           
            case '6':
            if(pos==120)
            { myservo_2.write(180);              // tell servo to go to position in variable 'pos'
              pos=180;
              delay(15); }  break;          

            case '0':
              {myservo_1.write(0);              // tell servo to go to position in variable 'pos'
              myservo_2.write(0);              // tell servo to go to position in variable 'pos'
              pos=0;
              } break;  
            
       }          


       void stop() {
              state = !state;
            }
}
