#pragma once
#include <string>
#include <iostream>
#include "SOIL/SOIL.h"
#include "plyloader.h"
using namespace std;

class Model
{
	string name;
	string ext;
	PLYModel model;
public:
	GLuint vao;
	GLuint tex;
	Model();
	~Model();
	// Parameratized constructor that reads in the model rply file
	Model(string, string);
	// This method loads the model into OpenGL(ie onto the GPU)
	bool Load(GLuint);
	void Draw(GLuint, vec4);
	bool IsModelType(string, string);
};

