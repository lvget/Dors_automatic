#include "Mp3Player.h"

#include <LittleFS.h>
#include <AudioFileSourceLittleFS.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2SNoDAC.h>
#include "IO.h"

extern IO io;

Mp3Player::~Mp3Player() {
  stop();
}

String Mp3Player::normalizePath(const String& fileName) const {
  if (fileName.length() == 0) {
    return "";
  }

  if (fileName[0] == '/') {
    return fileName;
  }

  return "/" + fileName;
}

String Mp3Player::mp3Path(uint16_t fileNumber) const {
  return "/mp3/" + String(fileNumber) + ".mp3";
}

uint16_t Mp3Player::parseMp3FileNumber(const String& fileName) const {
  String name = fileName;
  int slash = name.lastIndexOf('/');
  if (slash >= 0) {
    name = name.substring(slash + 1);
  }

  if (!name.endsWith(".mp3")) {
    return 0;
  }

  name.remove(name.length() - 4);
  if (name.length() == 0) {
    return 0;
  }

  for (unsigned int i = 0; i < name.length(); i++) {
    if (!isDigit(name[i])) {
      return 0;
    }
  }

  return (uint16_t)name.toInt();
}

uint16_t Mp3Player::findNextFileNumber(uint16_t startFrom) const {
  Dir dir = LittleFS.openDir("/mp3");
  uint16_t nearest = 0;
  uint16_t first = 0;

  while (dir.next()) {
    if (!dir.isFile()) {
      continue;
    }

    uint16_t number = parseMp3FileNumber(dir.fileName());
    if (number == 0) {
      continue;
    }

    if (first == 0 || number < first) {
      first = number;
    }

    if (number >= startFrom && (nearest == 0 || number < nearest)) {
      nearest = number;
    }
  }

  return nearest != 0 ? nearest : first;
}

void Mp3Player::release() {
  if (_mp3 != nullptr) {
    delete _mp3;
    _mp3 = nullptr;
  }

  if (_out != nullptr) {
    delete _out;
    _out = nullptr;
  }

  if (_file != nullptr) {
    delete _file;
    _file = nullptr;
  }
}

bool Mp3Player::play(const char* fileName) {
  return play(String(fileName));
}

bool Mp3Player::play(const String& fileName) {
  String path = normalizePath(fileName);

  if (path.length() == 0 || !LittleFS.exists(path)) {
    Serial.print("MP3 file not found: ");
    Serial.println(path);
    return false;
  }

  stop();

  _file = new AudioFileSourceLittleFS(path.c_str());
  _out = new AudioOutputI2SNoDAC();
  _mp3 = new AudioGeneratorMP3();

  if (_file == nullptr || _out == nullptr || _mp3 == nullptr) {
    Serial.println("MP3 player allocation failed");
    release();
    return false;
  }

  _out->SetGain(0.25f);

  if (!_mp3->begin(_file, _out)) {
    Serial.print("MP3 playback failed: ");
    Serial.println(path);
    release();
    return false;
  }

  Serial.print("MP3 playback started: ");
  Serial.println(path);
  Serial.print("Free heap: ");
  Serial.println(ESP.getFreeHeap());
  return true;
}

bool Mp3Player::playDoorbell(uint16_t fileNumber) {
  if (fileNumber != 0) {
    return play(mp3Path(fileNumber));
  }

  uint16_t number = findNextFileNumber(_nextFileNumber);
  if (number == 0) {
    Serial.println("No MP3 files found in /mp3");
    return false;
  }

  if (!play(mp3Path(number))) {
    return false;
  }

  _nextFileNumber = number + 1;
  return true;
}

void Mp3Player::stop() {
  if (_mp3 != nullptr && _mp3->isRunning()) {
    _mp3->stop();
  }

  release();
  io.restorePins();
}

void Mp3Player::loop() {
  if (_mp3 == nullptr) {
    return;
  }

  if (_mp3->isRunning()) {
    if (!_mp3->loop()) {
      stop();
    }
    yield();
  } else {
    stop();
  }
}

bool Mp3Player::isPlaying() const {
  return _mp3 != nullptr && _mp3->isRunning();
}
