#include <locale.h>
#include <stdio.h>
#include <string.h>
#define qtd_clientes 200
#define qtd_escalas 5
#define qtd_voos 5
#define qtd_passagens 160

void cadastra_cliente(char nome_clientes[][50], char CPF[][12], int contador_cliente);
void cadastra_escala(int codigo_escala[], char cidades_escalas[][50], int contador_escala);
int cadastra_voo(int codigo_voo[], int qtd_filas[], char cidade_origem[][50], char cidade_destino[][50], char tipo_voo[], float valor_passagem[], int codigo_escala[], char cidades_escalas[][50], int escala_do_voo[], int contador_voos);
int exibe_escalas(int codigo_escala[], char cidades_escalas[][50]);
int compra_passagem(char nome_clientes[][50], char CPF[][12], int codigo_voo[], char cidade_origem[][50], char cidade_destino[][50], int qtd_filas[], float valor_passagem[], char tipo_voo[], int codigo_escala[], char cidades_escalas[][50],int escala_do_voo[], char poltronas[qtd_voos][40][4], int contador[qtd_clientes][qtd_voos],int assentos_livres[qtd_voos], char passagens[qtd_voos][40][4][12], int contador_passagens);
int transforma_letra_do_assento(char aux);
int procura_cpf(char cpfdigitado[], char CPF[][12]);
int procura_codigo_voo(int codigo_voo_digitado, int codigo_voo[]);
int retorna_posicao_escala(int codigo_escala[qtd_escalas], int escala_escolhida);
void mapa_de_filas(char poltronas[qtd_voos][40][4], int qtd_filas[], int retorno_posicao_voo, int assentos_livres[]);
void exibir_det_voo(int codigo_voo[qtd_voos],char poltronas[qtd_voos][40][4], int qtd_filas[qtd_voos],char cidade_origem[qtd_voos][50], char cidade_destino[qtd_voos][50], char tipo_voo[qtd_voos], float valor_passagem[qtd_voos], char cidades_escalas[][50], int escala_do_voo[], int assentos_livres[]);
int compara_voo(int codigo_voo[],int codigo_digitado);
void exibir_cliente_passagens(char CPF[qtd_clientes][12], char nome_clientes[qtd_clientes][50], int codigo_voo[qtd_voos], char cidade_origem[qtd_voos][50], char cidade_destino[qtd_voos][50], int qtd_filas[qtd_voos], char passagens[qtd_voos][40][4][12]);
char transforma_numero_do_assento(int aux);


int main(void)
{
    setlocale(LC_ALL,"Portuguese");
    int menu, codigo_voo[qtd_voos], codigo_escala[qtd_escalas]={0}, qtd_filas[qtd_voos]={0}, escala_do_voo[qtd_voos], contador[qtd_clientes][qtd_voos]={0}, assentos_livres[qtd_voos]={0};
    int contador_cliente=0, contador_escala=0, contador_voos=0, contador_passagens=0, c=0, d=0;
    char nome_clientes[qtd_clientes][50], CPF[qtd_clientes][12], cidades_escalas[qtd_escalas][50], cidade_origem[qtd_voos][50], cidade_destino[qtd_voos][50], tipo_voo[qtd_voos], poltronas[qtd_voos][40][4]={' '}, cpfdigitado[12], passagens[qtd_voos][40][4][12];
    float valor_passagem[qtd_voos];

    do {
        printf("---------------------------------------------------\n");
        printf("\n                       MENU                       |\n");
        printf("1- Cadastrar cliente                              |\n");
        printf("2- Cadastrar Escala                               |\n");
        printf("3- Cadastrar Vôo                                  |\n");
        printf("4- Comprar passagem aérea                         |\n");
        printf("5- Exibir determinado voo                         |\n");
        printf("6- Exibir cliente e suas passagens                |\n");
        printf("7- Sair                                           |\n");
        printf("---------------------------------------------------\n");

        printf("\nDigite a opção: ");
        scanf("%d", &menu);
        printf("\nOpção escolhida: %d\n", menu);
        switch(menu)
        {
            case 1:
                cadastra_cliente(nome_clientes, CPF, contador_cliente);
                contador_cliente++;
                break;
            case 2:
                cadastra_escala(codigo_escala, cidades_escalas, contador_escala);
                contador_escala++;
                break;
            case 3:
                c = cadastra_voo(codigo_voo, qtd_filas, cidade_origem, cidade_destino, tipo_voo, valor_passagem, codigo_escala, cidades_escalas, escala_do_voo, contador_voos);
                contador_voos = c; //c é uma variável auxiliar que serve somente pra receber o contador de voos que a função retorna.
                break;
            case 4:
                d = compra_passagem(nome_clientes, CPF, codigo_voo, cidade_origem, cidade_destino, qtd_filas, valor_passagem, tipo_voo, codigo_escala, cidades_escalas, escala_do_voo, poltronas, contador, assentos_livres, passagens, contador_passagens);
                contador_passagens = d;
                break;
            case 5:
                exibir_det_voo(codigo_voo, poltronas, qtd_filas, cidade_origem, cidade_destino, tipo_voo, valor_passagem, cidades_escalas, escala_do_voo, assentos_livres);
                break;
            case 6:
                  exibir_cliente_passagens(CPF, nome_clientes, codigo_voo,  cidade_origem, cidade_destino, qtd_filas, passagens);
          default:
                break;
        }
    }while(menu < 7);
  return 0;
}

