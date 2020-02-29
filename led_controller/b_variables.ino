// Number of the pixels on the strip
#define DIODECOUNT 5

//Callback interface
void LEDComplete();

// Setup led config. Control pin is set to 6 for default
NeoAnimations LED(DIODECOUNT, 6, NEO_GRB + NEO_KHZ800, &LEDComplete);

// Bluetooth serial
SoftwareSerial bt(10, 11); // RX, TX

// List of command (command + '\0')
char CONNECTED[4] = "CNT";
char DISCONNECTED[5] = "DCNT";
char GET_CONFIGURATION[3] = "GC";

char SET_COLOR[4] = "SC_";
char SET_BRIGHTNESS[4] = "SB_";
char SET_ILLUMINATION[4] = "SI_";

//Speed for a BT and Serial
const PROGMEM int serialSpeed = 9600;

// Variables for reading the data
const PROGMEM byte numChars = 20;
char command[numChars];
boolean newData = false;
static byte ndx = 0;

boolean startupShown = false;
byte startupStep = 0;

// LED status
long currentColor = 0; // Backup value. See 'parseColor'
byte currentIllumination = 0; // None
byte currentR = 255;
byte currentG = 255;
byte currentB = 255;
String hexColor = "#FFFFFF";
