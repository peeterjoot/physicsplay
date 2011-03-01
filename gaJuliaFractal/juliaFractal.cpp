// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

// Copyright 2007, Daniel Fontijne, University of Amsterdam -- fontijne@science.uva.nl

#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined (OSX)
	#include <OpenGL/gl.h>
	#include <OpenGL/glext.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>

#include <e2ga.h>
#include <glut_util.h>

using namespace e2ga ;

const char *WINDOW_TITLE = "Geometric Algebra, Chapter 7, Example 5: Fractals" ;

// GLUT state information
int g_viewportWidth = 800 ;
int g_viewportHeight = 600 ;
int g_GLUTmenu ;

int g_mouseButton = -1 ;
e2ga::vector g_position ;
mv::Float g_zoom = 0.007f ;
int g_maxIter = 30 ;
e2ga::vector g_c ;

// mouse position on last call to MouseButton() / MouseMotion()
e2ga::vector g_prevMousePos ;

// *!*HTML_TAG*!* fractal
void computeJulia(const e2ga::vector &translation, const e2ga::vector &c, mv::Float zoom, int maxIter,
					std::vector<unsigned char> &rgbBuffer, int width, int height) {
	int idx = 0 ;

	e1_t e = e1 ;

	// for each pixel in the image, evaluate fractal function:
	for (int imageY = 0 ; imageY < height ; imageY++) {
		for (int imageX = 0 ; imageX < width ; imageX++) {
			double imageXf = (double)(imageX-width/2) ;
			double imageYf = (double)(imageY-height/2) ;
			e2ga::vector p(e2ga::vector::coord_e1_e2, imageXf, imageYf) ;
			e2ga::vector x = zoom * p - translation ;
			double normSquared ;

			for (int i = 0 ; i < maxIter ; i++) {
				//x = x * e * x + c ; // n = 2
				//x = x * e * x * e * x + c ; // n = 3
				//x = x * e * x * e * x * e * x + c ; // n = 4
				x = x * e * x * e * x * e * x * e * x + c ; // n = 5
			
				normSquared = norm2( x ) ;

				#define MAX_NORM_SQUARED 1e4f
		        	if (normSquared > MAX_NORM_SQUARED)
				{
					break ;
				}
			}

			// convert to colours
			double valF = normSquared * 256.0 * 256.0 * 256.0 / MAX_NORM_SQUARED ;
			int v = valF ;

			rgbBuffer[idx + 0] = v & 0xFF ;
			rgbBuffer[idx + 1] = (v >> 8) & 0xFF ;
			rgbBuffer[idx + 2] = (v >> 16) & 0xFF ;

			idx += 3 ;
		}
	}
}

void computeMandelbrot( std::vector<unsigned char> &rgbBuffer, int width, int height )
{
	int idx = 0 ;

	e1_t e = e1 ;

//x0 = scaled x co-ordinate of pixel (must be scaled to lie somewhere in the interval (-2.5 to 1)
//y0 = scaled y co-ordinate of pixel (must be scaled to lie somewhere in the interval (-1, 1)
	
	e2ga::vector c( e2ga::vector::coord_e1_e2, -2.5, -1 ) ;
	e2ga::vector dx ;
	e2ga::vector dy ;
	dx.set_e1( 3.5/(double)width ) ;
	dy.set_e2( 2.0/(double)height ) ;

#if 0
	printf( "dx=%s\n", dx.c_str_f() ) ;
	printf( "dy=%s\n", dy.c_str_f() ) ;
	printf( "dx=%f,%f\n", dx.get_e1(), dx.get_e2() ) ;
	printf( "dy=%f,%f\n", dy.get_e1(), dy.get_e2() ) ;
	fflush(NULL) ;
	return ;
#endif

	// for each pixel in the image, evaluate fractal function:
	for (int imageY = 0 ; imageY < height ; imageY++)
	{
		e2ga::vector p(c) ;

		for (int imageX = 0 ; imageX < width ; imageX++)
		{
			double normSquared ;
			e2ga::vector x = p ;

			int i = 0 ;
			#define MAX_MAND_ITERS 15
			for ( ; i < MAX_MAND_ITERS ; i++ )
			{
				x = x * e * x + p ;
			
				normSquared = norm2( x ) ;

				#define MAX_MAND_NORM_SQUARED 16.0f
		        	if ( normSquared >= MAX_MAND_NORM_SQUARED )
				{
					break ;
				}
			}

		        if ( normSquared >= MAX_MAND_NORM_SQUARED )
			{
				// 0's for black, 255's for white.
#if 0
				rgbBuffer[idx + 0] = 255 ;
				rgbBuffer[idx + 1] = 255 ;
				rgbBuffer[idx + 2] = 255 ;
#endif
				rgbBuffer[idx + 0] = 0 ;
				rgbBuffer[idx + 1] = 0 ;
				rgbBuffer[idx + 2] = 0 ;
			}
			else
			{
				double valF = normSquared * 256.0 * 256.0 * 256.0 / MAX_MAND_NORM_SQUARED ;
				int v = valF ;

#if 1
				rgbBuffer[idx + 0] = v & 0xFF ;
				rgbBuffer[idx + 1] = (v >> 8) & 0xFF ;
				rgbBuffer[idx + 2] = (v >> 16) & 0xFF ;
#endif
#if 0
				rgbBuffer[idx + 0] = 255 - (v & 0xFF) ;
				rgbBuffer[idx + 1] = 255 - ((v >> 8) & 0xFF) ;
				rgbBuffer[idx + 2] = 255 - ((v >> 16) & 0xFF) ;
#endif
			}

#if 0
			printf( "(%d,%d): iters: %d, n: %f ; RGB:%02X,%02X,%02X\n", imageX, imageY, i, normSquared, rgbBuffer[idx + 0], rgbBuffer[idx + 1], rgbBuffer[idx + 2] ) ;
			printf( "c=%s\n", c.c_str_f() ) ;
			printf( "p=%s\n", p.c_str_f() ) ;
#endif

			idx += 3 ;

			p += dx ;
		}

		c += dy ;
	}
}

