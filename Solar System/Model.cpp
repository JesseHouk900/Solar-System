#include "Model.h"
#include "Angel.h"
#include <vector>
Model::Model()
{
}

Model::~Model()
{
}

// Parameratized constructor that reads in the model rply file
Model::Model(string Oname, string Oext)
{
	if (this->IsModelType(Oext, "ply")) {
		//	PLYModel plymodel("monkey.ply", true, false);//true normals , false colors
		model = PLYModel((Oname + "." + Oext).c_str());
	}
	else
		cerr << "Model type is not supported" << endl;

	name = Oname;
	ext = Oext;
}


// This method loads the model into OpenGL(ie onto the GPU)
// Have NOT included color yet!
bool Model::Load(GLuint program)
{
	cout << "Loading " << name <<" onto gpu"<< endl;
	//glUseProgram(program);
	// Create a vertex array object
	// Each obj has its own vao and its stored in the class
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Generate the faces index buffer. These must be GLushort
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	int si=model.indices.size()*4;
	int sp = model.positions.size() * 16;//vec4
	int sn = model.normals.size() * 12;//vec3
	int sc = model.colors.size() * 16; // Modified by JJ Houk
	int suv = model.uvs.size() * 8;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, si, &model.indices[0],GL_STATIC_DRAW);

	// Create and initialize a buffer object to hold the data
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sp + sn + sc + suv,// reserve space for pos and norms
		NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sp, &model.positions[0]);// copy over the positions
	glBufferSubData(GL_ARRAY_BUFFER, sp,// copy over the normals
		sn, &model.normals[0]);
	if(sc>0)//if using colors
	  glBufferSubData(GL_ARRAY_BUFFER, sp+sn,// copy over the colors
		sc, &model.colors[0]);
	if (suv > 0)
		glBufferSubData(GL_ARRAY_BUFFER, sp + sn + sc,//copy over the uvs
			suv, &model.uvs[0]);
	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));

	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sp));
	if (sc > 0) {// if using colors
		GLuint vColor = glGetAttribLocation(program, "vColor");
		glEnableVertexAttribArray(vColor);
		// Modified by JJ Houk
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(sp + sn));
	}
	if (suv > 0) {// if using uvs
		GLuint vUV = glGetAttribLocation(program, "vUV");
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		int width, height, channels;
		string iname = name + ".png";
		unsigned char * image = SOIL_load_image(iname.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		SOIL_free_image_data(image);

		GLuint texMap = glGetUniformLocation(program, "texMap");
		glUniform1i(texMap, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glBindTexture(GL_TEXTURE_2D, 0);
		glEnableVertexAttribArray(vUV);
		glVertexAttribPointer(vUV, 2, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(sp + sn + sc));
		//for (auto uv : model.uvs) {
		//	vec3 v = glTexture2D(texMap, uv).xyz;
	
	}


	glBindVertexArray(0);// unbind this VAO

	// This code we will study later when we get to
	// lighting and materials.
	// Initialize shader lighting parameters
	// Normally you should get these from the object data
	// I have set them to a constant here since ply does not
	// have this data.
	/*vec4 light_position(0.0, 0.0, 0.0, 1.0);
	vec4 light_ambient(0.66, 0.66, 0.66, 1.0);
	vec4 light_diffuse(.85, .92, .96, 1.0);
	vec4 light_specular(1.0, 1.0, 1.0, 1.0);

	vec4 material_ambient(0.02, 0.02, 0.02, 1.0);
	vec4 material_diffuse(0.02, .02, .02, 1.0);
	vec4 material_specular(.02, .02, .02, 1.0);
	float  material_shininess = 100.0;*/
	vec4 light_ambient(1, 1, 1, 1.0);
	vec4 light_diffuse(.85, .92, .96, 1.0);
	vec4 light_specular(1.0, 1.0, 1.0, 1.0);

	vec4 material_ambient(0.0, 0.0, 0.0, 1.0);
	vec4 material_diffuse(0.55, 0.55, 0.55, 1.0);
	vec4 material_specular(0.7, 0.7, 0.7, 1.0);
	float  material_shininess = 32.0;
	vec4 ambient_product = light_ambient * material_ambient;
	vec4 diffuse_product = light_diffuse * material_diffuse;
	vec4 specular_product = light_specular * material_specular;

	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"),
		1, ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"),
		1, diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"),
		1, specular_product);


	glUniform1f(glGetUniformLocation(program, "Shininess"),
		material_shininess);


	return true;
}


void Model::Draw(GLuint program, vec4 light)
{
	vec4 light_position = light;
	glUniform4fv(glGetUniformLocation(program, "LightPosition"),
		1, light_position);
	glBindVertexArray(vao);
	// you normally change the objects material and lighting settings
	// here if you know them. Ply files do not have lighting and materials
	glBindTexture(GL_TEXTURE_2D, tex);
	glDrawElements(GL_TRIANGLES, model.indices.size(), GL_UNSIGNED_INT, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool Model::IsModelType(string ext1, string ext2) {
	return (ext1 == ext2);
}