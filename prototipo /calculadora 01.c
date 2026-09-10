#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>

#define MAX_PRODUTOS 5
#define MAX_CARRINHO 20

typedef struct {
    int codigo;
    char nome[50];
    float peso;
    float preco;
} Produto;

typedef struct {
    Produto produto;
    int quantidade;
} ItemCarrinho;

void exibirCabecalho();
void exibirProdutos(Produto produtos[]);
void exibirCarrinho(ItemCarrinho carrinho[], int totalItens);
int escolherProduto();
int escolherRegiao();
float calcularFrete(int regiao, float peso);
float calcularSubtotal(ItemCarrinho carrinho[], int totalItens);
float calcularPesoTotal(ItemCarrinho carrinho[], int totalItens);
float calcularTotal(float subtotal, float frete);
void adicionarProduto(ItemCarrinho carrinho[], int *totalItens, Produto produtos[]);
void removerProduto(ItemCarrinho carrinho[], int *totalItens);
void escolherPagamento(float total, int *formaPagamento, int *parcelas, char numeroCartao[]);
void exibirResumo(ItemCarrinho carrinho[], int totalItens, int regiao, float frete, float total, int formaPagamento, int parcelas, char numeroCartao[], struct tm *dataCompra, struct tm *dataEntrega);

int main() {
    setlocale(LC_ALL, "Portuguese");

    Produto produtos[MAX_PRODUTOS] = {
        {101, "Memoria RAM", 0.5, 250.00},
        {102, "SSD 480GB", 0.4, 320.00},
        {103, "Placa de Video", 1.8, 1500.00},
        {104, "Processador", 0.3, 900.00},
        {105, "Gabinete Completo", 2.0, 1800.00}
    };

    ItemCarrinho carrinho[MAX_CARRINHO];

    int totalItens = 0;
    int opcao;
    int regiao;
    int formaPagamento;
    int parcelas;

    float subtotal;
    float pesoTotal;
    float frete;
    float total;

    char numeroCartao[20];

    time_t agora;
    struct tm dataCompra;
    struct tm dataEntrega;

    exibirCabecalho();
    exibirProdutos(produtos);

    do {
        printf("\n==============================================");
        printf("\n                 MENU DE COMPRA");
        printf("\n==============================================");

        printf("\n[1] Adicionar produto");
        printf("\n[2] Remover produto");
        printf("\n[3] Visualizar carrinho");
        printf("\n[4] Finalizar compra");
        printf("\n[0] Sair");

        printf("\n\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                adicionarProduto(carrinho, &totalItens, produtos);
                break;

            case 2:
                removerProduto(carrinho, &totalItens);
                break;

            case 3:
                exibirCarrinho(carrinho, totalItens);
                break;

            case 4:

                if (totalItens == 0) {
                    printf("\nCarrinho vazio. Adicione pelo menos um produto.\n");
                    break;
                }

                exibirCarrinho(carrinho, totalItens);

                printf("\nDeseja finalizar a compra?");
                printf("\n[1] Sim");
                printf("\n[2] Nao");
                printf("\nEscolha: ");
                scanf("%d", &opcao);

                if (opcao != 1) {
                    printf("\nCompra nao finalizada.\n");
                    break;
                }

                regiao = escolherRegiao();

                subtotal = calcularSubtotal(carrinho, totalItens);
                pesoTotal = calcularPesoTotal(carrinho, totalItens);
                frete = calcularFrete(regiao, pesoTotal);
                total = calcularTotal(subtotal, frete);

                escolherPagamento(
                    total,
                    &formaPagamento,
                    &parcelas,
                    numeroCartao
                );

                time(&agora);

                dataCompra = *localtime(&agora);

                dataEntrega = dataCompra;
                dataEntrega.tm_mday += 7;

                mktime(&dataEntrega);

                exibirResumo(
                    carrinho,
                    totalItens,
                    regiao,
                    frete,
                    total,
                    formaPagamento,
                    parcelas,
                    numeroCartao,
                    &dataCompra,
                    &dataEntrega
                );

                printf("\nCompra finalizada com sucesso!");
                printf("\nObrigado pela compra!\n");

                totalItens = 0;

                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}

void exibirCabecalho() {
    printf("\n==============================================");
    printf("\n                 CALC.TECH                     ");
    printf("\n==============================================\n");
}

void exibirProdutos(Produto produtos[]) {
    int i;

    printf("\n==============================================");
    printf("\n                NOSSOS PRODUTOS");
    printf("\n==============================================");

    for (i = 0; i < MAX_PRODUTOS; i++) {
        printf("\n\n[%d] %s", i + 1, produtos[i].nome);
        printf("\nCodigo: %d", produtos[i].codigo);
        printf("\nPeso: %.2f kg", produtos[i].peso);
        printf("\nPreco: R$ %.2f", produtos[i].preco);
    }

    printf("\n\n==============================================\n");
}

int escolherProduto() {
    int opcao;

    printf("\nDigite o numero do produto (1, 2, 3, 4 ou 5): ");
    scanf("%d", &opcao);

    return opcao;
}

void adicionarProduto(ItemCarrinho carrinho[], int *totalItens, Produto produtos[]) {
    int opcao;
    int quantidade;
    int i;

    if (*totalItens >= MAX_CARRINHO) {
        printf("\nLimite do carrinho atingido.\n");
        return;
    }

    exibirProdutos(produtos);

    opcao = escolherProduto();

    if (opcao < 1 || opcao > MAX_PRODUTOS) {
        printf("\nProduto invalido.\n");
        return;
    }

    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);

    if (quantidade <= 0) {
        printf("\nQuantidade invalida.\n");
        return;
    }

    for (i = 0; i < *totalItens; i++) {
        if (carrinho[i].produto.codigo == produtos[opcao - 1].codigo) {
            carrinho[i].quantidade += quantidade;

            printf("\nProduto adicionado ao carrinho.\n");
            return;
        }
    }

    carrinho[*totalItens].produto = produtos[opcao - 1];
    carrinho[*totalItens].quantidade = quantidade;

    (*totalItens)++;

    printf("\nProduto adicionado ao carrinho.\n");
}

void removerProduto(ItemCarrinho carrinho[], int *totalItens) {
    int opcao;
    int i;

    if (*totalItens == 0) {
        printf("\nCarrinho vazio.\n");
        return;
    }

    exibirCarrinho(carrinho, *totalItens);

    printf("\nDigite o numero do produto que deseja remover: ");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > *totalItens) {
        printf("\nOpcao invalida.\n");
        return;
    }

    for (i = opcao - 1; i < *totalItens - 1; i++) {
        carrinho[i] = carrinho[i + 1];
    }

    (*totalItens)--;

    printf("\nProduto removido do carrinho.\n");
}

