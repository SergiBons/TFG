#pragma once
#include <GL/glew.h>
#include <vector>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
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

class Renderer
{
public:
    void Clear()const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void DrawRaw(const VertexArray& va, const Shader& shader, const int count) const;
};