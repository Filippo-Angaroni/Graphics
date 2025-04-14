#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "glad.h"

class VBO {

    public:
        GLuint ID;
        VBO(GLfloat* vertices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();

};

#endif


#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include "glad.h"

class EBO
{
    public:
        GLuint ID;
        EBO(GLuint* indices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
};

#endif

#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "glad.h"

class VAO 
{
    public:
        GLuint ID;
        VAO();

        void LinkVBO(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
        void Bind();
        void Unbind();
        void Delete();
};

#endif

#ifndef FBO_CLASS_H
#define FBO_CLASS_H

#include "glad.h"

class FBO 
{
    public:
        GLuint ID;
        FBO(GLfloat width, GLfloat height);

        GLuint getFrameTexture() { return texture; };
        void RescaleFBO(GLfloat width, GLfloat height);
        void Bind();
        void Unbind();
        void Delete();
    private:
        GLuint rbo;
        GLuint texture;
};

#endif