#pragma once

#define DEFAULT_FONT_PATH "assets/arial.ttf"
#define MAX_FONT_SIZE 100.0f

#define GUI_FONT(v) GUI::GetFontHelper()->GetFont(v)

#include "FontHelper.h"
#include "TextureHelper.h"

class GUI
{
private:
	static TextureHelper* g_pTexHelper;
	static FontHelper* g_pFontHelper;
public:
	static void Draw();
	static void DrawImage(const std::string& texturePath, const ImVec2& pos, const ImVec2& size);
	static TextureHelper* GetTextureHelper();
	static FontHelper* GetFontHelper();
	static void InitFonts();
	static ImFont* LoadFont(const char* fontPath, float fontSize, const ImFontConfig* config = nullptr);
	static void DrawCircle(const ImVec2& center, float radius, const ImVec4& color);
	static void DrawQuad(const ImVec2& topLeft, const ImVec2& bottomRight, const ImVec4& color);
	static void DrawFilledCircle(const ImVec2& center, float radius, const ImVec4& color);
	static void DrawText(const ImVec2& position, const char* text, const ImVec4& textColor, const ImVec4& shadowColor, const ImVec4& strokeColor, float fontSize, float strokeSize);
	static void DrawText(const ImFont* font, const ImVec2& position, const char* text, const ImVec4& textColor, const ImVec4& shadowColor, const ImVec4& strokeColor, float fontSize, float strokeSize);
};