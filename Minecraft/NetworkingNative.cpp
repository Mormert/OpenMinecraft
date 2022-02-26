
// Native code for the Networking class

#ifndef __EMSCRIPTEN__

#include "Networking.h"

void Networking::Connect(const std::string &uri) {
    c.set_logs_quiet();

    c.connect(uri);

    c.socket()->on("position", sio::socket::event_listener_aux(
            [&](std::string const &name, sio::message::ptr const &data, bool isAck, sio::message::list &ack_resp) {
                OnPositionEvent(data->get_string());
            }));

    c.socket()->on("block_update", sio::socket::event_listener_aux(
            [&](std::string const &name, sio::message::ptr const &data, bool isAck, sio::message::list &ack_resp) {
                OnBlockEvent(data->get_string());
            }));

    connected = true;
}

void Networking::EmitEvent(const std::string &event, const std::string &data) {
    c.socket()->emit(event, data);
}

std::string Networking::GetSessionID() {
    return c.get_sessionid();
}

#endif // __EMSCRIPTEN__