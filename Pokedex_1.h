struct pokemon{
    char name[25];
    int id, type, hp, attack, defense, speed, speed_attack, speed_defense, score;
    struct pokemon *next;
};
typedef struct pokemon Pokemon;

struct noDescritor{
    Pokemon *inicio;
    Pokemon *aux;
    Pokemon *aux2;
    int qtd, tipo;
};
typedef struct noDescritor Lista;

struct pokedex{
    int total;
    int qtd;
    Lista *vetor[18];
};
typedef struct pokedex Pokedex;

Pokedex *cria_pokedex(int);
Lista *lista();
Pokemon *cria_pokemon(Lista*, int, char*, int, int, int, int, int, int, int);
int atualiza_Pokemon(Pokedex*,int);
int remove_Pokemon(Pokedex*, int);
int busca_Pokemon(const Pokedex*, int);
int remove_Pokemon (Pokedex*,int);
int qtd_tipo(const Pokedex*, int);
int tamanho_pokedex(Pokedex*);
void lista_print(const Lista*);
void inseri_pokemon_ordenado(Lista*,Pokemon*);
void libera_pokedex(Pokedex*);
void menu();