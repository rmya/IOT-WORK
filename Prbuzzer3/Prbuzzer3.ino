//Sürekli ses çıkarıyor hassasiyet ayarı yapılması lazım

int sensor = D1;
int led = D2;
int buzzer = D5;
int sensordurum=LOW;
int deger=0;

void setup() {
// put your setup code here, to run once:
pinMode(sensor,INPUT);
pinMode(led,OUTPUT);
pinMode(buzzer,OUTPUT);
Serial.begin(9600);
}

void loop() {
// put your main code here, to run repeatedly:
sensordurum=digitalRead(sensor);

if(sensordurum==HIGH){
Serial.println("hareket var");

digitalWrite(led,HIGH);
tone(buzzer,340);
delay(3000);
noTone(buzzer);
}
else
{
Serial.println("hareket yok");

digitalWrite(led,LOW);
noTone(buzzer);
delay(300);
}

}