void cadastra_cliente(char nome_clientes[qtd_clientes][50], char cpf[qtd_clientes][12], int contador_cliente)
{
    printf("---------------------------------------------------\n");
    printf("\n                   CADASTRO DE CLIENTES          \n");
    if(contador_cliente < qtd_clientes)
    {   int retorno;
        char cpfdigitado[12];
        printf("\nDigite o nome do cliente %d: ", contador_cliente + 1);
        scanf("\n%[^\n]s", nome_clientes[contador_cliente]);
        do
          {   printf("\nDigite o CPF do cliente %d (somente números): ", contador_cliente + 1);
              scanf("\n%s", cpfdigitado);
              retorno = procura_cpf(cpfdigitado, cpf);
              if(retorno == -1)
              {   strcpy(cpf[contador_cliente], cpfdigitado);
                  printf("\nCliente Cadastrado!\n\n");
              }else
                  printf("\nCPF já cadastrado!, digite outro...\n");
          }while(retorno != -1);
    }else
        printf("\nLIMITE DE CLIENTES ATINGIDO!, Voltando para o menu...\n\n");
}

void cadastra_escala(int codigo_escala[qtd_escalas], char cidades_escalas[qtd_escalas][50], int contador_escala)
{
    printf("---------------------------------------------------\n");
    printf("\n                   CADASTRO DE ESCALAS           \n");
    if (contador_escala < qtd_escalas)
    {   int escala_digitada=0, aux=0;
        do
        {   printf("\nDigite o código da escala %d: ", contador_escala + 1);
            scanf("%d", &escala_digitada);
            aux = retorna_posicao_escala(codigo_escala, escala_digitada);
            if(aux == -1)// se o codigo da escala ainda nao existir
            {   codigo_escala[contador_escala] = escala_digitada;
                printf("\nDigite o nome da cidade da escala %d: ", contador_escala + 1);
                scanf("\n%[^\n]s", cidades_escalas[contador_escala]);
                printf("\nEscala Cadastrada!\n");
            }else// se o codigo da escala já existir
                printf("\nEssa escala já foi cadastrada, digite outro código...\n");
        }while(aux != -1);
    }else
        printf("\nLIMITE DE ESCALAS ATINGIDO! Voltando para o menu...\n");
}

