#include <stdio.h>
#include <string.h>
#include "evento.h"
#include "menu.h"
#include "components.h"

// Definição da estrutura para armazenar os dados do evento
void criarEvento() {
    Evento evento;
    char p_evento[21]; // Array de caracteres para armazenar o nome do evento
    char p_descricao[51]; // Array de caracteres para armazenar a descrição do evento
    char dataAtual[11];
    int p_status = 1;

    // Solicitar ao usuário que insira os dados do evento
    imprimirTituloCabecario("TELA DE CADASTRO DE EVENTOS",NULL);

    printf("|\tDigite o nome do evento: ");
    scanf(" %20[^\n]", p_evento); // Lê o nome do evento
    printf("|\tDigite uma descricao para o evento: ");
    scanf(" %50[^\n]", p_descricao); // Lê a descrição do evento
    imprimirLinhaDivisoria();

    // Preencher a estrutura do evento com os dados inseridos
    evento.id = carregarUltimoEvento() ; // Incrementar o ID do último evento
    strcpy(evento.evento, p_evento);
    strcpy(evento.descricao, p_descricao);
    obterDataAtual(dataAtual);
    strcpy(evento.data, dataAtual);
    evento.status = p_status;
    salvarEvento(evento);
}

void listarEventos() {
    FILE *file;
    char filename[] = "data/eventos.txt";
    file = fopen(filename, "r");

    if (file != NULL) {

        imprimirRodape();
        imprimirTituloCabecario("LISTA DE EVENTOS", NULL);

        printf("| %-3s | %-20s | %-57s | %-10s | %-10s |\n", "Cod", "Evento", "Descricao", "Data", "Status");
        imprimirLinhaDivisoria();

        // Variável para armazenar cada registro lido do arquivo
        Evento evento;

        // Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d '%[^']' '%[^']' %s %d", &evento.id, evento.evento, evento.descricao, evento.data, &evento.status) != EOF) {
            char status[10];
            if(evento.id == 0) continue;
            if(evento.status == 1){
                strcpy(status, "Ativo");
            } else {
                strcpy(status, "Desativo");
            }
            printf("| %-3d | %-20s | %-57s | %-10s | %-10s |\n", evento.id, evento.evento, evento.descricao, evento.data, status);
        }
        imprimirLinhaDivisoria();
        fclose(file);
    } else {
        printf("Não foi possível abrir o arquivo %s.\n\n", filename);
    }
}

void listarEventosCadastro() {
    FILE *file;
    char filename[] = "data/eventos.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        imprimirTituloCabecario("LISTA DE EVENTOS", NULL);

        printf("| %-3s | %-20s | %-57s | %-10s | %-10s |\n", "Cod", "Evento", "Descricao", "Data", "Status");
        imprimirLinhaDivisoria();

        // Variável para armazenar cada registro lido do arquivo
        Evento evento;

        // Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d '%[^']' '%[^']' %s %d", &evento.id, evento.evento, evento.descricao, evento.data, &evento.status) != EOF) {
            char status[10];
            if(evento.id == 0) continue;
            if(evento.status == 1){
                strcpy(status, "Ativo");
            } else {
                strcpy(status, "Desativo");
            }
            if(evento.status == 0){
                continue;
            } else {
                printf("| %-10d | %-100s |\n", evento.id, evento.evento);
            }
        }
        imprimirLinhaDivisoria();
        fclose(file);
    } else {
        printf("Não foi possível abrir o arquivo %s.\n\n", filename);
    }
}

int carregarUltimoEvento() {
    FILE *file;
    char filename[] = "data/eventos.txt";
    file = fopen(filename, "r");

    int contador_linhas = 0;

    if (file != NULL) {
        int c;
        // Percorrer o arquivo caractere por caractere
        while ((c = fgetc(file)) != EOF) {
            if (c == '\n') {
                ++contador_linhas;
            }
        }
        fclose(file);
        //printf("|\tRegistro(s): %d\n", contador_linhas);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    return contador_linhas+1;
}

void salvarEvento(Evento evento) {
    FILE *file;
    char filename[] = "data/eventos.txt";
    file = fopen(filename, "a"); // Abrir o arquivo em modo de escrita, acrescentando ao final

    if (file != NULL) {
        fprintf(file, "%d '%s' '%s' %s %d\n", evento.id, evento.evento, evento.descricao, evento.data, evento.status);
        fclose(file);
        printf("Evento salvo com sucesso!\n");
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }
}

