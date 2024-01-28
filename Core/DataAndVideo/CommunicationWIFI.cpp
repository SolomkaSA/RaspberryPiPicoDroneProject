#include "../Common/Constants.cpp"
#include "../Common/Models/StructuresForRC.cpp"
#include "pico/stdlib.h" // printf(), sleep_ms(), getchar_timeout_us(), to_us_since_boot(), get_absolute_time()
#include "pico/bootrom.h"
#include "hardware/spi.h"
#include "../RF24/RF24.h"
SPI my_spi;

class CommunicationWIFI
{
public:
    RF24 radio = RF24(NRF24_CE_GPIO, NRF24_CSN_GPIO); // ce = 9, csn= 14 for Pico W PRODUCTION 10000000
    struct payload payload;
    // Used to control whether this node is sending or receiving
    bool role = false; // true = TX role, false = RX role

    // For this example, we'll be using a payload containing
    // a single float number that will be incremented
    // on every successful transmission

    char *messages;
    void Message(char *msg)
    {
        // nRF.be
    }
    bool setup()
    {
        // Let these addresses be used for the pair
        uint8_t address[][6] = {"1Node", "2Node"};
        // It is very helpful to think of an address as a path instead of as
        // an identifying device destination
        // to use different addresses on a pair of radios, we need a variable to
        // uniquely identify which address this radio will use to transmit
        bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit
        my_spi.begin(spi1);

        // initialize the transceiver on the SPI bus
        if (!radio.begin(&my_spi))
        {
            printf("radio hardware is not responding!!\n");
            sleep_ms(1000);
            return false;
        }

        // To set the radioNumber via the Serial terminal on startup
        printf("Which radio is this? Enter '0' or '1'. Defaults to '0'\n");
        char input = getchar();
        radioNumber = input == 49;
        printf("radioNumber = %d\n", (int)radioNumber);

        // Set the PA Level low to try preventing power supply related problems
        // because these examples are likely run with nodes in close proximity to
        // each other.
        // Greater level = more consumption = longer distance
        radio.setPALevel(RF24_PA_MIN);   // RF24_PA_MAX is default. (RF24_PA_MIN|RF24_PA_LOW|RF24_PA_HIGH|RF24_PA_MAX)
        radio.setDataRate(RF24_250KBPS); // (RF24_250KBPS|RF24_1MBPS|RF24_2MBPS)
        radio.setChannel(111);
        // save on transmission time by setting the radio to only transmit the
        // number of bytes we need to transmit a float
        radio.setPayloadSize(sizeof(payload)); // float datatype occupies 4 bytes

        // set the TX address of the RX node into the TX pipe
        radio.openWritingPipe(address[radioNumber]); // always uses pipe 0

        // set the RX address of the TX node into a RX pipe
        radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1

        // additional setup specific to the node's role
        if (role)
        {
            radio.stopListening(); // put radio in TX mode
        }
        else
        {
            radio.startListening(); // put radio in RX mode
        }

        // For debugging info
        // radio.printDetails();       // (smaller) function that prints raw register values
        // radio.printPrettyDetails(); // (larger) function that prints human readable data

        // role variable is hardcoded to RX behavior, inform the user of this
        printf("*** PRESS 'T' to begin transmitting to the other node\n");

        return true;
    } // setup

    void loop()
    {
        if (role)
        {
            TransceiverMood();
        }
        else
        {
            ReceivingMood();
        }
    } // loop

    // This device is a TX node
    void TransceiverMood()
    {
        uint64_t start_timer = to_us_since_boot(get_absolute_time()); // start the timer
        bool report = radio.write(&payload, sizeof(payload));         // transmit & save the report
        uint64_t end_timer = to_us_since_boot(get_absolute_time());   // end the timer

        if (report)
        {
            // payload was delivered; print the payload sent & the timer result
            printf("Transmission successful! Time to transmit = %llu us. Sent: %f\n", end_timer - start_timer, messages);

            // increment float payload
            payload.LeftJoystickX += 1;
            payload.LeftJoystickY += 2;
            payload.RightJoystickX += 3;
            payload.RightJoystickY -= 4;
        }
        else
        {
            // payload was not delivered
            printf("Transmission failed or timed out\n");
        }
        // to make this example readable in the serial terminal
        // sleep_ms(1000); // slow transmissions down by 1 second
    }

