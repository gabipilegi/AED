#define TRUE 1
#define FALSE 0
#define BRANCO 0
#define CINZA 1
#define PRETO 2


typedef struct vstruct {

    int id;
    char*nome;
    char* cidade;
    char* pais;
    char IATA[100];
    double latitude;
    double longitude; 
	struct ArestaStruct * arestas;
	struct vstruct * pai;
	struct vstruct * prox;
	int nescalas;
	int cor;
	int distancia;

} Vertice;

typedef struct ArestaStruct {

	Vertice * dst;
    int peso;
	struct ArestaStruct * prox;

} Aresta;

typedef struct {

	int nv, na;

	Vertice * vertices;

} Grafo;

typedef struct{
	Vertice * inicio;
	Vertice * fim;
}Fila;

typedef struct {

	double x;
	double y;
	double z;

} Vector;

typedef struct {

	double latitude;
	double longitude;

} Coordinate;




Grafo * cria_grafo(int max_v);
void libera_grafo(Grafo * g);


void adiciona_aresta(Grafo * g, int u_id, int v_id);
void remove_aresta(Grafo * g);

void imprime_grafo(Grafo * g);
void imprime_adjacentes(Grafo * g, int u_id);
int verifica_aresta(Grafo * g, int u_id, int v_id);

