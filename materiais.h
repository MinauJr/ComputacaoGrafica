#ifndef MATERIALS_H
#define MATERIALS_H
#include "ofMain.h"

#define NUM_MAT 5

inline extern string Materiais[] = { "Ruby","Turquoise","Gold","Silver","Esmerald"};

inline void loadMaterial(int material) {

	GLfloat  rubyAmb[] = { 0.1745 ,0.01175 ,0.01175, 1. };
	GLfloat  rubyDif[] = { 0.61424 ,0.04136 ,0.04136, 1. };
	GLfloat  rubySpec[] = { 0.727811 ,0.626959 ,0.626959, 1. };
	GLint  rubyCoef = 0.6 * 128;

	GLfloat  turquoiseAmb[] = { 0.1 ,0.18725 ,0.1745, 1. };
	GLfloat  turquoiseDif[] = { 0.396 ,0.74151 ,0.69102, 1. };
	GLfloat  turquoiseSpec[] = { 0.297254 ,0.30829 ,0.306678, 1. };
	GLint  turquoiseCoef = 0.1 * 128;

	GLfloat  goldAmb[] = { 0.24725 ,0.1995 ,0.0745, 1. };
	GLfloat  goldDif[] = { 0.75164 ,0.60648 ,0.22648, 1. };
	GLfloat  goldSpec[] = { 0.628281 ,0.555802 ,0.366065, 1. };
	GLint  goldCoef = 0.4 * 128;

	GLfloat  silverAmb[] = { 0.19225 ,0.19225 ,0.19225, 1. };
	GLfloat  silverDif[] = { 0.50754 ,0.50754 ,0.50754, 1. };
	GLfloat  silverSpec[] = { 0.508273 ,0.508273 ,0.508273, 1. };
	GLint  silverCoef = 0.4 * 128;

	GLfloat  esmeraldAmb[] = { 0.0215 ,0.1745 ,0.0215, 1. };
	GLfloat  esmeraldDif[] = { 0.07568 ,0.61424 ,0.07568, 1. };
	GLfloat  esmeraldSpec[] = { 0.633 ,0.727811 ,0.633, 1. };
	GLint    esmeraldCoef = 0.6 * 128;


	switch (material) {
	case 3: //……………………………………………………………………………………………ruby
		glMaterialfv(GL_FRONT, GL_AMBIENT, rubyAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, rubyDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, rubySpec);
		glMaterialf(GL_FRONT, GL_SHININESS, rubyCoef);
		break;
	case 1: //……………………………………………………………………………………………turquoise
		glMaterialfv(GL_FRONT, GL_AMBIENT, turquoiseAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, turquoiseDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, turquoiseSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, turquoiseCoef);
		break;
	case 2: //……………………………………………………………………………………………gold
		glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, goldCoef);
		break;
	case 0: //……………………………………………………………………………………………silver
		glMaterialfv(GL_FRONT, GL_AMBIENT, silverAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silverDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, silverSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, silverCoef);
		break;

	case 4: //……………………………………………………………………………………………esmerald
		glMaterialfv(GL_FRONT, GL_AMBIENT, esmeraldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, esmeraldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, esmeraldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, esmeraldCoef);
		break;
	}
}

#endif