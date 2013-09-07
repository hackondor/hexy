#include <Servo.h>

Servo frontLeftFootServo;
Servo frontLeftThighServo;
Servo frontLeftHipServo;
Servo frontRightFootServo;
Servo frontRightThighServo;
Servo frontRightHipServo;
Servo middleLeftFootServo;
Servo middleLeftThighServo;
Servo middleLeftHipServo;
Servo middleRightFootServo;
Servo middleRightThighServo;
Servo middleRightHipServo;
Servo backLeftFootServo;
Servo backLeftThighServo;
Servo backLeftHipServo;
Servo backRightFootServo;
Servo backRightThighServo;
Servo backRightHipServo;

int frontLeftFootServoPin = 49;
int frontLeftThighServoPin = 51;
int frontLeftHipServoPin = 53;
int frontRightFootServoPin = 48;
int frontRightThighServoPin = 50;
int frontRightHipServoPin = 52;
int middleLeftFootServoPin = 47;
int middleLeftThighServoPin = 45;
int middleLeftHipServoPin = 43;
int middleRightFootServoPin = 46;
int middleRightThighServoPin = 44;
int middleRightHipServoPin = 42;
int backLeftFootServoPin = 41;
int backLeftThighServoPin = 39;
int backLeftHipServoPin = 37;
int backRightFootServoPin = 40;
int backRightThighServoPin = 38;
int backRightHipServoPin = 36;

int pingPin = 8;
long duration;
long cm;
long distance;
int dangerDistance = 30;

int distanceLeft;
int distanceCenter;
int distanceRight;
int bestDirection;

int walkForwardSequence[11][3] = 
{
  { 1700, 1700, 1700 },                                        // First Tripod of Thighs Up to the Horizontal Position                                                #1 - 0
  { 1850, 1150, 1850 },                                        // First Tripod of Hips Forward                                                                        #2 - 1 
  { 1100, 1100, 1100 },                                        // First Tripod of Thighs Down                                                                         #3 - 2
  { 1700, 1700, 1700 },                                        // Second Tripod of Thighs Up to Horizontal Postion (reduces friction for next hip move)               #1 - 0
  { 1150, 1500, 1150 },                                        // First Tripod of Hips Back to Neutral                                                                #4 - 3
  { 1150, 1850, 1150 },                                        // Second Tripod of Hips Forward                                                                       #2 - 1  
  { 1100, 1100, 1100 },                                        // Second Tripod of Thighs Down                                                                        #3 - 2
  { 1700, 1700, 1700 },                                        // First Tripod of Thighs up to the Horizontal Postion (reduces friction for next hip move)            #1 - 0
  { 1850, 1150, 1850 },                                        // Second Tripod of Hips back to Neutral                                                               #4 - 3
  { 1100, 1100, 1100 },                                        // First Tripod of Thighs Down                                                                         #3 - 2
  { 2300, 2300, 2300 }                                         // Use this one for the feet                                                                           #5 - 4
};

int walkBackwardSequence[11][3] = 
{
  { 1700, 1700, 1700 },
  { 1150, 1850, 1150 },
  { 1100, 1100, 1100 },
  { 1700, 1700, 1700 },
  { 1850, 1150, 1850 },
  { 1850, 1150, 1850 },
  { 1100, 1100, 1100 },
  { 1700, 1700, 1700 },
  { 1150, 1850, 1150 },
  { 1100, 1100, 1100 },
  { 2300, 2300, 2300 }                                     
};

int rotateRightSequence[11][3] = 
{
  { 1700, 1700, 1700 },                                        // First Tripod of Thighs Up to the Horizontal Position
  { 1850, 1850, 1850 },                                        // First Tripod of Hips Forward
  { 1100, 1100, 1100 },                                        // First Tripod of Thighs Down
  { 1700, 1700, 1700 },                                        // Second Tripod of Thighs Up to Horizontal Postion (reduces friction for next hip move)
  { 1150, 1150, 1150 },                                        // First Tripod of Hips Back to Neutral
  { 1150, 1150, 1150 },                                        // Second Tripod of Hips Forward                                       
  { 1100, 1100, 1100 },                                        // Second Tripod of Thighs Down
  { 1700, 1700, 1700 },                                        // First Tripod of Thighs up to the Horizontal Postion (reduces friction for next hip move)
  { 1850, 1850, 1850 },                                        // Second Tripod of Hips back to Neutral
  { 1100, 1100, 1100 },                                        // First Tripod of Thighs Down
  { 2300, 2300, 2300 }                                         // Use this one for the feet   
};

