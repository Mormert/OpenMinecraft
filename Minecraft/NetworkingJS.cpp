
// JavaScript glue code for the Networking class

#ifdef __EMSCRIPTEN__

#include "Networking.h"

#include <emscripten.h>

#include <string>
#include <regex>

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void position_event_js(char *value) {
        const std::string dataString{value};
        Networking::OnPositionEvent(dataString);
    }

    EMSCRIPTEN_KEEPALIVE
    void block_update_event_js(char *value) {
        const std::string dataString{value};
        Networking::OnBlockEvent(dataString);
    }

    EMSCRIPTEN_KEEPALIVE
    void socket_io_connected_js(char *value) {
        const std::string dataString{value};
        Networking::net->id = dataString;
        Networking::connected = true;
    }
}


void Networking::Connect(const std::string &uri) {

    // We need to connect with https
    std::string uri_https = std::regex_replace(uri, std::regex("http"), "https");

    // Note that we set the socket on the window object, such that it will be globally accessible.
    const std::string js_eval_string = "window.socket = io(\"" + uri_https +
                                       "\", {transports: ['websocket']}); console.log(\"Socket connecting...\");";
    emscripten_run_script(js_eval_string.c_str());

    EM_ASM(
        window.socket.on('position', data => {
                stringData = data;
                var ptr = allocate(intArrayFromString(stringData), ALLOC_NORMAL);

                // Pass the string over to C++
                _position_event_js(ptr);

                // Free the data string
                _free(ptr);
        });

        window.socket.on('block_update', data => {
                stringData = data;
                var ptr = allocate(intArrayFromString(stringData), ALLOC_NORMAL);

                // Pass the string over to C++
                _block_update_event_js(ptr);

                // Free the data string
                _free(ptr);
        });

        window.socket.on("connect", () => {
                stringData = window.socket.id;
                var ptr = allocate(intArrayFromString(stringData), ALLOC_NORMAL);

                // Pass the string over to C++
                _socket_io_connected_js(ptr);

                // Free the data string
                _free(ptr);

                console.log("Socket connected!");
        });
    );

}

void Networking::EmitEvent(const std::string &event, const std::string &data) {

    if(!connected)
    {
        return;
    }

    std::string js_eval_string = "window.socket.emit(\"" + event + "\", \"" + data + "\");";

    // We must replace all \n with \\n for it to not fail eval execution in JavaScript.
    js_eval_string = std::regex_replace(js_eval_string, std::regex("\n"), "\\n");

    emscripten_run_script(js_eval_string.c_str());
}

std::string Networking::GetSessionID() {

    if(!connected)
    {
        return "";
    }

    return id;
}

#endif // __EMSCRIPTEN__