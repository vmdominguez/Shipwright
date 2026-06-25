// Simple utility to load a display-list asset from an OTR/O2R/folder archive
// and print the raw F3D instructions in a human-readable form.

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <typeinfo>

#include <ship/Context.h>
#include <ship/resource/ResourceManager.h>
#include <ship/resource/archive/ArchiveManager.h>
#include <ship/resource/File.h>
#include <libultraship/libultra/gbi.h>
#include <fast/interpreter.h>
#include <fast/resource/ResourceType.h>
#include <fast/resource/factory/DisplayListFactory.h>
#include <fast/resource/type/DisplayList.h>

#include "FakeWindow.cxx"
#include "FakeWindowBackend.cxx"
#include "Extractor.cxx"
#include "CommandMap.cxx"

namespace Fast {
    void GfxSetInstance(std::shared_ptr<Interpreter> gfx);
}

void loadResourceFactories(std::shared_ptr<Ship::ResourceLoader> loader) {
    loader->RegisterResourceFactory(std::make_shared<Fast::ResourceFactoryBinaryDisplayListV0>(),
                                    RESOURCE_FORMAT_BINARY, "DisplayList",
                                    static_cast<uint32_t>(Fast::ResourceType::DisplayList), 0);
    loader->RegisterResourceFactory(std::make_shared<Fast::ResourceFactoryXMLDisplayListV0>(), RESOURCE_FORMAT_XML,
                                    "DisplayList", static_cast<uint32_t>(Fast::ResourceType::DisplayList), 0);
}

// Program entrypoint. Usage: vinny <path-to-otr/o2r/or-directory>
// The tool mounts the supplied path as an archive using libultraship's
// ArchiveManager, looks up the known bomb display-list key
// "__OTR__objects/object_gi_bomb_1/gGiBombDL", and dumps each 8-byte
// F3D instruction as: index, opcode, friendly name, and raw operands.
int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path-to-otr/o2r/dir>" << std::endl;
        return 2;
    }

    // Path to the archive or folder supplied by the user
    std::string archivePath = argv[1];

    // initialize main Ship context; required to work with ArchiveManager
    auto context = Ship::Context::CreateUninitializedInstance("OTR extractor", "vinny", "shipofharkinian.json");
    context->InitLogging(spdlog::level::debug, spdlog::level::debug);
    context->InitConfiguration();
    context->InitConsoleVariables();
    context->InitConsole();
    context->InitResourceManager({ archivePath }, {}, 3, true);
    auto guiWindows = std::vector<std::shared_ptr<Ship::GuiWindow>>();
    auto gui = std::make_shared<Ship::Gui>(guiWindows);
    gui->Init();
    context->InitWindow(std::make_shared<FakeWindow>(gui));

    // Create a temporary ArchiveManager and mount the provided path.
    // AddArchive() returns a shared_ptr to the created archive; we also
    // check IsLoaded() to ensure the virtual filesystem populated.
    auto am = *context->GetResourceManager()->GetArchiveManager();
    if (!am.IsLoaded()) {
        std::cerr << "Failed to open archive: " << archivePath << std::endl;
        return 3;
    }
    loadResourceFactories(context->GetResourceManager()->GetResourceLoader());

    // The OTR virtual asset key for the bomb display list (from SOH headers).
    const std::string assetKey = "__OTR__objects/object_gi_bomb_1/gGiBombDL";
    
    /* We'll use the Interpreter to traverse and process the display list command structure */
    auto interpreter = std::make_shared<Fast::Interpreter>();
    Fast::GfxSetInstance(interpreter);
    auto gfxDebugger = std::make_shared<Fast::GfxDebugger>();
    interpreter->SetGfxDebugger(gfxDebugger);
    interpreter->Init(
        new FakeWindowBackend(),
        new Extractor(),
        "extractor",
        false,
        0, 0,
        0, 0
    );

    auto res = context->GetResourceManager()->LoadResource(assetKey);
    if (res) {
        std::cout << "got resource of type: " << typeid(res).name() << std::endl;
        auto dlRes = std::dynamic_pointer_cast<Fast::DisplayList>(res);
        if (dlRes) {
            std::cout << "total Instruction Size: " << dlRes->Instructions.size() << ":" << std::endl;

            for (size_t i = 0; i < dlRes->Instructions.size(); i++) {
                std::string id = "##CMD" + std::to_string(i);
                Gfx* gfx = (Gfx*)&dlRes->Instructions[i];
                int cmd = static_cast<int>(gfx->words.w0 >> 24);
                if (cmdMap.find(cmd) == cmdMap.end())
                    continue;

                std::string cmdLabel = cmdMap.at(cmd);

                std::cout << id << ": " << cmdLabel << std::endl;
            }
        }
    }
    //     interpreter->Run(&gfx, {});

    context->DestroyInstance();
    return 0;
}
