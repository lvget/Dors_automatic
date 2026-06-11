#include "globals.h"
#include "WebServer.h"
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include "ArduinoJson-v7.4.3.h"

#define OTA_USER         "admin"    // Логин для входа в OTA
#define OTA_PASSWORD     "admin"    // Пароль для входа в ОТА
//#define OTA_PATH         "/update"// Путь, который будем дописывать после ip адреса в браузере.
#define SERVERPORT      80         // Порт для входа, он стандартный 80 это порт http

ESP8266WebServer server(SERVERPORT);
ESP8266HTTPUpdateServer httpUpdater;

const char* HTML = "text/html";
const char* JSON = "application/json";
void send(int code, const char *content_type, const char *content) {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(code, content_type, content);
}

void send(const char *content_type, const char *content) {
  send(200, content_type, content);
}

void send(const char *content) {
  send(200,HTML, content);
}

void sendJson(String& content) {
  send(200, JSON, content.c_str());
}

static void handleGetTime(){
  if (appClock.isSynced()) {
    String response = appClock.getFormattedTime();
      send(response.c_str()); // appClock.getFormattedTime());
    } else {
      send("Waiting for NTP time...");
    }
}

void handleGetSettings(){
  String response = settings.toJson();
  sendJson(response);
}

void handleSetSettings(){
    String body = server.arg("plain");

    if (!settings.fromJson(body)) {
        send(400, HTML, "Invalid JSON");
        return;
    }
    send("Ok");
}


void handleIOCommand(){
    String lamp = server.arg("id");
    int value = server.arg("value").toInt();
    IO_command(lamp, value);
    send("Ok");
}

void handleIOValues(){
  String response = IO_values();
  sendJson(response);
}


String getContentType(String filename) {
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".json")) return "application/json";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

void sendFile() {
    String path = server.uri();
    if(path == "/")
      path = "/index.html";
    Serial.print("Requested: ");
    Serial.println(path);

    File file = LittleFS.open(path, "r");
    if (!file) {
      send(404, "text/plain", "Not Found");
      return;
    }

    server.streamFile(file, getContentType(path));
    file.close();
}

void listFilesToJson(String &json, const String &path) {
  Dir dir = LittleFS.openDir(path);
  while (dir.next()) {
    if (dir.isFile()) {
      if (json.length() > 1) json += ",";
      json += "{\"name\":\"" + path + dir.fileName() + "\",";
      json += "\"size\":" + String(dir.fileSize()) + "}";
    } else if (dir.isDirectory()) {
      listFilesToJson(json, path + dir.fileName() + "/");
    }
  }
}

void handleFils() {
  String json = "[";
  listFilesToJson(json, "/");
  json += "]";
  sendJson(json);
}

void WebServer::begin(){
  httpUpdater.setup(&server, OTA_USER, OTA_PASSWORD);
  server.onNotFound(sendFile);
  server.on("/time", HTTP_GET, handleGetTime);
  server.on("/settings", HTTP_GET, handleGetSettings);
  server.on("/settings", HTTP_POST, handleSetSettings);
  server.on("/io", HTTP_POST, handleIOCommand);
  server.on("/io", HTTP_GET, handleIOValues);
  server.on("/files", HTTP_GET, handleFils);
  server.begin();
}

void WebServer::loop(){
  server.handleClient(); 
}