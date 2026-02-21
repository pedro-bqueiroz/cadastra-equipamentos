#ifndef MAX_TAM
#define MAX_TAM 31
#define MAX_EQUIPAMENTOS 256

typedef struct {
    char tipo[MAX_TAM]; // Categoria do equipamento. Exemplos: "Fonte", "Multímetro"
    float tensaoNominal; // Tensão nominal do equipamento, em Volts
    float correnteMaxima; // Corrente de curto-circuito do aparelho, em Amperes
    int Potencia; // Consumo estimado de energia do aparelho, em Watts
}EspecificacoesTecnicas;

typedef struct {
    int ano, utilizacao, quantidade, codigo;
    char serie[MAX_TAM];
    float valor; // Valor de mercado
    char nome[MAX_TAM], fabricante[MAX_TAM];
    EspecificacoesTecnicas t_specs;
}Equipamentos;

int loginSenha();
int configurarLoginSenha(int nivelAcesso);
void listarUsuarios(int nivelAcesso);
int modificarEquipamento(Equipamentos vetor[], int *n, int nivelAcesso);
void adicionarEquipamento(Equipamentos vetor[], int *n, int nivelAcesso);
void editarEquipamento(Equipamentos vetor[], int *n, int nivelAcesso);
void removerEquipamento(Equipamentos vetor[], int *n, int nivelAcesso);
void listarEquipamentos(Equipamentos vetor[], int *n, int nivelAcesso);
void buscarPorFabricante(Equipamentos vetor[], int *n, int nivelAcesso);
void listarEquipamentosEmUso(Equipamentos vetor[], int *n, int nivelAcesso);
void listarEquipamentosDisponiveis(Equipamentos vetor[], int *n, int nivelAcesso);
void salvarDadosEmArquivo(Equipamentos vetor[], int *n, int nivelAcesso);
void carregarDadosDoArquivo(Equipamentos vetor[], int *n, int nivelAcesso);
void orcamentoReposicao(Equipamentos vetor[], int *n, int nivelAcesso);
#endif
