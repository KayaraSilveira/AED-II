#include <stdio.h>
#include <stdlib.h>

typedef struct grafo Grafo;
struct grafo {

    int qtd_vertices; //a quantidade de vertices vai ser estática, o usuário decide na hora da criação do grafo
    int grau_max; //quantidade máxima de arestas pra cada vertice
    int **arestas; 
    int **pesos;
    int *grau; //guarda onde vai ser inserida a proxima aresta

};

Grafo *criaGrafo(int qtd_vertices, int grau_max);
int insereAresta(Grafo *g);
void imprimir(Grafo *g);
void sair(Grafo *g);
void kruskal (Grafo *g);

int main () {

    int menu, qtd_vertices, grau_max;
    Grafo *g;

    printf("Quantos vertices voce deseja no grafo?\n");
    scanf("%d", &qtd_vertices);
    printf("Qual a quantidade maxima de arestas em cada vertice?\n");
    scanf("%d", &grau_max);

    g = criaGrafo(qtd_vertices, grau_max);
    int ant[qtd_vertices], dist[qtd_vertices];

    do {
        printf("O que voce deseja fazer?\n1)Adicionar uma aresta\n2)Visualizar uma aresta\n3)Kruskal\n4)Sair\n");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            insereAresta(g);
            break;
        
        case 2:
            imprimir(g);
            break;

        case 3:
            kruskal(g);
            break;
        
        case 4:
            sair(g);
            break;

        } 
    } while (menu != 4);
   
    return 0;
}

Grafo *criaGrafo(int qtd_vertices, int grau_max) {

    Grafo *g = (Grafo*)malloc(sizeof(struct grafo));
    if(g == NULL) {
        printf("Erro ao alocar grafo\n");
        return NULL;
    }
    else {
        int i;
        g->qtd_vertices = qtd_vertices;
        g->grau_max = grau_max;
        g->grau = (int*)calloc(qtd_vertices, sizeof(int)); 
        g->arestas = (int**)malloc(qtd_vertices * sizeof(int*));
        for(i = 0; i < qtd_vertices; i++) {
            g->arestas[i] = (int*)malloc(grau_max * sizeof(int));
        }
        g->pesos = (int**)malloc(qtd_vertices * sizeof(int*));
        for(i = 0; i < qtd_vertices; i++) {
            g->pesos[i] = (int*)malloc(grau_max * sizeof(int));
        }
    }

    return g;

}

int insereAresta(Grafo *g) {

    int v1, v2, peso;

    printf("Digite o valor do vertice 1:\n");
    scanf("%d", &v1);
    printf("Digite o valor do vertice 2:\n");
    scanf("%d", &v2);
    printf("Digite o peso da aresta:\n");
    scanf("%d", &peso);


    while((v1 < 0) || (v1 >= g->qtd_vertices) || (v2 < 0) || (v2 >= g->qtd_vertices)) {

        printf("Voce digitou informacoes invalidas\nO valor dos vertices nao pode ser negtivo e nem maior que a quantidade maxima de vertices\nO peso da aresta nao pode ser negativo\n");
        printf("Digite um valor valido para o vertice 1:\n");
        scanf("%d", &v1);
        printf("Digite um valor valido para o vertice 2:\n");
        scanf("%d", &v2);
        printf("Digite um valor valido para o peso da aresta:\n");
        scanf("%d", &peso);
    
    }

    g->arestas[v1][g->grau[v1]] = v2;
    g->pesos[v1][g->grau[v1]] = peso;
    g->grau[v1]++;
    g->arestas[v2][g->grau[v2]] = v1;
    g->pesos[v2][g->grau[v2]] = peso;
    g->grau[v2]++;
    
}

void imprimir(Grafo *g) {

    int i;

    int v1, v2, peso = -1;
    printf("Digite o valor do vertice 1:\n");
    scanf("%d", &v1);
    printf("Digite o valor do vertice 2:\n");
    scanf("%d", &v2);
    for(i = 0; i < g->grau_max; i++) {
        if(g->arestas[v1][i] == v2) {
            peso = g->pesos[v1][i];
        }
    }
    if(peso == -1) {
        printf("Nao ha aresta entre estes dois vertices\n");
    }
    else {
        printf("O peso da aresta entre estes dois vertices eh %d\n", peso);
    } 

}

void sair(Grafo *g) {

    int i;

    for(i = 0; i < g->qtd_vertices; i++) {
        free(g->arestas[i]);
        free(g->pesos[i]);
    }

    free(g->arestas);
    free(g->pesos);
    free(g->grau);
    free(g);

}

void kruskal (Grafo *g) {

    int adj[g->qtd_vertices];
    int i, j, dest, primeiro, origem = 0;
    double menorP;

    int *aux = (int*)malloc(g->qtd_vertices * sizeof(int));
    for(i = 0; i < g->qtd_vertices; i++) {
        aux[i] = i;
        adj[i] = -1;
    }
    adj[0] = 0;

    while(1) {
        primeiro = 1;
        for(i = 0; i < g->qtd_vertices; i++) {
            for(j = 0; j < g->grau[i]; j++) {
                if(aux[i] != aux[g->arestas[i][j]]) {
                    if(primeiro) {
                        menorP = g->pesos[i][j];
                        origem = i;
                        dest = g->arestas[i][j];
                        primeiro = 0;
                    }
                    else {
                        if(menorP > g->pesos[i][j]) {
                            menorP = g->pesos[i][j];
                            origem = i;
                            dest = g->arestas[i][j];
                        }
                    }
                }
            }
        }

        if(primeiro == 1) {
            break;
        }
        if(adj[origem] == -1) {
            adj[origem] = dest;
        }
        else {
            adj[dest] = origem;
        }

        for(i = 0; i < g->qtd_vertices; i++) {
            if(aux[i] == aux[dest]) {
                aux[i] = aux[origem];
            }
        }
    }

    printf("Grafo gerado, estas sao as arestas restantes: \n");
    for(i = 1; i < g->qtd_vertices; i++) {
        printf("aresta que liga %d e %d\n", adj[i], i);
    }

    free(aux);

}

