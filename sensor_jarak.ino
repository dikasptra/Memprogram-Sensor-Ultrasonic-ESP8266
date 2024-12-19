/*
  Blynk example
  You should get Auth Token in the Blynk App.
  You need to write the right wifiCredentials.
*/

/* Comment this out to disable prints and save space */
#define BLYNK_TEMPLATE_ID "TMPL6w-8ZaLet"
#define BLYNK_TEMPLATE_NAME "Jarak"
#define BLYNK_AUTH_TOKEN "zZeCC0Q44S8EpFIxkqVs0Gq5hzvIvxWQ"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

int trig_sensor_jarak = 12; // Trigger pin
int echo_sensor_jarak = 14; // Echo pin
int buzzer_pin = 2; // Pin untuk buzzer
int led_pin = 5; // Pin untuk LED

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "zZeCC0Q44S8EpFIxkqVs0Gq5hzvIvxWQ";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Lab Robotika"; //nama hotspot yang digunakan
char pass[] = "lab_robotika"; //password hotspot yang digunakan

BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(trig_sensor_jarak, OUTPUT);
  pinMode(echo_sensor_jarak, INPUT);
  pinMode(buzzer_pin, OUTPUT); // Set buzzer pin as output
  pinMode(led_pin, OUTPUT); // Set LED pin as output

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, sendSensor); // Send data every second
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  timer.run();
}

void sendSensor() {
    long duration, distance;
    
    // Clear the trigPin condition
    digitalWrite(trig_sensor_jarak, LOW);
    delayMicroseconds(2);
    
    // Trigger the sensor
    digitalWrite(trig_sensor_jarak, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_sensor_jarak, LOW);
    
    // Read the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echo_sensor_jarak, HIGH);
    
    // Calculate the distance (in cm)
    distance = duration * 0.034 / 2;
    
    // Print distance to Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    // Send distance data to Blynk
    Blynk.virtualWrite(V14, distance); // Use V0 for a display widget in your Blynk app

    // Check if distance is less than 10 cm
     if (distance < 10) {
        digitalWrite(buzzer_pin, HIGH); // Turn on buzzer
        digitalWrite(led_pin, HIGH);    // Turn on LED
        Blynk.logEvent("notif_sensor");
    } else {
        digitalWrite(buzzer_pin, LOW); // Turn off buzzer
        digitalWrite(led_pin, LOW);    // Turn off LED
    }
} 