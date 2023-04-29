#include <conio.h>
#include <ctype.h>
#include <iostream>
#include <iomanip>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <windows.h>
#define color SetConsoleTextAttribute
//Investigamos sobre los códigos de escape ANSI, que otorgan formato a las salidas de terminales de texto, debido a ello los implementamos.
//Inician con \x1b[, un número arbitrario de enteros, separados por punto y coma, posteriormente una m.
#define RED      "\x1b[31m"
#define YELLOW   "\x1B[33m"
#define CYAN     "\x1b[36m"
#define WHITE    "\x1B[37m"
#define GRAY     "\x1B[38;2;176;174;174m"
#define RESET    "\x1B[0m"
#define BG_CREAM "\x1B[48;5;221m"
using namespace std;
int matriz[7][7];
char color_elegido1[5], color_elegido2[5];
string* nickname1 = new string, * nickname2 = new string;
int raya_repetido[7][2];
int raya_repetido_S[2][2];
int raya_repetidoD[7][2];
int raya_repetido_C[2][2];
int final_fase = -1;
int fichas_jugador_1 = 0;
int fichas_jugador_2 = 0;
void logo() {

	int* ca = new int;
	*ca = 219;
	char* c = new char;
	*c = *ca;
	cout << endl;
	cout << "         " << YELLOW << *c << " " << *c << "   " << *c << RESET << endl;
	cout << "     " << YELLOW << *c << "  " << *c << *c << " " << *c << "  " << *c << " " << *c << RESET << endl;
	cout << "     " << YELLOW << *c << *c << " " << *c << " " << *c << *c << " " << *c << " " << *c << *c << *c << RESET << "        " << RED << *c << "       " << *c << "        " << *c << RESET << endl;
	cout << "       " << YELLOW << *c << " " << *c << *c << " " << *c << *c << " " << *c << RESET << "        " << RED << *c << *c << "      " << *c << *c << "          " << *c << *c << RESET << endl;
	cout << "       " << YELLOW << *c << " " << *c << " " << *c << *c << " " << *c << *c << RESET << "       " << RED << *c << *c << "       " << *c << *c << *c << "          " << *c << *c << RESET << endl;
	cout << "       " << YELLOW << *c << "      " << *c << *c << RESET << "      " << RED << *c << *c << "         " << *c << *c << *c << "          " << *c << *c << RESET << endl;
	cout << "       " << YELLOW << *c << RESET << " " << GRAY << *c << *c << *c << *c << *c << RESET << " " << YELLOW << *c << RESET << "      " << RED << *c << *c << "          " << *c << *c << *c << "         " << *c << *c << RESET << endl;
	cout << "        " << GRAY << *c << RESET << YELLOW << *c << RESET << GRAY << *c << *c << *c << RESET << YELLOW << *c << RESET << GRAY << *c << RESET << "      " << RED << *c << *c << *c << "         " << *c << *c << *c << *c << "         " << *c << *c << *c << RESET << endl;
	cout << "     " << YELLOW << *c << RESET << "  " << GRAY << *c << RESET << YELLOW << *c << *c << RESET << GRAY << *c << RESET << YELLOW << *c << *c << RESET << GRAY << *c << RESET << "  " << YELLOW << *c << RESET << "     " << RED << *c << *c << "       " << *c << *c << *c << "          " << *c << *c << RESET << endl;
	cout << "     " << YELLOW << *c << *c << RESET << " " << GRAY << *c << *c << *c << GRAY << *c << *c << *c << *c << RESET << " " << YELLOW << *c << *c << RESET << "     " << RED << *c << *c << *c << "       " << *c << *c << "         " << *c << *c << *c << RESET << endl;
	cout << "      " << YELLOW << *c << *c << *c << RESET << GRAY << *c << RESET << YELLOW << *c << *c << *c << RESET << GRAY << *c << RESET << YELLOW << *c << *c << *c << RESET << "        " << RED << *c << *c << *c << "      " << *c << "       " << *c << *c << *c << RESET << endl;
	cout << "       " << YELLOW << *c << *c << *c << *c << *c << *c << *c << *c << *c << RESET << "            " << RED << *c << *c << *c << *c << *c << *c << *c << *c << *c << *c << *c << *c << *c << *c << RESET << endl;
	cout << "        " << YELLOW << *c << *c << *c << *c << *c << *c << *c << RESET << endl;
	cout << "         " << YELLOW << *c << *c << *c << *c << *c << RESET << endl;
	delete c, ca;
	c = NULL, ca = NULL;
}
void reglas() {

	system("Cls");
	cout << "......................................." << endl;
	cout << "...... ¿En qué consiste el juego? ....." << endl;
	cout << "......................................." << endl;

	cout << " Cada jugador dispone de nueve piezas." << endl;
	cout << " El objetivo es de intentar de que el" << endl;
	cout << " oponente se quede sin piezas o menos" << endl;
	cout << " de tres o también dejarlo sin" << endl;
	cout << " posibilidad de movimientos." << endl;
	cout << endl;
}

