#include<SoftwareSerial.h>

const byte co2_start_cmd[] = {0XFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
SoftwareSerial co2_serial(D7,D8);
byte co2_received_bytes[9];
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
co2_serial.begin(9600);
delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
int co2;
read_co2(&co2);
Serial.print("co2 :");
Serial.print(co2);
Serial.println(" ppm");
delay(1500);
}

void read_co2(int *CO2)
{
  if(co2_serial.write(co2_start_cmd,sizeof(co2_start_cmd))==9)
  {
        
    for(byte i =0;i<9;i++)
    {
      co2_received_bytes[i] = co2_serial.read();
    }
    
//    debug code  
//    for(int j = 0;j<9;j++)
//    {
//      Serial.println(co2_received_bytes[j]);
//    }
//    Serial.println();

//last byte of reading jumps to the fist byte index 
//so below code will auto detect the problem if occur and returns correct reading
   if((co2_received_bytes[0] == 255) && (co2_received_bytes[8] != 0))
   {
     *CO2 = (co2_received_bytes[2]*256) + co2_received_bytes[3];  
   }
   else if(co2_received_bytes[8] == 0) 
   {
     *CO2 = (co2_received_bytes[3]*256) + co2_received_bytes[4];
   }
  
  }
}
