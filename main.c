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

int main()
{
  tipoLista lista;
  inicializarLista(&lista);

  Cliente c1 = {"Carlos", 999555333, true};
  Cliente c2 = {"Jorge", 777222444, true};
  Cliente c3 = {"Milton", 888111666, false};
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
}
