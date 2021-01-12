//gerekli kütüphaneleri tanımladık.
//herhangi bir kütüphane yüklemenize gerek yok zaten bu kütüphaneler mevcutta var.
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

//ağ bilgilerinizi girin
#ifndef STASSID
#define STASSID "************"
#define STAPSK  "********"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

void setup() {
  Serial.begin(115200);
  Serial.println("Baslatiliyor");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Bağlantı hatası, yeniden başlıyor!!!");
    delay(5000);//5sn bekle
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
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

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
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Yetki Hatası");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Baslatma Basarisiz");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Baglanti Basarisiz");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Veri Alinamadi");
    } else if (error == OTA_END_ERROR) {
      Serial.println("Sonlandirma Basarisiz");
    }
  });
  ArduinoOTA.begin();//OTA'yi başlatıyor
  Serial.println("Sistem Hazir");
  Serial.print("IP Adresiniz: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();//sonraki kod atma işlemleri için kullanmamız gerekiyor
}
