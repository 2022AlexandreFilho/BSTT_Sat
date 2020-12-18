int value1 = analogRead(A0);
int value2= analogRead(A0);
int difference = 0;
int lightning = -1;

void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
}

void loop() {
  Serial.println(value1);
  Serial.println(value2);
  difference = value2 - value1;
  if (difference > 100) {
    lightning++;
    
  }
  Serial.println(lightning);
  value1 = value2;
  value2 = analogRead(A0);
  }

    
