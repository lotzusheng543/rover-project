#include <WiFi.h>
#include <ESP32Servo.h>
#include <CytronMotorDriver.h>

Servo myservo;  // create Servo object to control a servo for tail

int servoPin = 13;
CytronMD motor1(PWM_DIR, 21, 19);  // PWM = Pin 21 white, DIR = Pin 19 yellow
CytronMD motor2(PWM_DIR, 33, 32);   // PWM = Pin 33 white, DIR = Pin 32 yellow




const char *ssid = "ESP32_AP";  // Access Point Name
const char *password = "12345678";  // AP Password

WiFiServer server(80);  // Start server on port 80

void setup() {
    Serial.begin(115200);
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    
    myservo.attach(servoPin);

    delay(10);

    pinMode(19, OUTPUT);  // Motor 1 方向
    pinMode(32, OUTPUT);  // Motor 2 方向
    pinMode(21, OUTPUT);  // Motor 1 PWM
    pinMode(33, OUTPUT);  // Motor 2 PWM

    // 確保馬達初始化時不會亂轉
    digitalWrite(19, LOW);
    digitalWrite(32, LOW);
    analogWrite(21, 0);  // PWM = 0，馬達不轉
    analogWrite(33, 0);  // PWM = 0，馬達不轉



    // Start WiFi in Access Point mode
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    Serial.println("Access Point Started!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());  // Print AP IP Address

    server.begin();  // Start the server
    myservo.write(90);
}

void loop() {
    WiFiClient client = server.available();  // Check for incoming clients

    if (client) {  // If a new client connects
        Serial.println("New Client Connected");
        String request = "";

        while (client.connected()) {
            if (client.available()) {
                char c = client.read();  // Read incoming data
                request += c;
                Serial.write(c);

                if (request.endsWith("\r\n\r\n")) break;  // End of request
            }
        }

        // Movement controls
        if (request.indexOf("GET /R") != -1) {
            Serial.println("Turning Right");
            myservo.write(120);
        }
        if (request.indexOf("GET /L") != -1) {
            Serial.println("Turning Left");
            myservo.write(60);
        }
        if (request.indexOf("GET /S") != -1) {
            Serial.println("Moving Straight");
            myservo.write(90);
        }
        if (request.indexOf("GET /F") != -1) {
            Serial.println("Moving Forward");
            motor1.setSpeed(120);
            motor2.setSpeed(120);
        }
        if (request.indexOf("GET /B") != -1) {
            Serial.println("Moving Backward");
            motor1.setSpeed(-120);
            motor2.setSpeed(-120);
        }
        if (request.indexOf("GET /O") != -1) {
            Serial.println("Stopping");
            motor1.setSpeed(0);
            motor2.setSpeed(0);
        }

        // ✅ Handle speed slider updates
        if (request.indexOf("GET /speed?value=") != -1) {
        int index = request.indexOf("value=") + 6;
        int speed = request.substring(index).toInt();  // 取得速度值
        Serial.print("Setting Motor Speed to: ");
        Serial.println(speed);

        if (speed > 0) {
        // 前進
        digitalWrite(19, HIGH);
        digitalWrite(32, HIGH);
      } else if (speed < 0) {
        // 後退
        digitalWrite(19, LOW);
        digitalWrite(32, LOW);
        speed = -speed;  // PWM 不能是負值
        } else {
        // 停止
        digitalWrite(19, LOW);
        digitalWrite(32, LOW);
    }

        // 設定 PWM
        analogWrite(21, speed);
        analogWrite(33, speed);
}

        }

        // Send HTML response
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();

        
        client.println("<!DOCTYPE html><html lang='en'><head>");
        client.println("<meta charset='UTF-8'>");
        client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
        client.println("<title>Rover Control</title>");
        client.println("<style>");
        client.println("body { font-family: Arial, sans-serif; text-align: center; background-color: black; color: white; margin: 0; }");
        client.println(".container { display: flex; justify-content: center; align-items: center; height: 80vh; gap: 50px; }");
        client.println(".control-section { text-align: center; }");
        client.println(".grid { display: grid; grid-template-columns: 1fr; gap: 10px; justify-content: center; align-items: center; }");
        client.println(".middle-row { display: flex; justify-content: center; gap: 20px; }");
        client.println(".button { width: 80px; height: 80px; font-size: 16px; font-weight: bold; border: 4px solid #01f; background-color: #88f; cursor: pointer; border-radius: 5px; }");
        client.println(".button:hover { background-color: #66c; }");
        client.println(".stop-button { background-color: red; border: 2px solid lightgreen; color: white; width: 100px; height: 60px; }");
        client.println(".on-button { background-color: lightgreen; border: 2px solid lightsalmon; color: black; width: 100px; height: 60px; }");
        client.println(".stop-button:hover, .on-button:hover { opacity: 0.65; }");
        client.println(".extra-function { display: flex; flex-direction: column; align-items: center; gap: 15px; }");
        client.println("</style></head><body>");

        // Top Section
        client.println("<div class='top-section'><p>Group 5 Rover</p>");
        client.println("<img src='data:image/png;base64,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' ></div>");


        
        // Container for Controls
        client.println("<div class='container'>");

        // Movement Controls
        client.println("<div class='control-section'><p>Movement Controls</p>");
        client.println("<div class='control-buttons'>");

        // Forward button (↑)
        client.println("<button class='button' onclick=\"sendCommand('F')\">&#x2191;</button>");

        // Left (←), Stop, Right (→)
        client.println("<button class='button' onclick=\"sendCommand('L')\">&#x2190;</button>");
        client.println("<button class='button' onclick=\"sendCommand('R')\">&#x2192;</button>");

        // Backward button (↓)
        client.println("<button class='button' onclick=\"sendCommand('B')\">&#x2193;</button>");

        client.println("</div></div>"); // Close control-buttons and control-section

        // Extra Functions
        client.println("<div class='control-section'><p>EXTRA FUNCTION</p>");
        client.println("<button class='button stop-button' onclick=\"sendCommand('O')\">STOP</button>");
        client.println("<button class='button on-button' onclick=\"sendCommand('S')\">Straight</button>");
        client.println("</div>"); // Close control-section

        // ✅ Speed Control UI
        client.println("<div class='control-section'><p>Adjust Motor Speed</p>");
        client.println("<input type='range' id='speedSlider' min='-255' max='255' value='120' oninput='updateSpeed(this.value)'>");
        client.println("<p>Speed: <span id='speedValue'>120</span></p>");
        client.println("</div>");

        // ✅ JavaScript for Real-Time Speed Update (Prevents Page Refresh)
        client.println("<script>");
        client.println("function sendCommand(cmd) {");
        client.println("  fetch('/' + cmd, { method: 'GET' })");
        client.println("    .then(response => console.log('Command sent:', cmd))");
        client.println("    .catch(error => console.error('Error:', error));");
        client.println("}");

        client.println("function updateSpeed(value) {");
        client.println("  document.getElementById('speedValue').innerText = value;");
        client.println("  fetch('/speed?value=' + value, { method: 'GET' })");
        client.println("    .then(response => console.log('Speed updated:', value))");
        client.println("    .catch(error => console.error('Error:', error));");
        client.println("}");
        client.println("</script>");


        client.println("</body></html>");


            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
        client.stop();  // Close the connection
        Serial.println("Client Disconnected");
    }

