  #include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>
#include <string.h>

int bits[8]; // Declare bits array globally

// Constants
#define SOLARPIN A0
#define THRESHOLD 565
#define SD_ChipSelectPin 4
#define SPEAKER_PIN 9

// Global variables
TMRpcm tmrpcm;
bool isPlaying = false;
char receivedMessage[9]; // Array to store 8 bits + null terminator



// Function definitions
void setup() {
  pinMode(SOLARPIN, INPUT);
  //pinMode(SPEAKER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(SOLARPIN);

  if (reading > THRESHOLD) {
    for (int i = 0; i < 8; i++) {
      if (analogRead(SOLARPIN) > THRESHOLD) {
        bits[i] = 1;
      } else {
        bits[i] = 0;
      }
      delay(10);
    }

    // Convert bits to ASCII and store in receivedMessage
    for (int j = 0; j < 8; j++) {
      bits[0] = 0 ;
      receivedMessage[j] = bits[j] ;
    }

    int m = 0;
    for (int j = 1; j < 8; j++) {
      if (bits[j] == 1) {
        m += (1 << (7 - j));
      }
    }
    char n = m;
    String message = "";
    message += n;
    
    // Check for voice commands only if an hour has passed since the last one
      if (message == "!") {
        AudioPlay(); // Call the AudioPlay function to play audio
        isPlaying = true;
        Serial.println("Voice on received, playing audio.");
        Serial.end();

      } 
      else if (message == "@") {
        tmrpcm.stopPlayback();
        isPlaying = false;
        Serial.println("Voice off received, stopping audio.");
      }
      else {
      // Print remaining messages to serial and LCD (except voice commands within the last hour)
      Serial.begin(9600);
      //Serial.print(receivedMessage);
      Serial.print(message);
      //Serial.print(m)
    }
  }
}

void AudioPlay() {
  // Implement your logic for playing audio here
  // This could involve initializing the SD card, setting speaker pin, volume, and playing a specific audio file
  tmrpcm.speakerPin = SPEAKER_PIN;
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
  tmrpcm.setVolume(5);
  tmrpcm.play("alikhlas.wav"); // Replace "alikhlas.wav" with the actual filename of your audio file
}
