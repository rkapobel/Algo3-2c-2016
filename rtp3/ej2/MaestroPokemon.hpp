#include <list>
#include <algorithm>
#include <iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "trie.cpp"

#define GIMNASIO 0
#define PP 1

using namespace std;

class MaestroPokemon {

private:
	//Guardo la eleccion que se tomo en cada paso
	
	int* destinos_visitados;



public:
	int distancia;
	int paso = 0;

	struct destino
	{
		int tipo;
		int cant_pociones;
		pair <int, int> posicion;
		destino(int tipo, int cant_pociones, pair <int, int> posicion): 
		tipo(tipo),
		cant_pociones(cant_pociones),
		posicion(posicion){};

	};
	struct Eleccion
	{
		const MaestroPokemon* MP;
		int distancia =0;
		int id = -1; // El id da ordinalidad a todas las elecciones posibles, dentro de la matriz #personas x #personas
		bool posible;

		int tipo =-1;
		int pocionesNecesarias = -1;
		pair <int, int> posicion;
		Eleccion(){};
		Eleccion(const MaestroPokemon* MP):
		MP(MP),
		id(-1){
			recalcular();
		};

		

		void recalcular(){
			
			posible = MP->cant_pokeParadas + MP->cant_gimnasios > id;
			if (posible)
			{
				int x, y, xM, yM;


				xM = MP->eleccionActual.posicion.first;
				yM = MP->eleccionActual.posicion.second;
				

				if (id >= MP->cant_gimnasios)
				{
					//Si es una pp
					tipo = PP;
					int id2 = id - MP->cant_gimnasios;				
					x = MP->posiciones_pp[id2].first;
					y = MP->posiciones_pp[id2].second;
					pocionesNecesarias = 0;
				}else{
					//Si es un gym
					tipo = GIMNASIO;
					x = MP->gyms[id].first.first;
					y = MP->gyms[id].first.second;
					pocionesNecesarias = MP->gyms[id].second;
				}

				//Actualizo posicion
				posicion.first = x;
				posicion.second = y;
				
				distancia=0;
				if (id!=-1)
				{
					distancia = pow(x - xM, 2) + pow(y - yM, 2);
					if(distancia<0){
						distancia = 0;
					}
				}

				
				//printf("- - -DR: %d\n",distancia );

			}else{
				pocionesNecesarias = -1;
				posicion.first= -888;
				posicion.second= -888;
				distancia = 0;

			}
		}
	};


	MaestroPokemon(int cant_gimnasios, int cant_pokeParadas, int cap_mochila, const pair <pair <int,int>, int> gyms[], const pair <int,int> posiciones_pp[], int idInicial);
	~MaestroPokemon();
	//Devuelve el identificador de la eleccion

	bool gane();
	bool eleccionGolosa();

	//Para ver el estado del sistema
	void printEleccion(Eleccion par) const;
	void printStatus()const;
	std::list<int> * caminoRecorrido(const pair <int,int> pp_aux[]);

	Eleccion eleccionActual;
private:
	int cant_pokeParadas;
	int capacidad_mochila;
	int cantidad_pociones;
	const pair <pair <int,int>, int>* gyms;
	const pair <int,int>* posiciones_pp;
	int cant_gimnasios;
	int cant_gimnasios_por_ganar;
	std::list<Eleccion> * decisiones;
	std::list<int> * opciones;
	bool eleccionValida(Eleccion eleccion) const;



};
