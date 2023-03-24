#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>
dht DHT;

#define grzanie_pin 11
#define chlodzenie_pin 2
#define suszenie_pin 3
#define nawilzanie_pin 4
#define migacz_grzaniechlodzenie_pin 7
#define migacz_suszenienawilzanie_pin 8
#define czujnik_pin 9

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
DS3231 rtc(SDA, SCL);

int grzaniechlodzenie_stan = 1;
int migacz_grzaniechlodzenie_stan = 1;
int suszenienawilzanie_stan = 1;
int migacz_suszenienawilzanie_stan = 1;

int grzaniechlodzenie_led = 0;
int suszenienawilzanie_led = 0;

int grzaniechlodzeniaktywny;
int migacz_grzaniechlodzeniaktywny;
int suszenienawilzaniaktywny;
int migacz_suszenienawilzaniaktywny;

int nawilzaj;
int susz;
int jest_wilgotno;
int grzej;
int ochladzaj;
int jest_cieplo;

String odebrane;
int progGrzania = 19;
int progChlodzenia = 25;
int dobraTemperatura = 23;
int progSuszenia = 65;
int progNawilzania = 40;
int dobraWilgotnosc = 55;
String progGrzaniaS;
String progChlodzeniaS;
String dobraTemperaturaS;
String progSuszeniaS;
String progNawilzaniaS;
String dobraWilgotnoscS;

void setup()
{
  Serial.begin(9600);

  pinMode(grzanie_pin, OUTPUT);
  pinMode(chlodzenie_pin, OUTPUT);
  pinMode(migacz_grzaniechlodzenie_pin, OUTPUT);
  pinMode(suszenie_pin, OUTPUT);
  pinMode(nawilzanie_pin, OUTPUT);
  pinMode(migacz_suszenienawilzanie_pin, OUTPUT);
  pinMode(czujnik_pin, INPUT);

  lcd.begin(20, 4);
  lcd.setCursor(0, 0);

  rtc.begin();
}


