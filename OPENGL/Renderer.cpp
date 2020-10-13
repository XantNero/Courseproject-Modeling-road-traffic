#include "Renderer.h"
#include "GL/glew.h"
#include "debug.h"

Renderer::Renderer() { }
Renderer::~Renderer() { }

void Renderer::draw(const VertexArray &vao, const IndexBuffer &ibo, const Shader &shader) const
{
    vao.bind();
    shader.bind();
    GLCall(glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, 0));
}