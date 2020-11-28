#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "GlobalNamespace/BeatmapObjectSpawnController.hpp"
#include "GlobalNamespace/BeatmapObjectCallbackController.hpp"
#include "GlobalNamespace/BeatmapObjectManager.hpp"
#include "GlobalNamespace/IAudioTimeSource.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"
#include "GlobalNamespace/IReadonlyBeatmapData.hpp"
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/rapidjson.h"
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/document.h"

#include "CustomJSONData/CustomBeatmapData.h"
#include "NoodleExtensions/NEHooks.h"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace UnityEngine::SceneManagement;

// https://github.com/Aeroluna/Chroma/blob/ebc91c9fa672304ffe5cbf64b31293f56e262159/Chroma/ChromaController.cs#L106
void Start(BeatmapObjectSpawnController* beatmapObjectSpawnController) {
    BeatmapObjectManager* beatmapObjectManager = (BeatmapObjectManager*) beatmapObjectSpawnController->beatmapObjectSpawner; 
    BeatmapObjectCallbackController* coreSetup = beatmapObjectSpawnController->beatmapObjectCallbackController;
    IAudioTimeSource* IAudioTimeSource = coreSetup->audioTimeSource;
    IReadonlyBeatmapData* beatmapData = coreSetup->beatmapData;

    CustomJSONData::CustomBeatmapData* customBeatmap = (CustomJSONData::CustomBeatmapData*) beatmapData;

    if (customBeatmap && customBeatmap->customData) {
        rapidjson::Value &customData = *customBeatmap->customData->value;
        
        if (!customData.HasMember("_environmentRemoval")) return;

        rapidjson::GenericArray<false, rapidjson::Value> environmentRemoval = customData["_environmentRemoval"].GetArray();
        std::vector<std::string> ObjectsToKill;

        for (int i = 0; i < environmentRemoval.Size(); i++) {
            ObjectsToKill[i] = environmentRemoval[i].GetString();
        }
        
        for (std::string objectName : ObjectsToKill) {
            Il2CppString* il2cppObjectName = il2cpp_utils::createcsstr(objectName);
            GameObject* object = GameObject::Find(il2cppObjectName);
            auto realObjectName = (System::String*) object->get_name();
            auto sceneName = (System::String*) object->get_scene().get_name();

            NELogger::GetLogger().debug("Removing " + objectName);

            if (il2cpp_utils::createcsstr(objectName)->Equals(realObjectName)) {
                object->SetActive(false);
            }
        }
    }
}

MAKE_HOOK_OFFSETLESS(BeatmapObjectSpawnControllerStart, void, BeatmapObjectSpawnController* self) {
    BeatmapObjectSpawnControllerStart(self);
    Start(self);
}

void NoodleExtensions::InstallBeatmapObjectSpawnControllerHooks() {
	INSTALL_HOOK_OFFSETLESS(BeatmapObjectSpawnControllerStart, il2cpp_utils::FindMethodUnsafe("", "BeatmapObjectSpawnController", "Start", 0));
}