void loop() {
  odebrane = String(Serial.read());
  progGrzaniaS = odebrane.charAt(0)+odebrane.charAt(1);
  progChlodzeniaS = odebrane.charAt(2)+odebrane.charAt(3);
  dobraTemperaturaS = odebrane.charAt(4)+odebrane.charAt(5);
  progSuszeniaS = odebrane.charAt(6)+odebrane.charAt(7);
  progNawilzaniaS = odebrane.charAt(8)+odebrane.charAt(9);
  dobraWilgotnoscS = odebrane.charAt(10)+odebrane.charAt(11);
  progGrzania = progGrzaniaS.toInt();
  progChlodzenia = progChlodzeniaS.toInt();
  dobraTemperatura = dobraTemperaturaS.toInt();
  progSuszenia = progSuszeniaS.toInt();
  progNawilzania = progNawilzaniaS.toInt();
  dobraWilgotnosc = dobraWilgotnoscS.toInt();
  
  int grzanie;
  int chlodzenie;
  int suszenie;
  int nawilzanie;

  int grzaniechlodzenie_aktywny;
  int migacz_grzaniechlodzenie_aktywny;
  int suszenienawilzanie_aktywny;
  int migacz_suszenienawilzanie_aktywny;

  int x = DHT.read11(czujnik_pin);

  grzanie = digitalRead(grzanie_pin);
  chlodzenie = digitalRead(chlodzenie_pin);
  suszenie = digitalRead(suszenie_pin);
  nawilzanie = digitalRead(nawilzanie_pin);

if (millis() - grzaniechlodzeniaktywny > 5000)
  {
    grzaniechlodzenie_aktywny = 1;
  } else {
    grzaniechlodzenie_aktywny = 0;
  }

  if (DHT.temperature <= progGrzania) {
    grzej = 1;
  }
  else
  {
    grzej = 0;
  }

  if (DHT.temperature >= progChlodzenia) {
    ochladzaj = 1;
  }
  else
  {
    ochladzaj = 0;
  }

  if (DHT.temperature > dobraTemperatura) {
    jest_cieplo = 1;
  }
  else
  {
    jest_cieplo = 0;
  }


  grzaniechlodzenie(grzaniechlodzenie_aktywny,
  grzej, ochladzaj, jest_cieplo);
  if (millis() - migacz_grzaniechlodzeniaktywny > 333) {
    migacz_grzaniechlodzenie_aktywny = 1;
  } else {
    migacz_grzaniechlodzenie_aktywny = 0;
  }

  migacz_grzaniechlodzenie(migacz_grzaniechlodzenie_aktywny,
  grzaniechlodzenie_led);


if (millis() - suszenienawilzaniaktywny > 5000)
  {
    suszenienawilzanie_aktywny = 1;
  } else {
    suszenienawilzanie_aktywny = 0;
  }
  
  if (DHT.humidity <= progNawilzania) {
    nawilzaj = 1;
  }
  else
  {
    nawilzaj = 0;
  }


  if (DHT.humidity >= progSuszenia) {
    susz = 1;
  }
  else
  {
    susz = 0;
  }

  if (DHT.humidity > dobraWilgotnosc) {
    jest_wilgotno = 1;
  }
  else
  {
    jest_wilgotno = 0;
  }

  suszenienawilzanie(suszenienawilzanie_aktywny,
  nawilzaj, susz, jest_wilgotno);



  if (millis() - migacz_suszenienawilzaniaktywny > 333) {
    migacz_suszenienawilzanie_aktywny = 1;
  } else {
    migacz_suszenienawilzanie_aktywny = 0;
  }

  migacz_suszenienawilzanie
 (migacz_suszenienawilzanie_aktywny, suszenienawilzanie_led);


}
void grzaniechlodzenie
(int grzaniechlodzenie_aktywny, int grzej,
 int ochladzaj, int T)
{
  grzaniechlodzenie_stankolejny
 (grzaniechlodzenie_aktywny, grzej, ochladzaj, jest_cieplo);
  grzaniechlodzenie_skutek();
}

void migacz_grzaniechlodzenie
(int migacz_grzaniechlodzenie_aktywny,
 int grzaniechlodzenie_led)
{
  migacz_grzaniechlodzenie_stankolejny
 (migacz_grzaniechlodzenie_aktywny, grzaniechlodzenie_led);
  migacz_grzaniechlodzenie_skutek();
}

void suszenienawilzanie
(int suszenienawilzanie_aktywny, int nawilzaj,
 int susz, int H)
{
  suszenienawilzanie_stankolejny
 (suszenienawilzanie_aktywny, nawilzaj, susz, jest_wilgotno);
  suszenienawilzanie_skutek();
}

void migacz_suszenienawilzanie
(int migacz_suszenienawilzanie_aktywny, 
 int suszenienawilzanie_led)
{
  migacz_suszenienawilzanie_stankolejny
  (migacz_suszenienawilzanie_aktywny,
   suszenienawilzanie_led);
  migacz_suszenienawilzanie_skutek();
}


void grzaniechlodzenie_stankolejny
(int grzaniechlodzenie_aktywny, int grzej,
 int ochladzaj, int jest_cieplo)
{
  switch (grzaniechlodzenie_stan)
  {
    case 1:
      if (grzej == 1) {
        grzaniechlodzenie_stan = 3;
      }
      else if (ochladzaj == 1) {
        grzaniechlodzenie_stan = 2;
      }
      else
        grzaniechlodzenie_stan = 1;
      break;
    case 2:
      if (jest_cieplo == 0)
      {
        grzaniechlodzenie_stan = 4;
      }
      else
        grzaniechlodzenie_stan = 2;
      break;
    case 3:
      if (jest_cieplo == 1)
      {
        grzaniechlodzenie_stan = 5;
      }
      else
        grzaniechlodzenie_stan = 3;
      break;
    case 4:
      if (grzaniechlodzenie_aktywny == 1) {
        grzaniechlodzenie_stan = 1;
      }
      break;
    case 5:
      if (grzaniechlodzenie_aktywny == 1) {
        grzaniechlodzenie_stan = 1;
      }
      break;
    default:
      break; }

  lcd.setCursor(0, 0);
  lcd.print(rtc.getTimeStr());

  lcd.setCursor(10, 0);
  lcd.print(rtc.getDateStr());

  lcd.setCursor(0, 2);
  lcd.print("Temp=");

  lcd.setCursor(0, 3);
  lcd.print(DHT.temperature);

  lcd.setCursor(5, 3);
  lcd.print("C");

  lcd.setCursor(15, 2);
  lcd.print("Wilg=");

  lcd.setCursor(14, 3);
  lcd.print(DHT.humidity);

  lcd.setCursor(19, 3);
  lcd.print("%");

  delay(333);

}