int rotateLeftSequence[11][3] = 
{
  { 1700, 1700, 1700 },                                        // First Tripod of Thighs Up to the Horizontal Position
  { 1150, 1150, 1150 },                                        // First Tripod of Hips Forward
  { 1100, 1100, 1100 },                                        // First Tripod of Thighs Down
  { 1700, 1700, 1700 },                                        // Second Tripod of Thighs Up to Horizontal Postion (reduces friction for next hip move)
  { 1850, 1850, 1850 },                                        // First Tripod of Hips Back to Neutral
  { 1850, 1850, 1850 },                                        // Second Tripod of Hips Forward                                       
  { 1100, 1100, 1100 },                                        // Second Tripod of Thighs Down
  { 1700, 1700, 1700 },                                        // First Tripod of Thighs up to the Horizontal Postion (reduces friction for next hip move)
  { 1150, 1150, 1150 },                                        // Second Tripod of Hips back to Neutral
  { 1100, 1100, 1100 },                                        // First Tripod of Thighs Down
  { 2300, 2300, 2300 }                                         // Use this one for the feet   
};


void setup()
{
  // Serial.begin(9600);
  
  pinMode(pingPin, OUTPUT);

  frontLeftFootServo.attach(frontLeftFootServoPin, 700, 2300);
  frontLeftThighServo.attach(frontLeftThighServoPin, 700, 2300);
  frontLeftHipServo.attach(frontLeftHipServoPin, 700, 2300);
  frontRightFootServo.attach(frontRightFootServoPin, 700, 2300);
  frontRightThighServo.attach(frontRightThighServoPin, 700, 2300);
  frontRightHipServo.attach(frontRightHipServoPin, 700, 2300);
  middleLeftFootServo.attach(middleLeftFootServoPin, 700, 2300);
  middleLeftThighServo.attach(middleLeftThighServoPin, 700, 2300);
  middleLeftHipServo.attach(middleLeftHipServoPin, 700, 2300);
  middleRightFootServo.attach(middleRightFootServoPin, 700, 2300);
  middleRightThighServo.attach(middleRightThighServoPin, 700, 2300);
  middleRightHipServo.attach(middleRightHipServoPin, 700, 2300);
  backLeftFootServo.attach(backLeftFootServoPin, 700, 2300);
  backLeftThighServo.attach(backLeftThighServoPin, 700, 2300);
  backLeftHipServo.attach(backLeftHipServoPin, 700, 2300);
  backRightFootServo.attach(backRightFootServoPin, 700, 2300);
  backRightThighServo.attach(backRightThighServoPin, 700, 2300);
  backRightHipServo.attach(backRightHipServoPin, 700, 2300);

  // kneelDown(1500);                                             // In the presence of greatness, the humble can only bow
  // servoCheck(1000);                                            // Move the Servo's through the full range of motion
  
  setZero();                                                   // Useful for attaching Servo's at the zero position
  delay(1000);
  firstPosition();                                             // Set the Hips and feet to 1500 and the Thighs to 1900
  delay(1000);
  standUp(500);                                                // Get the legs in the proper positions and then wiggle a bit
}


void loop()
{
  bestDirection = whichWayToGo();

  switch(bestDirection)
  {
    case 360:
      {
        moveSequence(walkForwardSequence, 125, 1);
        break;
      }
    case 90:
      {
        moveSequence(walkBackwardSequence, 125, 2);
        moveSequence(rotateRightSequence, 125, 4);
        break;
      }
    case 270:
      {
        moveSequence(walkBackwardSequence, 125, 2);
        moveSequence(rotateLeftSequence, 125, 4);
        break;
      }
    default:
    {
      moveSequence(walkBackwardSequence, 125,5);
      firstPosition();
    }
  }
}
    

