//
// Created by Michael Caira on 2024-10-03.
//

#ifndef CHIP8_EMULATOR__PLATFORM_H_
#define CHIP8_EMULATOR__PLATFORM_H_


#include <cstdint>
#include <SDL.h>

class Platform {
public:
    Platform(const char* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
    ~Platform();

    void update(void const* buffer, int pitch);
    bool processInput(uint8_t* keys);


private:
    SDL_Window* window{};
    SDL_Renderer* renderer{};
    SDL_Texture* texture{};
};


#endif//CHIP8_EMULATOR__PLATFORM_H_
