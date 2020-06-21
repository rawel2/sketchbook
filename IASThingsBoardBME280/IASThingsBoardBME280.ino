/*
  This is an initial sketch to be used as a "blueprint" to create apps which can be used with IOTappstory.com infrastructure
  Your code can be filled wherever it is marked.

  Copyright (c) [2017] [Andreas Spiess]

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  IASBlink V1.0.2
*/

#define COMPDATE __DATE__ __TIME__
#define MODEBUTTON 0                                        // Button pin on the esp for selecting modes. D3 for the Wemos!
// #define TOKEN               "eDtTW5XThhi992DZdtcX"
#define TBVERSION "Ver 1.1.15"
#define TOKEN               "WpiszNowyTokenWtoPol"
#define THINGSBOARD_SERVER  "dom.romaniuk.pl"
#define THINGSBOARD_PORT "1883"

#include <ESP8266WiFi.h>
#include <IOTAppStory.h>                                    // IotAppStory.com library
#include <ThingsBoard.h>
#include <BME280.h>


WiFiClient espClient;

IOTAppStory IAS(COMPDATE, MODEBUTTON);                      // Initialize IOTAppStory
ThingsBoard tb(espClient);
BME280_Class   BME280;


// ================================================ EXAMPLE VARS =========================================
// used in this example to blink (LEDpin) every (blinkTime) miliseconds
unsigned long blinkEntry;
unsigned long tbEntry;

String deviceName = "ESPTBoard";
String chipId;

// We want to be able to edit these example variables below from the wifi config manager
// Currently only char arrays are supported. (Keep in mind that html form fields always return Strings)
// Use functions like atoi() and atof() to transform the char array to integers or floats
// Use IAS.dPinConv() to convert Dpin numbers to integers (D6 > 14)

char* LEDpin    = "2";				
char* trigPin    = "2";
char* echoPin    = "2";
char* blinkTime = "1000";
char* thingsBoardTime = "30000";
char* thingsBoardToken = TOKEN;
char* thingsBoardServer = THINGSBOARD_SERVER;
char* thingsBoardPort = THINGSBOARD_PORT;
char* pomiarOdleglosci = "1";

// ================================================ SETUP ================================================
void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.println(F("Start prosze czekac 60s ...."));
	delay(60000); // 1 minuta
  // creat a unique deviceName for classroom situations (deviceName-123)
  chipId      = String(ESP_GETCHIPID);
  chipId      = "-"+chipId.substring(chipId.length()-3);
  deviceName += chipId;
	
  IAS.preSetDeviceName(deviceName);                         // preset deviceName this is also your MDNS responder: http://iasblink.local


  IAS.addField(LEDpin, "ledpin", 2, 'P');                   // These fields are added to the config wifimanager and saved to eeprom. Updated values are returned to the original variable.
  IAS.addField(blinkTime, "Blinktime(mS)", 5, 'N');         // reference to org variable | field label value | max char return
  IAS.addField(thingsBoardTime, "ThingsBtime(mS)", 6, 'N');         // reference to org variable | field label value | max char return
  IAS.addField(thingsBoardToken, "Device Token", 25, 'L');         // reference to org variable | field label value | max char return
  IAS.addField(thingsBoardServer, "Server name or ip", 25, 'L');         // reference to org variable | field label value | max char return
  IAS.addField(thingsBoardPort, "Tcp Port", 6, 'N');         // reference to org variable | field label value | max char return
  IAS.addField(pomiarOdleglosci, "Pomiar odl:Wlacz", 1, 'C');         // reference to org variable | field label value | max char return
  IAS.addField(trigPin, "trigpin", 2, 'P'); 
  IAS.addField(echoPin, "echoPin", 2, 'P'); 

  // You can configure callback functions that can give feedback to the app user about the current state of the application.
  // In this example we use serial print to demonstrate the call backs. But you could use leds etc.
  IAS.onModeButtonShortPress([]() {
    Serial.println(F(" If mode button is released, I will enter in firmware update mode."));
    Serial.println(F("*-------------------------------------------------------------------------*"));
    digitalWrite(IAS.dPinConv(LEDpin), !digitalRead(IAS.dPinConv(LEDpin)));
    delay(200);
    digitalWrite(IAS.dPinConv(LEDpin), !digitalRead(IAS.dPinConv(LEDpin)));
    delay(200);
    digitalWrite(IAS.dPinConv(LEDpin), !digitalRead(IAS.dPinConv(LEDpin)));
    delay(200);
    digitalWrite(IAS.dPinConv(LEDpin), !digitalRead(IAS.dPinConv(LEDpin)));
    
  });

  IAS.onModeButtonLongPress([]() {
    Serial.println(F(" If mode button is released, I will enter in configuration mode."));
    Serial.println(F("*-------------------------------------------------------------------------*"));
    digitalWrite(IAS.dPinConv(LEDpin), !digitalRead(IAS.dPinConv(LEDpin)));
    delay(200);
    digitalWrite(IAS.dPinConv(LEDpin), !digitalRead(IAS.dPinConv(LEDpin)));
    delay(200);
    digitalWrite(IAS.dPinConv(LEDpin), !digitalRead(IAS.dPinConv(LEDpin)));
    delay(200);
    digitalWrite(IAS.dPinConv(LEDpin), !digitalRead(IAS.dPinConv(LEDpin)));
  });

  IAS.onFirmwareUpdateProgress([](int written, int total){
      Serial.print(".");
      digitalWrite(IAS.dPinConv(LEDpin), !digitalRead(IAS.dPinConv(LEDpin)));
  });
  
 /* 
  IAS.onFirstBoot([]() {
    IAS.eraseEEPROM('P');                   // Optional! What to do with EEPROM on First boot of the app? 'F' Fully erase | 'P' Partial erase
  });
*/  



  IAS.begin();                              // Run IOTAppStory
  IAS.setCallHomeInterval(7200);              // Call home interval in seconds(disabled by default), 0 = off, use 60s only for development. Please change it to at least 2 hours in production
  
	
  //-------- Your Setup starts from here ---------------
  
  
  pinMode(IAS.dPinConv(LEDpin), OUTPUT);
  pinMode(IAS.dPinConv(trigPin), OUTPUT);
  pinMode(IAS.dPinConv(echoPin), INPUT);



  Serial.println(F("Starting I2CDemo example program for BME280"));
  Serial.print(F("- Initializing BME280 sensor\n"));

  while (!BME280.begin(I2C_STANDARD_MODE)) // Start BME280 using I2C protocol
  {
    Serial.println(F("-  Unable to find BME280. Waiting 3 seconds."));
    delay(3000);
  } // of loop until device is located
  BME280.mode(SleepMode);
  Serial.print(F("- Sensor detected in operating mode \""));
  Serial.print(BME280.mode());
  Serial.println(F("\"."));
  if(BME280.mode()==0) 
  {
    Serial.print(F("- Turning sensor to normal mode, mode is now \""));
    Serial.print(BME280.mode(NormalMode)); // Use enumerated type values
    Serial.println("\"");
  } // of if-then we have sleep mode
  Serial.println(F("- Setting 16x oversampling for all sensors"));
  BME280.setOversampling(TemperatureSensor,Oversample16);
  BME280.setOversampling(HumiditySensor,   Oversample16);
  BME280.setOversampling(PressureSensor,   Oversample16);
  Serial.println(F("- Setting IIR filter to maximum value of 16 samples"));
  BME280.iirFilter(IIR16);
  Serial.println(F("- Setting time between measurements to 1 second"));
  BME280.inactiveTime(inactive1000ms);
  Serial.print(F("- Each measurement cycle will take "));
  Serial.print(BME280.measurementTime(MaximumMeasure)/1000);
  Serial.println(F("ms.\n\n"));
}



