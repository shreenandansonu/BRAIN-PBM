const int redLightPin = 7;
const int blueLightPin = 10;
const int speakerPin = 9;
const int Connection1 = 3;
int freqcy = 0;
int timeValue = 0;
int frequencyValue = 1;
int intensityValue = 255;

void setup()
{
    Serial.begin(9600);
    pinMode(redLightPin, OUTPUT);
    pinMode(blueLightPin, OUTPUT);
    pinMode(speakerPin, OUTPUT);
    pinMode(Connection1, OUTPUT);
    // Connecting Sound
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(redLightPin, HIGH);
        tone(speakerPin, 700, 200);
        delay(200);
        digitalWrite(redLightPin, LOW);
        noTone(speakerPin);
        delay(200);
    }
    // Power On LED
    digitalWrite(redLightPin, HIGH);
}

void loop()
{
    if (Serial.available() > 0)
    {
        char receivedChar = Serial.read();

        // Convert the received character to an integer
        int mode = receivedChar - '0';

        // Perform actions based on the received mode
        switch (mode)
        {
        case 0:
            playConnectTone();
            break;
        case 1:
            blinkLed(5, 10); // Blink for 5 seconds at 10 Hz
            blinkLed(5, 40); // Blink for 5 seconds at 40 Hz
            break;
        case 2:
            beep(2);
            break;
        case 3:
            freqcy = 10;
            break;
        case 4:
            freqcy = 40;
            break;
        case 5:
            freqcy = 100;
            break;
        case 6:
            blinkLed(300, freqcy);
            break;
        case 7:
            blinkLed(600, freqcy);
            break;
        case 8:
            blinkLed(1200, freqcy);
            break;
        case 9:
            blinkLed(1800, freqcy);
            break;
        case 10:
            if (Serial.available() > 0)
            {                                                       // Check if data is available to read
                String receivedData = Serial.readStringUntil('\n'); // Read the received data until newline character

                // Tokenize the received data based on commas
                char *token = strtok(const_cast<char *>(receivedData.c_str()), ",");
                timeValue = atoi(token); // Convert token to integer
                token = strtok(NULL, ",");
                frequencyValue = atoi(token); // Convert token to integer
                token = strtok(NULL, ",");
                intensityValue = atoi(token); // Convert token to integer

                // Flicker the Connection1 at the specified frequency, intensity, and duration
                flickerConnection1(frequencyValue, intensityValue, timeValue);
            }
        }
    }
}

void flickerConnection1(int frequency, int intensity, int duration)
{
    unsigned long previousMillis = 0;
    unsigned long interval = 1000 / frequency; // Calculate the interval based on frequency

    unsigned long startTime = millis(); // Get the current time
    while ((millis() - startTime) < (duration * 60000))
    {                                           // Convert duration to milliseconds
        unsigned long currentMillis = millis(); // Get the current time

        // Toggle the Connection1 based on the interval
        if (currentMillis - previousMillis >= interval)
        {
            previousMillis = currentMillis;  // Save the current time
            digitalWrite(Connection1, HIGH); // Turn on Connection1
            delayMicroseconds(intensity);    // Wait for intensity microseconds
            digitalWrite(Connection1, LOW);  // Turn off Connection1
            delayMicroseconds(intensity);    // Wait for intensity microseconds
        }
    }
}

// blink led function
void blinkLed(int durationSeconds, int frequencyHz)
{
    digitalWrite(blueLightPin, HIGH);
    int totalMillis = durationSeconds * 1000;
    int interval = 1000 / (2 * frequencyHz); // Calculate the interval for the given frequency

    for (int elapsedMillis = 0; elapsedMillis < totalMillis; elapsedMillis += interval * 2)
    {
        digitalWrite(Connection1, HIGH);
        delay(interval);
        digitalWrite(Connection1, LOW);
        delay(interval);
    }
    beep(5);
    digitalWrite(blueLightPin, LOW);
}
// blink led function  ends

void beep(int times)
{
    for (int i = 0; i < times; i++)
    {
        tone(speakerPin, 700, 200); // Beep for 200 milliseconds
        delay(300);                 // Pause between beeps
        noTone(speakerPin);
        delay(300);
    }
}

void playConnectTone()
{
    // Distinctive tone for connection
    for (int i = 0; i < 1; i++)
    {
        digitalWrite(redLightPin, LOW);
        digitalWrite(blueLightPin, HIGH);
        tone(speakerPin, 700, 200);
        delay(300);
        digitalWrite(redLightPin, HIGH);
        digitalWrite(blueLightPin, LOW);
        tone(speakerPin, 1400, 200);
        delay(300);
        digitalWrite(redLightPin, LOW);
        digitalWrite(blueLightPin, HIGH);
        tone(speakerPin, 2100, 200);
        delay(300);
        digitalWrite(redLightPin, HIGH);
        digitalWrite(blueLightPin, LOW);
        tone(speakerPin, 2800, 200);
        delay(300);
    }
    noTone(speakerPin); // Turn off the tone
}
