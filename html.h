/*
 * This file contains the actual (messy) HTML that makes up a web page. It looks far worse there than it really is because
 * we're scrunching it all up into strings. When you get the page working, it will actually look like this:
 *
 *
<!DOCTYPE HTML>
<html>
	<head>
		<title>ENC28J60 Testing</title>
		<style>
			* {margin:0;padding:0;box-sizing:border-box;font-family:arial;}
			table td {font-size:1em;text-align:right;padding: 5px;}
		</style>
		<link rel='icon' href='data:,'>
	</head>
	<body>
		<div style='width:405px;height:100vh;background-color:yellow;'>
		<div style='width:100%;height:60px;background-color:red;text-align:center;'>
		<h1 style='color:yellow;padding-top:15px;'>Arduinite Ethernet Special</h3></div>
		<table style='border:1px solid blue;margin-left:auto;margin-right:auto;margin-top:30px;'>
			<tr>
				<td>Air temperature:<td>188
			<tr>
				<td>Water temperature:<td>172
			<tr>
				<td>Min Water:<td>34
			<tr>
				<td>Max Water:<td>441
			<tr>
				<td>Water level:<td>OK
			<tr>
				<td>Clear min/max levels<td><input type='button' onclick="location.href='/?clear'" value='Clear'>
			<tr>
				<td>Refresh levels<td><input type='button' onclick="location.href='/'" value='Refresh'>
		</table>
	</body>
</html>
 */

#ifndef HTML_H_
#define HTML_H_

// We must include this library to use PROGMEM feature
#include <avr/pgmspace.h>

const char line_0[] PROGMEM = "HTTP/1.1 200 OK";
const char line_1[] PROGMEM = "Content-Type: text/html";
const char line_2[] PROGMEM = ""; // <---- IMPORTANT! Don't forget this empty line
const char line_3[] PROGMEM = "<!DOCTYPE HTML>";
const char line_4[] PROGMEM = "<html><head><title>ENC28J60 Testing</title>";

// Here we are use Cascading Style Sheet (CSS) to pretty up our HTML
const char line_5[] PROGMEM = "<style> * {margin:0;padding:0;box-sizing:border-box;font-family:arial;}";
const char line_6[] PROGMEM = "table td {font-size:1em;text-align:right;padding: 5px;}</style>";

// Hmmm. To prevent some browsers (eg Chrome, grrr) requesting a fancy icon to put into the address bar in your
// browser, we define it here just to shut it up. Don't omit this or your browser will make TWO requests.
const char line_7[] PROGMEM = "<link rel='icon' href='data:,'></head>";

// Now we are ready to actually send back some information that you can see. the "body" tag starts the bit you see.
const char line_8[] PROGMEM = "<body>";

// A "div" is a rectangular container block to contain other things. Here we're using it to cover the entire page in yellow.
const char line_9[] PROGMEM = "<div style='width:405px;height:100vh;background-color:yellow;'>";

// This "div" is the banner at the top. Sitting within the container "div" it has a fixed height and red background.
const char line_10[] PROGMEM = "<div style='width:100%;height:60px;background-color:red;text-align:center;'>";

// Just like Word, we have different levels of headings. "h1" is the biggest/highest setting.
const char line_11[] PROGMEM = "<h1 style='color:yellow;padding-top:15px;'>Arduinite Ethernet Special</h1></div>";

// Now we are creating a Word-like table to contains rows and columns. Rows start with "tr", cells start with "td". You can have
// as many "td" cells per row as you need. Most programmers will include end tags "</tr>" and "<td>" but they are actually optional
// so we will omit them here to save on space.
const char line_12[] PROGMEM = "<table style='border:1px solid blue;margin-left:auto;margin-right:auto;margin-top:30px;'>";
const char line_13[] PROGMEM = "<tr><td>Air temperature:<td>!AirTemp";
const char line_14[] PROGMEM = "<tr><td>Water temperature:<td>!WaterTemp";
const char line_15[] PROGMEM = "<tr><td>Min Water:<td>!MinTemp";
const char line_16[] PROGMEM = "<tr><td>Max Water:<td>!MaxTemp";
const char line_17[] PROGMEM = "<tr><td>Water level:<td>OK";

// Now we're creating a couple of buttons that cause a request to be made, back to the original site with a parameter
const char line_18[] PROGMEM = "<tr><td>Clear min/max levels<td><input type='button' onclick=\"location.href='/?clear'\" value='Clear'>";
const char line_19[] PROGMEM = "<tr><td>Refresh levels<td><input type='button' onclick=\"location.href='/'\" value='Refresh'>";

// And now we must end the "table", container "div", "body" and "html". Browsers are forgiving if you miss these out (as you saw on the video!)
// but may cause layout issues in your web page too!
const char line_20[] PROGMEM = "</table>";
const char line_21[] PROGMEM = "</div>";
const char line_22[] PROGMEM = "</body></html>";

// We want a pointer to an array of "const" pointers to "const" data that is itself a "const" pointer. Don't ask.
const char * const htmlTable[] PROGMEM = { line_0, line_1, line_2, line_3, line_4, line_5, line_6, line_7, line_8, line_9, line_10,
		line_11, line_12, line_13, line_14, line_15, line_16, line_17, line_18, line_19, line_20, line_21, line_22
};


// ------------------------------------------------------------------
// This is the routine that will display how much free SRAM you have.
// Ideally place in SETUP before the loop, but no hard rules.
//
// A "size_t" type can store the maximum size of any type. Commonly used for
// array indexing and loop counting. We could use an unsigned int here too.
// ------------------------------------------------------------------
size_t freeRam() {
	return RAMEND - size_t(__malloc_heap_start);
}

// End of library header file
#endif /* HTML_H_ */