// ************************************************************************** Here be functions ************************************************************************** 

long checkPing()
{
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  distance = ((duration / 29) / 2); 
  return(distance);
}

void moveSequence(int moveSequenceData[][3], int timer, int steps)
{
  for (int x = 0; x <= steps; x++)
  {
    frontRightThighServo.writeMicroseconds(moveSequenceData[0][0]);             // Lift the First Tripod of Thighs Horizontal
    middleLeftThighServo.writeMicroseconds(moveSequenceData[0][1]);
    backRightThighServo.writeMicroseconds(moveSequenceData[0][2]);
    frontRightHipServo.writeMicroseconds(moveSequenceData[1][0]);               // Move the First Tripod of Hips Forward
    middleLeftHipServo.writeMicroseconds(moveSequenceData[1][1]);
    backRightHipServo.writeMicroseconds(moveSequenceData[1][2]);
    frontRightFootServo.writeMicroseconds(moveSequenceData[10][0]);             // Set the Feet
    middleLeftFootServo.writeMicroseconds(moveSequenceData[10][1]);
    backRightFootServo.writeMicroseconds(moveSequenceData[10][2]);
    delay(timer);    
    frontRightThighServo.writeMicroseconds(moveSequenceData[2][0]);             // Put the First Tripod of Thighs Down 
    middleLeftThighServo.writeMicroseconds(moveSequenceData[2][1]);
    backRightThighServo.writeMicroseconds(moveSequenceData[2][2]);
    delay(timer);
    frontLeftThighServo.writeMicroseconds(moveSequenceData[3][0]);              // Lift the second Tripod of Thighs Horizontal  ... Reduces Friction for the Hip Movement
    middleRightThighServo.writeMicroseconds(moveSequenceData[3][1]);
    backLeftThighServo.writeMicroseconds(moveSequenceData[3][2]);
    delay(timer);
    frontRightHipServo.writeMicroseconds(moveSequenceData[4][0]);               // Rotate the First Tripod of Hips Back
    middleLeftHipServo.writeMicroseconds(moveSequenceData[4][1]);
    backRightHipServo.writeMicroseconds(moveSequenceData[4][2]);
    delay(timer);
    frontLeftHipServo.writeMicroseconds(moveSequenceData[5][0]);                // Rotate the Second Tripod of Hips Forward
    middleRightHipServo.writeMicroseconds(moveSequenceData[5][1]);
    backLeftHipServo.writeMicroseconds(moveSequenceData[5][2]);
    frontLeftFootServo.writeMicroseconds(moveSequenceData[10][0]);              // Place the Feet
    middleRightFootServo.writeMicroseconds(moveSequenceData[10][1]);
    backLeftFootServo.writeMicroseconds(moveSequenceData[10][2]);
    frontLeftThighServo.writeMicroseconds(moveSequenceData[6][0]);              // Put the Second Tripod of Thighs Down
    middleRightThighServo.writeMicroseconds(moveSequenceData[6][1]);
    backLeftThighServo.writeMicroseconds(moveSequenceData[6][2]);
    delay(timer);
    frontRightThighServo.writeMicroseconds(moveSequenceData[7][0]);             // Lift the First Tripod of Thighs Horizontal ... Again, Reduces Friction for the Hip Movement
    middleLeftThighServo.writeMicroseconds(moveSequenceData[7][1]);
    backRightThighServo.writeMicroseconds(moveSequenceData[7][2]);
    frontRightFootServo.writeMicroseconds(moveSequenceData[10][0]);             // Place the Feet 
    middleLeftFootServo.writeMicroseconds(moveSequenceData[10][1]);
    backRightFootServo.writeMicroseconds(moveSequenceData[10][2]);
    frontLeftHipServo.writeMicroseconds(moveSequenceData[8][0]);                // Rotate the Second Tripod of Hips Back
    middleRightHipServo.writeMicroseconds(moveSequenceData[8][1]);
    backLeftHipServo.writeMicroseconds(moveSequenceData[8][2]);
  }
}

