#define RAYSUITE_NO_MATH
#define RAYSUITE_NO_GUI
#include <raysuite.h>

#include "../assets/sprite.h"
#include "../scenes.h"

static GameSceneId next_scene;

#define DUNGEON_TILE_SIZE 16
#define DUNGEON_TILES_WIDTH 17
#define DUNGEON_TILES_HEIGHT 8
#define DUNGEON_TILES_COUNT DUNGEON_TILES_WIDTH * DUNGEON_TILES_HEIGHT

static Rectangle __dungeon_bounds;

void InitDungeon (void) {
    next_scene = SCENE_NULL;
    __dungeon_bounds = CLITERAL(Rectangle){ 0, 0, DUNGEON_TILES_WIDTH * DUNGEON_TILE_SIZE, DUNGEON_TILES_HEIGHT * DUNGEON_TILE_SIZE };

    Vector2 scene_view = SceneGetViewSize ();
    SceneSetViewOffset (CLITERAL(Vector2){ scene_view.x / 2, scene_view.y / 2 });
    SceneSetViewTarget (CLITERAL(Vector2){ __dungeon_bounds.width / 2, __dungeon_bounds.height / 2 });
}

void UpdateDungeon (void) {

}

void DrawDungeon (void) {
    DrawSpriteNineSlice ("assets/dungeon_bounds.png", __dungeon_bounds);
    // DrawRectangleLinesEx (__dungeon_bounds, 1.0f, WHITE);
}

void DrawDungeonGui (void) {

}

void UnloadDungeon (void) {

}

GameSceneId FinishDungeon (void) {
    return next_scene;
}