void grzaniechlodzenie_skutek()
{
  switch (grzaniechlodzenie_stan)
  {
    case 1:
      digitalWrite(grzanie_pin, LOW);
      digitalWrite(chlodzenie_pin, LOW);
      break;

    case 2:
      digitalWrite(grzanie_pin, LOW);
      digitalWrite(chlodzenie_pin, HIGH);
      grzaniechlodzenie_led = 1;
      grzaniechlodzeniaktywny = millis();
      break;

    case 3:
      digitalWrite(grzanie_pin, HIGH);
      digitalWrite(chlodzenie_pin, LOW);
      grzaniechlodzenie_led = 1;
      grzaniechlodzeniaktywny = millis();
      break;

    case 4:
      digitalWrite(grzanie_pin, LOW);
      digitalWrite(chlodzenie_pin, LOW);
      grzaniechlodzenie_led = 0;
      break;

    case 5:
      digitalWrite(grzanie_pin, LOW);
      digitalWrite(chlodzenie_pin, LOW);
      grzaniechlodzenie_led = 0;
      break;

    default:
      break;
  }
}


void migacz_grzaniechlodzenie_stankolejny
(int migacz_grzaniechlodzenie_aktywny,
 int grzaniechlodzenie_led)
{
  switch (migacz_grzaniechlodzenie_stan)
  {
    case 1:
      if (grzaniechlodzenie_led == 1) {
        migacz_grzaniechlodzenie_stan = 2;
      }
      break;

    case 2:
      migacz_grzaniechlodzenie_stan = 3;
      if (grzaniechlodzenie_led == 0) {
        migacz_grzaniechlodzenie_stan = 6;
      }

    case 3:
      if (migacz_grzaniechlodzenie_aktywny == 1) {
        migacz_grzaniechlodzenie_stan = 4;
      }

      if (grzaniechlodzenie_led == 0) {
        migacz_grzaniechlodzenie_stan = 6;
      }

      break;

    case 4:
      migacz_grzaniechlodzenie_stan = 5;
      if (grzaniechlodzenie_led == 0) {
        migacz_grzaniechlodzenie_stan = 6;
      }

      break;

    case 5:
      if (migacz_grzaniechlodzenie_aktywny == 1) {
        migacz_grzaniechlodzenie_stan = 2;
      }



      if (grzaniechlodzenie_led == 0) {
        migacz_grzaniechlodzenie_stan = 6;
      }
      break;

    default:
      migacz_grzaniechlodzenie_stan = 1;
      break; 
     }
  }

void migacz_grzaniechlodzenie_skutek()
{
  switch (migacz_grzaniechlodzenie_stan)
  {
    case 2:
      digitalWrite(migacz_grzaniechlodzenie_pin, HIGH);
      migacz_grzaniechlodzeniaktywny = millis();
      break;

    case 4:
      digitalWrite(migacz_grzaniechlodzenie_pin, LOW);
      migacz_grzaniechlodzeniaktywny = millis();
      break;

    case 6:
      digitalWrite(migacz_grzaniechlodzenie_pin, LOW);
      break;

    default:
      break;
  }
}


