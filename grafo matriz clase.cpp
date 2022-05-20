#include <iostream>

using namespace std;

//ESTRUCTURA
struct nodo{//Solo crea los nodos
	char letra;
	struct nodo * sig; //Almacena las direccion de los nodos
	struct arista * a; //Direcciones de las relaciones entre nodos
};

struct arista{
	int valor; //valor de la arista
	struct nodo * destino;//Direccion del nodo destino
	struct arista * siguiente;//Direccion de siguiente arista
};

//TDA
typedef struct nodo * N;
typedef struct arista * A;

N grafo;//Definicion del puntero principal del grafo.

void insertarNodo()//void insertarNodo(N &grafo)
{
	char dato;
	N aux = NULL;
	N nuevo = new struct nodo;
	
	cout<<endl<<"Ingresa letra: ";
	cin>>dato;
	
	/* CREAR NODO */
	nuevo->letra = dato;
	nuevo->sig = NULL;
	nuevo->a = NULL;
	
	/* AGREGAMOS EL NODO AL GRAFO */
	if(grafo == NULL)
		grafo = nuevo;
	else
	{
		aux = grafo;
		while(aux->sig != NULL)
		{
			aux = aux->sig;
		}
		aux->sig = nuevo;	
	}
	
}

void mostrarGrafo()//void mostrarGrafo(N grafo)
{
	N aux = grafo;
	A arista;
	
	cout<<endl<<endl<<"* * * G R A F O * * *"<<endl;
	while(aux != NULL)
	{
		/*Mostrar nodo*/
		cout<<"\t"<<aux->letra<<" ";
		
		/*Mostrar aristas*/
		if(aux->a != NULL)
		{
			arista = aux->a;//Indicar donde inician las aristas
			while(arista != NULL)
			{
				cout<<arista->destino->letra;//numero del nodo de la arista
				arista = arista->siguiente;//siguiente arista
			}

		}
		aux = aux->sig;//Siguiente nodo
		cout<<"\t"<<endl;	
	}	
}

void agregarArista()//void agregarArista(N &grafo)
{
	char inicio, fin;
	A arista = new struct arista;//Puntero ancla de la lista de aristas
	N aux, aux2;
	//Verificando que el grafo esta vacio
	if(grafo == NULL)
	{
		cout<<endl<<"Grafo vacio..."<<endl;
		return;
	}
	
	//Si el grafo no esta vacio
	arista->siguiente = NULL;
	
	cout<<"Ingresa el nodo de inicio: ";
	cin>>inicio;
	cout<<"Ingresa el nodo de fin: ";
	cin>>fin;
	cout<<"Ingresa valor: ";
	cin>>arista->valor; 
	
	aux = grafo;//Se apunta al primer nodo que se agrego al grafo
	aux2 = grafo;//Se buscara el nodo destino
	
	//BUSCAR NODO DESTINO-FIN
	while(aux2 != NULL)
	{
		if(aux2->letra == fin)
		{
			break;//Una vez encontrado, se detiene el ciclo
		}
		aux2 = aux2->sig;//Se recorren los nodos
	}
	
	while(aux != NULL)
	{
		if(aux->letra == inicio)//El primer nodo
		{
			A temporal;//puntero arista
			
			if(aux->a == NULL)//Se comprueba que no haya aristas
			{
				aux->a = arista;//Se genera la arista
				arista->destino = aux2;//Asigna el nodo destino
			}
			else
			{
				temporal = aux->a;//Almacena la direccion de la primer arista
				while(temporal->siguiente != NULL)//Busca la ultima arista
				{
					temporal = temporal->siguiente;//Recorre la lista de aristas
				}
				arista->destino = aux2;//Asignar el nodo fin a la arista
				temporal->siguiente = arista;
			}
			return;
		}
		aux = aux->sig;//Recorremos los nodos
	}
	
}

int pesoCamino(char _in, char _fi){
	
	char inicio=_in;
	char fin=_fi; 
	int suma;
	N aux=grafo ,aux1= grafo; //Auxiliares de tipo nodo
	
	
	//BUSCAR NODO INICIO
	while(aux != NULL) //recorre los nodos 
	{
		if(aux->letra == inicio) 
		{
			break;	//Una vez encontrado, se detiene el ciclo
		}
		aux = aux->sig;
	}
	
	//BUSCAR NODO FIN
	while(aux1 != NULL)
	{
		if(aux1->letra == fin)
		{
			break;	//Una vez encontrado, se detiene el ciclo
		}
		aux1 = aux1->sig; //Se recorren los nodos
	}
	
	A temporal=aux->a; //puntero arista iguala a auxiliar arista del nodo inicial
	
	while(temporal!=NULL){ //mientras puntero arista sea diferente a null se recorre
		
		A temporal2=aux1->a; // se crea otro puntero arista  que se iguala al nodo final 
		
		while(temporal2!=NULL){ //mientras puntero arista 2 sea diferente de nulo se recorre

			if(temporal->destino == temporal2->destino){  //se hace la conexiÃ³n entre nodos
				suma= suma + temporal->valor; //se suma el valor del nodo inicial con el nodo conexiÃ³n
				suma= suma + temporal2->valor; //se suma el valor del nodo conexion con el nodo final
				return suma; //regresa a main
			}
			temporal2=temporal2->siguiente;	//sino entra al if sigue recorriendo nodos 
		}
		temporal=temporal->siguiente;
	}
	
}