void creadores() {

	system("Cls");
	cout << " Creadores: " << endl << endl;
	cout << "- La Torre Soto, André Sebastian (U202217772)." << endl;
	cout << "- Chávez Antón, Manuel Stephano (U202216567)." << endl;
	cout << "- Cóndor Velásquez, Angela Bibiana (U202217165)." << endl;
	cout << endl;
}
void tablero() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "  ";
	//Marco superior de coordenadas
	for (int i = 0; i < 7; i++) {
		cout << WHITE << i << RESET << "   ";
	}
	cout << endl;
	//Marco lateral de coordenadas
	for (int i = 0; i < 7; i++) {
		cout << WHITE << i << RESET << "";
		for (int j = 0; j < 7; j++) {

			//Cuadrado exterior
			if (i == 0 && j == 0 || i == 3 && j == 0 || i == 6 && j == 0 || i == 0 && j == 3 || i == 0 && j == 6 || i == 6 && j == 3 ||
				i == 6 && j == 6 || i == 3 && j == 6 ||
				//Cuadrado del medio
				i == 1 && j == 1 || i == 3 && j == 1 || i == 5 && j == 1 || i == 1 && j == 3 || i == 1 && j == 5 || i == 3 && j == 5 ||
				i == 5 && j == 5 || i == 5 && j == 3 ||
				//Cuadrado pequeño
				i == 2 && j == 2 || i == 2 && j == 3 || i == 2 && j == 4 || i == 3 && j == 4 || i == 4 && j == 4 || i == 4 && j == 3 ||
				i == 4 && j == 2 || i == 3 && j == 2) {
				//Espacios donde van las fichas
				if (matriz[i][j] == 0) {
					cout << CYAN << BG_CREAM << "[ ]" << " " << RESET;
				}
				//Fichas
				else {
					if (matriz[i][j] == 1) {
						color(hConsole, color_elegido1[0]);
						cout << BG_CREAM << "[O]" << " " << RESET;
						color(hConsole, 7);
					}
					else if (matriz[i][j] == 2) {
						color(hConsole, color_elegido2[0]);
						cout << BG_CREAM << "[O]" << " " << RESET;
						color(hConsole, 7);
					}
				}
			}

			//Espacios vacíos
			else {

				matriz[i][j] = 3;
				matriz[3][3] = 0;

				if (matriz[i][j] == 3) {
					if (i == 0 || i == 6 || (i == 1 && j == 2 || j == 4) || (i == 5 && j == 2 || j == 4)) {
						cout << CYAN << BG_CREAM << "--- " << RESET;
					}
					else {
						cout << CYAN << BG_CREAM << " |" << "  " << RESET;
					}
				}
				if (matriz[i][j] == 0) {
					cout << CYAN << BG_CREAM << "    " << RESET;
				}
			}

		}
		cout << endl;
	}

}
void validar_numerico(char matriz[]) {

	do {
		cin >> matriz;

	} while (!(isdigit(matriz[0])));
	matriz[0] = atoi(matriz);
}
void colocarficha(int n) {

	char row[2], col[2];
	bool flag = false;

	while (!flag) {
		do {
			cout << "Digite la coordenada X(0-6): ";
			validar_numerico(row);
			cout << "Digite la coordenada Y(0-6): ";
			validar_numerico(col);

			//Para que no seleccione el espacio vacío del centro
		} while (row[0] == 3 && col[0] == 3);
		if (row[0] < 7 and col[0] < 7) {
			if (matriz[row[0]][col[0]] == 0) {
				matriz[row[0]][col[0]] = n;
				flag = true;
			}

		}

	}

	system("Cls");
	tablero();
}

