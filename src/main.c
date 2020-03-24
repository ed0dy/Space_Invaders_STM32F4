/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "serial.h"
#include "vt100.h"

// Fenetre

#define LONG_FENETRE (80)
#define LARG_FENETRE (24)
const char contour[] = "#";

//Touches

char toucheclav = 0;   //Récupère la dernière touche appuyé

//Missile

#define ORIGINE_MISSILE (21)
const char missile[] = "|";
uint8_t xm = 35;   //Initialise la position du missile en X et Y
uint8_t ym = 22;

//Alien

const char alien1[] = "Y";
typedef struct {

	uint8_t x;
	uint8_t y;
	uint8_t points;
	uint8_t toucher;

} alien;

alien t_alien[20] = { 0 };  //Initialise les valeurs de tous les enemies à 0
uint8_t pas_deplacement_alien = 0;  //

//Vaisseau

const char ship[] = "^";
uint8_t xv = 35;   //Initialise la position du vaisseau en X et Y
uint8_t yv = 22;

//Variables de jeu

uint8_t score = 0;
uint8_t vies = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Debut du programme

//Affiche le meunu principal du jeu

void menu_principal(void) {
	vt100_move(3, 2);
	serial_puts(
			"                                        d8b                             888");
	vt100_move(3, 3);
	serial_puts(
			"                                        Y8P                             888");
	vt100_move(3, 4);
	serial_puts(
			"                                                                        888");
	vt100_move(3, 5);
	serial_puts(
			".d8888b 88888b.  8888b.  .d8888b .d88b. 88888888b. 888  888 8888b.  .d88888");
	vt100_move(3, 6);
	serial_puts(
			"88K     888 Y88b    Y88bd88PY   d8P  Y8b888888 Y88b888  888    Y88bd88Y 888");
	vt100_move(3, 7);
	serial_puts(
			"dY8888b.888  888.d888888888     88888888888888  888Y88  88P.d888888888  888");
	vt100_move(3, 8);
	serial_puts(
			"     X88888 d88P888  888Y88b.   Y8b.    888888  888 Y8bd8P 888  888Y88b 888");
	vt100_move(3, 9);
	serial_puts(
			" 88888P'88888PY dY888888 dY8888P bY8888 888888  888  Y88P  dY888888 dY88888");
	vt100_move(3, 10);
	serial_puts(
			"        888                                                                ");
	vt100_move(3, 11);
	serial_puts(
			"        888                                                                ");
	vt100_move(3, 12);
	serial_puts(
			"        888                                                                ");

	vt100_move(25, 15);
	serial_puts("APPUYER SUR 'ESPACE' POUR JOUER");
	vt100_move(29, 17);
	serial_puts("GAUCHE : Q | D : DROITE");
	vt100_move(60, 22);
	serial_puts("Jean-Pascal BARRON");
}

//Attend l'appuie sur une touche pour lancer la fonction suivante

void lancer_jeu(void) {
	signed char touche = -1;
	while (touche == -1) {
		touche = serial_get_last_char();
	}
}

//Dessine le contour du menu principal

void contour_acceuil(void) {
	int dem = 0;

	for (dem = 1; dem <= LONG_FENETRE; dem++) {
		vt100_move(dem, 1);
		serial_puts(contour);
	}

	dem = 0;

	for (dem = 1; dem <= LARG_FENETRE; dem++) {
		vt100_move(1, dem);
		serial_puts(contour);
	}

	dem = 0;

	for (dem = 1; dem <= LARG_FENETRE; dem++) {
		vt100_move(LONG_FENETRE, dem);
		serial_puts(contour);
	}

	dem = 0;

	for (dem = 1; dem <= LONG_FENETRE; dem++) {
		vt100_move(dem, LARG_FENETRE);
		serial_puts(contour);
	}
}

//Desine le contour de la fenetre de jeu

void contour_jeu(void) {
	int dem = 0;

	for (dem = 1; dem <= LONG_FENETRE; dem++) {
		vt100_move(dem, 1);
		serial_puts(contour);
	}

	dem = 0;

	for (dem = 1; dem <= LARG_FENETRE; dem++) {
		vt100_move(1, dem);
		serial_puts(contour);
	}

	dem = 0;

	for (dem = 1; dem <= LARG_FENETRE; dem++) {
		vt100_move(LONG_FENETRE, dem);
		serial_puts(contour);
	}

	dem = 0;

	for (dem = 1; dem <= LONG_FENETRE; dem++) {
		vt100_move(dem, LARG_FENETRE);
		serial_puts(contour);

	}

	vt100_move(4, 23);
	serial_puts("SCORE : ");
	vt100_move(12, 23);
	serial_puts("0");

	vt100_move(70, 23);
	serial_puts("VIES : ");
	vt100_move(77, 23);
	serial_puts("1");

}

void deplacer_vaisseau(void) {
	toucheclav = serial_get_last_char();

	if (toucheclav == 'd') {
		if (xv < LONG_FENETRE - 1) {
			vt100_move(xv, yv);
			serial_putchar(' ');
			xv += 1;
			vt100_move(xv, yv);
			serial_puts(ship);
		}

	}

	if (toucheclav == 'q') {
		if (xv > 2) {
			vt100_move(xv, yv);
			serial_putchar(' ');
			xv -= 1;
			vt100_move(xv, yv);
			serial_puts(ship);
		}
	}
}

void init_enemies(void) {
	uint8_t xb = 3;
	uint8_t yb = 3;
	uint8_t ibot = 0;

	for (ibot = 0; ibot <= 19; ibot++) {

		t_alien[ibot].x = xb;
		t_alien[ibot].y = yb;
		//vt100_move(t_alien[ibot].x, t_alien[ibot].y);
		//serial_puts(alien1);
		xb += 1;
		//vt100_move(t_alien[xb].x, t_alien[yb].y);
		//vt100_move(t_alien[xb].x, yb + 1);
		//serial_puts(alien1);

	}
}

void enemies(void) {

	pas_deplacement_alien++;
	uint8_t ibot = 0;

	if (t_alien[20].x <= LONG_FENETRE - 3) {

		for (ibot = 0; ibot <= 19; ibot++) {

			vt100_move(t_alien[ibot].x, 3);
			serial_puts(" ");

			t_alien[ibot].x = pas_deplacement_alien;

			vt100_move(t_alien[ibot].x, 3);
			serial_puts(alien1);

		}

	}

}

void tir(void) {
	toucheclav = serial_get_last_char();
	uint8_t temps = 0;
	uint8_t missile_lance = 0;

	if (toucheclav == ' ') {
		missile_lance = 1;
	}
	if (temps <= 40 && missile_lance == 1) {
		temps++;

		if (ym != 2) {
			vt100_move(xm, ym);
			serial_putchar(' ');
			ym -= 1;
			vt100_move(xm, ym);
			serial_puts(missile);

			if (ym == 2) {
				vt100_move(xm, 2);
				serial_putchar(' ');
				ym = ORIGINE_MISSILE;
				xm = xv;
			}
		}
	}
}

int main(void) {
	serial_init(115200);
	vt100_clear_screen();
	contour_acceuil();
	menu_principal();
	lancer_jeu();
	vt100_clear_screen();
	contour_jeu();

	while (1) {
		deplacer_vaisseau();
		init_enemies();
		enemies();
		tir();

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Fin du programme

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size) {
	/* TODO, implement your code here */
	return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void) {
	/* TODO, implement your code here */
	return -1;
}

