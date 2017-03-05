/* Alumno: Velasco Osorio Aquino
   Grupo: 602-A
   Materia: Recuperación de la Información
   Técnica Boolean
*/   
 

#include <iostream>
#include <fstream>
#include <utility>
#include <map>
#include<vector>
#include<stack>
#include<string>
#include<sstream>
#include<cmath>
 #include <bitset>

using namespace std;

//Prototipo para la funcion to_string de la blioteca c++11
template <typename T>
string to_string(T value)
{      
      ostringstream os ;
      os << value ;
      return os.str() ;
}

//Mapa que va a contener las palablas y los archivos en que aparacecen
map<string, vector<int> >tabla;
//Mapa que contentrá el valor en entero de los bits de cada fila
map<string,int> terminos;
//Vector que contendrá la entrada infija
vector <string> infija;
//vector que contendrá la salida posfija
vector < string > posfija; 


//leida de archivo linea por por line
void leerarchivos(ifstream &fe, int archivo){
    //número de linea a leer
    int n;
    char linea [50];
    fe>>n;
    //después de leer el numero hacer un salto de linea
    fe.getline(linea,50);
    string cadena(linea); 
    while(n--) {
      /*fe >> cadena;
      tabla[cadena].push_back(archivo);*/
      fe.getline(linea,50);
      string cadena(linea); 
      //se recupera la palabra según el número de archivo
      tabla[cadena].push_back(archivo);
    } 
    fe.close();
}
//función que imprime la primera tabla
void imprimetabla1(){
   map<string, vector<int> >::iterator p = tabla.begin();
   int termino=1; 
   
   cout<<"\t\t Tabla1"<<endl; 
   cout<<"Identificador"<<"\tTérmino\t\t\t\t"<<"Identificador del documento"<<endl; 

   while (p != tabla.end() )
   {
     //se imprime los indentificadores
     cout<<"T"<<termino++<<"\t\t";
     //se imprime los términos
     cout <<  p->first;
     cout<<"\t\t\t\t";
     //se imprime los identificadores del documento
     for(int i=0;i<p->second.size();i++){
        if(i<p->second.size()-1)
          cout<<p->second[i]<<",";
        else
          cout<<p->second[i];
     }
     cout<<endl; 
     p ++;
   }   
}
//función que verifica si hay un número en un vector
int contains(vector<int> identdocumentos, int nbuscar){
    for(int i=0;i<identdocumentos.size();i++){
             if(identdocumentos[i]==nbuscar)
                 return 1;
    }
     return 0;  
}
//función que imprime la tabla2
void imprimetabla2(){
   map<string, vector<int> >::iterator p = tabla.begin();
   int termino=1;
   string identificador; 
   
   cout<<"\t\t Tabla2"<<endl; 
   cout<<"Terminos\t"<<"d1  "<<"d2  "<<"d3  "<<"d4  "<<"d5  "<<"d6  "<<"d7  "<<"d8  "<<"d9  "<<"d10  "<<endl; 
   while (p != tabla.end() )
   {
     
     identificador = "T"+to_string(termino);
     termino++; 
     //se imprime los términos
     cout<<identificador<<"\t\t";
     for(int i=1;i<=10;i++)
     {
         //se imprime 1 si el termino aparece en el archivo i o 0 de lo contrario
         if(contains(p->second,i)==1){
            cout<<1<<"   ";
         }
         else
            cout<<0<<"   ";
     } 
     cout<<endl;
     p ++;
   }   
}
//se rellena el vector términos con los valores enteros  equivalente en bits por teŕmino
void rellenatermino(){
   map<string, vector<int> >::iterator p = tabla.begin();
   int termino=1;
   string identificador; 

   while (p != tabla.end() )
   {
     identificador = "T"+to_string(termino);
     termino++; 
     //se guarda el equivante en entero de un reglón de bits
     for(int i=1;i<=10;i++)
     {
         if(contains(p->second,i)==1){
            terminos[identificador]+=pow(2,10-i);
         }
     } 
     p ++;
   }   
}
//función que lee la expresión a analizar
string leeconsola(){
  string entrada;
  cout<<"\n\nIntroduzca la expresión a evaluar con este formato ( T1 | T3 ) & T7"<<endl; 
  getline(cin,entrada);
  return entrada;
} 
//función que separa la entrada por espacio y lo guarda en infija
void truncaentrada(string entrada)
{
    istringstream iss(entrada);
    do
    {
        string sub;
        iss >> sub;
        infija.push_back(sub);
    } while (iss);
    infija.pop_back();
}
//función que convierta de infija a posfija
void infijaposfija(){
     stack < string > pila; 
     for( int i = 0; i < infija.size() ; i++ ){
          if( infija[i] == "(" )
		pila.push(infija[i]);
          else 
          if( (infija[i] == "&") || (infija[i] == "|") ){
 		if( pila.empty() )
                      pila.push(infija[i]);
                else
                if( pila.top() == "(" )
                      pila.push(infija[i]);
                else{
		    posfija.push_back(pila.top());
                    pila.pop();
                    pila.push(infija[i]);
		}
          }
          else
          if(infija[i] == ")" ){
		while( pila.top() != "(" ){
                    posfija.push_back(pila.top());
                    pila.pop();     
                } 
                pila.pop();
          }
          else
          posfija.push_back(infija[i]);
     }  
     while(!pila.empty()){
          posfija.push_back(pila.top());
          pila.pop();
     } 
}
//función que convierte un entero a binario de tamaño 10 bits 
void bit(int num){
   bitset<10> bs;
   bs=num;
   cout << bs.to_string()<<endl;
}
//función que evalua la expresión posfija
void evaluarposfija(){
     stack<int>pila;
     int temp1;
     int temp2;
     for(int  i=0;i<posfija.size();i++){
	if(posfija[i] == "&"){
	   temp1=pila.top();
           pila.pop();
           temp2=pila.top();
           pila.pop();
           pila.push(temp1 & temp2);
        }
        else
        if(posfija[i] == "|"){
	   temp1=pila.top();
           pila.pop();
           temp2=pila.top();
           pila.pop();
           pila.push(temp1 | temp2);
        }
        else{
           pila.push(terminos[posfija[i]]);
        } 
     }	
     if(!pila.empty()){
        cout<<"\nResulado = ";
        bit(pila.top());
        cout<<endl;
        pila.pop();
     }
}

int main() {

   int archivo=1;
   //lectura de archivos
   ifstream fe("d1.txt");
   leerarchivos(fe,archivo++);
   ifstream fe2("d2.txt");
   leerarchivos(fe2,archivo++); 
   ifstream fe3("d3.txt");
   leerarchivos(fe3,archivo++);
   ifstream fe4("d4.txt");
   leerarchivos(fe4,archivo++);
   ifstream fe5("d5.txt");
   leerarchivos(fe5,archivo++);
   ifstream fe6("d6.txt");
   leerarchivos(fe6,archivo++);
   ifstream fe7("d7.txt");
   leerarchivos(fe7,archivo++);
   ifstream fe8("d8.txt");
   leerarchivos(fe8,archivo++); 
   ifstream fe9("d9.txt");
   leerarchivos(fe9,archivo++);
   ifstream fe10("d10.txt");
   leerarchivos(fe10,archivo++); 
   
   imprimetabla1();

   cout<<"\n\n"<<endl; 
    
   imprimetabla2();
   
   //obtener los valores en entero de los bits de una fila
   rellenatermino();   
   
   string entrada;
   entrada=leeconsola(); 
   
   truncaentrada(entrada);

   infijaposfija();

   evaluarposfija();
 
  return 0;
}
