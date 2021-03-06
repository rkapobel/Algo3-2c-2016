
/*
 * Archivo para la clase de heuristicas de Algoritmos y Estructuras
 * de Datos 3. Segundo cuatrimestre 2016.
 *
 * Para compilar con gcc 4.8:
 * g++ -std=c++11 -o tsp tsp.cpp
 *
 * La funcion generarSolucion utiliza una heuristica constructiva
 * para encontrar un camino hamiltoniano.
 *
 * La funcion mejorarSolucion realiza una busqueda local sobre
 * un camino hamiltoniano.
 *
 * El define SEED define una semilla para generar numeros.
 * Si SEED es 0, el programa es random.
 *
 * El programa imprime en pantalla la solucion inicial obtenida a
 * partir de generarSolucion, y la solucion final luego de aplicar la
 * busqueda local.
 *
 */

#define SEED 39

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

bool nodosValidos(int i, int j, vector<vector<double>> &mat, vector<vector<bool>> &elegido);

double calcularCosto(vector<vector<double>> &mat, vector<int> &camino);

vector<int> generarSolucion(vector<vector<double>> &mat){
    int n = mat.size();
    vector<int> ans = vector<int>(n, 0);
    
    int ib = 0;
    int jb = 0;
    
    vector<vector<bool>> elegido;
    elegido = vector<vector<bool>>(n, vector<bool>(n, false));
    for (int x = 0; x < n; x++)
    {
        int aristaMasBarata = -1;
        
        for (int i = 0; i < n-1; i++)
        {
            for (int j = i+1; j < n; j++)
            {
                if ((aristaMasBarata == -1 || mat[i][j] < aristaMasBarata) && elegido[i][j] == false && nodosValidos(i,j,mat,elegido))
                {
                    aristaMasBarata = mat[i][j];
                    ib = i;
                    jb = j;
                }
            }
        }
        
        elegido[ib][jb] = true;
        elegido[jb][ib] = true;
    }
    
    int inicio = ib;
    int anterior = ib;
    int actual = jb;
    
    ans[0] = ib;
    ans[1] = jb;
    
    int index = 2;
    
    while (inicio != actual) {
        for (int i = 0; i < n; i++) {
            if (i != anterior && elegido[actual][i]) {
                ans[index] = i;
                anterior = actual;
                actual = i;
                index++;
                break;
            }
        }
    }
    
    /*vector<int> ans;
    for(int i=0;i<n;i++) ans.push_back(i);
    random_shuffle(ans.begin(),ans.end());*/
    
    // ****************
    
    return ans;
}

bool nodosValidos(int i, int j, vector<vector<double>> &mat, vector<vector<bool>> &elegido) {
    int n = mat.size();
    
    int a = i;
    int b = j;
    
    int cantA = 0;
    for (int j = 0; j < n; j++)
    {
        if (elegido[a][j])
        {
            cantA++;
        }
    }
    
    if (cantA > 1)
    {
        return false;
    }
    
    int cantB = 0;
    for (int j = 0; j < n; j++)
    {
        if (elegido[b][j])
        {
            cantB++;
        }
    }
    
    if (cantB > 1)
    {
        return false;
    }
    
    int cantAristasRecorridas = 0;
    int iact = a;
    int iant = a;
    int jact = 0;
    
    while (cantAristasRecorridas < n-2 && jact < n)
    {
        if (elegido[iact][jact] && iant != jact)
        {
            iant = iact;
            iact = jact;
            jact = 0;
            cantAristasRecorridas++;
        }else {
            jact++;
        }
    }
    
    if (cantAristasRecorridas > 0 && cantAristasRecorridas < n-2 && iact == b)
    {
        return false;
    }
    
    return true;
}

