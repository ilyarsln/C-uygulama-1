#ifndef _OGRENCI_h
#define _OGRENCI_h

typedef struct Ogrenci {
	char numara[20];
	char ad[20];
	char soyad[20];
	char adres[20];
	char tel[20];
	
} ogrenci ;



void giris();
int menu();
void yenikayit();
void kayitara();
void kayitsil();
void listele();
void tumkayitlarisil();
void veritabankaydet(ogrenci o1);
void girisal(char *p);


#endif
