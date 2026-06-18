#ifndef NonBlockingHTTPClient_h
#define NonBlockingHTTPClient_h

#include <ESP8266WiFi.h>
#include <functional>

class NonBlockingHTTPClient {
public:
  typedef std::function<void(int httpCode, const String& payload)> HttpResponseCallback;

  NonBlockingHTTPClient(unsigned long timeout = 5000);

  void setServer(const String& host, int port = 80);
  void setTimeout(unsigned long timeout);
  bool get(const String& path, HttpResponseCallback callback);
  void update();
  bool isBusy() const;
  void stop();

private:
  enum State {
    STATE_IDLE,
    STATE_CONNECTING,
    STATE_SENDING,
    STATE_READING,
    STATE_DONE
  };

  String _host;
  int _port;
  unsigned long _timeout;
  String _path;

  State _state;
  unsigned long _stateStartTime;

  WiFiClient _client;
  HttpResponseCallback _callback;

  String _responseBuffer;
  int _httpCode;
  bool _headersParsed;
};

#endif
