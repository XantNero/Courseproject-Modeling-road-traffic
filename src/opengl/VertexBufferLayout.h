#ifndef _VERTEXBUFFERLAYOUT_H_
#define _VERTEXBUFFERLAYOUT_H_
#include <vector>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    bool normalized;
    unsigned int size;
};


class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout();
    ~VertexBufferLayout();
    void push(unsigned int gltype, unsigned int count, unsigned int size);
    unsigned int getStride() const;
    const std::vector<VertexBufferElement>& getElementArray() const;
};



#endif