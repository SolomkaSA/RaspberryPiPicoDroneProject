#include <stdio.h>
#include "pico/stdlib.h"
#include "sd_card.h"
#include "ff.h"

class SDCard
{
    FRESULT fr;
    FATFS fs;
    FIL fil;

public:
    void WriteIntoFile(char filename[], char text[])
    {
        int ret;
        // Initialize SD card
        if (!sd_init_driver())
        {
            printf("ERROR: Could not initialize SD card\r\n");
            while (true)
                ;
        }

        // Mount drive
        fr = f_mount(&fs, "0:", 1);
        if (fr != FR_OK)
        {
            printf("ERROR: Could not mount filesystem (%d)\r\n", fr);
            while (true)
                ;
        }

        // Open file for writing ()
        fr = f_open(&fil, filename, FA_WRITE | FA_CREATE_ALWAYS);
        if (fr != FR_OK)
        {
            printf("ERROR: Could not open file (%d)\r\n", fr);
            while (true)
                ;
        }

        // Write something to file
        ret = f_printf(&fil, text);
        if (ret < 0)
        {
            printf("ERROR: Could not write to file (%d)\r\n", ret);
            f_close(&fil);
            while (true)
                ;
        }
        ret = f_printf(&fil, "of writing to an SD card.\r\n");
        if (ret < 0)
        {
            printf("ERROR: Could not write to file (%d)\r\n", ret);
            f_close(&fil);
            while (true)
                ;
        }

        // Close file
        fr = f_close(&fil);
        if (fr != FR_OK)
        {
            printf("ERROR: Could not close file (%d)\r\n", fr);
            while (true)
                ;
        }
    }

    void ReadFile(char filename[])
    {
        char buf[100];
        // Open file for reading
        fr = f_open(&fil, filename, FA_READ);
        if (fr != FR_OK)
        {
            printf("ERROR: Could not open file (%d)\r\n", fr);
            while (true)
                ;
        }

        // Print every line in file over serial
        printf("Reading from file '%s':\r\n", filename);
        printf("---\r\n");
        while (f_gets(buf, sizeof(buf), &fil))
        {
            printf(buf);
        }
        printf("\r\n---\r\n");

        // Close file
        fr = f_close(&fil);
        if (fr != FR_OK)
        {
            printf("ERROR: Could not close file (%d)\r\n", fr);
            while (true)
                ;
        }
    }

    void UnmountSDCard()
    {
        // Unmount drive
        f_unmount("0:");
    }
};