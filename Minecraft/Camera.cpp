#include "Camera.h"

#include "World.h"

Camera *Camera::mainCamera{nullptr};

Camera::Camera(glm::vec3 position, glm::vec3 up,
               float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                         MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

void Camera::SetMainCamera() {
    mainCamera = this;
}

Camera *Camera::GetMainCamera() {
    return mainCamera;
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    glm::vec3 newPos = Position;

    float velocity = MovementSpeed * deltaTime;
    if (direction == CAMERA_FORWARD)
        newPos += Front * velocity;
    if (direction == CAMERA_BACKWARD)
        newPos -= Front * velocity;
    if (direction == CAMERA_LEFT)
        newPos -= Right * velocity;
    if (direction == CAMERA_RIGHT)
        newPos += Right * velocity;

    if (World::g_world) {

        glm::vec3 moveVector = newPos - Position;

        if(moveVector == glm::zero<glm::vec3>())
        {
            return;
        }

        std::vector<int> blockTypes;
        glm::ivec3 pos;

        if (moveVector.x > 0) {
            pos = GetIntegerWorldPosOffsetted(newPos, glm::vec3{0.5f, 0.5f, 0.5f} + glm::vec3{0.35f, 0.15f, 0.f});
            auto bt = World::g_world->GetBlockAtWorldPosition(pos.x, pos.y, pos.z);
            if (!(bt == 0 || bt == -1)) {
                moveVector.x = 0;
            }
        } else {
            pos = GetIntegerWorldPosOffsetted(newPos, glm::vec3{0.5f, 0.5f, 0.5f} + glm::vec3{-0.35f, 0.15f, 0.f});
            auto bt = World::g_world->GetBlockAtWorldPosition(pos.x, pos.y, pos.z);
            if (!(bt == 0 || bt == -1)) {
                moveVector.x = 0;
            }
        }

        if (moveVector.x > 0) {
            pos = GetIntegerWorldPosOffsetted(newPos, glm::vec3{0.5f, 0.5f, 0.5f} + glm::vec3{0.35f, -1.25f, 0.f});
            auto bt = World::g_world->GetBlockAtWorldPosition(pos.x, pos.y, pos.z);
            if (!(bt == 0 || bt == -1)) {
                moveVector.x = 0;
            }
        } else {
            pos = GetIntegerWorldPosOffsetted(newPos, glm::vec3{0.5f, 0.5f, 0.5f} + glm::vec3{-0.35f, -1.25f, 0.f});
            auto bt = World::g_world->GetBlockAtWorldPosition(pos.x, pos.y, pos.z);
            if (!(bt == 0 || bt == -1)) {
                moveVector.x = 0;
            }
        }

        if (moveVector.y > 0) {
            pos = GetIntegerWorldPosOffsetted(newPos, glm::vec3{0.5f, 0.5f, 0.5f} + glm::vec3{0.f, 0.35f, 0.f});
            auto bt = World::g_world->GetBlockAtWorldPosition(pos.x, pos.y, pos.z);
            if (!(bt == 0 || bt == -1)) {
                moveVector.y = 0;
            }
        } else {
            pos = GetIntegerWorldPosOffsetted(newPos, glm::vec3{0.5f, 0.5f, 0.5f} + glm::vec3{0.f, -1.75f, 0.f});
            auto bt = World::g_world->GetBlockAtWorldPosition(pos.x, pos.y, pos.z);
            if (!(bt == 0 || bt == -1)) {
                moveVector.y = 0;
            }
        }

        if (moveVector.z > 0) {
            pos = GetIntegerWorldPosOffsetted(newPos, glm::vec3{0.5f, 0.5f, 0.5f} + glm::vec3{0.f, 0.15f, 0.35f});
            auto bt = World::g_world->GetBlockAtWorldPosition(pos.x, pos.y, pos.z);
            if (!(bt == 0 || bt == -1)) {
                moveVector.z = 0;
            }
        } else {
            pos = GetIntegerWorldPosOffsetted(newPos, glm::vec3{0.5f, 0.5f, 0.5f} + glm::vec3{0.f, 0.15f, -0.35f});
            auto bt = World::g_world->GetBlockAtWorldPosition(pos.x, pos.y, pos.z);
            if (!(bt == 0 || bt == -1)) {
                moveVector.z = 0;
            }
        }

        if (moveVector.z > 0) {
            pos = GetIntegerWorldPosOffsetted(newPos, glm::vec3{0.5f, 0.5f, 0.5f} + glm::vec3{0.f, -1.25f, 0.35f});
            auto bt = World::g_world->GetBlockAtWorldPosition(pos.x, pos.y, pos.z);
            if (!(bt == 0 || bt == -1)) {
                moveVector.z = 0;
            }
        } else {
            pos = GetIntegerWorldPosOffsetted(newPos, glm::vec3{0.5f, 0.5f, 0.5f} + glm::vec3{0.f, -1.25f, -0.35f});
            auto bt = World::g_world->GetBlockAtWorldPosition(pos.x, pos.y, pos.z);
            if (!(bt == 0 || bt == -1)) {
                moveVector.z = 0;
            }
        }

        Position = Position + moveVector;

    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    Zoom -= (float) yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front,
                                      WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}

glm::ivec3 Camera::GetIntegerWorldPos() {
    auto floatPosition = Camera::GetMainCamera()->Position;
    int intX = floatPosition.x;
    int intY = floatPosition.y;
    int intZ = floatPosition.z;

    if (floatPosition.x < 0.f) {
        intX--;
    }

    if (floatPosition.y < 0.f) {
        intY--;
    }

    if (floatPosition.z < 0.f) {
        intZ--;
    }

    return glm::ivec3{intX, intY, intZ};
}

glm::ivec3 Camera::GetIntegerWorldPosOffsetted(glm::vec3 offset) {
    auto floatPosition = Camera::GetMainCamera()->Position + offset;
    int intX = floatPosition.x;
    int intY = floatPosition.y;
    int intZ = floatPosition.z;

    if (floatPosition.x < 0.f) {
        intX--;
    }

    if (floatPosition.y < 0.f) {
        intY--;
    }

    if (floatPosition.z < 0.f) {
        intZ--;
    }

    return glm::ivec3{intX, intY, intZ};
}

glm::ivec3 Camera::GetIntegerWorldPosOffsetted(glm::vec3 pos, glm::vec3 offset) {
    auto floatPosition = pos + offset;
    int intX = floatPosition.x;
    int intY = floatPosition.y;
    int intZ = floatPosition.z;

    if (floatPosition.x < 0.f) {
        intX--;
    }

    if (floatPosition.y < 0.f) {
        intY--;
    }

    if (floatPosition.z < 0.f) {
        intZ--;
    }

    return glm::ivec3{intX, intY, intZ};
}

