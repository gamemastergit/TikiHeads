#include <EEPROM.h>


#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup()
{
  pinMode(4, INPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT_PULLUP);
    pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

}
struct correct {
  char uid[20];
};

void loop()
{
  correct answer;
  if(digitalRead(A1) == HIGH  && digitalRead(A2) == HIGH && digitalRead(A3) == HIGH && digitalRead(A4) == HIGH && digitalRead(A5) == HIGH){

  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  while(digitalRead(A1) == HIGH  || digitalRead(A2) == HIGH || digitalRead(A3) == HIGH || digitalRead(A4) || HIGH && digitalRead(A5) == HIGH){
      digitalWrite(2, LOW);
  }
  }
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    digitalWrite(3, LOW);
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
   if (digitalRead(4) ) {
    Serial.println("PROGRAMMING MODE ACTIVATED");
    correct temp;
    content.trim();
    Serial.println(content);
    Serial.println("test");
    content.toCharArray(temp.uid, 21  );
    EEPROM.put(0, temp);
    Serial.println("PROGRAMMING COMPLETE");
    return;
  }

 EEPROM.get(0, answer);

  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  String go = answer.uid;
  go.remove(20);
  Serial.println(go);
  if (content.substring(1).equalsIgnoreCase(go))//change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(3, HIGH);
    delay(3000);
  }

  else {
    Serial.println(" Access denied");
    digitalWrite(3, LOW);
    delay(3000);
  }
}


