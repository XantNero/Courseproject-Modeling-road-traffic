#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

class VertexBuffer
{
private:
    unsigned int m_RendererID;
    int m_Offset;
    unsigned int m_MaxSize;
public:
    VertexBuffer(unsigned int size, const void* data = nullptr);
    ~VertexBuffer();
    void addData(unsigned int size, const void* data);
    void resetData();

    void bind() const;
    void unbind() const;
};

#endif