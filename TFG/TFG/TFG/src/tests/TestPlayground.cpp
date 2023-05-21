#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "TestPlayground.h"
#include "Renderer.h"

namespace test {

	test::TestPlayground::TestPlayground()
        :m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f))),
        m_Rotation(-55.0f)
    {
     
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
        ImGui::SliderFloat3("Translation", &m_Translation.x, -100.0f, 100.0f);
        ImGui::SliderFloat("Rotation", &m_Rotation, -100.0f, 100.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	}
}