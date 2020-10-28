#include "Renderer.h"
#include "GL/glew.h"
#include "debug.h"

Renderer::Renderer() { }
Renderer::~Renderer() { }

void Renderer::draw(const unsigned int type, const VertexArray &vao, const IndexBuffer &ibo, const Shader &shader) const
{
    vao.bind();
    ibo.bind();
    shader.bind();
    GLCall(glDrawElements(type, ibo.getCount(), GL_UNSIGNED_INT, 0));
}