//SDplusAccel dengan button dan buzzer

//#include "U8glib.h"
//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send ACK

#include<Wire.h>
#include<SPI.h>
#include<SD.h>

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,nomor = 0;
int t0,t1,a,t2 = 0;
int SAMPLE = 10;
int stat = 0;
float arrX[10],arrY[10],arrZ[10];
int pb = 6, buzzer = 7;//pin pushbutton, pin buzzer, no pin led
int val = 0, lightON = 0, pushed = 0; //value pin pb, light status, push status
File Fileaksel;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  Serial.begin(500000);
  pinMode(pb, INPUT_PULLUP); //berbeda dengan INPUT biasa
  pinMode(buzzer, OUTPUT);
  
  t0 = millis();
  t2 = millis();
  
  //----------SD card-------------//
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  Fileaksel = SD.open("buzzer2.txt", FILE_WRITE);
  //------------------------------//
}

void loop(){
  val = digitalRead(pb);

 //--metode one push button--
  if(val == LOW && lightON == HIGH){
    pushed = 1-pushed;
    Serial.print("pushed=");
    Serial.print(pushed);
    Serial.print("\t");
    Serial.print(val);
    Serial.print("\t");
    Serial.println(lightON);
    if(pushed == 1){ //tanda nyala
      tone(buzzer, 1700,100); //1KHz sound signal
      delay(200);
      tone(buzzer, 2500,100); //1KHz sound signal
      Serial.println("start. File Open");
      Fileaksel = SD.open("buzzer1.txt", FILE_WRITE);
      Fileaksel.println("start. File Open");
    }
    else{ //tanda mati
      tone(buzzer, 2500,100); //1KHz sound signal
      delay(200);
      tone(buzzer, 1700,100); //1KHz sound signal
      Serial.println("done. File Closed");
      Fileaksel.println("done. File Closed");
      Fileaksel.close();
    }
  }
  lightON = val;

//--timing millis--//  
  t1 = millis();
  t0 = millis();
  float sumX = 0,sumY = 0,sumZ = 0;
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  
//Menghitung Varian dg jml range SAMPLE  
  for(int i = 0; i < SAMPLE; i++) {
    if(arrX[i] == 0){
      arrX[i]=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)  
        Serial.print(arrX[i]);
        Serial.print("\t");  
      arrY[i]=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
        Serial.print(arrY[i]);
        Serial.print("\t");
      arrZ[i]=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)     
        Serial.println(arrZ[i]);
      //Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
      while (t1-t0 < 100) { //delay selama n-milisecond, awal 50
        t1 = millis();
      }
    }
    sumX += arrX[i];
    sumY += arrY[i];
    sumZ += arrZ[i];
    //delay(50); // set this to whatever you want
  }
  
//--Menghitung rata-rata--//
  float meanSampleX = sumX/float(SAMPLE); //average X
  float meanSampleY = sumY/float(SAMPLE); //average Y
  float meanSampleZ = sumZ/float(SAMPLE); //average Z
  float sum2X = 0.0;
  float sum2Y = 0.0;
  float sum2Z = 0.0;

  for(int i = 0; i < SAMPLE; i++) {
    // pow(x, 2) is x squared.
    sum2X += pow((meanSampleX - float(arrX[i])), 2);
    sum2Y += pow((meanSampleY - float(arrY[i])), 2);
    sum2Z += pow((meanSampleZ - float(arrZ[i])), 2);
  }
  float varX = sum2X/float(SAMPLE-1);
  float varY = sum2Y/float(SAMPLE-1);
  float varZ = sum2Z/float(SAMPLE-1);

  float sumvar = 0.0;
  sumvar = varX + varY + varZ;

//Menghidupkan buzzer jika kondisi terpenuhi  
  //int stat = 0; //menyala ketika terpenuhi saja
  if(sumvar > 100000000){
    stat = 1;
    tone(buzzer, 2500, 30); //1KHz sound signal
  }
  else{
    stat = 0;
  }
  /*Serial.print("Varian: ");
  Serial.print(varX);
  Serial.print("\t"); 
  Serial.print(varY);
  Serial.print("\t");
  Serial.print(varZ); 
  Serial.print("\t");*/

  
//SD card//

  if(pushed == HIGH){ //ketika hidup dan file open
    //digitalWrite(led, HIGH);
    if (Fileaksel){
    //Serial.print("Writing to test.txt...");
      nomor++;
      Fileaksel.print(nomor);
      Fileaksel.print("\t");
      Fileaksel.print(arrX[0]);
      Fileaksel.print("\t"); 
      Fileaksel.print(arrY[0]);
      Fileaksel.print("\t"); 
      Fileaksel.print(arrZ[0]);
  
      Fileaksel.print("\t");
      Fileaksel.print(varX);
      Fileaksel.print("\t");
      Fileaksel.print(varY);
      Fileaksel.print("\t");
      Fileaksel.print(varZ);
  
      Fileaksel.print("\t");
      Fileaksel.print(sumvar);
      Fileaksel.print("\t");
      Fileaksel.println(stat);
        
      // close the file:
      //Serial.print(millis());
      /*Serial.print(nomor);
      Serial.print("\t"); 
      Serial.print(AcX);
      Serial.print("\t"); 
      Serial.print(AcY);
      Serial.print("\t"); 
      Serial.println(AcZ);*/
    }
 }
  else{ //ketika mati dan file closed
    // if the file didn't open, print an error:
    Serial.println("Not save in SD Card");
  }
  
  //Menggeser urutan
  for(int i = 0; i < SAMPLE; i++) {
    arrX[i] = arrX[i+1];
    arrY[i] = arrY[i+1];
    arrZ[i] = arrZ[i+1];
  }
  
  arrX[SAMPLE-1] = 0;
  arrY[SAMPLE-1] = 0;
  arrZ[SAMPLE-1] = 0;
 
}
