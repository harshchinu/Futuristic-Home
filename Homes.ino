#include <dht.h>
#include<SoftwareSerial.h>
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int pResistor = 10; // Photoresistor at Arduino analog pin A0
int ledPin=9;       // Led pin at Arduino pin 9
int value;          // Store value from photoresistor (0-1023)


int motion_1 = 7;

int trigPin = 8;
int echoPin = 1;
int led3=13;


#define DHT11_PIN 6     // what pin we're connected to
dht DHT;

int sensorPin = A0; // select the input pin for the LDR
int sensorValue = 0; // variable to store the value coming from the sensor


void setup(){
  
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode (motion_1,INPUT);
  pinMode(led3, OUTPUT);
   pinMode(ledPin, OUTPUT);  // Set lepPin - 9 pin as an output
  pinMode(pResistor, INPUT);// Set pResistor - A0 pin as an input (optional)
//  dht.begin();
  lcd.begin(16, 2);

}

void loop (){
    int chk = DHT.read11(DHT11_PIN);
    digitalWrite(led3, LOW);
    lcd.clear();
    
    int sensor_1 = digitalRead(motion_1);
    if (sensor_1 == HIGH)
    {
      lcd.setCursor(0, 0);
      lcd.print("Theft find");

      Serial.print("\ntheft find");
      digitalWrite(led3,HIGH);
      //delay(500);
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print("no Theft find");
      Serial.print("\no ntheft find");
      digitalWrite(led3,LOW);
    }
    delay(2000);


// temp mesure

  Serial.print(" Humidity " );
  Serial.print(DHT.humidity, 1);


  lcd.setCursor(0,0);
  
  lcd.print(" Humidity " );
  lcd.print(DHT.humidity);


  Serial.print(" Temparature ");
  Serial.println(DHT.temperature, 1);

  lcd.setCursor(0,1);
  lcd.print(" Temp" );
  lcd.print(DHT.temperature);

  

  // FLAME

  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if (sensorValue < 200)
  {
    Serial.println("Fire Detected");
    digitalWrite(led3,HIGH);
  }    
  else
  {
      Serial.println("No Fire");
      digitalWrite(led3,LOW);
  }  

  value = digitalRead(pResistor);

  Serial.print(value);
  //You can change value "25"
  if (value == HIGH)
  {
    
    digitalWrite(ledPin, HIGH);  //Turn led off
  }
  else
  {
    digitalWrite(ledPin, LOW); //Turn led on
  }

  delay(500); //Small delay

  
  delay(2000);

}


