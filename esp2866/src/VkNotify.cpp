#include "VkNotify.h"
#include "globals.h"


VkNotify::VkNotify() {
  httpClient.setTimeout(1000);
  httpClient.setServer("api.vk.com", 443);
}

void VkNotify::sendMessage(const String &messageText) {
  httpClient.get("/method/messages.send?user_id=" + urlEncode(settings.vkUserId) +
                "&message=" + urlEncode(messageText) +
                "&access_token=" + urlEncode(settings.vkAccessToken) +
                "&v=5.131&random_id=" + String(random(1, 2147483647)));
}

void VkNotify::loop() {
  httpClient.update();
}

String VkNotify::urlEncode(const String &value) {
  const char hex[] = "0123456789ABCDEF";
  String encoded;
  encoded.reserve(value.length() * 3);

  for (size_t i = 0; i < value.length(); i++) {
    uint8_t c = static_cast<uint8_t>(value[i]);
    if ((c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') ||
        c == '-' || c == '_' || c == '.' || c == '~') {
      encoded += static_cast<char>(c);
    } else {
      encoded += '%';
      encoded += hex[c >> 4];
      encoded += hex[c & 0x0F];
    }
  }

  return encoded;
}
