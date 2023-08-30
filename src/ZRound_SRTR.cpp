//==============================================================================
// Program:      ZRound_SRTR
// Author:       captainserial
// Target:       UNO R4 Minima 
// Date:         2023/08/29
// Time:         2:50pm
// Notes:        
//               Uses the hardware serial capabilities of the R4.
// Reference:    Heavily based on Sparkfun's Continuous Read Example from their
//               included library, and on RiCino Lap Counter.
//==============================================================================

//=====[ INCLUDE ]==============================================================
#include "ZRound_SRTR.h"
#include "SparkFun_UHF_RFID_Reader.h"

//=====[ CONSTANTS ]============================================================
  const int NANO_SERIAL_SPEED = 38400;      // nano serial communication speed
  const int PC_SERIAL_SPEED = 19200;        // PC serial communication speed (19200 per ZRound spec)
  const int NANO_READ_POWER = 27000;        // antenna power - DO NOT exceed 27000! DO NOT exceed 5000 with just USB power!
  const char ZROUND_STARTUP_ACK[] = "%A&";  // ZRound decoder startup acknowledgment string
  const long TIME_SYNC_INTERVAL = 5000;
  // The number of bytes needed to store the EPC from the tags.
  // Most tags are 96 or 128 bit, which is 12 or 16 bytes.
  // The Sparkfun stickers are 96-bit.
  const int EPC_BYTES = 12;
  const int MAX_TRANSPONDERS = 10; // maximum transponders allowed in a single race

// message text
  const char ERROR_NO_NANO[] = "Error: M6E Nano failed to respond.";
  const char ERROR_INVALID_ZROUND[] = "Error: Invalid ZRound command.";
  const char ERROR_NOT_ZROUND[] = "Error: Received a line that was not a ZRound command.";

//=====[ STRUCTS ]==============================================================
  typedef struct TagRecord {
    byte tagEPC[EPC_BYTES];
    unsigned long timeLastSeen;
  };

//=====[ VARIABLES ]============================================================
  bool MessageReceived = false;
  String IncomingMessage = "";
  bool ConnectedToPC = false;
  unsigned long TimeRaceStarted = 0;
  bool RaceIsRunning = false;
  unsigned long LastKeepAliveTime = 0;
  unsigned long LastTimeReported = 0;
  TagRecord TagsSeen[MAX_TRANSPONDERS]; // where we store transponders seen during race
  RFID nano; // Initialize RFID library object


//=====[ SETUP ]================================================================
void setup() {
  // start serial communications with PC
  Serial.begin(PC_SERIAL_SPEED);

  // wait for the PC serial port to initialize
  while (!Serial);

  // reserve 200 bytes for the incoming message string:
  IncomingMessage.reserve(200);

  // start nano communication
  while (setupNano(NANO_SERIAL_SPEED) == false) {
    // if it isn't working, say so over serial
    Serial.println(F(ERROR_NO_NANO));
  }

  // set North America frequency
  nano.setRegion(REGION_NORTHAMERICA);
  // set read power
  nano.setReadPower(NANO_READ_POWER);
}

//=====[ LOOP ]=================================================================
void loop() {

  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    IncomingMessage += inChar;
    // if the incoming character is an ampersand, set a flag so we can
    // do something about it:
    if (inChar == '&') {
      MessageReceived = true;
    }
  }

  // if we have PC serial data available
  if (MessageReceived) {
    // and if it has ZRound command at the end
    if (IncomingMessage.charAt(IncomingMessage.length() - 3) == '%' &&
        IncomingMessage.charAt(IncomingMessage.length() - 1) == '&') {
      // switch on ZRound command 2nd character
      switch (IncomingMessage.charAt(IncomingMessage.length() - 2)) {
        case 'C':
          startup();
          break;
        case 'I':
          startRace();
          break;
        case 'F':
          stopRace();
          break;
        default:
          Serial.println(F(ERROR_INVALID_ZROUND));
          break;
      }
    } else {
      Serial.println(F(ERROR_NOT_ZROUND));
    }
    MessageReceived = false;
    IncomingMessage = "";
  }  // end if message received

  // if the race is running
  if (RaceIsRunning) {
    // check for tag reads
    reportTags();
    // sync time to PC
    syncTime();
  }
}  // end main loop


//=====[ startup ]==============================================================
void startup() {
  Serial.print(F(ZROUND_STARTUP_ACK));
}

//=====[ startRace ]============================================================
void startRace() {
  // record time race started
  TimeRaceStarted = millis();
  // set race running flag
  RaceIsRunning = true;
  // start scanning for tags
  nano.startReading();
}

//=====[ stopRace ]=============================================================
void stopRace() {
  // blank time race started
  TimeRaceStarted = 0;
  // set race running flag
  RaceIsRunning = false;
  // clear the array of seen tags
  memset(TagsSeen, 0, sizeof(TagsSeen));
  // stop scanning for tags
  nano.stopReading();
}

