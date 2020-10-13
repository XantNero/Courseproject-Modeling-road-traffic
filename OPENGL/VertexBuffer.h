#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

class VertexBuffer
{
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};

#endif