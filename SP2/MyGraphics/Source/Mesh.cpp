#include "Mesh.h"
#include "Vertex.h"
#include "GL\glew.h"

/******************************************************************************/
/*!
\brief
Default constructor - generate VBO/IBO here

\param meshName - name of mesh
*/
/******************************************************************************/
Mesh::Mesh(const std::string &meshName): name(meshName), mode(DRAW_TRIANGLES)
{
    // Generate buffers
    glGenBuffers(1, &vertexBuffer);
    //glGenBuffers(1, &colorBuffer);
    glGenBuffers(1, &indexBuffer);
	textureID = 0;
}

/******************************************************************************/
/*!
\brief
Destructor - delete VBO/IBO here
*/
/******************************************************************************/
Mesh::~Mesh()
{
    glDeleteBuffers(1, &vertexBuffer);
    //glDeleteBuffers(1, &colorBuffer);
    glDeleteBuffers(1, &indexBuffer);
	if (textureID > 0)
		glDeleteTextures(1, &textureID);

}

/******************************************************************************/
/*!
\brief
OpenGL render code
*/
/******************************************************************************/
void Mesh::Render()     //next time just call Mesh::Render
{
	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors
	glEnableVertexAttribArray(2); // 3rd attribute buffer : normals
	if (textureID > 0)
	{
		glEnableVertexAttribArray(3);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);  //2nd last value is stride: how many "steps to take" to the next vertex

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));   //last value is offset
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position)+sizeof(Color)));

	if (textureID > 0)
	{
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position)+sizeof(Color)+sizeof(Vector3)));
	}
	//because mesh.h is made to be generic (not specifically written for OpenGL)
	//we need to convert the draw_mode to GL draw_modes
	if (mode == DRAW_TRIANGLE_STRIP) {
		glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0);
	}
	else if (mode == DRAW_LINES) {
		glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);
	}
	else {      //default is GL_TRIANGLES if got any error - "safer"
		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
	}

	if (textureID > 0)
	{
		glDisableVertexAttribArray(3);
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Mesh::Render(unsigned offset, unsigned count)
{
	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors
	glEnableVertexAttribArray(2); // 3rd attribute buffer : normals
	if (textureID > 0)
	{
		glEnableVertexAttribArray(3);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);  //2nd last value is stride: how many "steps to take" to the next vertex

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));   //last value is offset
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position)+sizeof(Color)));

	if (textureID > 0)
	{
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position)+sizeof(Color)+sizeof(Vector3)));
	}
	//because mesh.h is made to be generic (not specifically written for OpenGL)
	//we need to convert the draw_mode to GL draw_modes
	if (mode == DRAW_LINES)
		glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
	else if (mode == DRAW_TRIANGLE_STRIP)
		glDrawElements(GL_TRIANGLE_STRIP, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
	else
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));


	if (textureID > 0)
	{
		glDisableVertexAttribArray(3);
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	
}
