
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
GLuint VBO;
struct Matrix4f {
	float m[4][4];
};
glm::mat4 World;
float Scale = 0;

void func() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 WorldMat = glm::mat4{ 1.0f };

	const float ar = 1024 / 768;
	const float zNear = 0.005;
	const float zFar = 80;
	const float zRange = zNear-zFar;
	const float tanHalfFOV = tanf(glm::radians(20 / 2.0));
	Scale += 0.001f;


	World[0][0] = 1.0f / (tanHalfFOV * ar); World[0][1] = 0; World[0][2] = 0; World[3][0] = 0;
	World[1][0] = 0; World[1][1] = 1.0f / tanHalfFOV; World[1][2] = 0; World[1][3] = 0.0f;
	World[2][0] = 0; World[2][1] = 0; World[2][2] = (-zNear - zFar) / zRange; World[2][3] = 1.0f;
	World[3][1] = 0; World[3][2] = 2.0f * zFar * zNear / zRange; World[3][3] = 0.0f;

	//World[0][0] = 1.0f; World[0][1] = 0; World[0][2] = 0; World[3][0] = 0;
	//World[1][0] = 0; World[1][1] = 1; World[1][2] = 0; World[1][3] = 0.0f;
	//World[2][0] = 0; World[2][1] = 0; World[2][2] = 1; World[2][3] = 0.0f;
	//World[3][1] = 0; World[3][2] = 0; World[3][3] = 1.0f;
	glm::mat4 World2(0);
	glm::vec3 CameraPos(0.5, 0, 0);

	World2[0][0] = 1.0f; World2[0][1] = 0; World2[0][2] = 0; World2[0][3] = 0;
	World2[1][0] = 0; World2[1][1] = 1; World2[1][2] = 0; World2[1][3] = 0;
	World2[2][0] = 0; World2[2][1] = 0; World2[2][2] = 1; World2[2][3] = 0;
	World2[3][0] = -CameraPos.x; World2[3][1] = -CameraPos.y; World2[3][2] = -CameraPos.z; World2[3][3] = 1.0f;

	glm::vec3 CameraTarget(0.45f*sin(Scale), 0.0f, 1.0f);
	glm::vec3 CameraUp(0.0f, 1.0f, 1.0f);

	glm::vec3 N = CameraTarget;
	N = glm::normalize(N);
	glm::vec3 U = CameraUp;
	U = glm::normalize(U);
	U = glm::cross(U, CameraTarget);
	glm::vec3 V = glm::cross(N,U);

	glm::mat4 World3(0);

	World3[0][0] = U.x; World3[0][1] = V.x; World3[0][2] = N.x; World3[0][3] = 0.0f;
	World3[1][0] = U.y; World3[1][1] = V.y; World3[1][2] = N.x; World3[1][3] = 0.0f;
	World3[2][0] = U.z; World3[2][1] = V.z; World3[2][2] = N.z; World3[2][3] = 0.0f;
	World3[3][0] = 0.0f; World3[3][1] = 0.0f; World3[3][2] = 0.0f; World3[3][3] = 1;






	glm::mat4 Worldmat2 = World*World3*World2* WorldMat;



	glLoadMatrixf(static_cast<const float*>(glm::value_ptr(Worldmat2)));
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glDrawArrays(GL_POINTS, 0, 1);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//glDrawArrays(GL_LINE_STRIP, 0, 6);
	glDisableVertexAttribArray(0);
	glutSwapBuffers();
	glutPostRedisplay();
}




int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 01");
	glutDisplayFunc(func);
	//glClearColor(1.0, 1.0, 0.0, 1.0);

	//GLEW init

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}
	//glm::vec3 Vertices[1];
	//Vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f);

	//glm::vec3 Vertices[6];
	//Vertices[0] = glm::vec3(0, 0, 10);
	//Vertices[1] = glm::vec3(0, 0.5, 10);
	//Vertices[2] = glm::vec3(0.5, 0, 10);

	//Vertices[3] = glm::vec3(-0.7, 0, 20);
	//Vertices[4] = glm::vec3(-0.7, 0.5, 20);
	//Vertices[5] = glm::vec3(-0.7+0.5, 0, 20);

	glm::vec3 Vertices[3];
	Vertices[0] = glm::vec3(0, 0, 10);
	Vertices[1] = glm::vec3(0, 0.5, 10);
	Vertices[2] = glm::vec3(0.5, 0, 10);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);



	glutMainLoop();
}


