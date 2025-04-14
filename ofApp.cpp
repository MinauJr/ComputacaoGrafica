#include "ofApp.h"
#include "materiais.h"

void ofApp::setup() {
	glEnable(GL_DEPTH_TEST);
	ofBackground(0.05, 0.05, 0.05);
	glLineWidth(1);
	ofDisableArbTex();

	//textura
	skybox.load("space1.jpg");
	tower.load("tower.jpg");
	pyramid.load("pyramid.jpg");
	roof.load("telhado.jpg");

	//iluminação
	ambientGeralOn = true;
	difusaOn = true;
	especularOn = true;
	ambientOn = true;

	dirOn = false;
	pointOn = false;
	spotOn = false;
	spotOn2 = false;

	autoMove = true;

	pointZtheta = 0;
	dirVecTheta = 0.;

	focoExp = 0;
	focoCut = 1;
	focoExp2 = 0;
	focoCut2 = 1;

	view = 0;
	p = 0.5;      // unitario

	//Floor Parameters
	resFloorX = 6;
	resFloorY = 6;
	floorLarg = gw() * 0.5;
	floorAlt = gh() * 0.5;

	//elevador
	elevadorFloor = 10;
	elevadorAlt = 15;
	elevadorVel = 1.5;
	movElevador = false;

	//rotacao
	RotAng = 0;
	RotVel = 1.5;
	isRot = false;

	//camara
	lookAtAngle = 0;

	//Tamanho Spot
	spotLarg = floorLarg / GLfloat(resFloorX); 
	spotAlt = floorAlt / GLfloat(resFloorY);    

	//Cores tamanhos e modos para os buildings
	for (int i = 0; i < resFloorX; i++) {
		for (int j = 0; j < resFloorY; j++) {
			int step = 3 * i * resFloorX + j * resFloorY;

			//Escolhe cor
			materials[step + 0] = ofRandom(1, 5);

			//escala
			scales[step + 0] = ofRandom(spotLarg / 2, spotLarg - spotLarg / 5);     //largura da base (x)
			scales[step + 1] = ofRandom(spotAlt / 2, spotAlt - spotAlt / 5);	    //altura da base  (y)
			scales[step + 2] = ofRandom(60, 100);						            //altura do predio(z)

			//mode
			modes[step + 0] = (int)ofRandom(2); //0 a 1

			//Se for MALHA_CUBE ... adiciona os valores
			if (modes[step + 0] == 1) {
				modes[step + 1] = ofRandom(3, MAX_SIZE);
				modes[step + 2] = modes[step + 1] + ofRandom(-2, 3);
			}
			if (i == 2 && j == 0) {
				elevadorAltMax = scales[step + 2];
			}

		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	//elevador a subir(chega a cima para, e para no chao)
	if (movElevador) {
		elevadorAltAtual += elevadorVel;
		if (elevadorAltAtual >= elevadorAltMax) {
			movElevador = false;
			elevadorVel = -elevadorVel;
			elevadorAltAtual = elevadorAltMax;
		}
		if (elevadorAltAtual <= 0) {
			movElevador = false;
			elevadorVel = -elevadorVel;
			elevadorAltAtual = 0;
		}
	}
	//if para a rot
	if (isRot) {
		RotAng += RotVel;
		if (RotAng >= 360) {
			isRot = false;
			RotAng = 0;
		}
	}

	//camara a rodar
	if (view == 3) {
		lookAtAngle = ofGetElapsedTimef() * 0.3;
		camera.x = gw() / 2 * cos(lookAtAngle);
		camera.y = gw() / 2 * sin(lookAtAngle);
		//gw nos 2 pq o meu chão é um quadrado, se for retang, gw, gh.
	}

	if (autoMove) {
		//luz pontual
		pointZtheta = fmod(pointZtheta, 180); // Resets after half a circle
		pointPos[0] = gw() / 4 - (gw() / 2 * (pointZtheta / 180.0));

		pointPos[1] = -gw() / 4;

		pointPos[2] = 199 * sin(pointZtheta * PI / 180.0);

		pointZtheta += 0.25;

		///////////////////////////////////////
		//calculo da direcao da luz direcional
		float z = gh() * 0.25 * (cos(dirVecTheta * PI / 180.) * 0.5 + 0.45);
		float y = gh() * 0.5;
		float x = 0;
		dirVec3f = ofVec3f(x, y, z) - ofVec3f(0, 0, 0);
		dirVecTheta += 0.5;
	}

	else {
		//luz pontual
		pointPos[0] = 0;
		pointPos[1] = 0;
		pointPos[2] = 250;

		//luz direcional
		dirVec3f = ofVec3f(0, gh() * 0.5, gh() * 0.25 * 0.95) - ofVec3f(0, 0, 0);
	}

}

//--------------------------------------------------------------
void ofApp::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (view == 0 || view == 2 || view == 3) {
		perspective(60, 100, 100);
	}
	else {
		float viewSize = 500.0f; 
		glOrtho(-viewSize, viewSize, -viewSize * 720.0 / 1280.0, viewSize * 720.0 / 1280.0, 0.1, 5000);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Views
	switch (view) {
	case TOP_VIEW:
		// Top view               //perspetiva
		lookat(0, 0, 700, 0, 0, 0, 0, 1, 0);
		break;

	case FRONT_VIEW:              //ortogonal
		// Front view
		lookat(0, 500, 100, 0, 0, 0, 0, 0, 1);
		break;

	case BACK_VIEW:                //perspetiva

		lookat(0, -700, 150, 0, 0, 0, 0, 0, 1);
		break;

	case CUSTOM_VIEW:				//perspetiva

		lookat(camera.x, camera.y, 300, 0, 0, 0, 0, 0, 1);
		break;

	}
	//#################################################
	//define luzes
	glEnable(GL_LIGHTING);//habilita o uso de iluminação
	glEnable(GL_NORMALIZE);//utiliza versores para normais (normais normalizadas)
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	//#################################################
	//ambiente geral
	if (ambientGeralOn) {
		ambientGeralLight[0] = 1;//R
		ambientGeralLight[1] = 1;//G
		ambientGeralLight[2] = 1;//B
		ambientGeralLight[3] = 1;//useless
	}
	else {
		ambientGeralLight[0] = 0.;
		ambientGeralLight[1] = 0.;
		ambientGeralLight[2] = 0.;
		ambientGeralLight[3] = 1;
	}
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientGeralLight);

	//#################################################
	//luz direcional
	dirVec[0] = dirVec3f.x;//x
	dirVec[1] = dirVec3f.y;//y
	dirVec[2] = dirVec3f.z;//z
	dirVec[3] = 0;//vetor - direção!

	//Componente Ambiente
	if (ambientOn) {
		ambientLight[0] = 0.8;//R
		ambientLight[1] = 0.8;//G
		ambientLight[2] = 0.8;//B
		ambientLight[3] = 1;//useless
	}
	else {
		ambientLight[0] = 0.;
		ambientLight[1] = 0.;
		ambientLight[2] = 0.;
		ambientLight[3] = 1;
	}
	//Componente Difusa
	if (difusaOn) {
		difusaLight[0] = 0.6;//R
		difusaLight[1] = 0.6;//G
		difusaLight[2] = 0.6;//B
		difusaLight[3] = 1;//useless
	}
	else {
		difusaLight[0] = 0.;
		difusaLight[1] = 0.;
		difusaLight[2] = 0.;
		difusaLight[3] = 1;
	}
	//Componente Especular
	if (especularOn) {
		especularLight[0] = 0.8;//R
		especularLight[1] = 0.8;//G
		especularLight[2] = 0.8;//B
		especularLight[3] = 1;//useless
	}
	else {
		especularLight[0] = 0.;
		especularLight[1] = 0.;
		especularLight[2] = 0.;
		especularLight[3] = 1;
	}
	glLightfv(GL_LIGHT0, GL_POSITION, dirVec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusaLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, especularLight);

	if (dirOn) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}
	//#################################################
	//luz pontual
	pointPos[3] = 1;//ponto - posição!

	//Componente Ambiente
	if (ambientOn) {
		ambientLight[0] = 0.8;//R
		ambientLight[1] = 0.8;//G
		ambientLight[2] = 0.8;//B
		ambientLight[3] = 1;//useless
	}
	else {
		ambientLight[0] = 0.;
		ambientLight[1] = 0.;
		ambientLight[2] = 0.;
		ambientLight[3] = 1;
	}
	//Componente Difusa
	if (difusaOn) {
		difusaLight[0] = 0.6;//R
		difusaLight[1] = 0.6;//G
		difusaLight[2] = 0.6;//B
		difusaLight[3] = 1;//useless
	}
	else {
		difusaLight[0] = 0.;
		difusaLight[1] = 0.;
		difusaLight[2] = 0.;
		difusaLight[3] = 1;
	}
	//Componente Especular
	if (especularOn) {
		especularLight[0] = 0.8;//R
		especularLight[1] = 0.8;//G
		especularLight[2] = 0.8;//B
		especularLight[3] = 1;//useless
	}
	else {
		especularLight[0] = 0.;
		especularLight[1] = 0.;
		especularLight[2] = 0.;
		especularLight[3] = 1;
	}

	glLightfv(GL_LIGHT1, GL_POSITION, pointPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, difusaLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, especularLight);

	if (pointOn) {
		glEnable(GL_LIGHT1);
	}
	else {
		glDisable(GL_LIGHT1);
	}

	
	//#################################################
	//LUZ FOCO  1
    //Posicao
	spotPos[0] = -100;
	spotPos[1] = 0.;
	spotPos[2] = 180;
	spotPos[3] = 1.;

	//Direcao

	spotDir[2] = -1.;

	//Componente Ambiente
	if (ambientOn) {
		ambientLight[0] = 0.8;//R
		ambientLight[1] = 0.8;//G
		ambientLight[2] = 0.8;//B
		ambientLight[3] = 1;//useless
	}
	else {
		ambientLight[0] = 0.;
		ambientLight[1] = 0.;
		ambientLight[2] = 0.;
		ambientLight[3] = 1;
	}
	//Componente Difusa
	if (difusaOn) {
		difusaLight[0] = 0.6;//R
		difusaLight[1] = 0.6;//G
		difusaLight[2] = 0.6;//B
		difusaLight[3] = 1;//useless
	}
	else {
		difusaLight[0] = 0.;
		difusaLight[1] = 0.;
		difusaLight[2] = 0.;
		difusaLight[3] = 1;
	}
	//Componente Especular
	if (especularOn) {
		especularLight[0] = 0.8;//R
		especularLight[1] = 0.8;//G
		especularLight[2] = 0.8;//B
		especularLight[3] = 1;//useless
	}
	else {
		especularLight[0] = 0.;
		especularLight[1] = 0.;
		especularLight[2] = 0.;
		especularLight[3] = 1;
	}

	glLightfv(GL_LIGHT2, GL_POSITION, spotPos);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, difusaLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, especularLight);

	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, focoExp);  
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, focoCut);    


	///atenuation
	spotAtC = 1.;
	spotAtL = 0.;
	spotAtQ = 0.;
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, spotAtC);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, spotAtL);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, spotAtQ);
	

	if (spotOn) {
		glEnable(GL_LIGHT2);
	}
	else {
		glDisable(GL_LIGHT2);
	}
	
	//#################################################
	//LUZ FOCO  2
	//Posicao
	spotPos2[0] = 100;
	spotPos2[1] = 0.;
	spotPos2[2] = 180;
	spotPos2[3] = 1.;

	//Direcao

	spotDir2[2] = -1.;

	//Componente Ambiente
	if (ambientOn) {
		ambientLight[0] = 0.8;//R
		ambientLight[1] = 0.8;//G
		ambientLight[2] = 0.8;//B
		ambientLight[3] = 1;//useless
	}
	else {
		ambientLight[0] = 0.;
		ambientLight[1] = 0.;
		ambientLight[2] = 0.;
		ambientLight[3] = 1;
	}
	//Componente Difusa
	if (difusaOn) {
		difusaLight[0] = 0.6;//R
		difusaLight[1] = 0.6;//G
		difusaLight[2] = 0.6;//B
		difusaLight[3] = 1;//useless
	}
	else {
		difusaLight[0] = 0.;
		difusaLight[1] = 0.;
		difusaLight[2] = 0.;
		difusaLight[3] = 1;
	}
	//Componente Especular
	if (especularOn) {
		especularLight[0] = 0.8;//R
		especularLight[1] = 0.8;//G
		especularLight[2] = 0.8;//B
		especularLight[3] = 1;//useless
	}
	else {
		especularLight[0] = 0.;
		especularLight[1] = 0.;
		especularLight[2] = 0.;
		especularLight[3] = 1;
	}

	glLightfv(GL_LIGHT3, GL_POSITION, spotPos2);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDir2);

	glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, difusaLight);
	glLightfv(GL_LIGHT3, GL_SPECULAR, especularLight);

	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, focoExp2); 
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, focoCut2); 

	///atenuation
	spotAtC2 = 1.;
	spotAtL2 = 0.;
	spotAtQ2 = 0.;
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, spotAtC2);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, spotAtL2);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, spotAtQ2);
	

	if (spotOn2) {
		glEnable(GL_LIGHT3);
	}
	else {
		glDisable(GL_LIGHT3);
	}
	glDisable(GL_LIGHTING);
	//#################################################
	if (pointOn) {
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslatef(pointPos[0], pointPos[1], pointPos[2]);
		glScalef(30, 30, 30);
		cube_unit();
		glPopMatrix();
	}

	//representação da posição da Light0
	if (dirOn) {
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslatef(dirVec3f.x, dirVec3f.y, dirVec3f.z);
		glScalef(30, 30, 30);
		cube_unit();
		glPopMatrix();
	}

	if (spotOn) {
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslatef(spotPos[0], spotPos[1], spotPos[2]);
		glScalef(30, 30, 30);
		cube_unit();
		glPopMatrix();
	}

	if (spotOn2) {
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslatef(spotPos2[0], spotPos2[1], spotPos2[2]);
		glScalef(30, 30, 30);
		cube_unit();
		glPopMatrix();
	}
	glEnable(GL_LIGHTING);
	//#################################################

	/////////////////////////////////
	loadMaterial(0);
	glPushMatrix();
	glScalef(floorLarg, floorAlt, 1);
	malha_unit(resFloorX, resFloorY);
	glPopMatrix();

	//Prédios
	for (int i = 0; i < resFloorX; i++) {
		for (int j = 0; j < resFloorX; j++) {
			//Desenha predio
			int step = 3 * i * resFloorX + j * resFloorX;

			if (i == 0 && j == 5) {  
				loadMaterial(2);//piramide
				glPushMatrix();
				glTranslatef((-floorLarg / 2 + spotLarg / 2) + i * spotLarg,					//vai buscar a localizao de acordo com o spot
					(-floorAlt / 2 + spotAlt / 2) + j * spotAlt,
					0);
				piramide(pyramid,scales[step + 0], scales[step + 1], scales[step + 2]);
				glPopMatrix();
				continue;
			}
			if (i == 2 && j == 0) { //elevador & rotacao
				glPushMatrix();
				//vai buscar a localizao do spot
				glTranslatef((-floorLarg / 2 + spotLarg / 2) + i * spotLarg,
					(-floorAlt / 2 + spotAlt / 2) + j * spotAlt,                   //centro do predio, metade da altura do elevador
					elevadorAlt / 2 + elevadorAltAtual);

				glRotatef(RotAng, 0, 0, 1);
				glTranslatef(0, -scales[step + 1] / 2 - elevadorFloor / 2, 1);      //pro centro do elevador

				loadMaterial(1);//elevador turquesa
				glScalef(elevadorFloor, elevadorFloor, elevadorAlt);
				cube_unit();
				glPopMatrix();

				loadMaterial(0);  //ruby
				glPushMatrix();
				glTranslatef((-floorLarg / 2 + spotLarg / 2) + i * spotLarg,					//vai buscar a localizao do spot
					(-floorAlt / 2 + spotAlt / 2) + j * spotAlt,
					scales[step + 2] + 1);
				GLfloat R = (scales[step] > scales[step + 1] ? scales[step] : scales[step + 1]) / 2;  //max entre x e y
				R += elevadorFloor;         
				circleFill2D(R, 20);
				glPopMatrix();
			}

			//Cor
			loadMaterial(materials[step]);
			glPushMatrix();

			//Localizacao
			glTranslatef((-floorLarg / 2 + spotLarg / 2) + i * spotLarg,					//vai buscar a localizao 
				(-floorAlt / 2 + spotAlt / 2) + j * spotAlt,
				scales[step + 2] / 2);


			//Tamanaho
			glScalef(scales[step + 0], scales[step + 1], scales[step + 2]);				//vai buscar a escala (x,y,z)

			//Modo
			switch (modes[step + 0]) {
			case 0:
				cube_unit_text(tower,roof);
				break;
			case 1:
				cube_malha_unit(modes[step + 1], modes[step + 2]);
				break;
			}
			glPopMatrix();

		}
	}
	// Sky box 
	glEnable(GL_TEXTURE);
	skybox.bind();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glColor3f(1, 1, 1);
	glPushMatrix();

	glScalef(gw(), gw(), gw());
	sphereSkyBox(64);
	glPopMatrix();

	skybox.unbind();
	glDisable(GL_TEXTURE);
}