void eliminar_ficha(int n, int t) {

	int contador_linea = 0, row, col, contador_columnas = 0;
	bool si = true, flag = false;

	//Para las filas
	for (int i = 0; i < 7; i++) {
		contador_linea = 0;
		int contador_linea_S = 0, contador_linea_D = 0;
		for (int j = 0; j < 7; j++) {

			//Condicionales para saber si hay 3 fichas en una fila

			if (matriz[3][0] == n && matriz[3][1] == n && matriz[3][2] == n) {
				contador_linea_S = 3;
			}
			if (matriz[3][4] == n && matriz[3][5] == n && matriz[3][6] == n) {

				contador_linea_D = 3;
			}

			if (i != 3 && matriz[i][j] == n) {

				contador_linea++;

			}

			//Si es que hay 3 o mas fichas en una fila y esta no es repetida se quitara una ficha
			if ((contador_linea == 3 && raya_repetido[i][n - 1] == 0) || (contador_linea_S == 3 && raya_repetido_S[0][n - 1] == 0) ||
				(contador_linea_D == 3 && raya_repetido_S[1][n - 1] == 0)) {

				while (!flag) {

					cout << "Digite las coordenadas de la ficha que quiere quitar: " << endl;
					cout << "Coordenada X(0-6): ";
					cin >> row;
					cout << "Coordenada Y(0-6): ";
					cin >> col;

					if (row < 7 and col < 7) {
						if (matriz[row][col] == t) {
							matriz[row][col] = 0;
							flag = true;

							if (contador_linea_S == 3) {
								raya_repetido_S[0][n - 1] = 1;
							}
							if (contador_linea_D == 3) {

								raya_repetido_S[1][n - 1] = 1;
							}

							if (contador_linea == 3) {
								raya_repetido[i][n - 1] = 1;
							}
						}
					}
				}
			}
		}

		//Si es que hay menos de 3 fichas en una fila esta es accesible de nuevo
		if (contador_linea < 3) {
			raya_repetido[i][n - 1] = 0;

		}
		if ((contador_linea_S != 3)) {
			raya_repetido_S[0][n - 1] = 0;
		}
		if ((contador_linea_D != 3)) {
			raya_repetido_S[1][n - 1] = 0;
		}
	}

	//Columnas
	for (int i = 0; i < 7; i++) {
		contador_columnas = 0;
		int contador_columnas_S = 0, contador_columnas_D = 0;
		for (int j = 0; j < 7; j++) {

			//Condicionales para saber si hay 3 fichas en una columna
			if (matriz[0][3] == n && matriz[1][3] == n && matriz[2][3] == n) {
				contador_columnas_S = 3;
			}
			if (matriz[4][3] == n && matriz[5][3] == n && matriz[6][3] == n) {

				contador_columnas_D = 3;
			}

			if (i != 3 && matriz[j][i] == n) {

				contador_columnas++;

			}

			//Si es que hay 3 o mas fichas en una columna y esta no es repetida se quitara una ficha
			if ((contador_columnas == 3 && raya_repetidoD[i][n - 1] == 0) || (contador_columnas_S == 3 && raya_repetido_C[0][n - 1] == 0) ||
				(contador_columnas_D == 3 && raya_repetido_C[1][n - 1] == 0)) {

				while (!flag) {
					cout << endl;
					cout << "Digite las coordenadas de la ficha que quiere quitar: " << endl;
					cout << "Coordenada X(0-6): ";
					cin >> row;
					cout << "Coordenada Y(0-6): ";
					cin >> col;

					if (row < 7 and col < 7) {
						if (matriz[row][col] == t) {
							matriz[row][col] = 0;
							flag = true;

							if (contador_columnas_S == 3) {
								raya_repetido_C[0][n - 1] = 1;
							}
							if (contador_columnas_D == 3) {

								raya_repetido_C[1][n - 1] = 1;
							}

							if (contador_columnas == 3) {
								raya_repetidoD[i][n - 1] = 1;
							}


						}

					}
				}
			}
		}
		//Si es que hay menos de 3 fichas en una columna esta es accesible de nuevo
		if (contador_columnas < 3) {
			raya_repetidoD[i][n - 1] = 0;

		}
		if ((contador_columnas_S != 3)) {
			raya_repetido_C[0][n - 1] = 0;
		}
		if ((contador_columnas_D != 3)) {
			raya_repetido_C[1][n - 1] = 0;
		}
	}
	system("Cls");
	tablero();
}

