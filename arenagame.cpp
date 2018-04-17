#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include <time.h>
#include "tinyxml.h"

using namespace std;

int giraCanhao=0;
int gira=-90;
int angulo=0;
float numPassos=2;
int anteriorX=0;
int velocidade;


//circulo
typedef struct circle{
	float cx;
	float cy;
	float r;
	string cor;
	string id;
}circle;

//retangulo
int altura;
int largura;
int quadX;
int quadY;
string quadFill;
string quadId;

typedef struct tiro{
    float x;
    float y;
    float teta;
}tiro;
std::vector<tiro>t;
std::vector<tiro>tiroInimigo1;
std::vector<tiro>tiroInimigo2;
std::vector<tiro>tiroInimigo3;


circle vetCircle[6];
bool *keyStates = new bool[256];

//retangulo
typedef struct rectangle{
	int x;
	int y;
	int width;
	int height;
	char fill[15];
	char id[26];
}rectangle;

void init();
void desenha(void);
void drawRectangle(int width, int height,int fill, int id);
void drawCircle(int r, int fill, int id);
void drawPoint(float x, float y, int fill);
void resetGame();

void teclado(unsigned char tecla, int x, int y);
void recebeValores();
float distanciaEuclidiana(float x, float y);
float distanciaEuclidianaBordaExterna(float x, float y);
float distanciaEuclidianaInimigo1(float x, float y);
float distanciaEuclidianaInimigo2(float x, float y);
float distanciaEuclidianaInimigo3(float x, float y);
void desenhaTiro(void);
float distanciaEuclidianaTiro(float tiroX, float tiroY);
void lap();
void imprime();
void atualizaMovimentosInimigos();
void desenhaTiroInimigo1();
void atiraInimigo1();
void frequenciaTiro();
void desenhaTiroInimigo2();
void atiraInimigo2();
void desenhaTiroInimigo3();
void atiraInimigo3();
void timer(int value);
void tiroteio();


float posicaoInimigo1_X;
float posicaoInimigo1_Y;
float posicaoInimigo2_X;
float posicaoInimigo2_Y;
float posicaoInimigo3_X;
float posicaoInimigo3_Y;

int vezDeAtirar=0;

int movimentoInimigo1_x = 0;
int movimentoInimigo1_y = 0;
int inverte = 0;
int inverteY = 0;
int somatorioVoltas=48;
int moveInimigo1_x();
int moveInimigo1_y();

int movimentoInimigo2_x = 0;
int movimentoInimigo2_y = 0;
int moveInimigo2_x();
int moveInimigo2_y();
int inverte2 = 0;
int inverteY2 = 0;

int movimentoInimigo3_x = 0;
int movimentoInimigo3_y = 0;
int moveInimigo3_x();
int moveInimigo3_y();
int inverte3 = 0;
int inverteY3 = 0;
int congelaInimigo3 = 0;

int flagLinhaChegada1 = 0;
int flagLinhaChegada2 = 0;
int flagLinhaChegada3 = 0;
int flagLinhaChegada4 = 0;
int flagLinhaChegada5 = 0;
int volta=0;
int ganhou=0;
//int segundo = 0;



float somaRaios();

void keyUp (unsigned char key, int x, int y);
void keyOperations (void) ;

