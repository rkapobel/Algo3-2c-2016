//Recibir los parametros como esta en el enunciado
//Generar todas las tuplas posibles
// A los pares los identifico por el numero de fila y columna que representan en una matriz donde las filas son los arqueologos seguidos por los canibales
#include <iostream>
#include <fstream>
#include <utility>
#include "MaestroPokemon.hpp"
#include <chrono>
#define ya chrono::high_resolution_clock::now
using namespace std;


int algoritmoResolucion(int cant_arqueologos, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> * posiciones_gym,  pair<int,int> * posiciones_pp);

int main(int argc, char* argv[])
{
	int cant_gimnasios, cant_pokeParadas, cap_mochila;
	cin >> cant_gimnasios >> cant_pokeParadas >> cap_mochila;


	int posiciones_gym[cant_gimnasios];
	int posiciones_pp[cant_pokeParadas];

	int i = 0;
	for (i = 0; i < cant_gimnasios * 3; i++){
		pair <pair<int,int>, int> gymPuebloPaleta;
		if (i % 3 == 0){
			cin >> gymPuebloPaleta.first.first;
		}else{if (i % 3 == 2){
			cin >> gymPuebloPaleta.first.second;
		}else{
			cin >> gymPuebloPaleta.second;
		}
	}
		cin >> posiciones_gym[i];
	}
	for (i = 0; i < cant_pokeParadas * 2; i++)	{
		pair <int, int> posicion;
		if (i % 2 == 0)	{
			cin >> posicion.first;
		}else{
			cin >> posicion.second;
		}
		posiciones_pp[i] = posicion;
	}

	int f = algoritmoResolucion(cant_gimnasios, cant_pokeParadas, cap_mochila, posiciones_gym, posiciones_pp);
	cout <<f<<"\n";
	
	return 0;
}

int algoritmoResolucion(int cant_gimnasios, int cant_pokeParadas, int cap_mochila,  pair <pair <int,int>, int> * posiciones_gym,  pair<int,int> * posiciones_pp)
{

	//AGREGAR PODA DE SIN SOLUCION (LO MATAMOS ANTES DE QUE NAZCA)
	bool exitoBack = true;
	
	int minimo = -1; 
	MaestroPokemon ash = MaestroPokemon(cant_gimnasios, cant_pokeParadas, cap_mochila, posiciones_gym, posiciones_pp); //Aca se registran en el Pokedex
	while(exitoBack){
		if (ash.gane())
		{
			if (ash.distancia < minimo || minimo == -1)
			{
				minimo = ash.distancia;
			}
			
		}

		MaestroPokemon::Eleccion eleccion = ash.eleccionPosible();
			//Si hay un par posible y si la rama que estoy evaluando
			//me sigue dando una mejor solucion a la ya encontrada
		if (eleccion.posible==1 && (minimo == -1 || ash.distancia<minimo))
		{
			ash.elegir(eleccion);
		}else{
				//vuelve al paso anterior
			exitoBack = ash.deshacerEleccion();
		}
	}

	return minimo;
}