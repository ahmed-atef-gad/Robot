
 #include <SPI.h> // Call SPI Library 


// #include <nRF24L01.h> // Call NRE Version Library
// #include <RF24.h> // RF24 Header File

// /*-----( Declare Constants and Pin Numbers )-----*/
// #define CE_PIN   9
// #define CSN_PIN 10
#define rxd 0
#define txd 1

#define motor_R1 2  //Right motor pole 1
#define motor_R2 3  //Right motor pole 2
#define motor_L1 4  //left motor pole 1
#define motor_L2 7  //left motor pole 2
#define Rmotor_vel 5  //Right motor speed
#define Lmotor_vel 6  //Right motor speed
//#define center_ir 11     //SS3
#define LEFT_IR A1       //ss2
#define RIGHT_IR A2      //ss4
#define extLEFT_IR A0    //ss1
#define extRIGHT_IR A3   //ss5

// NOTE: the "LL" at the end of the constant is "LongLong" type
//const uint64_t pipe[2] = {0xE8E8F0F0E1LL, 0xE8E8F0F0F2LL}; // Define the transmitter pipe as Pipe[1] and Receiver Pipe as Pipe[0] Unlike the Transceiver 1// you can Select Any 40 bit Address Instead of "E8E8F0F0E1"and put LL in the end of the Address


/*-----( Declare objects )-----*/
//RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
/*-----( Declare Variables )-----*/

//int prev,time1;
//float timeStep = 0.01;
//float yaw = 0; 
int left_ir,right_ir,extleft_ir,extright_ir;//Define variables which used to store digital inputs values 
int Intersection_mask=0,start_mask=0,mark1=0,mark2=0,serial_mask=0; //int mask3=0;
int x=0,y=0,ox=0,oy=0,nx=0,ny=0,pos=0;
int pxy[2],prev[2];
//boolean tx_mode=false;
int income[2];
int state=0;//orientation state (1=Forward, 2=Reverse, 3=Right, 4=Left)Zero is initial state
void setup() 
{
  Serial.begin(9600);
  Serial.begin(9600);
  // radio.begin();//Intializing NRF24L01 Module
  // radio.openWritingPipe(pipe[0]);// For Transmitting Operation, Must OpenWritingPipe
  // radio.openReadingPipe(1,pipe[1]); //For Receiving Operation
  // radio.startListening();
  pinMode(motor_R1,OUTPUT);
  pinMode(motor_R2,OUTPUT);
  pinMode(motor_L1,OUTPUT);
  pinMode(motor_L2,OUTPUT);
  pinMode(Rmotor_vel,OUTPUT);
  pinMode(Lmotor_vel,OUTPUT);
  //pinMode(center_ir,INPUT);
  pinMode(LEFT_IR,INPUT);
  pinMode(RIGHT_IR,INPUT);
  pinMode(extLEFT_IR,INPUT);
  pinMode(extRIGHT_IR,INPUT);
  analogWrite(Rmotor_vel,100);
  analogWrite(Lmotor_vel,100);
  Serial.println("Initializing>>>>");
}
void loop()
{ 

   if(serial_mask==0)
   {
    //  while(!radio.available());
    //  radio.read( income, sizeof(income) ); 
    //  radio.stopListening();
    //  serial_mask=1;
    while(!Serial.available());
    if (Serial.available() >= 2 * sizeof(int)) {
      Serial.readBytes((char *)income, 2 * sizeof(int));
    }
    serial_mask=1;
   }
     /*
     Serial.print("(");
     Serial.print(income[0]);
     Serial.print(",");
     Serial.print(income[1]);
     Serial.print(")");
     Serial.println();
     */
     getxy();
     calc();
}

void inertia()
{
  analogWrite(Rmotor_vel,100);
  analogWrite(Lmotor_vel,100);
  digitalWrite(motor_R1,LOW);
  digitalWrite(motor_R2,HIGH);
  digitalWrite(motor_L1,LOW);
  digitalWrite(motor_L2,HIGH);
  delay(100);
}
void forward()
{
  analogWrite(Rmotor_vel,85);
  analogWrite(Lmotor_vel,85);
  digitalWrite(motor_R1,LOW);
  digitalWrite(motor_R2,HIGH);
  digitalWrite(motor_L1,LOW);
  digitalWrite(motor_L2,HIGH);
  //delay(200);
}

