#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>

void encontro();
void turnoJogador();
void calculoDanoMonstro();
void calculoDanoJogador();
int rng(int limite);
void atacar();
void defender();
void esquivar();
void fugir();
void turnoMonstro();
void atacarMonstro();
void defenderMonstro();
void esquivarMonstro();
void fugirMonstro();

int ataqueJogador = 50, defesaJogador = 50, vidaJogador = 100, vidaAtualJogador = 100;
int ataqueMonstro = 20, defesaMonstro = 30, vidaMonstro = 100, vidaAtualMonstro = 50, personalidade = 8;
int dano = 0, modificadorDanoJogador = 1, modificadorDanoMonstro = 1;
int esquivaJogador = 0, esquivaMonstro = 0;


int main()
{
	setlocale(LC_ALL, "");
	
	srand(time(NULL));
	
	printf("###############################\n");
	printf("#        JOGO DO MANGO        #\n");
	printf("###############################\n\n");
	
	system("pause");
	system("cls");

	encontro();

	return 0;
}


void encontro()
{
	printf("Você encontrou um monstro selvagem!\n\n");

	vidaAtualMonstro = vidaMonstro;

	system("pause");
	system("cls");

	turnoJogador();
}


void turnoJogador()
{
	int escolha;
	printf("O que deseja fazer agora?\n\n");
	printf("[1] Atacar\n");
	printf("[2] Defender\n");
	printf("[3] Esquivar\n");
	printf("[4] Fugir\n\n");
	scanf("%d", &escolha);

	switch(escolha)
	{
	case 1:
		atacar();
		break;

	case 2:
		defender();
		break;

	case 3:
		esquivar();
		break;

	case 4:
		fugir();
		break;

	default:
		printf("\nOpção inválida!\n\n");

		system("pause");
		system("cls");

		turnoJogador();
	}
}


void calculoDanoMonstro()
{
	dano = (sqrt((100 * ataqueJogador) / defesaMonstro)) / modificadorDanoMonstro;
}


void calculoDanoJogador()
{
	dano = (sqrt((100 * ataqueMonstro) / defesaJogador)) / modificadorDanoJogador;
}


int rng(int limite)
{
	return rand() % limite;
}


void atacar()
{
	int acao;

	printf("\nVocê atacou...\n\n");

	switch(esquivaMonstro)
	{
	case 1:
		acao = 255; // critico garantido
		break;

	case 2:
		acao = 0; // falha garantida
		break;

	default:
		acao = rng(255); // RNG
	}

	system("pause");
	system("cls");

	if(acao <= 3) // NAO HOUVE DANO
	{
		printf("...mas errou!\n\n");
		printf("Vida do monstro: %d/%d\n\n", vidaAtualMonstro, vidaMonstro);

		modificadorDanoMonstro = 1;
		esquivaMonstro = 0;

		system("pause");
		system("cls");

		turnoMonstro();
	}

	else // HOUVE ALGUM DANO, DEVE-SE CALCULA-LO
	{
		calculoDanoMonstro();

		if(acao < 239) // DANO NORMAL
		{
			if(dano >= vidaAtualMonstro) // DANO >= VIDA ATUAL
			{
				dano = vidaAtualMonstro;
				vidaAtualMonstro = 0;

				printf("... e causou %d de dano!\n\n", dano);
				printf("Vida do monstro: %d/%d\n", vidaAtualMonstro, vidaMonstro);
				printf("Você derrotou o monstro!!\n\n");

				modificadorDanoMonstro = 1;
				esquivaMonstro = 0;
			}

			else // DANO < VIDA ATUAL
			{
				vidaAtualMonstro -= dano;

				printf("... e causou %d de dano!\n\n", dano);
				printf("Vida do monstro: %d/%d\n\n", vidaAtualMonstro, vidaMonstro);

				modificadorDanoMonstro = 1;
				esquivaMonstro = 0;

				system("pause");
				system("cls");

				turnoMonstro();
			}
		}

		else // DANO CRÍTICO
		{
			if(dano >= vidaAtualMonstro) // DANO >= VIDA ATUAL
			{
				dano = vidaAtualMonstro;
				vidaAtualMonstro = 0;

				printf("... e causou %d de dano!\n\n", dano);
				printf("Dano crítico!\n\n");
				printf("Vida do monstro: %d/%d\n", vidaAtualMonstro, vidaMonstro);
				printf("Você derrotou o monstro!!\n\n");

				modificadorDanoMonstro = 1;
				esquivaMonstro = 0;
			}

			else // DANO < VIDA ATUAL
			{
				dano *= 2;
				vidaAtualMonstro -= dano;

				printf("... e causou %d de dano!\n\n", dano);
				printf("Dano crítico!\n\n");
				printf("Vida do monstro: %d/%d\n\n", vidaAtualMonstro, vidaMonstro);

				modificadorDanoMonstro = 1;
				esquivaMonstro = 0;

				system("pause");
				system("cls");

				turnoMonstro();
			}
		}
	}
}


