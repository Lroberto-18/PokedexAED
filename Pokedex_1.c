#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "Pokedex_1.h"

Lista *lista_criar(){
    Lista *L = (Lista *)malloc(sizeof(Lista));
    L->inicio = NULL;
    L->fim = NULL;
    L->aux = NULL;
    L->qtd = 0;
    L->tipo = 0;
    return L;
}

//Criar Pokedex
/*	Essa funcao recebe um inteiro e cria um array[Qtd Tipos] com a quantidade de tipos de pokemons
passados como parametro. Considere o tipo de um pokemon os elementos da coluna Type 1 do arquivo
.cvs em [POKEMONS]. Considere o tipo de um Pokemon dado como uma string no arquivo .cvs como
um tipo inteiro, i.e, codifique esse o tipo de um pokemon como um inteiro.
*/
Pokedex *criar_pokedex(int qtd){
    Pokedex *v = (Pokedex*)malloc(qtd*sizeof(Pokedex));
    if(v==NULL) printf("Erro\n");
    for(int a = 0; a < qtd; a++){
        Lista *L = lista_criar();
        v->vetor[a] = L;
    }
    v->qtd = qtd;
    return v;
}

//Destruir Pokedex
/*
	implementação: void libera_Pokedex(Pokedex *P);
    Essa funcao deve liberar o espaco de memoria para todos as listas de pokemons e para o endereco
    reservado a Pokedex.
*/

//criar e Insercao de um novo pokemon
Pokemon *criar_pokemon(Lista *L, int id, char *name, int type, int hp, int attack, int defense, int speed, int speed_attack, int speed_defense, int score){
    Pokemon *pk = (Pokemon *)malloc(sizeof(Pokemon));
    strcpy(pk->name, name);
    pk->id = id;
    pk->type = type;
    pk->hp = hp;
    pk->attack = attack;
    pk->defense = defense;
    pk->speed = speed;
    pk->speed_attack = speed_attack;
    pk->speed_defense = speed_defense;
    pk->score = score;
    pk->next = NULL;
    L->qtd += 1;
    return pk;
}
void inserir_pokemonOrdenado(Lista *L, Pokemon *pk){
    if (L->inicio == NULL){
        L->inicio = pk;
        L->fim = pk;
        L->tipo = pk->type;
    }else if ((pk->score) < (L->inicio->score)){
        pk->next = L->inicio;
        L->inicio = pk;
    }else{
        L->aux = L->inicio;
        while (L->aux->next && pk->score > L->aux->next->score)
            L->aux = L->aux->next;
        pk->next = L->aux->next;
        L->aux->next = pk;
        L->fim = pk;
    }
}
//remocao de pokemons
/*
	implementação: int remove_Pokemon ( Pokedex pd , int id );
    Essa funcao que recebe um endereco para uma pokedex, o identificador de um pokemon. A funcao
dever ́a retornar 0 caso nao haja na lista um pokemon com o identificador passado como parametro.
Caso contrario, o pokemon deve ser removido da Pokedex.
*/
int remove_Pokemon(Pokedex *P, int idt){
    for(int a=0; a<P->qtd;a++){
        P->vetor[a]->aux = P->vetor[a]->inicio;
        while(P->vetor[a]->aux!=NULL){
            if(P->vetor[a]->inicio->id==idt){
                P->vetor[a]->fim = P->vetor[a]->inicio->next;
                free(P->vetor[a]->inicio);
                P->vetor[a]->inicio = P->vetor[a]->fim;
                P->vetor[a]->qtd -=1;
                return 1;
            }

            if(idt==P->vetor[a]->aux->id){
                P->vetor[a]->qtd -=1;
                P->vetor[a]->fim->next = P->vetor[a]->aux->next;
                free(P->vetor[a]->aux);
                return 1;
            }
            P->vetor[a]->fim = P->vetor[a]->aux;
            P->vetor[a]->aux = P->vetor[a]->aux->next;
        }
    }
    return 0;
    //se não encontrou retorna 1
}

//atualizar dados de um pokemon.
/*
    implementação: int atualiza_Pokemon ( Pokedex * pd , int id );
	Esta funcao recebe como parametro o endere co de uma Pokedex e o identificador de um pokemon.ç,
e devera retornar 0, caso nao exista um pokemon com o identificador passado como parametro. Caso
contrario, devera alterar os campos do respectivo pokemon, reorganizar a respectiva lista ordenada, caso
seja necessario, e retornar 1. Observe que, caso o valor total do pokemon atual se torne estritamente
menor do que o valor total do pokemon anterior ou estritamente maior do que o valor total do proximo
pokemon, ele devera mudar de posicao na respectiva lista ligada ordenada (de forma que a lista continue
ordenada).
*/

//buscar pokemon por id
int busca_Pokemon(const Pokedex *P, int idt){
    for(int a=0; a<P->qtd;a++){
        for(int b=0; b<P->vetor[a]->qtd;b++){
            if(P->vetor[a]->inicio->id==idt){
                printf("id: %d Nome: %s\n", P->vetor[a]->inicio->id, P->vetor[a]->inicio->name);
                return 2;
                //Se encontrou retorna 2
            }
            if(P->vetor[a]->inicio->next==NULL){
                break;
            }
            P->vetor[a]->inicio = P->vetor[a]->inicio->next;
        }
    }
    return 1;
    //se não encontrou retorna 1
}

//Consulta a quantidade de pokemons diferentes na lista (tamanho)
int tamanho_pokedex(Pokedex *P){
    P->total = 0;
    for(int a = 0; a < P->qtd; a++){
        P->total += P->vetor[a]->qtd;
    }
    return P->total;
}

