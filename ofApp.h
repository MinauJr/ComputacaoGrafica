#pragma once
#include "ofMain.h"
#include "materiais.h"

#define MAX_SIZE        10
#define TOP_VIEW		0	// Top view 
#define FRONT_VIEW		1	// Front view 
#define BACK_VIEW       2   // Back view Identifier
#define CUSTOM_VIEW		3	// Custom view Identifier

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// Variaveis
	//camara
	ofVec3f camera;         //x,y,z
	GLfloat lookAtAngle;
	GLint view;

	//rotacao do elev
	bool isRot; 
	GLfloat RotVel, RotAng;
	GLfloat p;
	ofVec3f camPos, elevPos;

	// Floor
	GLint	resFloorX, resFloorY;
	GLfloat floorLarg, floorAlt;
	GLfloat spotLarg, spotAlt;           //spot é a "celula" do chao

	// Predios
	GLfloat materials[150];
	GLfloat scales[3 * MAX_SIZE * (MAX_SIZE + 2)];
	GLint	modes[3 * MAX_SIZE * (MAX_SIZE + 2)];
	
	//textura
	ofImage skybox;
	ofImage tower;
	ofImage pyramid;
	ofImage roof;

	//Elevador
	GLfloat elevadorAltMax, elevadorVel, elevadorFloor, elevadorAlt, elevadorAltAtual;
	bool	movElevador;

	//lights
	bool ambientOn;
	bool ambientGeralOn;
	bool dirOn;
	bool pointOn;
	bool autoMove;
	bool spotOn;
	bool spotOn2;
	bool difusaOn;
	bool especularOn;

	//foco
	GLfloat spotAtC, spotAtL, spotAtQ;
	GLfloat spotAtC2, spotAtL2, spotAtQ2;

	GLfloat ambientGeralLight[4];
	GLfloat especularLight[4];
	GLfloat difusaLight[4];
	GLfloat ambientLight[4];

	GLfloat dirVec[4];
	GLfloat dirAmb[4];
	GLfloat dirDif[4];
	GLfloat dirSpec[4];
	ofVec3f dirVec3f;
	GLfloat dirVecTheta;

	GLfloat pointPos[4];
	GLfloat pointAmb[4];
	GLfloat pointDif[4];
	GLfloat pointSpec[4];
	GLfloat pointZtheta;

	GLfloat spotDir[3];
	GLfloat spotPos[4];
	GLfloat spotAmb[4];
	GLfloat spotDif[4];
	GLfloat spotSpec[4];


	GLfloat spotDir2[3];
	GLfloat spotPos2[4];
	GLfloat spotAmb2[4];
	GLfloat spotDif2[4];
	GLfloat spotSpec2[4];


	GLfloat focoExp;
	GLfloat focoCut;

	GLfloat focoExp2;
	GLfloat focoCut2;
	//
	inline void piramide(ofImage text,GLfloat comp, GLfloat larg, GLfloat alt) {
		//base
		glBegin(GL_QUADS);

		glVertex3f(-comp / 2., larg / 2., 0);
		glVertex3f(-comp / 2., -larg / 2., 0);
		glVertex3f(comp / 2., -larg / 2., 0);
		glVertex3f(comp / 2., larg / 2., 0);
		glEnd();

		glEnable(GL_TEXTURE);
		text.bind();        //text

		//face 1
		glBegin(GL_TRIANGLES);
		glTexCoord2f(1,1); glVertex3f(comp / 2., larg / 2., 0);
		glTexCoord2f(0.5,0); glVertex3f(0., 0., alt);
		glTexCoord2f(0,1); glVertex3f(-comp / 2., larg / 2., 0);


		//face 2
		glTexCoord2f(1, 1); glVertex3f(-comp / 2., larg / 2., 0);
		glTexCoord2f(0.5, 0); glVertex3f(0., 0., alt);
		glTexCoord2f(0, 1); glVertex3f(-comp / 2., -larg / 2., 0);

		//face 3
		glTexCoord2f(1, 1); glTexCoord2f(1, 1);  glVertex3f(-comp / 2., -larg / 2., 0);
		glTexCoord2f(0.5,0); glVertex3f(0., 0., alt);
		glTexCoord2f(0, 1); glVertex3f(comp / 2., -larg / 2., 0);

		//face 4
		glTexCoord2f(1, 1); glTexCoord2f(1, 1);  glVertex3f(comp / 2., -larg / 2., 0);
		glTexCoord2f(0.5, 0); glVertex3f(0., 0., alt);
		glTexCoord2f(0, 1); glVertex3f(comp / 2., larg / 2., 0);

		glEnd();
		text.unbind();
		glDisable(GL_TEXTURE);
	}
	inline void cube_unit_text(ofImage textura, ofImage roof1) {   //para os predios darem
		glEnable(GL_TEXTURE);

		textura.bind();
		glBegin(GL_QUADS);
		
		// back
		glTexCoord2f(0, 0); glVertex3f(-p, -p, -p);
		glTexCoord2f(0, 1); glVertex3f(p, -p, -p);
		glTexCoord2f(1, 1); glVertex3f(p, p, -p);
		glTexCoord2f(1, 0); glVertex3f(-p, p, -p);

		// top
		glTexCoord2f(0, 0); glVertex3f(-p, -p, -p);
		glTexCoord2f(0, 1); glVertex3f(-p, -p, p);
		glTexCoord2f(1, 1); glVertex3f(p, -p, p);
		glTexCoord2f(1, 0); glVertex3f(p, -p, -p);

		// bottom
		glTexCoord2f(0, 0); glVertex3f(-p, p, p);
		glTexCoord2f(0, 1); glVertex3f(-p, p, -p);
		glTexCoord2f(1, 1); glVertex3f(p, p, -p);
		glTexCoord2f(1, 0); glVertex3f(p, p, p);

		// left
		glTexCoord2f(0, 0); glVertex3f(-p, -p, p);
		glTexCoord2f(0, 1); glVertex3f(-p, -p, -p);
		glTexCoord2f(1, 1); glVertex3f(-p, p, -p);
		glTexCoord2f(1, 0); glVertex3f(-p, p, p);

		// right
		glTexCoord2f(0, 0); glVertex3f(p, -p, p);
		glTexCoord2f(0, 1); glVertex3f(p, p, p);
		glTexCoord2f(1, 1);glVertex3f(p, p, -p);
		glTexCoord2f(1, 0); glVertex3f(p, -p, -p);

		glEnd();
		textura.unbind();

		roof1.bind();
		glBegin(GL_QUADS);
		//frente
		glTexCoord2f(0, 0); glVertex3f(-p, -p, p);
		glTexCoord2f(0, 1); glVertex3f(-p, p, p);
		glTexCoord2f(1, 1); glVertex3f(p, p, p);
		glTexCoord2f(1, 0); glVertex3f(p, -p, p);

		glEnd();
		roof1.unbind();

		glDisable(GL_TEXTURE);
	}

	// Draws a unit cube centered in the origin 
	inline void cube_unit() {
		glBegin(GL_QUADS);
		// front
		glVertex3f(-p, -p, p);
		glVertex3f(-p, p, p);
		glVertex3f(p, p, p);
		glVertex3f(p, -p, p);

		// back
		glVertex3f(-p, -p, -p);
		glVertex3f(p, -p, -p);
		glVertex3f(p, p, -p);
		glVertex3f(-p, p, -p);

		// top
		glVertex3f(-p, -p, -p);
		glVertex3f(-p, -p, p);
		glVertex3f(p, -p, p);
		glVertex3f(p, -p, -p);

		// bottom
		glVertex3f(-p, p, p);
		glVertex3f(-p, p, -p);
		glVertex3f(p, p, -p);
		glVertex3f(p, p, p);

		// left
		glVertex3f(-p, -p, p);
		glVertex3f(-p, -p, -p);
		glVertex3f(-p, p, -p);
		glVertex3f(-p, p, p);

		// right
		glVertex3f(p, -p, p);
		glVertex3f(p, p, p);
		glVertex3f(p, p, -p);
		glVertex3f(p, -p, -p);
		glEnd();
	}
	// Draws a unit malha centered in the origin with m x n squares 
	inline void malha_unit(GLint m, GLint n) {
		GLfloat x_start = -0.5;
		GLfloat y_start = -0.5;
		GLfloat x_step = 1.0 / GLfloat(m);
		GLfloat y_step = 1.0 / GLfloat(n);

		glBegin(GL_QUADS);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				glVertex2d(i * x_step + x_start, j * y_step + y_start);
				glVertex2d(i * x_step + x_start, (j + 1) * y_step + y_start);
				glVertex2d((i + 1) * x_step + x_start, (j + 1) * y_step + y_start);
				glVertex2d((i + 1) * x_step + x_start, j * y_step + y_start);
			}
		}
		glEnd();
	}

	// Draws a unit cube made of unit malhas centered in the origin 
	inline void cube_malha_unit(GLint m, GLint n) {
		// front
		glPushMatrix();
		glTranslated(0., 0., p);
		malha_unit(m, n);
		glPopMatrix();

		// back
		glPushMatrix();
		glTranslated(0., 0., -p);
		glRotated(180, 0, 1, 0);
		malha_unit(m, n);
		glPopMatrix();

		// top
		glPushMatrix();
		glTranslated(0., -p, 0.);
		glRotated(90, 1, 0, 0);
		malha_unit(m, n);
		glPopMatrix();

		// bottom
		glPushMatrix();
		glTranslated(0., p, 0.);
		glRotated(-90, 1, 0, 0);
		malha_unit(m, n);
		glPopMatrix();

		// left
		glPushMatrix();
		glTranslated(-p, 0., 0.);
		glRotated(-90, 0, 1, 0);
		malha_unit(m, n);
		glPopMatrix();

		// right
		glPushMatrix();
		glTranslated(p, 0., 0.);
		glRotated(90, 0, 1, 0);
		malha_unit(m, n);
		glPopMatrix();
		
	}
	// Returns the max value between A.x, A.y and A.z
	inline GLfloat max(ofVec3f A) {
		return A.x > A.y ? (A.x > A.z ? A.x : A.z) : (A.y > A.z ? A.y : A.z);
	}

	// Returns the min value between A.x, A.y and A.z
	inline GLfloat min(ofVec3f A) {
		return A.x < A.y ? (A.x < A.z ? A.x : A.z) : (A.y < A.z ? A.y : A.z);
	}

	// Calculates the cross product between A and B
	inline ofVec3f cross(ofVec3f A, ofVec3f B) {
		ofVec3f aux;
		aux.x = A.y * B.z - A.z * B.y;
		aux.y = A.z * B.x - A.x * B.z;
		aux.z = A.x * B.y - A.y * B.x;

		return aux;
	}


	// Returns A normalized
	inline ofVec3f normalize(ofVec3f A) {
		GLfloat ratio = max(A) - min(A);
		A.x = A.x / ratio;
		A.y = A.y / ratio;
		A.z = A.z / ratio;

		return A;
	}

	//implementa o algoritmo de lookAt
	inline void lookat(
		GLfloat camX,
		GLfloat camY,
		GLfloat camZ,
		GLfloat targetX,
		GLfloat targetY,
		GLfloat targetZ,
		GLfloat upX,
		GLfloat upY,
		GLfloat upZ)
	{
		ofVec3f cam = ofVec3f(camX, camY, camZ);
		ofVec3f target = ofVec3f(targetX, targetY, targetZ);
		ofVec3f up = ofVec3f(upX, upY, upZ);


		ofVec3f N = cam - target;
		N = N.normalized();
		ofVec3f U = cross(up, N);
		U = U.normalized();
		ofVec3f V = cross(N, U);
		V = V.normalized();

		GLfloat camTransformMatrix[4][4] = {
			{U.x, V.x, N.x, 0},
			{U.y, V.y, N.y, 0},
			{U.z, V.z, N.z, 0},
			{-U.dot(cam), -V.dot(cam), -N.dot(cam), 1}
		};


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMultMatrixf(&camTransformMatrix[0][0]);
		//glTranslatef(-cam.x, -cam.y, -cam.z);
	}

	//short named function to get screen width
	inline float gw() {
		return ofGetWidth();
	}

	//short named function to get screen height
	inline float gh() {
		return ofGetHeight();
	}

	//short named function to put Frame Rate as window title
	inline void setFrWt() {
		ofSetWindowTitle(ofToString(ofGetFrameRate()));
	}

	// Draws a circle centered in the origin with radius and n segments
	inline void circleFill2D(GLfloat radius, GLint n) {
		glBegin(GL_POLYGON);
		GLfloat angle = 0;
		for (int i = 0; i < n; i++) {
			glVertex2d(radius * cos(angle), radius * sin(angle));
			angle += 2 * PI / n;
		}
		glEnd();
	}

	//calcula o frustum com base em theta, alpha e beta
	inline void perspective(GLfloat theta, GLfloat alpha, GLfloat beta, bool invertX = false, bool invertY = false) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		GLfloat tan = tanf(theta * 0.5 * PI / 180.0);
		GLfloat d = (gh() / 2.0) / tan;
		GLfloat nearClip = d / alpha;
		GLfloat farClip = d * beta;
		GLfloat ymax = nearClip * tan;
		GLfloat xmax = (gw() / gh()) * ymax;
		if (invertX) {
			xmax = -xmax;
		}
		if (invertY) {
			ymax = -ymax;
		}
		glFrustum(-xmax, xmax, -ymax, ymax, nearClip, farClip);
	}

		inline void sphereSkyBox(int res) {
		float dtheta = PI / float(res);
		float dphi = 2 * PI / float(res);

		for (int i = 0; i < res; i++) {
			for (int j = 0; j < res; j++) {
				glBegin(GL_QUADS);

				float x1 = sin(i * dtheta) * cos(j * dphi);
				float y1 = sin(i * dtheta) * sin(j * dphi);
				float z1 = cos(i * dtheta);
				float tx1 = i / float(res);
				float ty1 = j / float(res);
				ofVec3f n1 = ofVec3f(-x1, -y1, -z1);
				glTexCoord2f(ty1, tx1);
				glNormal3f(n1.x, n1.y, n1.z);
				glVertex3f(x1, y1, z1);

				float x2 = sin(i * dtheta) * cos((j + 1) * dphi);
				float y2 = sin(i * dtheta) * sin((j + 1) * dphi);
				float z2 = cos(i * dtheta);
				float tx2 = i / float(res);
				float ty2 = (j + 1) / float(res);
				ofVec3f n2 = ofVec3f(-x2, -y2, -z2);
				glTexCoord2f(ty2, tx2);
				glNormal3f(n2.x, n2.y, n2.z);
				glVertex3f(x2, y2, z2);

				float x3 = sin((i + 1) * dtheta) * cos((j + 1) * dphi);
				float y3 = sin((i + 1) * dtheta) * sin((j + 1) * dphi);
				float z3 = cos((i + 1) * dtheta);
				float tx3 = (i + 1) / float(res);
				float ty3 = (j + 1) / float(res);
				ofVec3f n3 = ofVec3f(-x3, -y3, -z3);
				glTexCoord2f(ty3, tx3);
				glNormal3f(n3.x, n3.y, n3.z);
				glVertex3f(x3, y3, z3);

				float x4 = sin((i + 1) * dtheta) * cos(j * dphi);
				float y4 = sin((i + 1) * dtheta) * sin(j * dphi);
				float z4 = cos((i + 1) * dtheta);
				float tx4 = (i + 1) / float(res);
				float ty4 = j / float(res);
				ofVec3f n4 = ofVec3f(-x4, -y4, -z4);
				glTexCoord2f(ty4, tx4);
				glNormal3f(n4.x, n4.y, n4.z);
				glVertex3f(x4, y4, z4);

				glEnd();
			}
		}
	}
};
