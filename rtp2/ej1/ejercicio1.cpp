#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>

using std::queue;

int PMax;
int F;
int C;
bool finalizar;

struct Node {
	int i;
	int j;
	bool visited; // indica si el nivel fue recorrido
	bool marked; // marca para no encolar solo una vez
	bool iAmWall;
	int wallsBroken;
	int distMinToNode;
	Node():      i(0),
				 j(0),
       visited(false),
        marked(false),
       iAmWall(false),
       wallsBroken(-1),
       distMinToNode(-1) {}
};

Node*** Map; // Matriz mapa con Nodos
Node *nodeStart; // marcado por defecto
Node *nodeEnd;

queue<Node*> cola;

int max(int a, int b){
    return (a > b) ? a : b;
}

void proccessNode(int i, int j, Node *actual) {
    if (i > 0 && i < F-1 && j > 0 && j < C-1) {
        Node *node = Map[i][j];
        //printf("actual + si es pared %d actual %d,%d hijo %d,%d \n", actual->wallsBroken+(int)node->iAmWall, actual->i, actual->j, node->i, node->j);
        if (node->wallsBroken == -1 || actual->wallsBroken+(int)node->iAmWall < node->wallsBroken) { // realmente vale? consultar
            if (actual->distMinToNode == -1) {
                //inicializo porque lo voy a usar
                actual->distMinToNode = 0;
            }
            node->distMinToNode = actual->distMinToNode+1;
            node->wallsBroken = actual->wallsBroken+(int)node->iAmWall;
            
            if (node->i == nodeEnd->i && node->j == nodeEnd->j) {
                finalizar = true;
                return;
            }
            
            if(node->wallsBroken <= PMax) {
                cola.push(node);
            }
        }
    }
}

void mazeBfs () {
	cola.push(nodeStart);
	
	while(cola.size()){
		Node *actual = cola.front();
		cola.pop();
		
		int i = actual->i;
		int j = actual->j;

		proccessNode(i-1, j, actual);
		proccessNode(i+1, j, actual);
		proccessNode(i, j-1, actual);
		proccessNode(i, j+1, actual);
        
        if (finalizar) {
            break;
        }
	}
}

int main(){
/*   
	F = 5;
	C = 9;
	PMax = 1;
	
    finalizar = false;
    
	char map[] = {'#','#','#','#','#','#','#','#','#',
				  '#','o','.','#','#','#','#','x','#',
				  '#','.','.','#','.','#','#','#','#',
				  '#','.','.','.','.','#','#','#','#',
                  '#','#','#','#','#','#','#','#','#'};
*/
	std::cin >> F;
	std::cin >> C;
	std::cin >> PMax;

	char map[F*C];

	for(int i = 0; i < F*C; i++){
		std::cin >> map[i];
	}

    finalizar = false;
	Map = new Node**[F];
	
	for(int i = 0; i < F; i++){
		Map[i] = new Node*[C];
		for(int j = 0; j < C; j++){
            
            Node *n = new Node();
            n->i = i;
            n->j = j;
            Map[i][j] = n;
            
            char value = map[(i*C)+j];
            
            if(value == '#'){
                n->iAmWall = true;
            }else if(value == 'o'){
                nodeStart = n;
                n->iAmWall = false;
                n->wallsBroken = 0;
            }else if(value == 'x'){
                nodeEnd = n;
                n->iAmWall = false;
            }else {
                n->iAmWall = false;
            }
		}
	}
	
	mazeBfs();
	
	printf("%d \n", nodeEnd->distMinToNode);
  
	return 0;
}
