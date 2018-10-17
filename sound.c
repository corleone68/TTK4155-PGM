#include <stdint.h>
#include "sound.h"

/**
 * The sound data have been packed into binary files in the sounds folder. Every two
 * bytes are an unsigned 16-bit integer stored in little endian.
 *
 * The binary file is linked into read only memory by the linker, as declared in the
 * Makefile. The start, end, and size of each data section is stored in the symbol
 * table, they are therefore accessable and can be declared with the extern keyword.
 * */

extern int _binary_sounds_enemy_destroyed_binary_end;
extern int _binary_sounds_enemy_destroyed_binary_size;
extern int _binary_sounds_enemy_destroyed_binary_start;
extern int _binary_sounds_game_over_binary_end;
extern int _binary_sounds_game_over_binary_size;
extern int _binary_sounds_game_over_binary_start;
extern int _binary_sounds_jump_binary_end;
extern int _binary_sounds_jump_binary_size;
extern int _binary_sounds_jump_binary_start;
extern int _binary_sounds_zap_binary_end;
extern int _binary_sounds_zap_binary_size;
extern int _binary_sounds_zap_binary_start;


Sound silent = {.length=0};
Sound jump;
Sound zap;
Sound gameOver;
Sound enemyDestroyed;


Sound* getSound(int soundId) {
    if (soundId == 1) return &zap;
    if (soundId == 2) return &gameOver;
    if (soundId == 3) return &enemyDestroyed;

    return &silent;
}

void initializeSounds() {
    uint32_t jump_start = (uint32_t)&_binary_sounds_jump_binary_start;
    uint32_t jump_size = (uint32_t)&_binary_sounds_jump_binary_size;
    jump.data = (uint16_t *)jump_start;
    jump.length = jump_size / 2;

    uint32_t zap_start = (uint32_t)&_binary_sounds_zap_binary_start;
    uint32_t zap_size = (uint32_t)&_binary_sounds_zap_binary_size;
    zap.data = (uint16_t *)zap_start;
    zap.length = zap_size / 2;

    uint32_t game_over_start = (uint32_t)&_binary_sounds_game_over_binary_start;
    uint32_t game_over_size = (uint32_t)&_binary_sounds_game_over_binary_size;
    gameOver.data = (uint16_t *)game_over_start;
    gameOver.length = game_over_size / 2;

    uint32_t enemy_destroyed_start = (uint32_t)&_binary_sounds_enemy_destroyed_binary_start;
    uint32_t enemy_destroyed_size = (uint32_t)&_binary_sounds_enemy_destroyed_binary_size;
    enemyDestroyed.data = (uint16_t *)enemy_destroyed_start;
    enemyDestroyed.length = enemy_destroyed_size / 2;
}
