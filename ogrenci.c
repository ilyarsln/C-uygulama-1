#include <stdio.h>
#include "ogrenci.h"
#include <stdlib.h>
#include <string.h>

ogrenci o1;

void giris(){      // ilk çaðrýlan fonk (bütün mevzu burada dönüyor aslýnda)
	
	int secim = menu();		//menuyü burada çaðýrýyor
	
	while (secim != 0){		// deðer 0 deðilse loopda kal
		
		switch (secim){		// seçimi alýyorsun
			
			case 1 : yenikayit(); break;
			case 2 : kayitara(); break;
			case 3 : kayitsil(); break;
			case 4 : listele(); break;
			case 5 : tumkayitlarisil(); break;
		}
		secim=menu();    // seçilen fonksiyon tamamlandýktan sonra tekrar menüye dönüyor
		// 0'a kadar devam
	}
	
}


int menu(){  // sadece girdi alarak menüye gönderiyor
	
	
	printf("[1] Yeni Kayýt  ");
	printf("[2] Kayýt Ara  ");
	printf("[3] Kayýt Sil  ");
	printf("[4] Listele  ");
	printf("[5] Tüm Kayýtlarý Sil  ");
	printf("[0] ÇIKIÞ  ");
	
	int secim;
	
	do {
		
		printf("Seçim Yapýnýz [0-5] : ");
		secim = getche() - '0' ;	
		printf("\n");
		
		
	}  while( secim <0 || secim>5);
	
	return secim; // seçimi buradan gönderiyoruz
	
}


void yenikayit(){
	
	system("cls"); // ekraný temizledi
	printf("Yeni kayýt için ...\n");
	printf("Numara : "); girisal(o1.numara); // girdileri almaya baþlýyor
	printf("Ad : "); girisal(o1.ad);
	printf("Soyad : "); girisal(o1.soyad);
	printf("Adres : "); girisal(o1.adres);
	printf("Tel : "); girisal(o1.tel);
	veritabankaydet(o1);	// diðer fonksiyona dallanýyor
}


void kayitara(){
	
	system("cls");
	int sonuc=0;
	char aranan[20]; 
	printf("Ad: "); girisal(aranan );  // arayacaðýmýz metnin giriþi
	
	
	FILE *p;
	if(( p = fopen("ogrenciler.txt","rb")) == NULL  ) // bu sefer read
	{
		printf("Dosyaya Eriþilemedi ! \n");
		exit(1) ;
	}
	
	while(fread (&o1, sizeof(ogrenci), 1, p) != NULL){ //okuyor dosyayý
		
		if (strcmp( aranan, o1.ad) == 0){ // karþýlaþtýrýyor aranan ile dosyadaki isimleri
		//aynýysa 0 döner içeri girecek
			if(sonuc == 0)
			
			printf("%-20s%-20s%-20s%-20s%-20s\n", "NUMARA", "AD", "SOYAD",
			 "ADRES", "TEL");
			
			printf("%-20s%-20s%-20s%-20s%-20s\n", o1.numara, o1.ad, o1.soyad, o1.adres,
			 o1.tel);
			sonuc ++; // 1den fazla olma durumunda tekrar baþlýklarý atmasýn diye
		}
		
	}
	
	fclose(p); // dosya kapat
	if(sonuc == 0) // birini bulsa 1 olurdu, bulamadý
	printf("\n %s isimli kisi bulunamadý ! \n",aranan);
	else 
	printf("\n%s isimli kiþiden %d adet bulundu \n\n", aranan, sonuc);
	
}


void kayitsil(){
	
	system("cls");
	int sonuc=0;
	char aranan[20]; //aynen arýyor
	printf("Numara: "); girisal(aranan ); // isimle deðil numara ile arýyor
	
	
	FILE *p, *yp; // 2pointer tanýmlýyoruz 
	// 1 tanesi okuyacak
	// diðeri yedek oluþturacak
	if(( p = fopen("ogrenciler.txt","rb")) == NULL  )
	{
		printf("Dosyaya Eriþilemedi ! \n");
		exit(1) ;
	}
	
	if(( yp = fopen("yedek.txt","wb")) == NULL  )
	{
		printf("Dosyaya Eriþilemedi ! \n");
		exit(1) ;
	}
	
	while(fread (&o1, sizeof(ogrenci), 1, p) != NULL){ //okudu
		
		if (strcmp( aranan, o1.numara) == 0){  // karþýlaþtýrdý
		
		sonuc++;
		} 
		else
		{
		fwrite (&o1, sizeof(ogrenci), 1, yp);  // yedek oluþturdu
		}
		
	}

	fclose(p);
	fclose(yp);
	
	remove("ogrenciler.txt");
	rename("yedek.txt","ogrenciler.txt");
	
	if(sonuc == 0)
	printf("\n %s numaralý kisi bulunamadý ! \n",aranan);
	else 
	printf("\n%s numaralý kiþi silindi \n\n", aranan);
	
	
}


void listele(){
	
	system("cls");
	int sonuc=0;
	
	
	
	
	FILE *p;
	if(( p = fopen("ogrenciler.txt","rb")) == NULL  )
	{
		printf("Dosyaya Eriþilemedi ! \n");
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
	printf("\n Liste Boþ \n\n");
	else 
	printf("\n Listede %d adet öðrenci var \n\n", sonuc);
	
}

void tumkayitlarisil(){
	
	system("cls");
	char tercih;
	printf("Tüm kayýtlarý silmek istediðinize emin misiniz ? [E/H] "); scanf("%c",&tercih);
	
	if (tercih == 'e' || tercih =='E'){
		int sonuc = remove("ogrenciler.txt");
		if(sonuc == 0)
		printf("Kayýtlar Silindi.\n\n");
		else
		printf("Silme Ýþlemi Baþarýsýz !\n\n");
	}
	else
	{
		printf("Silme islemi iptal edildi \n\n");
	}
}

void veritabankaydet(ogrenci o1){ 
	
	system("cls");   // ekraný yine temizledi
	FILE *p; // pointer tanýmlandý file için
	if(( p = fopen("ogrenciler.txt","ab")) == NULL  ) //eðer dosya yoksa NULL döner 
	//eklemeli yazma ab
	{
		printf("Dosyaya Eriþilemedi ! \n");
		exit(1) ;
	}
	
	fwrite (&o1,sizeof(ogrenci),1,p); // o1 den baþlayacak //ogrenci size kadar yazacak 
	// 1 tane yazacak //p
	fclose(p); // kapatmak lazým
	printf("KAYIT BAÞARILI \n\n");
	
}


void girisal(char *p){
	
	
	fgets(p,20,stdin);
	int n = strlen(p);
	p[n-1] = '\0';
	
}