//Imprime os pokemons de um mesmo tipo inseridos na Pokedex
void lista_print(const Lista *L){
    Pokemon *p = L->inicio;
    printf("\n:\n");
    printf(" | \n");
    printf(" V \n");
    while(p!=NULL) {
        printf("___| %s |___\n", p->name);
        printf("ID: %d\n", p->id);
        printf("TIPO: %d\n", p->type);
        printf("HP: %d\n", p->hp);
        printf("ATAQUE: %d\n", p->attack);
        printf("DEFESA: %d\n", p->defense);
        printf("VELOCIDADE: %d\n", p->speed);
        printf("VELOCIDADE DE DEFESA: %d\n", p->speed_defense);
        printf("VELOCIDADE DE ATAQUE:%d\n", p->speed_attack);
        printf("FORÇA TOTAL: %d\n", p->score);
        printf("| \n");
        printf("V \n");
        p = p->next;
    }
    printf("NULL\n");
}

//Consulta a quantidade de pokemon de um unico tipo
int qtd_tipo(const Pokedex *P, int tipo){
    return P->vetor[tipo]->qtd;
}

void menu(){
    printf("\n\nDigite 1 inserir um novo pokemon:\n");
    printf("Digite 2 buscar por um pokemon pelo identificador:\n");
    printf("Digite 3 imprime os pokemons de um mesmo tipo inseridos na Pokedex:\n");
    printf("Digite 4 consultar a quantidade de pokemon de um  ́unico tipo:\n");
    printf("Digite 5 consultar a quantidade de pokemons diferentes na pokedex (tamanho):\n");
    printf("Digite 6 remover pokemon:\n");
    printf("Digite 7 alterar dos dados de um pokemon.\n");
    printf("Digite 8 para encerrar\n");
    printf("Digite uma opção:\n\n");
}
int main(){
    setlocale(LC_ALL, "Portuguese");
    int id, type, hp, attack, defense, speed, speed_attack, speed_defense, score;
    char name[30];
    int opcaoMenu, qTipo, tipo, tamanho, id_t,q;

    printf("Digite a quantidade de tipos da sua pokedex:\n");
    scanf("%d", &qTipo);
    fflush(stdin);
    Pokedex *P = criar_pokedex(qTipo);
    if(qTipo>18){
        printf("Quantidade máxima ultrapassada\n");
        return 0;
    }

    do{ menu();
        scanf("%d", &opcaoMenu);
        fflush(stdin);

        switch (opcaoMenu){
        case 8:
            break;
        case 1:
            /*system("clear");
            printf("Inserir o ID:\n");
            scanf("%d", &id);
            fflush(stdin);
            printf("Inserir o TIPO:\n");
            scanf("%d", &type);
            fflush(stdin);
            printf("Inserir o NOME:\n");
            scanf("%s", name);
            fflush(stdin);
            printf("Inserir O HP:\n");
            scanf("%d", &hp);
            fflush(stdin);
            printf("Inserir o ATAQUE:\n");
            scanf("%d", &attack);
            fflush(stdin);
            printf("Inserir a DEFESA:\n");
            scanf("%d", &defense);
            fflush(stdin);
            printf("Inserir a VELOCIDADE:\n");
            scanf("%d", &speed);
            fflush(stdin);
            printf("Inserir a VELOCIDADE DE ATAQUE:\n");
            scanf("%d", &speed_attack);
            fflush(stdin);
            printf("Inserir a VELOCIDADE DE DEFESA:\n");
            scanf("%d", &speed_defense);
            fflush(stdin);
            printf("Inserir o SCORE:\n");
            scanf("%d", &score);
            fflush(stdin);*/
            printf("Inserir o NOME:\n");
            scanf("%s", name);
            printf("Inserir o TIPO:\n");
            scanf("%d", &type);
            fflush(stdin);
            printf("Inserir o ID:\n");
            scanf("%d", &id);
            fflush(stdin);
            Pokemon *pk = criar_pokemon(P->vetor[type-1], id, name, type, 45, 49, 45, 49, 65, 65, 100);
            inserir_pokemonOrdenado(P->vetor[type-1], pk);
            break;
        case 2:
            printf("Digite um id: ");
            scanf("%d", &id_t);

            int k = busca_Pokemon(P,id_t);
            if(k==1)
                printf("Não encontrou\n");
            if(k==2)
                printf("Encontrou\n");
            k=0;
            break;
        case 3:
            system("clear");
            printf("Digite o Tipo: ");
            fflush(stdin);
            scanf("%d", &tipo);
            lista_print(P->vetor[tipo-1]);
            break;
        case 4:
            system("clear");
            printf("Digite um tipo: ");
            scanf("%d", &tipo);
            int t_ipo = qtd_tipo(P, tipo-1);
            printf("Quantidade do tipo %d é: %d\n", tipo, t_ipo);
            fflush(stdin);
            break;
        case 5:
            tamanho = tamanho_pokedex(P);
            printf("a quantidades de pokemons em uma Pokedex é: %d\n", tamanho);
            break;
        case 6:
            printf("Digite um id: ");
            scanf("%d", &id_t);

            int q = remove_Pokemon(P,id_t);
            if(q==0)
                printf("Não encontrou\n");
            if(q==1)
                printf("Removeu\n");
            break;
        case 7:
            printf("\na");
            break;
        default:
            break;
        }
    }while(opcaoMenu != 8);
    printf("Encerrado\n");
return 0;
}