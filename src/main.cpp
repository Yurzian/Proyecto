#include <iostream>
#include <cstring>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
#include <ctime> 


#ifdef __cplusplus__
#include <cstdlib>
#define CLEAR "cls"
#else
#include <stdlib.h>
#define CLEAR "clear"
#endif

using namespace std;

struct record
{
    string nombre;
    string tablero;
    string dificultad;
    double tiempo;

};

void configuracion(bool &seguir, int &filas, int &columnas, int &dificultad, int &zoom, int &njugadores, int &dif, int &jugador);

void tableroacero(int filas, int columnas, int **tableroa, char **tablerob);

void rellenartablero(int filas, int columnas, int **tablero2, int parejas, char **tablero);

void mostrartablero(int fila, int columna, int njugadores, char **tablero, int **tablero2, int zoom, int puntuacionjugador, int puntuacionbot);

void jugador1(int filas, int columnas, int njugadores, char **tablero, int **tablero2, char **tablerobot, int zoom, int &puntuacionjugador, int puntuacionbot, int parejas);

void esperarsegundos();

void compararpuntos(int puntuacionjugador, int puntuacionbot, int &puntuaciontotal, bool &terminar, int parejas, int &win);

void botfacil(int filas, int columnas, char **tablero, int **tablero2, char **tablerobot, int zoom, int puntuacionjugador, int puntuacionbot, int njugadores, int &pos1, int &pos2, int &pos3, int &pos4);

void compararbot(int filas, int columnas, int parejas, char **tablero, int **tablero2, char **tablerobot, bool &botacierta, int &pos1, int &pos2, int &pos3, int &pos4, bool cambiar);

void aleatoriobot(int filas, int columnas, char **tablero, int **tablero2, char **tablerobot, int &aleatibot, int &aleatjbot);

void aciertobot(char **tablero, int **tablero2, char **tablerobot, int &pos1, int &pos2, int &pos3, int &pos4, int &puntuacionbot);

void ganador(int win, int puntuacionjugador, int puntuacionbot, int parejas, double time);

void repetir(bool &fin, bool &terminar);

void ficherotiempos(int filas, int columnas, int dificultad, int njugadores, int win, double time, struct record &a);

void escribirfichero(struct record a, int filas, int columnas, string records);

