#include <windows.h>
#include <gl.h>

#if 0
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
	)
#else
int main()
#endif
{
	HDC    hdc   = 0 ;
	HGLRC  hglrc = 0 ;

	// create an OpenGL rendering context 
	hglrc = wglCreateContext( hdc ) ;

	// make it this thread's current rendering context 
	wglMakeCurrent( hdc, hglrc ) ;

	// make the color a deep blue hue 
	glClearColor( 0.0F, 0.0F, 0.4F, 1.0F ) ;

	// make the shading smooth
	glShadeModel( GL_SMOOTH );  // clear the color buffers 

	glClear( GL_COLOR_BUFFER_BIT ) ;

	// specify a red triangle 
	glBegin( GL_TRIANGLES ) ;
	    glColor3f( 1.0F, 0.0F, 0.0F ) ;
		glVertex2f( 10.0F, 10.0F ) ;
	    glVertex2f( 250.0F, 50.0F ) ;
		glVertex2f( 105.0F, 280.0F ) ;
	glEnd( ) ;

	// create bitmaps for the device context font's first 256 glyphs 
	wglUseFontBitmaps( hdc, 0, 256, 1000 ) ;

	// move bottom left, southwest of the red triangle 
	glRasterPos2f( 30.0F, 300.0F ) ;

	// set up for a string-drawing display list call 
	glListBase( 1000 ) ;

	// draw a string using font display lists 
	glCallLists( 12, GL_UNSIGNED_BYTE, "Red Triangle" ) ;

	// get all those commands to execute 
	glFlush( ) ;

	// delete our 256 glyph display lists 
	glDeleteLists( 1000, 256 ) ;

	// make the rendering context not current 
	wglMakeCurrent( NULL, NULL ) ;

	// release the device context 
	ReleaseDC( NULL, hdc ) ;

	// delete the rendering context 
	wglDeleteContext( hglrc ) ;

	Sleep( 6000 ) ;
	return 0 ;
}
