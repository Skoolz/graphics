
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
GLuint VBO;
glm::mat4 World;
glm::mat4 WorldPerspect;
glm::mat4 WorldCamRotate;
glm::mat4 WorldCamTrans;
glm::mat4 WorldScale;
glm::mat4 WorldRotate;
glm::mat4 WorldTrans;

const float ar = 1024 / 768;
const float zNear = 0.005;
const float zFar = 80;
const float zRange = zNear - zFar;
const float tanHalfFOV = tanf(glm::radians(20 / 2.0));


glm::vec3 CameraTarget(0.45f * sin(Scale), 0.0f, 1.0f);
glm::vec3 CameraUp(0.0f, 1.0f, 1.0f);

float Scale = 0;

void func() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Scale += 0.001f;

	CameraTarget = glm::vec3(0.45f * sin(Scale), 0.0f, 1.0f);

	glm::vec3 N = CameraTarget;
	N = glm::normalize(N);
	glm::vec3 U = CameraUp;
	U = glm::normalize(U);
	U = glm::cross(U, CameraTarget);
	glm::vec3 V = glm::cross(N, U);

	WorldCamRotate= glm::mat4{
		U.x,V.x,N.x,0.0f,
		U.y,V.y,N.y,0.0f,
		U.z,V.z,N.z,0.0f,
		0.0f,0.0f,0.0f,1.0f,
	};

	WorldTrans[0][3] = sinf(Scale);

	WorldRotate[0][0] = cosf(Scale);
	WorldRotate[1][0] = sinf(Scale);
	WorldRotate[0][1] = -sinf(Scale);
	WorldRotate[1][1] = cosf(Scale);

	WorldScale[0][0] = abs(sinf(Scale));
	WorldScale[1][1] = abs(cosf(Scale));
	WorldScale[2][2] = abs(sinf(Scale));


	glm::mat4 WorldMat2 = WorldPerspect * WorldCamRotate * WorldCamTrans * WorldScale * WorldRotate * WorldTrans * WorldMat;



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

	glm::vec3 Vertices[3];
	Vertices[0] = glm::vec3(0, 0, 10);
	Vertices[1] = glm::vec3(0, 0.5, 10);
	Vertices[2] = glm::vec3(0.5, 0, 10);



	CameraTarget = glm::vec3(0.45f * sin(Scale), 0.0f, 1.0f);

	glm::vec3 N = CameraTarget;
	N = glm::normalize(N);
	glm::vec3 U = CameraUp;
	U = glm::normalize(U);
	U = glm::cross(U, CameraTarget);
	glm::vec3 V = glm::cross(N, U);

	WorldMat = glm::mat4{ 1.0f };

	WorldTrans = glm::mat4{
	1.0f, 0.0f,  0.0f, 0.0f,
	0.0f, 1.0f,  0.0f, 0.0f,
	0.0f, 0.0f,  1.0f, 0.0f,
	sinf(Scale), 0.0f, 0.0f, 1.0f
	};

	WorldRotate = glm::mat4{
	cosf(Scale),  sinf(Scale), 0.0f, 0.0f,
	-sinf(Scale), cosf(Scale), 0.0f, 0.0f,
	 0.0f,        0.0f,        1.0f, 0.0f,
	 0.0f,        0.0f,        0.0f, 1.0f
	};

	WorldScale = glm::mat4{
	 abs(sinf(Scale)), 0.0f, 0.0f, 0.0f,
	 0.0f, abs(cosf(Scale)), 0.0f, 0.0f,
	 0.0f, 0.0f, abs(sinf(Scale)), 0.0f,
	 0.0f, 0.0f, 0.0f, 1.0f
	};

	WorldPerspect = glm::mat4{
		1.0f / (tanHalfFOV * ar), 0.0f,             0.0f, 0.0f,
		0.0f,                1.0f / tanHalfFOV,      0.0f, 0.0f,
		0.0f, 0.0f,          (-zN - zF) / zR,  2.0f * zF * zN / zR,
		0.0f, 0.0f,          1.0f,              0.0f
	};

	WorldCamTrans = glm::mat4{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
	   -cameraPos.x, -cameraPos.y, -cameraPos.z, 1.0f,
	};

	WorldCamRotate= glm::mat4{
	U.x,V.x,N.x,0.0f,
	U.y,V.y,N.y,0.0f,
	U.z,V.z,N.z,0.0f,
	0.0f,0.0f,0.0f,1.0f,
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);



	glutMainLoop();
}


