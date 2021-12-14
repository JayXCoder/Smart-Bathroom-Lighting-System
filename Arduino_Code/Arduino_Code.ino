#define BLYNK_TEMPLATE_ID "TMPLaxpFX7yn"
#define BLYNK_DEVICE_NAME "Rin FYP"
#define BLYNK_AUTH_TOKEN "IX8rABSt4NmWkWfcc2Y6vyuKu9_M3dIb";

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "RIN";
char pass[] = "parkjimin";

//PIR Sensor Declaration
int sensor = 15;              //D8

//Relay Based Declaration
const int Relay_1 = 14;        //D5
const int Relay_2 = 12;        //D6

#define VPIN_BUTTON_1    V1 
#define VPIN_BUTTON_2    V2

int toggleState_1 = 1; //Define integer to remember the toggle state for relay 1
int toggleState_2 = 1; //Define integer to remember the toggle state for relay 2

BlynkTimer timer;

void setup() 
{
  pinMode(Relay_1, OUTPUT);
  pinMode(Relay_2, OUTPUT);

  digitalWrite(Relay_1, toggleState_1);
  digitalWrite(Relay_2, toggleState_2);

  pinMode(sensor, INPUT); // declare sensor as input

  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}


void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi Not Connected");
  }
  else
  {
    Serial.println("WiFi Connected");
    Blynk.run();
  }
    automation();

}


void automation()
{
    if (digitalRead(sensor) == HIGH)
    {
      delay(2000);

      digitalWrite(Relay_1, LOW); // turn on relay 1
      toggleState_1 = 0;
      Serial.println("LED 1 ON"); 
      Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);   // Update Button Widget

      digitalWrite(Relay_2, LOW); // turn ON relay 2
      toggleState_2 = 0;
      Serial.println("LED 2 ON");     
      Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);   // Update Button Widget
    }

    else if (digitalRead(sensor) == LOW)
    {
      delay(2000);

      digitalWrite(Relay_1, HIGH); // turn off relay 1
      toggleState_1 = 1;
      Serial.println("LED 1 OFF");

      digitalWrite(Relay_2, HIGH); // turn off relay 2
      toggleState_2 = 1;
      Serial.println("LED 2 OFF");

    }
}



BLYNK_CONNECTED() 
  {
    // Request the latest state from the server
    Blynk.syncVirtual(VPIN_BUTTON_1);
    Blynk.syncVirtual(VPIN_BUTTON_2);
  }


// When App button is pushed - switch the state
BLYNK_WRITE(VPIN_BUTTON_1) 
{
  toggleState_1 = param.asInt();
  digitalWrite(Relay_1, toggleState_1);
}

BLYNK_WRITE(VPIN_BUTTON_2) 
{
  toggleState_2 = param.asInt();
  digitalWrite(Relay_2, toggleState_2);
