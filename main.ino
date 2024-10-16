#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "{redacted}";
const char* password = "{redacted}";

// Ultramsg API details
const char* ultramsgEndpoint = "https://api.ultramsg.com/{redacted}/messages/chat";
const char* ultramsgToken = "{redacted}";
const char* ultramsgInstanceId = "{redacted}"; // Replace XXXXX with your instance ID

WiFiServer server(80); // HTTP server on port 80

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  // Connect to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
  Serial.println("Server started, waiting for clients...");
}

void loop() {
  WiFiClient client = server.available(); // Check if a client has connected

  if (client) {
    Serial.println("New client connected.");

    String request = client.readStringUntil('\r');
    Serial.println("Client request: " + request);
    client.flush();

    // Check if the request is a POST request
    if (request.indexOf("POST /send") >= 0) {
      String body = client.readString();
      String phoneNumber = getFieldValue(body, "phone");
      String messageText = getFieldValue(body, "message");

      if (phoneNumber.length() > 0 && messageText.length() > 0) {
        if (sendWhatsAppMessage(phoneNumber, messageText)) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html><body>Message sent successfully!</body></html>");
        } else {
          client.println("HTTP/1.1 500 Internal Server Error");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html><body>Failed to send message.</body></html>");
        }
      } else {
        client.println("HTTP/1.1 400 Bad Request");
        client.println("Content-Type: text/html");
        client.println();
        client.println("<html><body>Invalid input data.</body></html>");
      }
    } else {
      // Serve the input form
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println();
      client.println("<html><body>");
      client.println("<h2>Send WhatsApp Message</h2>");
      client.println("<form action=\"/send\" method=\"POST\">");
      client.println("Phone Number: <input type=\"text\" name=\"phone\" placeholder=\"+1234567890\"><br>");
      client.println("Message: <input type=\"text\" name=\"message\" placeholder=\"Your message here\"><br>");
      client.println("<input type=\"submit\" value=\"Send Message\">");
      client.println("</form>");
      client.println("</body></html>");
    }

    client.stop(); // Close the connection
    Serial.println("Client disconnected.");
  }
}

// Function to extract field value from POST data
String getFieldValue(String data, String fieldName) {
  int start = data.indexOf(fieldName + "=");
  if (start == -1) {
    return "";
  }
  start += fieldName.length() + 1;
  int end = data.indexOf("&", start);
  if (end == -1) {
    end = data.length();
  }
  return data.substring(start, end);
}

// Function to send WhatsApp message using Ultramsg API
bool sendWhatsAppMessage(String phoneNumber, String message) {
  WiFiClientSecure client;
  client.setInsecure(); // Use this for testing, but less secure

  if (!client.connect("api.ultramsg.com", 443)) {
    Serial.println("Connection to Ultramsg failed.");
    return false;
  }

  // Prepare the POST request
  String postData = "token=" + String(ultramsgToken) + "&to=" + phoneNumber + "&body=" + message;
  String url = "/instance" + String(ultramsgInstanceId) + "/messages/chat";

  // Send HTTP POST request
  client.println("POST " + url + " HTTP/1.1");
  client.println("Host: api.ultramsg.com");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.println("Content-Length: " + String(postData.length()));
  client.println();
  client.print(postData);

  // Read the response
  String response = client.readString();
  Serial.println("Response: " + response);

  return response.indexOf("\"sent\": true") >= 0;
}
