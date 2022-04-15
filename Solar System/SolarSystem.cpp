// Jesse Houk
// Solar System
// Colors are assigned to each vertex and then the rasterizer interpolates
//   those colors across the triangles.  We us an orthographic projection
//   as the default projetion.

#include <vector>
#include <stack>

#include "Angel.h"

#include "Model.h"

#pragma comment(lib, "glew32")

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

//#define NUM_MODELS 4

GLuint modelviewLoc, projectionLoc;
int modelNum = 0;
GLuint program;
Model Sun = Model("Sun", "ply");
Model Earth = Model("Earth", "ply");
Model Mercury = Model("Mercury", "ply");
Model Mars = Model("Mars", "ply");
Model Saturn = Model("Saturn", "ply");
Model Moon = Model("Moon", "ply");
Model Enceladus = Model("Enceladus", "ply");
Model Titan = Model("Titan", "ply");
Model SaturnsRings = Model("SaturnsRings", "ply");
Model Falcon = Model("Falcon", "ply");
float EarthTheta = 0.0;
float MercuryTheta = 0.0;
float MarsTheta = 0.0;
float SaturnTheta = 0.0;
float MoonTheta = 0.0;
float EnceladusTheta = 0.0;
float TitanTheta = 0.0;
float FalconTheta = 0.0;

float EarthRevolution = 0.0;
float MarsRevolution = 0.0;

float fastForward = 1.0;
stack<mat4> ModelViews;
vec3 Thetas;
const vec4 EyeOrigin = { 0, 0, 12, 1 };
vec4 Eye = EyeOrigin;
// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int      Axis = Xaxis;
// OpenGL initialization
void
init()
{
	// Load shaders and use the resulting shader program
	program = InitShader("vshader_a6.glsl", "fshader_a4.glsl");
	glUseProgram(program);
	Sun.Load(program);
	Earth.Load(program);
	Mercury.Load(program);
	Mars.Load(program);
	Saturn.Load(program);
	Moon.Load(program);
	Enceladus.Load(program);
	Titan.Load(program);
	SaturnsRings.Load(program);
	Falcon.Load(program);
	modelviewLoc = glGetUniformLocation(program, "ModelView");
	projectionLoc = glGetUniformLocation(program, "Projection");


	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.10, 1.0);
}

//----------------------------------------------------------------------------

void
reshape(int width, int height) {

	glViewport(0, 0, width, height);

	GLfloat aspect = width / GLfloat(height);
	glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, Perspective(30.0, aspect, .5, 20.0));


}
//----------------------------------------------------------------------------

