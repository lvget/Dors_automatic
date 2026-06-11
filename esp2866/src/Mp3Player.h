#ifndef MP3_PLAYER_H
#define MP3_PLAYER_H

#include <Arduino.h>

class AudioFileSourceLittleFS;
class AudioGeneratorMP3;
class AudioOutputI2SNoDAC;

// AudioOutputI2SNoDAC on ESP8266 outputs audio on I2STx:
//   NodeMCU RX pin / GPIO3.
// Connect the amplifier/transistor input to RX/GPIO3 and GND to GND.
// Do not connect a speaker directly to the ESP8266 pin; use an amplifier
// or the transistor + resistor circuit from the ESP8266Audio NoDAC docs.
// RX/GPIO3 is also the serial receive pin, so the audio circuit may need to
// be disconnected while flashing if it interferes with upload.
class Mp3Player {
public:
  Mp3Player() = default;
  ~Mp3Player();

  Mp3Player(const Mp3Player&) = delete;
  Mp3Player& operator=(const Mp3Player&) = delete;

  bool play(const String& fileName);
  bool play(const char* fileName);
  void stop();
  void loop();
  bool isPlaying() const;

private:
  AudioGeneratorMP3* _mp3 = nullptr;
  AudioFileSourceLittleFS* _file = nullptr;
  AudioOutputI2SNoDAC* _out = nullptr;

  String normalizePath(const String& fileName) const;
  void release();
};

#endif
