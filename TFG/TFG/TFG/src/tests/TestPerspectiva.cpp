#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "TestPerspectiva.h"
#include "Renderer.h"

namespace test {

	test::TestPerspectiva::TestPerspectiva()
        :m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f))),
        m_Rotation(-55.0f)
    {
        //GLCall(glEnable(GL_DEPTH_TEST));

        float positions[] = {
                  -0.5f, -0.5f, 0.0f, 0.0f,
                  0.5f, -0.5f, 1.0f, 0.0f,
                  0.5f, 0.5f, 1.0f, 1.0f,
                  -0.5f, 0.5f, 0.0f, 1.0f
        };




        unsigned int indices[] = {
        0,1,2,
        2,3,0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


        m_VAO = std::make_unique<VertexArray>();


        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        m_Shader = std::make_unique<Shader>("res/Shaders/PerspectiveTest.shader");
        m_Shader->Bind();
        m_Shader->SetUniform1i("u_Texture1", 0);//Es a dir, si al bind assginem el slot 1, aqui ficariem un 1.
        //m_Texture = std::make_unique<Texture>("res/textures/testure.png");
        m_Texture = std::make_unique<Texture>("res/textures/testure.png");  


        //m_Shader->SetUniform1i("u_Texture2", 0);//Es a dir, si al bind assginem el slot 1, aqui ficariem un 1.
    }

	test::TestPerspectiva::~TestPerspectiva()
	{
	}

	void test::TestPerspectiva::OnUpdate(float deltaTime)
	{
	}

	void test::TestPerspectiva::OnRender()
	{
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        Renderer renderer;

        m_Texture->Bind();//Si passem argument, l'hem de settejar al uniform just a sota
        m_Shader->Bind();
        {
            glm::mat4 model = glm::mat4(1.0f);

            //model = glm::rotate(model, glm::radians(-55.0f), m_TranslationA);
            model = glm::translate(model, m_Translation);
            model = glm::rotate(model, glm::radians(m_Rotation), glm::vec3(1.0f, 0.0f, 0.0f));
            m_Shader->SetUniformMat4f("u_ModelMatrix", model);
            m_Shader->SetUniformMat4f("u_ViewMatrix", m_View);
            m_Shader->SetUniformMat4f("u_ProjectionMatrix", m_Proj);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
            //renderer.DrawRaw(*m_VAO, *m_Shader, 12);
        }
	}

	void test::TestPerspectiva::OnImGuiRender()
	{
        ImGui::SliderFloat3("Translation", &m_Translation.x, -100.0f, 100.0f);
        ImGui::SliderFloat("Rotation", &m_Rotation, -100.0f, 100.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	}
}