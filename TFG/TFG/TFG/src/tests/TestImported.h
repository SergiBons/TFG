#pragma once

#include "Test.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "objLoader.h"

#include <memory>
namespace test {


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
		bool encesa;				// Booleana que controla si la llum �s encesa [TRUE] o no [FALSE]
		CEsfe3D posicio;			// Posici� d ela foont de llum en coordenades esf�riques.
		GLfloat difusa[4];			// Intensitat difusa de la font de llum (r,g,b,a)
		GLfloat especular[4];		// Intensitat especular de la font de llum (r,g,b,a)
		CAtenua atenuacio;			// Coeficients de l'equaci� d'atenuaci� de la llum fatt=1/(ad2+bd+c)
		bool restringida;			// Booleana que indica si la font de llum �s restringida [TRUE] i per tant s�n v�lids els coeficients posteriors o no [FALSE].
		GLfloat spotdirection[3];	// Vector de direci� de la font de llum restringida (x,y,z).
		GLfloat spotcoscutoff;		// Coseno de l'angle d'obertura de la font de llum restringida.
		GLfloat spotexponent;		// Exponent que indica l'atenuaci� de la font del centre de l'eix a l'exterior, segons model de Warn.
	};

	class TestImported : public Test
	{
	public:
		TestImported();
		~TestImported();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		LLUM m_Lumin[8];
		glm::vec3 m_Rotation;
		glm::vec3 m_Translation;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;		
		std::unique_ptr<VertexArray> m_VAO1;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer1;
		COBJModel m_ObOBJ;
		glm::mat4 m_Proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	};


}