void mover_ficha(int n) {

	int row, col, row1, col2;
	bool si = true, flag = false;
	while (!flag) {
		do {
			cout << "Digite las coordenadas de la ficha que quiere mover: " << endl;
			cout << "Coordenada X(0-6): ";
			cin >> row;
			cout << "Coordenada Y(0-6): ";
			cin >> col;
			//Revisar si las fichas adyacentes están disponibles
		} while ((matriz[row + (3 - row)][col] != 0 && matriz[row][col + (3 - col)] != 0));
		if (row < 7 and col < 7) {
			if (matriz[row][col] == n) {
				matriz[row][col] = 0;
				flag = true;
			}

		}
	}

	while (si) {
		do {
			cout << "Digite la coordenada X a la cual quiere mover la ficha: ";
			cin >> row1;
			cout << "Digite la coordenada Y a la cual quiere mover la ficha: ";
			cin >> col2;
			//Revisar que este colocando la  ficha en una posicion adyacente en la linea 3 y en la columna 3
		} while ((row1 == 3 and (col2 > col + 1 || col2 < col - 1)) || col2 == 3 and (row1 > row + 1 || row1 < row - 1));
		if (row1 < 7 and col2 < 7) {
			//Si el espacio esta vacio
			if (matriz[row1][col2] == 0) {
				//que no sea la misma posicion
				if (row1 == row && col2 == col) {
					continue;
				}
				//Que se encuentre en la misma fila y columna
				else if (((row1 >= row || row1 <= row) && col2 == col) || (col2 >= col || col2 <= col) && row1 == row) {

					switch (row1 || col2)
					{

						//Restringir cuadrado grande
					case 0:
					case 6: {
						if ((row1 != (row + 6)) && (col2 != (col + 6))) {
							if ((row1 != (row - 6)) && (col2 != (col - 6))) {
								matriz[row1][col2] = n;
								si = false;
							}
						}
						break;
					}
						  //Restringir cuadrado mediano
					case 1:
					case 5: {
						if ((row1 != (row + 4)) && (col2 != (col + 4))) {
							if ((row1 != (row - 4)) && (col2 != (col - 4))) {
								matriz[row1][col2] = n;
								si = false;
							}
						}
						break;
					}
						  //Restringir cuadrado pequeño
					case 2:
					case 4: {
						if ((row1 != (row + 2)) && (col2 != (col + 2))) {
							if ((row1 != (row - 2)) && (col2 != (col - 2))) {
								matriz[row1][col2] = n;
								si = false;


							}
						}
						break;
					}
					}
				}

			}
		}
	}
	system("Cls");
	tablero();
}

