//Y���n (Stack) veri yap�s� kullarak k��eli parantez i�indeki metini �n�ndeki say� kadar yazd�rma uygulamas�

#include<stdio.h>
#include<string.h>

#define boyut  100
#define size 300


char metin[size];
char dizi[boyut];

typedef struct yiginInt{
	int indis ;
	int eleman[boyut];
}stackInt;

typedef struct yiginChar{
	int indisc ;
	char elemanc[boyut];
}stackChar;

stackInt stack;//temel y���n

stackChar charStack;//temel y���n


int doluMu(int x){
	if(x >= boyut-1)return -1; else return 1;
}

int bosMu(int x){
	if(x <= -1)return -1; else return 1;
}

void push(int x){
	
	if(doluMu(stack.indis) == -1){
		printf("Yigin dolu");
	}
	else{
		stack.indis++;
		stack.eleman[stack.indis] = x;
	}

}

void pushc(char x){
	
	if(doluMu(charStack.indisc) == -1){
		printf("Yigin dolu");
	}
	else{
		charStack.indisc++;
		charStack.elemanc[charStack.indisc] = x;
	}

}


int pop(){
	
	if(bosMu(stack.indis) == -1){
		printf("Yigin bos\n");
	}
	else{
		int po;		
		po = stack.eleman[stack.indis];
		stack.indis--;
		return po;
	}
	
}

char popc(){
	
	if(bosMu(charStack.indisc) == -1){
		printf("Yigin bos\n");
	}
	else {
		
		return charStack.elemanc[charStack.indisc--];
	}

}


void charOrInt(){
	int i,uzunluk = strlen(metin);
	for(i = 0; i < uzunluk; i++){
		
		if(metin[i]>=48 && metin[i]<=57){ //ACII koduna g�re rakamlar� buluyoruz
			int ascii = metin[i] - 48;//ASCII kodundan 48 ��kararak rakamlar� 0 la 9 aras�na �eviriyoruz
			push(ascii); //ve say� y���n�na ekliyoruz
		}
		else {if(metin[i] == ']')continue;
			pushc(metin[i]); //say� de�ilse char y���n�na ekliyoruz
		}
	}
	
}

int i = 0;


void popDizi(){ //y���ndan alma fonksiyonu
	int a = 0 ,sayac = 0;
	char control = 'c';
	int gcc = charStack.indisc;
	
	while(control != '[')
	{	
			control = charStack.elemanc[charStack.indisc];
	  		if(charStack.elemanc[charStack.indisc] == '['){
				charStack.indisc--;break;}
		 else{
			dizi[i] = charStack.elemanc[charStack.indisc];
			charStack.indisc--; 
			i++;
			}
		}

}


void outPut(){ //basma fonksiyonu
	int m,j;
	while(stack.eleman[stack.indis] != -1){
		popDizi();
		for(m = 1; m <= stack.eleman[stack.indis]; m++){
			
			for(j = 0; j<strlen(dizi); j++){
				printf("%c",dizi[j]);
			}
		
		}
		stack.indis--;
	}

}



int main(){
	
	stack.indis = -1;
	charStack.indisc = -1;
	int m,j,n;
	
	printf("\nLutfen yazdirmak istediginiz veriyi sayi[String] seklinde giriniz\n\nGiris:");
	scanf("%s",metin);
	printf("\nInput:%s\n",metin);
	
	charOrInt();
	
	printf("Output: ");	
 	 outPut();
 
	return 0;
}
