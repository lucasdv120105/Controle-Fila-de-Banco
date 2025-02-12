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
} tipoLista;

void inicializarLista(tipoLista *lista)
{
  lista->inicio = NULL;
  lista->fim = lista->inicio;
}

void cadastrarCliente(tipoLista *lista, Cliente cliente)
{
  int contadorPrioridade = 0;
  No *novoNo = (No *)malloc(sizeof(No));
  if (!novoNo)
    return;

  novoNo->dados = cliente;

  novoNo->anterior = NULL;
  novoNo->proximo = NULL;

  if (lista->inicio == NULL)
  {
    lista->inicio = novoNo;
    lista->fim = novoNo;
    return;
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
    else
    {
      novoNo->proximo = atual;
      novoNo->anterior = atual->anterior;

      if (atual->anterior)
      {
        atual->anterior->proximo = novoNo;
      }
      else
      {
        lista->inicio = novoNo;
      }

      atual->anterior = novoNo;
    }
  }
  else
  {
    novoNo->anterior = lista->fim;
    lista->fim->proximo = novoNo;
    lista->fim = novoNo;
    contadorPrioridade++;
  }
}

void imprimirLista(tipoLista *lista)
{
  No *atual = lista->inicio;
  char prioridade[10];
  while (atual != NULL)
  {
    if (atual->dados.prioridade == true)
      strcpy(prioridade, "SIM");
    else
      strcpy(prioridade, "NAO");

    printf("Nome: %s, CPF: %d, Prioridade?: %s\n", atual->dados.nome, atual->dados.cpf, prioridade);
    atual = atual->proximo;
  }
}

int main()
{
  tipoLista lista;
  Cliente c1 = {"Carlos", 999555333, true};
  Cliente c2 = {"Jorge", 777222444, true};
  Cliente c3 = {"Milton", 888111666, false};
  Cliente c4 = {"Amilcar", 111222333, true};
  inicializarLista(&lista);
  cadastrarCliente(&lista, c1);
  cadastrarCliente(&lista, c2);
  cadastrarCliente(&lista, c3);
  cadastrarCliente(&lista, c4);
  imprimirLista(&lista);
}
