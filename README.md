# IOT-WORK

* Eğer SerialMonitor üzerinde ???.? gibi anlamsız karakterler görüyorsan --> Serial.begin(115200) değerin ile Serial Monitor üzerindeki bound hızlarının aynı olmasına dikkat et.

* Kartına yeni bir program yüklemeden önce Araçlar-Kart'ın yüklemek istediğin kart olup olmadığına dikkat et.

* Portlarda sorun yaşamamak için kartı bilgisayardan çıkarmadan önce SerialMonitorü kapat yoksa tekrar kullanmak istediğinde "Port açık" yada "Port bulanamıyor" gibi hatalar ile karşılaşırsan --> Kullandığın portu değiştir ve Araçlar-Port kısmından yeniden seç.

* receiver1try ve sender1try ESP8266 lolin modüllerinin birbirleri ile haberleşmesi örneği sender olan esp içine haberleşme için receiver olarak kullanılan esp'nin mac adresi sender içinde tanımlanır. Bu örnekte com üzerinden veri okunmakta, kodu yüklediğin porta receiver1try.ino yüklü olan espyi taktığında senderdan gönderilen sonuçları alabiliyorsun. Ancak mevcut tanımlı olan porta senderın yüklü olduğu espyi takarsan serialMonitor üzerinde yalnızca "Delivery succes" çıktısı olmakta. Cihazları çalıştırmadan önce mac adreslerini öğren ve not al . Kodda kular olarak 0xFF gibi bir tanımlama var FF olan kısmı kendi mac adreini uyarla.

* Arduino ve ESP haberleşmesinde https://www.hackster.io/RoboticaDIY/send-data-from-arduino-to-nodemcu-and-nodemcu-to-arduino-17d47a# buradan yararlandım. Arduinoyu tak Araçlar kısmından karı ve portu seç ve yükle. ESP yi başka bir porta tak Araçlar-Kart kısmından değiştir ve yükle daha sonra espnin portunda gelen veriler okunuyor.

* OTA https://www.youtube.com/watch?v=wOLEQ50x_BU&feature=youtu.be bu kanaldan yararlandım. Önce BasicOto üzerinde kendi ağına göre /ağ adı, şifre/ değişiklik yap. Sisteminde python yüklü olduğundan emin ol. python 3.8 de sorunlu çalışıyorui, ben 3.7 üzerinde denedim sorun çıkmadı. BasicOto kodunu doğru  port ve kartı seçtikten sonra yükle. Daha sonra bağlı olan esp yi çıkartıp harici bir güce bağlamak daha kullanışlı. Daha sonra ledblinklerden istediğini aç, onda da ağ bilgileri değişikliği yap.Daha sonra Port/Ağ portları kısmından espIP si tanımlı olanı seç ve yükle.İlk yüklemede python için izin isteyecek o yüzden ilk hatalı olabilir. izin verdikten sonra  kapatıp yeniden yükle.
--> https://www.hakankaya.kim/blog/esp8266-01-ota-update/
--> https://lastminuteengineers.com/esp32-ota-web-updater-arduino-ide/

* PIR Hareket algılama sensörünün üzerindeki yıldız tornavida girişli olan turuncu kareler(trimport) ile hassasiyet ve mesafe ayarı yapılabilir.
--> https://hayaletveyap.com/arduino-pir-hareket-sensoru-hcsr501-kullanimi/


