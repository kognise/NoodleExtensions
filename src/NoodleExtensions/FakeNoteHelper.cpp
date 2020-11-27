#include "NoodleExtensions/FakeNoteHelper.h"

#include "GlobalNamespace/NoteController.hpp"

#include "CustomJSONData/CustomBeatmapData.h"

using namespace GlobalNamespace;
using namespace NoodleExtensions;

bool FakeNoteHelper::GetFakeNote(NoteController *noteController) {
    auto customNoteData = (CustomJSONData::CustomNoteData *) noteController->noteData;
    if (!customNoteData->customData) {
        return false;
    }
    rapidjson::Value &customData = *customNoteData->customData->value;
    return customData.HasMember("_fake") && customData.GetBool();
}

bool FakeNoteHelper::GetCuttable(NoteData *noteData) {
    auto customNoteData = (CustomJSONData::CustomNoteData *) noteData;
    if (!customNoteData->customData) {
        return true;
    }
    rapidjson::Value &customData = *customNoteData->customData->value;
    return !customData.HasMember("_interactable") || customData.GetBool();
}