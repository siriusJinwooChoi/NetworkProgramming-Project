
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "YOUR NETWORK SSID";     //your network SSID (name) 
char pass[] = "YOUR NETWORK PASSWORD"; //your network password

int status = WL_IDLE_STATUS;
IPAddress server(xxx,xxx,xxx,xxx);    //your Server IP address
WiFiClient client;

bool connected = false;
bool check = false;
String trans = " ";
const int temperaturePin = 0;
String confirm = "";
int count = 1;
int melody[] = {
  262, 294, 330, 349, 392, 440, 494, 523 };
  
void setup()
{
   Serial.begin(9600); 
   Serial.println("Attempting to connect to WPA network...");
   Serial.print("SSID: ");
   Serial.println(ssid);
}

void loop()
{

  status = WiFi.begin(ssid, pass);
  
  if ( status != WL_CONNECTED) { 
    Serial.println("Couldn't get a wifi connection");
    //don't do anything else:
    while(true);
  } 
  else {
    //Serial.println("Connected to wifi");
    //Serial.println("\nStarting connection...");    
  } 
       
  if(!connected) {
    Serial.println("connecting............");
    connected = true;
    
  if (client.connect(server, 80)) {
      Serial.println("Socket connected");
      float voltage;
      int degree;
      voltage = getVoltage(temperaturePin);
      degree = (voltage - 0.5) * 100.0; 
     /*
      Serial.print("degree :");
      Serial.println(degree);
      Serial.print("Count :");
      Serial.println(count);
      Serial.print("Confirm :");
      Serial.println(confirm);
      */
      if(degree > 30)
        count++;
      else
        count = 1;
        
      
      if(degree >= 30 && count >= 5) {
          tone(8, melody[2]);  // 'do' sound    
          delay(500);
          tone(8, melody[0]);
          delay(500);
          noTone(8); 
       }
       
       if(degree < 30 && count == 1){
         confirm = "Normal";
         client.print("GET /insert.php?val=");
         client.print(degree);
         client.print("&confirm=");
         client.print(confirm);
         client.println(" HTTP/1.1");
         client.println("Host: xxx.xxx.xxx.xxx");   //Your Server IP Address
         client.println("Connection: close");
         client.println();
         Serial.print("degree :");
         Serial.println(degree);
         Serial.print("Count :");
         Serial.println(count);
         Serial.print("Confirm :");
         Serial.println(confirm);
       } else if(degree > 30 && 1 < count && count < 5){
         confirm = "Alert";
         client.print("GET /insert.php?val=");
         client.print(degree);
         client.print("&confirm=");
         client.print(confirm);
         client.println(" HTTP/1.1");
         client.println("Host: xxx.xxx.xxx.xxx");   //Your Server IP Address
         client.println("Connection: close");
         client.println();
         Serial.print("degree :");
         Serial.println(degree);
         Serial.print("Count :");
         Serial.println(count);
         Serial.print("Confirm :");
         Serial.println(confirm);
       } else if(degree > 30 && count > 5){
         confirm = "Dangerous";
         client.print("GET /insert.php?val=");
         client.print(degree);
         client.print("&confirm=");
         client.print(confirm);
         client.println(" HTTP/1.1");
         client.println("Host: xxx.xxx.xxx.xxx");   //Your Server IP Address
         client.println("Connection: close");
         client.println();
         Serial.print("degree :");
         Serial.println(degree);
         Serial.print("Count :");
         Serial.println(count);
         Serial.print("Confirm :");
         Serial.println(confirm);
       }
         
       check = false;      
       
     delay(1000); //origin 1 sec
  }else {
    Serial.println("Socket connection failed");
   } 
 } else {
    if(client.connected() && client.available()) {
      char c = client.read();
      Serial.print(c);
    }
    //Serial.println("disconnecting");
    client.stop();
    connected = false;
   }
}

float getVoltage(int pin)
{
 return (analogRead(pin) * 0.004882814); 
}
