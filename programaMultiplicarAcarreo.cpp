#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define MAX 30
#define MAXBIN 8
int a,b;
int aBinarioCadena[MAXBIN],bBinarioCadena[MAXBIN];
int auxiliarA[MAXBIN],auxiliarB[MAXBIN],auxiliarR[MAXBIN];

int residuos[MAX],cocientes[MAX],contador=0;

void inicializar(){
	for(int i=0;i<MAX;i++){
		residuos[i] = 0;
		cocientes[i] = 0;
	}
	for(int i=0;i<MAXBIN;i++){
		aBinarioCadena[i] = 0;
		bBinarioCadena[i] = 0;
		auxiliarA[i] = 0;
		auxiliarB[i] =0;
		auxiliarR[i] = 0;
	}

}

void dividir(int dividendo,int divisor){
	cocientes[contador] = dividendo/divisor;
	residuos[contador] = dividendo%divisor;
	contador++;
}
void convertiraBinario(int numero,int base,int vector[]){
    contador=0;
    for(int i=0;i<MAX;i++){
		residuos[i] = 0;
		cocientes[i] = 0;
	}
	do{
		if(contador>0){	
			dividir(cocientes[contador-1],base);	
		}
		else{
			dividir(numero,base);
		}	
	}while(!(cocientes[contador-1]<base));
	
	for(int i=MAXBIN-1;i>=0;i--){
		vector[i] = residuos[MAXBIN-1-i];
	}
	vector[MAXBIN-contador-1] = cocientes[contador-1];
	for(int i=0;i<MAXBIN;i++){
		printf("%d",vector[i]);
	}

}
void asignarVectores(int vector1[],int vector2[]){
	for(int i=0;i<MAXBIN;i++){
		vector1[i] = vector2[i];
	}
}
void correrParaDerecha(int vector[]){
	//100101
	for(int i=MAXBIN-1;i>=1;i--){
		vector[i]=vector[i-1];	
	}
	vector[0] = 0;
}
void correrParaIzquierda(int vector[]){
	//0000 0110
	//0000 1110

	for(int i=0;i<MAXBIN;i++){
		
		vector[i] = vector[i+1];
	}
	vector[MAXBIN-1] =0;
}
void sumaBinaria(int vector1[],int vector2[]){
	int lleva=0,sumaCifra;
	for(int i=MAXBIN-1;i>=0;i--){
		sumaCifra = vector1[i]+vector2[i]+lleva;
		
		switch(sumaCifra){
			case 2: 
				auxiliarR[i] = 0;
				lleva = 1;
				break;
			case 3:
				auxiliarR[i] = 1;
				lleva=1;
				break;
			default:
				auxiliarR[i] = sumaCifra;
				lleva=0;
				break; 
		}
		
	}
}
void multiplicar(int numero1[],int numero2[]){
	bool finalizar;
	do
	{
		finalizar = true;
		printf("\n\nCiclo nuevo\n");	
		for(int i=0;i<MAXBIN;i++){
			printf("%d",numero1[i]);
		}
		printf("\t");
		for(int i=0;i<MAXBIN;i++){
			printf("%d",numero2[i]);
		}
		
		switch(numero1[7]){
			
			case 0:
			break;
			case 1: sumaBinaria(auxiliarR,numero2);
			break;
		}
		printf("\t");
		for(int i=0;i<MAXBIN;i++)
		{
			printf("%d",auxiliarR[i]);
		}
		correrParaDerecha(numero1);
		correrParaIzquierda(numero2);
		printf("\n");	
		for(int i=0;i<MAXBIN;i++){
			printf("%d",numero1[i]);
		}
		printf("\t");
		for(int i=0;i<MAXBIN;i++){
			printf("%d",numero2[i]);
		}
		printf("\t");
		for(int i=0;i<MAXBIN;i++)
		{
			printf("%d",auxiliarR[i]);
		}
		for(int i=0;i<MAXBIN;i++){
		
			if(numero1[i]!=0){
				finalizar = false;
			}
		}
	}while(!(finalizar));
	printf("\n\nFINAL:\n");
	for(int i=0;i<MAXBIN;i++)
	{
		printf("%d",auxiliarR[i]);
	}
}
void microcicloP(int a,int b){

	if(a<=b){
				asignarVectores(auxiliarR,auxiliarB);
			
				correrParaDerecha(auxiliarA);
				correrParaIzquierda(auxiliarB);	
			}
			else{
				asignarVectores(auxiliarR,auxiliarA);
			
				correrParaDerecha(auxiliarB);
				correrParaIzquierda(auxiliarA);
			}
}
void microcicloS(int a,int b){

	if(a<=b){
		correrParaDerecha(auxiliarA);
		correrParaIzquierda(auxiliarB);	
	}else{
		correrParaDerecha(auxiliarB);
		correrParaIzquierda(auxiliarA);
	}
}
main(){
	int valorParaSwitch = 0;
	printf("Ingresa el primer numero: ");
	scanf("%d",&a);
	printf("Ingresa el segundo numero: ");
	scanf("%d",&b);
	if(a<=255 && b<=255 &&a*b<=255)
	{
		printf("El vector A:\n");
		convertiraBinario(a,2,aBinarioCadena);
		
		printf("\n\nEl vector B:\n");
		convertiraBinario(b,2,bBinarioCadena);
		//
		asignarVectores(auxiliarA,aBinarioCadena);
		asignarVectores(auxiliarB,bBinarioCadena);
		printf("\n\nCiclo inicial\n");	
		
		if(a>b){
		
			for(int i=0;i<MAXBIN;i++){
				printf("%d",auxiliarB[i]);
			}
			printf("\t");
			for(int i=0;i<MAXBIN;i++){
				printf("%d",auxiliarA[i]);
			}
			valorParaSwitch = auxiliarB[MAXBIN-1];
		}else{
			for(int i=0;i<MAXBIN;i++){
				printf("%d",auxiliarA[i]);
			}
			printf("\t");
			for(int i=0;i<MAXBIN;i++){
				printf("%d",auxiliarB[i]);
			}
			valorParaSwitch = auxiliarA[MAXBIN-1];
		}
		switch(valorParaSwitch){
		
			case 0: microcicloS(a,b);
			break;
			case 1:
			microcicloP(a,b);
			break;
		}
		printf("\t");
		for(int i=0;i<MAXBIN;i++)
		{
			printf("%d",auxiliarR[i]);
		}
	
		//Segundo pelotón
		if(a<=b){
			printf("\n");
			for(int i=0;i<MAXBIN;i++){
				printf("%d",auxiliarA[i]);
			}
			printf("\t");
			for(int i=0;i<MAXBIN;i++){
				printf("%d",auxiliarB[i]);
			}
		}
		else{
			printf("\n");
			for(int i=0;i<MAXBIN;i++){
				printf("%d",auxiliarB[i]);
			}
			printf("\t");
			for(int i=0;i<MAXBIN;i++){
				printf("%d",auxiliarA[i]);
			}
		}
		
		printf("\t");
		for(int i=0;i<MAXBIN;i++)
		{
			printf("%d",auxiliarR[i]);
		}
		//
		
		if(a<=b){
			multiplicar(auxiliarA,auxiliarB);
		}
		else{
			multiplicar(auxiliarB,auxiliarA);
		}
		
	}
	else{
		printf("Ese número supera los 255");
	}
	getch();
	
}

