#include "../main.h"
#include "../VNEngine.h"
#include "GUI.h"

TextureHelper::TextureHelper() {

}

TextureHelper::~TextureHelper() {
    for (const auto& entry : textureCache) {
    	glDeleteTextures(1, &entry.textureID);
    }
}

GLuint TextureHelper::getTextureID(const std::string& texturePath) 
{
	auto it = this->findTexture(texturePath);
	if (it != textureCache.end()) {
		return it->textureID;
	} else {
		GLuint textureID = VisualNovelEngine::loadTexture(texturePath);
		textureCache.push_back({texturePath, textureID});
		return textureID;
	}
}