//--------------------------------------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case '1':
		glDisable(GL_CULL_FACE);
		break;

	case '2':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		break;

	case '3':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		break;

	case '4':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT_AND_BACK);
		break;

	case 'g':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;

	case 'f':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;

	case 'v':
		if (++view > 3) view = 0;
		if (view == CUSTOM_VIEW) {
			camPos.x = gw() / 2;
		}
		break;

	case 'e':
		if (!isRot) {

			movElevador = true;
		}
		break;

	case 'r':
		if (!movElevador && elevadorAltAtual == elevadorAltMax) {
			isRot = true;
		}
		break;

	case '6':
		//geral
		ambientGeralOn = !ambientGeralOn;
		break;
	case '7':
		dirOn = !dirOn;
		break;

	case '8':
		pointOn = !pointOn;
		break;

	case 'q':
		autoMove = !autoMove;
		break;

	case '9':
		spotOn = !spotOn;
		break;

	case '0':
		spotOn2 = !spotOn2;
		break;

	case 'l':
		focoCut++;
		if (focoCut > 180) {
			focoCut = 180;
		}
		focoCut2++;
		if (focoCut2 > 180) {
			focoCut2 = 180;
		}
		break;

	case 'k':
		focoCut--;
		if (focoCut < 1) {
			focoCut = 1;
		}
		focoCut2--;
		if (focoCut2 < 1) {
			focoCut2 = 1;
		}
		break;

	case 'd':
		difusaOn = !difusaOn;
		break;

	case 's':
		especularOn = !especularOn;
		break;

	case 'a':
		ambientOn = !ambientOn;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}