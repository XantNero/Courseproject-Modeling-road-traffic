#ifndef _INDEXBUFFER_H_
#define _INDEXBUFFER_H_

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
public:
    IndexBuffer(unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
    unsigned int getCount() const;
};

#endif