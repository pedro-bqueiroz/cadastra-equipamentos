#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cadastra_equipamentos.h"

int loginSenha(){ // Estabelece restrições de acesso a funções do programa
    int nivel = 0;
    char login[MAX_TAM], senha[MAX_TAM], loginarq[MAX_TAM], senhaarq[MAX_TAM];

    FILE *arq2 = fopen("loginSenha.txt", "r"); // Tentativa de abrir o arquivo
    
    while (arq2 == NULL){
        fprintf(stderr, "Não há arquivo de login e senha. Deseja criar um? S/N\n");
        char confirmacao;
        scanf("\n%c", &confirmacao);
        if (confirmacao == 'n' || confirmacao == 'N'){
            fprintf(stdout, "Saindo do Cadastra-Equipamentos...");
            return -1;
        }
        else if (confirmacao == 's' || confirmacao == 'S'){
            arq2 = fopen("loginSenha.txt", "w");
            fclose(arq2);
            fprintf(stdout, "Arquivo criado com sucesso.\n");
            break;
        }
        else {
            fprintf(stderr, "Opção inválida.\n");
        }

    fprintf(stderr, "Erro ao abrir o arquivo. Peça assistência a um administrador.\n");

    return -1;
    }

    fprintf(stdout, "Em suspeita de alteração não permitida, peça assistência a um administrador.\n");
    fprintf(stdout, "Insira seu login e senha. Digite 'c' em ambos para sair.\n");
    fprintf(stdout, "Login:\n");

    fgets(login, sizeof(login), stdin);

    if(strlen(login) > MAX_TAM - 1) {
        fprintf(stderr, "Login muito longo. Tente novamente.\n");
        return 0;
    }

    login[strcspn(login, "\r\n")] = 0;
    if (strcmp(login, "ICE CREAM") == 0){
        fprintf(stdout, "Bem vindo, administrador.\n");
        fclose(arq2);
        return 3;
    }

    fprintf(stdout, "Senha:\n");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = 0;

    if(strlen(senha) > MAX_TAM - 1) {
        fprintf(stderr, "Senha muito longa. Tente novamente.\n");
        return 0;
    }

    while (fscanf(arq2, "%s %s %d", loginarq, senhaarq, &nivel) == 3) {
       if (strcmp(login, loginarq) == 0 && strcmp(senha, senhaarq) == 0) {
            fprintf(stdout, "Nível de acesso: %d\n", nivel);
            fclose(arq2);
            return nivel;
        }
        if (login == "c" || login == "C"){
            nivel = 0;
            break;
        }
        fprintf(stderr, "Login ou senha incorretos. Tente novamente.\n");
    }

    fclose(arq2);
    return 0;
}

int configurarLoginSenha(int nivelAcesso){ //Oferece opções internas de configuração de usuários
    if (nivelAcesso < 3) {
        fprintf(stderr, "Acesso negado. Nível de acesso insuficiente.\n");
        return 0;
    }
}

void listarUsuarios(int nivelAcesso){
    int niv = 0;
    char login[MAX_TAM], senha[MAX_TAM];

    if (nivelAcesso < 2) {
        fprintf(stderr, "\nAcesso negado. Nível de acesso insuficiente.\n");
        return;
    }

    FILE *arq2 = fopen("loginSenha.txt", "r");

    if (arq2 == NULL) {
        fprintf(stderr, "\nErro ao abrir o arquivo. Peça assistência a um administrador.\n");
        return;
    }

    while (fscanf(arq2, "%s %s %d", login, senha, &niv) == 3) {
        if (nivelAcesso < niv) {
            fprintf(stdout, "\nLogin: %s\tSenha: %s\t*\t", login, senha);
            continue;
        } else {
            fprintf(stdout, "\nLogin: %s\tSenha: %s\t Nível: %d\t", login, senha, niv);
        }
    }

    fclose(arq2);
}

