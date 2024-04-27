#include "Sprite.h"
#include "Vertex.h"
#include<cstddef>

Sprite::~Sprite()
{//vertex buffer id
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
	}

}

void Sprite::init(float x, float y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	if (vboID == 0) {
		glGenBuffers(1, &vboID);
	}

	/*float vertexData[12];
	vertexData[0] = x + width;
	vertexData[1] = y + height;
	vertexData[2] = x;
	vertexData[3] = y + height;
	vertexData[4] = x;
	vertexData[5] = y;
	vertexData[6] = x;
	vertexData[7] = y;
	vertexData[8] = x+width;
	vertexData[9] = y;
	vertexData[10] = x+width;
	vertexData[11] = y+height;*/

	Vertex vertexData[6];

	vertexData[0].setPosition(x + width, y + height); // Inferior derecha
	vertexData[1].setPosition(x, y + height);        // Inferior izquierda
	vertexData[2].setPosition(x, y);                  // Superior izquierda
	vertexData[3].setPosition(x, y);                  // Superior izquierda
	vertexData[4].setPosition(x + width, y);          // Superior derecha
	vertexData[5].setPosition(x + width, y + height);  // Inferior derecha


	for (int i = 0; i < 6; i++)
	{
		//	red green blue alpha
		vertexData[i].setColor(255, 0, 0, 255);
	}
	vertexData[1].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255);



	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData , GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

Sprite::Sprite()
{
}