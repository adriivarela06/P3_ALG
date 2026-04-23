#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void fusionaMS(vector<int>& v, int posIni, int centro, int posFin, vector<int>& vaux) {
   int i = posIni;
   int j = centro;
   int k = 0;

   while (i < centro && j <= posFin) {
      if (v[i] <= v[j]) {
         vaux[k] = v[i];
         i++;
      } else {
         vaux[k] = v[j];
         j++;
      }
      k++;
   }

   while (i < centro){
      vaux[k] = v[i];
      i++; k++;
   }
   while (j <= posFin){
      vaux[k] = v[j];
      j++; k++;
   }

   for (int m = 0; m < k; m++)
      v[posIni + m] = vaux[m];
}

void mergeSortRecursivo(vector<int>& v, int posIni, int posFin, vector<int>& vaux) {
   if (posIni >= posFin) return;

   int centro = posIni + (posFin - posIni) / 2;

   mergeSortRecursivo(v, posIni, centro, vaux);
   mergeSortRecursivo(v, centro + 1, posFin, vaux);
   fusionaMS(v, posIni, centro + 1, posFin, vaux);
}

void ordenarVector(vector<int>& v) {
   if (v.empty()) return;
   
   vector<int> vaux(v.size()); 
   
   mergeSortRecursivo(v, 0, v.size() - 1, vaux);
}

bool esFactible(int requerimiento, int capacidad){
   return requerimiento <= capacidad;
}

int maximizarAsignaciones(vector<int> r, vector<int> c){
   unsigned output = 0,
       i = 0,
       j = 0;
   
   ordenarVector(r);
   ordenarVector(c);
    
   while(i < r.size() && j < c.size()) {
      if (esFactible(r[i], c[j])) {
         output++;
         i++; 
         j++; 
      }else
         j++; 
   }
    
   return output;

}

int main(){
   int n;
    
   cout << "=== ASIGNACION DE TAREAS Y SERVIDORES ===" << endl;
   cout << "Introduce el numero de tareas/servidores: ";
   cin >> n;
    
   if (n <= 0) {
      cout << "El numero debe ser mayor que 0." << endl;
      return 1;
   }

   vector<int> r(n);
   vector<int> c(n);

   cout << endl << "Introduce las " << n << " capacidades requeridas por las TAREAS (separadas por espacio):" << endl;
   for (int i = 0; i < n; i++) {
      cin >> r[i];
   }

   cout << endl << "Introduce las " << n << " capacidades de los SERVIDORES (separadas por espacio):" << endl;
   for (int i = 0; i < n; i++) {
      cin >> c[i];
   }

   int max_asignadas = maximizarAsignaciones(r, c);
    
   cout << endl <<  "--------------------------------------------------" << endl;
   cout << "-> El numero maximo de asignaciones logradas es: " << max_asignadas << endl;
   cout << "--------------------------------------------------" << endl;

    return 0;
}