void fase_vuelo(int n) {

	int row, col;
	int row1, col2;
	bool si = true;
	bool flag = false;
	while (!flag) {
		cout << "Digite las coordenadas de la ficha quiere mover: " << endl;
		cout << "Coordenada X(0-6): ";
		cin >> row;
		cout << "Coordenada Y(0-6): ";
		cin >> col;
		if (row < 7 and col < 7) {
			if (matriz[row][col] == n) {
				matriz[row][col] = 0;
				flag = true;
			}
		}
	}
	while (si) {
		do {
			cout << "Digite la coordenada X a la cual quiere mover la ficha: ";
			cin >> row1;
			cout << "Digite la coordenada Y a la cual quiere mover la ficha: ";
			cin >> col2;
		} while (row == 3 && col == 3);
		if (row1 < 7 and col2 < 7) {
			//Si el espacio esta vacio
			if (matriz[row1][col2] == 0) {
				//que no sea la misma posicion
				if (row1 == row && col2 == col) {
					continue;
				}
				//que este en la misma fila y columna
				else if (((row1 >= row || row1 <= row) && col2 == col) || (col2 >= col || col2 <= col) && row1 == row) {
					matriz[row1][col2] = n;
					si = false;
				}
			}
		}
	}
	system("Cls");
	tablero();
}

void contar_fichas();

