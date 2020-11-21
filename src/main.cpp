#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/stringbuffer.h"
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/prettywriter.h"
#include "custom-types/shared/logging.hpp"

#include "NoodleExtensions/NEHooks.h"
#include "CustomJSONData/CustomJSONDataHooks.h"
#include "NELogger.h"

#include <string>
#include <iostream>

void PrintJSONValue(const rapidjson::Value &json) {
    using namespace rapidjson;
        
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    json.Accept(writer);
    auto str = sb.GetString();
    NELogger::GetLogger().info("%s", str);
}

extern "C" void setup(ModInfo &info) {
    info.id = "NoodleExtensions";
    info.version = "0.1.0";
    NELogger::modInfo = info;
}

extern "C" void load() {
    NELogger::GetLogger().info("Installing NoodleExtensions Hooks!");

    // This prevents any and all Utils logging
    Logger::get().options.silent = true;

    // Install hooks

    CustomJSONData::InstallHooks();
    NoodleExtensions::InstallHooks();

    NELogger::GetLogger().info("Installed NoodleExtensions Hooks!");
}