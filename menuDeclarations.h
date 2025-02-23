// menu buttons init
Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);

//  ITEM NAME       ITEM ACTION     CALLBACK
MenuItem bleConnectItems[] = {
  { "Option 1", "Option 1", []() {
     Serial.println("Option 1 was selected!");
   } },
  { "Option 2", "Option 2", []() {
     Serial.println("Option 2 was selected!");
   } },
  { "Option 3", "Option 3", []() {
     Serial.println("Option 3 was selected!");
   } },
  { "Option 4", "Option 4", []() {
     Serial.println("Option 4 was selected!");
   } },
  { "Option 5", "Option 5", []() {
     Serial.println("Option 5 was selected!");
   } },
  { "Option 6", "Option 6", []() {
     Serial.println("Option 6 was selected!");
   } },
  { "Option 7", "Option 7", []() {
     Serial.println("Option 7 was selected!");
   } },
  { "Option 8", "Option 8", []() {
     Serial.println("Option 8 was selected!");
   } },
  { "Option 9", "Option 9", []() {
     Serial.println("Option 9 was selected!");
   } },
  { "Option 10", "Option 10", []() {
     Serial.println("Option 10 was selected!");
   } },
  { "Option 11", "Option 11", []() {
     Serial.println("Option 11 was selected!");
   } },
  { "Option 12", "Option 12", []() {
     Serial.println("Option 12 was selected!");
   } },
  { "Option 13", "Option 13", []() {
     Serial.println("Option 13 was selected!");
   } },
};

int bleConnectItemsCount = sizeof(bleConnectItems) / sizeof(bleConnectItems[0]);

MenuItem wiFiItems[] = {
  { "Scan", "Scan", nullptr },
  { "Create", "Create", nullptr }
};
int wiFiItemsCount = sizeof(wiFiItems) / sizeof(wiFiItems[0]);

//  ITEM NAME       ITEM ACTION     CALLBACK    SUB-MENU            SUB-MENU ITEMS COUNT
MenuItem bleItems[] = {
  { "Connect", "View", nullptr, bleConnectItems, bleConnectItemsCount },
  { "Scan", "Scan", nullptr },
};
int bleItemsCount = sizeof(bleItems) / sizeof(bleItems[0]);

MenuItem wirelessItems[] = {
  { "BLE", "View", nullptr, bleItems, bleItemsCount },
  { "Wi-Fi", "View", nullptr, wiFiItems, wiFiItemsCount },
};
int wirelessItemsCount = sizeof(wirelessItems) / sizeof(wirelessItems[0]);

//  ITEM NAME       ITEM ACTION     CALLBACK    SUB-MENU            SUB-MENU ITEMS COUNT
MenuItem flashlightItems[] = {
  { "Turn On/Off", "View", nullptr },
  { "Flash On/Off", "View", nullptr },
  { "SOS", "View", nullptr }
};
int flashlightItemsCount = sizeof(flashlightItems) / sizeof(flashlightItems[0]);


//  ITEM NAME       ITEM ACTION     CALLBACK    SUB-MENU            SUB-MENU ITEMS COUNT
MenuItem spotifyItems[] = {
  { "Fetch Spotify Data", "View", []() {
     currentArtist = sp.current_artist_names();
     currentTrack = sp.current_track_name();
     tft.drawString(currentArtist, 0, 70, 1);
     tft.drawString(currentTrack, 0, 80, 1);
     while (digitalRead(14) != 0) {
     }
   } },
  { "Play/Pause", "View", []() {
     if (sp.is_playing()) {
       sp.pause_playback();
     } else {
       sp.start_resume_playback(NULL);
     }
   } },
  { "Skip", "View", []() {
     sp.skip();
   } },
  { "Previous", "View", []() {
     sp.previous();
   } }
};
int spotifyItemsCount = sizeof(spotifyItems) / sizeof(spotifyItems[0]);


MenuItem menuItems[] = {
  { "Reminders", "View", nullptr },
  { "Home Devices", "View", nullptr },
  { "Spoofer", "View", nullptr },
  { "GPS Tracker", "View", nullptr },
  { "News", "View", []() {
     fetchNews();
     while (digitalRead(14) != 0) {
     }
   } },
  { "Spotify", "View", nullptr, spotifyItems, spotifyItemsCount },
  { "Flashlight", "View", nullptr, flashlightItems, flashlightItemsCount },
  { "Car View", "View", nullptr },
  { "Sleep", "Turn off", nullptr },
};

int menuItemsCount = sizeof(menuItems) / sizeof(menuItems[0]);

// menu top ofset (e.g. for status bar)
int oy = 0;
