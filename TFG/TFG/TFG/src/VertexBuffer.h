#pragma once
#include <vector>
class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(std::vector<double> data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};