void modificarEquipamento(Equipamentos vetor[], int *n, int nivelAcesso){ // Será chamada em adicionarEquipamento() ou editarEquipamento(). O nível de acesso é verificado aqui, e não nas outras duas.
     if (nivelAcesso < 2) {
        fprintf(stderr, "Acesso negado. Nível de acesso insuficiente.\n");
        return;
    }
    Equipamentos *cadastro = (Equipamentos *) malloc (sizeof(Equipamentos));
    char confirmacao;
    int ano, utilizacao, codigo;
    float valor, tensao, corrente;
    float Potencia;
    char tipo[MAX_TAM], nome[MAX_TAM], fabricante[MAX_TAM], serie[MAX_TAM];

    fprintf(stdout, "Código do equipamento, entre 0 e 99999: ");
    scanf("%d", &codigo);
    if (codigo < 0 || codigo > 99999) {
        fprintf(stderr, "Código inválido!\n");
        free(cadastro);
        return;
    }
    getchar();

    fprintf(stdout, "Nome do equipamento: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\r\n")] = 0;

    fprintf(stdout, "Fabricante: ");
    fgets(fabricante, sizeof(fabricante), stdin);
    fabricante[strcspn(fabricante, "\r\n")] = 0;

    fprintf(stdout, "Ano de fabricação: ");
    scanf("%d", &ano);
    if (ano < 0 || ano > 9999) {
        fprintf(stderr, "Ano inválido!\n");
        free(cadastro);
        return;
    }
    getchar();

    fprintf(stdout, "Utilização (digite 0 caso desocupado ou 1 caso ocupado): ");
    scanf("%d", &utilizacao);
    if (utilizacao != 0 && utilizacao != 1) {
        fprintf(stderr, "Valor inválido!\n");
        free(cadastro);
        return;
    }
    while(getchar() != '\n');

    fprintf(stdout, "Valor de mercado (em Reais, com ponto): ");
    scanf("%f", &valor);
    while(getchar() != '\n');

    fprintf(stdout, "Número de série: ");
    fgets(serie, sizeof(serie), stdin);
    serie[strcspn(serie, "\r\n")] = 0;

    fprintf(stdout, "Tipo (exemplo: multímetro): ");
    fgets(tipo, sizeof(tipo), stdin);
    tipo[strcspn(tipo, "\r\n")] = 0;

    fprintf(stdout, "Tensão (em Volts): "); 
    scanf("%f", &tensao);
    while(getchar() != '\n');

    fprintf(stdout, "Corrente (em Amperes): ");
    scanf("%f", &corrente);
    while(getchar() != '\n');

    fprintf(stdout, "Potência (em Watts): ");
    scanf("%f", &Potencia);

    fprintf(stdout, "\nConfirma? S/N\n");

    scanf(" %c", &confirmacao);

    if (confirmacao == 's' || confirmacao == 'S'){
        cadastro->codigo = codigo;
        cadastro->ano = ano;
        cadastro->t_specs.correnteMaxima = corrente;
        cadastro->t_specs.Potencia = Potencia;
        strcpy(cadastro->nome, nome);
        strcpy(cadastro->t_specs.tipo, tipo);
        cadastro->utilizacao = utilizacao;
        strcpy(cadastro->fabricante, fabricante);
        strcpy(cadastro->serie, serie);
        cadastro->valor = valor;
        cadastro->t_specs.tensaoNominal = tensao;
        vetor[*n] = *cadastro; //define a posição n do vetor(ambos definidos no main) como o equipamento salvo.
        (*n)++; //soma um ao n, indicando que outro equipamento foi adicionado ao sistema.
    }
    
    else if (confirmacao == 'n' || confirmacao == 'N'){
        free(cadastro);
        return;
    }

    else if (confirmacao != 's' && confirmacao !='n' && confirmacao != 'S' && confirmacao != 'N'){
        fprintf(stderr, "Opção inválida. Tente novamente.");
    }
    free(cadastro);
    return;
}

void adicionarEquipamento(Equipamentos vetor[], int *n, int nivelAcesso){
    fprintf(stdout, "\nPara adicionar o equipamento, informe:\n");
    modificarEquipamento(vetor, n, nivelAcesso);
    fprintf(stdout, "\nVocê adicionou o equipamento %d.\n", *n);
    return;
}

void editarEquipamento(Equipamentos vetor[], int *n, int nivelAcesso){
    int numero;
    char confirmacao;
    
    if (*n == 0) {
        printf("\nNão há equipamentos a serem editados.\n");
        return;
    }

    printf("\nQual o número do equipamento que você quer editar?\n");
    scanf("%i", &numero);
    printf("\nPara editar o equipamento, informe:\n");

    modificarEquipamento(vetor, n, nivelAcesso); 
    
    numero -=1; //atualiza o índice do equipamento no vetor
    fprintf(stdout,"O número atual do equipamento %d é %d.", numero+1, numero);
    return;
}

