#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

void configuracion(bool &seguir, int &filas, int &columnas, int &dificultad, int &zoom, int &njugadores, int &dif, int &jugador);

void tableroacero(int filas, int columnas, int **tableroa, char **tablerob);

void rellenartablero(int filas, int columnas, int **tablero2, int parejas, char **tablero);

void mostrartablero(int fila, int columna, int njugadores, char **tablero, int **tablero2, int zoom, int puntuacionjugador, int puntuacionbot);

void jugador1(int filas, int columnas, int njugadores, char **tablero, int **tablero2, char **tablerobot, int zoom, int &puntuacionjugador, int puntuacionbot);

void esperarsegundos();

void compararpuntos(int puntuacionjugador, int puntuacionbot, int &puntuaciontotal, bool &terminar, int parejas, int &win);

void botfacil(int filas, int columnas, char **tablero, int **tablero2, char **tablerobot, int zoom, int puntuacionjugador, int puntuacionbot, int njugadores, int &pos1, int &pos2, int &pos3, int &pos4);

void compararbot(int filas, int columnas, int parejas, char **tablero, int **tablero2, char **tablerobot, bool &botacierta, int &pos1, int &pos2, int &pos3, int &pos4, bool cambiar);

void aleatoriobot(int filas, int columnas, char **tablero, int **tablero2, char **tablerobot, int &aleatibot, int &aleatjbot);

void aciertobot(char **tablero, int **tablero2, char **tablerobot, int &pos1, int &pos2, int &pos3, int &pos4, int &puntuacionbot);