void desenha(void){
	//circulo azul
	
	keyOperations();

	glClear( GL_COLOR_BUFFER_BIT );

	//Circulo Azul
	glPushMatrix();
	glTranslatef(vetCircle[0].cx,vetCircle[0].cy,0);
	drawCircle(vetCircle[0].r, 1, 1);
	glPopMatrix();

	//Circulo Branco
	glPushMatrix();
		glTranslatef(vetCircle[1].cx,vetCircle[1].cy,0);
		drawCircle(vetCircle[1].r, 2, 1);

	glPopMatrix();

	
	//Linha Chegada
	glPushMatrix();
		glTranslatef(554+186/2,376+45/2, 0);//654,476	+136/2			+476+45/2
		drawRectangle(136,45,1,1);// width, height, fill, id
	glPopMatrix();
	
	atualizaMovimentosInimigos();
	
	//vetCircle[2].cx = novo;
	//Inimigo 1
	glPushMatrix();
		glTranslatef(posicaoInimigo1_X,posicaoInimigo1_Y,0);
		drawCircle(vetCircle[2].r, 2, 1);
	glPopMatrix();
	//Inimigo 2
	glPushMatrix();
		glTranslatef(posicaoInimigo2_X,posicaoInimigo2_Y,0);
		drawCircle(vetCircle[3].r, 3, 1);
	glPopMatrix();
	//Inimigo 3
	glPushMatrix();
		glTranslatef(posicaoInimigo3_X,posicaoInimigo3_Y,0);
		drawCircle(vetCircle[4].r, 3, 1);
	glPopMatrix();

	imprime();
    desenhaTiro();
    desenhaTiroInimigo1();
    desenhaTiroInimigo2();
    desenhaTiroInimigo3();
    frequenciaTiro();

    lap();

	///jogador
	glPushMatrix();
		glTranslatef(vetCircle[5].cx, vetCircle[5].cy,0);
        glRotatef(angulo, 0, 0, 1);
        glRotatef(-90,0,0,1);
        //(vetCircle[5].r, 4, 2);
        glScalef(2,2,1);

			//eixo inferior
			glPushMatrix();
				glTranslatef(0,-5,0);
				drawRectangle(25,5,2,1);
			glPopMatrix();
			//eixo superior
			glPushMatrix();
				glTranslatef(0,5,0);
				drawRectangle(25,5,2,1);
			glPopMatrix();

			//roda superior direita
			glPushMatrix();
				glTranslatef(12,5,0);
				glRotatef(gira,0,0,1);
				drawRectangle(5,8,3,1);
			glPopMatrix();

			//roda superior esquerda
			glPushMatrix();
				glTranslatef(-12,5,0);
				glRotatef(gira,0,0,1);
				drawRectangle(5,8,3,1);
			glPopMatrix();

			
			//roda inferior direita
			glPushMatrix();
				glTranslatef(12,-5,0);
				drawRectangle(5,8,3,1);
			glPopMatrix();

			//roda inferior esquerda
			glPushMatrix();
				glTranslatef(-12,-5,0);
				drawRectangle(5,8,3,1);
			glPopMatrix();

			//canhao
			glPushMatrix();
				glTranslatef(0,10,0);
				glRotatef(giraCanhao,0,0,1);
				glTranslatef(0,5,0);
				drawRectangle(4,10,6,1);
			glPopMatrix();
		
		drawRectangle(15,25,2,1);

	glPopMatrix();

	
    if(ganhou==1){
    	glPushMatrix();
    		glColor3f(0,0,0);
    		glTranslatef(400,400,0);
    		drawRectangle(2*vetCircle[0].r,2*vetCircle[0].r,1,1);

    	glPopMatrix();
    	glColor3f(1,0,1);
		glRasterPos2f(340.0 , 400.0);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
		glRasterPos2f(360.0 , 400.0);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
		glRasterPos2f(380.0 , 400.0);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');
		glRasterPos2f(400.0 , 400.0);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'H');
		glRasterPos2f(420.0 , 400.0);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
		glRasterPos2f(440.0 , 400.0);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'U');
    }
    else{
    	glColor3f(1,0,1);
		glRasterPos2f(400.0 , 400.0);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, somatorioVoltas);
    }

	keyOperations();
    
    glutSwapBuffers();

}

void atualizaMovimentosInimigos(){

	posicaoInimigo1_X = vetCircle[2].cx + moveInimigo1_x();
	posicaoInimigo1_Y = vetCircle[2].cy + moveInimigo1_y();
	posicaoInimigo2_X = vetCircle[3].cx + moveInimigo2_x();
	posicaoInimigo2_Y = vetCircle[3].cy + moveInimigo2_y();
	posicaoInimigo3_X = vetCircle[4].cx + moveInimigo3_x();
	posicaoInimigo3_Y = vetCircle[4].cy + moveInimigo3_y();
}

void lap(){

	//PRIMEIRO QUADRANTE
	if(vetCircle[5].cy-376 >= 40 && vetCircle[5].cx>=400){
		flagLinhaChegada1=1;
		flagLinhaChegada2=0;
		flagLinhaChegada3=0;
		flagLinhaChegada4=0;
	}
	//SEGUNDO QUADRANTE
	else if (vetCircle[5].cy-376 >= 0 && vetCircle[5].cx<400){
		flagLinhaChegada2=1;
		flagLinhaChegada3=0;
		flagLinhaChegada4=0;
		
	}
	//TERCEIRO QUADRANTE
	else if (vetCircle[5].cy-376 < 0 && vetCircle[5].cx<400){

		flagLinhaChegada3=1;
		flagLinhaChegada4=0;
	}
	//QUARTO QUADRANTE
	else if (vetCircle[5].cy-376 < 0 && vetCircle[5].cx>=400){
		flagLinhaChegada4=1;
		flagLinhaChegada5=0;

	}
	//FAIXA DE LARGADA
	else{
		flagLinhaChegada5=1;	
	}
	
	if(flagLinhaChegada2==1 && flagLinhaChegada3==1 && flagLinhaChegada4==1 && flagLinhaChegada1==1 && flagLinhaChegada5==1){
		somatorioVoltas++;
		if(somatorioVoltas==48+5){
			ganhou=1;
		}
		flagLinhaChegada1=0;
		flagLinhaChegada2=0;
		flagLinhaChegada3=0;
		flagLinhaChegada4=0;
		flagLinhaChegada5=0;
	}
	//printf("\n%d\t%d\t%d\t%d\t%d",flagLinhaChegada1,flagLinhaChegada2,flagLinhaChegada3,flagLinhaChegada4, flagLinhaChegada5);
}
//MOVIMENTO DO INIMIGO DEBAIXO
int moveInimigo1_x(){

	if (movimentoInimigo1_x == -280){
		inverte = !inverte;
		movimentoInimigo1_x ++ ;
	}
	else if (movimentoInimigo1_x == 190){
		inverte = !inverte;
		movimentoInimigo1_x --;
	}


	if(inverte == 0){
		movimentoInimigo1_x--;	
	}
	else if (inverte == 1){
		movimentoInimigo1_x ++ ;
	}

	return movimentoInimigo1_x;
}