void recursao(Equipamentos vetor[], int num, int n){ // Função recursiva usada em removerEquipamento().
    if (num >= (n-1)) return;
    vetor[num] = vetor[num+1];
    recursao(vetor, num+1, n); //Desloca, para a esquerda, os valores a partir do index escolhido, assim, alterando a disposição dos elementos.
}

void removerEquipamento(Equipamentos vetor[], int *n, int nivelAcesso){
    if (nivelAcesso < 2) {
        fprintf(stderr, "Acesso negado. Nível de acesso insuficiente.\n");
        return;
    }
    int numero;
    listarEquipamentos(vetor, n, nivelAcesso);
    
    if (*n > 0){
        fprintf(stdout, "\nQual dos equipamentos voce quer excluir?\n");
        recursao(vetor, numero, *n);
        *n-=1; //elemento excluído.
        scanf("%i", &numero); //Define o equipamento a ser excluído
        numero -= 1; //Ajusta o valor escolhido para um index no vetor
    }
}

void listarEquipamentos(Equipamentos vetor[], int *n, int nivelAcesso){
    if (nivelAcesso < 1) {
        fprintf(stderr, "Acesso negado. Nível de acesso insuficiente.\n");
        return;
    }
    if (*n == 0) {
        fprintf(stdout, "\nSem equipamentos cadastrados\n");
        return ;
    }

    fprintf(stdout, "\n-Lista de equipamentos:-\n");

    //percorre o vetor de equipamentos, mostando na tela suas características
    for (int i = 0; i < *n; i++) {
        fprintf(stdout, "\n-------- Equipamento %d --------\n\n", i+1);
        fprintf(stdout, "\tCodigo: %d\n", vetor[i].codigo);
        fprintf(stdout, "\tNome: %s\n", vetor[i].nome);
        fprintf(stdout, "\tFabricante: %s\n", vetor[i].fabricante);
        fprintf(stdout, "\tAno: %d\n", vetor[i].ano);
        fprintf(stdout, "\tUtilização: %d\n", vetor[i].utilizacao);
        fprintf(stdout, "\tValor: %.2f\n", vetor[i].valor);
        fprintf(stdout, "\tNumero de serie: %s\n", vetor[i].serie);
        fprintf(stdout, "\tTipo: %s\n", vetor[i].t_specs.tipo);
        fprintf(stdout, "\tVoltagem de operacao: %.2f V\n", vetor[i].t_specs.tensaoNominal);
        fprintf(stdout, "\tCorrente maxima: %.2f A\n", vetor[i].t_specs.correnteMaxima);
        fprintf(stdout, "\tConsumo: %.2f W\n", vetor[i].t_specs.Potencia);
    }

    //caso o valor de n seja 0 significa que não há elementos no vetor, logo não há equipamentos cadastrados
    if (*n == 0) 
        fprintf(stdout, "\nNenhum equipamento cadastrado\n");

}

void buscarPorFabricante(Equipamentos vetor[], int *n, int nivelAcesso){
    if (nivelAcesso < 1) {
        fprintf(stderr, "Acesso negado. Nível de acesso insuficiente.\n");
        return;
    }
    char fab[30];
    char vfab[20][20];
    int t=0;
    
    if (*n == 0) {
        fprintf(stdout, "\nSem equipamentos cadastrados\n");
        return ;
    }

    fprintf(stdout, "\nDigite o fabricante ");
    scanf("%s", fab);
    //Percorre o vetor de equipamentos
    for (int j = 0; j < *n; j++) {
        if (strcmp(fab, vetor[j].fabricante) == 0){
            //Caso o fabricante achado seja igual ao definido pelo usuário(variável fab), ele salva o produto em um vetor.
            strcpy(vfab[t], vetor[j].t_specs.tipo);
            t+=1;
        }
    }

    fprintf(stdout, "\n- produto(s) achado(s) -\n", t);

    //percorre o vetor para mostrar na tela todos os equipamentos condizentes com o fabricante procurado.
    for (int i = 0; i < t; i++) { 
        fprintf(stdout, "\n-------- Equipamento %d --------\n\n", i+1);
        fprintf(stdout, "\tCodigo: %d\n", vetor[i].codigo);
        fprintf(stdout, "\tNome: %s\n", vetor[i].nome);
        fprintf(stdout, "\tAno: %d\n", vetor[i].ano);
        fprintf(stdout, "\tUtilização: %d\n", vetor[i].utilizacao);
        fprintf(stdout, "\tValor: %.2f\n", vetor[i].valor);
        fprintf(stdout, "\tNumero de serie: %s\n", vetor[i].serie);
        fprintf(stdout, "\tTipo: %s\n", vetor[i].t_specs.tipo);
        fprintf(stdout, "\tVoltagem de operacao: %.2f V\n", vetor[i].t_specs.tensaoNominal);
        fprintf(stdout, "\tCorrente maxima: %.2f A\n", vetor[i].t_specs.correnteMaxima);
        fprintf(stdout, "\tConsumo: %.2f W\n", vetor[i].t_specs.Potencia);
    }

    //Se t = 0, não há produtos com esse fabricante no sistema
    if (t == 0) {
        fprintf(stdout, "\nNenhum equipamento do fabricante encontrado\n");
    }
}

