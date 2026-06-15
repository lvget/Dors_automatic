#ifndef __VK_BOT_H
#define __VK_BOT_H

#include <Arduino.h>

class VkBot {
public:
  VkBot();

  void sendMessage(const String &messageText);

private:
  static String urlEncode(const String &value);
};

#endif
