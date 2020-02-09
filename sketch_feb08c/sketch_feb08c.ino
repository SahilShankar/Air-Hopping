#define SERIAL_BUFFER_SIZE 512

void runLED(String);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()==9);
  String s1 = Serial.readString();
  runLED(s1); 
}

void runLED(String s1) {
  for(int i=0;i<s1.length();i++) {
  Serial.println(s1.charAt(i));

    if(s1.charAt(i) == '1') {

      digitalWrite(8, HIGH);
      delay(350);
      digitalWrite(8, LOW);
    }else if(s1.charAt(i) == '0'){
    digitalWrite(11, HIGH);
    delay(350);
    digitalWrite(11, LOW);
    }
  }

}  