void
display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glUniform3fv(theta, 1, Theta);
	mat4 modelView = LookAt(Eye, vec4(0, 0, 0, 1), vec4(0, 1, 0, 0)) *
		(RotateX(Thetas[Xaxis]) * RotateY(Thetas[Yaxis]) * RotateZ(Thetas[Zaxis])) *
		Scale(vec3(.25));
	glUniformMatrix4fv(modelviewLoc, 1, GL_TRUE, modelView);
	Sun.Draw(program, Eye);

	ModelViews.push(modelView);

	modelView = modelView * (RotateY(EarthTheta)) * Translate(vec3(5, 0, 0))* Scale(vec3(70)) /* RotateY(-EarthTheta) incorrect rotation when inculded*/;
	glUniformMatrix4fv(modelviewLoc, 1, GL_TRUE, modelView * RotateY(EarthRevolution));
	Earth.Draw(program, Eye);


	modelView = modelView * RotateY(MoonTheta) * Translate(vec3(.018, 0, 0)) * Scale(vec3(2));
	glUniformMatrix4fv(modelviewLoc, 1, GL_TRUE, modelView);
	Moon.Draw(program, Eye);


	modelView = ModelViews.top() * RotateY(MercuryTheta) * Translate(vec3(1.89, 0, 0)) * Scale(vec3(400));
	glUniformMatrix4fv(modelviewLoc, 1, GL_TRUE, modelView);
	Mercury.Draw(program, Eye);

	modelView = ModelViews.top() * RotateY(MarsTheta) * Translate(vec3(7.76, 0, 0)) * Scale(vec3(225));
	glUniformMatrix4fv(modelviewLoc, 1, GL_TRUE, modelView);
	Mars.Draw(program, Eye);

	modelView = ModelViews.top() * RotateY(SaturnTheta) * Translate(vec3(10, 0, 0)) * Scale(vec3(1));
	glUniformMatrix4fv(modelviewLoc, 1, GL_TRUE, modelView);
	Saturn.Draw(program, Eye);
	
	ModelViews.push(modelView);

	modelView = modelView * RotateX(90);// *Scale(vec3(34));
	glUniformMatrix4fv(modelviewLoc, 1, GL_TRUE, modelView);
	SaturnsRings.Draw(program, Eye);

	modelView = ModelViews.top() * RotateY(EnceladusTheta) * Translate(vec3(2, 0, 0)) * Scale(vec3(100));
	glUniformMatrix4fv(modelviewLoc, 1, GL_TRUE, modelView);
	Enceladus.Draw(program, Eye);

	modelView = ModelViews.top() * RotateX(TitanTheta) * Translate(vec3(0, 2, 0)) * Scale(vec3(80));
	glUniformMatrix4fv(modelviewLoc, 1, GL_TRUE, modelView);
	Titan.Draw(program, Eye);

	ModelViews.pop();

	modelView = ModelViews.top() * RotateY(FalconTheta) * Translate(vec3(3.5, 0, 0)) * RotateZ(180) * RotateX(90) * Scale(vec3(.2));
	glUniformMatrix4fv(modelviewLoc, 1, GL_TRUE, modelView);
	Falcon.Draw(program, Eye);


	glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 033: // Escape Key
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;
	case 'x':
		Thetas[Xaxis] -= 10;
		break;
	case 'X':
		Thetas[Xaxis] += 10;
		break;
	case 'y':
		Thetas[Yaxis] -= 10;
		break;
	case 'Y':
		Thetas[Yaxis] += 10;
		break;
	case 'z':
		Thetas[Zaxis] -= 10;

		break;
	case 'Z':
		Thetas[Zaxis] += 10;
		break;
	case 'r':
		Thetas = 0;
		Eye = EyeOrigin;
		break;

	case '+':
		Eye.z -= 1;
		break;

	case '-':
		Eye.z += 1;
		break;
	case 'a':
		Eye.x -= 1;
		break;
	case 'd':
		Eye.x += 1;
		break;
	case 's':
		Eye.y -= 1;
		break;
	case 'w':
		Eye.y += 1;
		break;
	case '1':
		fastForward += 1;
		break;
	case '!':
		fastForward -= 1;
		break;
	}
}

//----------------------------------------------------------------------------

void
mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		switch (button) {
		case GLUT_LEFT_BUTTON:    Axis = Xaxis;  break;
		case GLUT_MIDDLE_BUTTON:  Axis = Yaxis;  break;
		case GLUT_RIGHT_BUTTON:   Axis = Zaxis;  break;
		}
	}
}

//----------------------------------------------------------------------------

void
idle(void)
{
	EarthTheta += 0.01 * fastForward;
	MercuryTheta += 0.05 * fastForward;
	MarsTheta += 0.0085 * fastForward;
	SaturnTheta += 0.001 * fastForward;
	MoonTheta += 0.015 * fastForward;
	EnceladusTheta += 0.015 * fastForward;
	TitanTheta += 0.025 * fastForward;
	FalconTheta += 0.014 * fastForward;
	if (EarthTheta > 360.0) {
		EarthTheta -= 360.0;
	}
	if (MercuryTheta > 360.0) {
		MercuryTheta -= 360.0;
	}
	if (MarsTheta > 360.0) {
		MarsTheta -= 360.0;
	}
	if (SaturnTheta > 360.0) {
		SaturnTheta -= 360.0;
	}
	if (MoonTheta > 360.0) {
		MoonTheta -= 360.0;
	}
	if (EnceladusTheta > 360.0) {
		EnceladusTheta -= 360.0;
	}
	if (TitanTheta > 360.0) {
		TitanTheta -= 360.0;
	}
	if (FalconTheta > 360.0) {
		FalconTheta -= 360.0;
	}
	EarthRevolution += 0.0025;
	MarsRevolution += 0.003;
	if (EarthRevolution > 360.0) {
		EarthRevolution -= 360.0;
	}
	if (MarsRevolution > 360.0) {
		MarsRevolution -= 360.0;
	}

	glutPostRedisplay();
}

//----------------------------------------------------------------------------

int
main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Solar System");
	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}