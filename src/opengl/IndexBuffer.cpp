 #include "IndexBuffer.h"
 #include <GL/glew.h>
 #include "debug.h"
 
//set flag for static draw

 
IndexBuffer::IndexBuffer(unsigned int count, unsigned int* data)
    : m_Count(0), m_MaxCount(count)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), (void*)data,
        data == 0 ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
    if (data != 0)
        m_Count = count;
}
IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::addData(unsigned int count, unsigned int* data)
{
    GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int),
        count * sizeof(unsigned int), data));
    m_Count += count;
}

void IndexBuffer::ResetData()
{
    // GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
    //     m_Count * sizeof(unsigned int), 0));
    m_Count = 0;
}

void IndexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}
void IndexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::getCount() const
{
    return m_Count;
}