//gerekli kütüphaneleri tanımladık.
//herhangi bir kütüphane yüklemenize gerek yok zaten bu kütüphaneler mevcutta var.

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

//ağ bilgilerinizi girin
const char* ssid = "*******";
const char* password = "*********";

//Millis fonksiyonu ile ledi yakıp söndüreceğiz çünkü delay kullanırsak kod duracağı için yeni kod atarken sorun olacaktır.
const int led = D0; // Ledimizi bağlayacağımız pini tanımladık
unsigned long oncekiZaman = 0;  // son zaman bilgisini tutacağız
const long aralik = 1000;  // milisaniye olarak ledin yanıp sönme aralığı
int ledDurumu = LOW;  // ledin durumunu takip etmek için gerekli değişkenimiz

void setup() {
pinMode(led, OUTPUT); //pin modunu çıkış olarak tanımladık

    
  Serial.begin(115200);
  Serial.println("Başlatılıyor");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Bağlantı hatası, yeniden başlıyor!!!");
    delay(5000); //5sn bekle
    ESP.restart();//sistemi yeniden başlat
  }

  //iletişim için gerekli port
  // standart olarak  8266 portu gelir
  // ArduinoOTA.setPort(8266); //komutu ile değiştirilebilir

  // Sunucu ismi olarak  esp8266-[ChipID] gelir
  // ArduinoOTA.setHostname("myesp8266"); //komutu ile değiştirilebilir

  // Standart olarak şifre sormaz ama sorması istenirse
  // ArduinoOTA.setPassword("admin"); //komutu ile şifre belirlenebilir

  // Aynı zamanda bu şifre MD5 kriptolama algoritması ile kriptolanabilir.
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

//////////////////////////////////////////////////////////////////////////////////////
//daha sonra yeniden OTA kod atabilmek için gerekli OTA tanımlamalarını başlatmalıyız
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOT: FS kullandıysanız FS.end()komutu ile dosyayı kapatmalısınız
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Hata[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Yetki Hatası");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Baslatma Basarisiz");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Baglanti Basarisiz");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Veri Alinamadi");
    else if (error == OTA_END_ERROR) Serial.println("Sonlandirma Basarisiz");
  });
  ArduinoOTA.begin();//OTA'yi başlatıyor
  Serial.println("Sistem Hazir");
  Serial.print("IP Adresiniz: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();//sonraki kod atma işlemleri için kullanmamız gerekiyor

//ledi yakıp söndürme işlemini delay kullanmadan millis() fonksiyonu ile zaman tutarak yapalım
  unsigned long simdikiZaman = millis();
  if (simdikiZaman - oncekiZaman >= aralik) {
  // LED'i yaktığımız son zamanı kaydedelim
  oncekiZaman = simdikiZaman;
  // yanıksa söndür, sönükse yaktır diyelim
  ledDurumu = not(ledDurumu);
  // ve çıkışa yazdıralım:
  digitalWrite(led,  ledDurumu);
  }

}
