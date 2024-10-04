//
// Created by Michael Caira on 2024-09-30.
//

#ifndef CHIP8_EMULATOR_CHIP8_H
#define CHIP8_EMULATOR_CHIP8_H

#include <chrono>
#include <cstdint>
#include <random>

const unsigned int KEY_COUNT = 16;
const unsigned int MEMORY_SIZE = 4096;
const unsigned int REGISTER_COUNT = 16;
const unsigned int STACK_LEVELS = 16;
const unsigned int VIDEO_HEIGHT = 32;
const unsigned int VIDEO_WIDTH = 64;


class Chip8 {
public:
    uint8_t keypad[16]{};
    uint32_t video[64 * 32]{};

    Chip8();

    // Loads ROM into memory
    void LoadRom(char const *filename);

    // Performs one pipeline cycle
    void Cycle();

private:
    static const unsigned int START_ADDRESS = 0x200;
    static const unsigned int FONTSET_START_ADDRESS = 0x50;
    static const unsigned int FONTSET_SIZE = 80;

    uint8_t registers[16]{};
    uint8_t memory[4096]{};
    uint16_t index{};
    uint16_t pc{};
    uint16_t stack[16]{};
    uint8_t sp{};
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    uint16_t opcode;
    uint8_t fontset[FONTSET_SIZE] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0,// 0
            0x20, 0x60, 0x20, 0x20, 0x70,// 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0,// 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0,// 3
            0x90, 0x90, 0xF0, 0x10, 0x10,// 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0,// 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0,// 6
            0xF0, 0x10, 0x20, 0x40, 0x40,// 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0,// 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0,// 9
            0xF0, 0x90, 0xF0, 0x90, 0x90,// A
            0xE0, 0x90, 0xE0, 0x90, 0xE0,// B
            0xF0, 0x80, 0x80, 0x80, 0xF0,// C
            0xE0, 0x90, 0x90, 0x90, 0xE0,// D
            0xF0, 0x80, 0xF0, 0x80, 0xF0,// E
            0xF0, 0x80, 0xF0, 0x80, 0x80 // F
    };

    std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randByte;

    typedef void (Chip8::*chip8Func)();
    chip8Func table[0xF + 1];
    chip8Func table0[0xE + 1];
    chip8Func table8[0xE + 1];
    chip8Func tableE[0xE + 1];
    chip8Func tableF[0x65 + 1];

    // Nested function tables
    void Table0();
    void Table8();
    void TableE();
    void TableF();


    // Do nothing
    void OP_NULL();

    // Clear display
    void OP_00E0();

    // Return from a subroutine
    void OP_00EE();

    // Jump to location nnn
    void OP_1nnn();

    // Call subroutine at nnn
    void OP_2nnn();

    // Skip next instruction if Vx == kk
    void OP_3xkk();

    // Skip next instruction if Vx != kk
    void OP_4xkk();

    // Skip next instruction if Vx = Vy
    void OP_5xy0();

    // Set Vx = kk
    void OP_6xkk();

    // Set Vx = vx + kk
    void OP_7xkk();

    // Set Vx = Vy
    void OP_8xy0();

    // Set Vx = Vx OR Vy
    void OP_8xy1();

    // Set Vx = Vx AND Vy
    void OP_8xy2();

    // Set Vx = Vx XOR Vy
    void OP_8xy3();

    /*
     * Set Vx = Vx + Vy, VF = carry
     * Vx will be only the lowest 8 bits if overflow occurs
     */
    void OP_8xy4();

    // Set Vx = Vx - Vy, set VF = NOT borrow
    void OP_8xy5();

    // Set Vx = Vx SHR 1, LSB saved to VF
    void OP_8xy6();

    // Set Vx = Vy - Vx, set VF not borrow
    void OP_8xy7();

    // Set Vx = Vx SHL 1, VF set to 1 if MSB is 1
    void OP_8xyE();

    // Skip next instruction if Vx != Vy
    void OP_9xy0();

    // Set I = nnn
    void OP_Annn();

    // Jump to location nnn + V0
    void OP_Bnnn();

    // Set Vx = random byte AND kk
    void OP_Cxkk();

    /*
     * Display n-byte sprite at memory location I at (Vx, Vy)
     * VF = collision
     */
    void OP_Dxyn();

    // Skip next instruction if key of value Vx is pressed
    void OP_Ex9E();

    // Skip next instruction if key with the value of Vx is not pressed
    void OP_ExA1();

    // Set Vx = delay timer value
    void OP_Fx07();

    // Wait for a key press and then store its value in Vx
    void OP_Fx0A();

    // Set delay timer = Vx
    void OP_Fx15();

    // Set sound timer = Vx
    void OP_Fx18();

    // Set I = I + Vx
    void OP_Fx1E();

    // Set I = location of sprite for digit Vx
    void OP_Fx29();

    // Set I, I + 1, I + 2 to BCD version of Vx
    void OP_Fx33();

    // Store registers V0 -> Vx in memory starting at I
    void OP_Fx55();

    // Read registers V0 -> Vx in memroy starting at I
    void OP_Fx65();
};




#endif//CHIP8_EMULATOR_CHIP8_H
