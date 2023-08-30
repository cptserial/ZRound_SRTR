#include <Arduino.h>

void startup();
void startRace();
void stopRace();
void reportTags();
void addTagToList(byte EPC_Seen[], unsigned long timeSeen);
bool hasBeenSeenRecently(byte EPC_Seen[], unsigned long timeSeen);
void printTagsSeen();
void syncTime();
bool setupNano(long baudRate);