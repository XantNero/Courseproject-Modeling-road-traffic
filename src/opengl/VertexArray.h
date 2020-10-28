#ifndef _VERTEXARRAY_H_
#define _VERTEXARRAY_H_
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
class VertexArray
{
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;
    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};

#endif