void exibirCarrinho(ItemCarrinho carrinho[], int totalItens) {
    int i;
    float subtotalItem;

    printf("\n==============================================");
    printf("\n                  SEU CARRINHO");
    printf("\n==============================================");

    if (totalItens == 0) {
        printf("\n\nCarrinho vazio.");
        printf("\n==============================================\n");
        return;
    }

    for (i = 0; i < totalItens; i++) {

        subtotalItem =
            carrinho[i].produto.preco *
            carrinho[i].quantidade;

        printf("\n\n[%d] %s", i + 1, carrinho[i].produto.nome);
        printf("\nCodigo: %d", carrinho[i].produto.codigo);
        printf("\nQuantidade: %d", carrinho[i].quantidade);
        printf("\nPeso unitario: %.2f kg", carrinho[i].produto.peso);
        printf("\nPreco unitario: R$ %.2f", carrinho[i].produto.preco);
        printf("\nSubtotal: R$ %.2f", subtotalItem);
    }

    printf("\n\n----------------------------------------------");
    printf("\nSubtotal: R$ %.2f",
           calcularSubtotal(carrinho, totalItens));

    printf("\nPeso total: %.2f kg",
           calcularPesoTotal(carrinho, totalItens));

    printf("\n==============================================\n");
}

float calcularSubtotal(ItemCarrinho carrinho[], int totalItens) {
    float subtotal = 0;
    int i;

    for (i = 0; i < totalItens; i++) {
        subtotal +=
            carrinho[i].produto.preco *
            carrinho[i].quantidade;
    }

    return subtotal;
}

float calcularPesoTotal(ItemCarrinho carrinho[], int totalItens) {
    float peso = 0;
    int i;

    for (i = 0; i < totalItens; i++) {
        peso +=
            carrinho[i].produto.peso *
            carrinho[i].quantidade;
    }

    return peso;
}

int escolherRegiao() {
    int regiao;

    printf("\n==============================================");
    printf("\n              REGIAO DE ENTREGA");
    printf("\n==============================================");

    printf("\n[1] Sul");
    printf("\n[2] Sudeste");
    printf("\n[3] Norte");
    printf("\n[4] Nordeste");

    do {
        printf("\n\nDigite a regiao (1, 2, 3 ou 4): ");
        scanf("%d", &regiao);

        if (regiao < 1 || regiao > 4) {
            printf("\nRegiao invalida.");
        }

    } while (regiao < 1 || regiao > 4);

    return regiao;
}

float calcularFrete(int regiao, float peso) {
    float frete = 0;

    switch (regiao) {

        case 1:
            if (peso > 2)
                frete = 50;
            else
                frete = 30;
            break;

        case 2:
            if (peso > 2)
                frete = 45;
            else
                frete = 25;
            break;

        case 3:
            if (peso > 2)
                frete = 55;
            else
                frete = 35;
            break;

        case 4:
            if (peso > 2)
                frete = 60;
            else
                frete = 40;
            break;
    }

  
    return frete;

}

void  ExibirFrete(frete){
    printf("\nO Frete para essa regiao é  : %d",frete);
    return frete;
}

float calcularTotal(float subtotal, float frete) {
    return subtotal + frete;
}

