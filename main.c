#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
  char *nome;
  char *cpf;
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

  novoNo->dados.nome = strdup(cliente.nome);
  novoNo->dados.cpf = strdup(cliente.cpf);
  if (!novoNo->dados.nome || !novoNo->dados.cpf)
  {
    free(novoNo->dados.nome);
    free(novoNo->dados.cpf);
    free(novoNo);
    return;
  }

  novoNo->dados.prioridade = cliente.prioridade;
  novoNo->anterior = NULL;
  novoNo->proximo = NULL;

  if (lista->inicio == NULL)
  {
    lista->inicio = lista->fim = novoNo;
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
  while (atual)
  {
    printf("Nome: %s, CPF: %s, Prioridade?: %s\n",
           atual->dados.nome, atual->dados.cpf, atual->dados.prioridade ? "SIM" : "NAO");
    atual = atual->proximo;
  }
}

bool caixas[5] = {false, false, false, false, false};
int contadorCaixas[5] = {0, 0, 0, 0, 0};
int proximoCaixa = 0;

void chamaCliente(tipoLista *lista, bool caixas[], int numCaixas)
{
  if (!lista->inicio)
  {
    printf("Fila vazia.\n");
    return;
  }

  caixas[proximoCaixa] = false;

  if (lista->inicio->dados.prioridade)
    printf("Cliente %s (PRIORITARIO): CAIXA %d\n", lista->inicio->dados.nome, proximoCaixa + 1);
  else
    printf("Cliente %s: CAIXA %d\n", lista->inicio->dados.nome, proximoCaixa + 1);

  No *temp = lista->inicio;
  lista->inicio = lista->inicio->proximo;

  free(temp->dados.nome);
  free(temp->dados.cpf);
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
    getchar();

    switch (resp)
    {
    case 1:
      novoCliente.nome = (char *)malloc(100);
      novoCliente.cpf = (char *)malloc(20);
      if (!novoCliente.nome || !novoCliente.cpf)
      {
        printf("Erro ao alocar memória.\n");
        free(novoCliente.nome);
        free(novoCliente.cpf);
        break;
      }

      printf("Digite o nome do cliente: ");
      fgets(novoCliente.nome, 100, stdin);
      novoCliente.nome[strcspn(novoCliente.nome, "\n")] = 0;

      printf("Digite o CPF do cliente: ");
      fgets(novoCliente.cpf, 20, stdin);
      novoCliente.cpf[strcspn(novoCliente.cpf, "\n")] = 0;

      printf("O cliente tem prioridade? (1- Sim ou 0- Nao): ");
      scanf("%d", &novoCliente.prioridade);
      getchar();

      cadastrarCliente(&lista, novoCliente);

      free(novoCliente.nome);
      free(novoCliente.cpf);

      printf("Cliente cadastrado com sucesso!\n");
      break;

    case 2:
      imprimirLista(&lista);
      break;

    case 3:
      chamaCliente(&lista, caixas, 5);
      break;

    case 4:
    case 5:
      clientesPorCaixa();
      break;
    }
  } while (resp != 5);
}
