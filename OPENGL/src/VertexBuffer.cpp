#include "VertexBuffer.h"
#include <GL/glew.h>
#include "debug.h"

//set flag for static draw


VertexBuffer::VertexBuffer(unsigned int size, const void* data) 
    :m_Offset(0), m_MaxSize(size)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, data == 0 ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
}
VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::addData(unsigned int size, const void* data)
{
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, m_Offset, size, data));
    m_Offset += size;
}

void VertexBuffer::resetData()
{
    //GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_Offset, 0));
    m_Offset = 0;
}

void VertexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}
void VertexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}