void defender()
{
	int acao;

	printf("\nVocê tenta se defender do ataque do monstro! E...\n\n");

	acao = rng(99); // RNG

	system("pause");
	system("cls");

	if(acao <= 11) // 12% NAO CONSEGUE SE DEFENDER
	{
		printf("... não consegue!\n\n");

		modificadorDanoJogador = 1;

		system("pause");
		system("cls");

		turnoMonstro();
	}

	else // 88% CONSEGUE SE DEFENDER
	{
		printf("... consegue!\n\n");
		printf("O próximo dano recebido será reduzido pela metade!\n\n");

		modificadorDanoJogador = 2;

		system("pause");
		system("cls");

		turnoMonstro();
	}

}


void esquivar()
{
	int acao;

	printf("\nVocê tenta se esquivar do ataque do monstro! E...\n\n");

	acao = rng(99);

	system("pause");
	system("cls");

	if(acao <= 19) // 20% NAO CONSEGUE SE ESQUIVAR
	{
		printf("... acaba se atrapalhando!\n\n");
		printf("O próximo dano recebido será crítico!\n\n");

		esquivaJogador = 1;

		system("pause");
		system("cls");

		turnoMonstro();
	}

	else // 80% CONSEGUE SE ESQUIVAR
	{
		printf("... consegue!\n\n");
		printf("Você não receberá dano na próxima rodada!\n\n");

		esquivaJogador = 2;

		system("pause");
		system("cls");

		turnoMonstro();
	}

}


void fugir()
{
	int acao;

	printf("\nVocê tenta fugir do monstro! E...\n\n");

	acao = rng(99);

	system("pause");
	system("cls");

	if((ataqueJogador + defesaJogador) > (ataqueMonstro + defesaMonstro))
	{
		printf("...consegue!\n\n");
	}

	else
	{
		if(acao < 50)
		{
			printf("...não consegue!\n\n");

			turnoMonstro();
		}

		else
		{
			printf("...consegue!\n\n");
		}
	}
}


void turnoMonstro()
{
	int numRand;

	numRand = (rng(15)) + 1;

	printf("Turno do monstro!\n\n");
	printf("É a vez do monstro! Ele ...\n\n");

	if(numRand > personalidade) // chance = 100 - (personalidade/16)
	{
		atacarMonstro();
	}
	else // 1/16 fuga; 3/16 esquiva; 4/16 defesa.
	{
		numRand = (rng(15)) + 1;

		if(numRand == 1)
		{
			fugirMonstro();
		}

		else if(numRand > 1 && numRand < 5)
		{
			esquivarMonstro();
		}

		else if(numRand >= 5 && numRand < 9)
		{
			defenderMonstro();
		}

		else
		{
			system("pause");
			system("cls");

			printf("...só te observa, imóvel!\n\n");

			system("pause");
			system("cls");

			turnoJogador();
		}
	}
}


