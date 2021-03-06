
#define COMPDATE __DATE__ __TIME__
#define MODEBUTTON 0                                        // Button pin on the esp for selecting modes. D3 for the Wemos!
// #define TOKEN               "eDtTW5XThhi992DZdtcX"
#define TBVERSION "Ver 1.1.18"
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

char *LEDpin    = "2";				
char *trigPin    = "2";
char *echoPin    = "2";
char *blinkTime = "1000";
char *thingsBoardTime = "30000";
char *thingsBoardToken = TOKEN;
char *thingsBoardServer = THINGSBOARD_SERVER;
char *thingsBoardPort = THINGSBOARD_PORT;
char *pomiarOdleglosci = "1";

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

    static int32_t temperature, humidity, pressure, odleglosc[5];      // Store readings
    static float  temperature1, humidity1, pressure1, odleglosc1,avgodleglosc1=0;      // Store readings
    int32_t odlMin = 0,odlMax = 2147483647;
    int8_t odlMinPos = 0,odlMaxPos = 0;
    
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
      odlMin = 0;
      odlMax = 2147483647;
      odlMinPos = 0;
      odlMaxPos = 0;
      
      for(int8_t licz = 0; licz < 5 ; licz++){
        odleglosc[licz] = zmierz1raz(); 
        
        if(odleglosc[licz] > odlMin){
          odlMin = odleglosc[licz];
          odlMinPos = licz;
        }
        if(odleglosc[licz] < odlMax){
          odlMax = odleglosc[licz];
          odlMaxPos = licz;
        }
        delay(100);
      }
      odleglosc[odlMaxPos] =0;
      for(int8_t licz = 0; licz < 5 ; licz++){
        if((licz != odlMinPos) && (licz != odlMaxPos)){
          odleglosc[odlMaxPos] += odleglosc[licz];
        }
      }

      odleglosc1 = odleglosc[odlMaxPos]*0.034/6;

      if (avgodleglosc1 < 1){
        avgodleglosc1 = odleglosc1; 
      }
               
      Serial.print(F("Odleglosc: "));
      Serial.println(odleglosc1); // Temperature in deci-degrees
      Serial.print(F("Odleglosc avg: "));
      Serial.println(avgodleglosc1); // Temperature in deci-degrees
      
      if(odleglosc1 > 1.2*avgodleglosc1 || odleglosc1 < 0.8*avgodleglosc1){
        Serial.print(F("Odleglosc ERROR "));
        avgodleglosc1 = 0.95*avgodleglosc1 + 0.05*odleglosc1;
      } 
      else {
        tb.sendTelemetryFloat("distance", odleglosc1);
        avgodleglosc1 = 0.9*avgodleglosc1 + 0.1*odleglosc1;
      }

      
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

uint32_t zmierz1raz(){
    digitalWrite(IAS.dPinConv(trigPin), LOW);
    delayMicroseconds(2);
    digitalWrite(IAS.dPinConv(trigPin), HIGH);
    delayMicroseconds(10);
    digitalWrite(IAS.dPinConv(trigPin), LOW);

    return pulseIn(IAS.dPinConv(echoPin), HIGH); 
}
