/**
 * @file logger.cpp
 * @author Elvandry Ghiffary (elvandry13@gmail.com)
 * @brief Logger definition file
 * @version 0.1
 * @date 2021-07-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "logger.h"

#define SD_CS 5

LoggingClass::LoggingClass(String path)
{
    _path = path;
}

int LoggingClass::init()
{
    SD.begin(SD_CS);
    if (!SD.begin(SD_CS))
    {
        return logger_card_mount_failed;
    }

    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE)
    {
        return logger_no_sd_card;
    }

    if (!SD.begin(SD_CS))
    {
        return logger_init_failed;
    }

    // If the data.txt file doesn't exist
    // Create a file on the SD card and write the data labels
    File file = SD.open(_path);
    if (!file)
    {
        writeFile(SD, "pwm\r\n");
    }
    file.close();

    return logger_ok;
}

int LoggingClass::writeFile(fs::FS &fs, const char *message)
{
    File file = fs.open(_path, FILE_WRITE);
    if (!file)
    {
        return logger_open_file_failed;
    }

    if (!file.print(message))
    {
        return logger_write_file_failed;
    }

    file.close();

    return logger_ok;
}

int LoggingClass::appendFile(fs::FS &fs, const char *message)
{
    File file = fs.open(_path, FILE_APPEND);
    if (!file)
    {
        return logger_open_file_failed;
    }
    if (!file.print(message))
    {
        return logger_append_file_failed;
    }
    
    file.close();

    return logger_ok;
}

int LoggingClass::removeFile(fs::FS &fs)
{
	const char *path = _path.c_str();
    if (!fs.remove(path))
	{
        return logger_delete_file_failed;
	}
	
    return logger_ok;
}

String LoggingClass::readFile(fs::FS &fs)
{
	File file = fs.open(_path, "r");
    if (!file || file.isDirectory())
    {
        return String();
    }

    String fileContent;
    while (file.available())
    {
        fileContent += String((char)file.read());
    }
    return fileContent;
}