void atacarMonstro()
{
	int acao;

	switch(esquivaJogador)
	{
	case 1:
		acao = 255; // critico garantido
		break;

	case 2:
		acao = 0; // falha garantida
		break;

	default:
		acao = rng(255); // RNG
	}

	system("pause");
	system("cls");

	if(acao <= 3) // NAO HOUVE DANO
	{
		printf("... erra o ataque!\n\n");
		printf("Sua vida: %d/%d\n\n", vidaAtualJogador, vidaJogador);

		modificadorDanoJogador = 1;
		esquivaJogador = 0;

		system("pause");
		system("cls");

		printf("Seu turno!\n\n");

		system("pause");
		system("cls");

		turnoJogador();
	}

	else // HOUVE ALGUM DANO, DEVE-SE CALCULA-LO
	{
		calculoDanoJogador();

		if(acao < 239) // DANO NORMAL
		{
			if(dano >= vidaAtualJogador) // DANO >= VIDA ATUAL
			{
				dano = vidaAtualJogador;
				vidaAtualJogador = 0;

				printf("... te ataca, causando %d de dano!\n\n", dano);
				printf("Sua vida: %d/%d\n", vidaAtualJogador, vidaJogador);
				printf("Você morreu! Fim de jogo!\n\n");

				modificadorDanoJogador = 1;
				esquivaJogador = 0;
			}

			else // DANO < VIDA ATUAL
			{
				vidaAtualJogador -= dano;

				printf("... te ataca, causando %d de dano!\n\n", dano);
				printf("Sua vida: %d/%d\n\n", vidaAtualJogador, vidaJogador);

				modificadorDanoJogador = 1;
				esquivaJogador = 0;

				system("pause");
				system("cls");

				printf("Seu turno!\n\n");

				turnoJogador();
			}
		}

		else // DANO CRÍTICO
		{
			if(dano >= vidaJogador) // DANO >= VIDA ATUAL
			{
				dano = vidaAtualJogador;
				vidaAtualJogador = 0;

				printf("... te ataca, causando %d de dano!\n\n", dano);
				printf("Dano crítico!\n\n");
				printf("Sua vida: %d/%d\n", vidaAtualJogador, vidaJogador);
				printf("Você morreu! Fim de jogo!\n\n");

				modificadorDanoJogador = 1;
				esquivaJogador = 0;
			}

			else // DANO < VIDA ATUAL
			{
				dano *= 2;
				vidaAtualJogador -= dano;

				printf("... te ataca, causando %d de dano!\n\n", dano);
				printf("Dano crítico!\n\n");
				printf("Sua vida: %d/%d\n\n", vidaAtualJogador, vidaJogador);

				modificadorDanoJogador = 1;
				esquivaJogador = 0;

				system("pause");
				system("cls");

				printf("Seu turno!\n\n");

				turnoJogador();
			}
		}
	}
}

void defenderMonstro()
{
	system("pause");
	system("cls");

	printf("...se defende do seu ataque! E...\n\n");
	printf("O próximo dano causado será reduzido pela metade!\n\n");

	modificadorDanoMonstro = 2;

	system("pause");
	system("cls");

	turnoJogador();
}


void esquivarMonstro()
{
	int acao;

	system("pause");
	system("cls");

	printf("...tenta se esquivar do seu ataque! E...\n\n");

	acao = rng(99);

	system("pause");
	system("cls");

	if(acao <= 29) // 30% NAO CONSEGUE SE ESQUIVAR
	{
		printf("... acaba se atrapalhando!\n\n");
		printf("O próximo dano causado será crítico!\n\n");

		esquivaMonstro = 1;

		system("pause");
		system("cls");

		turnoJogador();
	}

	else // 70% CONSEGUE SE ESQUIVAR
	{
		printf("... consegue!\n\n");
		printf("Você não causará dano na próxima rodada!\n\n");

		esquivaMonstro = 2;

		system("pause");
		system("cls");

		turnoJogador();
	}
}


void fugirMonstro()
{
	int acao;

	system("pause");
	system("cls");

	printf("...tenta fugir de você! E...\n\n");

	acao = rng(99);

	system("pause");
	system("cls");

	if(acao < 50)
	{
		printf("...não consegue!\n\n");

		turnoJogador();
	}

	else
	{
		printf("...consegue!\n\n");
	}
}
