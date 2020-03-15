#include<iostream >
#include<windows.h>
#include<conio.h>
//#include<stdlib.h>
#include<time.h>
//#include<sstream> 
#include <stdio.h>

int vCuadro[9];//Creamos un vector global

char caracter(int i);//Funcion para mostrar en pantalla H y/o C
void mostrarC();//Funcion para mostrar el cuadro de juego
int ganador();//funcion para determinar si hay un ganador
int ia_serd(int player);//Funcion para el analisis del movimiento
void jmaquina();//Funcion para el juego de la maquina
void jusuari();//Funcion para el juego del usuario
void dados(bool &bTurno); //Funcion para lanzamiento de dados y determinar quien inicia
void inicializar();//Funcion para inicializar el vector con las posiciones del juego

using namespace std;


int main()
{
	bool bTurno=true,bContinue,bGanador=false;
	int nTurno=0,nRepeat=0;
	char cEnter;
	
	cout<<"\t ------------------------------------"<<endl<<endl;
	cout<<"\t |   BIENVENIDO AL JUEGO DEL GATO   |"<<endl<<endl;
	cout<<"\t ------------------------------------"<<endl<<endl;

	while(nRepeat==0){
		nTurno=0;
		bGanador=false;
		inicializar();
		cout<<" Para lanzar dados oprima Enter\n Para cancelar y salir oprima cualquier tecla"<<endl<<endl;;
		cEnter=getch(); //Damos a la varible el valor de la tecla oprimida
		
		//Analizamos si la tecla presionada fue Enter
		if(cEnter!=13)bContinue =false;
		if(cEnter==13)bContinue =true;
			
		if(bContinue) 
		{
			dados(bTurno);//Relizar lanzamiento de dados
			do //realizar siclo hasta que haya un ganador o se genere empate
			{
				if (bTurno)
				{
					system("CLS");
					cout<<"\t TU TURNO \n  Escoge posicion a jugar \n"<<endl;
					mostrarC();
					if(nTurno<9)
					{
						jusuari();//Juega el usuario
					}
					
					nTurno++;//contar los turnos
					bTurno=false;//Cambio de valor para realizar el cambio de jugador
				}		
				else
				{
					
					system("CLS");
					cout<<"\tTURNO MAQUINA \n\n "<<endl;
					mostrarC();
					if(nTurno<9)
					{
						jmaquina();//Juega la maquina
					}
					Sleep(1000);//Esperar un segundo
					nTurno++;
					bTurno=true;//Cambio de valor para realizar el cambio de jugador
					
				}
				
				
				switch(ganador())//Validar si hay ganador o empate
				{
	        case 0:
	        	if(nTurno==10)
						{
	            cout<<"\t EMPATE !! \n"<<endl; 
	          }
	          break;
	        case 1:
	            system("CLS");
	            cout<<"\t PERDISTE !! \n"<<endl;
	            mostrarC();
	            bGanador=true;
	            break;
	        case -1:
	        		system("CLS");
	            cout<<"\t GANASTE !! \n"<<endl;
	            mostrarC();
	            bGanador=true;
	            break;
	    	}
			}while(!bGanador && nTurno<=9);
		}
		Sleep(2000);
		system("CLS");
		cout<<" Desea jugar? \n 0=SI   1=NO"<<endl;//Preguntar si desea jugar y validar
		cin>>nRepeat;
		if(nRepeat==0)
		{
			system("CLS");
		}
		else
		{
			system("CLS");
			cout<<"\n \n \t ADIOS !!"<<endl;
			return 0;
		}
	}
}


//funcion para mostrar en pantalla H y/o C
char caracter(int i) {
    switch(i) 
		{//segun lo que haya en el espacio indocado del vector
        case -1:
            return 'H';
        case 0:
            return ' ';
        case 1:
            return 'C';
    }
}

//Funcion para mostrar el cuadro de juego
void mostrarC() {
	//se pasa el espacio del vector como parametro a l funcion caracter
	
	for(int i=0; i<9; i++){
		
		
		if(i==3 || i==6){
			cout<<endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			cout<<"\t---------"<<endl;
		}
		
		if(vCuadro[i]==1){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);//Juega maquina color azul
			if(i==0 || i==3 || i==6){
				cout<<"\t";
			}
			cout<<caracter(vCuadro[i]);
		}else if(vCuadro[i]==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);//Posicion vacia verde
			if(i==0 || i==3 || i==6){
				cout<<"\t";
			}
			cout<<i+1;
		}else{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);//Juega humano color rojo
			if(i==0 || i==3 || i==6){
				cout<<"\t";
			}
			cout<<caracter(vCuadro[i]);
		}
		
		if(i==0 || i==1 || i==3 || i==4 || i==6 || i==7){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			cout<<" | ";
		}

	}
	cout<<endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}

