#include "ESP8266WiFi.h"

const char* ssid = "Bme_StudentLab1";
const char* password =  "mybmewifi";
int flag = 1;
WiFiServer wifiServer(80);
int i;
char mystr; //Initialized variable to store recieved data
String str;

void writeString(String stringData);

void setup() {
    Serial.println("WiFi.begin");

  Serial.begin(115200);
    Serial.println("WiFi.begin");

  delay(1000);
   Serial.println("WiFi.begin");
  WiFi.begin(ssid, password);
  Serial.println("WiFi.begin");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
 
  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin();
}
 
void loop() {
  WiFiClient client = wifiServer.available();
  if (client) {
     Serial.println("hello");
    while (client.connected()) {
      Serial.readBytes(&mystr,1); //Read the serial data and store in var
      Serial.print(mystr);
     // client.write(mystr); 
      if(mystr == '*'){
        client.write("Server: ");
        for (int i = 0; i < str.length(); i++)
        {
          client.write(str[i]);   // Push each char 1 by 1 on each loop pass
        }
        str = "";
      }
      //str += mystr;
      if((mystr > 'a' && mystr < 'z') || (mystr == 'a' && mystr == 'z')){str += mystr;}
      
       //client.write("Server: iam ready\n");
       //writeString(req);
       while (client.available()>0) {
        delay(1);
        String c = client.readStringUntil('\n');
        delay(1);
        if(flag == 1){
          flag = 0;
          client.write("Client: ");
          delay(1);
        }
        for (int i = 0; i < c.length(); i++)
        {
          client.write(c[i]);   // Push each char 1 by 1 on each loop pass
        }
        client.write("\n");
      }
      flag = 1;
      delay(1000);
    }
 
    client.stop();
    Serial.println("Client disconnected");
 
  }
}

void writeString(String stringData) { // Used to serially push out a String with Serial.write()

  for (int i = 0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }

}// end writeString
