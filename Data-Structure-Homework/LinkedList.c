//Baðlý liste (Linked List) veri yapýsý kullanarak polinom uygulamasý

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct dugum{ //struct n yapýsýný urettik düðüm temel yapýsý
	int derece;
	int katSayi;
	struct dugum *next;
	
};

typedef struct dugum node; 


void yaz(node *p){ //Listeyi yazma fonksiyonu. 
	while(p != NULL){ 
		printf("Derece:%d Katsayi:%d\n ",p->derece,p->katSayi);
		p = p->next; 
	}
}

void yazpol(node *p){ //Polinom þeklinde yazma fonksiyonu.
	
	printf("\n");
	
	while(p != NULL){ 
		printf("(%d)X^%d + ",p->katSayi,p->derece);
		p = p->next; 
	}
}

void hesapla(node *p,int x){ //polinomu hesaplama fonksiyonu
	
	int sonuc = 0;
	
	while(p != NULL){ 
		sonuc += p->katSayi * pow(x,p->derece);
		p = p->next; 
	}
	
	printf("Sonuc: %d \n",sonuc);
}

void tersYaz(node *r){
	if(r->next != NULL) tersYaz(r->next);
	printf("%d",r->derece);
}

node * ekle(node *r,int x,int y) //Büyükten küçüðe sýrasýyla ekleme fonksiyonu 
{
	if(r == NULL){ //ilk eleman yoksa
		r = (node*)malloc(sizeof(node)); 
		r->derece = x;
		r->katSayi = y; 
		r->next = NULL; 
		return r;
	}
	
	if(r->derece < x){ //ilk elemandan büyük eleman gelirse
		node *gecici = (node*)malloc(sizeof(node));
		gecici->derece = x;
		gecici->katSayi = y;
		gecici->next = r;
		r = gecici;
		return gecici;
	}
	//arada bir deðer veya sona eklenecek elemanlar için 
	node *iter; 
	iter = r;
	while(iter->next != NULL && iter->next->derece > x){
		iter = iter->next;
	}
	
	node *gecici = (node*)malloc(sizeof(node));
	gecici->derece = x;
	gecici->katSayi = y;
	gecici->next = iter->next;
	iter->next = gecici;
	return r;

}

int listBoyut(node *r)//Listenin boyutunu bulan fonksiyon
{
	node *iter = r;
	int a = 0;
	while(iter != NULL){  
		iter = iter->next;
		a++;
	}	
	if(iter == NULL)
	{
		return a;
	} 
	return a;
}

int arama(node *r,int x)  //Ayný dereceli terim varmý bulmaya yarayan fonksiyon
{
	node *iter = r;
	while(iter != NULL && iter->derece != x){
		iter = iter->next;
	}	
	if(iter == NULL)
	{
		return 0;
	} 
	
	return 1;
}

node *sil(node *r,int x) // silme fonksiyonu
{
	node *gecici;
	node *iter = r;
	
	if(r->derece == x){
		gecici = r;
		r = r->next;
		free(gecici);
		return r;
	}
	
	while(iter->next != NULL && iter->next->derece != x){
		iter = iter->next;
	}
	
	if(iter->next == NULL){
		printf("Boyle bir deger yok\n");
		return r;
	}
	
	gecici = iter->next;
	iter->next = iter->next->next;
	free(gecici);
	return r;
}



int main(){
	
	char secim;
	node *root; 
	root = NULL; 
	int sayi = 1, der, kat, deger, taban;
	
	printf("Ekleme icin ' e ' harfine basiniz.\n ");
	printf("Silme icin ' s ' harfine basiniz.\n ");
	printf("Yazdirma icin ' y ' harfine basiniz.\n ");
	printf("Hesaplama icin ' h ' harfine basiniz.\n ");
	printf("Cikis ve kayit icin ' c ' harfine basiniz.\n ");
	printf("------------------------------------------\n\n ");
	
	do{
	printf("\nIslem Seciniz: ");
	scanf("%c",&secim);
	
		switch(secim)
		{
			case 'e':
			
			printf("Ekleme islemi secildi\nPolinomun degerlerini girin:\n");
			printf("(Deger girmeyi bitirmek icin dereceyi negatif girin)\n--------------------------------------------------------\n");
			
			printf("%d.Derece:",sayi);
			scanf("%d",&der);
			
			if(der<0)
			{
			break;
			}
			
			printf("%d.Kat sayi:",sayi);
			scanf("%d",&kat);
	
			root = ekle(root,der,kat); //listeye ekleme iþlemi
			
			while(sayi>=0)  //Derece katsayi giriþ bloðu 
			{
				sayi++;	
				printf("%d.Derece:",sayi);
				scanf("%d",&der);
		
				if(der<0)
				{
				break;
				}
			
				if(arama(root,der) == 1)
				{
				printf("Bu derece mevcut\n");
				sayi--;
				}
				else
				{
			
				printf("%d.Kat sayi:",sayi);
				scanf("%d",&kat);
	
				root = ekle(root,der,kat); 
				}
			}
		
			printf("\n****************************\n\n"); 	
			
			break;	
		
			case 's':
			printf("Silme islemi secildi\n-----------------------\n");
			printf("Silinecek deger:");
			scanf("%d",&deger);
			root = sil(root,deger);	
			printf("\n****************************\n\n"); 	
			break;
			
			case 'y':
			printf("Yazdirma islemi secildi\n-----------------------\n");
			yaz(root); // bastýrdýk
			yazpol(root);
			//tersYaz(root);
			printf("\n****************************\n\n"); 
			break;
		
			case 'h':
			printf("Hesaplama islemi secildi\n-----------------------\n");
			printf("Taban degerini giriniz: ");
			scanf("%d",&taban);
			hesapla(root,taban);
			printf("\n****************************\n\n"); 
			break;	
		
			case 'c':
			printf("Cikis islemi secildi\n-----------------------\n");;
			FILE *dosya = fopen("kayit.txt","w+");
			node *i;
			i = root;
			while(i != NULL)
			{
				fprintf(dosya,"Derece:%d Kat sayi:%d \n",i->derece,i->katSayi);
				i = i->next;
			}
			fclose(dosya);
			break;	
			
		}
	
	}while(secim != 'c');
	
	
	free(root);
		
}
