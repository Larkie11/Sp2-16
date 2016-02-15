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

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ)
{
	const GLfloat vertex_buffer[] = {
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,

        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,

        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,

        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,

        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,

        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f
	};

    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;

    Vertex v;
	//Go through the vertex_buffer array and keep pushing back
    for (int i = 0; i < 36; ++i) {
        v.pos.Set(lengthX * vertex_buffer[i * 3], lengthY * vertex_buffer[i * 3 + 1], lengthZ * vertex_buffer[i * 3 + 2]);
        v.color.Set(color.r, color.g, color.b);
		v.normal.Set();
        vertex_buffer_data.push_back(v);
    }

	//Push all vertices into index buffer
    for (int i = 0; i < 36; ++i) {
        index_buffer_data.push_back(i);
    }

	Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = 36;
    mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}
Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color, float lengthX, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float convert = 10 * (Math::PI / 180);
	float rad = 0;

	Vertex v;
	for (int theta = 0; theta < 37; theta++)
	{
		rad = convert * theta;
		v.pos.Set(lengthX*cos(rad), 0, lengthZ*sin(rad));
		v.color.Set(color.r, color.g, color.b);
		vertex_buffer_data.push_back(v);
		v.pos.Set(0, 0, 0);

		v.color.Set(color.r, color.g, color.b);
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < 74; ++i) {
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 74;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}
float CircleX(float theta)
{
	return cos(Math::DegreeToRadian(theta));
}
float CircleZ(float theta)
{
	return sin(Math::DegreeToRadian(theta));
}
Mesh* MeshBuilder::GenerateCircles(const std::string &meshName, Color color, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	float anglePerSlice = 360.f / numSlices;

	for (unsigned i = 0; i < numSlices+1; ++i)
	{
		float theta = i * anglePerSlice;
		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}
	v.pos.Set(0, 1, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);
	for (unsigned i = 0; i < numSlices + 1; ++i)
	{
		index_buffer_data.push_back(i); //center
		index_buffer_data.push_back(numSlices + 1); //edge
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
Mesh* MeshBuilder::GenerateHemisphere(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ, float radius)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	float convert = 10 * (Math::PI / 180);
	float rad = 0;
	float phi1 = 0;
	float theta1 = 0;
	float phiten = 0;

	for (int phi = 0; phi < 9; phi ++)
	{
		for (int theta = 0; theta < 37; theta ++)
		{
			phi1 = convert * phi;
			theta1 = convert * theta;
			phiten = phi1 + convert;
			v.color.Set(color.r, color.g, color.b);

			v.pos.Set(radius* cos(phi1)*cos(theta1), radius*sin(phi1), radius*cos(phi1)*sin(theta1));
			vertex_buffer_data.push_back(v);

			v.pos.Set(radius*cos(phiten)*cos(theta1), radius*sin(phiten), radius*cos(phiten)*sin(theta1));
			vertex_buffer_data.push_back(v);
		}
	}

	for (int theta = 0; theta < 37; theta++)
	{
		rad = convert * theta;
		
		v.color.Set(color.r, color.g, color.b);
		v.pos.Set(0, 0, 0);
		v.pos.Set(radius*cos(rad), 0, radius*sin(rad));
		vertex_buffer_data.push_back(v);
	

		v.color.Set(color.r, color.g, color.b);
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < 1000; ++i) {
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 1000;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}
Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, float radius, float lengthX, float lengthY)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	float convert = 10 * (Math::PI / 180);
	float rad = 0;
	float phi1 = 0;
	float theta1 = 0;
	float phiten = 0;

	for (int phi = 0; phi < 18; phi++)
	{
		for (int theta = 0; theta < 37; theta++)
		{
			phi1 = convert * phi;
			theta1 = convert * theta;
			phiten = phi1 + convert;
			v.color.Set(color.r, color.g, color.b);

			if (phi > 9){
				v.pos.Set(lengthX* cos(phi1)*cos(theta1), -lengthY*sin(phi1), lengthY*cos(phi1)*sin(theta1));
				vertex_buffer_data.push_back(v);

				v.pos.Set(lengthX*cos(phiten)*cos(theta1), -lengthY*sin(phiten), lengthY*cos(phiten)*sin(theta1));
				vertex_buffer_data.push_back(v);
			}

			else {
				v.pos.Set(lengthX* cos(phi1)*cos(theta1), lengthY*sin(phi1), lengthY*cos(phi1)*sin(theta1));
				vertex_buffer_data.push_back(v);

				v.pos.Set(lengthX*cos(phiten)*cos(theta1), lengthY*sin(phiten), lengthY*cos(phiten)*sin(theta1));
				vertex_buffer_data.push_back(v);
			}
		}
	}

	for (int i = 0; i < 1332; ++i) {
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 1332;
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
Mesh* MeshBuilder::GenerateConeHem(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	float anglePerSlice = 360.f / numSlices;
	float anglePerStack = 90.f / numStacks; //If hemisphere change to 90.f

	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		float phi = -90 + stack * anglePerStack; //If hemisphere change phi to -90 + stack
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			float theta = slice * anglePerSlice;
			v.pos.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
			v.color = color;
			v.normal.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
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
Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, float innerRadius, float outerRadius)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	for (int theta = 0; theta <= 360; theta+=10)
	{
		v.color.Set(color.r, color.g, color.b);
		v.pos.Set(outerRadius * cos(Math::DegreeToRadian(theta)), 0, outerRadius * sin(Math::DegreeToRadian(theta)));
		//v.normal(0, 1, 0);
		vertex_buffer_data.push_back(v);
		v.pos.Set(innerRadius * cos(Math::DegreeToRadian(theta)), 0, innerRadius * sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);
	}

	for (int theta = 0; theta <= 360; theta+=10)
	{
		v.color.Set(color.r, color.g, color.b);
		v.pos.Set(outerRadius * -cos(Math::DegreeToRadian(theta)), 0, outerRadius * sin(Math::DegreeToRadian(theta)));
		//v.normal(0, -1, 0);
		vertex_buffer_data.push_back(v);
		v.pos.Set(innerRadius * -cos(Math::DegreeToRadian(theta)), 0, innerRadius * sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);
	}


	for (int i = 0; i < 2000; ++i) 
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 2000;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCones2(const std::string &meshName, Color color, unsigned numSlices, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.f / numSlices;
	for (unsigned slice = 0; slice < numSlices + 1; slice++)
	{
		//bottom
		float theta = slice * anglePerSlice;
		v.pos.Set(lengthX* CircleX(theta), lengthY*-0.5f, lengthZ*CircleZ(theta));
		v.color = color;
		v.normal.Set(CircleX(theta), 1, CircleZ(theta));
		v.normal.Normalize();
		vertex_buffer_data.push_back(v);
		//top
		v.pos.Set(0, lengthY*0.5f, 0);
		v.color = color;
		v.normal.Set(CircleX(theta), 1, CircleZ(theta));
		v.normal.Normalize();
		vertex_buffer_data.push_back(v);
	}
	v.pos.Set(0, lengthY*-0.5f, 0);
	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);

	for (unsigned slice = 0; slice < numSlices + 1; slice++)
	{
		index_buffer_data.push_back(2 * (numSlices + 1));
		index_buffer_data.push_back(2 * slice);
	}

	for (unsigned slice = 0; slice < numSlices + 1; slice++)
	{
		index_buffer_data.push_back(2 * slice + 1);
		index_buffer_data.push_back(2 * slice);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}
Mesh* MeshBuilder::GenerateCone2(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	float anglePerSlice = 360.f / numSlices;
	float anglePerStack = 90.f / numStacks; //If hemisphere change to 90.f

	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		float phi = -90 + stack * anglePerStack; //If hemisphere change phi to -90 + stack
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			float theta = slice * anglePerSlice;
			v.pos.Set(lengthX*SphereX(phi, theta), lengthY*SphereY(phi, theta), lengthZ*SphereZ(phi, theta));
			v.color = color;
			v.normal.Set(lengthX*SphereX(phi, theta), lengthY*SphereY(phi, theta), lengthZ*SphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
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

Mesh* MeshBuilder::GenerateCylinder2(const std::string &meshName, Color color, float height, float numStack, float radius, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;
	float stackHeight = height / numStack;


	//Top
	for (int theta = 0; theta <= 360; theta += 10)
	{
		v.normal.Set(0, 1, 0);
		v.pos.Set(lengthX*radius*cos(Math::DegreeToRadian(theta)), lengthY*height / 2, lengthZ*radius*sin(Math::DegreeToRadian(theta)));
		v.color = color;
		vertex_buffer_data.push_back(v);

		v.normal.Set(0, 1, 0);
		v.pos.Set(0, lengthY*height / 2, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);
	}

	for (int stack = 0; stack < numStack; ++stack) //stack
	{
		for (int theta = 0; theta <= 360; theta += 10) //slice
		{
			v.normal.Set(lengthX*radius*cos(Math::DegreeToRadian(theta)), 0, lengthZ*radius*sin(Math::DegreeToRadian(theta)));
			v.pos.Set(lengthX*radius*cos(Math::DegreeToRadian(theta)), lengthY*-height / 2 + (stack*stackHeight), lengthZ*radius*sin(Math::DegreeToRadian(theta)));
			v.color = color;
			vertex_buffer_data.push_back(v);

			v.normal.Set(lengthX*radius*cos(Math::DegreeToRadian(theta)), 0, lengthZ*radius*sin(Math::DegreeToRadian(theta)));
			v.pos.Set(lengthX*radius*cos(Math::DegreeToRadian(theta)), lengthY *-height / 2 + (stack + 1), lengthZ*radius*sin(Math::DegreeToRadian(theta)));
			v.color = color;
			vertex_buffer_data.push_back(v);
		}
	}
	//Bottom
	for (int theta = 0; theta <= 360; theta += 10)
	{
		v.normal.Set(0, -1, 0);
		v.pos.Set(0, lengthY*-height / 2, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);

		v.normal.Set(0, -1, 0);
		v.pos.Set(lengthX*radius*cos(Math::DegreeToRadian(theta)), lengthY*-height / 2, lengthZ*radius*sin(Math::DegreeToRadian(theta)));
		v.color = color;
		vertex_buffer_data.push_back(v);

	}





	for (int i = 0; i <1000; ++i) {
		index_buffer_data.push_back(i);
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



Mesh* MeshBuilder::GenerateCubes2(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	//left
	v.pos.Set(lengthX*-0.5f, lengthY*-0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*-0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*-0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	//back
	v.pos.Set(lengthX*0.5f, lengthY*0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*-0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*0.5f, lengthY*0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*0.5f, lengthY*-0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*-0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	//bottom
	v.pos.Set(lengthX*0.5f, lengthY*-0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*-0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*0.5f, lengthY*-0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*0.5f, lengthY*-0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*-0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*-0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	//front
	v.pos.Set(lengthX*0.5f, lengthY*0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*0.5f, lengthY*-0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*-0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*0.5f, lengthY*-0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	//right
	v.pos.Set(lengthX*0.5f, lengthY*-0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*0.5f, lengthY*0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*0.5f, lengthY*-0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*0.5f, lengthY*0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*0.5f, lengthY*-0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*0.5f, lengthY*0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	//top
	v.pos.Set(lengthX*0.5f, lengthY*0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*0.5f, lengthY*0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*0.5f, lengthY*0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*0.5f, lengthZ*-0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX*-0.5f, lengthY*0.5f, lengthZ*0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);

	for (unsigned i = 0; i < 36; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}
Mesh* MeshBuilder::GenerateHemispheres2(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	float anglePerSlice = 360.f / numSlices;
	float anglePerStack = 90.f / numStacks; //If hemisphere change to 90.f

	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		float phi = -90 + stack * anglePerStack; //If hemisphere change phi to -90 + stack
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			v.color = color;
			float theta = slice * anglePerSlice;
			v.pos.Set(lengthX*SphereX(phi, theta), lengthY*SphereY(phi, theta), lengthZ*SphereZ(phi, theta));
			v.normal.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
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
/*
Mesh* MeshBuilder::GenerateRings(const std::string &meshName, Color color, float innerRadius, unsigned numSlices)
{

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	float anglePerSlice = 360.f / numSlices;

	for (unsigned i = 0; i < numSlices + 1; ++i)
	{
		float theta = i * anglePerSlice;
		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);

		v.pos.Set(innerRadius * CircleX(theta), 0, innerRadius * CircleZ(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);
	}

	v.pos.Set(0, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	for (unsigned i = 0; i < numSlices; ++i)
	{
		index_buffer_data.push_back(2 * i); //center
		index_buffer_data.push_back(2 * i + 1); //edge
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;


	return mesh;
}*/
Mesh* MeshBuilder::GenerateRings(const std::string &meshName, Color color, float innerRadius, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.f / numSlices;
	for (unsigned slice = 0; slice < numSlices + 1; slice++)
	{
		float theta = slice * anglePerSlice;
		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(innerRadius * CircleX(theta), 0, innerRadius * CircleZ(theta));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (unsigned slice = 0; slice < numSlices + 1; slice++)
	{
		index_buffer_data.push_back(2 * slice);
		index_buffer_data.push_back(2 * slice + 1);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}
/*
Mesh* MeshBuilder::GenerateTorus(const std::string &meshName, Color color, float outerRadius, float innerRadius, unsigned numSlices, unsigned numStacks)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	int stacks = 36;
	float angleStack = Math::TWO_PI / stacks;
	int slices = 18;
	float angleSlice = Math::TWO_PI / slices;

	Vertex v;
	v.color.Set(color.r, color.g, color.b);
	for (int i = 0; i < stacks; ++i) {
		for (int j = 0; j < slices + 1; ++j) {
			v.pos.Set( (outerRadius + innerRadius  cos(angleSlice  j)) sin(angleStack  i), innerRadius  sin(angleSlice  j), (outerRadius + innerRadius  cos(angleSlice  j))  cos(angleStack  i));
			vertex_buffer_data.push_back(v);

			v.pos.Set((outerRadius + innerRadius  cos(angleSlice(j + 1)))  sin(angleStack(i + 1)), innerRadius  sin(angleSlice(j + 1)), (outerRadius + innerRadius  cos(angleSlice(j + 1)))  cos(angleStack(i + 1)));
			v.color.Set(0.02*i, 0.02*i, 0.02*i);
			vertex_buffer_data.push_back(v);

		}
	}

	for (int i = 0; i < stacks 2 (slices + 1); ++i) {
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}*/
Mesh* MeshBuilder::GenerateCylinder(const std::string &meshName, Color color, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	float anglePerSlice = 360.f / numSlices;
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		float theta = slice * anglePerSlice;
		//point at edge of bottom circle
		v.pos.Set(CircleX(theta), -0.5f, CircleZ(theta));
		v.color = color;
		v.normal.Set(CircleX(theta), 0, CircleZ(theta));
		vertex_buffer_data.push_back(v);

		//point at edge of top circle
		v.pos.Set(CircleX(theta), 0.5f, CircleZ(theta));
		v.color = color;
		v.normal.Set(CircleX(theta), 0, CircleZ(theta));
		vertex_buffer_data.push_back(v);
	}
	//bottom lid - centre
	v.pos.Set(0, -0.5f, 0);
	v.normal.Set(0, -1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	//top lid - centre
	v.pos.Set(0, 0.5f, 0);
	v.normal.Set(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	//bottom lid
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		index_buffer_data.push_back(2 * (numSlices + 1));
		index_buffer_data.push_back(2 * slice);

	}
	//curved edges
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		index_buffer_data.push_back(2* slice);
		index_buffer_data.push_back(2* slice + 1);
	}
	//top lid
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		index_buffer_data.push_back(2 * slice +1);
		index_buffer_data.push_back(2 * (numSlices + 1) +1);
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
Mesh* MeshBuilder::GenerateCone(const std::string &meshName, Color color, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.f / numSlices;
	for (unsigned slice = 0; slice < numSlices + 1; slice++)
	{
		//bottom
		float theta = slice * anglePerSlice;
		v.pos.Set(CircleX(theta), -0.5f, CircleZ(theta));
		v.color = color;
		v.normal.Set(CircleX(theta), 1, CircleZ(theta));
		v.normal.Normalize();
		vertex_buffer_data.push_back(v);
		//top
		v.pos.Set(0, 0.5f, 0);
		v.color = color;
		v.normal.Set(CircleX(theta), 1, CircleZ(theta));
		v.normal.Normalize();
		vertex_buffer_data.push_back(v);
	}
	v.pos.Set(0, -0.5f, 0);
	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);

	for (unsigned slice = 0; slice < numSlices + 1; slice++)
	{
		index_buffer_data.push_back(2 * (numSlices + 1));
		index_buffer_data.push_back(2 * slice);
	}

	for (unsigned slice = 0; slice < numSlices + 1; slice++)
	{
		index_buffer_data.push_back(2 * slice + 1);
		index_buffer_data.push_back(2 * slice);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
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
