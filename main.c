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
  }
  else
  {
    novoNo->anterior = lista->fim;
    lista->fim->proximo = novoNo;
    lista->fim = novoNo;
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

int proximoCaixa = 0;

void chamaCliente(tipoLista *lista, bool caixas[], int numCaixas)
{
  if (lista->inicio == NULL)
  {
    printf("Fila vazia.\n");
    return;
  }

  caixas[proximoCaixa] = false;

  if (lista->inicio->dados.prioridade == true)
  {
    printf("Cliente %s (PRIORITARIO): CAIXA %d\n", lista->inicio->dados.nome, proximoCaixa + 1);
    lista->contadorPrioridades++;
  }
  else
  {
    printf("Cliente %s: CAIXA %d\n", lista->inicio->dados.nome, proximoCaixa + 1);
  }

  No *temp = lista->inicio;
  lista->inicio = lista->inicio->proximo;
  free(temp);

  caixas[proximoCaixa] = true;
  contadorCaixas[proximoCaixa]++;

  proximoCaixa = (proximoCaixa + 1) % numCaixas;
}

void clientesPorCaixa()
{
  printf("Caixa 1: %d clientes atendidos.\nCaixa 2: %d clientes atendidos.\n", contadorCaixas[0], contadorCaixas[1]);
  printf("Caixa 3: %d clientes atendidos.\nCaixa 4: %d clientes atendidos.\n", contadorCaixas[2], contadorCaixas[3]);
  printf("Caixa 5: %d clientes atendidos.\n", contadorCaixas[4]);
}

int main()
{
  tipoLista lista;
  inicializarLista(&lista);
  Cliente novoCliente;
  int resp;
  do
  {
    printf("\n== Fila de banco ==\n");
    printf("1- Cadastrar cliente\n");
    printf("2- Previsao de atendimento do cliente(listagem da organizacao da fila)\n");
    printf("3- Chamar cliente para atendimento\n");
    printf("4- Exibir quantitativo de clientes atendidos por cada caixa\n");
    printf("5- Encerrar expediente\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &resp);
    switch (resp)
    {
    case 1:
      novoCliente.nome = (char *)malloc(100 * sizeof(char));
      printf("Digite o nome do cliente: ");
      scanf(" %[^\n]s", novoCliente.nome);
      printf("Digite o cpf do cliente: ");
      scanf("%s", &novoCliente.cpf);
      printf("O cliente tem prioridade? (1- Sim ou 0- Nao): ");
      scanf("%d", &novoCliente.prioridade);
      cadastrarCliente(&lista, novoCliente);
      printf("Cliente cadastrado com sucesso!\n");
      break;

    case 2:
      imprimirLista(&lista);
      break;

    case 3:
      chamaCliente(&lista, caixas, 5);
      break;

    case 4:
      clientesPorCaixa();
      break;

    case 5:
      clientesPorCaixa();
      break;
    }
  } while (resp != 5);
}
