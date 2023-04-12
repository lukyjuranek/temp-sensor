/*
Authors: Lukas Juranek, Laith Elbeshti
*/

#define LED_PIN 3

int D;
float temp_cel;
float temp_far;
float total_temp = 0;
int count = 0;
float Vin;
float Voff = 2.63;
float temp_ref = -10;

boolean print_average = true;

void setup() {
    // pinMode(A0, INPUT);
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // Reads analog value from the pin
    D = analogRead(A0);

    // Calculates temperature
    Vin = D * (5.0 / 1023.0);
    temp_cel = (Vin / 8) / 0.01 + temp_ref;


    if (print_average) {
        total_temp += temp_cel;
        count++;
        int measurements = 40;
        // Prints average temperature every 40 measurements
        if (count == measurements) {
            float avg_temp = total_temp / measurements;
            temp_far = avg_temp * 9 / 5 + 32;
            Serial.println("Average temperature: " + String(avg_temp) + " C (" + String(temp_far) + " F)");
            count = 0;
            total_temp = 0;
            // Converts temperature to a value from 0 to 255
            int brightness = map(avg_temp, 0, 100, 0, 255);
            analogWrite(LED_PIN, brightness);
        }
        delay(50);
    } else {
        // Prints volatge and temperature every second
        Serial.println("Voltage: " + String(Vin) + " Temp: " + String(temp_cel) + " C");
        // Converts temperature to a value from 0 to 255
        int brightness = map(temp_cel, 0, 100, 0, 255);
        analogWrite(LED_PIN, brightness);
        delay(1000);
    }
}