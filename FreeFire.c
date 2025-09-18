#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.
void exibirMenu();
void inserirItem();
void removerItem();
void listarItens();
void buscaBinariaPorNome();
void menuDeOrdenacao();
void insertionSortPorNome();
void insertionSortPorPrioridade();
void insertionSortPorTipo();

bool ordenadaPorNome = false;

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscaBinariaPorNome();
                break;
            case 5:
                menuDeOrdenacao();
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
            }
        } while (opcao != 0);

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[15];
    char tipo[15];
    int quantidade;
    int prioridade;
} Item;

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
Item mochila[10];
int numItens = 0;

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
void exibirMenu() {
    printf("========================\n");
    printf("Escolha uma opcao:\n");
    printf("========================\n");
    printf("1 - Adicionar um item\n");
    printf("2 - Remover um item\n");
    printf("3 - Listar todos os itens\n");
    printf("4 - Realizar busca binaria por nome\n");
    printf("5 - Ordenar os itens por criterio (nome, tipo, prioridade)\n");
    printf("0 - Sair\n");
    printf("------------------------\n");
}

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
void inserirItem() {
    if (numItens >= 10) {
        printf("Mochila cheia!\n");
        return;
    }
    Item novoItem;

    printf("Digite o nome do item: ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);

    printf("Digite o tipo do item: ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);

    printf("Digite a quantidade do item: ");
    scanf("%d", &novoItem.quantidade);

    printf("Digite a prioridade do item (1 a 5): ");
    scanf("%d", &novoItem.prioridade);

    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0;
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;
    getchar();

    
    mochila[numItens] = novoItem;
    numItens++;
    printf("Item adicionado com sucesso!\n");
    
}

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
void removerItem() {
    char nome[50];
    printf("Digite o nome do item a ser removido: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    for(int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for(int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            numItens--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }
    printf("Item nao encontrado!\n");
}

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens() {
    printf("Mochila:\n");
    printf("Nome\tTipo\tQuantidade\tPrioridade\n");
    for(int i = 0; i < numItens; i++) {
        printf("%-15s%-15s%-10d%-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
}

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).
void menuDeOrdenacao() {
    int criterio;
    printf("Escolha um criterio de ordenacao:\n");
    printf("1 - Por nome\n");
    printf("2 - Por tipo\n");
    printf("3 - Por prioridade\n");
    scanf("%d", &criterio);
    getchar();

    if (criterio == 1) {
        insertionSortPorNome();
    } else if (criterio == 2) {
        insertionSortPorTipo();
    } else if (criterio == 3) {
        insertionSortPorPrioridade();
    } else {
        printf("Criterio invalido!\n");
    }
}

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)
void insertionSortPorNome() {
    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0 && strcmp(mochila[j].nome, chave.nome) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }
    ordenadaPorNome = true;
}

void insertionSortPorTipo() {
    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0 && strcmp(mochila[j].tipo, chave.tipo) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }
}

void insertionSortPorPrioridade() {
    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0 && mochila[j].prioridade < chave.prioridade) {
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }
}

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
void buscaBinariaPorNome() {
    char nome[50];
    printf("Digite o nome do item a ser encontrado: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    if (ordenadaPorNome) {
        int inicio = 0, fim = numItens - 1, meio;
        while (inicio <= fim) {
            meio = (inicio + fim) / 2;
            if (strcmp(mochila[meio].nome, nome) == 0) {
                printf("Nome: %s\n", mochila[meio].nome);
                printf("Tipo: %s\n", mochila[meio].tipo);
                printf("Quantidade: %d\n", mochila[meio].quantidade);
                printf("Prioridade: %d\n", mochila[meio].prioridade);
                return;
            } else if (strcmp(mochila[meio].nome, nome) > 0) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
    }
    printf("Item nao encontrado!\n");
}
