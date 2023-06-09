#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "glm.h"
#include "structs.h"
#include "cabecalho.h"

// Constantes globais
#define FPS 17.0
#define CARRINHOS 9.0
#define QTDECHAO 3.0
#define VELOCIDADE_RODA 0.5
#define TAMANHO 10
#define CAVALOS 5
#define VELOCIDADE_CAVALO 0.5
#define CONSTANTE 0.03
#define AMP_CAVALO 1
#define VEL_TORRE 3
#define XICARAS 6
#define VEL_XX 4
#define TIMER 0.000001
#define ROT_ROCKET 1

// Variaveis globais
Objeto3D	    rodaGG_base,rodaGG_aro,rodaGG_carro, arvore1, arvore2, terreno,pedra_1,pedra_2,pedra_3, fonte, pipoca, pipoca1,
		    banco, terreno_rua,terreno_rcurva,poste,lanchonete,lanchonete1,carrossel_base,carrossel_cavalo, mesa, torreB, torreC,
		    XM_base,XM_xicara, banco_Cadeira,baseF,foguetes,meio_fio,carro;
spriteObject    wallpaper_menu, wallpaper_controles, wallpaper_creditos, jogar, controles, creditos, sair_menu, sair_creditos, mouse, loadingO,
		indicadorCamera, indicadorBrinquedo;
vetorR3         camera, cursor;
int             keyboard[256], tela = 1, light = 0, xMouse = 0, yMouse = 0, modoCamera = 2, isLightingOn = 1, start=0,randomX=0,randomX1=0,fogOn=1, cameraBrinquedos=0, timer = 0;
float           matAmbAndDif[4], matShine[1], altura = 720, largura = 1280, pi = 70.686569, theta = 179.093338, auxRotacaoRGG = 0, auxRotacaoCAR = 0, 
		        auxRotacaoX = 0,alturaCavalo[CAVALOS],velAlt[CAVALOS],alturaTorre = 0,velTor, torreP=0, rotacaoXX[XICARAS],
		        rotacaoXXX[XICARAS], auxRotacaoF = 0,VEL_XICARA = 2, m = 1.0;
Mix_Chunk       *som1;

// Parâmetros do modelo de iluminação: MATERIAL
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void main(int argc, char** argv)
{
    // Inicializacao
    glutInit(&argc, argv);

    // Definindo versao do GLUT
    glutInitContextVersion(1,1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // Configuracoeses iniciais da janela GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glutInitWindowSize(largura, altura);
    glutInitWindowPosition (0, 0);

    // Inicializando a Janela
    glutCreateWindow("Lego Park");

    glutEnterGameMode();
    srand(time(0));

    // Seta valores iniciais    
    setup();
 
    // Callbacks
    glutDisplayFunc(desenhaMinhaCena);
    glutReshapeFunc(redimensiona);
    glutTimerFunc(FPS,refresh,FPS);
    glutKeyboardFunc(teclaPressionada);
    glutKeyboardUpFunc(teclaSegurada);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);

    glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL); 
	glEnable(GL_LIGHT_MODEL_AMBIENT);

    // Loop
    glutMainLoop();
}

#include "brinquedos.h"
#include "draws_aux.h"
#include "cod_aux.h"
#include "refresh.h"
#include "draws.h"
#include "setup.h"
#include "keyboard.h"
#include "mouse.h"
#include "musicas.h"