//#define DO_JULIA
void display() {
	//doIntelWarning() ; // warn for possible problems with pciking on Intel graphics chipsets

	// setup projection & transform
	glViewport(0, 0, g_viewportWidth, g_viewportHeight) ;
	glMatrixMode(GL_PROJECTION) ;
	glLoadIdentity() ;
	glOrtho(0, g_viewportWidth, 0, g_viewportHeight, -100.0, 100.0) ;
	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity() ;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f) ;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	glDisable(GL_DEPTH_TEST) ;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) ;

	// render fractal:
	int width = g_viewportWidth ^ (g_viewportWidth & 3) ;
	int height = g_viewportHeight ;
	std::vector<unsigned char>buf(width * height * 3) ;
#if defined DO_JULIA
	computeJulia(g_position, g_c, g_zoom, g_maxIter, buf, width, height) ;
#else
	computeMandelbrot(buf, width, height) ;
#endif

	glRasterPos2f(0.0f, 0.0f) ;
	glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, &buf[0]) ;

#if defined DO_JULIA
	glColor3f(0.5f, 0.5f, 1.0f) ;
	void *font = GLUT_BITMAP_HELVETICA_18 ;
	renderBitmapString(20, 20, font, "Press 1 .. 9 to set number of iterations.") ;
	renderBitmapString(20, 40, font, "Use mouse buttons to translate, modify and zoom.") ;
#endif

	glutSwapBuffers() ;
}

void reshape(GLint width, GLint height) {
	g_viewportWidth = width ;
	g_viewportHeight = height ;

	// redraw viewport
	glutPostRedisplay() ;
}


e2ga::vector mousePosToVector(int x, int y) {
	x -= g_viewportWidth / 2 ;
	y -= g_viewportHeight / 2 ;

	return e2ga::vector( e2ga::vector::coord_e1_e2, x, y ) ;
}

void MouseButton(int button, int state, int x, int y) {
	g_mouseButton = button ;
	g_prevMousePos = mousePosToVector(x, y) ;

}

// 
// I've messed this up translating from gasandbox syntax to the gaigen 2.5.1 syntax.  Not too big of a deal since
// the mouse heuristics were hard to figure out anyways.  Revisit this later.
//
void MouseMotion(int x, int y) {
	// get mouse position, motion
	e2ga::vector mousePos = mousePosToVector(x, y) ;
	e2ga::mv motion = (mousePos - g_prevMousePos) ;
	motion *= (-1.0f / (double)g_viewportWidth) ;

	if (g_mouseButton == GLUT_LEFT_BUTTON) {
		motion *= g_zoom ;
		motion *= -200.0f ;
		g_position = g_position - motion ;
	}
	else if (g_mouseButton == GLUT_MIDDLE_BUTTON) {
		e2ga::mv c(g_c) ;
		c += motion ;

		g_c = c ;
	}
	else if (g_mouseButton == GLUT_RIGHT_BUTTON) {
		g_zoom /= 1.5 ;
		//g_zoom *= 1.5 ;
		//g_zoom *= (1.0 + 0.5 * motion.get_e2()) ;
	}

	// redraw viewport
	glutPostRedisplay() ;
}

void Keyboard(unsigned char key, int x, int y) {
	// set
	if ((key >= '1') && (key <= '9'))
		g_maxIter = 10 * (key - '0') ;

	// redraw viewport
	glutPostRedisplay() ;
}

int main(int argc, char*argv[]) {


	if ( 3 == argc )
	{
		double d_r = strtod( argv[1], NULL ) ;
		double d_i = strtod( argv[2], NULL ) ;

		g_c = e2ga::vector( e2ga::vector::coord_e1_e2, d_r, d_i ) ;

		printf( "c = (%f,%f)\n", d_r, d_i ) ;
	}
	else
	{
		// Default:
		g_c = e2ga::vector( e2ga::vector::coord_e1_e2, -0.835f, -0.2321f ) ;
	}

	// profiling for Gaigen 2:
	//e2ga::g2Profiling::init() ;

	// GLUT Window Initialization:
	glutInit (&argc, argv) ;
	glutInitWindowSize(g_viewportWidth, g_viewportHeight) ;
	glutInitDisplayMode( GLUT_RGB | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH) ;
	glutCreateWindow(WINDOW_TITLE) ;

	// Register callbacks:
	glutDisplayFunc(display) ;
	glutReshapeFunc(reshape) ;
	glutKeyboardFunc(Keyboard) ;
	glutMouseFunc(MouseButton) ;
	glutMotionFunc(MouseMotion) ;

	glutMainLoop() ;

	return 0 ;
}
