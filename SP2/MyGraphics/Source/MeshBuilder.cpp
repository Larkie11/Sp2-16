#include <vector>
#include "MyMath.h"
#include "MeshBuilder.h"
#include <GL\glew.h>
#include "Vertex.h"
#include "LoadOBJ.h"
#include <iostream>

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	/*const GLfloat vertex_buffer_data[] = {
		-lengthX, 0, 0,
        lengthX, 0, 0,
        0, -lengthY, 0,
        0, lengthY, 0,
        0, 0, -lengthZ,
        0, 0, lengthZ,
	};
	const GLfloat color_buffer_data[] = {
		1, 0, 0,
        1, 0, 0,
        0, 1, 0,
        0, 1, 0,
        0, 0, 1,
        0, 0, 1,
	};
	const GLuint index_buffer_data[] = {
		0, 1,
        2, 3,
        4, 5,
	};*/

    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    
    Vertex v;
    v.pos.Set(-lengthX, 0, 0);
    v.color.Set(1, 0, 0);
    vertex_buffer_data.push_back(v);

    v.pos.Set(lengthX, 0, 0);
    v.color.Set(1, 0, 0);
    vertex_buffer_data.push_back(v);

    v.pos.Set(0, -lengthY, 0);
    v.color.Set(0, 1, 0);
    vertex_buffer_data.push_back(v);

    v.pos.Set(0, lengthY, 0);
    v.color.Set(0, 1, 0);
    vertex_buffer_data.push_back(v);

    v.pos.Set(0, 0, -lengthZ);
    v.color.Set(0, 0, 1);
    vertex_buffer_data.push_back(v);

    v.pos.Set(0, 0, lengthZ);
    v.color.Set(0, 0, 1);
    vertex_buffer_data.push_back(v);

    index_buffer_data.push_back(0);
    index_buffer_data.push_back(1);
    index_buffer_data.push_back(2);
    index_buffer_data.push_back(3);
    index_buffer_data.push_back(4);
    index_buffer_data.push_back(5);
	Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = 6;
    mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}
/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthY)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;

    Vertex v;

	v.pos.Set(0.5f*lengthX, 0.f, 0.5f*lengthY);
	v.color.Set(color.r, color.g, color.b);
	v.normal.Set(0,1,0);
	v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f*lengthX, 0.f, -0.5f*lengthY);
	v.color.Set(color.r, color.g, color.b);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f*lengthX, 0.f, -0.5f*lengthY);
	v.color.Set(color.r, color.g, color.b);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f*lengthX, 0.f, 0.5f*lengthY);
	v.color.Set(color.r, color.g, color.b);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f*lengthX, 0.f, -0.5f*lengthY);
	v.color.Set(color.r, color.g, color.b);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f*lengthX, 0.f, 0.5f*lengthY);
	v.color.Set(color.r, color.g, color.b);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	for (int i = 0; i < 6; ++i)
	{
		index_buffer_data.push_back(i);
	}
	/*index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);*/

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}
Mesh* MeshBuilder::GenerateRepeatQuad(const std::string &meshName, Color color, float lengthX, float lengthY,int textCoord)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	v.pos.Set(0.5f*lengthX , 0.f, 0.5f*lengthY);
	v.color.Set(color.r, color.g, color.b);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(textCoord, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f*lengthX, 0.f, -0.5f*lengthY);
	v.color.Set(color.r, color.g, color.b);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(textCoord, textCoord);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f*lengthX, 0.f, -0.5f*lengthY);
	v.color.Set(color.r, color.g, color.b);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(0, 10);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f*lengthX, 0.f, 0.5f*lengthY);
	v.color.Set(color.r, color.g, color.b);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(textCoord, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f*lengthX, 0.f, -0.5f*lengthY);
	v.color.Set(color.r, color.g, color.b);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(0, textCoord);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f*lengthX, 0.f, 0.5f*lengthY);
	v.color.Set(color.r, color.g, color.b);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	for (int i = 0; i < 6; ++i)
	{
		index_buffer_data.push_back(i);
	}
	/*index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);*/

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}
Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int offset = 0;

	for (unsigned i = 0; i < numRow; ++i)
	{
		for (unsigned j = 0; j < numCol; ++j)
		{
			/*v.pos.Set(0.5f, 0.f, 0.5f);
			v.texCoord.Set(1, 0);
			v.normal.Set(0, 1, 0);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, 0.f, -0.5f);
			v.normal.Set(0, 1, 0);
			v.texCoord.Set(1, 1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(-0.5f, 0.f, -0.5f);
			v.normal.Set(0, 1, 0);
			v.texCoord.Set(0, 1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, 0.f, 0.5f);
			v.normal.Set(0, 1, 0);
			v.texCoord.Set(1, 0);
			vertex_buffer_data.push_back(v);

			v.pos.Set(-0.5f, 0.f, -0.5f);
			v.normal.Set(0, 1, 0);
			v.texCoord.Set(0, 1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(-0.5f, 0.f, 0.5f);
			v.normal.Set(0, 1, 0);
			v.texCoord.Set(0,0);
			vertex_buffer_data.push_back(v);*/

			float u1 = j*width;
			float v1 = 1.f - height - i*height;

			v.pos.Set(-0.5f, -0.5f, 0);
			v.texCoord.Set(u1, v1);
			v.normal.Set(0, 0, 1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, -0.5f, 0);
			v.texCoord.Set(u1 + width, v1);
			v.normal.Set(0, 0, 1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, 0.5f, 0);
			v.texCoord.Set(u1 + width, v1 + height);
			v.normal.Set(0, 0, 1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(-0.5f, 0.5f, 0);
			v.texCoord.Set(u1, v1 + height);
			v.normal.Set(0, 0, 1);
			vertex_buffer_data.push_back(v);

			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
		}
	}
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	return mesh;
}
float SphereX(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * cos (Math::DegreeToRadian(theta));
}
float SphereY(float phi, float theta)
{
	return sin(Math::DegreeToRadian(phi));
}
float SphereZ(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));
}
Mesh* MeshBuilder::GenerateSpheres(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	float anglePerSlice = 360.f / numSlices;
	float anglePerStack = 180.f / numStacks; //If hemisphere change to 90.f

	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		float phi = -90 + stack * anglePerStack; //If hemisphere change phi to -90 + stack
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			float theta = slice * anglePerSlice;
			v.pos.Set(lengthX* SphereX(phi, theta), lengthY*SphereY(phi, theta), lengthZ*SphereZ(phi, theta));
			v.color = color;
			v.normal.Set(v.pos.x, v.pos.y, v.pos.z);
			//v.normal.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
			/*
			v.pos.Set(SphereX(phi+anglePerStack, theta), SphereY(phi+anglePerStack, theta), SphereZ(phi+anglePerStack, theta));
			v.color = color;
			vertex_buffer_data.push_back(v);*/
		}
	}

	v.pos.Set(0, 0, 0);
	v.color = color;
	unsigned index = 0;
	vertex_buffer_data.push_back(v);
	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			//index_buffer_data.push_back(index++);
			//index_buffer_data.push_back(index++);
			index_buffer_data.push_back(stack*(numSlices + 1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;


	return mesh;
}
Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path) {
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if (!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	//Create the mesh and call glBindBuffer, glBufferData
	//Use triangle list and remember to set index size

	Mesh *mesh = new Mesh(meshName);
	mesh->mode = Mesh::DRAW_TRIANGLES;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize =index_buffer_data.size();
	return mesh;
}
