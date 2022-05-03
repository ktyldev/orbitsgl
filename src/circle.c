#include "circle.h"

const int EDGES = 100;

void generateCircle(struct Circle* c, float r)
{
    c->vertCount = EDGES + 2;
    c->vertices = calloc(c->vertCount * VERT_SIZE, sizeof(GLfloat));

    // assign the first vertex in the middle
    c->vertices[0] = 0;
    c->vertices[1] = 0;
    c->vertices[2] = 0;

    // add more vertices in a circle around the first one
    for (int i = 0; i <= EDGES; i++)
    {
        float a = (float)i / (float)EDGES * 2 * PI;

        // calculate x, y, z coordinates of circle
        float x = sin(a) * r;
        float y = cos(a) * r;
        float z = 0;

        int vi = VERT_SIZE * (i + 1);
        c->vertices[vi + 0] = x;
        c->vertices[vi + 1] = y;
        c->vertices[vi + 2] = z;
    }

    glGenVertexArrays(1, &(c->vao));
    glBindVertexArray(c->vao);

    glGenBuffers(1, &(c->vbo));

    glBindBuffer(GL_ARRAY_BUFFER, c->vbo);
    glBufferData(GL_ARRAY_BUFFER, c->vertCount * VERT_SIZE * sizeof(GLfloat), c->vertices, GL_STATIC_DRAW);
}

void drawCircle(struct Circle c, GLuint shaderProgram)
{
    // first we want to draw a circle of points around the origin
    GLint loc = glGetUniformLocation(shaderProgram, "color");
    glUniform3f(loc, 1.0, 0.0, 0.0);

    loc = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(loc, VERT_SIZE, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(loc);

    glBindBuffer(GL_ARRAY_BUFFER, c.vbo);

    glBindVertexArray(c.vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, c.vertCount);

    // then we want to align it to face the camera with the model matrix
}
