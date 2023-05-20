#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "TestPlayground.h"
#include "Renderer.h"

namespace test {

	test::TestPlayground::TestPlayground()
        :m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)))
    {
        double size = 10.0f;
        std::vector<double> positions = {
             size,  size,  size, -size,  size,  size, -size, -size,  size,      // v0-v1-v2 (front)
            -size, -size,  size,  size, -size,  size,  size,  size,  size,      // v2-v3-v0
             size,  size,  size,  size, -size,  size,  size, -size, -size,      // v0-v3-v4 (right)
             size, -size, -size,  size,  size, -size,  size,  size,  size,      // v4-v5-v0
             size,  size,  size,  size,  size, -size, -size,  size, -size,      // v0-v5-v6 (top)
            -size,  size, -size, -size,  size,  size,  size,  size,  size,      // v6-v1-v0
            -size,  size,  size, -size,  size, -size, -size, -size, -size,      // v1-v6-v7 (left)
            -size, -size, -size, -size, -size,  size, -size,  size,  size,      // v7-v2-v1
            -size, -size, -size,  size, -size, -size,  size, -size,  size,      // v7-v4-v3 (bottom)
             size, -size,  size, -size, -size,  size, -size, -size, -size,      // v3-v2-v7
             size, -size, -size, -size, -size, -size, -size,  size, -size,      // v4-v7-v6 (back)
            -size,  size, -size,  size,  size, -size,  size, -size, -size };	// v6-v5-v4


        std::vector<double> normals = {
        0,  0,  1,  0,  0,  1,  0,  0,  1,   // v0-v1-v2 (front)
        0,  0,  1,  0,  0,  1,  0,  0,  1,   // v2-v3-v0
        1,  0,  0,  1,  0,  0,  1,  0,  0,   // v0-v3-v4 (right)
        1,  0,  0,  1,  0,  0,  1,  0,  0,   // v4-v5-v0
        0,  1,  0,  0,  1,  0,  0,  1,  0,   // v0-v5-v6 (top)
        0,  1,  0,  0,  1,  0,  0,  1,  0,   // v6-v1-v0
        -1,  0,  0, -1,  0,  0, -1,  0,  0,   // v1-v6-v7 (left)
        -1,  0,  0, -1,  0,  0, -1,  0,  0,   // v7-v2-v1
        0, -1,  0,  0, -1,  0,  0, -1,  0,   // v7-v4-v3 (bottom)
        0, -1,  0,  0, -1,  0,  0, -1,  0,   // v3-v2-v7
        0,  0, -1,  0,  0, -1,  0,  0, -1,   // v4-v7-v6 (back)
        0,  0, -1,  0,  0, -1,  0,  0, -1 }; // v6-v5-v4

        unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
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

        m_Shader = std::make_unique<Shader>("res/Shaders/Phong.shader");
        m_Shader->Bind();
        m_Texture = std::make_unique<Texture>("res/textures/testure.png");
        m_Shader->SetUniform1i("u_Texture", 0);//Es a dir, si al bind assginem el slot 1, aqui ficariem un 1.

        //m_Shader->SetUniform1i("u_Texture2", 0);//Es a dir, si al bind assginem el slot 1, aqui ficariem un 1.
    }

	test::TestPlayground::~TestPlayground()
	{
	}

	void test::TestPlayground::OnUpdate(float deltaTime)
	{
	}

	void test::TestPlayground::OnRender()
	{
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_Texture->Bind();//Si passem argument, l'hem de settejar al uniform just a sota

        {
            glm::mat4 model = glm::mat4(1.0f);

            //model = glm::rotate(model, glm::radians(-55.0f), m_TranslationA);
            model = glm::translate(model, m_Translation);
            model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_ModelMatrix", model);
            m_Shader->SetUniformMat4f("u_ViewMatrix", m_View);
            m_Shader->SetUniformMat4f("u_ProjectionMatrix", m_Proj);

            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
	}

	void test::TestPlayground::OnImGuiRender()
	{
        ImGui::SliderFloat3("Translation", &m_Translation.x, -10.0f, 10.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	}
}