void eliminarNodo(){
	
	char nE; 
	bool encontrado; 
	N aux=grafo;
	if(grafo == NULL)
	{
		cout<<endl<<"Grafo vacio..."<<endl;
		return;
	}
	
	cout<<endl<<"Ingrese el nodo a eliminar: ";
	cin>>nE;
	
	//verificar que exista el nodo
	while(aux!=NULL){
			
		if(aux->letra==nE){
			cout<<"Se encontro el nodo..."<<endl; 
			encontrado=true; 
			break; //nodo encontrado
		}
		else if(aux->sig==NULL){
			cout<<"No se encontro el nodo a eliminar..."<<endl; 
			encontrado=false; 
			return ; 
		}
		
		aux=aux->sig; 
	}
	
	//ELIMINAR NODO 
	if(encontrado==true){
		while(aux!=NULL){
		
			if(aux->letra==nE){ //se encuentra el nodo para eliminarlo 
			//	aux->a->letra=NULL; 
				aux->letra=NULL; 
				aux->a=NULL; 
				cout<<"Nodo eliminado..."<<endl<<endl;  
			}
			aux=aux->sig; 
		}	
	}
}

void eliminarArista(){
	
	char n, aE; 
	N aux=grafo;
	
	if(grafo == NULL)
	{
		cout<<endl<<"Grafo vacio..."<<endl;
		return;
	}
	
	cout<<"Ingrese el nodo: ";
	cin>>n; 
	cout<<"Ingrese la arista a eliminar: ";
	cin>>aE; 
	
	while(aux!=NULL){
		
		if(aux->letra==n){
			
				if(aux->a->destino->letra==aE){ 
					aux->a=NULL; 
					return;
				}
				
			while(aux->a->siguiente!=NULL){ 
				
						if(aux->sig->letra==aE){
							
							aux->a->siguiente=NULL;
							return;
						}
				
				aux->a->siguiente=aux->a->siguiente;
			}
		}
		aux=aux->sig; 
	}
	
}

void mostrarMatriz(){
	
	N aux1=grafo;
	N aux2=grafo;
	N aux=grafo;
	int cont;
	int f, c; 
	char matriz[cont][cont]; 

	while(aux1 != NULL) //recorre los nodos para saber cuantos hay y hacer la matriz
	{
		cont++;
		aux1 = aux1->sig;
	}

	cont=cont+1; //+ 1 para añadir la sección de los nodos
	cout<<"Contador: "<<cont<<endl; //lo imprimimos nomas pa saber que esta bien
	
/*	
	while(aux!=NULL){
	//	aux=grafo;
	for(int f=0; f<cont; f++){ //filas 
		cout<<endl<<"fila:"<<f<<" ";  
		for(int c=1; c<cont; c++){ //columnas 
				
				cout<<"columna:"<<c<<" "; 
				if(aux!=NULL){
					matriz[f][c]=aux->letra; 
				
				}
			
			cout<<"matriz:"<<matriz[f][c]<<" ";	
			}
			aux=aux->sig;
		}
	}*/
	
	while(aux!=NULL){ 
		for(int f=1; f<cont; f++){ //filas 
			aux2=grafo;
			cout<<endl<<"fila:"<<f<<" "; 
			while(aux2!=NULL){
				for(int c=1; c<cont; c++){ //columnas 	
					cout<<"columna:"<<c<<" "; 
					if(aux2!=NULL){
						matriz[f][c]=aux2->letra;
					} 
				aux2=aux2->sig;
				cout<<"matriz:"<<matriz[f][c]<<" ";	
				}
			}
			aux=aux->sig;
		}
	}
	

/*	
	for(int f=0; f<cont; f++){
			cout<<endl; 
		for(int c=1; c<cont; c++){
			cout<<matriz[f][c]<<" "<<endl; 
		}
	}
	*/
	
	cout<<endl; 


	
	
}

int main(){
	
	grafo = NULL;
	int opc = 0;
	char i, f;
	do{
		cout<<"Menu"<<endl
		<<"1 Insertar nodo"<<endl
		<<"2 Crear arista"<<endl
		<<"3 Mostrar grafo y peso"<<endl
		<<"4 Peso de un camino entre dos nodos"<<endl
		<<"5 Eliminar nodo"<<endl
		<<"6 Eliminar arista"<<endl
		<<"7 Mostrar matriz"<<endl
		<<"0 Salir"<<endl
		<<"Ingresa una opcion: ";
		cin>>opc;
		
		switch(opc)
		{
			case 0:
				cout<<endl<<"Terminando el programa"; 
				break;
			case 1:
				insertarNodo();//insertNodo(grafo);
				system("cls");
				break;
			case 2:
				agregarArista();//agregarArista(grafo)
				system("pause");
				system("cls");
				break;
			case 3:
				mostrarGrafo();//mostrarGrafo(grafo);
				system("pause");
				system("cls");
				break;
			case 4:
				cout<<"Ingresa el nodo de inicio: ";
				cin>>i;
				cout<<"Ingresa el nodo de fin: ";
				cin>>f;
			
				cout<<endl<<"La suma del peso es: "<<pesoCamino(i,f)<<endl<<endl; 
				system("pause");
				system("cls");
				break;
			case 5:
				eliminarNodo();
				break;
			case 6:
				eliminarArista();
				break; 
			case 7:
				mostrarMatriz();
				break; 
			default:
				cout<<endl<<"La opcion no se encuentra en el menu.";
				break;
		}
		
	}while(opc != 0);
	
	return 0;
}
