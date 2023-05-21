#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
//Optimizable *1
#include<fstream>
#include<string>
#include<sstream>

#include"Renderer.h"
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"Texture.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw_gl3.h"

#include"tests/TestClearColor.h"
#include"tests/TestTexture2D.h"
#include"tests/TestPerspectiva.h"
#include"tests/Test3D.h"
#include"tests/TestMultiobject.h"
#include"tests/TestPlayground.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);





    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "GlewInitError" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
       
        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();
        /*
        glm::vec3 translationA(200, 200, 0);
        glm::vec3 translationB(400, 200, 0);

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        float r = 0.0f;
        float inc = 0.05f;
        */
        /* Loop until the user closes the window */

        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
        testMenu->RegisterTest<test::TestPerspectiva>("Perspectiva");
        testMenu->RegisterTest<test::Test3D>("3D");
        testMenu->RegisterTest<test::TestMultiobject>("Multiobject");
        testMenu->RegisterTest<test::TestPlayground>("Playground");


        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();
            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }

                currentTest->OnImGuiRender();
                ImGui::End();
            }
           
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        delete currentTest;
        if (currentTest != testMenu)
            delete testMenu;
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}