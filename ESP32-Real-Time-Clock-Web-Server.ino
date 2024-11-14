#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WebServer.h>  // Use the correct WebServer library for ESP32

// Replace with your network credentials
const char* ssid = "[H*m£]";   // Replace with your Wi-Fi SSID
const char* password = "0900786010"; // Replace with your Wi-Fi password

// Define the NTP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 3600000); // Timezone offset (0 for UTC)

// Set up the web server
WebServer server(80);  // Use WebServer for ESP32

// Handle the root URL to show the current time
void handleRoot() {
  timeClient.update();
  String time = timeClient.getFormattedTime();
  String html = "<html><body>";
  html += "<h1>ESP32 Real-Time Clock</h1>";
  html += "<p>Current Time: " + time + "</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);  // Send the response
}

void setup() {
  // Initialize serial and WiFi
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Wait for the connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the NTP client
  timeClient.begin();

  // Define HTTP routes
  server.on("/", HTTP_GET, handleRoot);  // Handle GET requests at root URL

  // Start the server
  server.begin();
}

void loop() {
  // Handle client requests
  server.handleClient();
}
