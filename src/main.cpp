#include <_internals.hpp>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

static void processInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

static void handleInput()
{
    while (true)
    {
        std::string path;
        unsigned int mode;
        unsigned int priority;

        std::cout << "Enter path of model: ";
        std::cin >> path;
        std::cout << "Enter mode of rendering: ";
        std::cin >> mode;
        std::cout << "Enter priority of rendering: ";
        std::cin >> priority;

        ModelLoader loader = ModelLoader(path, mode, priority);
        Drawer::enqueue(loader);
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
    ImGui::Begin("DockSpace Demo", p_open, window_flags);
    ImGui::PopStyleVar(3);

    // Submit the DockSpace
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    ImGui::End();
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
        std::vector<PointLight> pointLights; // ({ PointLight().setPosition({ 1.5f, 1.2f, 2.0f }) });

        std::future<void> *inputThread = new std::future<void>(std::async(std::launch::async, handleInput));

        FrameBuffer frameBuffer;
        frameBuffer.attachTexture(7);
        frameBuffer.attachDepthBuffer(6);
        frameBuffer.validate();
        frameBuffer.unbind();

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Renderer::clearColor({0.5f, 0.5f, 0.5f, 1.0f});
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

            ImGui::SetNextWindowSize(ImVec2(width_ / 2, height_ / 2));
            ImGui::Begin("Render");
            ImVec2 pos = ImGui::GetCursorScreenPos();
            float window_width = ImGui::GetContentRegionAvail().x;
            float window_height = ImGui::GetContentRegionAvail().y;

            frameBuffer.bind();
            Renderer::stencilMask(0x00);
            Renderer::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            Drawer::update(width_, height_, dirLights, pointLights, spotLights);
            bool onWindow = Drawer::getOnWindow();
            Drawer::renderForMousePicking(onWindow);
            // frameBuffer.forwardBuffers(width_, height_);

            ImGui::GetWindowDrawList()->AddImage(
                (void *)(size_t)frameBuffer.getTexture()->getID(),
                ImVec2(pos.x, pos.y),
                ImVec2(pos.x + window_width, pos.y + window_height),
                ImVec2(0, 1),
                ImVec2(1, 0));

            Renderer::stencilMask(0xFF);
            frameBuffer.unbind();
            ImGui::End();

            Renderer::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            dockSpace(NULL);
            ImGui::Begin("Camera");
            Camera::drawCameraControlsGui();
            ImGui::Text("FrameRate %.3f", io.Framerate);
            bool onCameraWindow = ImGui::IsWindowHovered() | ImGui::IsAnyItemHovered() | ImGui::IsWindowFocused() | ImGui::IsAnyItemFocused() | ImGui::IsAnyItemActive();
            ImGui::End();

            ImGui::Begin("Objects");
            Drawer::update(width_, height_, dirLights, pointLights, spotLights);
            Drawer::render();
            bool onObjectWindow = ImGui::IsWindowHovered() | ImGui::IsAnyItemHovered() | ImGui::IsWindowFocused() | ImGui::IsAnyItemFocused() | ImGui::IsAnyItemActive();
            ImGui::End();

            Drawer::setOnWindow(onCameraWindow | onObjectWindow);

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

        if (inputThread->wait_for(std::chrono::milliseconds(200)) == std::future_status::timeout)
            Logger::logWarn("Closing input thread");
        else
            delete inputThread;

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