int moveInimigo1_y(){
	if (movimentoInimigo1_y == -45){
		inverteY = !inverteY;
		movimentoInimigo1_y ++ ;
	}
	else if (movimentoInimigo1_y == 30){
		inverteY = !inverteY;
		movimentoInimigo1_y --;
	}


	if(inverteY == 0){
		movimentoInimigo1_y--;	
		
	}
	else if (inverteY == 1){
		movimentoInimigo1_y ++ ;
	}

	return movimentoInimigo1_y;

}


//MOVIMENTO DO INIMIGO 2
int moveInimigo2_x(){

	if (movimentoInimigo2_x == -50){
		inverte2 = !inverte2;
		movimentoInimigo2_x ++ ;
	}
	else if (movimentoInimigo2_x == 50){
		inverte2 = !inverte2;
		movimentoInimigo2_x --;
	}

	// TO USANDO A VARIAVEL "INVERTE" DE OUTRO INIMIGO PARA CONFUNDIR AINDA MAIS O MOVIMENTO DESTE
	if(inverte == 0){
		movimentoInimigo2_x--;	
	}
	else if (inverte == 1){
		movimentoInimigo2_x ++ ;
	}

	return movimentoInimigo2_x;
}

int moveInimigo2_y(){
	if (movimentoInimigo2_y == -45){
		inverteY2 = !inverteY2;
		movimentoInimigo2_y ++ ;
		//printf("\nINCREMENTAAAAA\n");
	}
	else if (movimentoInimigo2_y == 40){
		inverteY2 = !inverteY2;
		movimentoInimigo2_y --;
	}

	if(inverteY2 == 0){
		movimentoInimigo2_y--;	
	}
	else if (inverteY2 == 1){
		movimentoInimigo2_y ++ ;
	}
	//printf("%d\n", movimentoInimigo2_y);
	return movimentoInimigo2_y;

}


//MOVIMENTO DO INIMIGO 3 (DIREITA ACIMA)
int moveInimigo3_x(){

	if (movimentoInimigo3_x == -50){
		inverte3 = !inverte3;
		movimentoInimigo3_x ++ ;
	}
	else if (movimentoInimigo3_x == 50){
		inverte3 = !inverte3;
		movimentoInimigo3_x --;
	}


	if(inverte3 == 0){
		movimentoInimigo3_x--;	
	}
	else if (inverte3 == 1){

		movimentoInimigo3_x ++ ;
	}

	return movimentoInimigo3_x;
}

int moveInimigo3_y(){
	if (movimentoInimigo3_y == -45 && congelaInimigo3 < 20){
		inverteY3 = !inverteY3;
		movimentoInimigo3_y ++ ;
		//printf("\nINCREMENTAAAAA\n");
	}
	else if (movimentoInimigo3_y == 40  && congelaInimigo3 < 20){
		inverteY3 = !inverteY3;
		movimentoInimigo3_y--;

	}

	if(inverteY3 == 0 && congelaInimigo3 < 20){
		movimentoInimigo3_y--;	
	}
	else if (inverteY3 == 1 && congelaInimigo3 < 20){
		movimentoInimigo3_y ++ ;
	}
	if(congelaInimigo3 > 100){
		congelaInimigo3=0;
	}

	if(inverte2==1 && inverte==1){
		congelaInimigo3++;
	}
	//printf("%d\n", movimentoInimigo3_y);
	return movimentoInimigo3_y;

}

void frequenciaTiro(){

}

void tiroteio(){
	vezDeAtirar++;
	if(vezDeAtirar >= 1 && vezDeAtirar <= 5)
		atiraInimigo1();
	if(vezDeAtirar >= 5 && vezDeAtirar <= 10)
		atiraInimigo2();
	if(vezDeAtirar >= 9 && vezDeAtirar <= 15){
		atiraInimigo3();
		
	}
	if(vezDeAtirar>15)
		vezDeAtirar=0;
}

void timer(int value){

			tiroteio();
			glutTimerFunc(500,timer, 1);

}

