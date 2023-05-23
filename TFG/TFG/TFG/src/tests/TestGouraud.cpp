#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "TestGouraud.h"
#include "Renderer.h"
#include "objLoader.h"

struct CEsfe3D
{
    GLdouble R;
    GLdouble alfa;
    GLdouble beta;
};

struct CAtenua
{
    GLdouble a;
    GLdouble b;
    GLdouble c;
};


struct LLUM
{
    bool encesa;				// Booleana que controla si la llum és encesa [TRUE] o no [FALSE]
    CEsfe3D posicio;			// Posició d ela foont de llum en coordenades esfèriques.
    GLfloat difusa[4];			// Intensitat difusa de la font de llum (r,g,b,a)
    GLfloat especular[4];		// Intensitat especular de la font de llum (r,g,b,a)
    CAtenua atenuacio;			// Coeficients de l'equació d'atenuació de la llum fatt=1/(ad2+bd+c)
    bool restringida;			// Booleana que indica si la font de llum és restringida [TRUE] i per tant són vàlids els coeficients posteriors o no [FALSE].
    GLfloat spotdirection[3];	// Vector de direció de la font de llum restringida (x,y,z).
    GLfloat spotcoscutoff;		// Coseno de l'angle d'obertura de la font de llum restringida.
    GLfloat spotexponent;		// Exponent que indica l'atenuació de la font del centre de l'eix a l'exterior, segons model de Warn.
};

namespace test {

	test::TestGouraud::TestGouraud()
        :m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f))),
        m_Rotation(glm::vec3(0.0f, 0.0f, 0.0f))
    {
    //GLCall(glEnable(GL_DEPTH_TEST));
    
    

    float positions[] = {
              0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
              1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

              0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 1.0f, 1.0f,

              0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
              1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

              0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
              1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    };

    unsigned int indices[] = {
    0,1,2,
    0,1,3,
    0,2,3,
    1,2,3
    };

    float positions2[] = {
         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
    GLCall(glShadeModel(GL_SMOOTH));
    m_VAO = std::make_unique<VertexArray>();
    m_VAO1 = std::make_unique<VertexArray>();

    m_VertexBuffer = std::make_unique<VertexBuffer>(positions2, 36 * 5 * sizeof(float));
    m_VertexBuffer1 = std::make_unique<VertexBuffer>(positions, 12 * 5 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_VAO->AddBuffer(*m_VertexBuffer, layout);
    m_VAO1->AddBuffer(*m_VertexBuffer1, layout);
    //m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

    m_Shader = std::make_unique<Shader>("res/Shaders/Gouraud.shader");
    m_Shader->Bind();
    GLfloat ambientg[] = { .5,.5,.5,1.0 };

    GLCall(glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientg));
    m_Shader->SetUniform1i("u_Texture1", 0);//Es a dir, si al bind assginem el slot 1, aqui ficariem un 1.

    m_Texture = std::make_unique<Texture>("res/textures/testure.png");
    //m_Shader->SetUniform1i("fixedLight", true);
    m_Shader->SetUniform1i("textur", true);
    m_Shader->SetUniform1i("flag_invert_y", true);



    //m_Shader->SetUniform1i("u_Texture2", 0);//Es a dir, si al bind assginem el slot 1, aqui ficariem un 1.
    }

	test::TestGouraud::~TestGouraud()
	{
	}

	void test::TestGouraud::OnUpdate(float deltaTime)
	{
	}

	void test::TestGouraud::OnRender()
	{
        GLCall(glClearColor(0.3f, 0.3f, 0.3f, 1.0f));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        GLdouble angv, angh;
        Renderer renderer;












        m_Texture->Bind();//Si passem argument, l'hem de settejar al uniform just a sota
        m_Shader->Bind();
        
        {
            m_VAO->Bind();
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 normal = glm::mat4(1.0f);

            //model = glm::rotate(model, glm::radians(-55.0f), m_TranslationA);
            model = glm::translate(model, m_Translation);
            model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            normal = glm::transpose(glm::inverse(m_View * model));

            
            //m_Shader->SetUniformMat4f("u_NormalMatrix", normal);
            m_Shader->SetUniformMat4f("u_ModelMatrix", model);  
            m_Shader->SetUniformMat4f("u_ViewMatrix", m_View);
            m_Shader->SetUniformMat4f("u_ProjectionMatrix", m_Proj);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            //renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
            //renderer.DrawRaw(*m_VAO, *m_Shader, 12);
        }
        /*
        {
            m_VAO1->Bind();
            glm::mat4 model = glm::mat4(1.0f);

            //model = glm::rotate(model, glm::radians(-55.0f), m_TranslationA);
            model = glm::translate(model, m_Translation);
            model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            m_Shader->SetUniformMat4f("u_ModelMatrix", model);
            m_Shader->SetUniformMat4f("u_ViewMatrix", m_View);
            m_Shader->SetUniformMat4f("u_ProjectionMatrix", m_Proj);
            glDrawArrays(GL_TRIANGLES, 0, 12);
            //renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
            //renderer.DrawRaw(*m_VAO, *m_Shader, 12);
        }
        */
	}

	void test::TestGouraud::OnImGuiRender()
	{
        ImGui::SliderFloat3("Translation", &m_Translation.x, -5.0f, 5.0f);
        ImGui::SliderFloat3("Rotation", &m_Rotation.x, 0.0f, 360.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	}
}