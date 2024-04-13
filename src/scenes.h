#ifndef SCENES_H
#define SCENES_H

#define DEFINE_SCENE(name)                                                                                              \
    void Init##name (void);                                                                                             \
    void Update##name (void);                                                                                           \
    void Draw##name (void);                                                                                             \
    void Draw##name##Gui (void);                                                                                        \
    void Unload##name (void);                                                                                           \
    GameSceneId Finish##name (void);

typedef enum GameSceneId {
    SCENE_UNKNOWN = -1,
    SCENE_MENU,
    SCENE_WORLD,

    SCENE_COUNT,
    SCENE_NULL,
} GameSceneId;

extern Camera2D world_camera;

#ifdef __cplusplus
extern "C" {
#endif

DEFINE_SCENE (Menu)
DEFINE_SCENE (World)

// Implimented in scene manager
Vector2 SceneGetViewSize (void);
Vector2 SceneGetMouse (void);
Vector2 SceneGetMouseGui (void);

void SceneSetViewTarget (Vector2 target);
void SceneSetViewOffset (Vector2 offset);

#ifdef __cplusplus
}
#endif

#undef DEFINE_SCENE

#endif // SCENES_H
