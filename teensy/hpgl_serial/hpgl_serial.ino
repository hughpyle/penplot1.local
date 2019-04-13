// Serial interface for HPGL plotter


#define BAUDRATE 4800
#define PLOTTER Serial1
#define USB Serial
#define XON 0x11
#define XOFF 0x13

// If XOFF for 30 seconds, let's assume something broke
#define XOFFTIMEOUT 30000

elapsedMillis millisSinceInactive;




// XON-XOFF flow control
bool isActive = true;


void setup() {
  // Initialization
  PLOTTER.begin(BAUDRATE);
  USB.begin(BAUDRATE);
  millisSinceInactive = 0;
  delay(100);
}


void loop() {
  int data;
  
  if (PLOTTER.available() > 0) {
    // Plotter has something to say.
    // Look for XON and XOFF flow control instructions.
    data = PLOTTER.read();
    if (data == XON) {
      isActive = true;
    }
    else if (data == XOFF) {
      isActive = false;
      millisSinceInactive = 0;
    }
    else {
      USB.write(data);
    }
    delay(1);
  }

  // Set the LED depending on whether we're active
  digitalWrite(LED_BUILTIN, isActive ? HIGH : LOW);

  if (USB.available() > 0 && isActive) {
    // read the next thing and send it to the plotter
    data = USB.read();
    PLOTTER.write(data);
  } else {
    delay(5);
  }

  if (!isActive && millisSinceInactive > XOFFTIMEOUT) {
    // be active again
    isActive = true;
  }
  

}
