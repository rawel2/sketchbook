
/*************************************************************************************

  Mark Bramwell, July 2010

  This program will test the LCD panel and the buttons.When you push the button on the shield，
  the screen will show the corresponding one.
 
  Connection: Plug the LCD Keypad to the UNO(or other controllers)

**************************************************************************************/
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include "pitches.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
byte timer_time = 5;
byte eeaddress = 100;
char timer_timet = 'M';
byte timer_times = 10;
long current_sec = 0;
long current_sec_time = 0;
long old_current_sec_time = 0;

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


#define btnRIGHT  0   //0
#define btnUP     1   //131
#define btnDOWN   2   //307
#define btnLEFT   3   //479
#define btnSELECT 4   //720
#define btnNONE   5   //1023
#define btnLONG   20

int read_LCD_buttons_(){               // read the buttons
    adc_key_in = analogRead(0);       // read the value from the sensor 

    // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
    // we add approx 50 to those values and check to see if we are close
    // We make this the 1st option for speed reasons since it will be the most likely result

    if (adc_key_in > 1000) return btnNONE; 

    // For V1.1 us this threshold
    if (adc_key_in < 50)   return btnRIGHT;  
    if (adc_key_in < 250)  return btnUP; 
    if (adc_key_in < 420)  return btnDOWN; 
    if (adc_key_in < 650)  return btnLEFT; 
    if (adc_key_in < 850)  return btnSELECT;  

    return btnNONE;                // when all others fail, return this.
}

int read_LCD_buttons(){
  int curr_rob = read_LCD_buttons_();
  long curr_millis = millis();
  
  if(curr_rob == btnNONE) return(btnNONE);
  delay(50);
  if(read_LCD_buttons_() != curr_rob) return(btnNONE);
  while(read_LCD_buttons_() != btnNONE){
    delay(10);
  }
  if(millis() - curr_millis > 700) return(curr_rob+btnLONG);
  return(curr_rob);
}

void melodia(void) {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(2, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(2);
  }
}


void printFixedWidth(Print &out, int number, byte width, char filler = ' '){
  unsigned int temp = number;
   
  //see how wide the number is
  while(temp && width){
    temp /= 10;
    width--;
  }

  if(!number) width--;
  
  //start by printing the rest of the width with 0
  while(width){
    out.print(filler);
    width--;
  }
  
  out.print(number);
}

void read_from_eeprom(){
  if(EEPROM.read(eeaddress) == 66){
    timer_time = EEPROM.read(eeaddress+1);
    timer_timet = (char)EEPROM.read(eeaddress+2);
    timer_times = EEPROM.read(eeaddress+3);
  }
}

void save_to_eeprom(){
   EEPROM.write(eeaddress, 66);
   EEPROM.write(eeaddress+1,timer_time);
   EEPROM.write(eeaddress+2,timer_timet);
   EEPROM.write(eeaddress+3,timer_times);
}


void setup(){
   lcd.begin(16, 2);               // start the library
   lcd.setCursor(0,0);             // set the LCD cursor   position 
   lcd.print("Timer :");  // print a simple message on the LCD
   read_from_eeprom();
}


 
void loop(){
   lcd.setCursor(8,0);             // move cursor to second line "1" and 9 spaces over
   //lcd.print(timer_time);    
   printFixedWidth(lcd, timer_time, 2);
   lcd.print(timer_timet);
   lcd.print(" X");// display seconds elapsed since power-up
   
   lcd.setCursor(14,0);             // move cursor to second line "1" and 9 spaces over
   // lcd.print(timer_times);    
   printFixedWidth(lcd, timer_times, 2);
   lcd.print(" ");// display seconds elapsed since power-up
   

   lcd.setCursor(0,1);             // move to the begining of the second line
   lcd_key = read_LCD_buttons();   // read the buttons

   switch (lcd_key){               // depending on which button was pushed, we perform an action

       case btnRIGHT:{             //  push button "RIGHT" and show the word on the screen
            timer_times += 1;
            break;
       }
       case btnLEFT:{
             timer_times -= 1;
             break;
       }    
       case btnUP:{
             timer_time += timer_timet == 'M' ? 1:5;
             break;
       }
       case btnDOWN:{
             timer_time -= timer_timet == 'M' ? 1:5;
             break;
       }
       case btnSELECT:{
             start_count();  //  push button "SELECT" and show the word on the screen
             break;
       }
       case btnSELECT+btnLONG:{
             save_to_eeprom();  //  push button "SELECT" and show the word on the screen
             lcd.print("SAVED            ");
             delay(800);
             break;
       }
       case btnNONE:{
             lcd.print("SELECT - START  ");  //  No action  will show "None" on the screen
             break;
       }
   }
   
   //
   
   if (timer_time < 1){
    if(timer_timet == 'M'){
      timer_time=55;
      timer_timet = 'S';
    }
    else{
      timer_time=5;  
    }
    
   }
   
   
   if(timer_time > 55){
    if(timer_timet == 'S'){
      timer_time=1;
      timer_timet = 'M';
    }
    else{
      timer_time=55;  
    }
   }
   
   if (timer_times < 1){
    timer_times=1;
   }

   if(timer_times > 55){
    timer_times=50;
   }
   
}


void start_count(void){
  tone(2, NOTE_C6, 400);
  delay(450);
  noTone(2);
  
  for(int i = 1 ;i <= timer_times;i++)
  {
    lcd.setCursor(0,1);
    lcd.print("TIME  :                 ");
    lcd.setCursor(7,1);
    if(timer_timet == 'M'){
      current_sec = millis()/1000+(timer_time * 60); 
      printFixedWidth(lcd, timer_time * 60, 3);
    }
    else{
      current_sec = millis()/1000+timer_time;
      printFixedWidth(lcd, timer_time , 3);
    }
    
    current_sec_time = current_sec -millis()/1000;
    old_current_sec_time =current_sec_time;
    
    
    
    lcd.setCursor(10,1);
    lcd.print("S X ");
    //lcd.print(timer_times);
    printFixedWidth(lcd, i, 2);
    
    while ( (current_sec_time>0) and (read_LCD_buttons() != btnDOWN)){
      current_sec_time = current_sec -millis()/1000;
      if (current_sec_time < old_current_sec_time){
        lcd.setCursor(7,1);
        // lcd.print(current_sec_time);
        printFixedWidth(lcd, current_sec_time, 3);
        
        if (current_sec_time< 10){
          tone(2, NOTE_C4, 200);
          delay(250);
          noTone(2);
          if (current_sec_time< 5){
            tone(2, NOTE_C4, 200);
            delay(250);
            noTone(2);
          }  
        
        }
      old_current_sec_time =current_sec_time;
      }
    }
    melodia();
  }
  tone(2, NOTE_C6, 400);
  delay(550);
  noTone(2);
  tone(2, NOTE_C6, 400);
  delay(550);
  noTone(2);
  tone(2, NOTE_C6, 400);
  delay(550);
  noTone(2);
};
