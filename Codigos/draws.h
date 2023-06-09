// Desenho do jogo
void desenhaMinhaCena()
{
    glMatrixMode(GL_MODELVIEW);
    glColor4f(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(1,1,1,1);
    
    if(tela == 0)
    {
        drawObject(wallpaper_menu);
        drawObject(jogar);
        drawObject(controles);
        drawObject(creditos);
        drawObject(sair_menu);
    }

    else if(tela == 1)
    {

	float colorFog[4] = {m, m, m, 1}; 

		if(fogOn==1)    
			glEnable(GL_FOG);
		else
			glDisable(GL_FOG);
    	
    	glFogi(GL_FOG_MODE, GL_LINEAR);    // GL_EXP, GL_EXP2 e GL_LINEAR
    	glFogf(GL_FOG_START, 100);         // Inicio e termino do fog para GL_LINEAR -3.00 ate 3.00
    	glFogf(GL_FOG_END, 200);
    	glFogf(GL_FOG_DENSITY, 0.005);     // Densidade do fog 0.00 á 3.00
    	glFogfv(GL_FOG_COLOR, colorFog);

        movimentacao();

        // Coordenadas da camera em coordenadas esfericas
        camera.x = 100*sin(pi)*cos(theta);
        camera.z = 100*sin(pi)*sin(theta);
        camera.y = 100*cos(pi);

		// DIA E NOITE
	
		/*const*/ GLfloat light_ambient[]  = { m, m, m, 1.0f };
		atualizaLuz();
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);

		//

        glLoadIdentity();

        switch(modoCamera)
        {
            // Camera simples
			case 1:	
				switch(cameraBrinquedos){
					case 1:
						gluLookAt(-80, 40, 0,-120, 30, 0, 0, 1, 0); // Roda Gigante
                        indicadorBrinquedo.textura = loadTexture("../Imagens/RodaGigante.png");
					break;
					case 2:
						gluLookAt(-30, 30, -10, -60, 28, -40, 0, 1, 0); // Torre que cai
                        indicadorBrinquedo.textura = loadTexture("../Imagens/DownTower.png");
		            break;
					case 3:
						gluLookAt(-108, 25, -50,-108, 23, -55, 0, 1, 0); // Carrossel
                        indicadorBrinquedo.textura = loadTexture("../Imagens/Carrossel.png");
					break;
					case 4:
						gluLookAt(-70, 30, -5, -70, 20, 40, 0, 1, 0); // Foguete
                        indicadorBrinquedo.textura = loadTexture("../Imagens/LegoRocket.png");
					break;
					case 5:
						gluLookAt(-110, 30, 30, -110, 26, 40, 0, 1, 0); // Xicara
                        indicadorBrinquedo.textura = loadTexture("../Imagens/XicaraMaluca.png");
					break;
				}
            	break;
		
            // Camera primeira pessoa
            case 2:

                gluLookAt(cursor.x + 0,cursor.y + 0, cursor.z + 0, cursor.x + camera.x,cursor.y + camera.y, cursor.z + camera.z, 0, 1, 0);
                break;

            // Camera terceira pessoa
            case 3:

                gluLookAt(cursor.x + camera.x,cursor.y + camera.y, cursor.z + camera.z, cursor.x + 0,cursor.y + 0, cursor.z + 0, 0, 1, 0);
                break;
            	
            default:
				break;
        }
			
		if (isLightingOn)
		{
	        	glEnable(GL_LIGHTING);
		}

		carros();
		chao();
		lanchonetes();
		desenhaOBJ(fonte,0);
		pipocas();
		postes();
		torre();
		arvores();
		desenhaRodaGigante();
		carrossel();
		bancos();
		ruas();
		xicaras_malucas();
		bancosCadeira();
		rocket();
		meiosFios();

		if (isLightingOn)
	    {
	    	glDisable(GL_LIGHTING);
	    }	

   		glColor4f(1, 1, 1, 1);
		desenhaInterface();
    }

    else if(tela == 2)
    {
    	drawObject(wallpaper_controles);
    	drawObject(sair_creditos);
    }

    else if(tela == 3)
    {
        drawObject(wallpaper_creditos);
        drawObject(sair_creditos);
    }
    
    glutSwapBuffers();
}

//Desenha os objetos 2D
void drawObject(spriteObject objeto)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, objeto.textura);

    glPushMatrix();
    glTranslatef(objeto.posicao.x, objeto.posicao.y, 0);

    glBegin(GL_TRIANGLE_FAN);
    {
        glTexCoord2f(0, 0);
        glVertex3f(-objeto.dimensoes.x/2, -objeto.dimensoes.y/2,  0);
        glTexCoord2f(1, 0);
        glVertex3f( objeto.dimensoes.x/2, -objeto.dimensoes.y/2,  0);
        glTexCoord2f(1, 1);
        glVertex3f( objeto.dimensoes.x/2,  objeto.dimensoes.y/2,  0);
        glTexCoord2f(0, 1);
        glVertex3f(-objeto.dimensoes.x/2,  objeto.dimensoes.y/2,  0);
    }

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void config2D(){

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, largura, 0, altura, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, largura, altura);

}

