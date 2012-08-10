#include "ParabolaCore/3DView.h"


#ifdef PARABOLA_ANDROID
#include <ParabolaCore/RendererGLES.h>
#elif defined PARABOLA_WINDOWS
#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#endif

PARABOLA_NAMESPACE_BEGIN

/// Apply the camera to openGL
void View3D::apply(){
	/*glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1024/768, 1, 10000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(m_eye.x,m_eye.y,m_eye.z, m_center.x, m_center.y, m_center.z, 0, 1, 0);*/
};

PARABOLA_NAMESPACE_END