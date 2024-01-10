#pragma once

class VisualNovelEngine {
public:
    VisualNovelEngine();

    ~VisualNovelEngine();

    void run();
    static GLuint loadTexture(const std::string& filePath);

    static float screenWidth, screenHeight;
private:
    GLFWwindow* window;

    void Draw();
    void Render();
    
    static void windowSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};