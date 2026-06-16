#ifndef NonBlockingHTTPClient_h
#define NonBlockingHTTPClient_h

#include <ESP8266WiFi.h>
#include <functional>

class NonBlockingHTTPClient {
public:
    // Тип функции обратного вызова: (HTTP код, Тело ответа)
    typedef std::function<void(int httpCode, const String& payload)> HttpResponseCallback;

    NonBlockingHTTPClient(unsigned long timeout = 5000);

    // Настройка параметров запроса
    void setServer(const String& host, int port = 80);
    void setTimeout(unsigned long timeout);

    // Запуск GET запроса. Возвращает true, если запрос успешно инициирован.
    bool get(const String& path, HttpResponseCallback callback);

    // Эту функцию нужно вызывать внутри основного loop()
    void update();

    // Проверка, выполняется ли сейчас запрос
    bool isBusy() const;

    // Принудительная остановка и сброс состояния
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
    String _path;           // <--- ДОБАВЛЕНО: переменная для хранения пути
    
    State _state;
    unsigned long _stateStartTime;
    
    WiFiClient _client;
    HttpResponseCallback _callback;
    
    String _responseBuffer;
    int _httpCode;
    bool _headersParsed;
};

// --- Реализация методов ---

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
        return false; // Уже выполняется запрос
    }
    
    _path = path;       // <--- ДОБАВЛЕНО: сохраняем путь запроса
    _callback = callback;
    _responseBuffer = "";
    _httpCode = 0;
    _headersParsed = false;
    _state = STATE_CONNECTING;
    _stateStartTime = millis();
    
    return true;
}

void NonBlockingHTTPClient::update() {
    if (_state == STATE_IDLE) return;

    switch (_state) {
        case STATE_CONNECTING:
            if (_client.connect(_host.c_str(), _port)) {
                _state = STATE_SENDING;
            } else if (millis() - _stateStartTime > _timeout) {
                _httpCode = -1; // Таймаут подключения
                _state = STATE_DONE;
            }
            break;

        case STATE_SENDING:
            // Теперь _path определен и используется корректно
            String request = String("GET ") + _path + " HTTP/1.1\r\n" +
                            "Host: " + _host + "\r\n" +
                            "Connection: close\r\n" +
                            "User-Agent: ESP8266\r\n\r\n";
            _client.print(request);
            
            _state = STATE_READING;
            _stateStartTime = millis();
            break;

        case STATE_READING: {
            // Истинно неблокирующее чтение чанками
            uint8_t buf[128];
            int len = _client.read(buf, sizeof(buf));
            
            if (len > 0) {
                for (int i = 0; i < len; i++) {
                    _responseBuffer += (char)buf[i];
                    
                    // Парсинг заголовков "на лету"
                    if (!_headersParsed && _responseBuffer.length() >= 4) {
                        int headerEnd = _responseBuffer.indexOf("\r\n\r\n");
                        if (headerEnd >= 0) {
                            _headersParsed = true;
                            
                            // Извлекаем HTTP код из первой строки (например, "HTTP/1.1 200 OK")
                            int firstSpace = _responseBuffer.indexOf(' ');
                            int secondSpace = _responseBuffer.indexOf(' ', firstSpace + 1);
                            if (firstSpace > 0 && secondSpace > 0) {
                                _httpCode = _responseBuffer.substring(firstSpace + 1, secondSpace).toInt();
                            }
                            
                            // Оставляем в буфере только тело ответа
                            _responseBuffer = _responseBuffer.substring(headerEnd + 4);
                        }
                    }
                }
            }
            
            // Если соединение разорвано сервером и буфер пуст, или истек таймаут
            if (!_client.connected() && _client.available() == 0) {
                _state = STATE_DONE;
            } else if (millis() - _stateStartTime > _timeout) {
                _httpCode = -2; // Таймаут чтения
                _state = STATE_DONE;
            }
            break;
        }

        case STATE_DONE:
            _client.stop();
            if (_callback) {
                _callback(_httpCode, _responseBuffer);
            }
            _state = STATE_IDLE; // Возврат в исходное состояние
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

#endif