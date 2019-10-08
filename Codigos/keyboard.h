// Callback de Teclado (Apertando)
void teclaPressionada(unsigned char key, int x, int y)
{
    switch(key)
    {
        // Teclas para andar com a camera
        case 'S':
        case 's':

            if(tela == 1)
               keyboard[83] = 1;    
            break;

        case 'W':
        case 'w':

            if(tela == 1)
                keyboard[87] = 1;         
            break;

        case 'A':
        case 'a':

            if(tela == 1)
                keyboard[65] = 1;                
            break;

        case 'D':
        case 'd':

            if(tela == 1)
                keyboard[68] = 1;  
            break;

        // As três cameras
        // Camera perspectiva
        case '1':

            if(tela == 1)
                modoCamera = 1;
            break;

        // Camera primeira pessoa
        case '2':

            if(tela == 1)
                modoCamera = 2;
            break;

        // Camera terceira pessoa
        case '3':

            if(tela == 1)
                modoCamera = 3;
            break;

        //ESC
        case 27 : 

            // Menu
            if(tela == 0)
            {
                exit(0);
            }
            else if(tela == 3)
            {
                tela = 0;
            }

            else
                exit(0);

        break;
    }   
}

// Callback de Teclado (Soltando)
void teclaSegurada(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'S':
        case 's':

            if(tela == 1)
               keyboard[83] = 0;
            break;

        case 'W':
        case 'w':

            if(tela == 1)
                keyboard[87] = 0;
            break;

        case 'A':
        case 'a':

            if(tela == 1)
                keyboard[65] = 0;
            break;

        case 'D':
        case 'd':

            if(tela == 1)
                keyboard[68] = 0;
            break;
    }
}

void movimentacao()
{
    if(tela == 1)
    {    
        // Tecla w/W        
        if(keyboard[87] == 1) 
        {
            cursor.x--;
        }

        // Tecla s/S
        if(keyboard[83] == 1)  
        {
            cursor.x++;
        }

        // Tecla a/A
        if(keyboard[65] == 1)  
        {
            cursor.z++;
        }

        // Tecla d/D
        if(keyboard[68] == 1)  
        {
            cursor.z--;
        }
    }
}