void ganador(int win, int puntuacionjugador, int puntuacionbot, int parejas);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    srand(time(NULL));

    int filas, columnas, dificultad, dif, zoom, jugador, njugadores;
    bool seguir = false;

    configuracion(seguir, filas, columnas, dificultad, zoom, njugadores, dif, jugador);

    char **tablero, **tablerobot;

    int **tablero2;

    tablero = new char *[filas];
    tablero2 = new int *[filas];
    tablerobot = new char *[filas];

    for (int i = 0; i < filas; i++)
    {
        tablero[i] = new char[columnas];
        tablero2[i] = new int[columnas];
        tablerobot[i] = new char[columnas];
    }

    int parejas = (filas * columnas) / 2; //NUMERO DE PAREJAS QUE VA A TENER EL TABLERO

    rellenartablero(filas, columnas, tablero2, parejas, tablero);

    tableroacero(filas, columnas, tablero2, tablerobot);

    bool terminar = false, botacierta=false, cambiar;

    int win, puntuacionjugador = 0, puntuacionbot = 0, puntuaciontotal = 0;

    int pos1, pos2, pos3, pos4;

    while (terminar == false)
    {
        switch (jugador)
        {
            case 1:
                jugador1(filas, columnas, njugadores, tablero, tablero2, tablerobot, zoom, puntuacionjugador, puntuacionbot);

                compararpuntos(puntuacionjugador, puntuacionbot, puntuaciontotal, terminar, parejas, win);

                if (njugadores == 2)
                {
                    jugador = 2;
                }

            break;
            
            case 2:

                if (dificultad == 0) //SI EL NIVEL ES MEDIO
                {
                    dif = 1 + rand() % (2); //HACE LA DIFICULTAD FACIL O DIFICIL AL AZAR
                }

                switch (dif)
                {
                    case 1: botfacil(filas, columnas, tablero, tablero2, tablerobot, zoom, puntuacionjugador, puntuacionbot, njugadores, pos1, pos2, pos3, pos4);
                            aciertobot(tablero, tablero2, tablerobot, pos1, pos2, pos3
                            , pos4, puntuacionbot);

                            esperarsegundos();
                            system("cls");
                    break;

                    case 2: 
                            cambiar=true;
                            botacierta=false;
                            compararbot(filas, columnas, parejas, tablero, tablero2, tablerobot, botacierta, pos1, pos2, pos3, pos4, cambiar);
                            
                            if (botacierta == true)
                            {
                                mostrartablero(filas, columnas, njugadores, tablero, tablero2, zoom, puntuacionjugador, puntuacionbot);
                                aciertobot(tablero, tablero2, tablerobot, pos1, pos2, pos3, pos4, puntuacionbot);
                                esperarsegundos();
                                system("cls");
                            }
                            else 
                            {
                                aleatoriobot(filas, columnas, tablero, tablero2, tablerobot, pos1, pos2);

                                mostrartablero(filas, columnas, njugadores, tablero, tablero2, zoom, puntuacionjugador, puntuacionbot);
                                cout<<"Turno del Bot" << endl;                              
                                esperarsegundos();
                                system("cls");
        
                                cambiar=false;
                                compararbot(filas, columnas, parejas, tablero, tablero2, tablerobot, botacierta, pos1, pos2, pos3, pos4, cambiar);

                                if (botacierta == true)
                                {
                                    mostrartablero(filas, columnas, njugadores, tablero, tablero2, zoom, puntuacionjugador, puntuacionbot);
                                    aciertobot(tablero, tablero2, tablerobot, pos1, pos2, pos3, pos4, puntuacionbot);
                                    esperarsegundos();
                                    system("cls");
                                }
                                else 
                                {
                                    aleatoriobot(filas, columnas, tablero, tablero2, tablerobot, pos3, pos4);

                                    mostrartablero(filas, columnas, njugadores, tablero, tablero2, zoom, puntuacionjugador, puntuacionbot);
                                    aciertobot(tablero, tablero2, tablerobot, pos1, pos2, pos3, pos4, puntuacionbot);
                                    esperarsegundos();
                                    system("cls");
                                }
                            }
                    break;
                }

            compararpuntos(puntuacionjugador, puntuacionbot, puntuaciontotal, terminar, parejas, win);

            jugador = 1;

            break;

        }
    }

    ganador(win, puntuacionjugador, puntuacionbot, parejas);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void configuracion(bool &seguir, int &filas, int &columnas, int &dificultad, int &zoom, int &njugadores, int &dif, int &jugador)
{
    int temporal = 0;
    filas = 3;
    columnas = 3;
    while ((filas * columnas) % 2 != 0)
    {

        if (temporal > 0)
        {
            system("cls");
            cout << "ERROR. La tabla debe ser par (la multiplicacion de las filas y columnas debe ser un número par)." << endl;
        }
        cout << "Elige el numero de filas: ";
        cin >> filas;

        cout << "Elige el numero de columnas: ";
        cin >> columnas;
        
        temporal++;
    }

    temporal = 0;
    zoom = -1;
    while ((zoom > 2) || (zoom < 0))
    {
        system("cls");

        if (temporal > 0)
        {
            cout << "ERROR. ESCOJA UNA DE LAS OPCIONES ENRTE PARENTESIS" << endl;
        }

        cout << "Elige el zoom (0,1,2): ";
        cin >> zoom;

        temporal++;
    }

    temporal = 0;
    njugadores = 0;
    while (njugadores > 2 || njugadores < 1)
    {
        system("cls");

        if (temporal > 0)
        {
            cout << "ERROR. Elija una de las siguientes opciones" << endl;
        }

        cout << "Elige quien va a jugar:" << endl;
        cout << "1.- Yo solo." << endl;
        cout << "2.- Yo contra la maquina." << endl;
        cin >> njugadores;

        temporal++;
    }

    if (njugadores == 2)
    {
        temporal = 0;
        njugadores = 0;
        while (dificultad > 3 || dificultad < 1)
        {
            system("cls");

            if (temporal > 0)
            {
                cout << "ERROR. Elija una de las opciones" << endl;
            }

            cout << "Elige la dificultad del bot:" << endl;
            cout << "1.- Facil." << endl;
            cout << "2.- Medio." << endl;
            cout << "3.- Dificil." << endl;
            cin >> dificultad;
            
            temporal++;
        
        }

        temporal = 0;
        jugador = 0;
        while (jugador > 2 || jugador < 1)
        {
            system("cls");

            if (temporal > 0)
            {
                cout << "ERROR. Elija una de las opciones." << endl;
            }

            cout << "Elige quien empieza:" << endl;
            cout << "1.- Jugador" << endl;
            cout << "2.- Maquina" << endl;
            cin >> jugador;

            temporal++;
        }

        if (dificultad == 2) //SI ESCRIBE QUE EL NIVEL ES MEDIO
        {
            dificultad = 0; //LO PASO A LO QUE EL ORDENADOR INTERPRETA QUE ES EL NIVEL MEDIO
        }
        else if (dificultad == 1)
        {
            dif = 1;
        }
        else if (dificultad == 3)
        {
            dif = 2;
        }
        
        //EL NIVEL FACIL LO INTERPRETA COMO 1 POR LO QUE NO SE CAMBIA
    }
    else 
    {
        jugador = 1;
    }

    if ((filas * columnas) % 2 == 0)
    {
        seguir = true;
    }


    system("cls");

}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void tableroacero(int filas, int columnas, int **tableroa, char **tablerob)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            tableroa[i][j] = 0; //PONEMOS TODOS LOS VALORES DE TABLERO2 A 0
            tablerob[i][j] = 0; //PONEMOS TODOS LOS VALORES DE TABLEROBOT A 0
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void rellenartablero(int filas, int columnas, int **tablero2, int parejas, char **tablero)
{
    int aleati, aleatj;
    int obj = 97;
    bool seguir;

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            tablero2[i][j] = 0; //PONEMOS TODOS LOS VALORES DE TABLERO2 A 0
        }
    }

    for (int i = 0; i < parejas; i++)
    {
        for (int j = 0; j < 2; j++) // BUCLE DE DOS PARA PONER LA MISMA LETRA DOS VECES EN CASILLAS DISTINTAS
        {
            seguir = false;
            while (seguir == false)
            {
                aleati = rand() % (filas); //HACEMOS LOS NUMEROS ALEATORIOS
                aleatj = rand() % (columnas);

                if (tablero2[aleati][aleatj] == 0) //SI LA CASILLA ESTÁ EN CERO, ES DECIR, SI LA CASILLA NO ESTÁ
                {
                    seguir = true; // SALIR DEL BUCLE
                }
            }

            tablero[aleati][aleatj] = obj; // LO METEMOS EN EL TABLERO
            tablero2[aleati][aleatj] = 1;  // TABLERO2 LO PONEMOS EN 1 PARA QUE SEPA QUE YA SE HA USADO ESA CASILLA
        }

        obj++; // AUMENTAMOS LA LETRA
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void mostrartablero(int fila, int columna, int njugadores, char **tablero, int **tablero2, int zoom, int puntuacionjugador, int puntuacionbot)
{

    int letrai = 65, letraj = 65, x;

    cout << "   ";

    for (int i = 0; i < columna; i++) //PRIMERA FILA CON LAS LETRAS DE LAS POSICIONES
    {
        cout << (char)letrai;
        letrai++;
        for (int j = 0; j < zoom + 1; j++)
        {
            cout << " ";
        }
        if (zoom == 3)
        {
            cout << " ";
        }
    }

    cout << endl;

    for (int i = 0; i < fila; i++) //RESTO DE LA TABLA
    {
        x = 0;

        for (int l = 0; l < zoom + 1; l++) //PRIMERA COLUMNA CON LAS LETRAS DE LAS POSICIONES
        {

            if (x == 0)
            {
                cout << " " << (char)letraj;
                letraj++;
                x++;
            }

            else
            {
                cout << "  ";
            }

            cout << " ";

            for (int j = 0; j < columna; j++)
            {
                for (int k = 0; k < zoom + 1; k++)
                {
                    if (tablero2[i][j] == 1) //SI LA POSICION DEL TABLERO2 ES 1 SE MUESTRA
                    {
                        cout << tablero[i][j];
                    }
                    else //SINO ES 0 Y SE MUESTRA EL CUADRADO
                    {
                        cout << (char)254;
                    }
                }

                if (zoom == 3)
                {
                    cout << " ";
                }
                if (j != columna - 1)
                {
                    cout << " ";
                }
            }
            cout << endl;
        }
        if (zoom > 0)
        {
            cout << endl;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void jugador1(int filas, int columnas, int njugadores, char **tablero, int **tablero2, char **tablerobot, int zoom, int &puntuacionjugador, int puntuacionbot)
{
    bool seguir = true, error = false, acertada=false;

    int p1, p2, p3, p4;
    char pos1[2], pos2[2];

    while (seguir == true)
    {

        if (error == true)
        {
            if (acertada == false)
            {
            tablero2[p1][p2] = 0;
            }
        }

        acertada=false;

        error = false;

        mostrartablero(filas, columnas, njugadores, tablero, tablero2, zoom, puntuacionjugador, puntuacionbot);

            cout << "Tu puntuacion: " << puntuacionjugador << " pt.";

        if (njugadores == 2)
        {
        cout << "    Puntuacion bot: " << puntuacionbot << " pt.";
        }

        cout << endl
             << endl;

        cout << "Escribe la primera posicion: ";
        cin >> pos1;

        pos1[0] = toupper(pos1[0]); //SE PONEN EN MAYUSCULA
        pos1[1] = toupper(pos1[1]);

        p1 = (int)pos1[0] - 65; //SE LES DA EL VALOR PARA USARLAS EN LA MATRIZ
        p2 = (int)pos1[1] - 65;

        if (tablero2[p1][p2] == 1)
        {
            acertada=true;
        }

        tablero2[p1][p2] = 1; //SE METE EN LA MATRIZ 2 PARA MOSTRARLO

        system("cls");

        mostrartablero(filas, columnas, njugadores, tablero, tablero2, zoom, puntuacionjugador, puntuacionbot);

        if (acertada == false)
        {
        tablero2[p1][p2] = 0; //SE VUELVE A QUITAR DE LA MATRIZ 2 PARA COMPROBAR SI LA SEGUNDA POSICION ES CORRECTA
        }

        cout << "Escribe la segunda posicion: ";
        cin >> pos2;
        pos2[0] = toupper(pos2[0]); //SE PONEN EN MAYUSCULA
        pos2[1] = toupper(pos2[1]);

        p3 = (int)pos2[0] - 65; //SE LES DA EL VALOR PARA USARLAS EN LA MATRIZ
        p4 = (int)pos2[1] - 65;

        system("cls");

        if ((p1 == p3) && (p2 == p4)) //ERROR
        {
            cout << "EYEYEYEYEYEYEY. NO SE VALEN TRAMPAS." << endl;
            cout << "No introduzcas la misma casilla dos veces maquina." << endl;
            cout << endl
                 << endl;
            error = true;
        }
        else
        {
            if ((tablero2[p1][p2] == 1) || (tablero2[p3][p4] == 1)) //ERROR
            {
                cout << "EYEYEYEYEYEYEY. NO SE VALEN TRAMPAS." << endl;
                cout << "No introduzcas una casilla ya levantada maquina." << endl;
                cout << endl
                     << endl;
                error = true;
            }
            else //NO HAY ERROR
            {
                seguir = false;
                tablero2[p1][p2] = 1; //LAS MOSTRAMOS EN EL TABLERO2
                tablero2[p3][p4] = 1;

                tablerobot[p1][p2] = tablero[p1][p2]; //METEMOS LAS CASILLAS EN TABLEROBOT
                tablerobot[p3][p4] = tablero[p3][p4];

                mostrartablero(filas, columnas, njugadores, tablero, tablero2, zoom, puntuacionjugador, puntuacionbot); //MOSTRAMOS TABLERO

                if (tablero[p1][p2] != tablero[p3][p4]) //FALLO
                {
                    cout << endl
                         << "TAS EQUIVOCAO CHAVAAAAAAL" << endl;

                    tablero2[p1][p2] = 0;
                    tablero2[p3][p4] = 0;
                }
                else //ACIERTO
                {
                    cout << endl
                         << "EYEYEYEY QUE LO TIENES BIEN Y TO" << endl;
                    tablerobot[p1][p2] = 1;
                    tablerobot[p3][p4] = 1;
                    tablero2[p1][p2] = 1;
                    tablero2[p3][p4] = 1;
                    puntuacionjugador++;
                }
            }
        }
    }
    esperarsegundos();

    system("cls");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void esperarsegundos()
{
    double secs = 4.5;

    for (int i = (time(NULL) + secs); time(NULL) != i; time(NULL))
        ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void compararpuntos(int puntuacionjugador, int puntuacionbot, int &puntuaciontotal, bool &terminar, int parejas, int &win)
{

    puntuaciontotal = puntuacionjugador + puntuacionbot;

    if (puntuacionjugador > (parejas / 2))
    {
        terminar = true;
        win = 1; ////JUGADOR COMO GANADOR
    }

    if (puntuacionbot > (parejas / 2))
    {
        terminar = true;
        win = 2; ////BOT COMO GANADOR
    }

    if (puntuaciontotal == parejas)
    {
        if (puntuacionjugador == puntuacionbot)
        {
            terminar = true;
            win = 3; //// EMPATE
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void botfacil(int filas, int columnas, char **tablero, int **tablero2, char **tablerobot, int zoom, int puntuacionjugador, int puntuacionbot, int njugadores, int &pos1, int &pos2, int &pos3, int &pos4)
{
    bool seguir = false;

    while (seguir == false)
    {
        pos1 = rand() % (filas); //SEGUNDA CASILLA ALEATORIA
        pos2 = rand() % (columnas);

        if (tablero2[pos1][pos2] == 0) //SI LA CASILLA NO ESTA ACERTADA
        {
            seguir = true; //SALIMOS DEL BUCLE
        }
    }

    tablerobot[pos1][pos2] = tablero[pos1][pos2];
    tablero2[pos1][pos2] = 1;

    system("cls");
    mostrartablero(filas, columnas, njugadores, tablero, tablero2, zoom, puntuacionjugador, puntuacionbot); //MUESTRA TABLERO
    esperarsegundos();

    ////////////////////

    seguir = false;

    while (seguir == false)
    {
        pos3 = rand() % (filas); //SEGUNDA CASILLA ALEATORIA
        pos4 = rand() % (columnas);

        if (pos3 != pos1 && pos4 != pos2 && tablero2[pos3][pos4] == 0) //SI LAS DOS CASILLAS NO SON LA MISMA Y NO ESTA ACERTADA
        {
            seguir = true; //SALIMOS DEL BUCLE
        }
    }

    tablerobot[pos3][pos4] = tablero[pos3][pos4];
    tablero2[pos3][pos4] = 1;

    system("cls");
    mostrartablero(filas, columnas, njugadores, tablero, tablero2, zoom, puntuacionjugador, puntuacionbot); //MUESTRA TABLERO

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void compararbot(int filas, int columnas, int parejas, char **tablero, int **tablero2, char **tablerobot, bool &botacierta, int &pos1, int &pos2, int &pos3, int &pos4, bool cambiar)
{
    int letra = 97;
    int repeticiones=0;
    int p1=0, p2=0,p3=0,p4=0;

    while ((letra < 97 + parejas) && (repeticiones < 3)) //COMPARA TODOS LOS VALORES QUE TIENE EL BOT EN SU TABLERO
    {
        for (int i = 0; i < filas; i++)
        {
            for (int j = 0; j < columnas; j++)
            {
                if (tablerobot[i][j] == letra)
                {
                    repeticiones++;

                    if (repeticiones == 1)
                    {
                        p1 = i;
                        p2 = j;
                    }
                    if (repeticiones == 2)
                    {
                        p3 = i;
                        p4 = j;
                        botacierta = true;
                        repeticiones += 2;
                    }
                }
            }
        }

        letra++;

        if (botacierta == false)
        {
            repeticiones = 0;
        }
    }

    if (botacierta == true)
    {
        pos1 = p1;
        pos2 = p2;
        pos3 = p3;
        pos4 = p4;

        tablerobot[pos1][pos2] = tablero[pos1][2]; //LA PONE EN EL TABLEROBOT
        tablero2[pos1][pos2] = 1; //SE MUESTRA EN EL TABLERO2

        tablerobot[pos3][pos4] = tablero[pos3][4]; //LA PONE EN EL TABLEROBOT
        tablero2[pos3][pos4] = 1; //SE MUESTRA EN EL TABLERO2
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void aleatoriobot(int filas, int columnas, char **tablero, int **tablero2, char **tablerobot, int &aleatibot, int &aleatjbot)
{

    bool seguir = false;

    while (seguir == false) //HACE LA PRIMERA CASILLA ALEATORIA
    {
        aleatibot = rand() % (filas); //PRIMERA CASILLA ALEATORIA
        aleatjbot = rand() % (columnas);

        if ((tablerobot[aleatibot][aleatjbot] == 0) && (tablero2[aleatibot][aleatjbot] == 0)) //SI LA CASILLA NO ESTÁ ACERTADA O LEVANTADA
        {
            seguir = true; //SALE DEL BUCLE
        }
    }

    tablerobot[aleatibot][aleatjbot] = tablero[aleatibot][aleatjbot]; //LA PONE EN EL TABLEROBOT

    tablero2[aleatibot][aleatjbot] = 1; //SE MUESTRA EN EL TABLERO2

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void aciertobot(char **tablero, int **tablero2, char **tablerobot, int &pos1, int &pos2, int &pos3, int &pos4, int &puntuacionbot)
{
    if (tablero[pos1][pos2] == tablero[pos3][pos4]) //SI ACIERTA
    {
        cout << "EL BOTARDO HA ACERTADO" << endl;

        puntuacionbot++; //SUMAMOS PUNTUACIONES

        tablero2[pos1][pos2] = 1; //PONEMOS LOS DOS VALORES DE TABLERO2 PARA QUE SE VEAN
        tablero2[pos3][pos4] = 1;

        tablerobot[pos1][pos2] = 1; //PONEMOS LAS DOS CASILLAS DE TABLEROBOT A 1 PARA QUE NO VUELVA A USARLOS
        tablerobot[pos3][pos4] = 1;
    }

    else
    {
        cout << "EL BOTARDO HA FALLADO" << endl;

        tablero2[pos1][pos2] = 0; //QUITAMOS LOS DOS VALORES DE TABLERO2 PARA QUE NO SE VEAN
        tablero2[pos3][pos4] = 0;

        tablerobot[pos1][pos2] = tablero[pos1][pos2]; //METEMOS LOS DOS VALORES EN TABLEROBOT PARA QUE SE ACUERDE
        tablerobot[pos3][pos4] = tablero[pos3][pos4];
    }
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ganador(int win, int puntuacionjugador, int puntuacionbot, int parejas)
{
    if (puntuacionbot == puntuacionjugador)
    {
        win = 0;
    }


    switch (win)
    {
    case 0:
        cout << "EMPATE" << endl;
        break;

    case 1:
        cout << "GANA EL JUGADOR CON " << puntuacionjugador << " puntos de " << parejas << endl;
        break;

    case 2:
        cout << "GANA LA MAQUINA CON " << puntuacionbot << " puntos de " << parejas << endl;
        break;
    }

    esperarsegundos();

}
