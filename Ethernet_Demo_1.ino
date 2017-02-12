/* Demo sketch for a simple web page that can monitor (in this case) water
 * temperature and water levels but could be used for any monitoring purpose.
 *
 * Space is at a premium on an Arduino UNO or Nano so we've stored the actual
 * web page HTML in program memory - otherwise the run-time SRAM would be
 * immediately filled with the large strings of HTML data.
 *
 * This is using the UIPEthernet library which is drop-in replacement for
 * the standard Ethernet library (which comes with the Arduino IDE).
 *
 * This means that not only can you use the W5100 (which the original Ethernet
 * library supports) you can also use the cheap ENC29J60 module as a retrofit.
 * Just be aware that the UIPEthenet library is quite large so space may be tight.
 * If all else fails use an Arduino MEGA!
 *
 * Attribution:
 * This demo sketch is an adapted version of the example sketch in the library.
 * Plus some stuff from the Internet I should think. Plus my own work.
 */
#include "Arduino.h"
#include <UIPEthernet.h>
#include "HTML.h"

// Some global variables to capture the highest and lowest temperature recorded
int minTemp = 1000;
int maxTemp = 0;

// Let's create our Web Server on port 1000 (use port 80 for standard browsing)
// This means your browser request MUST append :1000 the URL. Use port 80 if you
// don't want to do this.
EthernetServer server = EthernetServer(1000);

// ------------------------------------------------------------------------------
// SETUP     SETUP     SETUP     SETUP     SETUP     SETUP     SETUP     SETUP
// ------------------------------------------------------------------------------
void setup() {
	// Serial Monitor aka Debugging Window
	Serial.begin(9600);

	// You must assign a UNIQUE MAC address to the Ethernet module. Well, unique
	// in your home or work setup anyway. Set it and don't keep changing is as
	// your router is tracking it.
	uint8_t mac[6] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05 };

	// Give your web server a STATIC address here so the browser can find it.
	// From a Windows command prompt, try and "ping" it to see whether you can
	// see it on the network.
	/*
	 *  Microsoft Windows [Version 10.0.14393]
		(c) 2016 Microsoft Corporation. All rights reserved.

		C:\Users\Ralph>ping 192.168.1.123   <--- you type this in!

		Pinging 192.168.1.123 with 32 bytes of data:
		Reply from 192.168.1.123: bytes=32 time=1ms TTL=64
		Reply from 192.168.1.123: bytes=32 time=1ms TTL=64
		Reply from 192.168.1.123: bytes=32 time=1ms TTL=64
		Reply from 192.168.1.123: bytes=32 time=1ms TTL=64

		Ping statistics for 192.168.1.123:
			Packets: Sent = 4, Received = 4, Lost = 0 (0% loss),
		Approximate round trip times in milli-seconds:
        Minimum = 1ms, Maximum = 1ms, Average = 1ms
	 */
	IPAddress myIP(192, 168, 1, 123);

	// All information set up, we can begin
	Ethernet.begin(mac, myIP);
	server.begin();

	// Just to prove that your server is running on your specified IP address
	Serial.print("IP Address: ");
	Serial.println(Ethernet.localIP());

	// Let's see how much free ram we have left before the loop starts
	Serial.print(F("Free SRAM: "));Serial.println(freeRam());
}

// ------------------------------------------------------------------------------
// LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP
// ------------------------------------------------------------------------------
void loop() {

	// Listen for incoming clients on above port
	if (EthernetClient client = server.available()) {
		Serial.println(F("Client connected."));

		// Let's see how much free ram we have left. This should not grow and grow!
		Serial.print(F("Free SRAM: "));Serial.println(freeRam());

		// Display all the info sent back to the Arduino from your browser
		String readData = "";

		// While there is data to read
		while (client.available()) {

			// Read it character by character
			char dataChar = client.read();

			// And concatenate into the string
			readData += dataChar;

			// IF we hit a New Line character we'll print and inspect that line
			if (dataChar == '\n') {

				// Debugging/monitoring - slows down the sending back of the page quite a bit
				Serial.print(readData);

				// We're looking for the GET request and any parameters
				if (readData.startsWith("GET")) {
					if (readData.indexOf("clear") > -1) {

						// Reset the min/max
						minTemp = 1000;
						maxTemp = 0;
					}
				}

				// Clear the concatenated string ready for next line (if any)
				readData = "";
			}
		}

		// Now send back the web page to your browser (desktop, phone etc)
		sendStaticPage(client);

		// Give it a chance to finish
		delay(50);

		// Terminate the client link, ready for another
		client.stop();
		Serial.println(F("Client disconnected."));
	}
}

// ------------------------------------------------------------------------------
// Send back the HTML page with correct headers
// ------------------------------------------------------------------------------
void sendStaticPage(EthernetClient client) {
	// Return the response
	char buffer[100];

	// Here is where you might call functions to retrieve measurement data such
	// as temperature, flow, presence (or absence), switch status etc
	// I'm just emulating that here by reading random analog values
	int airTemp = analogRead(A0);
	int waterTemp = analogRead(A1);

	// Update the min/max
	minTemp = min(minTemp, waterTemp);
	maxTemp = max(maxTemp, waterTemp);

	// We're reading the string information from PROGMEM
	for (unsigned int cnt = 0; cnt < 21; cnt++) {
		strcpy_P(buffer, (char*) pgm_read_word(&(htmlTable[cnt])));

		// Convert our measurements into displayable values
		//String target = String(airTemp, DEC);
		String temp = buffer;

		// As we render each 'line' of HTML see whether we should 'inject'
		// the data values - crude but effective in the Arduino world!
		// The "replace" looks at each line, and, if it can, replaces the
		// source string with the target string. If not, it leaves it unchanged.
		temp.replace(F("!AirTemp"), String(airTemp, DEC));
		temp.replace(F("!WaterTemp"), String(waterTemp, DEC));
		temp.replace(F("!MinTemp"), String(minTemp, DEC));
		temp.replace(F("!MaxTemp"), String(maxTemp, DEC));

		// Send the HTML line back to the client (your browser)
		client.println(temp);
	}
}
