#ifndef __VK_NOTIFY_H
#define __VK_NOTIFY_H

#include <Arduino.h>
#include "NonBlockingHTTPClient.h"


class VkNotify{
  public:
  VkNotify();
  void sendMessage(const String &messageText);
  void loop();

private:
  NonBlockingHTTPClient httpClient;
  static String urlEncode(const String &value);
};

#endif