void leerfichero(string records);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    srand(time(NULL));

    struct record a;

    //VARIABLES PARA LA CONFIGURACION
    int filas, columnas, dificultad, dif, zoom, jugador, njugadores; 
    bool seguir = false;

    //VARIABLES PARA CUANDO EMPIEZA EL JUEGO
    bool terminar=false, botacierta=false, cambiar, fin=false; //PARA LOS BUCLES Y POR SI ACIERTA EL BOT

    int win, puntuacionjugador = 0, puntuacionbot = 0, puntuaciontotal = 0, end, diferencia; //QUIEN GANA Y PUNTUACIONES

    int pos1, pos2, pos3, pos4; //POSICIONES PARA EL BOT

    unsigned t0, t1; //PARA EL TIEMPO
    double time; //PARA EL TIEMPO
    
    //CONFIGURACIÓN PARTIDA
    configuracion(seguir, filas, columnas, dificultad, zoom, njugadores, dif, jugador);
    
    //TABLEROS
    char **tablero, **tablerobot;
    int **tablero2;

    //TABLEROS CON PUNTEROS
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
    
    while (fin == false)
    {
        t0=clock(); //EMPIEZA EL CONTADOR

        rellenartablero(filas, columnas, tablero2, parejas, tablero); //RELLENA EL TABLERO CON LAS CARTAS

        tableroacero(filas, columnas, tablero2, tablerobot); //TABLERO2 Y TABLERO BOT A 0 PARA COMENZAR

        puntuacionjugador=0;
        puntuacionbot=0;

        while (terminar == false) //MIENTRAS EL JUEGO NO ACABE
        {
            switch (jugador)
            {
                case 1: //JUGADOR
                    jugador1(filas, columnas, njugadores, tablero, tablero2, tablerobot, zoom, puntuacionjugador, puntuacionbot, parejas);

                    compararpuntos(puntuacionjugador, puntuacionbot, puntuaciontotal, terminar, parejas, win);

                    if (njugadores == 2) //SI JUEGAS CONTRA EL BOT
                    {
                        jugador = 2; //CAMBIA EL TURNO AL BOT
                    }

                break;
                
                case 2: //BOT
                    
                    //SI EL NIVEL ES MEDIO
                    if (dificultad == 0)
                    {
                        dif = 1 + rand() % (2); //HACE LA DIFICULTAD FACIL O DIFICIL AL AZAR
                    }
                    //SI ES NIVEL ADAPTATIVO
                    else if (dificultad == 4)
                    {
                        if (puntuacionjugador > puntuacionbot) //SI GANA EL JUGADOR
                        {
                            dif = 2;//DIFICULTAD EN DIFICIL
                        }
                        else if (puntuacionbot > puntuacionjugador) //SI GANA EL BOT
                        {
                            dif = 1; //DIFICULTAD EN FACIL
                        }
                        else if (puntuacionjugador == puntuacionbot) //SI LAS PUNTUACIONES IGUALES
                        {
                            dif = 1 + rand() % (2); //DIFICULTAD FACIL O DIFICIL AL AZAR
                        }
                    }

                    switch (dif) //MIRA SI ES FACIL O DIFICIL
                    {
                        case 1: botfacil(filas, columnas, tablero, tablero2, tablerobot, zoom, puntuacionjugador, puntuacionbot, njugadores, pos1, pos2, pos3, pos4);
                                aciertobot(tablero, tablero2, tablerobot, pos1, pos2, pos3, pos4, puntuacionbot);

                                esperarsegundos(); system(CLEAR);
                        break;

                        case 2: 
                                cambiar=true; 
                                botacierta=false;

                                //BUSCA EN SU TABLERO PARA VER SI SABE ALGUNA PAREJA
                                compararbot(filas, columnas, parejas, tablero, tablero2, tablerobot, botacierta, pos1, pos2, pos3, pos4, cambiar);
                                
                                if (botacierta == true) //SI LAS SABE Y LAS ACIERTA
                                {   
                                    //MUESTRA EL TABLERO CON LAS CASILLAS ACERTADAS Y PONE QUE HA ACERTADO
                                    mostrartablero(filas, columnas, njugadores, tablero, tablero2, zoom, puntuacionjugador, puntuacionbot);
                                    aciertobot(tablero, tablero2, tablerobot, pos1, pos2, pos3, pos4, puntuacionbot);
                                    esperarsegundos(); system(CLEAR);
                                }
                                else 
                                {
                                    //PRIMERA CASILLA ALEATORIA
                                    aleatoriobot(filas, columnas, tablero, tablero2, tablerobot, pos1, pos2);
                                    
                                    //MUESTRA LA PRIMERA CASILLA DEL BOT
                                    mostrartablero(filas, columnas, njugadores, tablero, tablero2, zoom, puntuacionjugador, puntuacionbot);      
                                    cout<<"Turno del Bot" << endl;  esperarsegundos();  system(CLEAR);
            
                                    cambiar=false;
                                    //COMPARA LA PRIMERA CASILLA CON EL RESTO DE CASILLAS PARA VER SI LA TIENE
                                    compararbot(filas, columnas, parejas, tablero, tablero2, tablerobot, botacierta, pos1, pos2, pos3, pos4, cambiar);

                                    if (botacierta == true) //SI LA TIENE
                                    {
                                        //LA MUESTRA Y PONE QUE LA HA ACERTADO
                                        mostrartablero(filas, columnas, njugadores, tablero, tablero2, zoom, puntuacionjugador, puntuacionbot);
                                        aciertobot(tablero, tablero2, tablerobot, pos1, pos2, pos3, pos4, puntuacionbot);
                                        esperarsegundos(); system(CLEAR);
                                    }
                                    else //SI NO LA TIENE
                                    {
                                        //SEGUNDA CASILLA ALEATORIA
                                        aleatoriobot(filas, columnas, tablero, tablero2, tablerobot, pos3, pos4);

                                        //LA MUESTRA E INDICA SI HA ACERTADO O NO
                                        mostrartablero(filas, columnas, njugadores, tablero, tablero2, zoom, puntuacionjugador, puntuacionbot);
                                        aciertobot(tablero, tablero2, tablerobot, pos1, pos2, pos3, pos4, puntuacionbot);
                                        esperarsegundos(); system(CLEAR);
                                    }
                                }
                        break;
                    }

                //COMPARA PUNTOS PARA VER SI HA FINALIZADO
                compararpuntos(puntuacionjugador, puntuacionbot, puntuaciontotal, terminar, parejas, win);

                jugador = 1;

                break;

            }
        }
        t1 = clock(); //PARA ACABAR EL CONTADOR
        time = (double(t1-t0)/CLOCKS_PER_SEC);

        //DICE EL GANADOR
        ganador(win, puntuacionjugador, puntuacionbot, parejas, time);

        //MUESTRA LOS TIEMPOS
        ficherotiempos(filas, columnas, dificultad, njugadores, win, time, a);

        //PARA VER SI VOLVER A JUGAR
        repetir(fin, terminar);


    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void configuracion(bool &seguir, int &filas, int &columnas, int &dificultad, int &zoom, int &njugadores, int &dif, int &jugador)
{
    int temporal = 0;
    filas = 3;
    columnas = 3;
    while ((filas * columnas) % 2 != 0) //WHILE PARA QUE SOLO SALGA SI LA TABLA ES PAR
    {

        if (temporal > 0) //SI ES MAS DE UNO ES PORQUE HA FALLADO, POR LO QUE PONE ERROR
        {
            system(CLEAR);
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
    while ((zoom > 2) || (zoom < 0)) //WHILE PARA QUE SALGA SOLO SI ES UNA OPCION
    {
        system(CLEAR);

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
    while (njugadores > 2 || njugadores < 1) //WHILE PARA QUE SALGA SOLO SI ES UNA OPCION
    {
        system(CLEAR);

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
        dificultad = 0;
        while (dificultad > 4 || dificultad < 1) //WHILE PARA QUE SALGA SOLO SI ES UNA OPCION
        {
            system(CLEAR);

            if (temporal > 0)
            {
                cout << "ERROR. Elija una de las opciones" << endl;
            }

            cout << "Elige la dificultad del bot:" << endl;
            cout << "1.- Facil." << endl;
            cout << "2.- Medio." << endl;
            cout << "3.- Dificil." << endl;
            cout << "4.- Adaptativa." << endl;
            cin >> dificultad;
            
            temporal++;
        
        }

        temporal = 0;
        jugador = 0;
        while (jugador > 2 || jugador < 1) //WHILE PARA QUE SALGA SOLO SI ES UNA OPCION
        {

            system(CLEAR);

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
        else if (dificultad == 1) //SI ESTA EN FACIL
        {
            dif = 1; //DIF EN FACIL
        }
        else if (dificultad == 3) //SI ESTA EN DIFICIL
        {
            dif = 2; //DIF EN DIFICIL
        }
        else if (dificultad == 4) //SI ESTA EN ADAPTATIVA
        {
            dificultad = 1; //DIFICULTAD EN ADAPTATIVA
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


    system(CLEAR);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void tableroacero(int filas, int columnas, int **tableroa, char **tablerob)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            tableroa[i][j] = 0; //PONEMOS TODOS LOS VALORES DE TABLERO2 A 0
            tableroa[i][j] = 0; //PONEMOS TODOS LOS VALORES DE TABLEROBOT A 0
        }
    }

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            tablerob[i][j] = 0; //PONEMOS TODOS LOS VALORES DE TABLERO2 A 0
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

void jugador1(int filas, int columnas, int njugadores, char **tablero, int **tablero2, char **tablerobot, int zoom, int &puntuacionjugador, int puntuacionbot, int parejas)
{
    bool seguir = true, error = false, mostrada=false;

    int p1, p2, p3, p4;
    char pos1[2], pos2[2];

    while (seguir == true)
    {

        if (error == true)
        {
            if (mostrada == false)
            {
            tablero2[p1][p2] = 0;
            }
        }

        mostrada=false;

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
            mostrada=true;
        }

        tablero2[p1][p2] = 1; //SE METE EN LA MATRIZ 2 PARA MOSTRARLO

        system(CLEAR);

        mostrartablero(filas, columnas, njugadores, tablero, tablero2, zoom, puntuacionjugador, puntuacionbot);

        if (mostrada == false)
        {
        tablero2[p1][p2] = 0; //SE VUELVE A QUITAR DE LA MATRIZ 2 PARA COMPROBAR SI LA SEGUNDA POSICION ES CORRECTA
        }

        cout << "Escribe la segunda posicion: ";
        cin >> pos2;
        pos2[0] = toupper(pos2[0]); //SE PONEN EN MAYUSCULA
        pos2[1] = toupper(pos2[1]);

        p3 = (int)pos2[0] - 65; //SE LES DA EL VALOR PARA USARLAS EN LA MATRIZ
        p4 = (int)pos2[1] - 65;

        system(CLEAR);

        if (p1 > filas-1 || p1 < 0 || p2 > columnas-1 || p2 < 0 || p3 > filas-1 || p3 < 0 || p4 > columnas-1 || p4 < 0 ) //SI ALGUNA NO EXISTE
        {
            cout << "ERROR. Elige posiciones que existan" << endl;
            cout << endl
                 << endl;
            error = true;
            seguir = false;
        }
        else
        if ((p1 == p3) && (p2 == p4)) //SI ALGUNA ESTA REPETIDA
        {
            cout << "EYEYEYEYEYEYEY. NO SE VALEN TRAMPAS." << endl;
            cout << "No introduzcas la misma casilla dos veces maquina." << endl;
            cout << endl
                 << endl;
            error = true;
        }
        else
        {
            if ((tablero2[p1][p2] == 1) || (tablero2[p3][p4] == 1)) //SI ALGUNA YA SE MUESTRA
            {
                cout << "EYEYEYEYEYEYEY. NO SE VALEN TRAMPAS." << endl;
                cout << "No introduzcas una casilla ya levantada maquina." << endl;
                cout << endl
                     << endl;
                error = true;
            }
            else //SI NO HAY ERROR
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

    system(CLEAR);
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

    system(CLEAR);
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

    system(CLEAR);
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
                if (tablerobot[i][j] == letra) //SI ES LA MISMA LETRA
                {
                    repeticiones++;

                    if (repeticiones == 1) //SE REPITE UNA VEZ
                    {
                        p1 = i;
                        p2 = j;
                    }
                    if (repeticiones == 2) //SE REPITE DOS VECES
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

void ganador(int win, int puntuacionjugador, int puntuacionbot, int parejas, double time)
{
    if (puntuacionbot == puntuacionjugador)
    {
        win = 0;
    }


    switch (win)
    {
    case 0:
        cout << "EMPATE con una duracion de " << time << endl;
        break;

    case 1:
        cout << "GANA EL JUGADOR CON " << puntuacionjugador << " puntos de " << parejas << " en " << time << endl;
        break;

    case 2:
        cout << "GANA LA MAQUINA CON " << puntuacionbot << " puntos de " << " en " << time << endl;
        break;
    }

    esperarsegundos();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void repetir (bool &fin, bool &terminar)
{
    int temporal=0;
    int numero=-1;

    while(numero < 0 || numero > 1) //WHILE PARA QUE SEA UNA OPCION VALIDA
    {
        system(CLEAR);

        if (temporal > 0)
        {
            cout << "ERROR, elige una de las opciones." << endl;
        }

        cout << "Quieres seguir jugando? (0=SI / 1=NO): ";
        cin >> numero;

        temporal++;
    }

    switch (numero)
    {
        case 0: //SEGUIR JUGANDO
            fin = false; 
            terminar = false;
            system(CLEAR);
        break;

        case 1: //SALIR
            fin = true;
        break;
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ficherotiempos(int filas, int columnas, int dif, int njugadores, int win, double time, struct record &a)
{
    int ver;

    if (win == 1)
    {
    cout << "Introduce el nombre con el que guardar tu tiempo: ";
    cin >> a.nombre;
    }
    else if (win == 0)
    {
        cout << "Empate guardado en la tabla de tiempos" << endl;
        a.nombre="Empate";
    }
    else if (win == 2)
    {
        cout << "Victoria del BOT guardada en la tabla de tiempos" << endl;
        a.nombre="BOT";
    }


    if (njugadores == 1)
    {
        a.dificultad="Solo";
    }
    else if (njugadores == 2)
    {
        switch (dif)
        {
            case 1:
                a.dificultad="Facil";
            break;
            
            case 2:
                a.dificultad="Medio";
            break;

            case 3:
                a.dificultad="Dificil";
            break;

            case 4:
                a.dificultad="Adaptativo";
            break;
        }
    }
    a.tiempo=time;

    escribirfichero(a, filas, columnas, "records");
    
    cout << endl << "Quieres ver el historial de tiempos? (1=Si): ";
    cin >> ver;

    if (ver == 1)
    {
        while (ver != 0)
        {
            system(CLEAR);
            leerfichero("records");
            cout << endl << "Introduce 0 para salir: "; 
            cin >> ver;
        }
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void escribirfichero(struct record a, int filas, int columnas, string records)
{
    ofstream f( records );

    if ( f.is_open() )
    {
        f << a.nombre << " " << filas << "x" << columnas << " " << a.dificultad << " " << a.tiempo << endl; 
    }
    else
        cout << "Error de apertura del archivo." << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void leerfichero(string records)
{
    string s;
    ifstream f( records );

    if ( f.is_open() )
    {
        getline( f, s );

        while( !f.eof() ) 
        {
            stringstream buffer;
            buffer.str(s); 

            string nombre;
            string tablero;
            string dificultad;
            double tiempo;

            //ordeñar el stringstream
            buffer >> nombre;
            buffer >> tablero;
            buffer >> dificultad;
            buffer >> tiempo;
            
            cout <<  nombre << " " << tablero << " " << dificultad << " " << tiempo << endl;

            getline( f, s );
        }
    }
    else
        cout << "Error de apertura del archivo." << endl;
}

