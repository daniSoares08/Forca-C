#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"


char palavrasecreta[TAM_PALAVRA];
char chutes[26];
int chutesdados = 0;


int chuteserrados(){
    int erros = 0;

	for(int i = 0; i < chutesdados; i++) {
		
		int existe = 0;

		for(int j = 0; j < strlen(palavrasecreta); j++) {
			if(chutes[i] == palavrasecreta[j]) {
				existe = 1;
				break;
			}
		}

		if(!existe) erros++;
	}
    return erros;
}

int enforcou() {
	return chuteserrados() >= 5;
}

int ganhou() {
	for(int i = 0; i < strlen(palavrasecreta); i++) {
		if(!jachutou(palavrasecreta[i])) {
			return 0;
		}
	}

	return 1;
}

void abertura() {
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

void adicionarpal(){
    char add;
    printf("Voce deseja adicionar uma palavra ao dicionario? (S/N): ");
    scanf(" %c", &add);

    if(add == 'S'){
        printf("Digite a palavra a ser adicionada: ");
        char novapal[20];
        scanf(" %s", &novapal);

        FILE* f;
        f = fopen("palavras.txt", "r+");
        
        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapal);

        fclose(f);
    }

}

void chuta() {
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
}

int jachutou(char letra) {
    int achou = 0;
    for(int j = 0; j < chutesdados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaforca() {

    int erros = chuteserrados();

    printf("Voce ja deu %d chutes\n", chutesdados);
    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %c%c%c \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c \n", (erros >= 2 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 2 ? '/' : ' '));
    printf(" |       %c    \n", (erros >= 3 ? '|' : ' '));
    printf(" |      %c %c  \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    printf(" |             \n");
    printf("|__          \n");
    printf("\n\n");

    for(int i = 0; i < strlen(palavrasecreta); i++) {

        if(jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }

    }
    printf("\n");

}

void escolhepalavra() {
    FILE* f;

    f = fopen("palavras.txt", "r+");
    if(f == 0) {
        printf("Banco de dados de palavras nao disponivel\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavrasecreta);
    }
    

    fclose(f);
}


int main() {

    int acertou = 0;

    abertura();
    adicionarpal();
    escolhepalavra();

    do {

        desenhaforca();
        chuta();

        chutesdados++;

    } while (!ganhou() && !enforcou());

    if (ganhou()){
        printf("Parabens, voce GANHOU!!!");
    } else {
        printf(" Voce perdeu! Mais sorte na proxima vez.. :(");
    }
}