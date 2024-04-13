#include <raylib.h>

#include "../scenes.h"

static GameSceneId next_scene;

void InitMenu (void) {
    Vector2 size = SceneGetViewSize ();

    SceneSetViewOffset (CLITERAL(Vector2){ .x = 32, .y = 32 });
}

void UpdateMenu (void) {

}

void DrawMenu (void) {
    Vector2 mouse = SceneGetMouse ();

    DrawCircle (0, 0, 32, RED);

    DrawText ("[ MENU ]", (int)mouse.x, (int)mouse.y, 20, WHITE);
}

void DrawMenuGui (void) {

}

void UnloadMenu (void) {

}

GameSceneId FinishMenu (void) {
    return next_scene;
}
