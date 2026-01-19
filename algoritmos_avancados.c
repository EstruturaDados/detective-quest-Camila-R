#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_LENGTH 10

/* =========================================================
   ESTRUTURAS
   ========================================================= */

// Nó da árvore de cômodos
typedef struct Node {
    char name[50];
    char tip[100];
    struct Node* left;
    struct Node* right;
} Node;

// Nó da árvore BST de pistas coletadas
typedef struct TipNode {
    char tip[100];
    struct TipNode* left;
    struct TipNode* right;
} TipNode;

// Nó da tabela hash (pista -> suspeito)
typedef struct HashNode {
    char tip[100];      
    char suspect[100]; 
    struct HashNode* next;
} HashNode;

// Tabela hash
HashNode* hashTable[TABLE_LENGTH];

/* =========================================================
   FUNÇÕES DE CÔMODOS
   ========================================================= */

// cria dinamicamente um cômodo
Node* createRoom(const char* name, const char* tip) {
    Node* room = (Node*)malloc(sizeof(Node));

    if (room == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    strcpy(room->name, name);

    if (tip != NULL)
        strcpy(room->tip, tip);
    else
        room->tip[0] = '\0';

    room->left = NULL;
    room->right = NULL;

    return room;
}

/* =========================================================
   FUNÇÕES DE PISTAS (BST)
   ========================================================= */

// insere pista em ordem alfabética (BST)
TipNode* insertTip(TipNode* root, const char* tip) {
    if (root == NULL) {
        TipNode* node = (TipNode*)malloc(sizeof(TipNode));
        strcpy(node->tip, tip);
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    if (strcmp(tip, root->tip) < 0)
        root->left = insertTip(root->left, tip);
    else if (strcmp(tip, root->tip) > 0)
        root->right = insertTip(root->right, tip);

    return root;
}

// exibe pistas em ordem alfabética
void viewTips(TipNode* root) {
    if (root == NULL) return;

    viewTips(root->left);
    printf("- %s\n", root->tip);
    viewTips(root->right);
}

/* =========================================================
   FUNÇÕES DE HASH
   ========================================================= */

// função hash simples
int hashFunction(const char* key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++)
        sum += key[i];
    return sum % TABLE_LENGTH;
}

// insere associação pista -> suspeito
void insertOnHash(const char* tip, const char* suspect) {
    int index = hashFunction(tip);

    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    strcpy(node->tip, tip);
    strcpy(node->suspect, suspect);

    node->next = hashTable[index];
    hashTable[index] = node;
}

// busca suspeito associado a uma pista
const char* findSuspect(const char* tip) {
    int index = hashFunction(tip);
    HashNode* current = hashTable[index];

    while (current != NULL) {
        if (strcmp(current->tip, tip) == 0)
            return current->suspect;
        current = current->next;
    }
    return NULL;
}

/* =========================================================
   EXPLORAÇÃO DA MANSÃO
   ========================================================= */

void exploreRooms(Node* room, TipNode** tipsCollected) {

    if (room == NULL) return;

    printf("\n==============================\n");
    printf("Você está em: %s\n", room->name);
    printf("==============================\n");

    // coleta pista automaticamente
    if (strlen(room->tip) > 0 && strcmp(room->tip, "Nenhuma pista") != 0) {
        printf("🔍 Pista encontrada: %s\n", room->tip);
        *tipsCollected = insertTip(*tipsCollected, room->tip);
        room->tip[0] = '\0'; // evita coleta duplicada
    }

    printf("\nEscolha um caminho:\n");
    if (room->left)  printf("E - Esquerda\n");
    if (room->right) printf("D - Direita\n");
    printf("S - Sair\n");
    printf("Opção: ");

    char choice;
    scanf(" %c", &choice);

    if (choice == 'E' || choice == 'e')
        exploreRooms(room->left, tipsCollected);
    else if (choice == 'D' || choice == 'd')
        exploreRooms(room->right, tipsCollected);
    else if (choice == 'S' || choice == 's')
        printf("\nVocê saiu da mansão.\n");
    else {
        printf("Opção inválida!\n");
        exploreRooms(room, tipsCollected);
    }
}

/* =========================================================
   JULGAMENTO FINAL
   ========================================================= */

int countEvidence(TipNode* root, const char* accused) {
    if (root == NULL) return 0;

    int count = 0;

    count += countEvidence(root->left, accused);

    const char* suspect = findSuspect(root->tip);
    if (suspect && strcmp(suspect, accused) == 0)
        count++;

    count += countEvidence(root->right, accused);

    return count;
}

void verifyFinalSuspect(TipNode* tipsCollected) {
    char accused[100];

    printf("\nQuem você acusa? ");
    scanf(" %[^\n]", accused);

    int evidence = countEvidence(tipsCollected, accused);

    if (evidence >= 2)
        printf("\n🔴 VEREDITO: %s é CULPADO (%d pistas).\n", accused, evidence);
    else
        printf("\n⚪ VEREDITO: provas insuficientes contra %s (%d pista(s)).\n",
               accused, evidence);
}

/* =========================================================
   MAIN
   ========================================================= */

int main() {

    // inicializa tabela hash
    for (int i = 0; i < TABLE_LENGTH; i++)
        hashTable[i] = NULL;

    printf("=== Bem-vindo ao Detective Quest ===\n");

    // Montagem da mansão
    Node* root = createRoom("Jardim", "Nenhuma pista");

    root->left  = createRoom("Hall de entrada", "Pegadas de lama");
    root->right = createRoom("Garagem", "Nenhuma pista");

    root->left->left  = createRoom("Cozinha", "Faca suja de sangue");
    root->left->right = createRoom("Escada", "Papel picado");

    root->right->left  = createRoom("Oficina", "Chave de fenda");
    root->right->right = createRoom("Lavanderia", "Camiseta suja de sangue");

    root->left->left->left  = createRoom("Sala de jantar", "Taça de vinho com batom");
    root->left->left->right = createRoom("Despensa", "Nenhuma pista");

    root->left->right->left  = createRoom("Quarto", "Remédio em comprimido");
    root->left->right->right = createRoom("Biblioteca", "Livro sobre remédios");

    root->right->left->left  = createRoom("Lavabo", "Pia suja de sangue");
    root->right->left->right = createRoom("Sala de jogos", "Nenhuma pista");

    root->left->left->left->right = createRoom("Sala de estar", "Almofadas bagunçadas");

    // associa pistas a suspeitos
    insertOnHash("Faca suja de sangue", "Marido");
    insertOnHash("Pia suja de sangue", "Marido");
    insertOnHash("Taça de vinho com batom", "Esposa");
    insertOnHash("Livro sobre remédios", "Esposa");
    insertOnHash("Chave de fenda", "Jardineiro");

    TipNode* tipsCollected = NULL;

    // exploração
    exploreRooms(root, &tipsCollected);

    // relatório final
    printf("\n📂 Pistas coletadas:\n");
    viewTips(tipsCollected);

    verifyFinalSuspect(tipsCollected);

    return 0;
}
