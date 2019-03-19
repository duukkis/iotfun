/*
 * If you connect the voltage to 3,3V the lines marked as // PIN can be removed
 * If you connect the voltage to digital pin (so that the meter is not always on)
 */

#define DPIN 12 // PIN D6
#define INTERVAL 20

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(DPIN, OUTPUT); // PIN
}


int timer = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (timer > INTERVAL){
    // set the soil moisture on
    digitalWrite(DPIN, HIGH); // PIN set power to meter
    delay(3000); // PIN wait for the meter to start
    timer = 0;
    int val = analogRead(0);
    // WATER GLASS 195
    // DRY 609 - the dry is 447 when power is connected to D6 (so check the values)
    Serial.println(val);
    digitalWrite(DPIN, LOW); // PIN turn off power to meter
  } else {
    timer++;
  }
  delay(1000);
}
