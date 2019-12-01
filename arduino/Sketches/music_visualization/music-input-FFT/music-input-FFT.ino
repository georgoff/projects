#include <SPI.h>

#include <LedControl.h>
#include "arduinoFFT.h"

 
#define SAMPLES 64             //Must be a power of 2
#define SAMPLING_FREQUENCY 9900 //Hz, must be less than 10000 due to ADC
const int n_bins = 8;
const int bin_width = SAMPLES / 2 / n_bins;
double bin_sum = 0;
const int DATA_IN = 8;
const int CLOCK = 9;
const int CS = 10;

LedControl lc = LedControl(DATA_IN, CLOCK, CS, 1);
 
arduinoFFT FFT = arduinoFFT();
 
unsigned int sampling_period_us;
unsigned long microseconds;
 
double vReal[SAMPLES];
double vImag[SAMPLES];

double binnedSignal[n_bins];
 
void setup() {
    Serial.begin(115200);

    ADCSRA = 0b11100101;
    ADMUX = 0b00000000;
 
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));

    lc.shutdown(0, false);
    lc.setIntensity(0,8);
}

void loop() {
   
    /*SAMPLING*/
//    for(int i=0; i<SAMPLES; i++)
//    {
//        microseconds = micros();    //Overflows after around 70 minutes!
//     
//        vReal[i] = analogRead(0);
//        vImag[i] = 0;
//     
//        while(micros() < (microseconds + sampling_period_us)){
//        }
//    }

   // ++ Sampling
   for(int i=0; i<SAMPLES; i++)
    {
      while(!(ADCSRA & 0x10));        // wait for ADC to complete current conversion ie ADIF bit set
      ADCSRA = 0b11110101 ;               // clear ADIF bit so that ADC can do next operation (0xf5)
      int value = ADC - 512 ;                 // Read from ADC and subtract DC offset caused value
      vReal[i]= value;                      // Copy to bins after compressing
      vImag[i] = 0;                         
    }
    // -- Sampling
 
    /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
 
    /*PRINT RESULTS*/
    //Serial.println(peak);     //Print out what frequency is the most dominant.
 
//    for(int i=0; i<(SAMPLES/2); i++)
//    {
//        /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/
//         
////        Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
////        Serial.print(" ");
////        Serial.println(vReal[i], 1);    //View only this line in serial plotter to visualize the bins
//    }

    // take first 64 values of vReal
    // start with the first (64/8) = 8 values
    // average them
    // write that value to the corresponding binnedSignal[]

    for(int i = 0; i < n_bins; i++) {
      bin_sum = 0;
      
      for(int j = 0; j < bin_width; j++) {
        if(i == 0 && j < 2) {
          continue;
        }
        bin_sum += vReal[i*bin_width + j];
      }

      binnedSignal[i] = bin_sum / bin_width;

      Serial.println(binnedSignal[i]);
//      Serial.println(ceil(binnedSignal[i] / 100));
    }

//    Serial.print("Major Peak = ");
//    Serial.println(peak);
//    Serial.println("-------------");

    for(int i = 0; i < 8; i++) {
      lightColumn(i, ceil(binnedSignal[i] / 100));
    }

//    lc.setLed(0,3,5,true);
 
//    delay(500);  //Repeat the process every second OR:
//    while(1);       //Run code once
}

void lightColumn(int col, int height) {
  // turn off pixels above height
  for(int i = 0; i < 8 - height; i++) {
    lc.setLed(0, i, col, false);
  }

  // turn on pixels up to height
  for(int j = 8 - height; j < 8; j++) {
    lc.setLed(0, j, col, true);
  }
}

