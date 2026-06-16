#ifndef __VK_BOT_H
#define __VK_BOT_H

#include <Arduino.h>

class VkBot {
public:
  VkBot();

  void sendMessage(const String &messageText);
  void loop();

private:
  static const uint8_t QUEUE_SIZE = 3;
  String messages[QUEUE_SIZE];
  uint8_t queueHead = 0;
  uint8_t queueTail = 0;
  uint8_t queueCount = 0;
  unsigned long nextAttemptMillis = 0;

  bool enqueue(const String &messageText);
  bool dequeue(String &messageText);
  void sendQueuedMessage(const String &messageText);

  static String urlEncode(const String &value);
};

#endif
