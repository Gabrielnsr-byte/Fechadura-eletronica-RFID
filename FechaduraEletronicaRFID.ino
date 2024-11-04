#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <NewPing.h>
#include <SoftwareSerial.h>

#define TRIGGER_PIN 4
#define ECHO_PIN 5
#define MAX_DISTANCE 20
#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 2
#define I2C_ADDR 0x27
#define colunas 16
#define linhas 2
#define LED_VERMELHO 6
#define LED_VERDE 7
#define BOTAO_PIN 3
#define FECHAR_FECHADURA 90
#define RX_PIN 0
#define TX_PIN 1

LiquidCrystal_I2C lcd(I2C_ADDR, colunas, linhas);
MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myServo;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
SoftwareSerial mySerial(0, 1);

// UID do cartão que você deseja autorizar
byte cardUID[] = {0x23, 0x4F, 0xC9, 0x2F};

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.print("Leitor RFID pronto!");
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(BOTAO_PIN, INPUT_PULLUP);
  myServo.attach(SERVO_PIN);
  myServo.write(FECHAR_FECHADURA);
  digitalWrite(LED_VERMELHO, HIGH);
  delay(5000);
}

void loop() {
  Serial.println("Distancia do objeto em cm: " + String(sonar.ping_cm()));
  // Leitura do cartão RFID
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    if (memcmp(cardUID, mfrc522.uid.uidByte, sizeof(cardUID)) == 0) {
      // Acesso concedido
      lcd.print(" Acesso concedido !");
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_VERMELHO, LOW);
      myServo.write(0);
      delay(10000);
    } else {
      // Acesso negado
      lcd.print(" Negado!");
      digitalWrite(LED_VERMELHO, HIGH);
      delay(5000);
    }
    mfrc522.PICC_HaltA();
  }

  // Controle via Bluetooth
  if (mySerial.available() > 0) {
    char data = mySerial.read();
    if (data == 'A') {
      myServo.write(0);
    } else if (data == 'F') {
      myServo.write(FECHAR_FECHADURA);
    }
  }

  // Controle manual
  if (digitalRead(BOTAO_PIN) == LOW && myServo.read() == 0) {
    myServo.write(FECHAR_FECHADURA);
    delay(1000);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
  }
  lcd.init();
  lcd.backlight();
  lcd.clear();
}
