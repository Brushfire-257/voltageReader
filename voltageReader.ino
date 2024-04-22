// Pin connections
int segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9}; // Segment pins (a-g, dp)
int digitPins[] = {10, 11, 12, 13}; // Common cathode pins (digits 1-4)

// The segments for each digit (0-9)
int segmentCodes[10] = {
  0b1111110, // 0
  0b0110000, // 1
  0b1101101, // 2
  0b1111001, // 3
  0b0110011, // 4
  0b1011011, // 5
  0b1011111, // 6
  0b1110000, // 7
  0b1111111, // 8
  0b1111011  // 9
};

void setup() {
  // Set up the segment and digit pins as outputs
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
  Serial.begin(9600); // Start the serial communication with the computer
  pinMode(A0, INPUT); // Set the A0 pin as input
}

void loop() {
  int sensorValue = analogRead(A0); // Read the input on analog pin 0
  float voltage = sensorValue * (5.0 / 1023.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
  
  // Convert the voltage to a 4-digit number
  int displayValue = round(voltage * 1000);
  
  // Display the value on the 7-segment display
  displayNumber(displayValue);

  Serial.print(voltage);
  Serial.print(",");
  Serial.println(displayValue);

  delay(1000);
}

void displayNumber(int number) {
  for (int digit = 0; digit < 4; digit++) {
    // Get the value of the current digit
    int digitValue = number % 10;
    number /= 10;

    // Turn on the current digit
    digitalWrite(digitPins[digit], LOW);

    // Set the segments for this digit
    for (int segment = 0; segment < 8; segment++) {
      digitalWrite(segmentPins[segment], segmentCodes[digitValue] & (1 << segment));
    }

    // Wait a bit
    delay(100);

    // Turn off the current digit before moving to the next one
    digitalWrite(digitPins[digit], HIGH);
  }
}