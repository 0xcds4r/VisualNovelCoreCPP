#pragma once

class TextureHelper {
public:
    TextureHelper();
    ~TextureHelper();

    GLuint getTextureID(const std::string& texturePath);
private:
    struct TextureEntry {
        std::string texturePath;
        GLuint textureID;
    };

    std::list<TextureEntry> textureCache;

    std::list<TextureEntry>::iterator findTexture(const std::string& texturePath) {
        return std::find_if(textureCache.begin(), textureCache.end(),
            [&](const TextureEntry& entry) {
                return entry.texturePath == texturePath;
            });
    };
};