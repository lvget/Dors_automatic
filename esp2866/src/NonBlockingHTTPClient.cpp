#include "NonBlockingHTTPClient.h"

NonBlockingHTTPClient::NonBlockingHTTPClient(unsigned long timeout) {
  _timeout = timeout;
  _state = STATE_IDLE;
  _port = 80;
  _httpCode = 0;
  _headersParsed = false;
}

void NonBlockingHTTPClient::setServer(const String& host, int port) {
  _host = host;
  _port = port;
}

void NonBlockingHTTPClient::setTimeout(unsigned long timeout) {
  _timeout = timeout;
}

bool NonBlockingHTTPClient::get(const String& path, HttpResponseCallback callback) {
  if (_state != STATE_IDLE) {
    return false;
  }

  _path = path;
  _callback = callback;
  _responseBuffer = "";
  _httpCode = 0;
  _headersParsed = false;
  _state = STATE_CONNECTING;
  _stateStartTime = millis();

  return true;
}

void NonBlockingHTTPClient::update() {
  if (_state == STATE_IDLE) {
    return;
  }

  switch (_state) {
    case STATE_CONNECTING:
      if (_client.connect(_host.c_str(), _port)) {
        _state = STATE_SENDING;
      } else if (millis() - _stateStartTime > _timeout) {
        _httpCode = -1;
        _state = STATE_DONE;
      }
      break;

    case STATE_SENDING: {
      String request = String("GET ") + _path + " HTTP/1.1\r\n" +
                       "Host: " + _host + "\r\n" +
                       "Connection: close\r\n" +
                       "User-Agent: ESP8266\r\n\r\n";
      _client.print(request);

      _state = STATE_READING;
      _stateStartTime = millis();
      break;
    }

    case STATE_READING: {
      uint8_t buf[128];
      int len = _client.read(buf, sizeof(buf));

      if (len > 0) {
        for (int i = 0; i < len; i++) {
          _responseBuffer += (char)buf[i];

          if (!_headersParsed && _responseBuffer.length() >= 4) {
            int headerEnd = _responseBuffer.indexOf("\r\n\r\n");
            if (headerEnd >= 0) {
              _headersParsed = true;

              int firstSpace = _responseBuffer.indexOf(' ');
              int secondSpace = _responseBuffer.indexOf(' ', firstSpace + 1);
              if (firstSpace > 0 && secondSpace > 0) {
                _httpCode = _responseBuffer.substring(firstSpace + 1, secondSpace).toInt();
              }

              _responseBuffer = _responseBuffer.substring(headerEnd + 4);
            }
          }
        }
      }

      if (!_client.connected() && _client.available() == 0) {
        _state = STATE_DONE;
      } else if (millis() - _stateStartTime > _timeout) {
        _httpCode = -2;
        _state = STATE_DONE;
      }
      break;
    }

    case STATE_DONE:
      _client.stop();
      if (_callback) {
        _callback(_httpCode, _responseBuffer);
      }
      _state = STATE_IDLE;
      break;

    case STATE_IDLE:
      break;
  }
}

bool NonBlockingHTTPClient::isBusy() const {
  return _state != STATE_IDLE;
}

void NonBlockingHTTPClient::stop() {
  _client.stop();
  _state = STATE_IDLE;
  _responseBuffer = "";
}
