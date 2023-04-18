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
        float positions[] = {
                100.0f, 100.0f, 0.0f, 0.0f,
                200.0f, 100.0f, 1.0f, 0.0f,
                200.0f, 200.0f, 1.0f, 1.0f,
                100.0f, 200.0f, 0.0f, 1.0f
        };


        unsigned int indices[] = {
        0,1,2,
        2,3,0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
        glm::mat4 mvp = proj * view * model;
        

        Shader shader("res/Shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4f("u_MVP",mvp);
 
        Texture texture("res/textures/testure.png");
        texture.Bind();//Si passem argument, l'hem de settejar al uniform just a sota
        shader.SetUniform1i("u_Texture", 0);//Es a dir, si al bind assginem el slot 1, aqui ficariem un 1.

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();
  

        Renderer renderer;

        float r = 0.0f;
        float inc = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();



            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);



            renderer.Draw(va, ib, shader);
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            if (r >= 1.0f)
                inc = -0.01f;
            else if (r <= 0.0f)
                inc = 0.01f;
            r += inc;
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}