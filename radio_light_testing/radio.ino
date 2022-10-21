#include "Radio.h"
RH_RF69 rf69(RFM69_CS, RFM69_INT);// create radio
void startRadio()
{
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);
  //Serial.println("Feather RFM69 RX/TX Test!");
  // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  if (!rf69.init()) {
    //Serial.println("RFM69 radio init failed");
    while (1);
  }
  //Serial.println("RFM69 radio init OK!");

  if (!rf69.setFrequency(RF69_FREQ)) {
    //Serial.println("setFrequency failed");
  }
  rf69.setTxPower(14, true);

  // The encryption key has to be the same as the one in the server
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
                  };
  rf69.setEncryptionKey(key);

  //Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");


}

void transmit(byte mode, byte modeStart, byte hue)
{
  byte radiopacket[4];
  radiopacket[0] = mode;
  radiopacket[1] = modeStart;
  radiopacket[2] = hue;
  radiopacket[3] = 0;
  rf69.send((uint8_t *)radiopacket, strlen(radiopacket));
  rf69.waitPacketSent();
  Serial.println("sending "); 
  Serial.print("mode = ");Serial.println(radiopacket[0]);
  Serial.print("modeStart = ");Serial.println(radiopacket[1]);
  Serial.print("hue = ");Serial.println(radiopacket[2]);
}
void receive(byte & m, byte & i, byte & h)
{

  uint8_t data[RH_RF69_MAX_MESSAGE_LEN];
  uint8_t datalen = sizeof(data);
  if (rf69.recv(data, &datalen))
  {
    //rf69.printBuffer("Received: ", hue, huelen);
    Serial.println("got ");
    Serial.print("mode = ");Serial.println(data[0]);
    Serial.print("modeStart = ");Serial.println(data[1]);
    Serial.print("hue = ");Serial.println(data[2]);
    m = data[0];//mode
    i = data[1];//interval
    h = data[2];//hue
  }

}
boolean timeout()
{
  return(rf69.waitAvailableTimeout(100));
}
void radioWake()
{
  rf69.available();
}

void radioSleep()
{
  rf69.sleep();
}