void reverse()
{
  digitalWrite(motor_R1,HIGH);
  digitalWrite(motor_R2,LOW);
  digitalWrite(motor_L1,HIGH);
  digitalWrite(motor_L2,LOW);
}

void Tleft()
{
  analogWrite(Rmotor_vel,130);
  analogWrite(Lmotor_vel,110);
  digitalWrite(motor_R1,LOW);
  digitalWrite(motor_R2,HIGH);
  digitalWrite(motor_L1,HIGH);
  digitalWrite(motor_L2,LOW);
  //delay(100);
}
void Tright()
{
  analogWrite(Rmotor_vel,110);
  analogWrite(Lmotor_vel,130);
  digitalWrite(motor_R1,HIGH);
  digitalWrite(motor_R2,LOW);
  digitalWrite(motor_L1,LOW);
  digitalWrite(motor_L2,HIGH);
  //delay(100);
}
void off()
{
  digitalWrite(motor_R1,LOW);
  digitalWrite(motor_R2,LOW);
  digitalWrite(motor_L1,LOW);
  digitalWrite(motor_L2,LOW);
}
void Tleft90()
{
  forward();
  //delay(10);
  off();
  delay(200);
  analogWrite(Rmotor_vel,120);
  analogWrite(Lmotor_vel,120);
  digitalWrite(motor_R1,LOW);
  digitalWrite(motor_R2,HIGH);
  digitalWrite(motor_L1,HIGH);
  digitalWrite(motor_L2,LOW);
  delay(730);
}
void Tright90()
{
  forward();
  //delay(30);
  off();
  delay(200);
  analogWrite(Rmotor_vel,110);
  analogWrite(Lmotor_vel,110);
  digitalWrite(motor_R1,HIGH);
  digitalWrite(motor_R2,LOW);
  digitalWrite(motor_L1,LOW);
  digitalWrite(motor_L2,HIGH);
  delay(720);  
}

/*void Tleft180()
{
  analogWrite(Rmotor_vel,170);
  analogWrite(Lmotor_vel,170);
  digitalWrite(motor_R1,LOW);
  digitalWrite(motor_R2,HIGH);
  digitalWrite(motor_L1,HIGH);
  digitalWrite(motor_L2,LOW);
  delay(1100);
}*/

void Tright180()
{
  analogWrite(Rmotor_vel,120);
  analogWrite(Lmotor_vel,120);
  digitalWrite(motor_R1,HIGH);
  digitalWrite(motor_R2,LOW);
  digitalWrite(motor_L1,LOW);
  digitalWrite(motor_L2,HIGH);
  delay(1000);
}

/*void Tright1()
{
  analogWrite(ena,160);
  analogWrite(enb,160);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(350);
}

void Tleft1()
{
  analogWrite(ena,170);
  analogWrite(enb,170);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(350);
}*/

void getvalues()
{
  // If value is equal to 0 means Black and other 1 means White
  extleft_ir=digitalRead(extLEFT_IR);
  left_ir=digitalRead(LEFT_IR);
  //c=digitalRead(center_ir);
  right_ir=digitalRead(RIGHT_IR);
  extright_ir=digitalRead(extRIGHT_IR);  
}

void compare()
{
    if(extleft_ir==1&&left_ir==1&&right_ir==1&&extright_ir==1)
  {
    
    if(start_mask==0)
    {
      inertia();
      start_mask=1;
    }
    forward();
  }
  if((extleft_ir==1&&left_ir==0&&right_ir==1&&extright_ir==1)||(extleft_ir==0&&left_ir==1&&right_ir==1&&extright_ir==1))
  {
    Tleft();
  }
  if((extleft_ir==1&&left_ir==1&&right_ir==0&&extright_ir==1)||(extleft_ir==1&&left_ir==1&&right_ir==1&&extright_ir==0))
  {
    Tright();
  }
  
  if(extleft_ir==0&&left_ir==0&&right_ir==0&&extright_ir==0&&Intersection_mask==0)
  {
     off();
     delay(100);
     Intersection_mask=1;
     if((y>0&&x<0&&mark1==1)||(y<0&&x>0&&mark1==1))
     {
      pos--;
     }
     else if((x<0&&y<0&&mark2==1)||(y<0&&x==0)||(x<0&&y==0))
     {
      pos--;
     }else pos++;
     
    //inertia();
    forward();
  }
  if(extleft_ir==1&&extright_ir==1)
  {
    Intersection_mask=0;
  }
}

