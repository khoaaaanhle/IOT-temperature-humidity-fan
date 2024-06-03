
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#define DHT_SENSOR_PIN 23 // ESP32 pin GIOP23 connected to DHT22 sensor
#define DHT_SENSOR_TYPE DHT11

#define BLYNK_TEMPLATE_ID "TMPL65ILb8Mb1"
#define BLYNK_TEMPLATE_NAME "khoacutedethuong"
#define BLYNK_AUTH_TOKEN "_sRQxnjyxKNBuQkO89ygbELQIXWi8xQA"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <string.h> 
#define TAMPIL_SERIAL true

int ENA = 13;
int IN1 = 5;
int IN2 = 4;
int led_1 = 5;
int led_2 = 18;
int led_3 = 19;
int nutnhan;
int muc1;
int muc2;
int muc3;

const int frequency = 500;
const int pwm_channel = 0;
const int resolution = 8;

int dutyCycle = 200;

LiquidCrystal_I2C lcd(0x27,20,4);  // I2C address 0x3F, 16 column and 2 rows
DHT dht(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "B";
char pass[] = "11111119";

void setup() {
    Serial.begin(115200);
  dht.begin(); // initialize the DHT sensor
  lcd.init();         // initialize the lcd
  lcd.backlight();    // open the backlight
  lcd.setCursor(1,0);
  lcd.print("HE THONG NHUNG");
  lcd.setCursor(1,1);
  lcd.print("MACH TICH HOP");
  lcd.createChar(2, degree);

  
  pinMode (led_1, OUTPUT);
  pinMode (led_2, OUTPUT);
  pinMode (led_3, OUTPUT);

 
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  ledcSetup(pwm_channel, frequency, resolution);
  ledcAttachPin(ENA, pwm_channel);
  Serial.print("ESP32_BT");
  delay(5000);
  lcd.clear();


    Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  float h  = dht.readHumidity();    // read humidity
  float t = dht.readTemperature(); // read temperature

  char value;
    lcd.setCursor(1,0);
  lcd.print("NHIET DO:");
 lcd.setCursor(10,0);
 lcd.print(t);
 lcd.write(1);
 lcd.print("C");
 lcd.setCursor(1,1);
 lcd.print("DO AM:");
 lcd.setCursor(10,1);
 lcd.print(h);
 lcd.setCursor(12,1);
 lcd.print("%");
 delay(1000);
 lcd.clear();
  Blynk.virtualWrite(V0, t);//BLYNK
  if(nutnhan == 0){
    chaytudong();
    }
   else{
   if(muc1==1){
     lcd.setCursor(1,0);
  lcd.print("quat mo muc: 1");
  lcd.setCursor(1,1);
  lcd.print("PWM: 50");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(pwm_channel, 50);
  delay(15000);
  
  }
  if(muc2==1){
     lcd.setCursor(1,0);
  lcd.print("quat mo muc: 2");
  lcd.setCursor(1,1);
  lcd.print("PWM: 150");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(pwm_channel, 150);
  delay(15000);
  lcd.clear();
  }
  if(muc3 ==1){
      lcd.setCursor(1,0);
  lcd.print("quat mo muc: 3");
  lcd.setCursor(1,1);
  lcd.print("PWM: 254");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(pwm_channel, 254);
  delay(15000);
  lcd.clear();
  }
  delay(5000);
    chaybangtay();
    lcd.clear();
 
   }
}
BLYNK_WRITE(V1){
  nutnhan= param.asInt();
  }
  BLYNK_WRITE(V2){
  muc1= param.asInt();
  }
  BLYNK_WRITE(V3){
  muc2= param.asInt();
  }
  BLYNK_WRITE(V4){
  muc3= param.asInt();
  }
void chaytudong(){
  float h  = dht.readHumidity();    // read humidity
  float t = dht.readTemperature(); // read temperature
   lcd.setCursor(1,0);
  lcd.print("NHIET DO:");
 lcd.setCursor(10,0);
 lcd.print(t);
 lcd.write(1);
 lcd.print("C");
 lcd.setCursor(1,1);
 lcd.print("DO AM:");
 lcd.setCursor(10,1);
 lcd.print(h);
 lcd.setCursor(12,1);
 lcd.print("%");
 delay(1000);
 lcd.clear();
  if (nutnhan == 0){
    if ((t>=25)&& (t<=33)){
  lcd.setCursor(1,0);
  lcd.print("quat mo muc: 1");
  lcd.setCursor(1,1);
  lcd.print("PWM: 50");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2, HIGH);
  delay(5000);
  ledcWrite(pwm_channel, 50);
  lcd.clear();
  }
    if ((t>=33)&& (t<=35)){
  lcd.setCursor(1,0);
  lcd.print("quat mo muc: 2");
  lcd.setCursor(1,1);
  lcd.print("PWM: 150");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(pwm_channel, 150);
  delay(5000);
  lcd.clear();
  }
    if (t>= 36){
  lcd.setCursor(1,0);
  lcd.print("quat mo muc: 3");
  lcd.setCursor(1,1);
  lcd.print("PWM: 254");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(pwm_channel, 254);
  delay(5000);
  lcd.clear();
  }  
  }
  }
 void chaybangtay(){
    float h  = dht.readHumidity();    // read humidity
  float t = dht.readTemperature(); // read temperature
  if( nutnhan == 1){
    digitalWrite(IN1,LOW);
  digitalWrite(IN2, LOW);
    ledcWrite(pwm_channel, 0);
    
    lcd.setCursor(1,0);
  lcd.print("che do");
  lcd.setCursor(1,1);
  lcd.print("nhan tay");
  delay(3000);}
  
  }
    