void setZero()
{
  frontLeftHipServo.writeMicroseconds(1500);
  frontRightHipServo.writeMicroseconds(1500);
  middleLeftHipServo.writeMicroseconds(1500);
  middleRightHipServo.writeMicroseconds(1500);
  backLeftHipServo.writeMicroseconds(1500);
  backRightHipServo.writeMicroseconds(1500);

  frontLeftThighServo.writeMicroseconds(1500);
  frontRightThighServo.writeMicroseconds(1500);
  middleLeftThighServo.writeMicroseconds(1500);
  middleRightThighServo.writeMicroseconds(1500);
  backLeftThighServo.writeMicroseconds(1500);
  backRightThighServo.writeMicroseconds(1500);

  frontLeftFootServo.writeMicroseconds(1500);
  frontRightFootServo.writeMicroseconds(1500);
  middleLeftFootServo.writeMicroseconds(1500);
  middleRightFootServo.writeMicroseconds(1500);
  backLeftFootServo.writeMicroseconds(1500);
  backRightFootServo.writeMicroseconds(1500);
}


void firstPosition()
{
  frontLeftHipServo.writeMicroseconds(1500);
  frontRightHipServo.writeMicroseconds(1500);
  middleLeftHipServo.writeMicroseconds(1500);
  middleRightHipServo.writeMicroseconds(1500);
  backLeftHipServo.writeMicroseconds(1500);
  backRightHipServo.writeMicroseconds(1500);

  frontLeftThighServo.writeMicroseconds(1900);
  frontRightThighServo.writeMicroseconds(1900);
  middleLeftThighServo.writeMicroseconds(1900);
  middleRightThighServo.writeMicroseconds(1900);
  backLeftThighServo.writeMicroseconds(1900);
  backRightThighServo.writeMicroseconds(1900);

  frontLeftFootServo.writeMicroseconds(1500);
  frontRightFootServo.writeMicroseconds(1500);
  middleLeftFootServo.writeMicroseconds(1500);
  middleRightFootServo.writeMicroseconds(1500);
  backLeftFootServo.writeMicroseconds(1500);
  backRightFootServo.writeMicroseconds(1500);
}


void standUp(int timer)
{

  firstPosition();

  for (int u = 0; u <= 600; u++)
  {
    frontLeftFootServo.writeMicroseconds(1500 + u);
    frontRightFootServo.writeMicroseconds(1500 + u);
    middleLeftFootServo.writeMicroseconds(1500 + u);
    middleRightFootServo.writeMicroseconds(1500 + u);
    backLeftFootServo.writeMicroseconds(1500 + u);
    backRightFootServo.writeMicroseconds(1500 + u);
    delayMicroseconds(timer);
  }
  for (int x = 0; x <= 800; x++)
  {
    frontLeftThighServo.writeMicroseconds(1900 - x);
    frontRightThighServo.writeMicroseconds(1900 - x);
    middleLeftThighServo.writeMicroseconds(1900 - x);
    middleRightThighServo.writeMicroseconds(1900 - x);
    backLeftThighServo.writeMicroseconds(1900 - x);
    backRightThighServo.writeMicroseconds(1900 - x);
    delayMicroseconds(timer);
  }
  for (int i = 0; i <= 700; i++)
  {
    frontLeftHipServo.writeMicroseconds(1500 - i);
    frontRightHipServo.writeMicroseconds(1500 - i);
    middleLeftHipServo.writeMicroseconds(1500 - i);
    middleRightHipServo.writeMicroseconds(1500 - i);
    backLeftHipServo.writeMicroseconds(1500 - i);
    backRightHipServo.writeMicroseconds(1500 - i);
    delayMicroseconds(timer);
  }
  for (int x = 0; x <= 1400; x++)
  {
    frontLeftHipServo.writeMicroseconds(800 + x);
    frontRightHipServo.writeMicroseconds(800 + x);
    middleLeftHipServo.writeMicroseconds(800 + x);
    middleRightHipServo.writeMicroseconds(800 + x);
    backLeftHipServo.writeMicroseconds(800 + x);
    backRightHipServo.writeMicroseconds(800 + x);
    delayMicroseconds(timer);
  }
  for (int j = 0; j <= 700; j++)
  {
    frontLeftHipServo.writeMicroseconds(2200 - j);
    frontRightHipServo.writeMicroseconds(2200 - j);
    middleLeftHipServo.writeMicroseconds(2200 - j);
    middleRightHipServo.writeMicroseconds(2200 - j);
    backLeftHipServo.writeMicroseconds(2200 - j);
    backRightHipServo.writeMicroseconds(2200 - j);
    delayMicroseconds(timer);    
  }
}