void listarEquipamentosEmUso(Equipamentos vetor[], int *n, int nivelAcesso){
    if (nivelAcesso < 1) {
        fprintf(stderr, "Acesso negado. Nível de acesso insuficiente.\n");
        return;
    }
    int j=0; //j é controle, caso seja 0 não há elementos em uso
    
    if (*n == 0) {
        fprintf(stdout, "\nSem equipamentos cadastrados\n");
        return;
    }

    fprintf(stdout, "\n- Produto(s) em uso -\n");

    //percorre o vetor de equipamentos.
    for (int i = 0; i < *n; i++) {
        //verifica se o equipamento, em cada posição do vetor, está em uso.
        if (vetor[i].utilizacao == 1){ 
            fprintf(stdout, "\n-------- Equipamento %d --------\n\n", i+1);
            fprintf(stdout, "\tCodigo: %d\n", vetor[i].codigo);
            fprintf(stdout, "\tNome: %s\n", vetor[i].nome);
            fprintf(stdout, "\tFabricante: %s\n", vetor[i].fabricante);
            fprintf(stdout, "\tAno: %d\n", vetor[i].ano);
            fprintf(stdout, "\tValor: %.2f\n", vetor[i].valor);
            fprintf(stdout, "\tNumero de serie: %s\n", vetor[i].serie);
            fprintf(stdout, "\tTipo: %s\n", vetor[i].t_specs.tipo);
            fprintf(stdout, "\tVoltagem de operacao: %.2f V\n", vetor[i].t_specs.tensaoNominal);
            fprintf(stdout, "\tCorrente maxima: %.2f A\n", vetor[i].t_specs.correnteMaxima);
            fprintf(stdout, "\tConsumo: %.2f W\n", vetor[i].t_specs.Potencia);
            j +=1;
        }
    }

    //se j = 0, sem elementos em uso
    if (j == 0)
        fprintf(stdout, "\nNenhum produto em uso\n");

}

void listarEquipamentosDisponiveis(Equipamentos vetor[], int *n, int nivelAcesso){
    if (nivelAcesso < 1) {
        fprintf(stderr, "Acesso negado. Nível de acesso insuficiente.\n");
        return;
    }
    if (*n == 0) {
        fprintf(stdout, "\nSem equipamentos cadastrados\n");
        return ;
    }

    fprintf(stdout, "\n-produto(s) livre(s)-\n");

    int j=0; //controle, idem ao anterior.
    for (int i = 0; i < *n; i++) {
        //verifica se o equipamento, em uma posição do vetor, está livre.
        if (vetor[i].utilizacao == 0){ 
            fprintf(stdout, "\n-------- Equipamento %d --------\n\n", i+1);
            fprintf(stdout, "\tCodigo: %d\n", vetor[i].codigo);
            fprintf(stdout, "\tNome: %s\n", vetor[i].nome);
            fprintf(stdout, "\tFabricante: %s\n", vetor[i].fabricante);
            fprintf(stdout, "\tAno: %d\n", vetor[i].ano);
            fprintf(stdout, "\tValor: %.2f\n", vetor[i].valor);
            fprintf(stdout, "\tNumero de serie: %s\n", vetor[i].serie);
            fprintf(stdout, "\tTipo: %s\n", vetor[i].t_specs.tipo);
            fprintf(stdout, "\tVoltagem de operacao: %.2f V\n", vetor[i].t_specs.tensaoNominal);
            fprintf(stdout, "\tCorrente maxima: %.2f A\n", vetor[i].t_specs.correnteMaxima);
            fprintf(stdout, "\tConsumo: %.2f W\n", vetor[i].t_specs.Potencia);
            j+=1;
        }
    }

    //se j = 0, não há equipamentos disponíveis.
    if (j == 0)
        fprintf(stdout, "\nNenhum produto livre\n");
    
}

