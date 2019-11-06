
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
 // while (!Serial) {
 ///   ; // wait for serial port to connect. Needed for native USB port only
 //   delay(10);
 // }
//  Serial.println( "hello");
  pwm.begin();
  pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates, sg90 runs at 50mhz
  delay(10);
}


/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void read_serial() {
  while (!Serial) return;
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      break;
    }
    else
      inputString += inChar;
  }
}

void loop() {
  // print the string when a newline arrives:
  read_serial();
  if (stringComplete) {
    main_work(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  else
    delay(10);
}

void main_work(String input) {
  
  int p=input.indexOf(' ');
  if(p>0)
  {
   String sub1=input.substring(0,p);
   String sub2="";
   String sub3="";
   
   int p2=input.indexOf(' ',p+1);
   bool input_default=false;
   if(p2==-1)
   {
    Serial.println( "wrong parameters count");
    return;
    
    //sub2=sub1;
    //sub3=input.substring(p+1);
    //sub1="d";
    //input_default=true;
   }
   else
   {
    sub2=input.substring(p+1,p2);
    sub3=input.substring(p2+1);
   }
   Serial.println("input \""+sub1+"\" \""+sub2+"\" \""+sub3+"\" "); 

   bool servo_absolute=sub1.equals("a");
   bool servo_inverse=sub1.equals("i"); //    bool servo_inverse=!sub1.equals("d");
   
   uint8_t servo_n=sub2.toInt();
   double servo_degree=sub3.toDouble();
 

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
// Range of Micro servo Lofty Ambition SG90: 96-496
// Range of Micro servo Tower Pro SG90: 200-1000
// Range of FITEC FS5106B: (180)200-550(570) = 180°
   int servoMin; // this is the 'minimum' pulse length count (out of 4096)
   int servoMax;  // this is the 'maximum' pulse length count (out of 4096)

   // test servo by typing in terminal various numbers "a 0 90" or "a 0 500" and press enter.
   // use servo by typing in terminal various numbers "d 0 60" for 60 degree
   // use servo by typing in terminal various numbers "i 0 60" for 60 degree inverse
   
   int servo_mapped_value_in_range; 
   
   if(servo_n==0)
   {
    servoMin=96; servoMax=466;
    if(input_default) servo_inverse=true; 
   }
   else
   {
    servoMin=96; servoMax=466;
    if(input_default) servo_inverse=false;
   }

   if(servo_absolute)
     servo_mapped_value_in_range=servo_degree;
   else
   {
    if(!servo_inverse)
      servo_mapped_value_in_range=map(servo_degree, 0, 179, servoMin, servoMax);
    else
      servo_mapped_value_in_range=map(servo_degree, 0, 179, servoMax, servoMin);
   }   
   
   Serial.println( "s:"+String(servo_n)+" d:"+String(servo_degree)+" a:"+String(servo_absolute?1:0)+"  i:"+String(servo_inverse?1:0)+" m:"+String(servo_mapped_value_in_range));
   pwm.setPWM(servo_n, 0, servo_mapped_value_in_range);

   

  }
  else{
   Serial.println( "syntax: <a=absolute|d=degree|i=inverse degree> <servo number> <degree or absolute>");
   Serial.println( "example: d 0 90");
  }
}

