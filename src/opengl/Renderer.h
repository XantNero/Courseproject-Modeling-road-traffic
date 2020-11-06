#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer 
{
private:
    unsigned int m_Renderer_ID;
public:
    Renderer();
    ~Renderer();
    void draw(const unsigned int type, const VertexArray &, const IndexBuffer &, const  Shader &) const;
};


#endif