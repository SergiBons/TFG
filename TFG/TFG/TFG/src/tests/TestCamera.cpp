#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "TestCamera.h"
#include "Renderer.h"

#include <string>



namespace test {

    test::TestCamera::TestCamera(GLFWwindow* window)
        :m_Proj(glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f))),
        m_Rotation(glm::vec3(0.0f, 0.0f, 0.0f)), m_Window(window)
    {

        std::string nomFitxer = "res/Models/MC/MainChar.obj";
        m_ObOBJ.LoadModel(const_cast<char*>(nomFitxer.c_str()));
        /*
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_VAO1->AddBuffer(*m_VertexBuffer1, layout);
        */
        //m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

            









        m_Shader = std::make_unique<Shader>("res/Shaders/PerspectiveTest.shader");
        m_Shader->Bind();
        m_Shader->SetUniform1i("u_Texture1", 0);//Es a dir, si al bind assginem el slot 1, aqui ficariem un 1.
        m_Texture = std::make_unique<Texture>("res/textures/testure.png");


        //m_Shader->SetUniform1i("u_Texture2", 0);//Es a dir, si al bind assginem el slot 1, aqui ficariem un 1.
    
    
    }

	test::TestCamera::~TestCamera()
	{

	}

	void test::TestCamera::OnUpdate(float deltaTime)
	{
        int stateZ = glfwGetKey(m_Window, GLFW_KEY_W);
        if (stateZ == GLFW_PRESS)
        {
            m_Translation.z = 0.05;
        }
        else
        {
            stateZ = glfwGetKey(m_Window, GLFW_KEY_S);
            if (stateZ == GLFW_PRESS)
            {
                m_Translation.z = -0.05;
            }
            else
                m_Translation.z = 0.00;
        }
        int stateX = glfwGetKey(m_Window, GLFW_KEY_D);
        if (stateX == GLFW_PRESS)
        {
            m_Translation.x = -0.05;
        }
        else
        {
            stateX = glfwGetKey(m_Window, GLFW_KEY_A);
            if (stateX == GLFW_PRESS)
            {
                m_Translation.x = 0.05;
            }
            else
                m_Translation.x = 0.00;
        }

	}

	void test::TestCamera::OnRender()
	{
        GLCall(glClearColor(0.3f, 0.3f, 0.3f, 1.0f));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        Renderer renderer;

        m_Texture->Bind();//Si passem argument, l'hem de settejar al uniform just a sota
        m_Shader->Bind();

        {
            glm::mat4 model = glm::mat4(1.0f);

            //model = glm::rotate(model, glm::radians(-55.0f), m_TranslationA);
            model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            m_View = glm::translate(m_View, m_Translation);
            m_Shader->SetUniformMat4f("u_ModelMatrix", model);
            m_Shader->SetUniformMat4f("u_ViewMatrix", m_View);
            m_Shader->SetUniformMat4f("u_ProjectionMatrix", m_Proj);
            m_ObOBJ.draw_TriVAO_OBJ(m_Shader->GetID());
            //renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
            //renderer.DrawRaw(*m_VAO, *m_Shader, 12);
        }
        const int scancode = glfwGetKeyScancode(GLFW_KEY_X);
	}

	void test::TestCamera::OnImGuiRender()
	{
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	}
}