void wiggleIt(int timer)
{
  for (int i = 0; i <= 700; i++)
  {
    frontLeftHipServo.writeMicroseconds(1500 - i);
    frontRightHipServo.writeMicroseconds(1500 - i);
    middleLeftHipServo.writeMicroseconds(1500 - i);
    middleRightHipServo.writeMicroseconds(1500 - i);
    backLeftHipServo.writeMicroseconds(1500 - i);
    backRightHipServo.writeMicroseconds(1500 - i);
    delayMicroseconds(timer);
  }
  for (int x = 0; x <= 1400; x++)
  {
    frontLeftHipServo.writeMicroseconds(800 + x);
    frontRightHipServo.writeMicroseconds(800 + x);
    middleLeftHipServo.writeMicroseconds(800 + x);
    middleRightHipServo.writeMicroseconds(800 + x);
    backLeftHipServo.writeMicroseconds(800 + x);
    backRightHipServo.writeMicroseconds(800 + x);
    delayMicroseconds(timer);
  }
  for (int j = 0; j <= 700; j++)
  {
    frontLeftHipServo.writeMicroseconds(2200 - j);
    frontRightHipServo.writeMicroseconds(2200 - j);
    middleLeftHipServo.writeMicroseconds(2200 - j);
    middleRightHipServo.writeMicroseconds(2200 - j);
    backLeftHipServo.writeMicroseconds(2200 - j);
    backRightHipServo.writeMicroseconds(2200 - j);
    delayMicroseconds(timer);
  }
}

int whichWayToGo()
{
    
  distanceCenter = checkPing();  
  if (distanceCenter > dangerDistance)
    {
      return(360);
    }

  for (int i = 0; i <= 500; i++)
  {
    frontLeftHipServo.writeMicroseconds(1500 - i);
    frontRightHipServo.writeMicroseconds(1500 - i);
    middleLeftHipServo.writeMicroseconds(1500 - i);
    middleRightHipServo.writeMicroseconds(1500 - i);
    backLeftHipServo.writeMicroseconds(1500 - i);
    backRightHipServo.writeMicroseconds(1500 - i);
    delayMicroseconds(500);
  }  

  distanceLeft = checkPing();

  for (int x = 0; x <= 1200; x++)
  {
    frontLeftHipServo.writeMicroseconds(800 + x);
    frontRightHipServo.writeMicroseconds(800 + x);
    middleLeftHipServo.writeMicroseconds(800 + x);
    middleRightHipServo.writeMicroseconds(800 + x);
    backLeftHipServo.writeMicroseconds(800 + x);
    backRightHipServo.writeMicroseconds(800 + x);
    delayMicroseconds(500);
  }
  
  distanceRight = checkPing();
  
  for (int j = 0; j <= 500; j++)
  {
    frontLeftHipServo.writeMicroseconds(2000 - j);
    frontRightHipServo.writeMicroseconds(2000 - j);
    middleLeftHipServo.writeMicroseconds(2000 - j);
    middleRightHipServo.writeMicroseconds(2000 - j);
    backLeftHipServo.writeMicroseconds(2000 - j);
    backRightHipServo.writeMicroseconds(2000 - j);
    delayMicroseconds(500);
  }
 
  if (distanceLeft > distanceRight && distanceLeft > distanceCenter)
  {
    return(270);
  }
  
  if (distanceRight > distanceLeft && distanceRight > distanceCenter)
  {
    return(90);
  }
  
  if (distanceCenter > distanceLeft && distanceCenter > distanceRight)
  {    
    return(360);
  }
  
  if (distanceCenter == distanceLeft == distanceRight)
  {
    return(0);
  }
  
}


