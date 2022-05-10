//HashMap ile öðrenci notlarýný tutan uygulama

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<locale.h>

typedef struct {
	int ogr_no;
	char ad[20];
	int notu;
}Ogrenci;

Ogrenci veriListe[10];

int hashTablo[10][2];

void tabloSifirla(){ //hashTablo nun tüm deðerlerini -1 yapar

	int i = 0;

	while(i < 10){
		hashTablo[i][0] = -1;
		hashTablo[i][1] = -1;
		i++;
	}
}

void veriSifirla(){ //veriListe  nin tüm deðerlerini -1 yapar

	int i = 0;

	while(i < 10){
		veriListe[i].ogr_no = 0;
		strcpy(veriListe[i].ad,"\0");
		veriListe[i].notu = 0;
		i++;
	}
}

int hash(int veri){//hashing islemi yapar
	int indis;
	indis = veri % 10;
	return indis;
}

int bosBul(){ //tabloda bos yer bulur
	int i = 0;
	while((hashTablo[i][0] != -1) && (i<= 9)){
		i++;
	}
	if(i <= 9){
		return i;
	}else{
		return -1;
	}
}

int ayniMi(int deger){ //farklý indisteki ayný degerin sonuna ekler
	int i = 0;//indis degerini tutuyor 
	int onceki,gcc,a,b;
	while(((hashTablo[i][0] % 10) != (deger % 10) ) && (i<= 9)){
		i++;
	}
	a = hashTablo[i][0] % 10; b = deger % 10;
	
	if(hashTablo[i][1] == -1){//nexti -1 se 
		onceki = i;
		i = bosBul();
		if(i == -1)return i;
		hashTablo[i][0] = deger;
		hashTablo[onceki][1] = i;
		return i;
	}
	
	else if(hashTablo[i][1] != -1){
		
		while(hashTablo[i][1] != -1){
			
			i = hashTablo[i][1];
		}
		gcc = bosBul();
		if(gcc == -1)return gcc;
		if(a == b){
		hashTablo[i][1] = gcc;
		}
		hashTablo[gcc][0] = deger;
		hashTablo[gcc][1] = -1;
		return gcc;
	}
	
}

int ekle(int indis,int deger){//tabloya ekleme islemi
	int onceki,a,b,gcc;
	a = hashTablo[indis][0] % 10; b = deger % 10;
	
	if(hashTablo[indis][0] == -1){ //notu -1 se 
		hashTablo[indis][0] = deger;
		return indis;	
	}
	
	else if(hashTablo[indis][1] == -1 && (a==b)){//nexti -1 se 
		onceki = indis;
		indis = bosBul();
		if(indis == -1)return indis;
		hashTablo[indis][0] = deger;
		hashTablo[onceki][1] = indis;
		return indis;
	}
	
	else if((hashTablo[indis][1] != -1) && (a == b)){
		
		while(hashTablo[indis][1]!=-1){

			indis = hashTablo[indis][1];
		}
		gcc = bosBul();
		if(gcc == -1)return gcc;
		if(a==b)
		hashTablo[indis][1] = gcc;
		hashTablo[gcc][0] = deger;
		hashTablo[gcc][1] = -1;
		return gcc;
	}
	else{
		
		return ayniMi(deger);
	}
	
}

int tablodaMi(int aranan){//tabloda böyle bir indisin olup olmadýðýný kontrol eder varsa o indisten baþlamayý saðlar
	int i = 0,indis;
	indis = hash(aranan);
	if(hashTablo[indis][0] % 10 == aranan % 10){
		return indis;
	}else{
	
		for(i = 0;i <= 9; i++){//o indiste olmasý gereken farklý indisteyse
			if(hashTablo[i][0] % 10 == aranan % 10)return i;	
		}
		return -1;//yoksa -1 döner
	}
}

int veriBul(int aranan){
	int i = 0,indis,a = 0;
	indis = tablodaMi(aranan);
	if(indis == -1){
		printf("Tabloda böyle bir indis deðeri yok\n\n");
		return -1;
	}
	
	while(indis != -1){

		i++;
		if(hashTablo[indis][0] == aranan){
			printf("\n(%d) Veri %d.adýmda bulundu\n",aranan,i);
			printf("Verinin içindekiler;\nNo:%d Ad:%s Notu:%d\n\n",veriListe[indis].ogr_no,veriListe[indis].ad,veriListe[indis].notu);
			a++;
			if(hashTablo[indis][1] == -1){//sonrasý yoksa
				return 1;
			}
			indis = hashTablo[indis][1];//iterasyon iþlemi
		}
		else{
		
			if((hashTablo[indis][0] != aranan) && (hashTablo[indis][1] == -1) && (a == 0)){
				printf("Aranan deðer bulunamadý\n\n");return 0;
			}
			indis = hashTablo[indis][1];//iterasyon iþlemi
			
		}
	}

}

