# IOT-WORK

* Eğer SerialMonitor üzerinde ???.? gibi anlamsız karakterler görüyorsan --> Serial.begin(115200) değerin ile Serial Monitor üzerindeki bound hızlarının aynı olmasına dikkat et.

* Kartına yeni bir program yüklemeden önce Araçlar-Kart'ın yüklemek istediğin kart olup olmadığına dikkat et.

* Portlarda sorun yaşamamak için kartı bilgisayardan çıkarmadan önce SerialMonitorü kapat yoksa tekrar kullanmak istediğinde "Port açık" yada "Port bulanamıyor" gibi hatalar ile karşılaşırsan --> Kullandığın portu değiştir ve Araçlar-Port kısmından yeniden seç.

*receiver1try ve sender1try ESP8266 lolin modüllerinin birbirleri ile haberleşmesi örneği sender olan esp içine haberleşme için receiver olarak kullanılan esp'nin mac adresi sender içinde tanımlanır. Bu örnekte com üzerinden veri okunmakta, kodu yüklediğin porta receiver1try.ino yüklü olan espyi taktığında senderdan gönderilen sonuçları alabiliyorsun. Ancak mevcut tanımlı olan porta senderın yüklü olduğu espyi takarsan serialMonitor üzerinde yalnızca "Delivery succes" çıktısı olmakta. Cihazları çalıştırmadan önce mac adreslerini öğren ve not al . Kodda kular olarak 0xFF gibi bir tanımlama var FF olan kısmı kendi mac adreini uyarla.

