#include <iostream>
using namespace std;
const char *nombre_archivo = "archivo.dat";
struct Palabra{
	
	char palabras[50];
	char traduccion[50];
	char funcionalidad[50];
};
void Crear();
void Leer();
void Actualizar();
void Borrar();
main(){
	Leer();
	Crear();
	Actualizar();
	Borrar();
	system("pause");
}
void Leer(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo,"rb");
	if (!archivo){
		archivo = fopen(nombre_archivo,"w+b");
	} 
	Palabra palabra;
	int id=0; 
	fread(&palabra,sizeof(Palabra),1,archivo);
	cout<<"******************************************************************************"<<endl;
		cout<<"ID"<< "   |" <<"Palabra"<<"                    |"<<"Traduccion"<<"                              |"<<"Funcionalidad"<<endl;
	cout<<"******************************************************************************"<<endl;
	do{
		cout<<id<<"    ||"<<palabra.palabras<<"             ||"<<palabra.traduccion<<"                 //"<<palabra.funcionalidad<<endl;
		fread(&palabra,sizeof(Palabra),1,archivo);
		id+=1;
	}while(feof(archivo)==0);
	fclose(archivo);
}
void Crear(){
	FILE* archivo = fopen(nombre_archivo,"a+b");
	char res;
	Palabra palabra;
	do{
		fflush(stdin);
		cout<<"Ingrese Palabra:";
        cin.getline(palabra.palabras,100);
		
		cout<<"Ingrese Traduccion:";
		cin.getline(palabra.traduccion,100);
		
		cout<<"Ingrese Funcionalidad:";
		cin.getline(palabra.funcionalidad,900);
		
		fwrite(&palabra,sizeof(Palabra),1,archivo);
		cout<<"Desea Ingresar otra palabra(s/n):";
		cin>>res;
	}while (res=='s' || res=='S');
	fclose(archivo);
	Leer();
}
void Actualizar(){
	
	FILE* archivo = fopen(nombre_archivo,"r+b");
	Palabra palabra;
	int id=0;
	cout<<"Ingrese el ID que desea Modificar:";
	cin>>id;
	fseek(archivo,id * sizeof(Palabra),SEEK_SET);
	
		cout<<"Ingrese Palabra:";
		cin>>palabra.palabras;
		cin.ignore();
		
		cout<<"Ingrese Traduccion:";
        cin>>palabra.traduccion;
		cin.ignore();
		
		cout<<"Ingrese Funcionalidad:";
		cin.getline(palabra.funcionalidad,900);
		
		fwrite(&palabra,sizeof(Palabra),1,archivo);
    fclose(archivo);
	Leer();
}
void Borrar(){
	const char *nombre_archivo_temp = "archivo_temp.dat";
	FILE* archivo_temp = fopen(nombre_archivo_temp,"w+b");
	FILE* archivo = fopen(nombre_archivo,"rb");
	Palabra palabra;
	int id=0,id_n=0;
	cout<<"Ingrese el ID que desea eliminar:";
	cin>>id;
	while(fread(&palabra,sizeof(Palabra),1,archivo)){
		if(id_n !=id){
			fwrite(&palabra,sizeof(Palabra),1,archivo_temp);
		}
		id_n++;
	}
	fclose(archivo);
	fclose(archivo_temp);
	
	archivo_temp = fopen(nombre_archivo_temp,"rb");
	archivo = fopen(nombre_archivo,"wb");
	while(fread(&palabra,sizeof(Palabra),1,archivo_temp)){
		fwrite(&palabra,sizeof(Palabra),1,archivo);
	}
	fclose(archivo);
	fclose(archivo_temp);
	Leer();
}