void escolherPagamento(
    float total,
    int *formaPagamento,
    int *parcelas,
    char numeroCartao[]
) {
    int i;
    int valido;

    printf("\n==============================================");
    printf("\n                PAGAMENTO");
    printf("\n==============================================");

    printf("\nValor total: R$ %.2f", total);

    printf("\n\n[1] PIX");
    printf("\n[2] Debito");
    printf("\n[3] Credito");

    do {
        printf("\n\nEscolha a forma de pagamento: ");
        scanf("%d", formaPagamento);

        if (*formaPagamento < 1 || *formaPagamento > 3) {
            printf("\nOpcao invalida.");
        }

    } while (*formaPagamento < 1 || *formaPagamento > 3);

    if (*formaPagamento == 1) {

        *parcelas = 1;

        strcpy(numeroCartao, "Nao se aplica");

        printf("\nPagamento selecionado: PIX\n");
    }

    else {

        do {
            printf("\nDigite o numero do cartao: ");
            scanf("%19s", numeroCartao);

            valido = 1;

            if (
                strlen(numeroCartao) < 13 ||
                strlen(numeroCartao) > 19
            ) {
                valido = 0;
            }

            for (
                i = 0;
                i < (int)strlen(numeroCartao);
                i++
            ) {
                if (!isdigit(
                    (unsigned char)numeroCartao[i]
                )) {
                    valido = 0;
                    break;
                }
            }

            if (!valido) {
                printf(
                    "\nNumero de cartao invalido. "
                    "Digite de 13 a 19 numeros.\n"
                );
            }

        } while (!valido);

        if (*formaPagamento == 2) {

            *parcelas = 1;

            printf("\nPagamento selecionado: Debito\n");
        }

        else {

            do {
                printf(
                    "\nEscolha o numero de parcelas "
                    "(1 a 12): "
                );

                scanf("%d", parcelas);

                if (*parcelas < 1 || *parcelas > 12) {
                    printf("\nNumero de parcelas invalido.");
                }

            } while (*parcelas < 1 || *parcelas > 12);

            printf("\nPagamento selecionado: Credito");
            printf("\nParcelas: %d", *parcelas);
            printf(
                "\nValor de cada parcela: R$ %.2f\n",
                total / *parcelas
            );
        }
    }
}

void exibirResumo(
    ItemCarrinho carrinho[],
    int totalItens,
    int regiao,
    float frete,
    float total,
    int formaPagamento,
    int parcelas,
    char numeroCartao[],
    struct tm *dataCompra,
    struct tm *dataEntrega
) {
    int i;
    char cartaoExibicao[30];

    if (strcmp(numeroCartao, "Nao se aplica") == 0) {
        strcpy(cartaoExibicao, "Nao se aplica");
    }
    else {
        sprintf(
            cartaoExibicao,
            "**** **** **** %s",
            &numeroCartao[strlen(numeroCartao) - 4]
        );
    }

    printf("\n\n==============================================");
    printf("\n                RESUMO DA COMPRA");
    printf("\n==============================================");

    for (i = 0; i < totalItens; i++) {

        printf("\n\nProduto %d", i + 1);
        printf("\nCodigo: %d", carrinho[i].produto.codigo);
        printf("\nNome: %s", carrinho[i].produto.nome);
        printf("\nPeso: %.2f kg", carrinho[i].produto.peso);
        printf("\nQuantidade: %d", carrinho[i].quantidade);
        printf(
            "\nPreco unitario: R$ %.2f",
            carrinho[i].produto.preco
        );
        printf(
            "\nSubtotal: R$ %.2f",
            carrinho[i].produto.preco *
            carrinho[i].quantidade
        );
    }

    printf("\n\n----------------------------------------------");

    printf("\nRegiao de entrega: ");

    switch (regiao) {

        case 1:
            printf("Sul");
            break;

        case 2:
            printf("Sudeste");
            break;

        case 3:
            printf("Norte");
            break;

        case 4:
            printf("Nordeste");
            break;
    }

    printf("\nFrete: R$ %.2f", frete);
    printf("\nTotal da compra: R$ %.2f", total);

    printf("\nForma de pagamento: ");

    switch (formaPagamento) {

        case 1:
            printf("PIX");
            break;

        case 2:
            printf("Debito");
            break;

        case 3:
            printf("Credito");
            break;
    }

    if (formaPagamento == 3) {

        printf("\nParcelas: %d", parcelas);

        printf(
            "\nValor de cada parcela: R$ %.2f",
            total / parcelas
        );
    }

    if (
        formaPagamento == 2 ||
        formaPagamento == 3
    ) {
        printf("\nCartao: %s", cartaoExibicao);
    }

    printf(
        "\n\nData da compra: %02d/%02d/%04d",
        dataCompra->tm_mday,
        dataCompra->tm_mon + 1,
        dataCompra->tm_year + 1900
    );

    printf(
        "\nHorario da compra: %02d:%02d:%02d",
        dataCompra->tm_hour,
        dataCompra->tm_min,
        dataCompra->tm_sec
    );

    printf(
        "\nData prevista de entrega: %02d/%02d/%04d",
        dataEntrega->tm_mday,
        dataEntrega->tm_mon + 1,
        dataEntrega->tm_year + 1900
    );

    printf("\n==============================================\n");
}
