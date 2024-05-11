  
const int LASERPIN = 10;
 
String state;
void setup() {
  // Set the laser pin as an output
  pinMode(LASERPIN, OUTPUT);  
  Serial.begin(9600);
  

}

void loop() {
  // Check if there is data available on the serial port
  if (Serial.available() > 0) {
    // Read the incoming serial data until a newline character is encountered
      state=Serial.readStringUntil('\n');
    // Process each character in the received data
    for (int i = 0; i < state.length(); i++) {
      char c = state[i];
      int bits[8];
      
      // Convert the ASCII character to binary bits
      for (int z = 0; z < 8; z++) {
        bits[z] = c % 2;
        c /= 2;
      }
      
      // Reverse the binary bits
      for (int j = 0; j < 4; j++) {
        int temp = bits[j];
        bits[j] = bits[7 - j];
        bits[7 - j] = temp;
        bits[0]=1;
      }
      
      // Write the binary bits to the laser pin
      for (int p = 0; p < 8; p++) {
        digitalWrite(LASERPIN, bits[p]);
        delay(10);
        Serial.print(bits[p]);
        

      }
      
      // Turn off the laser after each transmission
      digitalWrite(LASERPIN, LOW);
      delay(10);
    }
  }
}

