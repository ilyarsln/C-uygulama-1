#include <stdio.h>
#include "ogrenci.h"
#include <stdlib.h>
#include <string.h>

ogrenci o1;

void giris(){      // ilk �a�r�lan fonk (b�t�n mevzu burada d�n�yor asl�nda)
	
	int secim = menu();		//menuy� burada �a��r�yor
	
	while (secim != 0){		// de�er 0 de�ilse loopda kal
		
		switch (secim){		// se�imi al�yorsun
			
			case 1 : yenikayit(); break;
			case 2 : kayitara(); break;
			case 3 : kayitsil(); break;
			case 4 : listele(); break;
			case 5 : tumkayitlarisil(); break;
		}
		secim=menu();    // se�ilen fonksiyon tamamland�ktan sonra tekrar men�ye d�n�yor
		// 0'a kadar devam
	}
	
}


int menu(){  // sadece girdi alarak men�ye g�nderiyor
	
	
	printf("[1] Yeni Kay�t  ");
	printf("[2] Kay�t Ara  ");
	printf("[3] Kay�t Sil  ");
	printf("[4] Listele  ");
	printf("[5] T�m Kay�tlar� Sil  ");
	printf("[0] �IKI�  ");
	
	int secim;
	
	do {
		
		printf("Se�im Yap�n�z [0-5] : ");
		secim = getche() - '0' ;	
		printf("\n");
		
		
	}  while( secim <0 || secim>5);
	
	return secim; // se�imi buradan g�nderiyoruz
	
}


void yenikayit(){
	
	system("cls"); // ekran� temizledi
	printf("Yeni kay�t i�in ...\n");
	printf("Numara : "); girisal(o1.numara); // girdileri almaya ba�l�yor
	printf("Ad : "); girisal(o1.ad);
	printf("Soyad : "); girisal(o1.soyad);
	printf("Adres : "); girisal(o1.adres);
	printf("Tel : "); girisal(o1.tel);
	veritabankaydet(o1);	// di�er fonksiyona dallan�yor
}


void kayitara(){
	
	system("cls");
	int sonuc=0;
	char aranan[20]; 
	printf("Ad: "); girisal(aranan );  // arayaca��m�z metnin giri�i
	
	
	FILE *p;
	if(( p = fopen("ogrenciler.txt","rb")) == NULL  ) // bu sefer read
	{
		printf("Dosyaya Eri�ilemedi ! \n");
		exit(1) ;
	}
	
	while(fread (&o1, sizeof(ogrenci), 1, p) != NULL){ //okuyor dosyay�
		
		if (strcmp( aranan, o1.ad) == 0){ // kar��la�t�r�yor aranan ile dosyadaki isimleri
		//ayn�ysa 0 d�ner i�eri girecek
			if(sonuc == 0)
			
			printf("%-20s%-20s%-20s%-20s%-20s\n", "NUMARA", "AD", "SOYAD",
			 "ADRES", "TEL");
			
			printf("%-20s%-20s%-20s%-20s%-20s\n", o1.numara, o1.ad, o1.soyad, o1.adres,
			 o1.tel);
			sonuc ++; // 1den fazla olma durumunda tekrar ba�l�klar� atmas�n diye
		}
		
	}
	
	fclose(p); // dosya kapat
	if(sonuc == 0) // birini bulsa 1 olurdu, bulamad�
	printf("\n %s isimli kisi bulunamad� ! \n",aranan);
	else 
	printf("\n%s isimli ki�iden %d adet bulundu \n\n", aranan, sonuc);
	
}


void kayitsil(){
	
	system("cls");
	int sonuc=0;
	char aranan[20]; //aynen ar�yor
	printf("Numara: "); girisal(aranan ); // isimle de�il numara ile ar�yor
	
	
	FILE *p, *yp; // 2pointer tan�ml�yoruz 
	// 1 tanesi okuyacak
	// di�eri yedek olu�turacak
	if(( p = fopen("ogrenciler.txt","rb")) == NULL  )
	{
		printf("Dosyaya Eri�ilemedi ! \n");
		exit(1) ;
	}
	
	if(( yp = fopen("yedek.txt","wb")) == NULL  )
	{
		printf("Dosyaya Eri�ilemedi ! \n");
		exit(1) ;
	}
	
	while(fread (&o1, sizeof(ogrenci), 1, p) != NULL){ //okudu
		
		if (strcmp( aranan, o1.numara) == 0){  // kar��la�t�rd�
		
		sonuc++;
		} 
		else
		{
		fwrite (&o1, sizeof(ogrenci), 1, yp);  // yedek olu�turdu
		}
		
	}

	fclose(p);
	fclose(yp);
	
	remove("ogrenciler.txt");
	rename("yedek.txt","ogrenciler.txt");
	
	if(sonuc == 0)
	printf("\n %s numaral� kisi bulunamad� ! \n",aranan);
	else 
	printf("\n%s numaral� ki�i silindi \n\n", aranan);
	
	
}


void listele(){
	
	system("cls");
	int sonuc=0;
	
	
	
	
	FILE *p;
	if(( p = fopen("ogrenciler.txt","rb")) == NULL  )
	{
		printf("Dosyaya Eri�ilemedi ! \n");
		exit(1) ;
	}
	
	printf("%-20s%-20s%-20s%-20s%-20s\n", "NUMARA", "AD", "SOYAD",
			 "ADRES", "TEL");
	
	while(fread (&o1, sizeof(ogrenci), 1, p) != NULL){
		
			printf("%-20s%-20s%-20s%-20s%-20s\n", o1.numara, o1.ad, o1.soyad, o1.adres,
			 o1.tel);
			sonuc ++;
	
	}
	
	fclose(p);
	if(sonuc == 0)
	printf("\n Liste Bo� \n\n");
	else 
	printf("\n Listede %d adet ��renci var \n\n", sonuc);
	
}

void tumkayitlarisil(){
	
	system("cls");
	char tercih;
	printf("T�m kay�tlar� silmek istedi�inize emin misiniz ? [E/H] "); scanf("%c",&tercih);
	
	if (tercih == 'e' || tercih =='E'){
		int sonuc = remove("ogrenciler.txt");
		if(sonuc == 0)
		printf("Kay�tlar Silindi.\n\n");
		else
		printf("Silme ��lemi Ba�ar�s�z !\n\n");
	}
	else
	{
		printf("Silme islemi iptal edildi \n\n");
	}
}

void veritabankaydet(ogrenci o1){ 
	
	system("cls");   // ekran� yine temizledi
	FILE *p; // pointer tan�mland� file i�in
	if(( p = fopen("ogrenciler.txt","ab")) == NULL  ) //e�er dosya yoksa NULL d�ner 
	//eklemeli yazma ab
	{
		printf("Dosyaya Eri�ilemedi ! \n");
		exit(1) ;
	}
	
	fwrite (&o1,sizeof(ogrenci),1,p); // o1 den ba�layacak //ogrenci size kadar yazacak 
	// 1 tane yazacak //p
	fclose(p); // kapatmak laz�m
	printf("KAYIT BA�ARILI \n\n");
	
}


void girisal(char *p){
	
	
	fgets(p,20,stdin);
	int n = strlen(p);
	p[n-1] = '\0';
	
}
