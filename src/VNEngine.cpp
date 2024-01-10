#include "main.h"
#include "VNEngine.h"
#include "gui/GUI.h"

float VisualNovelEngine::screenWidth = 1920.0f;
float VisualNovelEngine::screenHeight = 1080.0f;

void VisualNovelEngine::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void VisualNovelEngine::windowSizeCallback(GLFWwindow* window, int width, int height) 
{
	VisualNovelEngine::screenWidth = width;
	VisualNovelEngine::screenHeight = height;
	glViewport(0, 0, width, height);
}	

VisualNovelEngine::VisualNovelEngine() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	window = glfwCreateWindow(VisualNovelEngine::screenWidth, VisualNovelEngine::screenHeight, "Visual Novel Engine", NULL, NULL);

	if (!window) {
		glfwTerminate();
		std::cerr << "Failed to create GLFW window" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, VisualNovelEngine::keyCallback);
	glfwSetWindowSizeCallback(window, VisualNovelEngine::windowSizeCallback);

    if (glewInit() != GLEW_OK) {
   		std::cerr << "Failed to initialize GLEW" << std::endl;
        std::exit(EXIT_FAILURE);
    }

	glViewport(0, 0, VisualNovelEngine::screenWidth, VisualNovelEngine::screenHeight);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    GUI::InitFonts();
}

VisualNovelEngine::~VisualNovelEngine() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
	glfwTerminate();
}

GLuint VisualNovelEngine::loadTexture(const std::string& filePath) 
{
    printf("Loading new texture: %s\n", filePath.c_str());
    int width, height;
    unsigned char* image = SOIL_load_image(filePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

void VisualNovelEngine::Draw() {
	GUI::Draw();
}

void VisualNovelEngine::Render() {

}

void VisualNovelEngine::run() 
{
	glEnable(GL_CULL_FACE);
   	glEnable(GL_BLEND);
   	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!glfwWindowShouldClose(window)) 
	{
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

       	this->Draw();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        this->Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwPollEvents();
        glfwSwapBuffers(window);
	}
}