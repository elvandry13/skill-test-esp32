/**
 * @file main.cpp
 * @author Elvandry Ghiffary (elvandry13@gmail.com)
 * @brief Skill Test for ESP32 firmware
 * @version 0.1
 * @date 2021-07-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Arduino.h"
#include "logger.h"
#include <AntaresESP32MQTT.h>

// Antares Credentials
#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"
#define projectName "your-project-name"
#define deviceName "your-device-name"

String buff = "";
byte buffbyte[1];
int ret, pwm;
bool datasent = false;

LoggingClass logger("/log.txt");
AntaresESP32MQTT antares(ACCESSKEY);

void setup()
{
	// Serial0 for flash firmware and serial debugging
	Serial.begin(115200);

	// Serial2 for serial communication
	Serial2.begin(115200);

	// Logger init
	ret = logger.init();
	if (ret != logger_ok)
	{
		Serial.printf("Logger init failed : %d\r\n", ret);
	}

	// Antares MQTT init
	antares.setDebug(false);
	antares.wifiConnection(WIFISSID, PASSWORD);
	antares.setMqttServer();
}

void loop()
{
	antares.checkMqttConnection();

	if (Serial2.readBytes(buffbyte, 1))
	{
		pwm = buffbyte[0];
		datasent = false;
	}

	if ((pwm != 0) && ((pwm % 10) == 0) && (datasent == false))
	{
		buff = String(pwm) + "\r\n";
		Serial.print("Recv : " + buff);

		// log data
		ret = logger.appendFile(SD, buff.c_str());
		if (ret != logger_ok)
		{
			Serial.printf("Append file failed : %d\r\n", ret);
		}

		// publish mqtt
		antares.add("pwm", pwm);
		antares.publish(projectName, deviceName);

		datasent = true;
	}
}