void servoCheck(int timer)
{

  for (int i = 700; i <= 2300; i++)
  {
    frontLeftFootServo.writeMicroseconds(i);
    frontRightFootServo.writeMicroseconds(i);
    middleLeftFootServo.writeMicroseconds(i);
    middleRightFootServo.writeMicroseconds(i);
    backLeftFootServo.writeMicroseconds(i);
    backRightFootServo.writeMicroseconds(i);
    delayMicroseconds(timer);

    frontLeftThighServo.writeMicroseconds(i);
    frontRightThighServo.writeMicroseconds(i);
    middleLeftThighServo.writeMicroseconds(i);
    middleRightThighServo.writeMicroseconds(i);
    backLeftThighServo.writeMicroseconds(i);
    backRightThighServo.writeMicroseconds(i);
    delayMicroseconds(timer);

    frontLeftHipServo.writeMicroseconds(i);
    frontRightHipServo.writeMicroseconds(3000 - i);
    middleLeftHipServo.writeMicroseconds(i);
    middleRightHipServo.writeMicroseconds(3000 - i);
    backLeftHipServo.writeMicroseconds(i);
    backRightHipServo.writeMicroseconds(3000 - i);
    delayMicroseconds(timer);    
  }

  for (int x = 2300; x >= 700; x--)
  {
    frontLeftFootServo.writeMicroseconds(x);
    frontRightFootServo.writeMicroseconds(x);
    middleLeftFootServo.writeMicroseconds(x);
    middleRightFootServo.writeMicroseconds(x);
    backLeftFootServo.writeMicroseconds(x);
    backRightFootServo.writeMicroseconds(x);
    delayMicroseconds(timer);

    frontLeftThighServo.writeMicroseconds(x);
    frontRightThighServo.writeMicroseconds(x);
    middleLeftThighServo.writeMicroseconds(x);
    middleRightThighServo.writeMicroseconds(x);
    backLeftThighServo.writeMicroseconds(x);
    backRightThighServo.writeMicroseconds(x);
    delayMicroseconds(timer);

    frontLeftHipServo.writeMicroseconds(x);
    frontRightHipServo.writeMicroseconds(3000 - x);
    middleLeftHipServo.writeMicroseconds(x);
    middleRightHipServo.writeMicroseconds(3000 - x);
    backLeftHipServo.writeMicroseconds(x);
    backRightHipServo.writeMicroseconds(3000 - x);
    delayMicroseconds(timer);    
  }
}

void kneelDown(int timer)
{
  for (int foot = 0; foot <= 800; foot ++)
    {
      frontLeftFootServo.writeMicroseconds(1500 + foot);
      frontRightFootServo.writeMicroseconds(1500 + foot);
      middleLeftFootServo.writeMicroseconds(1500 + foot);
      middleRightFootServo.writeMicroseconds(1500 + foot);
      backLeftFootServo.writeMicroseconds(1500 - foot);
      backRightFootServo.writeMicroseconds(1500 - foot);
      delayMicroseconds(timer);
    }

  
  for (int hip = 0; hip <= 400; hip++)
    { 
      frontLeftHipServo.writeMicroseconds(1500 + hip);
      frontRightHipServo.writeMicroseconds(1500 - hip);
      middleLeftHipServo.writeMicroseconds(1500);
      middleRightHipServo.writeMicroseconds(1500);
      backLeftHipServo.writeMicroseconds(1500 - hip);
      backRightHipServo.writeMicroseconds(1500 + hip);
      delayMicroseconds(timer);
    }
  
  for (int thigh = 0; thigh <= 1100; thigh ++)
    {
      frontLeftThighServo.writeMicroseconds(1900 - thigh);
      frontRightThighServo.writeMicroseconds(1900 - thigh);
      middleLeftThighServo.writeMicroseconds(1900 - thigh);
      middleRightThighServo.writeMicroseconds(1900 - thigh);
      backLeftThighServo.writeMicroseconds(1900 - thigh);
      backRightThighServo.writeMicroseconds(1900 - thigh);
      delayMicroseconds(timer);
    }
  
}
