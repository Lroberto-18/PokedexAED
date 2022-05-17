struct pokemon{
    char name[25];
    int id, type, hp, attack, defense, speed, speed_attack, speed_defense, score;
    struct pokemon *next;
};
typedef struct pokemon Pokemon;

struct noDescritor{
    Pokemon *inicio;
    Pokemon *aux;
    Pokemon *fim;
    int qtd, tipo;
};
typedef struct noDescritor Lista;

struct pokedex{
    int total;
    int qtd;
    Lista *vetor[18];
};
typedef struct pokedex Pokedex;

Pokedex *criar_pokedex(int qtd);
void libera_pokedex(Pokedex *P);
Lista *lista_criar();
Pokemon *criar_pokemon(Lista*, int, char*, int, int, int, int, int, int, int, int);
int atualiza_Pokemon ( Pokedex *pd , int);
int remove_Pokemon(Pokedex *P, int);
int busca_Pokemon(const Pokedex *P, int);
void menu(void);
int remove_Pokemon (Pokedex *P,int idt);
int qtd_tipo(const Pokedex *P, int tipo);
int tamanho_pokedex(Pokedex *P);
void lista_print(const Lista *L);
void inserir_pokemonOrdenado(Lista* L,Pokemon* pk);