void suszenienawilzanie_stankolejny
(int suszenienawilzanie_aktywny, int nawilzaj, int susz,
 int jest_wilgotno)
{
  switch (suszenienawilzanie_stan)
  {
    case 1:
      if (nawilzaj == 1) {
        suszenienawilzanie_stan = 3;
      }
      else if (susz == 1) {
        suszenienawilzanie_stan = 2;
      }
      else
        suszenienawilzanie_stan = 1;
      break;

    case 2:
      if (jest_wilgotno==0)
      {
        suszenienawilzanie_stan = 4;
      }
      break;

    case 3:
      if (jest_wilgotno==1) {
        suszenienawilzanie_stan = 5;
      }
      break;

    case 4:
      if (suszenienawilzanie_aktywny == 1) {
        suszenienawilzanie_stan = 1;
      }
      break;

    case 5:
      if (suszenienawilzanie_aktywny == 1) {
        suszenienawilzanie_stan = 1;
      }
      break;

    default:
      break;
  }
}
void suszenienawilzanie_skutek()
{
  switch (suszenienawilzanie_stan)
  {
    case 1:
      digitalWrite(nawilzanie_pin, LOW);
      digitalWrite(suszenie_pin, LOW);
      break;

    case 2:
      digitalWrite(nawilzanie_pin, LOW);
      digitalWrite(suszenie_pin, HIGH);

      suszenienawilzanie_led = 1;
      suszenienawilzaniaktywny = millis();
      break;

    case 3:
      digitalWrite(nawilzanie_pin, HIGH);
      digitalWrite(suszenie_pin, LOW);

      suszenienawilzanie_led = 1;
      suszenienawilzaniaktywny = millis();
      break;

    case 4:
      digitalWrite(nawilzanie_pin, LOW);
      digitalWrite(suszenie_pin, LOW);

      suszenienawilzanie_led = 0;
      break;

    case 5:
      digitalWrite(nawilzanie_pin, LOW);
      digitalWrite(suszenie_pin, LOW);

      suszenienawilzanie_led = 0;
      break;

    default:
      break;
  }
}


void migacz_suszenienawilzanie_stankolejny
(int migacz_suszenienawilzanie_aktywny,
 int  suszenienawilzanie_led)
{
  switch (migacz_suszenienawilzanie_stan)
  {
    case 1:
      if (suszenienawilzanie_led == 1) {
        migacz_suszenienawilzanie_stan = 2;
      }
      break;

    case 2:
      migacz_suszenienawilzanie_stan = 3;
      if (suszenienawilzanie_led == 0) {
        migacz_suszenienawilzanie_stan = 6;
      }

    case 3:
      if (migacz_suszenienawilzanie_aktywny == 1) {
        migacz_suszenienawilzanie_stan = 4;
      }
      if (suszenienawilzanie_led == 0) {
        migacz_suszenienawilzanie_stan = 6;
      }
      break;

    case 4:
      migacz_suszenienawilzanie_stan = 5;
      if (suszenienawilzanie_led == 0) {
        migacz_suszenienawilzanie_stan = 6;
      }
      break;

    case 5:
      if (migacz_suszenienawilzanie_aktywny == 1) {
        migacz_suszenienawilzanie_stan = 2;
      }
      if (suszenienawilzanie_led == 0) {
        migacz_suszenienawilzanie_stan = 6;
      }
      break;

    default:
      migacz_suszenienawilzanie_stan = 1;
      break;
  }
}


void migacz_suszenienawilzanie_skutek()
{

  switch (migacz_suszenienawilzanie_stan)
  {
    case 2:
      digitalWrite(migacz_suszenienawilzanie_pin, HIGH);
      migacz_suszenienawilzaniaktywny = millis();
      break;

    case 4:
      digitalWrite(migacz_suszenienawilzanie_pin, LOW);
      migacz_suszenienawilzaniaktywny = millis();
      break;

    case 6:
      digitalWrite(migacz_suszenienawilzanie_pin, LOW);
      break;

    default:
      break;

  }
}
