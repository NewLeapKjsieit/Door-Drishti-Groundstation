#define minelev 3
#define maxelev 90
#define minaz 0
#define maxaz 360
#define stepdelay 10
float celev,caz,telev,taz,stepangle=1.8;
String indata, az, elev;
#define azdir 2
#define azstepp 3
#define eldir 4
#define elstepp 5
#define homeaz 8
#define homeel 9
void setup() {
  // put your setup code here, to run once:
  
  pinMode(azdir, OUTPUT);
  pinMode(azstepp,OUTPUT);
  pinMode(eldir,OUTPUT);
  pinMode(elstepp,OUTPUT);
  pinMode(homeaz, INPUT);
  pinMode(homeel, INPUT);
  digitalWrite(6, HIGH);
  digitalWrite(7,HIGH);
homing();
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available())
{
  indata=Serial.readString();
  getazel();
  moveaz();
  moveel();
  }
  
 
}
void homing()
{
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
 while(digitalRead(homeaz)!= LOW){
  moveazacw();
  }
  while(digitalRead(homeel)!= LOW){
    moveelacw();
    }
  digitalWrite(6, HIGH);
  digitalWrite(7,HIGH);
    celev=0;
    caz=0;
    taz=0;
    telev=0;
}
void getazel()
{
  int  n = indata.indexOf(' ');
  if (n > 0) {
    az = indata.substring(2,n);
    elev = indata.substring(n+3,n+5);
    elev.trim();
    taz=az.toFloat();
    telev=elev.toFloat();
  }
  Serial.print(taz);
  Serial.println(telev);
  /*if(celev<minelev)
{
  homing();
  }*/
}

  
void moveaz()
{ 
  digitalWrite(6, LOW);
  while(caz-taz>stepangle)
  {
    moveazacw();
    }
  while(taz-caz>stepangle)
  {
    moveazcw();
    }
  digitalWrite(6, HIGH);  
  }
void moveel()
{ 
  digitalWrite(7, LOW);
    while(celev-telev>stepangle)
  {
    moveelacw();
    }
  while(telev-celev>stepangle)
  {
    moveelcw();
    }  
    digitalWrite(7, HIGH);
  }
void moveazcw()
{
  digitalWrite(azdir, LOW);
  digitalWrite(azstepp, HIGH);
  delay(stepdelay);
  digitalWrite(azstepp, LOW);
  delay(stepdelay);
  caz=caz+stepangle;
}
void moveazacw()
{
  digitalWrite(azdir, HIGH);
  digitalWrite(azstepp, HIGH);
  delay(stepdelay);
  digitalWrite(azstepp, LOW);
  delay(stepdelay);
  caz=caz-stepangle;
}
void moveelcw()
{
  digitalWrite(eldir, LOW);
  digitalWrite(elstepp, HIGH);
  delay(stepdelay);
  digitalWrite(elstepp, LOW);
  delay(stepdelay);
  celev=celev+stepangle;
  }
void moveelacw()
{
  digitalWrite(eldir, HIGH);
  digitalWrite(elstepp, HIGH);
  delay(stepdelay);
  digitalWrite(elstepp, LOW);
  delay(stepdelay);
  celev=celev-stepangle;
  }
