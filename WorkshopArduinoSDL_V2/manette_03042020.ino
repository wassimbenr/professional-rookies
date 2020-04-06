char data;
void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(5, INPUT);
  pinMode(7, INPUT);

}

void loop() {
  if (Serial.available() > 0) {
    char data = (char) Serial.read(); //read only 1 byte
    delay(5); // Delay for 5 ms so the next byte has time to be received
    if (data == '0')
    {
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
    }
    else if (data == '1')
    {
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
    }
    else if (data == '2')
    {
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
    }
  }
  if (Serial.available() > 0) {
    delay(5);
    char data = (char)Serial.println();
    if (digitalRead(5) == LOW && digitalRead(7) == LOW)
    {
      data = '0';
    }
    else if (digitalRead(5) == HIGH && digitalRead(7) == LOW)
    {
      data = '1';
    }
    else if (digitalRead(7) == HIGH && digitalRead(5) == LOW)
    {
      data = '2';
    }

    Serial.println(data);
  }

}
