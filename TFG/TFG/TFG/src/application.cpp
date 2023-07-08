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
#include"tests/TestMultiDrawCalls.h"
#include"tests/TestCamera.h"
#include"tests/TestRainbowRoad.h"
#include"tests/TestBoard.h"
#include"tests/TestImported.h"

int main(void)
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Orenaut", NULL, NULL);
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
       

        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("C:/Users/sbons/OneDrive/Documentos/GitHub/TFG/TFG/TFG/TFG/res/Sound/Baseline.wav")) {
            // Error handling if sound file fails to load
        }
        sf::Sound* so = new sf::Sound(buffer);

        sf::SoundBuffer buffer1;
        if (!buffer1.loadFromFile("C:/Users/sbons/OneDrive/Documentos/GitHub/TFG/TFG/TFG/TFG/res/Sound/BaselinePP.wav")) {
            // Error handling if sound file fails to load
        }
        sf::Sound* so2 = new sf::Sound(buffer1);
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        /* Loop until the user closes the window */

        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        test::TestCamera* testCamera = new test::TestCamera(window);
        test::TestPlayground* testPlayground = new test::TestPlayground(window, so, so2);


        currentTest = testMenu;
        //testMenu->RegisterTest<test::TestPlayground>("Playground");
        testMenu->RegisterTest<test::TestBoard>("Board");
        testMenu->RegisterTest<test::TestRainbowRoad>("RainbowRoad");
        testMenu->RegisterTest<test::TestMultiDrawCalls>("MultiDrawCalls");
        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
        testMenu->RegisterTest<test::TestPerspectiva>("Perspectiva");
        testMenu->RegisterTest<test::Test3D>("3D");
        testMenu->RegisterTest<test::TestMultiobject>("Multiobject");
        //testMenu->RegisterTest<test::TestPhong>("Phong (WIP)");
        testMenu->RegisterTest<test::TestImported>("Imported");



        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

            ImGui_ImplGlfwGL3_NewFrame();
            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != testCamera && ImGui::Button("Camera"))
                {
                    currentTest = testCamera;
                }
                    
                if (currentTest != testPlayground && ImGui::Button("Playground"))
                {
                    currentTest = testPlayground;
                }

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