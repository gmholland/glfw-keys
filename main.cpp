#include <fmt/core.h>
#include <fmt/ranges.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <string>
#include <vector>

static std::string keyActionToString(int action)
{
    switch (action)
    {
    case GLFW_RELEASE:
        return "RELEASE";
    case GLFW_PRESS:
        return "PRESS";
    case GLFW_REPEAT:
        return "REPEAT";
    }
    return "";
}

static std::string modKeysToString(int mods)
{
    std::vector<std::string> v;
    if (mods & GLFW_MOD_ALT)
    {
        v.emplace_back("alt");
    }
    if (mods & GLFW_MOD_CAPS_LOCK)
    {
        v.emplace_back("caps_lk");
    }
    if (mods & GLFW_MOD_CONTROL)
    {
        v.emplace_back("ctrl");
    }
    if (mods & GLFW_MOD_NUM_LOCK)
    {
        v.emplace_back("num_lk");
    }
    if (mods & GLFW_MOD_SHIFT)
    {
        v.emplace_back("shift");
    }
    if (mods & GLFW_MOD_SUPER)
    {
        v.emplace_back("super");
    }
    return fmt::format("{}", fmt::join(v, ","));
}

void printKeyEvent(int key, int scancode, int action, int mods)
{
    std::string out = fmt::format("Key event: {}, key: {}", keyActionToString(action), key);

    auto keyName = glfwGetKeyName(key, scancode);
    if (keyName)
    {
        out += fmt::format(" ({})", keyName);
    }
    out += fmt::format(", scancode: {:#x}", scancode);

    auto modsStr = modKeysToString(mods);
    if (!modsStr.empty())
    {
        out += fmt::format(", mods: {}", modsStr);
    }

    fmt::print("{}\n", out);
    fflush(stdout);
}

void keyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    printKeyEvent(key, scancode, action, mods);
    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
    {
        fmt::print("Received Esc, closing...\n");
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main()
{
    fmt::print("GLFW Version String: {}\n", glfwGetVersionString());
    fmt::print("Press Esc to exit\n");

    glfwSetErrorCallback([](int code, const char* description) {
        fmt::print(stderr, "GLFW Error (code: {}, description: {}\n", code, description);
    });

    if (!glfwInit())
    {
        fmt::print(stderr, "GLFW Init failed\n");
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", nullptr, nullptr);
    if (!window)
    {
        fmt::print("GLFW CreateWindow failed\n");
        glfwTerminate();
        return 1;
    }

    glfwSetKeyCallback(window, keyEventCallback);
    glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codepoint){
        fmt::print("Codepoint: {}\n", codepoint);
        fflush(stdout);
    });

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
