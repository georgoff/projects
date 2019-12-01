#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=104,370
AudioMixer4              mixer1;         //xy=305,373
AudioAnalyzeFFT1024      fft1024_1;      //xy=564,377
AudioConnection          patchCord1(i2s1, 0, mixer1, 0);
AudioConnection          patchCord2(i2s1, 1, mixer1, 1);
AudioConnection          patchCord3(mixer1, fft1024_1);
// GUItool: end automatically generated code


void setup() {
  AudioMemory(12);

  audioShield

}

void loop() {
  // put your main code here, to run repeatedly:

}
