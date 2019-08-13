//Author: Shaanan Curtis
//Date:   January 2019

#define statusPin 2
#define trigPin 13
#define echoPin 12

bool flag = false;
int i;
int a[5];
int sum;
int avg;

// returns the distance in cm
long distance()
{
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // starts timing when signal goes HIGH
  // and stops timing when signal goes LOW
  // returns time in microseconds
  duration = pulseIn(echoPin, HIGH, 5000);  //the 5000 timeout is to limit reading to < 80 cm
  
  // calculate the distance (in cm) based on the speed of sound
  return duration/58.2;
}

void detectedObject(int d=0)
{
  digitalWrite(statusPin, LOW);
  Serial.print("Detected object");
  Serial.print(d);
  Serial.print("cm away at time");
  Serial.print(millis());
  Serial.println("milliseconds");
}

void noObject()
{
  digitalWrite(statusPin, HIGH);
  Serial.println("No object detected");
}

void setup() 
{
  //run once  
  Serial.begin(74880);
  pinMode(statusPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("Ready...");
}

void loop() 
{
  //loop infinitely
  int d = distance();
  
  if(i>4)
  {
    i=0;
    while(i<5)
    {
      sum += a[i];
      i++;
    }
 
    avg = sum/5;
    
    // if distance is not within bounds of avg distance after 5 iterations (error +-5),
    // set flag
    if(!((d>=sum-5)&&(d<=sum+5)))
    {
      noObject();
      flag = true;
    }
  }
  
  if(flag)
  {
    while(!((d>=sum-5)&&(d<=sum+5)) || !d)
    {
      d = distance();
    }
    flag = false;
  }
  
  detectedObject(d);
  //reset iterator and sum avg
  i=0;
  sum=0;
  avg=0;
  if(d>0)
  {
    //detectedObject(d);
    a[i] = d;
    i++;
  }
  else
  {
    noObject();
    flag = true;
  }

  delay(100);
}