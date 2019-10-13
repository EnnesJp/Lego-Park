void cenario();

// Desenho do jogo
void desenhaMinhaCena()
{
    glMatrixMode(GL_MODELVIEW);
    glColor4f(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
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
        movimentacao();

        // Coordenadas da camera em coordenadas esfericas
        camera.x = 100*sin(pi)*cos(theta);
        camera.y = 100*cos(pi);
        camera.z = 100*sin(pi)*sin(theta);

        glLoadIdentity();

        switch(modoCamera)
        {
            // Camera simples
            default:

                gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);
                break;

            // Camera primeira pessoa
            case 2:

                gluLookAt(cursor.x + 0,cursor.y + 0, cursor.z + 0, cursor.x + camera.x,cursor.y + camera.y, cursor.z + camera.z, 0, 1, 0);
                break;

            // Camera terceira pessoa
            case 3:

                gluLookAt(cursor.x + camera.x,cursor.y + camera.y, cursor.z + camera.z, cursor.x + 0,cursor.y + 0, cursor.z + 0, 0, 1, 0);
                break;
        }

    // Esfera indicativa de onde está a luz
	/*	
		glPushMatrix();
        glTranslatef(20.0, 50.0, 50.0);
        glColor3f(0, 0, 0);
        glutWireSphere(2, 8, 8); 
    	glPopMatrix();
	*/
		
	if (isLightingOn)
	{
        glEnable(GL_LIGHTING);
    }
    
	glClearColor(1,1,1,1);
	cenario();
	desenhaRodaGigante();
	desenhaInterface();

	if (isLightingOn)
    {
    	glDisable(GL_LIGHTING);
    }

    }

    else if(tela == 2)
    {

    }

    else if(tela == 3)
    {
        drawObject(wallpaper_creditos);
        drawObject(sair_creditos);
    }
    
    glutSwapBuffers();
}

//Desenha os objetos e imagens
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

void desenhaInterface(){	
        //perguntar como fazer isso
}


void desenhaRodaGigante(){
    int i;
    const float angulo = 360/CARRINHOS;
    const float raio = rodaGG_aro.dimensoes.y/*-(ERRO VISUAL)*/;//tem que arrumar isso daqui ainda
    auxRotacao+=1;
    
    //desenhando a base
    glPushMatrix();
	glTranslatef(rodaGG_aro.posicao.x,rodaGG_aro.posicao.y-rodaGG_aro.dimensoes.y,rodaGG_aro.posicao.z);
	glScalef(rodaGG_base.dimensoes.x,rodaGG_base.dimensoes.y,rodaGG_base.dimensoes.z);
    	glCallList(rodaGG_base.listaVisualizacao);
    glPopMatrix();
    
    glPushMatrix();
		glRotatef(auxRotacao,1,0,0);
	    	glTranslatef(rodaGG_aro.posicao.x, rodaGG_aro.posicao.y, rodaGG_aro.posicao.z);

		//desenhando o aro
		glPushMatrix();
			    glScalef(rodaGG_aro.dimensoes.x,rodaGG_aro.dimensoes.y,rodaGG_aro.dimensoes.z);
			    glCallList(rodaGG_aro.listaVisualizacao);
		glPopMatrix();

		for(i=0; i<CARRINHOS; i++){
			glPushMatrix();
		    //glRotatef(-auxRotacao,1,0,0); //só para teste, faz os carrinhos não girarem
			glTranslatef(0, raio*cos(angulo*i),raio*sin(angulo*i)); //ta dando algum problema aqui pra transladar os acrrinhos
			//printf("\n%f %f %f\n",raio,angulo,angulo*i); //retorna valores corretos
		    glRotatef(-auxRotacao,1,0,0);
			glScalef(rodaGG_carro.dimensoes.x,rodaGG_carro.dimensoes.y,rodaGG_carro.dimensoes.z);
			glCallList(rodaGG_carro.listaVisualizacao);
			glPopMatrix();
		}
    glPopMatrix();
}

void desenhaOBJ(Objeto3D objeto)
{
	glPushMatrix();
	glTranslatef(objeto.posicao.x,objeto.posicao.y,objeto.posicao.z);
	glScalef(objeto.dimensoes.x,objeto.dimensoes.y,objeto.dimensoes.z);
	glCallList(objeto.listaVisualizacao);
	glPopMatrix();
}

void cenario()
{
		// Terreno
		glPushMatrix();
		glTranslatef(0,-100,0);
		for(int random = -QTDECHAO, auxrandom, random1, auxrandom1 ; random <= QTDECHAO ;random++)
		{
			auxrandom = random*50;
			for(random1 = -QTDECHAO ;random1 <= QTDECHAO; random1++)
			{
				auxrandom1 = random1*50;
				glPushMatrix();
				glTranslatef(auxrandom,0,auxrandom1);
				desenhaOBJ(terreno);
				glPopMatrix();
			}
		}		
		glPopMatrix();
}