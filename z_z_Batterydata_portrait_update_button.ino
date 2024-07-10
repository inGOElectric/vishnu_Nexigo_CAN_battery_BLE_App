#include <SPI.h>
#include <mcp2515.h>
#include "BluetoothSerial.h"
#include <Wire.h>

BluetoothSerial ESP_BT; //Class name

struct can_frame canMsg;
MCP2515 mcp2515(5);
//
int frame_01 = 0x9F10FA01;
int frame_11 = 0x9F11FA01;
int frame_51 = 0x9F15FA01;

void setup() {
  Serial.begin(19200);
  ESP_BT.begin("ESP32_Control");
  SPI.begin();
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) 
  {       
        if(canMsg.can_id == frame_01)
        {
          Serial.print("SoC : ");Serial.println(canMsg.data[0], DEC);
          int SoC = ESP_BT.write(canMsg.data[0]);
          //Current
          long MSBC = canMsg.data[3]<<8;
          long MSBFC = MSBC | canMsg.data[2];
          float MSBFFC = MSBFC*0.01;
          Serial.print("Current : "); Serial.println(MSBFFC);
          int A = ESP_BT.write(MSBFFC);
          //Voltage
          long MSBV = canMsg.data[5]<<8;
          long MSBFV = MSBV | canMsg.data[4];
          float MSBFFV = MSBFV*0.01;
          Serial.print("Voltage : "); Serial.println(MSBFFV);
          int V = ESP_BT.write(MSBFFV);
          }
        if(canMsg.can_id == frame_11)
        {
          long MSBWh = canMsg.data[5]<<8;
          long MSBFWh = MSBWh | canMsg.data[4];
          int MSBFFWh = MSBFWh;
          Serial.print("Wh : "); Serial.println(MSBFFWh);
          int KWh = ESP_BT.write(MSBFFWh);
          }
        if(canMsg.can_id == frame_51)
        {
          Serial.print("T1 : ");Serial.println(canMsg.data[2]-80, DEC);
          int t1 = ESP_BT.write(canMsg.data[2]-80);
          Serial.print("T2 : ");Serial.println(canMsg.data[3]-80, DEC);
          int t2 = ESP_BT.write(canMsg.data[3]-80);
          Serial.print("T3 : ");Serial.println(canMsg.data[4]-80, DEC);
          int t3 = ESP_BT.write(canMsg.data[4]-80);
          Serial.print("T4 : ");Serial.println(canMsg.data[5]-80, DEC);
          int t4 = ESP_BT.write(canMsg.data[5]-80);
          Serial.println("");
          }
    }
}
