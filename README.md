# Web Enable your Arduino with an Ethernet ENC28J60 or W5100 Controller
See video #74 here: https://www.youtube.com/c/RalphBacon

It's easy to fit an Ethernet Controller module to your Arduino board that will let you serve a web-page to your browser or smartphone - as well as send you an email to alert you to potential issues.

Using the simple, four-wire SPI communications protocol it's easy to wire up an ENC28J60 to any Arduino UNO, Nano or Mega - and if you use the W5100 board there's no wiring to be done! What could be simpler than that?

It's one thing to wire up an Ethernet Controller, but how do you write the HTML to create a (simple) web page? I show you how, and how we save valuable run-time SRAM. It's not complicated and if you download the fully documented example sketch it will be very obvious how it hangs together.

In the next part we'll cover the (even simpler) process to send an email, and then we'll tie everything together into one project. This is going to monitor my attic water temperature and water level and will alert me if either is too low (no burst pipes for me!).

Github UIPEthernet library
https://github.com/UIPEthernet

In depth PROGMEM guide by Nick Gammon (from Arduino.cc forum)
http://www.gammon.com.au/progmem
