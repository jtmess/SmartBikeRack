int an0=0;
int an1=1;
int tamper=0;
int cut=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  tamper=analogRead(an0);
  cut=analogRead(an1);
  Serial.print(tamper);Serial.print(", break?:");Serial.println(cut);
  delay(100);
  // put your main code here, to run repeatedly:

}
