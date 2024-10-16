# WhatsApp Messaging with NodeMCU ESP8266

This project allows you to send WhatsApp messages using a NodeMCU ESP8266 board and the Ultramsg API. The NodeMCU hosts a web server where users can input a phone number and message, and the ESP8266 will send the WhatsApp message using the Ultramsg service.

## Features
- Hosts a web server on the NodeMCU for user input.
- Sends WhatsApp messages using the Ultramsg API.
- Simple HTML form for entering phone number and message.
- Displays success or error messages based on the sending status.

## Requirements
- NodeMCU ESP8266 board
- Arduino IDE with the ESP8266 package installed
- Ultramsg API account (Instance ID and API token)
- Wi-Fi network for the NodeMCU to connect to

## Getting Started

### Prerequisites
1. **Install Arduino IDE**: Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
2. **Install the ESP8266 Board Package**:
   - In the Arduino IDE, go to `File > Preferences`, and add the following URL to the **Additional Board Manager URLs**:
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
   - Go to `Tools > Board > Board Manager`, search for `ESP8266`, and install the package.

3. **Required Libraries**:
   - The `ESP8266WiFi` and `WiFiClientSecure` libraries should already be installed with the ESP8266 package.

### Hardware Setup
- Connect the NodeMCU to your computer via a USB cable.

### Code Setup
1. **Clone this repository**:
   ```bash
   git clone https://github.com/ayu2606/esp-whatsap.git
   ```
1. **Open the code in Arduino IDE**:
   - Launch the Arduino IDE.
   - Go to `File > Open` and navigate to the folder where you cloned this repository.
   - Select the main `.ino` file (e.g., `main.ino`) and click **Open**.

2. **Update the following variables in the code**:
   - Replace `"Your_SSID"` and `"Your_PASSWORD"` with your Wi-Fi network credentials.
   - Update `"Your_Ultramsg_Token"` and `"Your_Instance_ID"` with the Ultramsg API credentials.

3. **Upload the code to the NodeMCU**:
   - Select `NodeMCU 1.0 (ESP-12E Module)` under `Tools > Board`.
   - Select the correct port under `Tools > Port`.
   - Click the **Upload** button.

### Running the Project
1. **Open the Serial Monitor** to view the IP address assigned to the NodeMCU after connecting to the Wi-Fi.
2. **Visit the IP address** shown in the Serial Monitor using a web browser on the same network.
3. **Fill in the form** with the phone number (in international format) and the message, then click **Send Message**.

## Troubleshooting
- **Connection Issues**:
  - Ensure that the NodeMCU is connected to the correct Wi-Fi network.
  - Verify the Ultramsg API credentials (Instance ID and Token).
- **Failed to Connect to Ultramsg**:
  - Try a different Wi-Fi network or check if the router's firewall settings allow outgoing traffic on port 443.
  - Increase the connection timeout and retry logic in the code.

## Code Explanation

### Main Components
- **Wi-Fi Connection**: The NodeMCU connects to the specified Wi-Fi network using `ESP8266WiFi`.
- **Web Server**: The ESP8266 hosts a basic HTTP web server to display a form for user input.
- **HTTP POST Request**: The ESP8266 sends an HTTP POST request to the Ultramsg API to deliver the WhatsApp message.

### Code Breakdown
1. **Wi-Fi Setup**: Connects the NodeMCU to the Wi-Fi network.
2. **Web Server Setup**: Sets up a web server on port 80 for handling incoming HTTP requests.
3. **Form Handling**: The web form accepts phone numbers and messages, then sends a POST request to the NodeMCU.
4. **Sending the WhatsApp Message**: Uses the Ultramsg API to send the message securely.

## Example Response
When the message is sent successfully, the server returns:
```json
{
  "sent": true,
  "message_id": "xxxxxxxxx"
}
```

## Dependencies
- **ESP8266WiFi**: For connecting to Wi-Fi networks.
- **WiFiClientSecure**: For making secure HTTPS connections.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing
Feel free to submit issues, fork the repository, and send pull requests. All contributions are welcome!

## Contact
For any questions or issues, please open an issue in the repository or contact me at [your email].

## Acknowledgments
- Thanks to [Ultramsg](https://www.ultramsg.com) for providing the API service for sending WhatsApp messages.
