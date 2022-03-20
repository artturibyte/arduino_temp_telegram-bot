# arduino_temp_telegram-bot

ESP8266 arduino controller is measuring temperature with ds18b20 sensor and sending the measurement value to telegram bot, which is messaging the value to telegram group chat.
Requirements
- Wifi connection for ESP8266.
- Need to setup telegram account and telegram bot.


## TODO

Idea is to create a system where all scripts are mainly executed on server and ESP8266 controller is used only for measuring temperature data. 
Idea is to simplify the field device and makes it easier to work with the code(no need to get the system from outside and connect via usb). 
Also for learning purposes.

plan:
- linux server
- ESP8266 controller with sensor and wifi connection
- Script (python?) fetching data from controller and sending it to telegram bot.
- Maybe own website for visuals.

