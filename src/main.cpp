#include <Arduino.h>
#include <WiFiNINA.h>
#include <OOCSI.h>
#include <ArduinoHttpClient.h>
#include <OOCSIDevice.h>
#include <oneEuroFilter.h>

String incomingByte = ""; // for incoming serial data

const int BUFFER_SIZE = 100;
char buf[BUFFER_SIZE];
int openerloc[2];

String coordinates;
OOCSI oocsi = OOCSI(); 
oneEuroFilter euro = oneEuroFilter(0,0.0,1.0,0.0,1.0);

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);  // opens serial port, sets data rate to 9600 bps
  oocsi.connect("SensorLocation", "oocsi.id.tue.nl", "boefspot", "B03ff13u1tl4t3n");
  OOCSIDevice prototype = oocsi.heyOOCSI("proximity");
  prototype.addProperty("creator", "Diede!");
  prototype.addSensor("proximity distance","proxchannel","","out of range","mm","social-distance-6-feet" );
  prototype.sayHi();
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}


void loop() {
  // check if data is available
  // delay(100);
  if (Serial1.available() > 0) {
    // read the incoming bytes:
    int rlen = Serial1.readBytesUntil('\n', buf, BUFFER_SIZE);
    String message;
    // prints the received data
    for(int i = 0; i < rlen; i++)
      // Serial.print(buf[i]);
      message += buf[i];
    // Serial.println(message);
    


    if ((buf[0]) == 'D'){
      // Serial.println(message);
      float time = millis();
      int opening = message.indexOf('(');  //finds location of first (
      int closing = message.indexOf(')');  //finds location of first )
      
      coordinates = message.substring(opening, closing);   //captures first data String

      int ind1 = message.indexOf(',' );   //finds location of second ,
      String tag = message.substring(opening+1, ind1);   //captures second data String

      int ind2 = message.indexOf(',', ind1+1);   //finds location of second ,
      String xcor = message.substring(ind1+1, ind2);   //captures second data String

      int ind3 = message.indexOf(',', ind2+1);   //finds location of second ,
      String ycor = message.substring(ind2+1, ind3);   //captures second data String

      int ind4 = message.indexOf(',', ind3+1);   //finds location of second ,
      String zcor = message.substring(ind3+1, closing);

      // Serial.println(("check tag:" +tag + " x:" + xcor + " y:"+ ycor+ " z:" + zcor));
      
      int zcori = zcor.toInt();
      int ycori = ycor.toInt();
      int xcori = xcor.toInt();

      int xcorf = euro.filter(time, xcori);
      int ycorf = euro.filter(time, ycori);
      int zcorf = euro.filter(time, zcori);


      if (xcori != 0 ){
        Serial.println(("tag:" +tag + " x:" + xcori + " y:"+ ycori+ " z:" + zcori));
        Serial.println(("tag:" +tag + " x:" + xcorf + " y:"+ ycorf+ " z:" + zcorf));

        // int openingProx = message.indexOf('(', opening +1);  //finds location of first (
        // int closingProx = message.indexOf(')', closing +1);  //finds location of first )
        // String closest = message.substring(openingProx, closingProx);   //captures first data String

        oocsi.newMessage("proxchannel");
        oocsi.addInt("xcor",xcorf);
        oocsi.addInt("ycor",ycorf);
        oocsi.addInt("zcor",zcorf);
        oocsi.sendMessage();
        oocsi.printSendMessage();

      }

      
    }
    
  }
}

