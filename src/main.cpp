#include <_internals.hpp>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <IGFD/ImGuiFileDialog.h>

static void processInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void fileDialog(bool &onWindow)
{
    IGFD::FileDialogConfig config;
    config.path = ".";
    config.flags = ImGuiFileDialogFlags_DisableQuickPathSelection;
    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".obj,.mtl,.fbx,.bin,.gltf", config);
    ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByTypeDir | IGFD_FileStyleByTypeLink, nullptr, ImVec4(0.8f, 0.8f, 0.8f, 0.8f), ICON_IGFD_FOLDER);
    ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtention, ".obj", ImVec4(0.8f, 0.8f, 0.8f, 0.8f), ICON_IGFD_FILE);
    onWindow |= ImGui::IsWindowFocused() | ImGui::IsWindowHovered();

    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

            ModelLoader loader = ModelLoader(filePathName, 1, 1);
            Drawer::enqueue(loader);
        }
        ImGuiFileDialog::Instance()->Close();
    }
}

void dockSpace(bool *p_open)
{
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", p_open, window_flags);
    ImGui::PopStyleVar(3);

    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    ImGui::End();
}

void lightControls(bool &onWindow)
{
    
}

int main(void)
{
    Logger::init();
    Camera::init();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 16);

    GLFWwindow *window = glfwCreateWindow(Screen::getScreenWidth(), Screen::getScreenHeight(), "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        Logger::logError("Failed to initialize GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Renderer::viewportCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::logError("Failed to initialize GLAD!");
        return -1;
    }

    {
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags != ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.Fonts->AddFontDefault();
        static const ImWchar icons_ranges[] = {ICON_MIN_IGFD, ICON_MAX_IGFD, 0};
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;
        io.Fonts->AddFontFromMemoryCompressedBase85TTF(FONT_ICON_BUFFER_NAME_IGFD, 15.0f, &icons_config, icons_ranges);

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 450");

        Renderer::clearDepth();
        Renderer::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        Renderer::enable(GL_BLEND);
        Renderer::enable(GL_CULL_FACE);
        Renderer::enable(GL_DEPTH_TEST);
        Renderer::enable(GL_STENCIL_TEST);
        Renderer::enable(GL_MULTISAMPLE);
        Renderer::enable(GL_PROGRAM_POINT_SIZE);

        Drawer::init();

        float lastFrame = 0.0f;
        float deltaTime = 0.0f;

        std::vector<DirLight> dirLights({DirLight().setDirection({-0.2f, -1.0f, -0.3f})});
        Drawer::addDirLight(dirLights[0]);
        std::vector<PointLight> pointLights; // ({ PointLight().setPosition({ 1.5f, 1.2f, 2.0f }) });

        glfwGetWindowSize(window, &Screen::getScreenWidth(), &Screen::getScreenHeight());

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            Renderer::enable(GL_DEPTH_TEST);
            Renderer::stencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

            glfwGetWindowSize(window, &Screen::getScreenWidth(), &Screen::getScreenHeight());
            float currentTime = glfwGetTime();
            deltaTime = currentTime - lastFrame;
            lastFrame = currentTime;
            std::vector<SpotLight> spotLights; //({SpotLight()
                                               //  .setPosition(Camera::getCameraPos())
                                               //.setDirection(Camera::getCameraFront())});
            int width_ = Screen::getScreenWidth();
            int height_ = Screen::getScreenHeight();

            Drawer::update(width_, height_, dirLights, pointLights, spotLights);
            Drawer::renderForMousePicking();

            Renderer::clearColor({0.5f, 0.5f, 0.5f, 1.0f});
            Renderer::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            bool onWindow = false;
            dockSpace(NULL);
            ImGui::Begin("Camera");
            Camera::drawCameraControlsGui();
            onWindow |= ImGui::IsWindowFocused() | ImGui::IsWindowHovered();
            ImGui::Text("FrameRate %.3f", io.Framerate);
            ImGui::End();

            ImGui::Begin("Objects");
            Drawer::render();
            onWindow |= ImGui::IsWindowFocused() | ImGui::IsWindowHovered();
            ImGui::End();

            ImGui::Begin("Lights");
            Drawer::lightControlsGui();
            ImGui::End();

            fileDialog(onWindow);

            onWindow |= ImGui::IsAnyItemActive() | ImGui::IsAnyItemHovered() | ImGui::IsAnyItemFocused();

            Drawer::setOnWindow(onWindow);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow *backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }
            processInput(window, deltaTime);
            glfwSwapBuffers(window);
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        Drawer::clearModels();
        Drawer::clearMeshes();
        Drawer::clearUniformBuffers();
        Texture::clearTextures();
    }

    glfwTerminate();
    return 0;
}