void fetchNews() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName.c_str());
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();
      StaticJsonDocument<8192> doc;  // Adjust size if necessary

      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }

      JsonArray articleArray = doc["articles"].as<JsonArray>();

      int i = 0;
      for (JsonObject article : articleArray) {
        if (i >= 3) break;

        JsonObject source = article["source"];

        articles[i].source_id = source["id"] | "Unknown";
        articles[i].source_name = source["name"] | "Unknown";
        articles[i].author = article["author"] | "Unknown";
        articles[i].title = article["title"] | "Untitled";
        articles[i].description = article["description"] | "No description";
        articles[i].url = article["url"] | "No URL";
        articles[i].urlToImage = article["urlToImage"] | "No Image";
        articles[i].publishedAt = article["publishedAt"] | "Unknown Date";
        articles[i].content = article["content"] | "No content available";
        i++;
      }
      tft.fillScreen(TFT_BLACK);
      tft.drawLine(0, 157, tft.width(), 157,
                   MENU_DIVIDER_COLOR);
      tft.fillRect(0, 158, tft.width(), 12, TFT_BLACK);
      tft.setCursor(2, 161);
      tft.print("<< Exit News App");
      tft.setCursor(0, 0);
      for (int i = 0; i < 3; i++) {
        tft.print(articles[i].title);
        tft.println("");
        tft.print(articles[i].description);
        tft.println("\n");
      }
      Serial.println(articles[0].source_name);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}


void drawBoot() {
  tft.fillScreen(TFT_BLACK);
  tft.drawString("Welcome to arcticOS!", 60, 0, 1);
  tft.drawString("vm-page-bootstrap: 987323 free pages and 5723 used", 150, 8, 1);
  delay(random(250, 750));
  tft.drawString("arcticOS Kernel version 0.1 starting...", 117, 16, 1);
  delay(random(250, 750));
  tft.drawString("zone leak detection enabled", 80, 24, 1);
  delay(random(250, 750));
  tft.drawString("standard timesplicing sequence is 1000ms behind schedule", 113, 32, 1);
  delay(random(250, 750));
  tft.drawString("turbo encabulator: ACTIVE", 75, 40, 1);
  delay(random(250, 750));
  tft.drawString("hyperdrive: ACTIVE", 55, 48, 1);
  delay(50);
  tft.drawString("coreprocessor id=1 ENABLED", 85, 56, 1);
  delay(50);
  tft.drawString("coreprocessor id=2 ENABLED", 85, 64, 1);
  delay(50);
  tft.drawString("coreprocessor id=3 ENABLED", 85, 72, 1);
  delay(50);
  tft.drawString("coreprocessor id=4 ENABLED", 85, 80, 1);
  delay(random(250, 750));
  tft.drawString("calling eDEX-UI inspiration", 82, 88, 1);
  delay(random(250, 750));
  tft.drawString("com.arcticOS.activation kmod start", 103, 96, 1);
  delay(random(250, 750));
  tft.drawString("hacking capabilities: ACTIVE", 85, 104, 1);
  delay(random(250, 750));
  tft.drawString("project TYPE-01 intialize...", 85, 112, 1);
  delay(random(250, 750));
  tft.drawString("assigning hostname: GHOST-02", 85, 120, 1);
  delay(random(250, 750));
  tft.drawString("arcticOS is now booting", 70, 128, 1);
  delay(random(250, 500));
  tft.drawString(".", 138, 128, 1);
  delay(random(250, 500));
  tft.drawString(".", 144, 128, 1);
  delay(random(250, 500));
  tft.drawString(".", 150, 128, 1);
  delay(1000);
  tft.fillScreen(TFT_BLACK);
}

void arcticOSLaunch() {
  drawBoot();
  tft.fillScreen(TFT_WHITE);
  tft.drawXBitmap(0, 0, arcticLOGO, 320, 170, TFT_BLACK);
  delay(random(1000, 2500));
  tft.fillScreen(TFT_BLACK);
}


void wifiTimeInit() {
  WiFi.begin("np2.jassri", "274Church");
  Serial.println("Connecting...");

  WiFi.mode(WIFI_STA);  //Optional
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");
  tft.println("Connecting to main servers...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    tft.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  timeClient.update();
}

void spotifyInit() {
  sp.begin();
  while (!sp.is_auth()) {
    sp.handle_client();
  }
}
