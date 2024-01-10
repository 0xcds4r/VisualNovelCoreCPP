#pragma once

class FontHelper {
public:
    FontHelper() = default;
    ~FontHelper();

    ImFont* LoadFont(const char* fontPath, float fontSize, const ImFontConfig* config = nullptr);
    ImFont* GetFont(const std::string& fontKey, float fontSize = 100.0f, const ImFontConfig* config = nullptr);
    const ImWchar* GetGlyphRangesUTF8();
private:
    struct CachedFont {
        std::string key;
        ImFont* font;
    };

    std::list<CachedFont> fontCache;
};