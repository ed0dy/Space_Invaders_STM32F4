/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "serial.h"
#include "vt100.h"

#define LONG_FENETRE (80)
#define LARG_FENETRE (24)
#define ORIGINE_MISSILE (21)

const char ship[] = "^";
const char bot[] = "Y";

typedef struct {

	uint8_t x;
	uint8_t y;
	uint8_t points;
	uint8_t toucher;

} alien;

alien t_alien[20] = {0};

uint8_t toucheclav;
uint8_t depbot = 0;

uint8_t xv = 35;
uint8_t yv = 22;

uint8_t ibot = 0;
uint8_t jbot = 0;

uint8_t xm = 35;
uint8_t ym = 22;


uint8_t missile_lance = 0;

void menu_principal(void) {
	vt100_move(3, 2);
	serial_puts("                                        d8b                             888");
	vt100_move(3, 3);
	serial_puts("                                        Y8P                             888");
	vt100_move(3, 4);
	serial_puts("                                                                        888");
	vt100_move(3, 5);
	serial_puts(".d8888b 88888b.  8888b.  .d8888b .d88b. 88888888b. 888  888 8888b.  .d88888");
	vt100_move(3, 6);
	serial_puts("88K     888 Y88b    Y88bd88PY   d8P  Y8b888888 Y88b888  888    Y88bd88Y 888");
	vt100_move(3, 7);
	serial_puts("dY8888b.888  888.d888888888     88888888888888  888Y88  88P.d888888888  888");
	vt100_move(3, 8);
	serial_puts("     X88888 d88P888  888Y88b.   Y8b.    888888  888 Y8bd8P 888  888Y88b 888");
	vt100_move(3, 9);
	serial_puts(" 88888P'88888PY dY888888 dY8888P bY8888 888888  888  Y88P  dY888888 dY88888");
	vt100_move(3, 10);
	serial_puts("        888                                                                ");
	vt100_move(3, 11);
	serial_puts("        888                                                                ");
	vt100_move(3, 12);
	serial_puts("        888                                                                ");

	vt100_move(25, 15);
	serial_puts("APPUYER SUR 'ESPACE' POUR JOUER");
	vt100_move(29, 17);
	serial_puts("GAUCHE : Q | D : DROITE");
}

void lancer_jeu(void) {
	signed char touche = -1;
	while (touche == -1) {
		touche = serial_get_last_char();
	}
}

void contour(void) {
	int dem = 0;

	for (dem = 1; dem <= LONG_FENETRE; dem++) {
		vt100_move(dem, 1);
		serial_puts("#");
	}

	dem = 0;

	for (dem = 1; dem <= LARG_FENETRE; dem++) {
		vt100_move(1, dem);
		serial_puts("#");
	}

	dem = 0;

	for (dem = 1; dem <= LARG_FENETRE; dem++) {
		vt100_move(LONG_FENETRE, dem);
		serial_puts("#");
	}

	dem = 0;

	for (dem = 1; dem <= LONG_FENETRE; dem++) {
		vt100_move(dem, LARG_FENETRE);
		serial_puts("#");
	}
}

void contour2(void) {
	int dem = 0;

	for (dem = 1; dem <= LONG_FENETRE; dem++) {
		vt100_move(dem, 1);
		serial_puts("#");
	}

	dem = 0;

	for (dem = 1; dem <= LARG_FENETRE; dem++) {
		vt100_move(1, dem);
		serial_puts("#");
	}

	dem = 0;

	for (dem = 1; dem <= LARG_FENETRE; dem++) {
		vt100_move(LONG_FENETRE, dem);
		serial_puts("#");
	}

	dem = 0;

	for (dem = 1; dem <= LONG_FENETRE; dem++) {
		vt100_move(dem, LARG_FENETRE);
		serial_puts("#");

	}

	vt100_move(4, 23);
	serial_puts("SCORE : 0");

	vt100_move(70, 23);
	serial_puts("VIES : 1");

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

void enemies(void) {

	for (depbot = 2; depbot <= 40; depbot +=3) {

		t_alien[depbot].x = depbot;
		vt100_move(t_alien[depbot].x, 3);
		serial_puts(bot);
	}
}

void tir(void) {
	uint8_t toucheclav = serial_get_last_char();
	uint8_t temps = 0;

	if (toucheclav == ' '){
		missile_lance = 1;
	}
	if (temps <= 40 && missile_lance == 1) {
		temps++;

		if (ym != 2) {
			vt100_move(xm, ym);
			serial_putchar(' ');
			ym -= 1;
			vt100_move(xm, ym);
			serial_putchar('|');

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
	contour();
	menu_principal();
	lancer_jeu();
	vt100_clear_screen();
	contour2();

	while (1) {
		enemies();
		tir();
		deplacer_vaisseau();

	}
}

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

