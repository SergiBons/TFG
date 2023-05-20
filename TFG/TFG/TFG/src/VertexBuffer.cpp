#include "VertexBuffer.h"
#include "Renderer.h"



VertexBuffer::VertexBuffer(std::vector<double> data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, &data[0]));

}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1,&m_RendererID))
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
