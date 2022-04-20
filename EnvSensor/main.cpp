
#include <httplib.h>
#include <json.hpp>

#include <cstdio>
#include <cstdlib>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <thread>
#include <atomic>

using namespace std::chrono_literals;
using json = nlohmann::json;

std::atomic<float> g_humidity, g_brightness, g_temperature;

void read_data_thread()
{
    // Create I2C bus
    int file;
    const char *bus = "/dev/i2c-1";
    if((file = open(bus, O_RDWR)) < 0)
    {
        printf("Failed to open the bus. \n");
        exit(1);
    }
    // Get I2C device, SI7021 I2C address is 0x40(64)
    ioctl(file, I2C_SLAVE, 0x40);

    while(true)
    {
        // Send humidity measurement command(0xF5)
        char config[1] = {0xF5};
        write(file, config, 1);
        std::this_thread::sleep_for(100ms);

        // Read 2 bytes of humidity data
        // humidity msb, humidity lsb
        char data[2] = {0};
        if(read(file, data, 2) != 2)
        {
            printf("Error : Input/output Error \n");
        }
        else
        {
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
        if(read(file, data, 2) != 2)
        {
            printf("Error : Input/output Error \n");
        }
        else
        {
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

int main(int argc, char **argv) {

    std::thread dataReadThread{read_data_thread};

    httplib::Client cli("http://hexablo:314");

    cli.set_bearer_token_auth("super-secret-token");

    while (true) {

        json j{
                {"humidity",        float(g_humidity)},
                {"temperature",     float(g_temperature)},
                {"brightness",      float(g_brightness)}
        };

        const auto data = j.dump();

        cli.Post("/env",data, "application/json");

        std::this_thread::sleep_for(200ms);
    }

    return 0;
}