    // This device is a RX node
    void ReceivingMood()
    {
        uint8_t pipe;
        if (radio.available(&pipe))
        {                                           // is there a payload? get the pipe number that recieved it
            uint8_t bytes = radio.getPayloadSize(); // get the size of the payload
                                                    // radio.read(&payload, bytes);            // fetch payload from FIFO
            radio.read(&payload, bytes);
            // print the size of the payload, the pipe number, payload's value
            printf("Received %d bytes on pipe %d: %c %f\n", bytes, pipe, payload.LeftJoystickX, payload.RightJoystickY);
        }
    }
    void ChangeRole()
    {
        // role
        char str[] = {NULL};
        get_block(str);
        char input = str[0];
        char c1 = str[2];
        char c2 = str[3];
        char c3 = str[4];
        if (input != PICO_ERROR_TIMEOUT)
        {
            // change the role via the serial terminal

            if ((input == 'T' || input == 't') && !role)
            {
                // Become the TX node

                role = true;
                printf("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK\n");
                radio.stopListening();
            }
            else if ((input == 'R' || input == 'r') && role)
            {
                // Become the RX node

                role = false;
                printf("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK\n");
                radio.startListening();
            }
            else if (input == 'b' || input == 'B')
            {
                // reset to bootloader
                radio.powerDown();
                printf("*** powerDown\n");
                // reset_usb_boot(0, 0);
            }
            else if (input == 'u' || input == 'U')
            {
                radio.powerUp();
                printf("*** powerUp\n");
                // reset_usb_boot(0, 0);
            }
            else if (input == 'c')
            {
                char ch[] = {NULL};
                ch[0] = str[2];
                ch[1] = str[3];
                ch[3] = str[4];
                int channel = charArrayToInt(ch);
                radio.setChannel(channel);
                radio.powerDown();
                printf("*** powerDown\n");
                printf("Changed channel:%i %i %i %i %i %i %i %i", channel, radio.getChannel(), str[2], str[3], str[4], c1, c2, c3);
                radio.powerUp();
                printf("*** powerUp\n");
            }
        }
    }
    uint16_t get_block(char *buffer)
    {
        uint16_t buffer_index = 0;
        while (true)
        {
            char c = getchar_timeout_us(0);
            if (c != PICO_ERROR_TIMEOUT && buffer_index < BUFFER_LENGTH)
            {
                buffer[buffer_index++] = c;
            }
            else
            {
                break;
            }
        }
        return buffer_index;
    }
    int charArrayToInt(char *arr)
    {
        int i, value, r, flag;

        flag = 1;
        i = value = 0;

        for (i = 0; i < strlen(arr); ++i)
        {

            // if arr contain negative number
            if (i == 0 && arr[i] == '-')
            {
                flag = -1;
                continue;
            }

            r = arr[i] - '0';
            value = value * 10 + r;
        }

        value = value * flag;

        return value;
    }
    int main()
    {
        while (!setup())
        { // if radio.begin() failed
          // hold program in infinite attempts to initialize radio
        }
        {
            loop();
            return 0; // we will never reach this
        }
    }
};

// instantiate an object for the nRF24L01 transceiver
// RF24 radio(17, 14);

// // Channel info
// const uint8_t num_channels = 126;
// uint8_t values[num_channels];

// const int num_reps = 100;
// int reset_array = 0;

// int main2()
// {
//     // wait here until the CDC ACM (serial port emulation) is connected
//     while (!tud_cdc_connected())
//     {
//         sleep_ms(10);
//     }

//     // initialize the transceiver on the SPI bus
//     while (!radio.begin())
//     {
//         printf("radio hardware is not responding!!\n");
//     }

//     // print example's name
//     printf("RF24/examples_pico/scanner\n");

//     radio.setAutoAck(false);

//     // Get into standby mode
//     radio.startListening();
//     radio.stopListening();

//     // radio.printDetails();

//     // Print out header, high then low digit
//     int i = 0;

//     while (i < num_channels)
//     {
//         printf("%x", i >> 4);
//         ++i;
//     }
//     printf("\n");

//     i = 0;
//     while (i < num_channels)
//     {
//         printf("%x", i & 0xf);
//         ++i;
//     }
//     printf("\n");

//     // forever loop
//     while (1)
//     {
//         // Clear measurement values
//         memset(values, 0, sizeof(values));

//         // Scan all channels num_reps times
//         int rep_counter = num_reps;
//         while (rep_counter--)
//         {

//             int i = num_channels;
//             while (i--)
//             {

//                 // Select this channel
//                 radio.setChannel(i);

//                 // Listen for a little
//                 radio.startListening();
//                 sleep_us(128);
//                 radio.stopListening();

//                 // Did we get a carrier?
//                 if (radio.testCarrier())
//                 {
//                     ++values[i];
//                 }
//             }
//         }

//         // Print out channel measurements, clamped to a single hex digit
//         i = 0;
//         while (i < num_channels)
//         {
//             if (values[i])
//                 printf("%x", rf24_min(0xf, (values[i] & 0xf)));
//             else
//                 printf("-");

//             ++i;
//         }
//         printf("\n");
//     }

//     return 0;
// }