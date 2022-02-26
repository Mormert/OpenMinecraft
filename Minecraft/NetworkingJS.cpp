
// JavaScript glue code for the Networking class

#ifdef __EMSCRIPTEN__

#include "Networking.h"

void Networking::Connect(const std::string &uri) {
    // Not implemented
}

void Networking::EmitEvent(const std::string &event, const std::string &data) {
    // Not implemented
}

std::string Networking::GetSessionID() {
    return "not_implemented";
}

#endif // __EMSCRIPTEN__