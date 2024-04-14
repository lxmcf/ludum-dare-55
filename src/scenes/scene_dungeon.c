#define RAYSUITE_NO_GUI
#include <raysuite.h>

#include "../assets/sprite.h"
#include "../scenes.h"

#define PLAYER_SPEED 100.0f
typedef struct Player {
    Vector2 position;

    int max_cards;
    int current_card;

    int life;
    int max_life;
} Player;

static GameSceneId next_scene;

#define DUNGEON_TILE_SIZE 16
#define DUNGEON_TILES_WIDTH 16
#define DUNGEON_TILES_HEIGHT 8

static Rectangle __dungeon_bounds;
static Player player;

struct DungeonState {
    bool dungeon_complete;
} dungeon_state;

static void __ResetPlayerPosition (void) {
    player.position = CLITERAL(Vector2){ __dungeon_bounds.width / 2, __dungeon_bounds.height - (DUNGEON_TILE_SIZE / 4) };
}

void InitDungeon (void) {
    next_scene = SCENE_NULL;
    __dungeon_bounds = CLITERAL(Rectangle){ 0, 0, DUNGEON_TILES_WIDTH * DUNGEON_TILE_SIZE, DUNGEON_TILES_HEIGHT * DUNGEON_TILE_SIZE };

    Vector2 scene_view = SceneGetViewSize ();
    SceneSetViewOffset (CLITERAL(Vector2){ scene_view.x / 2, scene_view.y / 2 });
    SceneSetViewTarget (CLITERAL(Vector2){ __dungeon_bounds.width / 2, __dungeon_bounds.height / 2 });

    // Ensure texture's have correct data that need it
    LoadSprite ("assets/player.png", CLITERAL(Vector2){ 8, 16 }, WHITE);
    LoadSprite ("assets/dungeon_door_closed.png", CLITERAL(Vector2){ 8, 16 }, WHITE);
    LoadSprite ("assets/dungeon_door_open.png", CLITERAL(Vector2){ 8, 16 }, WHITE);
    LoadSprite ("assets/pointer_arrow.png", CLITERAL(Vector2){ 8, 0 }, WHITE);

    player = CLITERAL(Player) {
        .position = Vector2Zero (),
        .life = 3,
        .max_life = 6,

        .max_cards = 4,
        .current_card = 0,
    };

    __ResetPlayerPosition ();
}

void UpdateDungeon (void) {
    #ifdef BUILD_DEBUG
    {   // Debug Stuff
        if (IsKeyReleased (KEY_SPACE)) dungeon_state.dungeon_complete = !dungeon_state.dungeon_complete;
    }
    #endif

    {   // MISC

    }

    {   // Update Player
        int xaxis = IsKeyDown (KEY_D) - IsKeyDown (KEY_A);
        int yaxis = IsKeyDown (KEY_S) - IsKeyDown (KEY_W);

        Vector2 velocity = Vector2Normalize (CLITERAL(Vector2){ xaxis, yaxis });
        velocity = CLITERAL(Vector2){ velocity.x * (PLAYER_SPEED * GetFrameTime ()), velocity.y * (PLAYER_SPEED * GetFrameTime ()) };

        player.position = Vector2Add (player.position, velocity);

        // Confine Player
        #define PADDING_X 8
        #define PADDING_Y 16
        if (player.position.x < PADDING_X) player.position.x = PADDING_X;
        if (player.position.y < PADDING_Y) player.position.y = PADDING_Y;

        if (player.position.x > __dungeon_bounds.width - PADDING_X) player.position.x = __dungeon_bounds.width - PADDING_X;
        if (player.position.y > __dungeon_bounds.height) player.position.y = __dungeon_bounds.height;

        #undef PADDING_X
        #undef PADDING_Y
    }

    {   // Card Selection
        int xaxis = IsKeyPressed (KEY_RIGHT) - IsKeyPressed (KEY_LEFT);

        player.current_card += xaxis;

        if (player.current_card < 0) player.current_card = player.max_cards - 1;
        if (player.current_card > player.max_cards - 1) player.current_card = 0;
    }
}

void DrawDungeon (void) {
    DrawSpriteNineSlice ("assets/dungeon_bounds.png", __dungeon_bounds);

    if (dungeon_state.dungeon_complete) {
        DrawSprite ("assets/dungeon_door_open.png", CLITERAL(Vector2){ __dungeon_bounds.width / 2 , 0 });

        // Exit Arrow
        DrawSprite ("assets/pointer_arrow.png", CLITERAL(Vector2){ __dungeon_bounds.width / 2, SINE (GetTime () * 8) * 4 });
    } else {
        DrawSprite ("assets/dungeon_door_closed.png", CLITERAL(Vector2){ __dungeon_bounds.width / 2 , 0 });
    }

    DrawSprite ("assets/player.png", player.position);
}

void DrawDungeonGui (void) {
    Vector2 scene_view = SceneGetViewSize ();

    #define UI_PADDING 2

    for (int i = 0; i < player.max_life; i++) {
        Vector2 position = CLITERAL(Vector2) {
            .x = UI_PADDING + i * (16 + UI_PADDING),
            .y = UI_PADDING
        };

        if (i > player.life - 1) {
            DrawSprite ("assets/heart_empty.png", position);
            continue;
        }

        DrawSprite ("assets/heart.png", position);
    }

    Rectangle card_bounds = SpriteGetBounds ("assets/card.png");
    for (int i = 0; i < player.max_cards; i++) {
        int offset = 16;

        if (player.current_card == i) offset = 32;

        Vector2 position = CLITERAL(Vector2) {
            .x = 8 + i * (card_bounds.width + (UI_PADDING * 2)),
            .y = scene_view.y - offset,
        };

        DrawSprite ("assets/card.png", position);
    }
}

void UnloadDungeon (void) { }

GameSceneId FinishDungeon (void) {
    return next_scene;
}
