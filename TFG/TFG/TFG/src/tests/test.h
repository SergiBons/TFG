#pragma once

#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace test  {

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

	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

	};


	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);

		void OnImGuiRender() override;
		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() {return new T();  }));
		}



	private:
		Test*& m_CurrentTest;
		std::vector < std::pair<std::string, std::function<Test*()>>> m_Tests;
	};

}