void config3D(){

	glEnable(GL_DEPTH_TEST);
    glViewport (0, 0, largura, altura);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)largura/(float)altura, 0.2, 400.0);     //colocar fovy entre 45.0 e 60.0
    glMatrixMode(GL_MODELVIEW);
    begin3d();
	glLoadIdentity();

}

void desenhaInterface()
{

	config2D();
	drawObject(indicadorCamera);
    if(modoCamera == 1)
        drawObject(indicadorBrinquedo);
	config3D();

}

// Desenha objetos 3D
void desenhaOBJ(Objeto3D objeto, float rotacao)
{
	glPushMatrix();
	    	glTranslatef(objeto.posicao.x,objeto.dimensoes.y/2+objeto.posicao.y,objeto.posicao.z);
	    	glScalef(objeto.aumento.x,objeto.aumento.y,objeto.aumento.z);
		glRotatef(rotacao,0,1,0);
	    	glCallList(objeto.listaVisualizacao);
	glPopMatrix();
}

// Desenha objetos 3D em uma posição especifica passada como referência
void desenhaPosicao(Objeto3D objeto,float centrox, float centroz, float rotacao)
{
	glPushMatrix();
		glTranslatef(centrox,0,centroz);
		desenhaOBJ(objeto,rotacao);
	glPopMatrix();
}

void chao()
{

		glPushMatrix();
		for(int random = -QTDECHAO, auxrandom, random1, auxrandom1 ; random <= QTDECHAO ;random++)
		{
			auxrandom = random*terreno.dimensoes.x;
			for(random1 = -QTDECHAO ;random1 <= QTDECHAO; random1++)
			{
				auxrandom1 = random1*terreno.dimensoes.x;
				glPushMatrix();
	    				glTranslatef(auxrandom,0,auxrandom1);
		            		glScalef(terreno.aumento.x,terreno.aumento.y,terreno.aumento.z);
		            		glCallList(terreno.listaVisualizacao);
				glPopMatrix();
			}
		}		
		glPopMatrix();
}

void ruas()
{
	glPushMatrix();

		// Ajustar erro terreno/rua
		glTranslatef(0,terreno.dimensoes.y/2,0);

		// Ruas em torno da fonte e alongando pros extremos laterais
		// Baixo
		aux_rua(11,terreno_rua.dimensoes.x*2,-terreno_rua.dimensoes.x*5,0);
		// Cima Fonte -> Pipocas
		aux_rua(11,-terreno_rua.dimensoes.x*2,-terreno_rua.dimensoes.x*5,0);
		// Esquerda Brinquedo1 -> Brinquedo2
		aux_rua(5,-terreno_rua.dimensoes.x*2,terreno_rua.dimensoes.x*2.5,1);
		// Direita
		aux_rua(5,-terreno_rua.dimensoes.x*2,-terreno_rua.dimensoes.x*2.5,1);

		// Ruas em torno das pipocas
		aux_rua(3,-terreno_rua.dimensoes.x*4,-terreno_rua.dimensoes.x,0);
		aux_rua(2,-terreno_rua.dimensoes.x*3,terreno_rua.dimensoes.x*2,1);
		aux_rua(2,-terreno_rua.dimensoes.x*3,-terreno_rua.dimensoes.x*2,1);

		// Ruas centrais levando à brinquedo 3
		aux_rua(10,terreno_rua.dimensoes.x*2,0,1);
		aux_rua(9,-terreno_rua.dimensoes.x*13,0,1);

		// Rua brinquedos 1-2
		aux_rua(19,-terreno_rua.dimensoes.x*11,-terreno_rua.dimensoes.x*9,0);

		// Rua brinquedos 4-5
		aux_rua(9,-terreno_rua.dimensoes.x*7,-terreno_rua.dimensoes.x*4,0);

		// Ruas para "fechar" caixa das arvores
		aux_rua(3,-terreno_rua.dimensoes.x,-terreno_rua.dimensoes.x*6,1);
		aux_rua(3,-terreno_rua.dimensoes.x,terreno_rua.dimensoes.x*6,1);

		// Ruas levando para as lanchonetes
		aux_rua(2,0,terreno_rua.dimensoes.x*7,0);
		aux_rua(2,0,-terreno_rua.dimensoes.x*8,0);

		// Ruas curvas
		// Ruas ao lado da lanchonete, na parte oposta da direção dos brinquedos
		glPushMatrix();
			glTranslatef(terreno_rua.dimensoes.x*2,0,0);
			desenhaPosicao(terreno_rcurva,0,-terreno_rua.dimensoes.x*6,-90);
			desenhaPosicao(terreno_rcurva,0,terreno_rua.dimensoes.x*6,180);
		glPopMatrix();

		// Ruas na direção Lanchonete -> Brinquedos
		glPushMatrix();
			glTranslatef(-terreno_rua.dimensoes.x*2,0,0);
			desenhaPosicao(terreno_rcurva,0,-terreno_rua.dimensoes.x*6,0);
			desenhaPosicao(terreno_rcurva,0,terreno_rua.dimensoes.x*6,90);
		glPopMatrix();

		// Ruas próximas à pipoca
		glPushMatrix();
			glTranslatef(-terreno_rua.dimensoes.x*4,0,0);
			desenhaPosicao(terreno_rcurva,0,-terreno_rua.dimensoes.x*2,0);
			desenhaPosicao(terreno_rcurva,0,terreno_rua.dimensoes.x*2,90);
		glPopMatrix();

	glPopMatrix();
}

