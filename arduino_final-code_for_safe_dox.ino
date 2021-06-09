#include <TM1637Display.h> //Arduino library for using tm1637


#define trig1 5       //trigger pin for ultrasonic sensor1
#define echo1 6       //echo pin for ultrasonic sensor 1
#define trig2 9      //trigger pin for ultrasonic sensor 2
#define echo2 10      //echo pin for ultrasonic sensor 2
#define lim_sw 7
#define uv_relay 8
#define rev_sw 11


#define stepper_led 4


#define CLK 2
#define DIO 3


TM1637Display display(CLK, DIO);



int k=1;
int i;
int h;
int t;



  

long t1;
long t2;

int d1;
int d2;


int chng=0;
int counter;
int c;

#define stp 12
#define dir 13
#define step_rev 105






void setup() {
  
  Serial.begin(9600);

  pinMode(dir, OUTPUT);
  pinMode(stp, OUTPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(lim_sw, INPUT_PULLUP);
  pinMode(uv_relay, OUTPUT);
  pinMode(rev_sw, INPUT);
  pinMode(stepper_led, OUTPUT);
  digitalWrite(uv_relay,HIGH);




/*____________________________________________________________
Code to activate and reset the display to the 2 minute timer
*/ 

      uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
    uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
    display.setBrightness(0x0f);

    display.setSegments(data);
    delay(100);
 
    display.showNumberDecEx(02, (0x80 >> k), true, 2);

    delay(1000);






}






void us1()   // function to call ultrasonic sensor 1 to receive essential data
{
  
  digitalWrite(trig1, HIGH);
  delayMicroseconds(2);
  digitalWrite(trig1, LOW);
  delayMicroseconds(10);

  t1=pulseIn(echo1, HIGH);

  d1= t1/29;

}



void us2()   // function to call ultrasonic sensor 2 to receive essential data
{

  digitalWrite(trig2, HIGH);
  delayMicroseconds(2);
  digitalWrite(trig2, LOW);
  delayMicroseconds(10);

  t2=pulseIn(echo2, HIGH);

  d2=t2/29;

}


void stepper_clk()  // function to rotate the stepper in clockwise direction
{ 
  digitalWrite(dir,LOW); 
  digitalWrite(stepper_led, HIGH);
 
  for(int a = 0; a < step_rev; a++)
  {
    digitalWrite(stp,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stp,LOW);
    delayMicroseconds(1000);

  }
  c=0;
  
}



void stepper_anticlk()   //  function to rotate the stepper in anticlockwise direction
{
  digitalWrite(dir, HIGH);

  for(int a = 0; a < step_rev; a++)
  {
    digitalWrite(stp,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stp,LOW); 
    delayMicroseconds(1000); 
  }

}



void turn_on()
{
  if(digitalRead(lim_sw)==0)
  {
    digitalWrite(uv_relay, HIGH);
  }
}





void loop() {

 for (i=30;i>=0;i--)
    {
      if(digitalRead(lim_sw)==0) // to check if the lid is closed and the continue
  {
    display.showNumberDec(i, true, 2, 2); 
    delay(1000);
    Serial.println("C is");
    Serial.println(digitalRead(rev_sw));
    digitalWrite(uv_relay, LOW);
   //starting both of the ultrasonic sensors
    us1();
    us2();
    Serial.println("D1");
    Serial.println(d1);
    Serial.println("D2");
    Serial.println(d2);






  


while(digitalRead(rev_sw)>0)  //to read switch for reversing the motion of paper
{
 digitalWrite(trig1, LOW);
 digitalWrite(echo1, LOW);
 digitalWrite(trig2, LOW);
 digitalWrite(echo2, LOW);

 stepper_anticlk();           //to reverse the direction of the paper moving

 c=1;
  }


{
      if((d1>=9) && (d2<8))
    {
//  Serial.println("Moving IN");
  stepper_clk();

    }


if((d1>=9) && (d2>=8))
{
    stepper_clk();
}



if((d2>=8) && (d1<9))
{
//  Serial.println("Moving OUT");
  stepper_clk();
  digitalWrite(stepper_led, HIGH);
}

digitalWrite(stepper_led, LOW);
}

}


    
    }







 
for(i=59; i>=0; i--) // to start the timer on display
{
  if(digitalRead(lim_sw)==0) // to check if the lid is closed and the continue
  {


//digitalWrite(stepper_led, LOW);

   display.showNumberDecEx(01, (0x80 >> k), true, 2);
   display.showNumberDec(i, true, 2, 2); 
   delay(1000);

    Serial.println("C is");
    Serial.println(digitalRead(rev_sw));
    digitalWrite(uv_relay, LOW);
   //starting both of the ultrasonic sensors
    us1();
    us2();
    Serial.println("D1");
    Serial.println(d1);
    Serial.println("D2");
    Serial.println(d2);






  


while(digitalRead(rev_sw)>0)  //to read switch for reversing the motion of paper
{
 digitalWrite(trig1, LOW);
 digitalWrite(echo1, LOW);
 digitalWrite(trig2, LOW);
 digitalWrite(echo2, LOW);

 stepper_anticlk();           //to reverse the direction of the paper moving

 c=1;
  }


{
      if((d1>=9) && (d2<8))
    {
//  Serial.println("Moving IN");
  stepper_clk();

    }


if((d1>=9) && (d2>=8))
{
    stepper_clk();
}



if((d2>=8) && (d1<9))
{
//  Serial.println("Moving OUT");
  stepper_clk();
  digitalWrite(stepper_led, HIGH);
}

digitalWrite(stepper_led, LOW);
}

}
  
}




for(i=59; i>=0; i--)
{
  if(digitalRead(lim_sw)==0)
  {



digitalWrite(stepper_led, LOW);


display.showNumberDecEx(00, (0x80 >> k), true, 2); // to start the last minute timer

    
  display.showNumberDec(i, true, 2, 2); 
  delay(1000);

    Serial.println("C is");
    Serial.println(digitalRead(rev_sw));
    digitalWrite(uv_relay, LOW);
    // again starting the ultrasonic sensors 1 and 2
    us1();  
    us2();
    Serial.println("D1");
    Serial.println(d1);
    Serial.println("D2");
    Serial.println(d2);






  


while(digitalRead(rev_sw)>0)    //to read switch for reversing the motion of paper
{
 digitalWrite(trig1, LOW);
 digitalWrite(echo1, LOW);
 digitalWrite(trig2, LOW);
 digitalWrite(echo2, LOW);

 stepper_anticlk();             //to reverse the direction of the paper moving

 c=1;



 

  }

//else
{
      if((d1>=9) && (d2<9))
    {
//  Serial.println("Moving IN");
  stepper_clk();
    }

if((d1>=9) && (d2>=9))
{
    stepper_clk();
}



if((d2>=9) && (d1<9))
{
//  Serial.println("Moving OUT");
  stepper_clk();
}
}

}
  
}

if(digitalRead(lim_sw)==1)
{
  digitalWrite(uv_relay, HIGH); // to turn of the ultraviolet light rays
    delay(100);
 
    display.showNumberDecEx(02, (0x80 >> k), true, 2);    // to display the 2 minute timer on hold when the lid is open

    display.showNumberDec(30, true, 2, 2);

  
}



    
  }
