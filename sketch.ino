#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 7
#define DHTTYPE DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pinos
const int ldrPin = A0;
const int ledVerde = 2;
const int ledAmarelo = 3;
const int ledVermelho = 4;
const int buzzer = 9;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  lcd.backlight();

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Realiza as médias de 5 leituras
  float tempMedia = mediaTemperatura();
  float umidMedia = mediaUmidade();
  int luzMedia = mediaLDR();

  // Zera todos os atuadores antes da nova análise
  desligaTodos();

  // --- Temperatura ---
  if (tempMedia < 10) {
    lcd.setCursor(0, 0);
    lcd.print("Temp. Baixa:");
    lcd.setCursor(0, 1);
    lcd.print(tempMedia); lcd.print(" C");
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(buzzer, HIGH);
  } else if (tempMedia <= 15) {
    lcd.setCursor(0, 0);
    lcd.print("Temperatura OK");
    lcd.setCursor(0, 1);
    lcd.print(tempMedia); lcd.print(" C");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Temp. Alta:");
    lcd.setCursor(0, 1);
    lcd.print(tempMedia); lcd.print(" C");
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(buzzer, HIGH);
  }

  delay(3000);
  lcd.clear();

  // --- Umidade ---
  if (umidMedia < 50) {
    lcd.setCursor(0, 0);
    lcd.print("Umidade Baixa:");
    lcd.setCursor(0, 1);
    lcd.print(umidMedia); lcd.print(" %");
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(buzzer, HIGH);
  } else if (umidMedia <= 70) {
    lcd.setCursor(0, 0);
    lcd.print("Umidade OK");
    lcd.setCursor(0, 1);
    lcd.print(umidMedia); lcd.print(" %");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Umidade Alta:");
    lcd.setCursor(0, 1);
    lcd.print(umidMedia); lcd.print(" %");
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(buzzer, HIGH);
  }

  delay(3000);
  lcd.clear();

  // --- Luminosidade ---
  if (luzMedia < 400) {
    lcd.setCursor(0, 0);
    lcd.print("Ambiente escuro");
    digitalWrite(ledVerde, HIGH);
  } else if (luzMedia <= 600) {
    lcd.setCursor(0, 0);
    lcd.print("Amb. a meia luz");
    digitalWrite(ledAmarelo, HIGH);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Amb. muito claro");
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(buzzer, HIGH);
  }

  delay(2000);
  lcd.clear();
}

// Função para desligar todos os LEDs e buzzer
void desligaTodos() {
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(buzzer, LOW);
}

// Média de 5 leituras de temperatura
float mediaTemperatura() {
  sensors_event_t event;
  float soma = 0;
  for (int i = 0; i < 5; i++) {
    dht.temperature().getEvent(&event);
    soma += event.temperature;
    delay(1000);
  }
  return soma / 5.0;
}

// Média de 5 leituras de umidade
float mediaUmidade() {
  sensors_event_t event;
  float soma = 0;
  for (int i = 0; i < 5; i++) {
    dht.humidity().getEvent(&event);
    soma += event.relative_humidity;
    delay(1000);
  }
  return soma / 5.0;
}

// Média de 5 leituras do LDR
int mediaLDR() {
  int soma = 0;
  for (int i = 0; i < 5; i++) {
    soma += analogRead(ldrPin);
    delay(1000);
  }
  return soma / 5;
}
