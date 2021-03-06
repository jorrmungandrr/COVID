
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "jlib.h"

// bool promjenjiva
typedef enum { false, true } bool;

#define arrow_DOWN 66
#define arrow_UP 65
#define ENTER 10



void bell(void){
	printf("\a");
}

// ispis strelice u meniju
void strelica(int x, int y){

	(x == y) ? printf("\t-->\t") : printf("\t\t ");
}



// meni za izbor drzave
int meniDrzava(void){

	int taster = 0;
	int y = 1;

	do{

		system("clear");
		printf("Izaberi jednu od sljedećih opcija : \n\n");

		strelica(1, y);		printf("Srbija\n");
		strelica(2, y);		printf("Italija\n");
		strelica(3, y);		printf("Francuska\n");
		strelica(4, y);		printf("Izlaz\n");


		taster = getch();

		if (taster == arrow_DOWN && y != 4)
			y++;

		else if (taster == arrow_UP && y != 1)
			y--;

	} while (taster != ENTER);

	return y;
	
}



// meni za izbor statistike
int meniOpcija(void){

	int taster = 0;
	int y = 1;

	do{

		printf("Izaberi jednu od sljedećih opcija : \n\n");

		strelica(1, y);		printf("Statistika\n");
		strelica(2, y);		printf("Procjene\n");
		strelica(3, y);		printf("Izbor države\n");

		taster = getch();

		if (taster == arrow_DOWN && y != 3)
			y++;

		else if (taster == arrow_UP && y != 1)
			y--;

		system("clear");

	} while (taster != ENTER);

	return y;
	
}



// opšte informacije - broj zaraženih, umrlih, mortalitet
void statistika(float zarazeni, float umrli){

	system("clear");
	printf("Broj zaraženih : %ld, broj umrlih : %g\nStopa mortaliteta : %.2f %%\n\n\n", (long)zarazeni, umrli, umrli / zarazeni * 100);
}



// procjene u opdnosu na populaciju
void procjene(float zarazeni, float umrli, int stanovnici){

	system("clear");
	printf("%.2f %% populacije je zaraženo.\n%.5f %% populacije je umrlo.\nMogući broj zaraženih je između %d i %d.\n\n",
		   (zarazeni / stanovnici) * 100, (umrli / stanovnici) * 100, (long)zarazeni * 32, (long)zarazeni * 73);
}



// preuzimanje fajla sa podacima o broju umrlih i zaraženih
void info(){

	CURL *curl;
	FILE *f;
	int rez;

	f = fopen("info.txt", "wb");

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/jorrmungandrr/COVID/master/info.txt");
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);

	rez = curl_easy_perform(curl);

	fclose(f);
	curl_easy_cleanup(curl);
}





void main(){

	int D, i, j,
		uI, uS, uF, uA,
		zI, zS, zF, zA;

	static int umrli[3], zarazeni[3];
	int stanovnici[] = {9024734, 60317116, 67076000};

	long s;
	float p, k;
	FILE *infos;
	bool kraj = false;


	// pruzimanje informacija
	info();

	// otvaranje fajla sa informacijama
	infos = fopen("info.txt", "r");

			for (j = 0; j < 3; j++){

				fscanf(infos, "%d %d\n", &zarazeni[j], &umrli[j]);
			}

	fclose(infos);




	while (1){

		kraj = false;
		D = meniDrzava();
		bell();
		
		if (D == 4)
			break;

		if (D >= 6)
			continue;


		p = umrli[D - 1];
		k = zarazeni[D - 1];
		s = stanovnici[D - 1];

		system("clear");



		do{

			i = meniOpcija();
			bell();
			
			
			switch (i){

			case 1:
				statistika(k, p);
				break;

			case 2:
				procjene(k, p, s);
				break;

			case 3:
				kraj = true;
				bell();
				break;

			default:
				system("clear");
				continue;
			}

		} while (kraj == false);
	}
}