void tabloListele(){//tabloyu listeler
	
	int i = 0;
	
	while(i < 10){
		printf("%d %d\n",hashTablo[i][0],hashTablo[i][1] );
		i++;
	}
}

void Listele(){//tablo ve veriyi listeler
	
	int i = 0;
	printf("  Tablo          Veriler\n");
	printf("*********     *************\n");
	while(i < 10){
		
		printf("%d| %d %d -----> %d %s %d\n",i,hashTablo[i][0],hashTablo[i][1],veriListe[i].ogr_no,veriListe[i].ad,veriListe[i].notu);
		i++;
	}
	printf("\n\n");
}


int main(){
	
	setlocale(LC_ALL,"Turkish");
	
	int secim, i, deger, indis, a, c,aranan;
	FILE *veri;
	
	tabloSifirla();
	do{
		
	printf("----------Ana Menü-----------\n");
	printf("-> Dosyadan veri çekmek için : 1\n");
	printf("-> Veri girmek için : 2\n");
	printf("-> Veri aramak için : 3\n");
	printf("-> Veri listelemek için : 4\n");
	printf("-> Tablo sýfýrlama için : 5\n");
	printf("-> Çýkýþ için : 6 Giriniz\n**********************************\n");
	printf("-> Giriþ: ");
	scanf("%d",&secim);
	
	system("cls");
	
	switch(secim){
		case 1:
			printf("\n (1) Dosyadan veri çekme' iþlemi seçildi\n");
			veri = fopen("veri.txt","r");
			if(veri == NULL) {
				printf("\nDosya Bulunamadý!\n");
			}else{
				printf("\nDosya mevcut, veri dosyadan çekildi.\n\n");
				Ogrenci gcc[10];
				i = 0;
				while(!feof(veri)){
					fscanf(veri,"%d %s %d",&gcc[i].ogr_no,&gcc[i].ad,&gcc[i].notu);
					
					deger = gcc[i].notu;
					indis = hash(deger);
					a = ekle(indis,deger);
					
					if(a != -1){
						veriListe[a].notu = deger;
						strcpy(veriListe[a].ad,gcc[i].ad);
						veriListe[a].ogr_no = gcc[i].ogr_no;
					}
					else{
						printf(" Tablo doluuu !\n");
					}
					i++;
				}
			}
			
			break;
		case 2:
			printf("\n'(2) Veri girme' iþlemi seçildi\n");
			
				Ogrenci gccc[10];
				i = 0;
				while(i<11){
					printf("\nVeriyi Numara Ad Not þeklinde giriniz.\n");
					scanf("%d %s %d",&gccc[i].ogr_no,&gccc[i].ad,&gccc[i].notu);
					
					deger = gccc[i].notu;
					indis = hash(deger);
					a = ekle(indis,deger);
					
					if(a != -1){
						veriListe[a].notu = deger;
						strcpy(veriListe[a].ad,gccc[i].ad);
						veriListe[a].ogr_no = gccc[i].ogr_no;
					}
					else{
						printf(" tablo doluuu !\n");
					}
					i++;
					printf("\nDevam Etmek istiyor musunuz[Evet(1)/Hayýr(0)]");
					scanf("%d",&c);
					
					if(c == 0){
						system("cls");
						break;
					}else continue;
					
					}
			break;
		case 3:
			printf("\n'(3) Veri arama' iþlemi seçildi\n");
			printf("Aranýlan deðer: ");
			scanf("%d",&aranan);
			if(aranan != -1){
				veriBul(aranan);
			}
			else{
				printf("\nYasak giriþ yapýldý! Ana menüye dönüldü.\n\n");
			}
			break;
		case 4:
			printf("\n'(4) Veri Listeleme' iþlemi seçildi\n");
			Listele();
			break;	
		case 5:
			printf("\n'(5) Tablo sýfýrlama' iþlemi seçildi\n");
			tabloSifirla();
			veriSifirla();
			printf("\nVeri Sýfýrlandý\n\n");
			break;	
		case 6:
			printf("\n'(6) Çýkýþ' iþlemi seçildi\n\n");
			break;		
		default:
			printf("\nHatalý giriþ.Lütfen geçerli bir giriþ yapýnýz.\n\n");
			break;		
	}
	
	}while(secim != 6);
	fclose("damage.txt");	
	return 0;
}
