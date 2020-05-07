
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "konveyeur.firebaseio.com"
#define FIREBASE_AUTH "1Cetmp50V2NJFqUhBoahTkYFpDz8dNMFEvdwUReQ"
#define WIFI_SSID "SLS-WIFI"
#define WIFI_PASSWORD "aira2009"
#define mulai D6
#define henti D7

int nowTime, lastTime;
bool out;
int flag = 0,flagToogle;
int lastVar;
void setup() {
  Serial.begin(9600);
  pinMode(mulai, INPUT_PULLUP);
  pinMode(henti, INPUT_PULLUP);

  pinMode(14, OUTPUT);pinMode(D0,OUTPUT);
digitalWrite(D0,HIGH);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //FirebaseObject object = Firebase.get("/");
  //out =  Firebase.getBool("nilai");
  //Firebase.set("nilai", 0);
}

void loop() {
  nowTime = millis();


  if (nowTime - lastTime <= 200) {}
  else {
    lastTime = nowTime;
    if (Firebase.failed()) {
      Serial.print("setting / Firebase failed:");
      digitalWrite(D0,HIGH);
      Serial.println(Firebase.error());
      return;
    }
    else digitalWrite(D0,LOW);
  }
  Serial.print(digitalRead(mulai));Serial.print(" ");
  Serial.println(digitalRead(henti));

  if (digitalRead(mulai) == LOW ) {
    //while(!digitalRead(mulai)){}//Deboncing    
    Firebase.setInt("Conveyor/C3/Nilai",1);
    flagToogle=1;
 
    
    
  }
   else if (digitalRead(henti) == LOW ) {
      //while(!digitalRead(henti)){}//Deboncing
      Firebase.setInt("Conveyor/C3/Nilai",0);
      flagToogle=0;
  }

  if(Firebase.getInt("Conveyor/C3/Nilai")==1){
      flagToogle=1;
      }
  else if(Firebase.getInt("Conveyor/C3/Nilai")==0){
      flagToogle=0;
      }   


   if(flagToogle==1)digitalWrite(14,HIGH);
   else if(flagToogle==0)digitalWrite(14,LOW);


}

