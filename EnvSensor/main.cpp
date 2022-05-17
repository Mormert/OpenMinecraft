
#include <httplib.h>
#include <json.hpp>

#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <time.h>
#include <fcntl.h>

#include "DEV_Config.h"
#include "TSL2591.h"

#include <thread>
#include <atomic>
#include <string>
#include <vector>

using namespace std::chrono_literals;
using json = nlohmann::json;

std::atomic<float> g_humidity, g_brightness, g_temperature;

void read_data_thread_humidity_temp() {
    // Create I2C bus
    int file;
    const char *bus = "/dev/i2c-1";
    if ((file = open(bus, O_RDWR)) < 0) {
        printf("Failed to open the bus. \n");
        exit(1);
    }
    // Get I2C device, SI7021 I2C address is 0x40(64)
    ioctl(file, I2C_SLAVE, 0x40);

    while (true) {
        // Send humidity measurement command(0xF5)
        char config[1] = {0xF5};
        write(file, config, 1);
        std::this_thread::sleep_for(100ms);

        // Read 2 bytes of humidity data
        // humidity msb, humidity lsb
        char data[2] = {0};
        if (read(file, data, 2) != 2) {
            printf("Error : Input/output Error \n");
        } else {
            // Convert the data
            float humidity = (((data[0] * 256 + data[1]) * 125.0) / 65536.0) - 6;
            g_humidity = humidity;

            // Output data to screen
            printf("Relative Humidity : %.2f RH \n", humidity);
        }

        // Send temperature measurement command(0xF3)
        config[0] = 0xF3;
        write(file, config, 1);
        std::this_thread::sleep_for(100ms);

        // Read 2 bytes of temperature data
        // temp msb, temp lsb
        if (read(file, data, 2) != 2) {
            printf("Error : Input/output Error \n");
        } else {
            // Convert the data
            float cTemp = (((data[0] * 256 + data[1]) * 175.72) / 65536.0) - 46.85;
            float fTemp = cTemp * 1.8 + 32;

            g_temperature = cTemp;

            // Output data to screen
            printf("Temperature in Celsius : %.2f C \n", cTemp);
            printf("Temperature in Fahrenheit : %.2f F \n", fTemp);
        }

        std::this_thread::sleep_for(100ms);
    }

}

void read_data_thread_brightness() {

    DEV_ModuleInit();

    TSL2591_Init();
    // TSL2591_SET_InterruptThreshold(0xff00, 0x0010);
    while (1) {

        int readLux = TSL2591_Read_Lux();

        g_brightness = readLux;

        //printf("Lux = %d\r\n", readLux);
        TSL2591_SET_LuxInterrupt(50, 200);
        //printf("Infrared light: %d\r\n", TSL2591_Read_Infrared());
        //printf("Visible light: %d\r\n", TSL2591_Read_Visible());
        //printf("Full spectrum (IR + visible) light: %d\r\n\r\n", TSL2591_Read_FullSpectrum());


    }
    // System Exit
    DEV_ModuleExit();
}

void ExceptionHandler(int signo) {
    //System Exit
    printf("\r\nCTRL + C Exit...\r\n");
    DEV_ModuleExit();

    exit(0);
}

int main(int argc, char **argv) {

    std::vector<std::string> arguments;
    for (int i = 1; i < argc; i++) {
        arguments.push_back(argv[i]);
    }

    if(arguments.size() != 2)
    {
        std::printf("ERROR: Please Specify: API-URL API-KEY");
        std::exit(EXIT_FAILURE);
    }

    // Exception handling: 'Ctrl + C'
    signal(SIGINT, ExceptionHandler);

    std::thread dataReadThread_humid_temp{read_data_thread_humidity_temp};
    std::thread dataReadThread_brightness{read_data_thread_brightness};

    httplib::Client cli(arguments.at(0).c_str());

    cli.set_bearer_token_auth(arguments.at(1).c_str());

    std::this_thread::sleep_for(3000ms);

    while (true) {

        json j{
                {"humidity",    float(g_humidity)},
                {"temperature", float(g_temperature)},
                {"brightness",  float(g_brightness)}
        };

        const auto data = j.dump();
        std::cout << data << '\n';

        cli.Post("/env", data, "application/json");

        std::this_thread::sleep_for(1000ms);
    }

    return 0;
}