// ================================================ LOOP =================================================
void loop() {
  IAS.loop();   // this routine handles the calling home functionality,
                // reaction of the MODEBUTTON pin. If short press (<4 sec): update of sketch, long press (>7 sec): Configuration
                // reconnecting WiFi when the connection is lost,
                // and setting the internal clock (ESP8266 for BearSSL)


  //-------- Your Sketch starts from here ---------------

	
  if (millis() - blinkEntry > atoi(blinkTime) && digitalRead(MODEBUTTON) == HIGH) {
    digitalWrite(IAS.dPinConv(LEDpin), !digitalRead(IAS.dPinConv(LEDpin)));
    blinkEntry = millis();

    // Serial feedback
    Serial.println(F(TBVERSION));
  }

  if (millis() - tbEntry > atoi(thingsBoardTime) && digitalRead(MODEBUTTON) == HIGH) {
    
    tbEntry = millis();

    static int32_t temperature, humidity, pressure, odleglosc;      // Store readings
    static float  temperature1, humidity1, pressure1, odleglosc1;      // Store readings
    
    BME280.getSensorData(temperature,humidity,pressure); // Get most recent readings
    temperature1 = temperature/100.0;
    humidity1= humidity/100.0;
    pressure1= pressure/100.0;
    
    Serial.print(F("Temperature: "));
    Serial.print(temperature1); // Temperature in deci-degrees
    Serial.print(F("C "));
    Serial.print(F("Humidity: "));
    Serial.print(humidity1); // Humidity in deci-percent
    Serial.print(F("% "));
    Serial.print(F("Pressure: "));
    Serial.print(pressure1);
    Serial.println(F("hPa"));

    if (!tb.connected()) {
      // Connect to the ThingsBoard
      Serial.print("Connecting to: ");
      Serial.print(thingsBoardServer);
      Serial.print(":");
      Serial.print(thingsBoardPort);
      Serial.print(" with token ");
      Serial.println(thingsBoardToken);
      if (!tb.connect(thingsBoardServer, thingsBoardToken, atoi(thingsBoardPort))) {
        Serial.println("Failed to connect");
        return;
      }
    }
  
    Serial.println("Sending data to ThingsBoard ...");

    // tb.sendTelemetryFloat("temperature", temperature/100.0);
    // tb.sendTelemetryFloat("humidity", humidity/100.0);
    // tb.sendTelemetryFloat("pressure", pressure/100.0);

    Serial.println("Sending telemetry data...");
    Telemetry data[3] = {
      { "temperature" , temperature1 },
      { "humidity"    , humidity1 },
      { "pressure"    , pressure1},
    };
    
    tb.sendTelemetry(data, 3);

    if (atoi(pomiarOdleglosci) == 1){
      digitalWrite(IAS.dPinConv(trigPin), LOW);
      delayMicroseconds(2);
      digitalWrite(IAS.dPinConv(trigPin), HIGH);
      delayMicroseconds(10);
      digitalWrite(IAS.dPinConv(trigPin), LOW);

      odleglosc = pulseIn(IAS.dPinConv(echoPin), HIGH);

      odleglosc1 = odleglosc*0.034/2;

      Serial.print(F("Odleglosc: "));
      Serial.println(odleglosc1); // Temperature in deci-degrees
      tb.sendTelemetryFloat("distance", odleglosc1);
    }

    Serial.println("Sending attributes data...");

    Attribute attributes[2] = {
      { "app_version",  TBVERSION },
      { "app_active",       true     },
    };

    tb.sendAttributes(attributes, 2);    
  }

  tb.loop();    
  
}
