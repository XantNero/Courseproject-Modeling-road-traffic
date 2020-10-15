#include "VertexBufferLayout.h"
#include "debug.h"

VertexBufferLayout::VertexBufferLayout()
: m_Elements(), m_Stride(0) { }

VertexBufferLayout::~VertexBufferLayout() { }

void VertexBufferLayout::push(unsigned int gltype, unsigned int count, unsigned int size)
{
    m_Elements.push_back({gltype, count, false, size});
    m_Stride += size;
}
unsigned int VertexBufferLayout::getStride() const
{
    return m_Stride;
}
const std::vector<VertexBufferElement>& VertexBufferLayout::getElementArray() const
{
    return m_Elements;
}