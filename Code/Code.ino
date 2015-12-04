// when called, GPRS picks up right after the first ring is reported
// serial mirroring is preserved for debug
// that was certainly faster than last time ;)

// works on battery power
// remember to turn on battery, then turn on GPRS, wait for connection, and turn on amp correctly
 
#include <SoftwareSerial.h>
 
SoftwareSerial GPRS(7, 8);
unsigned char buffer[256];          // buffer array for data recieve over serial port
int count=0; // counter for buffer array 
String bufferString;


void setup()
{
  GPRS.begin(19200);               // GPRS baud rate (software)  
  Serial.begin(19200);             // Arduino baud rate (hardware)
}
 
void loop()
{
  
/* Data traveling from GPRS to Arduino ************/
  if (GPRS.available())              
  {
    while(GPRS.available())          // reading data into char array 
    {
      buffer[count++]=GPRS.read();   // writing data into array
      if(count == 256)break;
  }
    Serial.write(buffer,count);      // if no data transmission ends, write buffer to hardware serial port
    for(int i = 0; i < count; i++){
        bufferString += char(buffer[i]);
    }
    Serial.println(bufferString.substring(2,6));
    if(bufferString.substring(2,6) == "RING"){
      GPRS.println("ATA");
    }
    clearBufferArray();              // call clearBufferArray function to clear the storaged data from the array
    bufferString = 0;
    count = 0;                       // set counter of while loop to zero
  }

/* Data traveling from Arduino to GPRS ***************/
  if (Serial.available())            
    GPRS.write(Serial.read());       // write it to the GPRS shield
}
void clearBufferArray()              // function to clear buffer array
{
  for (int i=0; i<count;i++)
    { buffer[i]=NULL;}               // clear all index of array with command NULL
}
