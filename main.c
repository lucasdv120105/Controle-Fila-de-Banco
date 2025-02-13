#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
  char *nome;
  int cpf;
  bool prioridade;
} Cliente;

typedef struct No
{
  Cliente dados;
  struct No *anterior;
  struct No *proximo;
} No;

typedef struct
{
  No *inicio;
  No *fim;
  int contadorPrioridades;
} tipoLista;

void inicializarLista(tipoLista *lista)
{
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->contadorPrioridades = 0;
}

void cadastrarCliente(tipoLista *lista, Cliente cliente)
{
  No *novoNo = (No *)malloc(sizeof(No));
  if (!novoNo)
    return;

  novoNo->dados.nome = (char *)malloc(strlen(cliente.nome) + 1);
  strcpy(novoNo->dados.nome, cliente.nome);
  novoNo->dados.cpf = cliente.cpf;
  novoNo->dados.prioridade = cliente.prioridade;

  novoNo->anterior = NULL;
  novoNo->proximo = NULL;

  if (lista->contadorPrioridades == 2 && cliente.prioridade)
  {
    novoNo->dados.prioridade = false;
    lista->contadorPrioridades = 0;
  }

  if (lista->inicio == NULL)
  {
    lista->inicio = novoNo;
    lista->fim = novoNo;
  }
  else if (novoNo->dados.prioridade)
  {
    No *atual = lista->inicio;

    while (atual->proximo != NULL && atual->dados.prioridade)
    {
      atual = atual->proximo;
    }

    if (atual == lista->inicio && !atual->dados.prioridade)
    {
      novoNo->proximo = lista->inicio;
      lista->inicio->anterior = novoNo;
      lista->inicio = novoNo;
    }
    else if (atual == lista->inicio && atual->dados.prioridade)
    {
      novoNo->anterior = lista->fim;
      lista->fim->proximo = novoNo;
      lista->fim = novoNo;
    }
    else
    {
      novoNo->proximo = atual;
      novoNo->anterior = atual->anterior;

      if (atual->anterior)
        atual->anterior->proximo = novoNo;
      else
        lista->inicio = novoNo;

      atual->anterior = novoNo;
    }

    lista->contadorPrioridades++;
  }
  else
  {
    novoNo->anterior = lista->fim;
    lista->fim->proximo = novoNo;
    lista->fim = novoNo;

    lista->contadorPrioridades = 0;
  }
}

void imprimirLista(tipoLista *lista)
{
  No *atual = lista->inicio;
  while (atual != NULL)
  {
    printf("Nome: %s, CPF: %d, Prioridade?: %s\n",
           atual->dados.nome, atual->dados.cpf, atual->dados.prioridade ? "SIM" : "NAO");
    atual = atual->proximo;
  }
}

bool caixas[5] = {false, false, false, false, false};
int contadorCaixas[5] = {0, 0, 0, 0, 0};

void chamaCliente(tipoLista *lista, bool caixas[], int numCaixas)
{
  if(lista->inicio == NULL){
    printf("Fila vazia.\n");
    return;
  }

  No *atual = lista->inicio;
  
  while (atual != NULL)
  {
    for(int i = 0; i < numCaixas; i++){
      if(!caixas[i]){
        if(atual->dados.prioridade == true){
          printf("Cliente %s (PRIORITARIO): CAIXA %d\n", atual->dados.nome, i + 1);
        }
        else{
          printf("Cliente %s: CAIXA %d\n", atual->dados.nome, i + 1);
        }
        No *temp = lista->inicio;
        lista->inicio = lista->inicio->proximo;
        free(temp);
        caixas[i] = true;
        contadorCaixas[i]++;
        return;
      }
    }
    printf("Todos os caixas estão ocupados, espere algum liberar o cliente.\n");
  }
}

void liberaCaixa(bool caixas[], int numCaixas)
{
  caixas[numCaixas - 1] = false;
  printf("Caixa %d liberado.\n", numCaixas);
}

void clientesPorCaixa(){
  printf("Caixa 1: %d clientes atendidos.\nCaixa 2: %d clientes atendidos.\n", contadorCaixas[0], contadorCaixas[1]);
  printf("Caixa 3: %d clientes atendidos.\nCaixa 4: %d clientes atendidos.\n", contadorCaixas[2], contadorCaixas[3]);
  printf("Caixa 5: %d clientes atendidos.\n", contadorCaixas[4]);
}

int main()
{
  tipoLista lista;
  inicializarLista(&lista);

  Cliente c1 = {"Carlos", 999555333, true};
  Cliente c2 = {"Jorge", 777222444, true};
  Cliente c3 = {"Milton", 888111666, true};
  Cliente c4 = {"Amilcar", 111222333, true};
  Cliente c5 = {"Ricardo", 321321321, true};
  Cliente c6 = {"Luiz", 654987321, true};
  Cliente c7 = {"Ana", 123456789, false};

  cadastrarCliente(&lista, c1);
  cadastrarCliente(&lista, c2);
  cadastrarCliente(&lista, c3);
  cadastrarCliente(&lista, c4);
  cadastrarCliente(&lista, c5);
  cadastrarCliente(&lista, c6);
  cadastrarCliente(&lista, c7);

  imprimirLista(&lista);

  chamaCliente(&lista, caixas, 5);

  imprimirLista(&lista);

  chamaCliente(&lista, caixas, 5);

  imprimirLista(&lista);

  liberaCaixa(caixas, 1);

  chamaCliente(&lista, caixas, 5);

  imprimirLista(&lista);

  clientesPorCaixa();
}
