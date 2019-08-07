#include "DHT.h";
 
// Define Constants
 
#define DHTPIN 7     // DHT-22 Output Pin connection
#define DHTTYPE DHT11   // DHT Type is DHT 22 (AM2302)
 
// Initialize DHT sensor for normal 16mhz Arduino
 
DHT dht(DHTPIN, DHTTYPE); 
 
 
// Define Variables
 
float hum;  //Stores humidity value
float temp; //Stores temperature value
 
void setup()
{
  Serial.begin(9600);
  dht.begin();
}
 
void loop()
{
    delay(2000);  // Delay so sensor can stabalize
   
    hum = dht.readHumidity();  // Get Humidity value
    temp= dht.readTemperature();  // Get Temperature value
    
    // Print temperature and humidity values to serial monitor
    
    Serial.print("Humidity: ");
    Serial.print(dht.readHumidity());
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius"); 
  
}