//=====[ reportTags ]===========================================================
void reportTags() {
  if (nano.check() == true)  // Check to see if any new data has come in from module
  {
    byte responseType = nano.parseResponse();  // Break response into tag ID, RSSI, frequency, and timestamp

    if (responseType == RESPONSE_IS_KEEPALIVE) {
      LastKeepAliveTime = millis();
      
    } else if (responseType == RESPONSE_IS_TAGFOUND) {
      unsigned long timeStamp = nano.getTagTimestamp();  // Get the time this was read, (ms) since last keep-alive message
      byte tagEPCBytes = nano.getTagEPCBytes();  // Get the number of bytes of EPC from response
      unsigned long time = (LastKeepAliveTime + timeStamp) - TimeRaceStarted;

      // get tag EPC
      byte EPC[EPC_BYTES];
      for (byte x = 0; x < tagEPCBytes; x++) {
        EPC[x] = nano.msg[31 + x];
      }

      // if we have seen this tag less than (1 second?) ago, ignore it
      if (!hasBeenSeenRecently(EPC, time)) {
        Serial.print("%L");
        for(int i = 0; i < EPC_BYTES; i++) {
          if(EPC[i] < 0x10) Serial.print(0);
          Serial.print(EPC[i], HEX);
        }
        Serial.print(',');
        Serial.print(time, HEX);
        Serial.print("&");
      }

      // add this tag to the TagsSeen list
      // if it is already there just update the time
      addTagToList(EPC, time);

    } else if (responseType == ERROR_CORRUPT_RESPONSE) {
      Serial.println("Error: Bad CRC");
    } else {
      // Unknown response
      Serial.println("Error: Unknown RFID response");
    }
  }
}

//=====[ addTagToList ]=========================================================
void addTagToList(byte EPC_Seen[], unsigned long timeSeen) {
  bool added = false;
  TagRecord newRecord;

  // check if the tag has been seen before
  for (int i = 0; i < MAX_TRANSPONDERS; i++) {
    // if it has, add it to the array at the same position
    if (memcmp(EPC_Seen, TagsSeen[i].tagEPC, EPC_BYTES) == 0) {
      memcpy(newRecord.tagEPC, EPC_Seen, EPC_BYTES);
      newRecord.timeLastSeen = timeSeen;
      TagsSeen[i] = newRecord;
      added = true;
    }
  }

  // if it hasn't been seen before
  if(!added) {
    // step through the array and look for an open slot
    for (int i = 0; i < MAX_TRANSPONDERS && added == false; i++) {
      // open slot should have a 0 in the timelastseen
      if (TagsSeen[i].timeLastSeen == 0) {
        memcpy(newRecord.tagEPC, EPC_Seen, EPC_BYTES);
        newRecord.timeLastSeen = timeSeen;
        TagsSeen[i] = newRecord;
        added = true;
      }
    }
  }

  // if there were no open slots in the array
  if(!added) {
    Serial.println("Error: no room in array of transponders.");
  }
}

//=====[ hasBeenSeenRecently ]==================================================
bool hasBeenSeenRecently(byte EPC_Seen[], unsigned long timeSeen) {
  // check if EPC has been seen less than a second ago
  for (int i = 0; i < MAX_TRANSPONDERS; i++) {
    /*Serial.print("debug_array:");
    for(int j = 0; j < EPC_BYTES; j++) {
          if(TagsSeen[i].tagEPC[j] < 0x10) Serial.print(0);
          Serial.print(TagsSeen[i].tagEPC[j], HEX);
        }
    Serial.print(",");
    Serial.println(TagsSeen[i].timeLastSeen, DEC);*/
    if ((timeSeen - TagsSeen[i].timeLastSeen) < 1000 &&
        memcmp(EPC_Seen, TagsSeen[i].tagEPC, EPC_BYTES ) == 0 ) {
      return true;
    }
  }
  return false;
}

//=====[ syncTime ]=============================================================
void syncTime() {
  unsigned long currentRaceTime = millis() - TimeRaceStarted;
  if (currentRaceTime % TIME_SYNC_INTERVAL == 0 && currentRaceTime != LastTimeReported) {
    Serial.print("%T");
    Serial.print(currentRaceTime, HEX);
    Serial.print("&");
    // this variable keeps us from reporting the time more than once per millisecond, if the main
    // loop is returning us here more than once per millisecond (was 5 times in testing)
    LastTimeReported = currentRaceTime;
  }
}

//=====[ setupNano ]=============================================================
bool setupNano(long baudRate) {
  nano.begin(Serial1);  // Tell the library to communicate over Uno R4 hardware serial port

  // Test to see if we are already connected to a module
  // This would be the case if the Arduino has been reprogrammed and the module has stayed powered
  // For this test, assume module is already at our desired baud rate
  Serial1.begin(baudRate);  // Initialize UART

  //About 200ms from power on the module will send its firmware version at 115200. We need to ignore this.
  while (Serial1.available()) Serial1.read();
  nano.getVersion();

  if (nano.msg[0] == ERROR_WRONG_OPCODE_RESPONSE) {
    //This happens if the baud rate is correct but the module is doing a continuous read
    nano.stopReading();
    Serial.println(F("Module continuously reading. Asking it to stop..."));
    delay(1500);
  } else {
    //The module did not respond so assume it's just been powered on and communicating at 115200bps
    Serial1.begin(115200);  // Start software serial at 115200
    nano.setBaud(baudRate);  // Tell the module to go to the chosen baud rate. Ignore the response msg
    Serial1.begin(baudRate);  // Start the software serial port, this time at user's chosen baud rate
    delay(250);
  }

  // Test the connection
  nano.getVersion();
  if (nano.msg[0] != ALL_GOOD) return (false);  //Something is not right

  // The M6E has these settings no matter what
  nano.setTagProtocol();  //Set protocol to GEN2
  nano.setAntennaPort();  //Set TX/RX antenna ports to 1

  return (true);  //We are ready to rock
}
