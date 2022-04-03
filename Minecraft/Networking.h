#ifndef OPENMINECRAFT_NETWORKING_H
#define OPENMINECRAFT_NETWORKING_H

#ifndef __EMSCRIPTEN__
#include <sio_client.h>
#endif

#include "glm/vec3.hpp"

#include <string>
#include <array>

class Networking {

public:

    Networking() { net = this; }

    // Has native and JS implementation
    void Connect(const std::string &uri);

    void EmitPlayerPosition(glm::vec3 position, float rotation = 0.f, float headRotation = 0.f);

    void EmitUpdateBlock(int x, int y, int z, int block_id);

    static inline Networking *net;

    static inline bool connected = false;

    // Called from JS or Native C++
    static void OnPositionEvent(const std::string& data);
    static void OnBlockEvent(const std::string& data);
    static void OnPlayerDisconnectEvent(const std::string& data);
    static void OnEnvironmentSettingUpdateEvent(const std::string& data);

#ifdef __EMSCRIPTEN__
    std::string id;
#endif

private:

    // Has native and JS implementation
    void EmitEvent(const std::string &event, const std::string &data);

    // Has native and JS implementation
    std::string GetSessionID();

#ifndef __EMSCRIPTEN__
    sio::client c;
#endif
};


#endif //OPENMINECRAFT_NETWORKING_H
