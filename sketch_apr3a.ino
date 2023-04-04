#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define BLYNK_TEMPLATE_ID "TMPL6dpFQe7Y6"
#define BLYNK_TEMPLATE_NAME "posttest2"
#define BLYNK_AUTH_TOKEN "OVCBCdvdy23TkIlcfoLB-TJvP9sNue-4"

#define BLYNK_PRINT Serial

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Universitas Mulawarman";  // type your wifi name
char pass[] = "";  // type your wifi password

#define LEDPIN3 D4 //Kaki anoda dari LED terhubung ke pin D4 NodeMCU
#define LEDPIN2 D2
#define LEDPIN1 D0  
#define DHTPIN D5 //Pin data dari DHT terhubung ke pin D4 NodeMCU
#define DHTTYPE DHT11 //Mengatur TYPE DHT (Karena ada 2 jenis [DHT11 & DHT22])

BlynkTimer timer;

DHT dht(DHTPIN, DHTTYPE);

// Untuk kontroling LED
BLYNK_WRITE(V1) { // V1 adalah pin LED yang sudah kita atur pada Blynk
  digitalWrite(LEDPIN1, param.asInt()); // Mengubah nilai LED dari Blynk
}//hera

BLYNK_WRITE(V2) { // V2 adalah pin LED yang sudah kita atur pada Blynk
  digitalWrite(LEDPIN2, param.asInt()); // Mengubah nilai LED dari Blynk
}//cantika
BLYNK_WRITE(V3) { // V3 adalah pin LED yang sudah kita atur pada Blynk
  digitalWrite(LEDPIN3, param.asInt()); // Mengubah nilai LED dari Blynk
}//riska

void setup(){
  Serial.begin(115200);
  // Mengatur pin LED
  pinMode(LEDPIN1, OUTPUT);
  pinMode(LEDPIN2, OUTPUT);
  pinMode(LEDPIN3, OUTPUT);
  // Setup Blynk
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  // Setup Sensor DHT 11
  dht.begin();
  // Fungsi mengirim data setiap 2,5 detik
  timer.setInterval(2500L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}

void sendSensor(){ //riska
  float t = dht.readTemperature();
  // Mengecek kondisi apakah DHT bisa dibaca atau tidak
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Mengatur nilai suhu ke pin V0(Suhu) yang sudah diatur pada Blynk
  Blynk.virtualWrite(V0, t);
 
  // Menampilkan ke serial monitor
  Serial.print("Suhu : ");
  Serial.print(t);
  // Event log
  if(t < 20){//hera
    Blynk.logEvent("notifikasi","Suhu dibawah 20 Derajat celcius");
    digitalWrite(LEDPIN1, HIGH);
    digitalWrite(LEDPIN2, LOW);
    digitalWrite(LEDPIN3, LOW);
  }
  if( 20 < t < 27){//cantika
  
    Blynk.logEvent("notifikasi","Suhu diantara 21 sampai 26 Derajat celcius");
    digitalWrite(LEDPIN2, HIGH);
    digitalWrite(LEDPIN1, LOW);
    digitalWrite(LEDPIN3, LOW);
  }
  if( t > 27){//riska
    Blynk.logEvent("notifikasi","Suhu diatas 27 Derajat celcius");
    digitalWrite(LEDPIN3, HIGH);
    digitalWrite(LEDPIN1, LOW);
    digitalWrite(LEDPIN2, LOW);
  }
}