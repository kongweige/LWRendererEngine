#include "glad/glad.h"
#include "controller/displayManager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <cstdio>


DisplayManager::DisplayManager() { }

DisplayManager::~DisplayManager() { }

// Start order of the rendering Library
bool DisplayManager::startUp()
{
  if (!startGLFW())
  {
    return false;
  }

  if (!createWindow())
  {
    return false;
  }

  if (!createGLContext())
  {
    return false;
  }

  if (!startOpenGL())
  {
    return false;
  }

  if (!createImGuiContext()) 
  {
    return false;
  }

  return true;
}

void DisplayManager::shutDown()
{
  // resource reclamation
  glfwTerminate();
  ImGui::EndFrame();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  window = nullptr;
}

// Swaps the finished drawn buffer with the window bufffer.
// Also initializes a new frame for the gui renderer.
void DisplayManager::swapDisplayBuffer() {
  // Now that all data has been added to the frame we overlay the GUI onto it
  // Just before frame swap
  ImGui::EndFrame();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  // Actual buffer swap
  glfwSwapBuffers(window);
  glfwPollEvents();

  // Signaling beginning of frame to gui
  ImGui::StyleColorsDark();
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

// Binding the display framebuffer for drawing and clearing it before rendering
void DisplayManager::bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// initialize and configure glfw
bool DisplayManager::startGLFW()
{
  if (!glfwInit())
  {
    printf("Failed to initialize GLFW.\n");
    return false;
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  return true;
}

// glfw window creation
bool DisplayManager::createWindow()
{
  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "EGE", NULL, NULL);
  if (window == NULL)
  {
    printf("Failed to create GLFW window.\n");
    glfwTerminate();
    return false;
  }  
  return true;
}


// load all OpenGl function pointers
bool DisplayManager::startOpenGL()
{
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("Failed to initialize GLAD.\n");
    return false;
  }
}

// Bind current window context
bool DisplayManager::createGLContext()
{
  glfwMakeContextCurrent(window);
  return true;
}

// Inits our GUI library and calls all init functions related to configuring it for use
bool DisplayManager::createImGuiContext()
{
  IMGUI_CHECKVERSION();
  ImGuiContext* mGuiContext = ImGui::CreateContext();
  if (mGuiContext == nullptr) 
  {
    printf("Could not load IMGUI context!\n");
    return false;
  }  
  
  // 将imgui嵌入到glfw中
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Imgui first frame setup
  ImGui::StyleColorsDark();
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  return true;
}

GLFWwindow* DisplayManager::getGlfwWindow()
{
  return window;
}