void imprime(){
/*	printf("\n\t%d\t%d\t%d\t%d\t%d\t%d\t%.1f\t%.1f",movimentoInimigo1_x,movimentoInimigo1_y,
		movimentoInimigo2_x,movimentoInimigo2_y,
		movimentoInimigo3_x,movimentoInimigo3_y,
		vetCircle[5].cx, vetCircle[5].cy);*/
}



void keyOperations (void) {  

	float variacaoX = numPassos*cos(angulo*(M_PI/180));
    float variacaoY = numPassos*sin(angulo*(M_PI/180));

     if(!keyStates['a'] || !keyStates['d']){
        gira = 0;
    }
    
    
    if(keyStates['a'] && keyStates['w'] && (gira < 45)){

    	if((distanciaEuclidiana(-1,0)>=somaRaios()) &&
    		(distanciaEuclidianaBordaExterna(-1,0)<=(vetCircle[0].r- vetCircle[5].r)) &&
		 (distanciaEuclidianaInimigo1(-1,0)>vetCircle[2].r + vetCircle[5].r) && 
		 (distanciaEuclidianaInimigo2(-1,0)>vetCircle[3].r + vetCircle[5].r) && 
		 (distanciaEuclidianaInimigo3(-1,0)>vetCircle[4].r + vetCircle[5].r) &&
		 distanciaEuclidiana(0,1)>=somaRaios()  &&
		 (distanciaEuclidianaBordaExterna(0,1)<=(vetCircle[0].r- vetCircle[5].r)) && 
		(distanciaEuclidianaInimigo1(0,1)>vetCircle[2].r + vetCircle[5].r) && 
		(distanciaEuclidianaInimigo2(0,1)>vetCircle[3].r + vetCircle[5].r) && 
		(distanciaEuclidianaInimigo3(0,1)>vetCircle[4].r + vetCircle[5].r)){
        
            vetCircle[5].cx += variacaoX;
            vetCircle[5].cy += variacaoY;
            if(gira < 0) angulo -= numPassos;
            if(gira > 0) angulo += numPassos;
            gira++;
        }
        
    }
     if(keyStates['d'] && keyStates['w'] && (gira > -45)){
		if((distanciaEuclidiana(0,1)>=somaRaios())&&(distanciaEuclidianaBordaExterna(0,1)<=(vetCircle[0].r- vetCircle[5].r)) && (distanciaEuclidianaInimigo1(0,1)>vetCircle[2].r+vetCircle[5].r) && (distanciaEuclidianaInimigo2(0,1)>vetCircle[3].r+vetCircle[5].r) && (distanciaEuclidianaInimigo3(0,1)>vetCircle[4].r+vetCircle[5].r)&& ((distanciaEuclidiana(1,0)>=somaRaios()) && (distanciaEuclidianaBordaExterna(1,0)<=(vetCircle[0].r- vetCircle[5].r)) && (distanciaEuclidianaInimigo1(1,0)>vetCircle[2].r+vetCircle[5].r) && (distanciaEuclidianaInimigo2(1,0)>vetCircle[3].r+vetCircle[5].r) && (distanciaEuclidianaInimigo3(1,0)>vetCircle[4].r+vetCircle[5].r))){

            vetCircle[5].cx += variacaoX;
            vetCircle[5].cy += variacaoY;
            if(gira < 0) angulo -= numPassos;
            if(gira > 0) angulo += numPassos;
            gira--;
		}        
    }
    if(keyStates['a'] && keyStates['s'] && (gira > -45)){
		if((distanciaEuclidiana(-1,0)>=somaRaios())&&(distanciaEuclidianaBordaExterna(-1,0)<=(vetCircle[0].r- vetCircle[5].r)) && (distanciaEuclidianaInimigo1(-1,0)>vetCircle[2].r+vetCircle[5].r) && (distanciaEuclidianaInimigo2(-1,0)>vetCircle[3].r+vetCircle[5].r) && (distanciaEuclidianaInimigo3(-1,0)>vetCircle[4].r+vetCircle[5].r) && ((distanciaEuclidiana(0,-1)>=somaRaios())&&(distanciaEuclidianaBordaExterna(0,-1)<=(vetCircle[0].r- vetCircle[5].r)) && (distanciaEuclidianaInimigo1(0,-1)>vetCircle[2].r+vetCircle[5].r) && (distanciaEuclidianaInimigo2(0,-1)>vetCircle[3].r+vetCircle[5].r) && (distanciaEuclidianaInimigo3(0,-1)>vetCircle[4].r+vetCircle[5].r))){
        
            vetCircle[5].cx -= variacaoX;
            vetCircle[5].cy -= variacaoY;
            if(gira < 0) angulo -= numPassos;
            if(gira > 0) angulo += numPassos;
            gira++;
		}        
    }
    if(keyStates['d'] && keyStates['s'] && (gira < 45)){
		if((distanciaEuclidiana(0,-1)>=somaRaios())&&(distanciaEuclidianaBordaExterna(0,-1)<=(vetCircle[0].r- vetCircle[5].r)) && (distanciaEuclidianaInimigo1(0,-1)>vetCircle[2].r+vetCircle[5].r) && (distanciaEuclidianaInimigo2(0,-1)>vetCircle[3].r+vetCircle[5].r) && (distanciaEuclidianaInimigo3(0,-1)>vetCircle[4].r+vetCircle[5].r) && ((distanciaEuclidiana(1,0)>=somaRaios()) && (distanciaEuclidianaBordaExterna(1,0)<=(vetCircle[0].r- vetCircle[5].r)) && (distanciaEuclidianaInimigo1(1,0)>vetCircle[2].r+vetCircle[5].r) && (distanciaEuclidianaInimigo2(1,0)>vetCircle[3].r+vetCircle[5].r) && (distanciaEuclidianaInimigo3(1,0)>vetCircle[4].r+vetCircle[5].r))){
        
            vetCircle[5].cx -= variacaoX;
            vetCircle[5].cy -= variacaoY;
            if(gira < 0) angulo -= numPassos;
            if(gira > 0) angulo += numPassos;
            gira--;
		}        
    }
    if(keyStates['a'] && (gira < 45)){

	        gira += 45;

    }
    if(keyStates['d'] && (gira > -45)){
		
    	    gira -= 45;
  		
    }
    if(keyStates['w']){
		if((distanciaEuclidiana(0,1)>=somaRaios())&&(distanciaEuclidianaBordaExterna(0,1)<=(vetCircle[0].r- vetCircle[5].r)) && (distanciaEuclidianaInimigo1(0,1)>vetCircle[2].r+vetCircle[5].r) && (distanciaEuclidianaInimigo2(0,1)>vetCircle[3].r+vetCircle[5].r) && (distanciaEuclidianaInimigo3(0,1)>vetCircle[4].r+vetCircle[5].r)){
        
            vetCircle[5].cx += variacaoX;
            vetCircle[5].cy += variacaoY;
            if(gira < 0) angulo -= numPassos;
            if(gira > 0) angulo += numPassos;
		}        
    }
    if(keyStates['s']){
		if((distanciaEuclidiana(0,-1)>=somaRaios())&&(distanciaEuclidianaBordaExterna(0,-1)<=(vetCircle[0].r- vetCircle[5].r)) && (distanciaEuclidianaInimigo1(0,-1)>vetCircle[2].r+vetCircle[5].r) && (distanciaEuclidianaInimigo2(0,-1)>vetCircle[3].r+vetCircle[5].r) && (distanciaEuclidianaInimigo3(0,-1)>vetCircle[4].r+vetCircle[5].r)){
        
            vetCircle[5].cx -= variacaoX;
            vetCircle[5].cy -= variacaoY;
            if(gira > 0) angulo -= numPassos;
            if(gira < 0) angulo += numPassos;
		}        
    }
    if(angulo > 360){
        angulo -= 360;
    }
    else if(angulo < -360){
        angulo += 360;
    }


    if(keyStates['q']){
    	giraCanhao++;
    }
    else if(keyStates['e']){
    	giraCanhao--;	
    }

    

    glutPostRedisplay();

}  