void salvarDadosEmArquivo(Equipamentos vetor[], int *n, int nivelAcesso){
    if (nivelAcesso < 2) {
        fprintf(stderr, "Acesso negado. Nível de acesso insuficiente.\n");
        return;
    }
    const char *nome = "equipamentos.txt";
    FILE *arq = fopen(nome, "w"); //abre o arquivo "equipamentos.txt" no modo de escrita.
    if (arq == NULL) { //verifica se o arquivo existe.
        fprintf(stderr, "Erro ao abrir o arquivo"); //Caso o arquivo não seja encontrado ou por qualquer outra falha, isso é retornado.
    }
    else {
        //caso contrário ele lê o arquivo e salva todos os equipamentos do vetor no arquivo em questão,
        for (int i = 0; i < *n; i++) { 
            fprintf(arq, "%d %s %s %d %d %.2f %s %s %.2f %.2f %.2f\n", vetor[i].codigo, vetor[i].nome, vetor[i].fabricante, vetor[i].ano, vetor[i].utilizacao, vetor[i].valor, vetor[i].serie, vetor[i].t_specs.tipo, vetor[i].t_specs.tensaoNominal, vetor[i].t_specs.correnteMaxima, vetor[i].t_specs.Potencia);
        }
    }
    fclose(arq);
    fprintf(stdout, "\nDados salvos com sucesso\n");
}

void carregarDadosDoArquivo(Equipamentos vetor[], int *n, int nivelAcesso){
    if (nivelAcesso < 1) {
        fprintf(stderr, "Acesso negado. Nível de acesso insuficiente.\n");
        return;
    }
    const char *nome = "equipamentos.txt";
    FILE *arq = fopen(nome, "r"); //abre o arquivo "equipamentos.txt" no modo de leitura;

    if (arq == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo");
    }
    else {
        int i = 0; //variável que vai fazer a contagem de quantos equipamentos há no arquivo
        while (fscanf(arq, "%d %s %s %d %d %f %s %s %f %f %f", &vetor[i].codigo,vetor[i].nome,vetor[i].fabricante,&vetor[i].ano,&vetor[i].utilizacao,&vetor[i].valor,vetor[i].serie,vetor[i].t_specs.tipo,&vetor[i].t_specs.tensaoNominal,&vetor[i].t_specs.correnteMaxima,&vetor[i].t_specs.Potencia) == 11) { //leitura do arquivo.
            //exibe os dados do arquivo
            fprintf(stdout, "\n-------- Equipamento %d --------\n\n", i+1);
            fprintf(stdout, "\tCodigo: %d\n", vetor[i].codigo);
            fprintf(stdout, "\tNome: %s\n", vetor[i].nome);
            fprintf(stdout, "\tFabricante: %s\n", vetor[i].fabricante);
            fprintf(stdout, "\tAno: %d\n", vetor[i].ano);
            fprintf(stdout, "\tUtilizacao: %d\n", vetor[i].utilizacao);
            fprintf(stdout, "\tValor: %.2f\n", vetor[i].valor);
            fprintf(stdout, "\tNumero de serie: %s\n", vetor[i].serie);
            fprintf(stdout, "\tTipo: %s\n", vetor[i].t_specs.tipo);
            fprintf(stdout, "\tVoltagem de operacao: %.2f V\n", vetor[i].t_specs.tensaoNominal);
            fprintf(stdout, "\tCorrente maxima: %.2f A\n", vetor[i].t_specs.correnteMaxima);
            fprintf(stdout, "\tConsumo: %.2f W\n", vetor[i].t_specs.Potencia);

            //Adiciona um ao número de equipamentos presentes.
            i++;
        }
        if (*n == 0 && i != 0) { //verifica se é a primeira execução, pois o valor de n é definido em 0 e caso i seja 0 significa que não há nada, logo não há necessidade de salvar.
            *n = i; //define o número de equipamentos presentes no sistema
            return;
        }
    
    }
    fclose(arq);
}