void getxy()
{
  nx=income[0];
  ny=income[1];
}
void calc()
{
  x=nx-ox;
  y=ny-oy;
  if(x>0&&y>0)
  {
    moveY();
    state=3;
    orientation();
    moveX();
    state=4;
    orientation();
    ox=nx;
    oy=ny;
    //radio.startListening();
    serial_mask=0;
    return;
    
  }else if(x<0&&y<0)
  {
    mark2=1;
    getvalues();
    state=2;
    orientation();
    moveY_neg();
    state=3;
    orientation();
    moveX_neg();
    state=3;
    orientation();
    mark2=0;
    ox=nx;
    oy=ny;
    //radio.startListening();
    serial_mask=0;
    return;
  }else if(x==0&&y>0)
  {
    getvalues();
    moveY();
    ox=nx;
    oy=ny;
    //radio.startListening();
    serial_mask=0;
    return;
  }else if(x==0&&y<0)
  {
    getvalues();
    state=2;
    orientation();
    moveY_neg();
    state=2;
    orientation();
    ox=nx;
    oy=ny;
    //radio.startListening();
    serial_mask=0;
    return;
  }else if(y==0&&x>0)
  {
    getvalues();
    state=3;
    orientation();
    moveX();
    state=4;
    orientation();
    ox=nx;
    oy=ny;
    //radio.startListening();
    serial_mask=0;
    return;
  }else if(y==0&&x<0)
  {
    getvalues();
    state=4;
    orientation();
    moveX_neg();
    state=3;
    orientation();
    ox=nx;
    oy=ny;
    //radio.startListening();
    serial_mask=0;
    return;
  }else if(x>0&&y<0)
  {
    getvalues();
    state=3;
    orientation();
    moveX();
    state=3;
    orientation();
    mark1=1;
    moveY_neg();
    state=2;
    orientation();
    mark1=0;
    ox=nx;
    oy=ny;
    //radio.startListening();
    serial_mask=0;
    return;
  }else if(x<0&&y>0)
  {
    getvalues();
    moveY();
    state=4;
    orientation();
    mark1=1;
    moveX_neg();
    state=3;
    orientation();
    mark1=0;
    ox=nx;
    oy=ny;
    //radio.startListening();
    serial_mask=0;
    return;
  }
  
}

void orientation()
{
  if (state==2)
  {//reverse Orientation
    Tright180();
    off();
    state=0;
  }else if(state==3)
  {
    //inertia();
    Tright90();
    off();
    state=0;
  }else if(state==4)
  {
    //inertia();
    Tleft90();
    off();
    state=0;
  }
}

void moveY()
{
  while(true)
  {
    pxy[1]=oy+pos;
    if(pxy[1]!=prev[1])
    {
      //radio.write(pxy,sizeof(pxy));
      Serial.write((uint8_t *)income, 2 * sizeof(int));
    }
    prev[1]=pxy[1];
    if(y > pos)
    {
      getvalues();
      compare();
    }
    else if(y == pos)
    {
      off();
      pos = 0;
      break;
    }
  }
  pos = 0;
}

void moveX()
{
  while(true)
  {
    pxy[0]=ox+pos;
    if (pxy[0] != prev[0])
    {
      //radio.write(pxy, sizeof(pxy));
      Serial.write((uint8_t *)income, 2 * sizeof(int));
    }
    prev[0] = pxy[0];
    if(x > pos)
    {
      getvalues();
      compare();
    }
    else if(x == pos)
    {
      off();
      pos = 0;
      break;
    }
  }
  pos = 0;
}

void moveY_neg()
{
  while(true)
  {
    pxy[1]=pos+oy;
    if(pxy[1]!=prev[1])
    {
      //radio.write(pxy,sizeof(pxy));
      Serial.write((uint8_t *)income, 2 * sizeof(int));
    }
    prev[1]=pxy[1];
    if(y < pos)
    {
      getvalues();
      compare();
    }
    else if(y == pos)
    {
      off();
      pos = 0;
      break;
    }
  }
  pos = 0;
}

void moveX_neg()
{
  while(true)
  {
    pxy[0]=pos+ox;
    if(pxy[0]!=prev[0])
    {
      //radio.write(pxy,sizeof(pxy));
      Serial.write((uint8_t *)income, 2 * sizeof(int));
    }
    prev[0]=pxy[0];
    if(x < pos)
    {
      getvalues();
      compare();
    }
    else if(x == pos)
    {
      off();
      pos = 0;
      break;
    }
  }
  pos = 0;
}