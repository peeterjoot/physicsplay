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

#ifndef _GLUT_UTIL_H_
#define _GLUT_UTIL_H_

/**
Renders 'string' at raster position x, y.  
Between each character, 'spacing' pixels are inserted.
The font can be:
GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18 
*/
void renderSpacedBitmapString(float x, float y, float spacing, void *font, const char *string);

/**
Calls renderSpacedBitmapString() with spacing set to 0.0
*/
inline void renderBitmapString(float x, float y, void *font, const char *string) {
	renderSpacedBitmapString(x, y, 0.0f, font, string);
}


/** returns the width of the string, as rendered through renderSpacedBitmapString */
float getSpacedBitmapStringWidth(float spacing, void *font, const char *string);

/**
Calls renderSpacedBitmapString() with spacing set to 0.0
*/
inline float getBitmapStringWidth(void *font, const char *string) {
	return getSpacedBitmapStringWidth(0.0f, font, string);
}

#endif /* _GLUT_UTIL_H_ */
 
