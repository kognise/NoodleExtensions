#include "NoodleExtensions/NEHooks.h"

using namespace NoodleExtensions;

void NoodleExtensions::InstallHooks() {
    InstallBeatmapObjectSpawnMovementDataHooks();
    InstallBeatmapDataTransformHelperHooks();
    InstallSpawnRotationProcessorHooks();
    InstallGameplayCoreInstallerHooks();
    InstallObstacleControllerHooks();
    
    // Fake notes
    InstallGameNoteControllerHooks();
    InstallBombNoteControllerHooks();
    InstallBeatmapObjectSpawnControllerHooks();
}