void meiosFios(){

	//Lado esquerdo
	desenhaPosicao(meio_fio,terreno_rua.dimensoes.x*4,terreno_rua.dimensoes.z/2+meio_fio.dimensoes.z/2+2,0);
	desenhaPosicao(meio_fio,terreno_rua.dimensoes.x*5.5,terreno_rua.dimensoes.z/2+meio_fio.dimensoes.z/2+2,0);
	desenhaPosicao(meio_fio,terreno_rua.dimensoes.x*7,terreno_rua.dimensoes.z/2+meio_fio.dimensoes.z/2+2,0);
	desenhaPosicao(meio_fio,terreno_rua.dimensoes.x*8.5,terreno_rua.dimensoes.z/2+meio_fio.dimensoes.z/2+2,0);
	desenhaPosicao(meio_fio,terreno_rua.dimensoes.x*10,terreno_rua.dimensoes.z/2+meio_fio.dimensoes.z/2+2,0);

	//Lado direito
	desenhaPosicao(meio_fio,terreno_rua.dimensoes.x*4,-(terreno_rua.dimensoes.z/2+meio_fio.dimensoes.z/2+2),0);
	desenhaPosicao(meio_fio,terreno_rua.dimensoes.x*5.5,-(terreno_rua.dimensoes.z/2+meio_fio.dimensoes.z/2+2),0);
	desenhaPosicao(meio_fio,terreno_rua.dimensoes.x*7,-(terreno_rua.dimensoes.z/2+meio_fio.dimensoes.z/2+2),0);
	desenhaPosicao(meio_fio,terreno_rua.dimensoes.x*8.5,-(terreno_rua.dimensoes.z/2+meio_fio.dimensoes.z/2+2),0);
	desenhaPosicao(meio_fio,terreno_rua.dimensoes.x*10,-(terreno_rua.dimensoes.z/2+meio_fio.dimensoes.z/2+2),0);
}

void carros(){
	//Lado direito
	desenhaPosicao(carro,terreno_rua.dimensoes.x*3.25,-(terreno_rua.dimensoes.z/2+carro.dimensoes.z/2+2),0);
	desenhaPosicao(carro,terreno_rua.dimensoes.x*9.25,-(terreno_rua.dimensoes.z/2+carro.dimensoes.z/2+2),0);

	//Lado esquerdo
	desenhaPosicao(carro,terreno_rua.dimensoes.x*4.75,terreno_rua.dimensoes.z/2+carro.dimensoes.z/2+2,180);
}

void pipocas()
{
	// Pipoca da direita
    	desenhaOBJ(pipoca,90);
	// Pipoca da esquerda
	desenhaOBJ(pipoca1,-90);
	// Pipoca do meio
	desenhaPosicao(pipoca,0,-pipoca.posicao.z,0);
}

void bancos()
{
	// Bancos horizontais em frente à pipoca
	// Banco da direita
	desenhaPosicao(banco,pipoca.posicao.x-terreno_rua.dimensoes.x*2,pipoca.posicao.z-2,90);
	// Banco da esquerda
	desenhaPosicao(banco,pipoca.posicao.x-terreno_rua.dimensoes.x*2,pipoca.posicao.z+terreno_rua.dimensoes.x*2+3,90);

	// Bancos verticais em frente à pipoca
	desenhaPosicao(banco,pipoca.posicao.x,pipoca.posicao.z-terreno_rua.dimensoes.x*2,0);
	desenhaPosicao(banco,pipoca.posicao.x,pipoca1.posicao.z+terreno_rua.dimensoes.x*2,180);
}

