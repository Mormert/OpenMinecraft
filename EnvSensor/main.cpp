
#include <httplib.h>
#include <json.hpp>

#include <thread>

using namespace std::chrono_literals;
using json = nlohmann::json;

int main(int argc, char **argv) {

    httplib::Client cli("http://localhost:314");

    cli.set_bearer_token_auth("super-secret-token");

    while (true) {

        json j{
                {"humidity",   0.35f},
                {"brightness", 0.75f}
        };

        const auto data = j.dump();

        cli.Post("/env",data, "application/json");

        std::this_thread::sleep_for(200ms);
    }

    return 0;
}