// WIFI INCLUDES
#include "WiFi.h"
#include <WiFiUdp.h>
#include <NTPClient.h>

// WIFI CREDENTIAL DECLARATIONS
const char *ssid = "np2";
const char *password = "somepass";

// TIME DECLARATIONS
const long utcOffsetInSeconds = -18000;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
int previousHour;
int previousMinute;
bool initTime = false;
String formattedDate;
String timeStamp;

// SPOTIFY DECLARATIONS
const char* CLIENT_ID = "776b2c6f0d7347d6b7aae2e9ae50263b";//leave these empty if you want to set the credentials during runtime
const char* CLIENT_SECRET = "19955d891af446debd48933ea0786789";//leave these empty if you want to set the credentials during runtime
const char* REFRESH_TOKEN = "someKey";
String currentArtist;
String currentTrack;

// NEWS DECLARATIONS
String serverName = "http://newsapi.org/v2/top-headlines?country=us&apiKey=somekey&category=technology&pageSize=3";
struct Article {
  String source_id;
  String source_name;
  String author;
  String title;
  String description;
  String url;
  String urlToImage;
  String publishedAt;
  String content;
};

Article articles[10];  // Adjust size as needed
int articleCount = 0;