void postes()
{
	//Postes em torno da fonte
	desenhaPosicao(poste,fonte.dimensoes.x/2-1,fonte.dimensoes.z/2+4,0);
	desenhaPosicao(poste,fonte.dimensoes.x/2-1,-(fonte.dimensoes.z/2+4),0);
	desenhaPosicao(poste,-(fonte.dimensoes.x/2-1),fonte.dimensoes.z/2+4,0);
	desenhaPosicao(poste,-(fonte.dimensoes.x/2-1),-(fonte.dimensoes.z/2+4),0);

	// Postes ao lado das cadeiras e mesas
	desenhaPosicao(poste,fonte.dimensoes.x*1,terreno_rua.dimensoes.x*6.5,0);
	desenhaPosicao(poste,fonte.dimensoes.x*1,-terreno_rua.dimensoes.x*6.5,0);

}

void arvores()
{
	// Arvores próximas à fonte
	// Conjunto do lado esquerdo
	desenhaPosicao(arvore1,arvore1.dimensoes.x/2,fonte.dimensoes.z*1.8,0);
	desenhaPosicao(arvore1,-arvore1.dimensoes.x/2,fonte.dimensoes.z*1.4,0);
	desenhaPosicao(pedra_3,arvore1.dimensoes.x/2,fonte.dimensoes.z*1.8-arvore1.dimensoes.z/2-pedra_3.dimensoes.z/2,45);
	// Conjunto do lado direito
	desenhaPosicao(arvore1,arvore1.dimensoes.x/2,-fonte.dimensoes.z*1.8,0);
	desenhaPosicao(arvore1,-arvore1.dimensoes.x/2,-fonte.dimensoes.z*1.4,0);
	desenhaPosicao(pedra_3,-arvore1.dimensoes.x/2,-fonte.dimensoes.z*1.4-arvore1.dimensoes.z/2-pedra_3.dimensoes.z/2,30);

	//Arvores 1 aleatórias
	desenhaPosicao(arvore1,-terreno_rua.dimensoes.x*7+30,-100,0);
	desenhaPosicao(arvore1,-terreno_rua.dimensoes.x*7-23,-135,0);
	desenhaPosicao(arvore1,-terreno_rua.dimensoes.x*7,170,0);
	desenhaPosicao(arvore1,-terreno_rua.dimensoes.x*7+15,136,30);

	//Arvores 2 aleatórias
	desenhaPosicao(arvore2,-140, 50,0);
	desenhaPosicao(arvore2,-150, -80,0);
	desenhaPosicao(arvore2,-180, 100,0);
	desenhaPosicao(arvore2,-100, 40,0);
	desenhaPosicao(arvore2,0,170,0);
	desenhaPosicao(arvore2,0,-140,0);
	desenhaPosicao(arvore2,50,100,0);
	desenhaPosicao(arvore2,-75,120,0);
	desenhaPosicao(arvore2,100,-80,0);
	desenhaPosicao(arvore2,80,40,0);

	//Pedras 1 aleatórias
	desenhaPosicao(pedra_1,-90,35,0);
	desenhaPosicao(pedra_1,30,70,0);
	desenhaPosicao(pedra_1,60,90,0);
	desenhaPosicao(pedra_1,100,-100,0);
	desenhaPosicao(pedra_1,100,30,0);

	//Pedras 2 aleatórias
	desenhaPosicao(pedra_2,40,140,90);
	desenhaPosicao(pedra_2,50,-140,0);
	desenhaPosicao(pedra_2,100,-50,30);
	desenhaPosicao(pedra_2,80,-120,0);
	desenhaPosicao(pedra_2,150,55,10);
	desenhaPosicao(pedra_2,80,90,-120);

	//Pedras 3 aletórias
	desenhaPosicao(pedra_3,-terreno_rua.dimensoes.x*7-10,-75,0);
	desenhaPosicao(pedra_3,-terreno_rua.dimensoes.x*7+10,-100,0);
	desenhaPosicao(pedra_3,120,40,0);
}

void lanchonetes()
{
	desenhaOBJ(lanchonete,180);
	desenhaOBJ(lanchonete1,0);
}

void bancosCadeira()
{
	desenhaPosicao(banco_Cadeira,terreno_rua.dimensoes.z*1.5,terreno_rua.dimensoes.x*7.5,90);
	desenhaPosicao(banco_Cadeira,-terreno_rua.dimensoes.z*1.5,terreno_rua.dimensoes.x*7.5,90);
	desenhaPosicao(banco_Cadeira,terreno_rua.dimensoes.z*1.5,-terreno_rua.dimensoes.x*7.5,90);
	desenhaPosicao(banco_Cadeira,-terreno_rua.dimensoes.z*1.5,-terreno_rua.dimensoes.x*7.5,90);
}

void loading()
{	
        drawObject(loadingO);
	glutSwapBuffers();
}

void atualizaLuz(){
	
	if(m>=1)
		timer=-1;	
	else if(m<=0)
		timer=1;
		
	m += TIMER*timer;

	if(timer<0)
		timer--;
	else
		timer++;

}