int cadastra_voo(int codigo_voo[qtd_voos], int qtd_filas[qtd_voos], char cidade_origem[qtd_voos][50], char cidade_destino[qtd_voos][50], char tipo_voo[qtd_voos], float valor_passagem[qtd_voos], int codigo_escala[qtd_voos], char cidades_escalas[qtd_voos][50], int escala_do_voo[qtd_voos], int contador_voos)
{
    printf("---------------------------------------------------\n");
    printf("\n                   CADASTRO DE VOOS              \n");
    if (contador_voos < qtd_voos)
    {   int i, loop, codigo_digitado;
        do //registro do codigo dos voos
        {   printf("\nDigite o código do voo %d: ", contador_voos+1);
            scanf("%d", &codigo_digitado);
            loop = compara_voo(codigo_voo, codigo_digitado); // verifica se o voo já existe ou não
            if(loop == 1) // se já existir o voo, ele pede outro codigo para ser cadastrado
            {  printf("\nEsse voo já foi cadastrado, digite outro código...\n");
            }else//se nao existir voo cadastrado
            {
                printf("\nDigite o tipo do voo (D- direto, E- escala): ");
                scanf("\n%c", &tipo_voo[contador_voos]);
                if (tipo_voo[contador_voos]=='e' || tipo_voo[contador_voos]=='E') //exibição das escalas disponíveis
                {   //exibição de todas as escalas cadastradas
                    int retorno;
                    printf("\nTipo de voo escolhido: Escala\n");
                    retorno = exibe_escalas(codigo_escala, cidades_escalas);
                    if(retorno == 0)// se não existir escala cadastrada a função retorna 0.
                        return contador_voos; //Logo, volta para o menu inicial

                    do //Escolha da escala que o voo fará
                    {   int escala_escolhida;
                        printf("\nDigite o código da escala que o voo %d fará: ", contador_voos+1);
                        scanf("%d", &escala_escolhida);
                        escala_do_voo[contador_voos] = retorna_posicao_escala(codigo_escala, escala_escolhida);
                        if(escala_do_voo[contador_voos] == -1)
                            printf("\nEscala inválida! Digite uma escala válida...\n");
                        else
                            printf("\nEscala escolhida: %d", escala_escolhida);
                    }while(escala_do_voo[contador_voos] == -1);
                }else
                  if(tipo_voo[contador_voos]=='d' || tipo_voo[contador_voos]=='D')
                      printf("\nTipo de voo escolhido: Direto\n");
               codigo_voo[contador_voos] = codigo_digitado; // caso nao exista o codigo na lista, ele cadastra como um novo voo
            }
        }while(loop == 1);

        do //registro da quantidade de filas do voo
        {   printf("\nDigite a quantidade de filas do voo %d: ", contador_voos+1);
            scanf("%d", &qtd_filas[contador_voos]);
            if(qtd_filas[contador_voos] > 40)
                printf("\nQUANTIDADE DE FILAS ACIMA DO PERMITIDO! Digite novamente...\n");
        }while(qtd_filas[contador_voos] > 40);  //restrição para que o usuário não cadastre mais de 40 filas(limite)

        printf("\nDigite a cidade de origem: ");
        scanf("\n%[^\n]s", cidade_origem[contador_voos]);
        printf("\nDigite a cidade de destino: ");
        scanf("\n%[^\n]s", cidade_destino[contador_voos]);


        printf("\nDigite o valor da passagem: ");
        scanf("%f", &valor_passagem[contador_voos]);
        printf("\nVoo Cadastrado!\n");
    }else
        printf("\nLIMITE DE VOOS ATINGIDO!, Voltando ao menu...\n");
    contador_voos++;
    return contador_voos;
}

int exibe_escalas(int codigo_escala[qtd_escalas], char cidades_escalas[qtd_escalas][50])
{
    int i, escala_escolhida, cont=0;
    for (i=0; i<qtd_escalas; i++)
    {
        if (codigo_escala[i] != 0) //se existir escala
        {   printf("\nEscala %d - código: %d", i+1, codigo_escala[i]);
            printf(" Cidade: %s", cidades_escalas[i]);
        }

        if(codigo_escala[i] == 0 && (i==0 || codigo_escala[i-1]==0)) //se nao existir escala cadastrada no índice atual, e não existir escala no indice anterior
        {
            cont++;
        }
    }
    if(cont == qtd_escalas)
    {
        printf("\nNÃO EXISTE ESCALA CADASTRADA!, Voltando ao menu...\n");
        return 0; //para a função e volta ao menu
    }
    return 1;
}

