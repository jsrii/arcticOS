#include <Arduino.h>
#include <MenuX.h>
#include "arcticLOGO.h"
#include "wifiDeclarations.h"
#include <SpotifyEsp32.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

Spotify sp(CLIENT_ID, CLIENT_SECRET, REFRESH_TOKEN);
TFT_eSPI tft = TFT_eSPI(170, 320);

#include "functionDeclarations.h"
#include "menuDeclarations.h"
Menu menu(btn1, btn2, tft, menuItems, menuItemsCount, &oy);

void setup() {
  Serial.begin(115200);

  // basic TFT init for TTGO T-Display
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(0, 0);
  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(1);
  tft.setSwapBytes(true);

  //arcticOSLaunch();
  wifiTimeInit();
  spotifyInit();

  // set up callback for menu context changes
  menu.getMenuFlow().subscribe([](const Menu::MenuContext& context) {
    Serial.print("State changed: Label=");
    Serial.print(context.currentItemLabel);
    Serial.print(", Action=");
    Serial.println(context.currentItemAction);
  });
  menu.begin();
}


void loop() {
  menu.loop();
  formattedDate = timeClient.getFormattedTime();
  int splitT = formattedDate.indexOf("T");
  timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 3);
  tft.drawString(timeStamp, 50, 161, 1);
  timeClient.update();
}

