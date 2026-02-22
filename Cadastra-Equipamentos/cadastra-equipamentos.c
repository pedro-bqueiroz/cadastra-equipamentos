#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cadastra_equipamentos.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "Portuguese"); // Configura a localidade para Português do Brasil, garantindo a exibição correta de caracteres acentuados.
    system("cls || clear"); // útil para limpar a tela em sistemas Windows e Unix, respectivamente.

    FILE *arq = fopen("equipamentos.txt", "r"); // será feito um teste de existência do arquivo.
    int n=0; //variável que vai fazer a contagem de quantos equipamentos estão cadastrados, importante para se usar nos loops.
    int confirmacao;
    Equipamentos vetor[256]; //Vetor responsável por armazenar os equipamentos já cadastrados.

    int nivelAcesso = loginSenha();
    if (nivelAcesso == -1) {
        return 0;
    }

    fprintf(stdout, "\nBem vindo ao Cadastra-Equipamentos.\nCertifique-se de que fechou o programa quando for embora!!!\n");

    while (arq == NULL){ //testa se o arquivo existe ou não
        fprintf(stderr, "ATENÇÃO! Não há arquivo .txt a ser aberto. Deseja criar um? S/N ");
        scanf("\n%c", &confirmacao);
        if (confirmacao == 'n' || confirmacao == 'N'){
        fprintf(stdout, "Saindo do Cadastra-Equipamentos...");
        return 0;
        }
        else if (confirmacao == 's' || confirmacao == 'S'){
        arq = fopen("equipamentos.txt", "w");
        fclose(arq);
        }
        else {
        fprintf(stderr, "Opção inválida.\n");
        }
    }
    
    fprintf(stdout, "\nNível de acesso: %d\n", nivelAcesso);

    fprintf(stdout, "Selecione uma das alternativas abaixo:");
    char input;
    do {
        fprintf(stdout, "\n\n1) Adicionar equipamento\n");
        fprintf(stdout, "2) Editar equipamento\n");
        fprintf(stdout, "3) Remover equipamento\n");
        fprintf(stdout, "4) Listar equipamentos\n");
        fprintf(stdout, "5) Buscar por fabricante\n");
        fprintf(stdout, "6) Listar equipamentos em uso\n");
        fprintf(stdout, "7) Listar equipamentos disponiveis\n");
        fprintf(stdout, "8) Salvar dados em arquivo\n");
        fprintf(stdout, "9) Carregar dados do arquivo\n");
        fprintf(stdout, "0) Configurações de login e senha\n");
        fprintf(stdout, "Q) Listar usuários\n");
        fprintf(stdout, "C) Sair do programa\n\n");
        scanf(" %c", &input);
        switch (input){
            case '1':
                adicionarEquipamento(vetor, &n, nivelAcesso);
                break;
            case '2':
                editarEquipamento(vetor, &n, nivelAcesso);
                break;
            case '3':
                removerEquipamento(vetor, &n, nivelAcesso);
                break;
            case '4':
                listarEquipamentos(vetor, &n, nivelAcesso);
                break;
            case '5':
                buscarPorFabricante(vetor, &n, nivelAcesso);
                break;
            case '6':
                listarEquipamentosEmUso(vetor, &n, nivelAcesso);
                break;
            case '7':
                listarEquipamentosDisponiveis(vetor, &n, nivelAcesso);
                break;
            case '8':
                salvarDadosEmArquivo(vetor, &n, nivelAcesso);
                break;
            case '9':
                carregarDadosDoArquivo(vetor, &n, nivelAcesso);
                break;
            case '0':
                configurarLoginSenha(nivelAcesso);
                break;
            case 'q':
            case 'Q':
                listarUsuarios(nivelAcesso);
                break;
            case 'c':
            case 'C':
                fprintf(stdout, "Saindo do programa...");
                break;
            default:
                fprintf(stderr, "Alternativa inválida.\n");
                break;
        }
    } while (input != 'c' && input != 'C');
}