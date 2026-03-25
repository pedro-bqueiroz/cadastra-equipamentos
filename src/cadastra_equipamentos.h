#ifndef MAX_STRING
#define MAX_STRING 31
#define MAX_EQUIPAMENTOS 256
#define MAX_USUARIOS 32
#define LOGINSENHAMESTRES "ICE CREAM"

typedef struct {
    char login[MAX_STRING];
    char senha[MAX_STRING];
    int nivelAcesso; 
} LoginSenha;

typedef struct {
    char tipo[MAX_STRING]; // Categoria do equipamento. Exemplos: "Fonte", "Multímetro"
    float tensaoNominal; // Tensão nominal do equipamento, em Volts
    float correnteMaxima; // Corrente de curto-circuito do aparelho, em Amperes
    float Potencia; // Consumo estimado de energia do aparelho, em Watts
} EspecificacoesTecnicas;

typedef struct {
    int ano, utilizacao, quantidade, codigo;
    char serie[MAX_STRING]; // Número de série
    float valor; // Valor de mercado
    char nome[MAX_STRING], fabricante[MAX_STRING];
    EspecificacoesTecnicas t_specs;
} Equipamentos;

int loginSenha();
void configurarLoginSenha(int nivelAcesso);
int modificarEquipamento(Equipamentos vetor[], int index, int nivelAcesso);
void adicionarEquipamento(Equipamentos vetor[], int *n, int nivelAcesso);
void editarEquipamento(Equipamentos vetor[], int *n, int nivelAcesso);
void recursao(Equipamentos vetor[], int index, int n);
void removerEquipamento(Equipamentos vetor[], int *n, int nivelAcesso);
int lista(Equipamentos vetor[], int j);
int contaEquipamentos(Equipamentos vetor[]);
void listarEquipamentos(Equipamentos vetor[], int *n, int nivelAcesso);
void buscarPorFabricante(Equipamentos vetor[], int *n, int nivelAcesso);
void listarEquipamentosPorUso(Equipamentos vetor[], int *n, int nivelAcesso);
void salvarDadosEmArquivo(Equipamentos vetor[], int *n, int nivelAcesso);
void carregarDadosDoArquivo(Equipamentos vetor[], int *n, int nivelAcesso);
void abrirOutrosFormatos(Equipamentos vetor[], int *n, int nivelAcesso);
void verificarAlteracoes(Equipamentos vetor[], int *n, int nivelAcesso);
void listarUsuarios(int nivelAcesso);

#endif
