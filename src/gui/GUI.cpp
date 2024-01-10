#include "../main.h"
#include "GUI.h"
#include "../VNEngine.h"

TextureHelper* GUI::g_pTexHelper = nullptr;
FontHelper* GUI::g_pFontHelper = nullptr;

ImFont* GUI::LoadFont(const char* fontPath, float fontSize, const ImFontConfig* config)
{
    ImGuiIO& io = ImGui::GetIO();
    return io.Fonts->AddFontFromFileTTF(fontPath, fontSize, config);
}

void GUI::InitFonts()
{
	GUI::GetFontHelper()->LoadFont(DEFAULT_FONT_PATH, MAX_FONT_SIZE);
	GUI::GetFontHelper()->LoadFont("assets/monas.ttf", MAX_FONT_SIZE);	
}

void GUI::Draw() 
{
    ImVec2 imageSize(VisualNovelEngine::screenWidth, VisualNovelEngine::screenHeight); 
    ImVec2 position(0,0);
    GUI::DrawImage("assets/bg/Street_Summer_Evening.png", position, imageSize);

    ImVec2 circleCenter(100, 100);
    float circleRadius = 20.0f;
    ImVec4 circleColor(1.0f, 0.0f, 0.0f, 1.0f); // Red color
    GUI::DrawCircle(circleCenter, circleRadius, circleColor);

    ImVec2 quadTopLeft(200, 200);
    ImVec2 quadBottomRight(300, 300);
    ImVec4 quadColor(0.0f, 1.0f, 0.0f, 1.0f); // Green color
    GUI::DrawQuad(quadTopLeft, quadBottomRight, quadColor);

    ImVec2 filledCircleCenter(150, 150);
    float filledCircleRadius = 25.0f;
    ImVec4 filledCircleColor(0.0f, 0.0f, 1.0f, 1.0f); // Blue color
    GUI::DrawFilledCircle(filledCircleCenter, filledCircleRadius, filledCircleColor);

    ImVec2 subtitleBackgroundTopLeft(0, VisualNovelEngine::screenHeight * 0.85); 
    ImVec2 subtitleBackgroundBottomRight(VisualNovelEngine::screenWidth, VisualNovelEngine::screenHeight);
    ImVec4 subtitleBackgroundColor(0.0f, 0.0f, 0.0f, 0.5f); 
    GUI::DrawQuad(subtitleBackgroundTopLeft, subtitleBackgroundBottomRight, subtitleBackgroundColor);

    ImVec2 textPosition(50, (VisualNovelEngine::screenHeight * 0.92)); 
    const char* text = "привет мир";
    ImVec4 textColor(1.0f, 1.0f, 1.0f, 1.0f); // White color
    ImVec4 shadowColor(0.0f, 0.0f, 0.0f, 0.7f); // Dark shadow color
    ImVec4 strokeColor(0.0f, 0.0f, 0.0f, 1.0f); // Black stroke color
    float fontSize = 20.0f;
    float strokeSize = 1.5f;	
    GUI::DrawText(GUI_FONT("assets/arial.ttf"), textPosition, text, textColor, shadowColor, strokeColor, fontSize, strokeSize);
    textPosition.y += 20.0f;
    const char* text2 = "hello world";
    GUI::DrawText(GUI_FONT("assets/monas.ttf"), textPosition, text2, textColor, shadowColor, strokeColor, fontSize * 2, strokeSize);
}

void GUI::DrawImage(const std::string& texturePath, const ImVec2& pos, const ImVec2& size) {
	GLuint textureID = GUI::GetTextureHelper()->getTextureID(texturePath);
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    drawList->AddImage((void*)(intptr_t)textureID, pos, ImVec2(pos.x + size.x, pos.y + size.y));
}

void GUI::DrawCircle(const ImVec2& center, float radius, const ImVec4& color)
{
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    drawList->AddCircle(center, radius, IM_COL32(color.x * 255, color.y * 255, color.z * 255, color.w * 255));
}

void GUI::DrawQuad(const ImVec2& topLeft, const ImVec2& bottomRight, const ImVec4& color)
{
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    drawList->AddRectFilled(topLeft, bottomRight, IM_COL32(color.x * 255, color.y * 255, color.z * 255, color.w * 255));
}

void GUI::DrawFilledCircle(const ImVec2& center, float radius, const ImVec4& color)
{
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    drawList->AddCircleFilled(center, radius, IM_COL32(color.x * 255, color.y * 255, color.z * 255, color.w * 255));
}

void GUI::DrawText(const ImVec2& position, const char* text, const ImVec4& textColor, const ImVec4& shadowColor, const ImVec4& strokeColor, float fontSize, float strokeSize)
{
   	ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    // Draw shadow
    drawList->AddText(GUI::GetFontHelper()->GetFont(DEFAULT_FONT_PATH), fontSize, ImVec2(position.x + 2, position.y + 2), IM_COL32(shadowColor.x * 255, shadowColor.y * 255, shadowColor.z * 255, shadowColor.w * 255), text);

    // Draw stroke
    for (float dx = -strokeSize; dx <= strokeSize; dx += 0.5f)
    {
        for (float dy = -strokeSize; dy <= strokeSize; dy += 0.5f)
        {
            if (dx * dx + dy * dy >= strokeSize * strokeSize)
                continue;

            drawList->AddText(GUI::GetFontHelper()->GetFont(DEFAULT_FONT_PATH), fontSize, ImVec2(position.x + dx, position.y + dy), IM_COL32(strokeColor.x * 255, strokeColor.y * 255, strokeColor.z * 255, strokeColor.w * 255), text);
        }
    }

    // Draw text
    drawList->AddText(GUI::GetFontHelper()->GetFont(DEFAULT_FONT_PATH), fontSize, position, IM_COL32(textColor.x * 255, textColor.y * 255, textColor.z * 255, textColor.w * 255), text);
}

void GUI::DrawText(const ImFont* font, const ImVec2& position, const char* text, const ImVec4& textColor, const ImVec4& shadowColor, const ImVec4& strokeColor, float fontSize, float strokeSize)
{
   	ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    // Draw shadow
    drawList->AddText(font, fontSize, ImVec2(position.x + 2, position.y + 2), IM_COL32(shadowColor.x * 255, shadowColor.y * 255, shadowColor.z * 255, shadowColor.w * 255), text);

    // Draw stroke
    for (float dx = -strokeSize; dx <= strokeSize; dx += 0.5f)
    {
        for (float dy = -strokeSize; dy <= strokeSize; dy += 0.5f)
        {
            if (dx * dx + dy * dy >= strokeSize * strokeSize)
                continue;

            drawList->AddText(font, fontSize, ImVec2(position.x + dx, position.y + dy), IM_COL32(strokeColor.x * 255, strokeColor.y * 255, strokeColor.z * 255, strokeColor.w * 255), text);
        }
    }

    // Draw text
    drawList->AddText(font, fontSize, position, IM_COL32(textColor.x * 255, textColor.y * 255, textColor.z * 255, textColor.w * 255), text);
}

TextureHelper* GUI::GetTextureHelper() 
{
	if(GUI::g_pTexHelper == nullptr) {
		GUI::g_pTexHelper = new TextureHelper();
	}

	return g_pTexHelper;
}

FontHelper* GUI::GetFontHelper() 
{
	if(GUI::g_pFontHelper == nullptr) {
		GUI::g_pFontHelper = new FontHelper();
	}

	return g_pFontHelper;
}