int compra_passagem(char nome_clientes[qtd_clientes][50], char CPF[qtd_clientes][12], int codigo_voo[qtd_voos], char cidade_origem[qtd_voos][50], char cidade_destino[qtd_voos][50], int qtd_filas[qtd_voos], float valor_passagem[qtd_voos], char tipo_voo[qtd_voos], int codigo_escala[qtd_escalas], char cidades_escalas[qtd_escalas][50], int escala_do_voo[qtd_voos], char poltronas[qtd_voos][40][4], int contador[qtd_clientes][qtd_voos], int assentos_livres[qtd_voos], char passagens[qtd_voos][40][4][12], int contador_passagens)
{
    char cpf_digitado[12];
    int submenu, retorno_cpf, retorno_posicao_voo, codigo_voo_digitado;
    printf("---------------------------------------------------\n");
    printf("\n               COMPRAR PASSAGEM                  \n");
    if(contador_passagens < qtd_passagens)
    {   //cpf do cliente
        do//loop para caso o usuário digite o cpf errado
        {   printf("\nDigite um CPF (somente números): ");
            scanf("\n%s", cpf_digitado);
            retorno_cpf = procura_cpf(cpf_digitado, CPF);
            if(retorno_cpf == -1) //retorno_cpf == -1 significa que o cpf não está no vetor de CPFs
            {
                printf("\n\n1- Digite novamente o CPF");
                printf("\n2- Voltar ao menu\n");
                printf("\nESCOLHA UMA OPÇÃO:");
                scanf("%d", &submenu);
                switch (submenu)
                {
                  case 1:
                      break;
                  case 2:
                      return 0;//fecha a função e volta pro menu inicial
                      break;
                  default:
                      printf("\nOPÇÃO INVÁLIDA!, Por favor digite uma opção válida...\n");
                      submenu = 1;
                      break;
                }
            }else // se o cpf estiver no vetor de cpfs
                {   printf("\nCliente %s, CPF: %s\n", nome_clientes[retorno_cpf], CPF[retorno_cpf]); // se o CPFs estiver cadastrado, exibe o nome do cliente e o seu cpf
                    submenu = 0; //pára o do-while
                }
        }while(submenu == 1); //enquanto o usuário escolher digitar cpf novamente, ou digitar uma opção que não está no submenu o do-while irá dar loop

        //código de voo
        do
        {   printf("\nDigite o código do voo: ");
            scanf("%d", &codigo_voo_digitado);
            retorno_posicao_voo = procura_codigo_voo(codigo_voo_digitado, codigo_voo);

            //essa parte não deixa o usuario comprar mais de 2 passagens por voo
            contador[retorno_cpf][retorno_posicao_voo]++;//voltar aqui mais tarde
            if(contador[retorno_cpf][retorno_posicao_voo] > 2)
            {   printf("\nVocê atingiu o limite de passagens por CPF para esse voo\n");
                return contador_passagens;
            }

            if(retorno_posicao_voo != -1)// se o voo for encontrado
            {
                printf("\n# Código do voo: %d", codigo_voo[retorno_posicao_voo]);
                printf("\n# Cidade de Origem: %s", cidade_origem[retorno_posicao_voo]);
                printf("\n# Cidade de Destino: %s", cidade_destino[retorno_posicao_voo]);
                printf("\n# Quantidade de Filas: %d", qtd_filas[retorno_posicao_voo]);
                printf("\n# Tipo de voo: ");
                if(tipo_voo[retorno_posicao_voo] == 'd' || tipo_voo[retorno_posicao_voo] == 'D')
                    printf("Direto\n");
                else
                if(tipo_voo[retorno_posicao_voo] == 'e' || tipo_voo[retorno_posicao_voo] == 'E')
                {
                    printf("Com Escala\n");
                    printf("\n##Código da escala: %d, ", codigo_escala[escala_do_voo[retorno_posicao_voo]]);
                    printf("\n##Cidade da escala: %s", cidades_escalas[escala_do_voo[retorno_posicao_voo]]);
                }
                printf("\n#Valor da Passagem: %.2f R$\n", valor_passagem[retorno_posicao_voo]);
            }else
            {   printf("\nVoo não cadastrado!");
                printf("\n1- Digitar código novamente");
                printf("\n2- Voltar para o menu");
                printf("\nEscolha uma opção: ");
                scanf("%d", &submenu);
                if(submenu == 2)
                    return 0;
            }
        }while(submenu == 1);

        //registro da fila e assento do cliente
        int fila=0, assento=0;
        char aux;
        do
        {   mapa_de_filas(poltronas, qtd_filas, retorno_posicao_voo, assentos_livres);//exibe o estado de cada poltrona do voo (LIVRE ou OCUPADA)
            printf("\nDigite o número da fila que deseja escolher (1 a %d): ", qtd_filas[retorno_posicao_voo]);
            scanf("%d", &fila);
            fila--;
            do
            {   printf("\nDigite qual assento deseja escolher (A, B, C ou D): ");
                scanf("\n%c", &aux);
                assento = transforma_letra_do_assento(aux);//converte a letra escolhida para um número que indicará a posicao do assento
            }while(assento == -1);

            if(poltronas[retorno_posicao_voo][fila][assento] == 'O')//se a poltrona escolhida estiver ocupada
            {
                printf("\nPoltrona Ocupada, escolha outra poltrona...\n");
                printf("\n1- Digitar novamente\n2- Voltar para o menu: ");
                scanf("%d", &submenu);
                if(submenu == 2)
                  return 0;
            }else//se a poltrona escolhida NÃO estiver ocupada
            {
                poltronas[retorno_posicao_voo][fila][assento] = 'O';
                strcpy(passagens[retorno_posicao_voo][fila][assento], cpf_digitado);//copia o cpf do cliente para a matriz de passagens no exato lugar onde ele comprou o assento
                printf("\nPoltrona (%d - %c) Reservada com sucesso!\n", fila+1, aux);
                break;
            }
        }while(submenu == 1);
    }else
        printf("\nLIMITE DE PASSAGENS ATINGIDO! Voltando ao menu...\n");
    contador_passagens++;
    return contador_passagens;
}

