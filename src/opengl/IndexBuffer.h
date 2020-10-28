#ifndef _INDEXBUFFER_H_
#define _INDEXBUFFER_H_

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
    unsigned int m_MaxCount;
public:
    IndexBuffer(unsigned int count, unsigned int* data = nullptr);
    ~IndexBuffer();
    void addData(unsigned int count, unsigned int* data);
    void ResetData();

    void bind() const;
    void unbind() const;
    unsigned int getCount() const;
};

#endif