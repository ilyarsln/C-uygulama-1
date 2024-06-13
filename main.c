#include <stdio.h>
#include <stdlib.h>
#include "ogrenci.h"
#include <locale.h> 	// dil kütüphanesi


int main(int argc, char *argv[]) {
	
	setlocale(LC_ALL,"Turkish");      // türkçe karakter kullanýmý için ayarlama
	printf("\nÖÐRENCÝ KAYIT UYGULAMASI\n\n");
	giris();
	
	return 0;
}