int transforma_letra_do_assento(char aux)
{
    if(aux == 'A' || aux == 'a')
      return 0;
    else
    if(aux == 'B' || aux == 'b')
      return 1;
    else
    if(aux == 'C' || aux == 'c')
      return 2;
    else
    if(aux == 'D' || aux == 'd')
      return 3;
    else
    {   printf("\nOpção inválida!, escolha novamente...\n");
        return -1;
    }
}

int procura_cpf(char cpfdigitado[12], char CPF[qtd_clientes][12])//O objetivo da função "procura_cpf" é comparar o cpf digitado pelo usuário com todos os CPFs cadastrados, retornar se ele existe e qual a sua posição no vetor de CPFs
{
    int i, resultado, indice;
    for(i=0; i<qtd_clientes; i++) //faz um loop para comparar o cpf digitado com todos os cpfs armazenados no vetor CPF
    {   resultado = strcmp(cpfdigitado, CPF[i]); //a função STRCMP compara se o cpfdigitado é igual ao cpf do vetor
        if(resultado == 0) // se são iguais, a variavel resultado receberá "0" como saida do STRCMP
        {   //printf("\nCPF encontrado!\n");
            indice = i;//"indice" recebe a posição do cpf no vetor de CPFs para que possa ser utilizado no futuro
            break;// se o cpf já foi achado, não tem pq continuar o loop, por isso o break
        }
    }
    if(resultado != 0)//se o cpf não estiver no vetor de cpfs
    {   //printf("\nCPF não encontrado!\n");
        return -1; //se o cpf digitado pelo usuário não for achado pela função, ela retornará "-1", para que possa ser exibido o submenu
    }
    return indice; //se o cpf foi encontrado, a posição de onde ele está na lista será retornada
}

int procura_codigo_voo(int codigo_voo_digitado, int codigo_voo[qtd_voos])
{
    int i, resultado, indice;
    for(i=0; i<qtd_voos; i++)
    {   if(codigo_voo_digitado == codigo_voo[i])//se o código digitado for igual
        {   printf("\nVoo encontrado!\n");
            indice = i;// indice recebe em qual posicao da lista o codigo está
            break;//como o codigo foi encontrado nao tem pq continuar o loop
        }else
            indice = -1;
    }
    return indice;
}

int retorna_posicao_escala(int codigo_escala[qtd_escalas], int escala_escolhida)
{
    int i;
    for(i=0; i<qtd_escalas; i++)
    {   if(codigo_escala[i] == escala_escolhida)
          return i;
    }
    return -1; // se a escala não estiver na lista a função retorna -1
}

void mapa_de_filas(char poltronas[qtd_voos][40][4], int qtd_filas[qtd_voos], int retorno_posicao_voo, int assentos_livres[qtd_voos])
{
    int i, j;
    assentos_livres[retorno_posicao_voo] = qtd_filas[retorno_posicao_voo]*4;//quantidade de assentos livres inicial
    for(i=0; i<qtd_filas[retorno_posicao_voo]; i++)
    {
        printf("\nFila %d", i+1);
        for(j=0; j<4; j++)
        {
            if(poltronas[retorno_posicao_voo][i][j] == 'O')
            {   printf("\nAssento %d: OCUPADO", j+1);
                assentos_livres[retorno_posicao_voo]--;
            }else
                printf("\nAssento %d: LIVRE", j+1);
        }
        printf("\n");
    }
    printf("\nQuantidade de assentos livres: %d\n", assentos_livres[retorno_posicao_voo]);
}

