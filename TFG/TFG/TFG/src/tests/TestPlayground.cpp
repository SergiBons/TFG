#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "TestPlayground.h"
#include "Renderer.h"
#include "objLoader.h"

namespace test {

	test::TestPlayground::TestPlayground()
        :m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f))),
        m_Rotation(glm::vec3(0.0f, 0.0f, 0.0f))
    {
    //GLCall(glEnable(GL_DEPTH_TEST));
    
    
    }

	test::TestPlayground::~TestPlayground()
	{
	}

	void test::TestPlayground::OnUpdate(float deltaTime)
	{
	}

	void test::TestPlayground::OnRender()
	{
       
	}

	void test::TestPlayground::OnImGuiRender()
	{
        ImGui::SliderFloat3("Translation", &m_Translation.x, -5.0f, 5.0f);
        ImGui::SliderFloat3("Rotation", &m_Rotation.x, 0.0f, 360.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	}
}