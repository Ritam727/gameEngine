#include <_internals.hpp>

static void processInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    Camera::keyboardCallback(window, deltaTime);
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

int main(void)
{
    Logger::init();
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, (float)Screen::getScreenWidth() / 2.0f, (float)Screen::getScreenHeight() / 2.0f);
    glfwSetCursorPosCallback(window, Camera::mouseCallback);
    glfwSetScrollCallback(window, Camera::scrollCallback);
    glfwSetFramebufferSizeCallback(window, Renderer::viewportCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::logError("Failed to initialize GLAD!");
        return -1;
    }

    {
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

        std::vector<DirLight> dirLights; // ({ DirLight().setDirection({ -0.2f, -1.0f, -0.3f }) });
        std::vector<PointLight> pointLights; // ({ PointLight().setPosition({ 1.5f, 1.2f, 2.0f }) });

        std::future<void> *inputThread = new std::future<void>(std::async(std::launch::async, handleInput));

        while (!glfwWindowShouldClose(window))
        {
            Renderer::clearColor({0.5f, 0.5f, 0.5f, 1.0f});
            Renderer::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            glfwGetWindowSize(window, &Screen::getScreenWidth(), &Screen::getScreenHeight());
            float currentTime = glfwGetTime();
            deltaTime = currentTime - lastFrame;
            lastFrame = currentTime;
            std::vector<SpotLight> spotLights({
                SpotLight()
                .setPosition(Camera::getCameraPos())
                .setDirection(Camera::getCameraFront())
            });

            processInput(window, deltaTime);
            glfwPollEvents();
            // cubemaps
            
            // objects
            Drawer::update(dirLights, pointLights, spotLights);
            Drawer::render();
            
            glfwSwapBuffers(window);
        }
        
        if (inputThread->wait_for(std::chrono::milliseconds(200)) == std::future_status::timeout)
            Logger::logWarn("Closing input thread");
        else
            delete inputThread;

        Drawer::clearModels();
        Drawer::clearMeshes();
        Drawer::clearUniformBuffers();
        Texture::clearTextures();
    }

    glfwTerminate();
    return 0;
}