

#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

#define IRQ   (2)
#define RESET (3)  // Not connected by default on the NFC Shield

Adafruit_NFCShield_I2C nfc(IRQ, RESET);

String tagId; //RFID ID Number
String headdressIDs[] = {
  "12323015213", "2719110213", "15513017213", "272214213"}; //Array to hold all scanned RFID ID Numbers

void setup(void) {
  Serial.begin(115200);
  Serial.println("Hello!");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); 
  Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); 
  Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); 
  Serial.println((versiondata>>8) & 0xFF, DEC);

  // configure board to read RFID tags
  nfc.SAMConfig();

  Serial.println("Waiting for an ISO14443A Card ...");
}


void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 
    0, 0, 0, 0, 0, 0, 0       };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Display some basic information about the card
    //    Serial.println("Found an ISO14443A card");
    //    Serial.print("  UID Length: ");
    //    Serial.print(uidLength, DEC);
    //    Serial.println(" bytes");
    //    Serial.print("  UID Value: ");
    //nfc.PrintHex(uid, uidLength);

    // PRINT OUT ID #'s in SERIAL // 

    for (uint8_t i=0; i < uidLength; i++) 
    {
      //      Serial.print(" 0x");
      //      Serial.print(uid[i], HEX); 
      tagId = tagId += String(uid[i]);
    }

    Serial.print("tagId: ");
    Serial.println(tagId);
    tagId = "";  // Clear Tag ID after Displaying in Serial

  }

  delay (1000);
}
