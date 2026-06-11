#include "Mp3Player.h"

#include <LittleFS.h>
#include <AudioFileSourceLittleFS.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2SNoDAC.h>

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

  _out->SetGain(0.6f);

  if (!_mp3->begin(_file, _out)) {
    Serial.print("MP3 playback failed: ");
    Serial.println(path);
    release();
    return false;
  }

  Serial.print("MP3 playback started: ");
  Serial.println(path);
  return true;
}

void Mp3Player::stop() {
  if (_mp3 != nullptr && _mp3->isRunning()) {
    _mp3->stop();
  }

  release();
}

void Mp3Player::loop() {
  if (_mp3 == nullptr) {
    return;
  }

  if (_mp3->isRunning()) {
    if (!_mp3->loop()) {
      stop();
    }
  } else {
    stop();
  }
}

bool Mp3Player::isPlaying() const {
  return _mp3 != nullptr && _mp3->isRunning();
}