//Movimento Canhao
void passiveMotion(int x, int y){

	if(anteriorX < x && giraCanhao<45){
		giraCanhao++;

	}
	else if(anteriorX >= x && giraCanhao>-45)
		giraCanhao--;
	anteriorX=x;
}
/*****************************************************************************************************************************/
/*			TIRO 				tiros  			TIRO 		TIRO
/*****************************************************************************************************************************/
//TIRO
void DrawCircle(float cx, float cy, float r, int num_segments){
    glBegin(GL_TRIANGLE_FAN);
    for(int ii = 0; ii < num_segments; ii++){
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}


void atiraInimigo1(){

	float d = sqrt (pow(posicaoInimigo1_X - vetCircle[5].cx,2) + (pow(posicaoInimigo1_Y - vetCircle[5].cy,2)));
    tiro tirosInimigo1;
    tirosInimigo1.x = posicaoInimigo1_X +  ((posicaoInimigo1_X-vetCircle[5].cx) / d ) ;
    tirosInimigo1.y = posicaoInimigo1_Y +  ((posicaoInimigo1_Y-vetCircle[5].cy) / d ) ;
    tirosInimigo1.teta = angulo;
    t.push_back(tirosInimigo1);
}


void desenhaTiroInimigo1(){
	if(!tiroInimigo1.empty()){
		for(int i = 0; i < t.size(); i++){
			float x_tiroInimigo1 = tiroInimigo1[i].x;
			float y_tiroInimigo1 = tiroInimigo1[i].y;
		//	float ang_tiroInimigo1 = tiroInimigo1[i].teta;

			glColor3f(1.0,0,1.0);
			DrawCircle(x_tiroInimigo1, y_tiroInimigo1, 4, 10);
		//	printf("\n%.1f\t %.1f",x_t, y_t);
			tiroInimigo1[i].x +=  ((posicaoInimigo1_X-vetCircle[5].cx) / distanciaEuclidianaInimigo1(0,1) ) *velocidade;
			tiroInimigo1[i].y +=  ((posicaoInimigo1_Y-vetCircle[5].cy) / distanciaEuclidianaInimigo1(0,1) ) *velocidade;

			float dTiro = sqrt(pow(tiroInimigo1[i].x - vetCircle[5].cx,2) + pow(tiroInimigo1[i].y - vetCircle[5].cy,2));

			if(dTiro < 4+vetCircle[5].r){
			//	printf("\nPEGOOOOOOOOOOUUUUUUUUUUUUU");
			}

			//printf("pow: x: %.1f\n y: %.1f\n", t[i].x, t[i].y);
//			if (distanciaEuclidianaTiro(t[i].x, t[i].y) <= 4+vetCircle[2].r)
				
		}
	}	
}

//TIRO DE INIMIGO 2

void atiraInimigo2(){

	float d = sqrt (pow(vetCircle[3].cx - vetCircle[5].cx,2) + (pow(vetCircle[3].cy - vetCircle[5].cy,2)));
    tiro tirosInimigo2;
    tirosInimigo2.x = posicaoInimigo2_X +  ((posicaoInimigo2_X-vetCircle[5].cx) / d ) ;
    tirosInimigo2.y = posicaoInimigo2_Y +  ((posicaoInimigo2_Y-vetCircle[5].cy) / d ) ;
    tirosInimigo2.teta = angulo;
    t.push_back(tirosInimigo2);
}


void desenhaTiroInimigo2(){
	if(!tiroInimigo2.empty()){
		for(int i = 0; i < t.size(); i++){
			float x_tiroInimigo2 = tiroInimigo2[i].x;
			float y_tiroInimigo2 = tiroInimigo2[i].y;
		//	float ang_tiroInimigo1 = tiroInimigo1[i].teta;

			glColor3f(1.0,0,1.0);
			DrawCircle(x_tiroInimigo2, y_tiroInimigo2, 4, 10);
		//	printf("\n%.1f\t %.1f",x_t, y_t);
			tiroInimigo2[i].x +=  ((posicaoInimigo2_X-vetCircle[5].cx) / distanciaEuclidianaInimigo1(0,1) ) *velocidade;
			tiroInimigo2[i].y +=  ((posicaoInimigo2_Y-vetCircle[5].cy) / distanciaEuclidianaInimigo1(0,1) ) *velocidade;

			float dTiro = sqrt(pow(tiroInimigo2[i].x - vetCircle[5].cx,2) + pow(tiroInimigo2[i].y - vetCircle[5].cy,2));

			if(dTiro < 4+vetCircle[5].r){
			//	printf("\nPEGOOOOOOOOOOUUUUUUUUUUUUU");
			}

			//printf("pow: x: %.1f\n y: %.1f\n", t[i].x, t[i].y);
//			if (distanciaEuclidianaTiro(t[i].x, t[i].y) <= 4+vetCircle[2].r)
				
		}
	}	
}


//TIRO DE INIMIGO 2

void atiraInimigo3(){

	float d = sqrt (pow(posicaoInimigo3_X - vetCircle[5].cx,2) + (pow(posicaoInimigo3_Y - vetCircle[5].cy,2)));
    tiro tirosInimigo3;
    tirosInimigo3.x = posicaoInimigo3_X +  ((posicaoInimigo3_X-vetCircle[5].cx) / d ) ;
    tirosInimigo3.y = posicaoInimigo3_Y +  ((posicaoInimigo3_Y-vetCircle[5].cy) / d ) ;
    tirosInimigo3.teta = angulo;
    t.push_back(tirosInimigo3);
}


void desenhaTiroInimigo3(){
	if(!tiroInimigo3.empty()){
		for(int i = 0; i < t.size(); i++){
			float x_tiroInimigo3 = tiroInimigo3[i].x;
			float y_tiroInimigo3 = tiroInimigo3[i].y;
		//	float ang_tiroInimigo1 = tiroInimigo1[i].teta;

			glColor3f(1.0,0,1.0);
			DrawCircle(x_tiroInimigo3, y_tiroInimigo3, 4, 10);
		//	printf("\n%.1f\t %.1f",x_t, y_t);
			tiroInimigo3[i].x +=  ((posicaoInimigo3_X-vetCircle[5].cx) / distanciaEuclidianaInimigo1(0,1) ) *velocidade;
			tiroInimigo3[i].y +=  ((posicaoInimigo3_Y-vetCircle[5].cy) / distanciaEuclidianaInimigo1(0,1) ) *velocidade;

			float dTiro = sqrt(pow(tiroInimigo3[i].x - vetCircle[5].cx,2) + pow(tiroInimigo3[i].y - vetCircle[5].cy,2));

			if(dTiro < 4+vetCircle[5].r){
			//	printf("\nPEGOOOOOOOOOOUUUUUUUUUUUUU");
			}

			//printf("pow: x: %.1f\n y: %.1f\n", t[i].x, t[i].y);
//			if (distanciaEuclidianaTiro(t[i].x, t[i].y) <= 4+vetCircle[2].r)
				
		}
	}	
}

//TIRO do jogador
void desenhaTiro(void){


	if(!t.empty()){
		for(int i = 0; i < t.size(); i++){
			float x_t = t[i].x;
			float y_t = t[i].y;
			float ang_t = t[i].teta;

			glColor3f(1.0,0,1.0);
			DrawCircle(x_t, y_t, 4, 10);
		//	printf("\n%.1f\t %.1f",x_t, y_t);
			t[i].x += cos(ang_t * M_PI/180.0)*velocidade;
			t[i].y += sin(ang_t * M_PI/180.0)*velocidade;

			float d= sqrt(pow(t[i].x - posicaoInimigo1_X,2) + pow(t[i].y - posicaoInimigo1_Y,2));

//			if(d < 5)
			//	printf("\nACERTOUUU PARCEIROOOOO");
//			else
			//	printf("\n.");
			//printf("pow: x: %.1f\n y: %.1f\n", t[i].x, t[i].y);
//			if (distanciaEuclidianaTiro(t[i].x, t[i].y) <= 4+vetCircle[2].r)
				
		}
	}
}

//TIRO
void mouse(int botao, int estado, int x, int y){
    if(botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
        tiro tiros;
        tiros.x = vetCircle[5].cx + cos((angulo) * M_PI/180.0)*(25/2.0) + cos((angulo + giraCanhao ) * M_PI/180.0)*14/2;
        tiros.y = vetCircle[5].cy + sin((angulo) * M_PI/180.0)*(25/2.0) + sin((angulo + giraCanhao ) * M_PI/180.0)*14/2;
        tiros.teta = angulo + giraCanhao ;
        t.push_back(tiros);

    }
}

void keyUp (unsigned char key, int x, int y) {  
	keyStates[key] = false;
} 

void drawRectangle(int width, int height,int fill, int id){
	if(fill==1)
		glColor3f(0,0,0);
	else if(fill==2)
		glColor3f(.8,.5,0);
	else if(fill==3)
		glColor3f(.5,.1,.8);
	else if(fill==4)
		glColor3f(1,0,1);
	else if(fill==5)
		glColor3f(0,1,1);
	else if(fill==6)
		glColor3f(1,1,0);
	else
		glColor3f(1,1,1);
	int h=height/2;
	int w=width/2;
	glBegin(GL_QUADS);
		glVertex2f(-w,-h);
		glVertex2f(w, -h);
		glVertex2f(w,h);
		glVertex2f(-w, h);
	glEnd();
}



void drawCircle(int r, int fill, int id){
	int i, numeroLinhas=360;
	float radiano;
	float pi=3.14159;
	if(fill==1)
		glColor3f(0,0,1);
	else if(fill==2)
		glColor3f(1,1,1);
	else if(fill==3)
		glColor3f(1,0,0);
	else if(fill==4)
		glColor3f(0,1,0);
	else if(fill==5)
		glColor3f(.5,.1,.8);
	else if(fill==6)
		glColor3f(0,0,0);

	glBegin(GL_POLYGON);
		for(i=0 ; i< numeroLinhas ; i++){
			radiano = i*pi/180;
			glVertex2f(cos(radiano)*r, sin(radiano)*r);
			
		}
	glEnd();
}
void teclado(unsigned char tecla, int x, int y){
		keyStates[tecla] = true;
		glutPostRedisplay();
}

float distanciaEuclidianaTiro(float tiroX, float tiroY){
	return (sqrt(pow(tiroX - vetCircle[2].cx+movimentoInimigo1_x, 2) + pow(tiroY - vetCircle[2].cy+movimentoInimigo1_y,2)));
}

float distanciaEuclidiana(float x, float y){
	
	//printf("quad1: %.1f\tquad2: %.1f\n",pow(vetCircle[1].cx - vetCircle[5].cx, 2), pow(vetCircle[1].cy - vetCircle[5].cy,2));
	return (sqrt(pow(vetCircle[1].cx - vetCircle[5].cx-x, 2) + pow(vetCircle[1].cy - vetCircle[5].cy-y,2)));
}
float distanciaEuclidianaBordaExterna(float x, float y){
	return (sqrt(pow(vetCircle[0].cx - vetCircle[5].cx-x, 2) + pow(vetCircle[0].cy - vetCircle[5].cy-y,2)));	
}
float distanciaEuclidianaInimigo1(float x, float y){
	return (sqrt(pow(vetCircle[2].cx+movimentoInimigo1_x - vetCircle[5].cx-x, 2) + pow(vetCircle[2].cy+movimentoInimigo1_y - vetCircle[5].cy-y,2)));	
}
float distanciaEuclidianaInimigo2(float x, float y){
	return (sqrt(pow(vetCircle[3].cx+movimentoInimigo2_x - vetCircle[5].cx-x, 2) + pow(vetCircle[3].cy+movimentoInimigo2_y - vetCircle[5].cy-y,2)));	
}
float distanciaEuclidianaInimigo3(float x, float y){
	return (sqrt(pow(vetCircle[4].cx+movimentoInimigo3_x - vetCircle[5].cx-x, 2) + pow(vetCircle[4].cy+movimentoInimigo3_y - vetCircle[5].cy-y,2)));	
}
float somaRaios(){
	return (vetCircle[1].r+vetCircle[5].r);
}

void init(){
	glMatrixMode(GL_PROJECTION);
    gluOrtho2D(vetCircle[0].cx-vetCircle[0].r,vetCircle[0].cx+vetCircle[0].r,vetCircle[0].cy-vetCircle[0].r,vetCircle[0].cy+vetCircle[0].r);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1,1,1,1);
    // pizza pré-assada 997321653
}




