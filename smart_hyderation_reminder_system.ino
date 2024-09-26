#define BLYNK_TEMPLATE_ID "TMPL3DrJhgLPz"
#define BLYNK_TEMPLATE_NAME "Smart Hydration Reminder System"

#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <RTClib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

RTC_DS3231 rtc;

char auth[] = "QhKsUdo_JhGT9QszcEo0gFX2ZlhSknBH"; // Replace with your Blynk Auth Token
char ssid[] = "Diksha sky"; // Replace with your Wi-Fi SSID
char pass[] = "diksha263284"; // Replace with your Wi-Fi password

const int buzzerPin = D3; // Buzzer pin
int totalGlasses = 0; // Counter for water glasses consumed
bool reminderSent = false; // Flag to check if reminder was sent
int reminderHour = 15; // Default reminder hour
int reminderMinute = 25; // Default reminder minute

// NTP Client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000); // UTC+5:30

// Function to log water consumption
BLYNK_WRITE(V0) {
    if (param.asInt() == 1) {
        totalGlasses++;
        Blynk.virtualWrite(V1, totalGlasses); // Send total glasses to Blynk app
        tone(buzzerPin, 1000, 200); // Buzzer alert
        Serial.print("Total glasses consumed: ");
        Serial.println(totalGlasses); // Debug output
    }
}

// Function to capture reminder time from Slider widget
BLYNK_WRITE(V3) {
    int timeInput = param.asInt(); // Time in minutes
    reminderHour = timeInput / 60; // Calculate hour from slider input
    reminderMinute = timeInput % 60; // Calculate minute from slider input

    String reminderTimeStr = String(reminderHour) + ":" + (reminderMinute < 10 ? "0" : "") + String(reminderMinute);
    Blynk.virtualWrite(V2, "Reminder set for: " + reminderTimeStr); // Update reminder label
    Serial.println("Reminder time set to: " + reminderTimeStr);
}

// Function to send a reminder notification
void sendReminder() {
    DateTime now = rtc.now(); // Get the current time
    String timeStr = String(now.hour()) + ":" + (now.minute() < 10 ? "0" : "") + String(now.minute()); // Format the time
    String reminderMessage = "Reminder at " + timeStr + ": Time to drink water!";
    Blynk.virtualWrite(V2, reminderMessage); // Update reminder message with the current time
    tone(buzzerPin, 1000, 1000); // Buzzer alert for 1 second
    delay(1000); // Wait for 1 second
    noTone(buzzerPin); // Turn off the buzzer
    Serial.println(reminderMessage); // Debug output
}

// Function to update RTC with the current time from NTP
void updateRTCTime() {
    timeClient.update(); // Update the time
    unsigned long epochTime = timeClient.getEpochTime(); // Get epoch time

    // Print the fetched epoch time for debugging
    Serial.print("Fetched Epoch Time: ");
    Serial.println(epochTime);

    DateTime now = DateTime(epochTime); // Convert to DateTime object
    rtc.adjust(now); // Set RTC to current time

    Serial.print("RTC updated to: ");
    Serial.print(now.year());
    Serial.print("-");
    Serial.print(now.month());
    Serial.print("-");
    Serial.print(now.day());
    Serial.print(" ");
    Serial.print(now.hour());
    Serial.print(":");
    Serial.print(now.minute());
    Serial.print(":");
    Serial.println(now.second());
}

// Function to check if it's time to send the reminder
void checkReminderTime() {
    DateTime now = rtc.now(); // Get current RTC time

    if (now.hour() == reminderHour && now.minute() == reminderMinute && !reminderSent) {
        sendReminder(); // Send reminder if the time matches
        reminderSent = true; // Set flag to prevent multiple reminders
    } else if (now.hour() != reminderHour || now.minute() != reminderMinute) {
        reminderSent = false; // Reset flag when the time changes
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(buzzerPin, OUTPUT);

    // Initialize Blynk
    Blynk.begin(auth, ssid, pass);

    // Initialize RTC
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }

    // Update RTC to current time
    updateRTCTime(); // Call this to set the RTC time
    delay(2000); // Delay for stability
}

void loop() {
    Blynk.run(); // Run Blynk
    checkReminderTime(); // Check for reminder
    delay(100); // Short delay to avoid excessive processing
}
