#include "GLHeader.h"
#include "ShaderUtil.h"
#include "CameraUtil.h"
#include "RenderModeUtil.h"
#include "ImageUtil.h"
#include "TextUtil.h"
#include "MouseUtil.h"
#include "SoundUtil.h"
#include "DataUtil.h"
#include "FontLoaderUtil.h"
#include "FWM.h"

#include "Mode1.h"

#include <iostream>
#include <map>
#include <ctime>

int WIDTH = 1200;
int HEIGHT = 800;

GLfloat ASPECT;
Rect rect;

std::string VENDOR;

ShaderUtil shader;
CameraUtil cam;
CamaraControlUtil camUtil;
RenderModeUtil renderMode;
ImageUtil imageUtil;
TextUtilUnicode textUnicode;
MouseUtil mouse;
SoundUtil soundUtil;
DataUtil dataUtil;
FontLoaderUtil fontloaderUtil;
FWM fw;

clock_t StartTime, EndTime;


GLvoid DisplayReshape(int w, int h) {
	glViewport(0, 0, w, h);
	WIDTH = w;
	HEIGHT = h;
}

GLvoid GLMain() {
	StartTime = clock();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	soundUtil.Update();
	fw.Routine();

	glutSwapBuffers();
	glutPostRedisplay();

	EndTime = clock();
	fw.SetFrameTime(float(EndTime - StartTime) / 1000);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GL_MULTISAMPLE);

	glutInitWindowPosition(GetSystemMetrics(SM_CXSCREEN) / 2 - WIDTH / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - HEIGHT / 2);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("GL2D");

	if (StartWithFullScreen)
		glutFullScreen();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Unable to initialize GLEW\n\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n\n";

	const GLubyte* VecdorInfo = glGetString(GL_VENDOR);
	if (VecdorInfo) {
		VENDOR = reinterpret_cast<const char*>(VecdorInfo);
		if (PrintVendorInfoOpt)
			std::cout << "GPU Vendor: " << VENDOR << "\n\n";
	}

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader.LoadVertexShader("GLSL//GLSL_vertex.glsl");
	shader.LoadFragmentShader("GLSL//GLSL_fragment.glsl");
	shader.CreateShader(ImageShader);

	shader.LoadFragmentShader("GLSL//GLSL_fragment_text.glsl");
	shader.CreateShader(TextShader);

	imageUtil.Init();
	soundUtil.Init();

	fw.Init(Mode1::GameMode1, Mode1::SetController);

	glutDisplayFunc(GLMain);
	glutReshapeFunc(DisplayReshape);
	glutMainLoop();
}