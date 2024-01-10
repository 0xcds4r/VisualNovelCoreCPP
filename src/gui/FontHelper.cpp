#include "../main.h"
#include "../VNEngine.h"
#include "GUI.h"

FontHelper::~FontHelper() {
    for (const CachedFont& cachedFont : fontCache) {
        ImGui::GetIO().Fonts->TexID = 0;
        ImGui::GetIO().Fonts->ClearFonts();
        if (cachedFont.font) {
            delete cachedFont.font;
        }
    }
}

const ImWchar* FontHelper::GetGlyphRangesUTF8()
{
    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF,   // Basic Latin + Latin Supplement
        0x0400, 0x04FF,   // Cyrillic
        0x2000, 0x206F,   // General Punctuation
        0x3000, 0x30FF,   // CJK Symbols and Punctuation
        0x4E00, 0x9FFF,   // CJK Ideographs
        0xAC00, 0xD7A3,   // Hangul Syllables
        0,
    };
    return &ranges[0];
}

ImFont* FontHelper::LoadFont(const char* fontPath, float fontSize, const ImFontConfig* config) {
    ImGuiIO& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromFileTTF(fontPath, fontSize, config, GetGlyphRangesUTF8());

    std::string key = std::string(fontPath);

    printf("New font added: %s\n", key);
    fontCache.push_back({ key, font });

    return font;
}

ImFont* FontHelper::GetFont(const std::string& fontKey, float fontSize, const ImFontConfig* config) {
    for (CachedFont& cachedFont : fontCache) {
        if (cachedFont.key == fontKey) {
            return cachedFont.font;
        }
    }

    return nullptr;
}