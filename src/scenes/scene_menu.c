#include <raylib.h>
#include <raymath.h>

#include "../scenes.h"

static GameSceneId next_scene;

static Vector2 position;

void InitMenu (void) {
    Vector2 size = SceneGetViewSize ();

    SceneSetViewOffset (CLITERAL(Vector2){ .x = size.x / 2, .y = size.y / 2 });

    position = Vector2Zero ();
}

void UpdateMenu (void) {
    #define SPEED 200.0f
    int xaxis = IsKeyDown (KEY_RIGHT) - IsKeyDown (KEY_LEFT);
    int yaxis = IsKeyDown (KEY_DOWN) - IsKeyDown (KEY_UP);

    Vector2 velocity = CLITERAL(Vector2) {
        .x = (xaxis * SPEED) * GetFrameTime (),
        .y = (yaxis * SPEED) * GetFrameTime (),
    };

    position = Vector2Add (position, velocity);

    SceneSetViewTarget (position);
}

void DrawMenu (void) {
    Vector2 mouse = SceneGetMouse ();

    DrawCircle (0, 0, 32, RED);

    // DrawText ("[ MENU ]", (int)mouse.x, (int)mouse.y, 20, WHITE);

    DrawCircleV (mouse, 8.0f, GREEN);
}

void DrawMenuGui (void) {
    DrawCircleV (Vector2Zero (), 8.0f, BLUE);
}

void UnloadMenu (void) {

}

GameSceneId FinishMenu (void) {
    return next_scene;
}