int main() {

	bool valor = true;
	int* spd = new int;
	*spd = 6;
	char* s = new char;
	*s = *spd;
	struct Morris
	{
		//Char opcion[1];
		int opcion = 0, t = 0, contador = 9, moneda = 0;
	}Morris;
	logo();
	setlocale(LC_ALL, "Spanish");

	srand(time(NULL));

	//Rellenando las matrices globales
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {

			matriz[i][j] = 0;
		}
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 2; j++) {
			raya_repetido[i][j] = 0;
		}
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 2; j++) {
			raya_repetidoD[i][j] = 0;
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			raya_repetido_S[i][j] = 0;
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			raya_repetido_C[i][j] = 0;
		}
	}
	cout << "\n\n......................................." << endl;
	cout << "... Bienvenidos a NINE MEN'S MORRIS ..." << endl;
	cout << "......................................." << endl << endl;
	do {
		cout << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << endl;
		cout << *s << " Digite la accion que desea realizar " << *s << endl;
		cout << *s << " 1. Ver las reglas                   " << *s << endl;
		cout << *s << " 2. Ver a los creadores del programa " << *s << endl;
		cout << *s << " 3. Ir al juego                      " << *s << endl;
		cout << *s << " 4. Salir                            " << *s << endl;
		cout << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << *s << endl;
		cin >> Morris.opcion;

		switch (Morris.opcion) {
		case 1:
			reglas();
			break;
		case 2:

			creadores();
			break;
		case 3:
			system("Cls");
			cout << "............................." << endl;
			cout << ".... ¿Listos para jugar? ...." << endl;
			cout << "............................." << endl << endl;


			cout << "Digite su nickname jugador 1: " << endl;
			cin >> *nickname1;

			cout << "Digite de que color quiere que sean sus fichas (1 = Azul;  2 = Verde;" << endl;
			cout << "3 = Aguamarina; 4 = Rojo; 5 = Púrpura; 6 = Amarillo; 7 = Blanco; " << endl;
			cout << "8 = Gris; 9 = Azul Claro): ";
			validar_numerico(color_elegido1);
			cout << "\n-----------------------------------\n";
			cout << "Digite su nickname jugador 2: " << endl;
			cin >> *nickname2;
			cout << "Digite de que color quiere que sean sus fichas (1 = Azul;  2 = Verde;" << endl;
			cout << "3 = Aguamarina; 4 = Rojo; 5 = Púrpura; 6 = Amarillo; 7 = Blanco; " << endl;
			cout << "8 = Gris; 9 = Azul Claro): ";
			validar_numerico(color_elegido2);

			cout << "Es hora de ver que jugador empieza primero!!!" << endl;
			Morris.moneda = 1 + rand() % (3 - 1);
			if (Morris.moneda == 1) {
				cout << "El jugador 1 comenzará el juego" << endl;
			}
			else {
				cout << "El jugador 2 comenzará el juego" << endl;
			}
			system("Pause");
			system("Cls");

			//Primera fase---Colocar las fichas
			while (Morris.t < 9) {
				system("Cls");
				tablero();
				if (Morris.moneda == 1) {
					cout << endl;
					cout << "Fichas jugador 1: " << Morris.contador << endl;
					cout << "Turno de: " << *nickname1 << endl;
					colocarficha(1);
					eliminar_ficha(1, 2);
					cout << endl;
					cout << "Fichas jugador 2: " << Morris.contador << endl;
					cout << "Turno de: " << *nickname2 << endl;
					colocarficha(2);
					eliminar_ficha(2, 1);
				}
				else {
					cout << endl;
					cout << "Fichas jugador 2: " << Morris.contador << endl;
					cout << "Turno de: " << *nickname2 << endl;
					colocarficha(2);
					eliminar_ficha(2, 1);
					cout << endl;
					cout << "Fichas jugador 1: " << Morris.contador << endl;
					cout << "Turno de: " << *nickname1 << endl;
					colocarficha(1);
					eliminar_ficha(1, 2);

				}


				Morris.t++;
				Morris.contador--;
			}

			//Segunda fase---Mover las fichas
			while (final_fase == -1) {
				if (Morris.moneda == 1) {
					cout << endl;
					cout << "Turno de: " << *nickname1 << endl;
					mover_ficha(1);
					eliminar_ficha(1, 2);
					cout << endl;
					cout << "Turno de: " << *nickname2 << endl;
					mover_ficha(2);
					eliminar_ficha(2, 1);
					contar_fichas();

				}
				else {
					cout << endl;
					cout << "Turno de: " << *nickname2 << endl;
					mover_ficha(2);
					eliminar_ficha(2, 1);
					cout << endl;
					cout << "Turno de: " << *nickname1 << endl;
					mover_ficha(1);
					eliminar_ficha(1, 2);
					contar_fichas();
				}

			}
			system("Cls");
			cout << "Comienza la fase de vuelo" << endl;
			system("Pause");

			//Tercera fase---"Vuelo"
			while (true) {
				system("Cls");
				tablero();
				if (fichas_jugador_1 == 3) {
					cout << endl;
					cout << "Turno de: " << nickname1 << endl;
					fase_vuelo(1);
					eliminar_ficha(1, 2);
				}
				else {
					cout << endl;
					cout << "Turno de: " << nickname1 << endl;
					mover_ficha(1);
					eliminar_ficha(1, 2);
				}
				if (fichas_jugador_2 == 3) {
					cout << endl;
					cout << "Turno de: " << nickname2 << endl;
					fase_vuelo(2);
					eliminar_ficha(2, 1);
				}
				else {
					cout << endl;
					cout << "Turno de: " << nickname2 << endl;
					mover_ficha(2);
					eliminar_ficha(2, 1);
				}
				contar_fichas();
			}
			break;
		case 4:
			exit(0);
			break;
		default:
			cout << "UPS se equivocó al marcar, inténtelo de nuevo" << endl;
			break;

		}
	} while (true);

	return 0;
	delete spd, s, nickname1, nickname2;
	spd = NULL, s = NULL, nickname1 = NULL, nickname2 = NULL;
}
void contar_fichas() {
	fichas_jugador_1 = 0;
	fichas_jugador_2 = 0;
	int k = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {

			if (matriz[i][j] == 1) {
				fichas_jugador_1++;

			}
			if (matriz[i][j] == 2) {
				fichas_jugador_2++;

			}
		}
	}

	if (fichas_jugador_1 == 3) {
		final_fase = 1;
	}
	if (fichas_jugador_2 == 3) {
		final_fase = 1;
	}

	if (fichas_jugador_1 < 3) {
		cout << "FELICIDADES " << *nickname2 << ", ERES EL GANADOR." << endl;
		cout << "Digite 1 para reiniciar el programa o digite cualquier otro número para salir del juego." << endl;
		cin >> k;
		if (k == 1) {

			main();
		}
		else {
			exit(0);
		}
	}
	if (fichas_jugador_2 < 3) {
		cout << "FELICIDADES " << *nickname1 << ", ERES EL GANADOR." << endl;
		cout << "Digite 1 para reiniciar el programa o digite cualquier otro número para salir del juego." << endl;
		cin >> k;
		if (k == 1) {

			main();
		}
		else {
			exit(0);
		}
	}
}
