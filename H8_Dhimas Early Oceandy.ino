//pins
int mr1 = 23; // motor right 1
int mr2 = 22; // motor right 2
int ml1 = 21; // motor left 1
int ml2 = 19; // motor left 2
int sr = 18; // sensor right 
int sl = 17; // sensor left 
int enr = 12; // enable right (for right motors speed)
int enl = 14; // enable left (for left motors speed)

// variable values
int svr = 0; // sensor value right
int svl = 0; // sensor value left

// constants
const int vspeed = 100; // forward speed
const int tspeed = 255; // turn speed
const int tdelay = 20; // turn delay

void setup()
{
  // initialize the pins
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);
  pinMode(sr, INPUT);
  pinMode(sl, INPUT);
  
  // PWM pins
  ledcSetup(0, 5000, 8);
  ledcAttachPin(enr, 0);
  ledcSetup(1, 5000, 8);
  ledcAttachPin(enl, 1);

  delay(5000);
}

void loop()
{
  svr = digitalRead(sr);
  svl = digitalRead(sl);
  
  // LOW -> sensor detects white
  // HIGH -> sensor detects black
  // different type of sensors might differ
  if(svl == LOW && svr == LOW)
  {
    forward();
  }

  if(svl == HIGH && svr == LOW)
  {
    turnLeft();
  }
 
  if(svl == LOW && svr == HIGH)
  { 
    turnRight();
  }
  
  // arrive at point A or B
  if(svl == HIGH && svr == HIGH)
  {
    stop();
    delay(5000);
    reverseOrientation(); // back become front

    // driving away from the box for a fixed amount of time before continuing with the main algorithm
    forward();
    delay(1000);
  }
}

void forward()
{
  // all wheels spin forward
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);

  ledcWrite(0, vspeed);
  ledcWrite(1, vspeed);
} 

void turnRight()
{
  // the left wheels spin forward, while the right wheels spin backward
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);

  ledcWrite(0, tspeed);
  ledcWrite(1, tspeed);
  delay(tdelay);
}

void turnLeft()
{
  // the right wheels spin forward, while the left wheels spin backward
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);

  ledcWrite(0, tspeed);
  ledcWrite(1, tspeed);
  delay(tdelay);
}  

void stop()
{
  ledcWrite(enr, 0);
  ledcWrite(enl, 0);
}

// reverse the front and back face of the robot
void reverseOrientation()
{
  int temp;
  temp = mr1; mr1 = ml1; ml1 = temp;
  temp = mr2; mr2 = ml2; ml2 = temp;
  temp = sr; sr = sl; sl = temp;
  temp = enr; enr = enl; enl = temp;
}
