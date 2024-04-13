#include <raylib.h>

#include "../scenes.h"

static GameSceneId next_scene;

void InitWorld (void) {
    next_scene = SCENE_NULL;
}

void UpdateWorld (void) {

}

void DrawWorld (void) {
    DrawText ("World Scene", 8, 128, 40, WHITE);
}

void DrawWorldGui (void) {

}

void UnloadWorld (void) {

}

GameSceneId FinishWorld (void) {
    return next_scene;
}