vector<int> mejorarSolucion(vector<vector<double>> &mat, vector<int> camino){
    vector<int> ans = camino;
    double costoAns = calcularCosto(mat,ans);
    int n = mat.size();
    
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            
            swap(camino[j], camino[(j+1)%n]);
            
            swap(camino[i], camino[i+1]);
            
            double costoActual = calcularCosto(mat, camino);
            
            cout << "Cambiando 3 aristas: " << calcularCosto(mat,camino) << endl;
            for(int i=0;i<n;i++) cout << camino[i] << ' ';
            cout << endl;
            
            if (costoActual < costoAns) {
                costoAns = costoActual;
                ans = camino;
            }
            
            swap(camino[i], camino[i+1]);
            
            swap(camino[j], camino[(j+1)%n]);
        }
    }
    
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            swap(camino[i], camino[j]);
            
            double costoActual = calcularCosto(mat, camino);
            
            cout << "Cambiando 2? aristas: " << calcularCosto(mat,camino) << endl;
            for(int i=0;i<n;i++) cout << camino[i] << ' ';
            cout << endl;
            
            if (costoActual < costoAns) {
                costoAns = costoActual;
                ans = camino;
            }
            
            swap(camino[i], camino[j]);
        }
    }

    /*for(int i=1;i<n;i++){
        swap(camino[0],camino[i]);

        double costoActual = calcularCosto(mat,camino);
        
        cout << "Cambiando 2? aristas (profe version): " << calcularCosto(mat,camino) << endl;
        for(int i=0;i<n;i++) cout << camino[i] << ' ';
        cout << endl;

        if(costoActual < costoAns){
            costoAns = costoActual;
            ans = camino;
        }
        swap(camino[0],camino[i]);
    }*/
   
   	cout << "solucion: " << calcularCosto(mat,ans) << endl;
    for(int i=0;i<n;i++) cout << ans[i] << ' ';
    cout << endl;
    
    // ****************
    
    return ans;
}

double calcularCosto(vector<vector<double>> &mat, vector<int> &camino){
    double ans = 0;
    int n = mat.size();
    for(int i=0;i<n;i++) ans += mat[camino[i]][camino[(i+1)%n]];
    return ans;
}

int main(){
    
    int n;
    
    vector<vector<double>>mat;
    
    if(SEED == 0){
        n = 10;
        int aux = time(NULL);
        cout << "Utilizando semilla random: " << aux << endl;
        srand(aux);
        mat = vector<vector<double>>(n, vector<double>(n, 0));
        
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                mat[i][j] = mat[j][i] = (rand() * 1.) / RAND_MAX * 100;
            }
        }
        
    }else{
#define RND num = num * SEED + SEED / 2
        
        unsigned num = SEED + SEED/2;
        RND;
        RND;
        
        n = num % 100;
        mat = vector<vector<double>>(n, vector<double>(n, 0));
        
        RND;
        
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                RND;
                mat[i][j] = mat[j][i] = num % 200;
            }
        }
    }
    
    //Para que las distancias sean transitivas, Floyd Warshall
    //for(int k=0;k<n;k++)
    //  for(int i=0;i<n;i++){
    //    for(int j=0;j<n;j++){
    //      if(mat[i][k] + mat[j][k] < mat[i][j]) mat[i][j] = mat[i][k] + mat[k][j];
    //    }
    //}
    
    vector<int> camino = generarSolucion(mat);
    
    // cout << "Matriz " << endl;
    // for(int i=0;i<n;i++){
    //   for(int j=0;j<n;j++) cout << mat[i][j] << ' ';
    //   cout << endl;
    // }
    
    cout << "Solucion constructiva: " << calcularCosto(mat,camino) << endl;
    for(int i=0;i<n;i++) cout << camino[i] << ' ';
    cout << endl;
    
    camino = mejorarSolucion(mat,camino);
    
    cout << "Solucion mejorada: " << calcularCosto(mat,camino) << endl;
    for(int i=0;i<n;i++) cout << camino[i] << ' ';
    cout << endl;
}
