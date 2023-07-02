#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "TestImported.h"
#include "Renderer.h"

#include <string>



namespace test {

	test::TestImported::TestImported()
        :m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f))),
        m_Rotation(glm::vec3(0.0f, 0.0f, 0.0f))
    {

        float w = 960.0f;
        float h = 540.0f;

        std::string nomFitxer = "res/Models/Enemy/Enemy1.obj";
        m_ObOBJ.LoadModel(const_cast<char*>(nomFitxer.c_str()));
        /*
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_VAO1->AddBuffer(*m_VertexBuffer1, layout);
        */
        //m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);
        GLCall(glEnable(GL_BLEND));

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
        GLCall(glShadeModel(GL_SMOOTH));
        //lights

        GLfloat position[] = { 0.0,0.0,200.0,1.0 };

        int i = 0;
        for (i = 1; i < 8; i++) m_Lumin[i].encesa = false;
        for (i = 0; i < 8; i++) {
            m_Lumin[i].encesa = false;
            m_Lumin[i].difusa[0] = 1.0f;	m_Lumin[i].difusa[1] = 1.0f;	m_Lumin[i].difusa[2] = 1.0f;	m_Lumin[i].difusa[3] = 1.0f;
            m_Lumin[i].especular[0] = 1.0f; m_Lumin[i].especular[1] = 1.0f; m_Lumin[i].especular[2] = 1.0f; m_Lumin[i].especular[3] = 1.0f;
        }

        // LLum 0: Atenuació constant (c=1), sobre l'eix Z, no restringida.
        m_Lumin[0].encesa = true;
        m_Lumin[0].difusa[0] = 1.0f;			m_Lumin[0].difusa[1] = 1.0f;			m_Lumin[0].difusa[2] = 1.0f;		m_Lumin[0].difusa[3] = 1.0f;
        m_Lumin[0].especular[0] = 1.0f;		m_Lumin[0].especular[1] = 1.0f;		m_Lumin[0].especular[2] = 1.0f;	m_Lumin[0].especular[3] = 1.0f;

        m_Lumin[0].posicio.R = 200.0;		m_Lumin[0].posicio.alfa = 90.0;		m_Lumin[0].posicio.beta = 0.0;		// Posició llum (x,y,z)=(0,0,200)
        m_Lumin[0].atenuacio.a = 0.0;		m_Lumin[0].atenuacio.b = 0.0;		m_Lumin[0].atenuacio.c = 1.0;		// Llum sense atenuació per distància (a,b,c)=(0,0,1)
        m_Lumin[0].restringida = false;
        m_Lumin[0].spotdirection[0] = 0.0;	m_Lumin[0].spotdirection[1] = 0.0;	m_Lumin[0].spotdirection[2] = 0.0;
        m_Lumin[0].spotcoscutoff = 0.0;		m_Lumin[0].spotexponent = 0.0;

        // LLum 1: Atenuació constant (c=1), sobre l'eix X, no restringida.
        m_Lumin[1].encesa = false;
        m_Lumin[1].difusa[0] = 1.0f;			m_Lumin[1].difusa[1] = 1.0f;			m_Lumin[1].difusa[2] = 1.0f;		m_Lumin[1].difusa[3] = 1.0f;
        m_Lumin[1].especular[0] = 1.0f;		m_Lumin[1].especular[1] = 1.0f;		m_Lumin[1].especular[2] = 1.0f;	m_Lumin[1].especular[3] = 1;

        m_Lumin[1].posicio.R = 75.0;			m_Lumin[1].posicio.alfa = 0.0;		m_Lumin[1].posicio.beta = 0.0;// (x,y,z)=(75,0,0)
        m_Lumin[1].atenuacio.a = 0.0;		m_Lumin[1].atenuacio.b = 0.0;		m_Lumin[1].atenuacio.c = 1.0;
        m_Lumin[1].restringida = false;
        m_Lumin[1].spotdirection[0] = 0.0;	m_Lumin[1].spotdirection[1] = 0.0;	m_Lumin[1].spotdirection[2] = 0.0;
        m_Lumin[1].spotcoscutoff = 0.0;		m_Lumin[1].spotexponent = 0.0;

        // LLum 2: Atenuació constant (c=1), sobre l'eix Y, no restringida.
        m_Lumin[2].encesa = false;
        m_Lumin[2].difusa[1] = 1.0f;			m_Lumin[2].difusa[1] = 1.0f;			m_Lumin[2].difusa[2] = 1.0f;		m_Lumin[2].difusa[3] = 1.0f;
        m_Lumin[2].especular[1] = 1.0f;		m_Lumin[2].especular[1] = 1.0f;		m_Lumin[2].especular[2] = 1.0f;	m_Lumin[2].especular[3] = 1;

        m_Lumin[2].posicio.R = 75.0;			m_Lumin[2].posicio.alfa = 0.0;		m_Lumin[2].posicio.beta = 90.0;	// (x,y,z)=(0,75,0)
        m_Lumin[2].atenuacio.a = 0.0;		m_Lumin[2].atenuacio.b = 0.0;		m_Lumin[2].atenuacio.c = 1.0;
        m_Lumin[2].restringida = false;
        m_Lumin[2].spotdirection[0] = 0.0;	m_Lumin[2].spotdirection[1] = 0.0;	m_Lumin[2].spotdirection[2] = 0.0;
        m_Lumin[2].spotcoscutoff = 0.0;		m_Lumin[2].spotexponent = 0.0;

        // LLum 3: Atenuació constant (c=1), sobre l'eix Y=X, no restringida.
        m_Lumin[3].encesa = false;
        m_Lumin[3].difusa[0] = 1.0f;			m_Lumin[2].difusa[1] = 1.0f;			m_Lumin[3].difusa[2] = 1.0f;		m_Lumin[3].difusa[3] = 1.0f;
        m_Lumin[3].especular[0] = 1.0f;		m_Lumin[2].especular[1] = 1.0f;		m_Lumin[3].especular[2] = 1.0f;	m_Lumin[3].especular[3] = 1;

        m_Lumin[3].posicio.R = 75.0;			m_Lumin[3].posicio.alfa = 45.0;		m_Lumin[3].posicio.beta = 45.0;// (x,y,z)=(75,75,75)
        m_Lumin[3].atenuacio.a = 0.0;		m_Lumin[3].atenuacio.b = 0.0;		m_Lumin[3].atenuacio.c = 1.0;
        m_Lumin[3].restringida = false;
        m_Lumin[3].spotdirection[0] = 0.0;	m_Lumin[3].spotdirection[1] = 0.0;	m_Lumin[3].spotdirection[2] = 0.0;
        m_Lumin[3].spotcoscutoff = 0.0;		m_Lumin[3].spotexponent = 0.0;

        // LLum 4: Atenuació constant (c=1), sobre l'eix -Z, no restringida.
        m_Lumin[4].encesa = false;
        m_Lumin[4].difusa[0] = 1.0f;			m_Lumin[4].difusa[1] = 1.0f;			m_Lumin[4].difusa[2] = 1.0f;		m_Lumin[4].difusa[3] = 1.0f;
        m_Lumin[4].especular[0] = 1.0f;		m_Lumin[4].especular[1] = 1.0f;		m_Lumin[4].especular[2] = 1.0f;	m_Lumin[4].especular[3] = 1;

        m_Lumin[4].posicio.R = 75.0;			m_Lumin[4].posicio.alfa = -90.0;		m_Lumin[4].posicio.beta = 0.0;// (x,y,z)=(0,0,-75)
        m_Lumin[4].atenuacio.a = 0.0;		m_Lumin[4].atenuacio.b = 0.0;		m_Lumin[4].atenuacio.c = 1.0;
        m_Lumin[4].restringida = false;
        m_Lumin[4].spotdirection[0] = 0.0;	m_Lumin[4].spotdirection[1] = 0.0;	m_Lumin[4].spotdirection[2] = 0.0;
        m_Lumin[4].spotcoscutoff = 0.0;		m_Lumin[4].spotexponent = 0.0;

        // LLum #5:
        m_Lumin[5].encesa = false;
        m_Lumin[5].difusa[0] = 1.0f;			m_Lumin[5].difusa[1] = 1.0f;			m_Lumin[5].difusa[2] = 1.0f;		m_Lumin[5].difusa[3] = 1.0f;
        m_Lumin[5].especular[0] = 1.0f;		m_Lumin[5].especular[1] = 1.0f;		m_Lumin[5].especular[2] = 1.0f;	m_Lumin[5].especular[3] = 1;

        m_Lumin[5].posicio.R = 0.0;			m_Lumin[5].posicio.alfa = 0.0;		m_Lumin[5].posicio.beta = 0.0; // Cap posició definida
        m_Lumin[5].atenuacio.a = 0.0;		m_Lumin[5].atenuacio.b = 0.0;		m_Lumin[5].atenuacio.c = 1.0;
        m_Lumin[5].restringida = false;
        m_Lumin[5].spotdirection[0] = 0.0;	m_Lumin[5].spotdirection[1] = 0.0;	m_Lumin[5].spotdirection[2] = 0.0;
        m_Lumin[5].spotcoscutoff = 0.0;		m_Lumin[5].spotexponent = 0.0;

        // LLum #6: Llum Vaixell, configurada a la funció vaixell() en escena.cpp.
        m_Lumin[6].encesa = false;
        m_Lumin[6].difusa[0] = 1.0f;			m_Lumin[6].difusa[1] = 1.0f;			m_Lumin[6].difusa[2] = 1.0f;		m_Lumin[6].difusa[3] = 1.0f;
        m_Lumin[6].especular[0] = 1.0f;		m_Lumin[6].especular[1] = 1.0f;		m_Lumin[6].especular[2] = 1.0f;	m_Lumin[6].especular[3] = 1;

        m_Lumin[6].posicio.R = 0.0;			m_Lumin[6].posicio.alfa = 0.0;		m_Lumin[6].posicio.beta = 0.0; // Cap posició definida, definida en funció vaixell() en escena.cpp
        m_Lumin[6].atenuacio.a = 0.0;		m_Lumin[6].atenuacio.b = 0.0;		m_Lumin[6].atenuacio.c = 1.0;
        m_Lumin[6].restringida = false;
        m_Lumin[6].spotdirection[0] = 0.0;	m_Lumin[6].spotdirection[1] = 0.0;	m_Lumin[6].spotdirection[2] = 0.0;
        m_Lumin[6].spotcoscutoff = 0.0;		m_Lumin[6].spotexponent = 0.0;

        // LLum #7: Llum Far, configurada a la funció faro() en escena.cpp.
        m_Lumin[7].encesa = false;
        m_Lumin[7].difusa[0] = 1.0f;			m_Lumin[7].difusa[1] = 1.0f;			m_Lumin[7].difusa[2] = 1.0f;		m_Lumin[7].difusa[3] = 1.0f;
        m_Lumin[7].especular[0] = 1.0f;		m_Lumin[7].especular[1] = 1.0f;		m_Lumin[7].especular[2] = 1.0f;	m_Lumin[7].especular[3] = 1;

        m_Lumin[7].posicio.R = 0.0;			m_Lumin[7].posicio.alfa = 0.0;		m_Lumin[7].posicio.beta = 0.0; // Cap posició definida, definida en funció faro() en escena.cpp
        m_Lumin[7].atenuacio.a = 0.0;		m_Lumin[7].atenuacio.b = 0.0;		m_Lumin[7].atenuacio.c = 1.0;
        m_Lumin[7].restringida = false;
        m_Lumin[7].spotdirection[0] = 0.0;	m_Lumin[7].spotdirection[1] = 0.0;	m_Lumin[7].spotdirection[2] = 0.0;
        m_Lumin[7].spotcoscutoff = 0.0;		m_Lumin[7].spotexponent = 0.0;

        //m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

        m_Shader = std::make_unique<Shader>("res/Shaders/Phong.shader");
        m_Shader->Bind();
        GLfloat ambientg[] = { .5,.5,.5,1.0 };

        GLCall(glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientg));
        m_Shader->SetUniform1i("fixedLight", true);
        m_Shader->SetUniform1i("textur", true);
        m_Shader->SetUniform1i("flag_invert_y", false);
        m_Shader->SetUniform1i("fixedLight", true); //
        m_Shader->SetUniform4f("LightModelAmbient", ambientg[0], ambientg[1], ambientg[2], ambientg[3]);
    }

	test::TestImported::~TestImported()
	{

	}

	void test::TestImported::OnUpdate(float deltaTime)
	{
	}

	void test::TestImported::OnRender()
	{
        GLCall(glClearColor(0.3f, 0.3f, 0.3f, 1.0f));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        Renderer renderer;
        GLdouble angv, angh;
        GLfloat position[] = { 0.0,0.0,200.0,1.0 };
        angv = m_Lumin[0].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[0].posicio.beta * 3.14159 / 180;

        // Conversió Coord. esfèriques -> Coord. cartesianes per a la posició de la llum
        position[0] = m_Lumin[0].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[0].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[0].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].diffuse"), m_Lumin[0].difusa[0], m_Lumin[0].difusa[1], m_Lumin[0].difusa[2], m_Lumin[0].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].specular"), m_Lumin[0].especular[0], m_Lumin[0].especular[1], m_Lumin[0].especular[2], m_Lumin[0].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].attenuation"), m_Lumin[0].atenuacio.a, m_Lumin[0].atenuacio.b, m_Lumin[0].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].restricted"), m_Lumin[0].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].spotDirection"), m_Lumin[0].spotdirection[0], m_Lumin[0].spotdirection[1], m_Lumin[0].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].spotCosCutoff"), m_Lumin[0].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].spotExponent"), m_Lumin[0].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].sw_light"), m_Lumin[0].encesa);

        angv = m_Lumin[1].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[1].posicio.beta * 3.14159 / 180;

        // Conversió Coord. esfèriques -> Coord. cartesianes per a la posició de la llum
        position[0] = m_Lumin[1].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[1].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[1].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].diffuse"), m_Lumin[1].difusa[0], m_Lumin[1].difusa[1], m_Lumin[1].difusa[2], m_Lumin[1].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].specular"), m_Lumin[1].especular[0], m_Lumin[1].especular[1], m_Lumin[1].especular[2], m_Lumin[1].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].attenuation"), m_Lumin[1].atenuacio.a, m_Lumin[1].atenuacio.b, m_Lumin[1].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].restricted"), m_Lumin[1].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].spotDirection"), m_Lumin[1].spotdirection[0], m_Lumin[1].spotdirection[1], m_Lumin[1].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].spotCosCutoff"), m_Lumin[1].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].spotExponent"), m_Lumin[1].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].sw_light"), m_Lumin[1].encesa);

        angv = m_Lumin[2].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[2].posicio.beta * 3.14159 / 180;

        // Conversió Coord. esfèriques -> Coord. cartesianes per a la posició de la llum
        position[0] = m_Lumin[2].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[2].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[2].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].diffuse"), m_Lumin[2].difusa[0], m_Lumin[2].difusa[1], m_Lumin[2].difusa[2], m_Lumin[2].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].specular"), m_Lumin[2].especular[0], m_Lumin[2].especular[1], m_Lumin[2].especular[2], m_Lumin[2].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].attenuation"), m_Lumin[2].atenuacio.a, m_Lumin[2].atenuacio.b, m_Lumin[2].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].restricted"), m_Lumin[2].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].spotDirection"), m_Lumin[2].spotdirection[0], m_Lumin[2].spotdirection[1], m_Lumin[2].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].spotCosCutoff"), m_Lumin[2].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].spotExponent"), m_Lumin[2].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].sw_light"), m_Lumin[2].encesa);

        angv = m_Lumin[3].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[3].posicio.beta * 3.14159 / 180;

        // Conversió Coord. esfèriques -> Coord. cartesianes per a la posició de la llum
        position[0] = m_Lumin[3].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[3].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[3].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].diffuse"), m_Lumin[3].difusa[0], m_Lumin[3].difusa[1], m_Lumin[3].difusa[2], m_Lumin[3].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].specular"), m_Lumin[3].especular[0], m_Lumin[3].especular[1], m_Lumin[3].especular[2], m_Lumin[3].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].attenuation"), m_Lumin[3].atenuacio.a, m_Lumin[3].atenuacio.b, m_Lumin[3].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].restricted"), m_Lumin[3].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].spotDirection"), m_Lumin[3].spotdirection[0], m_Lumin[3].spotdirection[1], m_Lumin[3].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].spotCosCutoff"), m_Lumin[3].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].spotExponent"), m_Lumin[3].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].sw_light"), m_Lumin[3].encesa);

        angv = m_Lumin[4].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[4].posicio.beta * 3.14159 / 180;

        // Conversió Coord. esfèriques -> Coord. cartesianes per a la posició de la llum
        position[0] = m_Lumin[4].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[4].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[4].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].diffuse"), m_Lumin[4].difusa[0], m_Lumin[4].difusa[1], m_Lumin[4].difusa[2], m_Lumin[4].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].specular"), m_Lumin[4].especular[0], m_Lumin[4].especular[1], m_Lumin[4].especular[2], m_Lumin[4].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].attenuation"), m_Lumin[4].atenuacio.a, m_Lumin[4].atenuacio.b, m_Lumin[4].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].restricted"), m_Lumin[4].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].spotDirection"), m_Lumin[4].spotdirection[0], m_Lumin[4].spotdirection[1], m_Lumin[4].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].spotCosCutoff"), m_Lumin[4].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].spotExponent"), m_Lumin[4].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].sw_light"), m_Lumin[4].encesa);

        angv = m_Lumin[5].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[5].posicio.beta * 3.14159 / 180;

        // Conversió Coord. esfèriques -> Coord. cartesianes per a la posició de la llum
        position[0] = m_Lumin[5].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[5].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[5].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].diffuse"), m_Lumin[5].difusa[0], m_Lumin[5].difusa[1], m_Lumin[5].difusa[2], m_Lumin[5].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].specular"), m_Lumin[5].especular[0], m_Lumin[5].especular[1], m_Lumin[5].especular[2], m_Lumin[5].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].attenuation"), m_Lumin[5].atenuacio.a, m_Lumin[5].atenuacio.b, m_Lumin[5].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].restricted"), m_Lumin[5].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].spotDirection"), m_Lumin[5].spotdirection[0], m_Lumin[5].spotdirection[1], m_Lumin[5].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].spotCosCutoff"), m_Lumin[5].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].spotExponent"), m_Lumin[5].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].sw_light"), m_Lumin[5].encesa);

        angv = m_Lumin[6].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[6].posicio.beta * 3.14159 / 180;

        // Conversió Coord. esfèriques -> Coord. cartesianes per a la posició de la llum
        position[0] = m_Lumin[6].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[6].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[6].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].diffuse"), m_Lumin[6].difusa[0], m_Lumin[6].difusa[1], m_Lumin[6].difusa[2], m_Lumin[6].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].specular"), m_Lumin[6].especular[0], m_Lumin[6].especular[1], m_Lumin[6].especular[2], m_Lumin[6].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].attenuation"), m_Lumin[6].atenuacio.a, m_Lumin[6].atenuacio.b, m_Lumin[6].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].restricted"), m_Lumin[6].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].spotDirection"), m_Lumin[6].spotdirection[0], m_Lumin[6].spotdirection[1], m_Lumin[6].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].spotCosCutoff"), m_Lumin[6].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].spotExponent"), m_Lumin[6].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].sw_light"), m_Lumin[6].encesa);

        angv = m_Lumin[6].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[6].posicio.beta * 3.14159 / 180;

        // Conversió Coord. esfèriques -> Coord. cartesianes per a la posició de la llum
        position[0] = m_Lumin[0].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[0].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[0].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].diffuse"), m_Lumin[0].difusa[0], m_Lumin[0].difusa[1], m_Lumin[0].difusa[2], m_Lumin[0].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].specular"), m_Lumin[0].especular[0], m_Lumin[0].especular[1], m_Lumin[0].especular[2], m_Lumin[0].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].attenuation"), m_Lumin[0].atenuacio.a, m_Lumin[0].atenuacio.b, m_Lumin[0].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].restricted"), m_Lumin[0].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].spotDirection"), m_Lumin[0].spotdirection[0], m_Lumin[0].spotdirection[1], m_Lumin[0].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].spotCosCutoff"), m_Lumin[0].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].spotExponent"), m_Lumin[0].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].sw_light"), m_Lumin[0].encesa);


        m_Shader->Bind();


        {
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 normal = glm::mat4(1.0f);
            //model = glm::rotate(model, glm::radians(-55.0f), m_TranslationA);
            model = glm::translate(model, m_Translation);
            model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            normal = glm::transpose(glm::inverse(m_View * model));

            m_Shader->SetUniformMat4f("normalMatrix", normal);
            m_Shader->SetUniformMat4f("viewMatrix", m_View);
            m_Shader->SetUniformMat4f("modelMatrix", model);
            m_Shader->SetUniformMat4f("projectionMatrix", m_Proj); //
            m_ObOBJ.draw_TriVAO_OBJ(m_Shader->GetID());
            //renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
            //renderer.DrawRaw(*m_VAO, *m_Shader, 12);
        }
	}

	void test::TestImported::OnImGuiRender()
	{
        ImGui::SliderFloat3("Translation", &m_Translation.x, -10.0f, 10.0f);
        ImGui::SliderFloat3("Rotation", &m_Rotation.x, 0.0f, 360.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	}
}