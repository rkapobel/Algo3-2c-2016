//Recibir los parametros como esta en el enunciado
//Generar todas las tuplas posibles
// A los pares los identifico por el numero de fila y columna que representan en una matriz donde las filas son los arqueologos seguidos por los canibales
#include <iostream>
#include <fstream>
#include <utility>
#include "MaestroPokemon.hpp"
#include <chrono>
#define ya chrono::high_resolution_clock::now
#define cantMaxGym 101
#define cantMaxPP 100
using namespace std;


pair <int,std::list<int> * > * algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int> posiciones_pp[]);

int main(int argc, char* argv[])
{
	/*int cant_gimnasios, cant_pokeParadas, cap_mochila;
	cin >> cant_gimnasios >> cant_pokeParadas >> cap_mochila;


	pair <pair<int,int>, int> posiciones_gym[cant_gimnasios];
	pair <int, int>  posiciones_pp[cant_pokeParadas];

	int i = 0;
	for (i = 0; i < cant_gimnasios; i++){
		pair <pair<int,int>, int> gymPuebloPaleta;
		
		cin >> gymPuebloPaleta.first.first >> gymPuebloPaleta.first.second >> gymPuebloPaleta.second;
		posiciones_gym[i] = gymPuebloPaleta;
		
	}
	for (i = 0; i < cant_pokeParadas; i++)	{
		pair <int, int> posicion;
		
		cin >> posicion.first >> posicion.second;
		
		posiciones_pp[i] = posicion;
		
	}*/

	/*Caso sin solucion:*/
	int cant_gimnasios = 0; 
	int cant_pokeParadas = 0;
	int cap_mochila = 0;
	pair <pair<int,int>, int> posiciones_gym[cantMaxGym];
	pair <int, int>  posiciones_pp[cantMaxPP];
	
	for(int j = 1; j < 15; j++){
		cant_gimnasios = j;
		cant_pokeParadas = j*2;
		
		int i = 0;
			for (i = 0; i < cant_gimnasios; i++){
			pair <pair<int,int>, int> gymPuebloPaleta;
			gymPuebloPaleta.first.first = i;
			gymPuebloPaleta.first.second = i+1;
			if (i % 2 == 0){
				gymPuebloPaleta.second = 3;
			}else{
				gymPuebloPaleta.second = 6;
			}
			//cantidad_pociones_necesarias_total += i*3;
			posiciones_gym[i] = gymPuebloPaleta;
			
		}
		for (i = 0; i < cant_pokeParadas; i++)	{
			pair <int, int> posicion;
			posicion.first = i;
			posicion.second = i+2;
			posiciones_pp[i] = posicion;
		}
		/*ACA LA MOCHILA SOPORTA LA CAPACIDAD MAXIMA PARA AVANZAR POR TODOS, SE VAN A HACER DOS TESTEOS SIN SOLUCION YA QUE TENEMOS DOS PODAS
		cap_mochila = cantMaxGym*3	;
		cout << "j es:" << j << "\n"; 
		printf("%d %d %d \n", cant_gimnasios, cant_pokeParadas, cap_mochila);
		
		for(i = 0; i < cant_gimnasios; i++){
			printf("%d %d %d \n", posiciones_gym[i].first.first, posiciones_gym[i].first.second, posiciones_gym[i].second );
			}
			
		for(i = 0; i < cant_pokeParadas; i++){
			printf("%d %d\n", posiciones_pp[i].first, posiciones_pp[i].second);
			
			}
*/
		pair <int,std::list<int> * > * f;
			for (int h = 0; h < 1; ++h){
				
		auto start = ya();
		f = algoritmoResolucion(cant_gimnasios, cant_pokeParadas, cap_mochila, posiciones_gym, posiciones_pp);
	auto end = ya();
		if(h == 0){
			    cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << "\t";
				cout << "\n";
			}
		}
	/*
		if ( f == NULL || f->first == -1)	{
			cout << "-1" << "\n";
			//return -1;
		}else{
			cout << f->first <<" "<< f->second->size();
			for (std::list<int>::iterator it=f->second->begin(); it != f->second->end(); ++it){
				cout << " " << *it;
			}
		}
		cout << "\n";
		*/
		
		
		delete f;
	}
	return 0;
}

 pair <int,std::list<int> * > * algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> posiciones_gym[],  pair<int,int>  posiciones_pp[])
{
	pair <int,std::list<int>*> * final = new pair <int,std::list<int> * >;
	/*
	int cantidadTotalDePocionesConSuerte = 3 * cant_pokeParadas;
	int pocionesANecesitar = 0;
	for (int i = 0; i < cant_gimnasios; ++i){
		pocionesANecesitar = pocionesANecesitar + posiciones_gym[i].second;
		if (posiciones_gym[i].second > cap_mochila || posiciones_gym[i].second > cantidadTotalDePocionesConSuerte){
			//Sin solucion!
			final->first = -1;
			return final;
		}
	}
	if(pocionesANecesitar > cantidadTotalDePocionesConSuerte){
			//Sin solucion!
		final->first = -1;
		return final;
	}
	*/
	bool exitoBack = true;
	
	int minimo = -1; 
	MaestroPokemon ash = MaestroPokemon(cant_gimnasios, cant_pokeParadas, cap_mochila, posiciones_gym, posiciones_pp); //Aca se registran en el Pokedex
	std::list<int> * camino;
	while(exitoBack){
		//ash.printStatus();
		/*if (ash.gane())
		{
			if (ash.distancia < minimo || minimo == -1)
			{
			//	cout<<"fin de rama\n";
				minimo = ash.distancia;
				camino = ash.caminoRecorrido();

			}
			
		}*/

		MaestroPokemon::Eleccion eleccion = ash.eleccionPosible();
			//Si hay un par posible y si la rama que estoy evaluando
			//me sigue dando una mejor solucion a la ya encontrada

		if (eleccion.posible==1)
		{
			//printf("La eleccion tiene una distancia: %d \n",eleccion.distancia );

			//ash.printEleccion(eleccion);
			//cout << "Eligiendo \n" ;
			ash.elegir(eleccion);
		}else{
				//vuelve al paso anterior
			//cout << "Backtrack \n" ;
			exitoBack = ash.deshacerEleccion();
		}
	}

	final->first = minimo;
	final->second = camino;
	return final;
}
