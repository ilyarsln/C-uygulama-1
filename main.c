#include <stdio.h>
#include <stdlib.h>
#include "ogrenci.h"
#include <locale.h> 	// dil k�t�phanesi


int main(int argc, char *argv[]) {
	
	setlocale(LC_ALL,"Turkish");      // t�rk�e karakter kullan�m� i�in ayarlama
	printf("\n��RENC� KAYIT UYGULAMASI\n\n");
	giris();
	
	return 0;
}