//Função de parse xml
char * loadConfig(char *  path){
    strcat(path, "config.xml");

    TiXmlDocument doc;
    if(!doc.LoadFile(path))
        printf("Problema!\n");

    //Aplicacao
    TiXmlElement* root = doc.FirstChildElement();

    if(root == NULL){
        printf("Deu problema! Xml invalido\n");
        doc.Clear();
    }

    //arquivoDaArena
	TiXmlElement* principal = root->FirstChildElement();
     const char* attr;
    //nome do arquivo -> nome
    std::string nome_a = principal->Attribute("nome");
    //caminho do arquivo -> caminho
    std::string caminho_a = principal->Attribute("caminho");
    //tipo do arquivo -> tipo
    std::string tipo_a = principal->Attribute("tipo");
    //concatenação de tudo
    std::string caminho_quase = caminho_a + nome_a + '.' + tipo_a;
    char * caminho_final = strdup(caminho_quase.c_str());
    //carro
    principal = principal->NextSiblingElement();
    attr = principal->Attribute("velTiro");
    velocidade = atof(attr);
    doc.Clear();

	return caminho_final;
}


void svg(char * caminho_a){
	TiXmlDocument doc;

    if(!doc.LoadFile(caminho_a)){
        printf("\nProblema com o SVG!\n");
        return;
    }

  	//<svg xmlns="http://www.w3.org/2000/svg" version="1.1">
	TiXmlElement* root = doc.FirstChildElement();

    if(root == NULL){
        	doc.Clear();
        	return;
    }
    TiXmlElement* principal;
    //Contadores das posições dos circulos e dos retângulos
    int contCirc,contRet;
    //
    for(principal = root->FirstChildElement(), contCirc = 0,contRet = 0;
                    principal != NULL; principal = principal->NextSiblingElement()){
        string elenName = principal->Value();
         const char* attr;
        if(elenName == "rect"){
            attr = principal->Attribute("x");
            quadX = atof(attr);

            attr = principal->Attribute("y");
            quadY = atof(attr);

            attr = principal->Attribute("width");
            largura = atof(attr);

            attr = principal->Attribute("height");
            altura = atof(attr);

            attr = principal->Attribute("fill");
            quadFill = atof(attr);

            attr = principal->Attribute("id");
            quadId = atof(attr);
            contRet++;
        }
        else if(elenName == "circle"){

            attr = principal->Attribute("cx");
            vetCircle[contCirc].cx = atof(attr);

            attr = principal->Attribute("cy");
            vetCircle[contCirc].cy = atof(attr);

            attr = principal->Attribute("r");
            vetCircle[contCirc].r = atof(attr);

            vetCircle[contCirc].cor = principal->Attribute("fill");

            vetCircle[contCirc].id = principal->Attribute("id");
            contCirc++;
        }
    }
 doc.Clear();
}




int main (int argc, char *argv[]){
	

	//recebeValores();

	char*  caminho;
    caminho = loadConfig(argv[1]);
    svg(caminho);


	glutInit (&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(2*vetCircle[0].r,2*vetCircle[0].r);
	glutInitWindowPosition(905,75);

	glutCreateWindow("Beethoven");
	
	init();
	glutDisplayFunc(desenha);
	glutKeyboardFunc(teclado);
	glutKeyboardUpFunc(keyUp);
	glutPassiveMotionFunc(passiveMotion);
	glutMouseFunc(mouse);
	glutTimerFunc(3000, timer, 1);


	glutMainLoop();
	return 0;
}