// Simple utility to load a display-list asset from an OTR/O2R/folder archive
// and print the raw F3D instructions in a human-readable form.

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include <unordered_map>

#include <ship/Context.h>
#include <ship/resource/ResourceManager.h>
#include <ship/resource/archive/ArchiveManager.h>
#include <ship/resource/File.h>

#include "FakeWindow.h"

using namespace Ship;

// Small helper that maps an F3D opcode byte to a readable name. This is
// intentionally minimal — it only provides friendly labels for common opcodes
// so the printed output is easier to scan.
static std::string OpcodeName(uint8_t op)
{
    static const std::unordered_map<uint8_t, std::string> m = {
        {0x00, "G_SPNOOP/G_NOOP"}, {0x01, "G_MTX"}, {0x03, "G_MOVEMEM"}, {0x04, "G_VTX"},
        {0x06, "G_DL"}, {0xAF, "G_LOAD_UCODE"}, {0xB0, "G_BRANCH_Z"}, {0xB1, "G_TRI2"},
        {0xB2, "G_MODIFYVTX"}, {0xB3, "G_RDPHALF_2"}, {0xB4, "G_RDPHALF_1"}, {0xB5, "G_QUAD"},
        {0xB6, "G_CLEARGEOMETRYMODE"}, {0xB7, "G_SETGEOMETRYMODE"}, {0xB8, "G_ENDDL"},
        {0xB9, "G_SETOTHERMODE_L"}, {0xBA, "G_SETOTHERMODE_H"}, {0xBB, "G_TEXTURE"},
        {0xBC, "G_MOVEWORD"}, {0xBD, "G_POPMTX"}, {0xBE, "G_CULLDL"}, {0xBF, "G_TRI1"},
        {0xC0, "G_NOOP"}, {0xE4, "G_TEXRECT"}, {0xE5, "G_TEXRECTFLIP"}, {0xE6, "G_RDPLOADSYNC"},
        {0xE7, "G_RDPPIPESYNC"}, {0xE8, "G_RDPTILESYNC"}, {0xE9, "G_RDPFULLSYNC"},
        {0xEA, "G_SETKEYGB"}, {0xEB, "G_SETKEYR"}, {0xEC, "G_SETCONVERT"}, {0xED, "G_SETSCISSOR"},
        {0xEE, "G_SETPRIMDEPTH"}, {0xEF, "G_RDPSETOTHERMODE"}, {0xF0, "G_LOADTLUT"},
        {0xF2, "G_SETTILESIZE"}, {0xF3, "G_LOADBLOCK"}, {0xF4, "G_LOADTILE"}, {0xF5, "G_SETTILE"},
        {0xF6, "G_FILLRECT"}, {0xF7, "G_SETFILLCOLOR"}, {0xF8, "G_SETFOGCOLOR"},
        {0xF9, "G_SETBLENDCOLOR"}, {0xFA, "G_SETPRIMCOLOR"}, {0xFB, "G_SETENVCOLOR"},
        {0xFC, "G_SETCOMBINE"}, {0xFD, "G_SETTIMG"}, {0xFE, "G_SETZIMG"}, {0xFF, "G_SETCIMG"}
    };
    auto it = m.find(op);
    return it != m.end() ? it->second : "UNKNOWN";
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
    auto guiWindows = std::vector<std::shared_ptr<GuiWindow>>();
    auto gui = std::make_shared<Gui>(guiWindows);
    gui->Init();
    context->InitWindow(std::make_shared<FakeWindow>(gui));

    // Create a temporary ArchiveManager and mount the provided path.
    // AddArchive() returns a shared_ptr to the created archive; we also
    // check IsLoaded() to ensure the virtual filesystem populated.
    ArchiveManager am = *context->GetResourceManager()->GetArchiveManager();
    if (!am.IsLoaded()) {
        std::cerr << "Failed to open archive: " << archivePath << std::endl;
        return 3;
    }

    // The OTR virtual asset key for the bomb display list (from SOH headers).
    // const std::string assetKey = "__OTR__objects/object_gi_bomb_1/gGiBombDL";
    const std::string assetKey = "objects/object_gi_bomb_1/gGiBombDL";

    // Load raw file bytes. ArchiveManager::LoadFile returns a Ship::File
    // containing a shared buffer we can inspect without needing the whole
    // engine Context.
    auto file = am.LoadFile(assetKey);
    if (!file || !file->IsLoaded || file->Buffer->empty()) {
        std::cerr << "Asset not found or empty: " << assetKey << std::endl;
        return 4;
    }

    // Interpret the buffer as a sequence of 64-bit big-endian words (F3D
    // instructions are 8 bytes each). We then split each word into the
    // opcode (top byte) and the remaining operands (low 56 bits).
    auto& buf = *file->Buffer;
    size_t size = buf.size();
    std::cout << "Loaded asset " << assetKey << " (" << size << " bytes)" << std::endl;

    if (size % 8 != 0) {
        std::cout << "Warning: display list size not divisible by 8 bytes." << std::endl;
    }

    size_t count = size / 8;
    for (size_t i = 0; i < count; ++i) {
        // Build 64-bit big-endian value from 8 consecutive bytes
        uint64_t v = 0;
        for (size_t b = 0; b < 8; ++b) {
            v = (v << 8) | static_cast<uint8_t>(buf[i * 8 + b]);
        }
        uint8_t opcode = static_cast<uint8_t>(v >> 56);
        uint64_t operands = v & 0x00FFFFFFFFFFFFFFULL;

        // Print index, opcode (hex), friendly name and raw operands (hex).
        std::cout << "[" << i << "] 0x" << std::hex << std::uppercase << (uint32_t)opcode << std::dec
                  << " (" << OpcodeName(opcode) << ") ";
        std::cout << " operands=0x" << std::hex << operands << std::dec << std::nouppercase << std::endl;
    }

    context->DestroyInstance();
    return 0;
}