void exibir_det_voo(int codigo_voo[qtd_voos], char poltronas[qtd_voos][40][4], int qtd_filas[qtd_voos],char cidade_origem[qtd_voos][50], char cidade_destino[qtd_voos][50], char tipo_voo[qtd_voos], float valor_passagem[qtd_voos], char cidades_escalas[qtd_escalas][50], int escala_do_voo[qtd_voos], int assentos_livres[qtd_voos])
{
      int codigo_voo_digitado, retorno_posicao_voo, submenu;
      printf("---------------------------------------------------\n");
      printf("\n                  EXIBIR VOO                     \n");
      do
        {   printf("\nDigite o código do voo: ");
            scanf("%d", &codigo_voo_digitado);
            retorno_posicao_voo = procura_codigo_voo(codigo_voo_digitado, codigo_voo);

            if(retorno_posicao_voo != -1)
            {
                printf("\n# Código do voo: %d\n", codigo_voo[retorno_posicao_voo]);
                printf("\n# ASSENTOS DO VOO\n");
                mapa_de_filas(poltronas, qtd_filas, retorno_posicao_voo, assentos_livres);
                printf("\n# Cidade de Origem: %s", cidade_origem[retorno_posicao_voo]);
                printf("\n# Cidade de Destino: %s", cidade_destino[retorno_posicao_voo]);
                printf("\n# Tipo de voo: ");
                if(tipo_voo[retorno_posicao_voo] == 'd' || tipo_voo[retorno_posicao_voo] == 'D')
                    printf("Direto\n");
                else
                if(tipo_voo[retorno_posicao_voo] == 'e' || tipo_voo[retorno_posicao_voo] == 'E')
                {   printf("Com Escala\n");
                    printf("\n##Cidade da escala: %s", cidades_escalas[escala_do_voo[retorno_posicao_voo]]);
                }
                printf("\n#Valor da Passagem: %.2f R$\n", valor_passagem[retorno_posicao_voo]);
            }else
            {   printf("\nVoo não cadastrado!\n");
                return;
            }
        }while(submenu == 1);
}

int compara_voo(int codigo_voo[qtd_voos],int codigo_digitado)
{
    int i;
    for(i=0; i<qtd_voos; i++)
    {  if(codigo_digitado == codigo_voo[i])
          return 1;
    }
    return 0;
}

void exibir_cliente_passagens(char CPF[qtd_clientes][12], char nome_clientes[qtd_clientes][50], int codigo_voo[qtd_voos], char cidade_origem[qtd_voos][50], char cidade_destino[qtd_voos][50], int qtd_filas[qtd_voos], char passagens[qtd_voos][40][4][12])
{
    int retorno_posicao_cpf, retorno;
    int i, j, k, cont=0;
    char cpfdigitado[12], assento;
    printf("---------------------------------------------------\n");
    printf("\n              EXIBIR CLIENTE                    \n");
    printf("Digite o cpf: ");
    scanf("%s", cpfdigitado);
    retorno_posicao_cpf = procura_cpf(cpfdigitado, CPF);
    if(retorno_posicao_cpf != -1)//se o cpf existir na lista
    {
        for(i=0; i<qtd_voos; i++)//percorre todos os voos
        {
            for(j=0; j<qtd_filas[i]; j++)//percorre todas as filas do voo
            {
                for(k=0; k<4; k++)//percorre todos os assentos da fila
                {
                    retorno = strcmp(passagens[i][j][k], cpfdigitado);//compara o cpf digitado com a reserva do assento
                    if(retorno == 0)//se o assento estiver reservado com o cpf digitado
                    {
                        printf("\n#PASSAGEM:");
                        printf("\nNome do cliente: %s", nome_clientes[retorno_posicao_cpf]);
                        printf("\nCPF do cliente: %s", CPF[retorno_posicao_cpf]);
                        printf("\nCódigo do voo: %d", codigo_voo[i]);
                        printf("\nCidade de origem: %s", cidade_origem[i]);
                        printf("\nCidade de destino: %s", cidade_destino[i]);
                        assento = transforma_numero_do_assento(k);
                        printf("\nFila: %d - Assento: %c\n", j+1, assento);
                        cont = 1;
                    }
                }
            }
        }
        if(cont != 1)
            printf("\nNão há nenhuma passagem reservada para esse CPF!\n");
    }else
        printf("\nCPF não cadastrado!\n");
}

char transforma_numero_do_assento(int aux)
{
    switch(aux)
    {
      case 0:
        return 'A';
        break;
      case 1:
        return 'B';
        break;
      case 2:
        return 'C';
        break;
      case 3:
        return 'D';
        break;
      default:
        break;
    }
}
