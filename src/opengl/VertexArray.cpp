#include "VertexArray.h"
#include <GL/glew.h>
#include "debug.h"
#include <iostream>


VertexArray::VertexArray() 
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
}
VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}
void VertexArray::unbind() const
{
    GLCall(glBindVertexArray(0));
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout& layout)
{
    bind();
    vb.bind();
    const auto& elements = layout.getElementArray();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); ++i) {
        const auto& element = elements[i];
        GLCall(glEnableVertexArrayAttrib(m_RendererID, i));
        //std::cout << i << ' ' << element.count << ' ' << element.type << " " << element.normalized << ' ' << layout.getStride() << ' ' << offset << '\n';
        GLCall(glVertexAttribPointer(i, element.count, element.type,
            element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), (void*)offset));
        offset += element.size;
    }
    // GLCall(glEnableVertexAttribArray(0));
    // GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));
}