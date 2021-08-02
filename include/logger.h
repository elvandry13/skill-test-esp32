/**
 * @file logger.h
 * @author Elvandry Ghiffary (elvandry13@gmail.com)
 * @brief Logger declaration file
 * @version 0.1
 * @date 2021-07-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "FS.h"
#include "SD.h"
#include <SPI.h>

class LoggingClass
{
    public:
        /**
         * @brief Construct a new Logging Class object
         * 
         * @param path 
         */
        LoggingClass(String path);

        /**
         * @brief Init logging class object
         * 
         * @return int 
         */
        int init();

        /**
         * @brief Write something to file
         * 
         * @param fs 
         * @param message Some messages
         * @return int 
         */
        int writeFile(fs::FS &fs, const char *message);

        /**
         * @brief Append something to file
         * 
         * @param fs 
         * @param message Some messages
         * @return int 
         */
        int appendFile(fs::FS &fs, const char *message);

        /**
         * @brief Remove file
         * 
         * @param fs 
         * @return int 
         */
        int removeFile(fs::FS &fs);

        /**
         * @brief Read content of file
         * 
         * @param fs 
         * @return String 
         */
        String readFile(fs::FS &fs);
    
    private:
        String _path;
};

typedef enum
{
    logger_ok = 0,
    logger_card_mount_failed = 1,
    logger_no_sd_card = 2,
    logger_init_failed = 3,
    logger_open_file_failed = 4,
    logger_write_file_failed = 5,
    logger_append_file_failed = 6,
    logger_delete_file_failed = 7,
} logger_error;