//Funcion para determinar si hay algún ganador
int ganador() {
    //matriz con las posiciones/espacios del vector posibles de ganar 
    int nPos[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
  	
    for(int i = 0; i < 8; ++i)
		{//comparar la matriz con las posibles posiciones a ganar con el vector 
      if(vCuadro[nPos[i][0]] != 0 && vCuadro[nPos[i][0]] == vCuadro[nPos[i][1]] && vCuadro[nPos[i][0]] == vCuadro[nPos[i][2]])
      {
        return vCuadro[nPos[i][2]];
      }
    }
    return 0;
}

//Funcion para hacer analisis de donde jugar
int ia_serd(int nJuego) {
    int nGanador = ganador();
    if(nGanador != 0) return nGanador*nJuego;

    int nMover = -1;
    int nPunto = -2;
    int i;
    for(i = 0; i < 9; ++i) {//Probar para todas las posiciones 
        if(vCuadro[i] == 0) {
            vCuadro[i] = nJuego;
            int nRaya = -ia_serd(nJuego*-1);
            if(nRaya > nPunto) {//seleccionar la mejor opcion 
                nPunto = nRaya;
                nMover = i;
            }
            vCuadro[i] = 0;//Volver a vaciar las posiciones del vector
        }
    }
    if(nMover == -1) return 0;
    return nPunto;//devolver mejor opcion
}

//Funcion para que juegue la maquina
void jmaquina() {
    int nMover = -1;
    int nJugar = -2;
    //int i;
    for(int i = 0; i < 9; ++i) {
        if(vCuadro[i] == 0) { //verificar las posiciones del vector que estan vacias
            vCuadro[i] = 1;
            int nPunto = -ia_serd(-1);//Se llama a la funcion ia_serd 
            vCuadro[i] = 0;
            if(nPunto > nJugar) {
                nJugar = nPunto;
                nMover = i;//determinar posicion en la que se va jugar
            }
        }
    }
    
    vCuadro[nMover] = 1; //Se juega en la posicion deseada
}

//funcion para que juegue el usuario
void jusuari() {
    int nUs,nConter;
	cin>>nUs;
	if (nUs<1 || nUs>9)//validar que ingrese posicion valida 
	{
		cout<<" Ingrese una posicion valida"<<endl;
		jusuari();
	}
	nConter=1;
	for (int i=0;i<9;i++){
		
			if (nConter==nUs)
			{
				if (vCuadro[i] != 0)//Validar que posiciones estan ocupadas
				{
					cout<<" No puede jugar en esta posicion, escoja una casilla desocupada"<<endl;
					jusuari();
				}
				else
				{
					vCuadro[i] = -1;//marcar jugada del usuario
				}
			}
			nConter++;
	}
}
void dados(bool &bTurno)
{
	int nDama=0,nDaus=0;
	
	while (nDama == nDaus) //Lanzamiento de dados se realizara hasta que los valores de ambos dados sean diferentes
	{
		srand(time(NULL));
		//Lanzamiento del dado de la maquina
		nDama = 1 + rand() % 6;
		cout<<"Maquina: "<<nDama<<endl<<endl;
		Sleep(1000); //Esperar un segundo
		//(Al realizar cambio de segundo se reducen las posivilades de que los dados del usuario y la maquina tengan valores iguales)
		nDaus = 1 + rand() % 6;
		cout<<"Tu: "<<nDaus<<endl<<endl;
		//Se decide si se volveran a lanzar los dados o que jugador inicia
		if(nDama == nDaus){
			cout<<"Se Volveran a lanzar los dados"<<endl;
		}
		else
		{
			if(nDama > nDaus)
			{
				cout<<"COMIENZA MAQUINA"<<endl;
				bTurno=false;
			}
			else
			{
				cout<<"COMIENZA USUARIO"<<endl;
				bTurno=true;
			}			
		}
		Sleep(2000);//Esperar dos segundos para dar tiempo de leer los mensajes en pantalla
		system("CLS");//limpiar pantalla
	}
}

//Funcion para inicializar el vector
void inicializar()
{
	int nPos=0;
	for (int i=0;i<9;i++)
	{		
		vCuadro[i]=nPos;		
	}
}

