#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da árvore (cômodo da mansão)
typedef struct Node
{
    char name[50];
    char tip[100];
    struct Node* left;
    struct Node* right;
} Node;

typedef struct TipNode {
    char tip[100];
    struct TipNode* left;
    struct TipNode* right;
} TipNode;

// Cria dinamicamente uma sala da mansão
Node* createRoom(char* name, char* tip){
    Node* room = (Node*)malloc(sizeof(Node));

    if (room == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    strcpy(room->name, name);

    if(tip){
        strcpy(room->tip, tip);
    } else{
        room->tip[0] = '\0';
    }

    room->left = NULL;
    room->right = NULL;

    return room;
};

//Função para inserir pista em ordem alfabética
TipNode* insertTip(TipNode* root, char* tip){
    if(root == NULL){
        TipNode* new = (TipNode*)malloc(sizeof(TipNode));

        strcpy(new->tip, tip);
        new->left = NULL;
        new->right = NULL;

        return new;
    }

    if(strcmp(tip, root->tip) < 0){
        root->left = insertTip(root->left, tip);
    } else{
        root->right = insertTip(root->right, tip);
    }

    return root;
}

// Função para exibir as pistas
void viewTips(TipNode* root){
    if(root == NULL) return;

    viewTips(root->left);
    printf("- %s\n", root->tip);
    viewTips(root->right);
}

// Função para explorar os cômodos da mansão
void exploreRoomsWithTips(struct Node* room, TipNode** tipsCollected){

    if(room == NULL){
        return;
    }

    printf("=====\n");
    printf("Você está aqui: %s\n", room->name);
    printf("=====\n");

    // Coleta automática da pista
    if(strlen(room->tip) > 0){
        printf("Pista encontrada: %s\n", room->tip);
        *tipsCollected = insertTip(*tipsCollected, room->tip);
        room->tip[0] = '\0';
    }

    // Verifica se é um nó-folha
    if (room->left == NULL && room->right == NULL) {
        printf("Este cômodo não possui mais caminhos.\n");
        printf("Fim da exploração!\n");
        return;
    }

    printf("Escolha um caminho:\n");

    if (room->left != NULL)
    {
        printf("Digite 'E' para ir ao cômodo à esquerda\n");
    }
    
    if (room->right != NULL)
    {
        printf("Digite 'D' para ir ao cômodo à direita\n");
    }
        
    printf("Digite 'S' para sair da mansão\n");
    printf("=====\n");

    char choice;
    scanf(" %c", &choice);

    if(choice == 'E' || choice == 'e'){
        exploreRoomsWithTips(room->left, tipsCollected);
    } else if(choice == 'D' || choice == 'd'){
        exploreRoomsWithTips(room->right, tipsCollected);
    } else if(choice == 'S' || choice == 's'){
        printf("Você saiu da mansão\n");
        printf("Obrigado por jogar!\n");
        return;
    }
     else {
        printf("Escolha inválida! Tente novamente.\n");
        exploreRoomsWithTips(room, tipsCollected);
    }   

}

int main() {

    printf("=== Bem-vindo ao Detective Quest! ===\n");

    // Jardim -> Hall de entrada e Garagem
    Node* root = createRoom("Jardim", "Nenhuma pista");

    root->left  = createRoom("Hall de entrada", "Pegadas de lama");
    root->right = createRoom("Garagem", "Nenhuma pista");

    // Hall de entrada -> Cozinha e Escada
    root->left->left  = createRoom("Cozinha", "Faca suja de sangue");
    root->left->right = createRoom("Escada", "Papel picado");

    // Garagem -> Oficina e Lavanderia
    root->right->left  = createRoom("Oficina", "Chave de fenda");
    root->right->right = createRoom("Lavanderia", "Camiseta suja de sangue");

    // Cozinha -> Sala de jantar e Despensa
    root->left->left->left  = createRoom("Sala de jantar", "Taça de vinho com batom");
    root->left->left->right = createRoom("Despensa", "Nenhuma pista");

    // Escada -> Quarto e Biblioteca
    root->left->right->left  = createRoom("Quarto", "Remédio em comprimido");
    root->left->right->right = createRoom("Biblioteca", "Livro sobre remédios");

    // Oficina -> Lavabo e Sala de jogos
    root->right->left->left  = createRoom("Lavabo", "Pia suja de sangue");
    root->right->left->right = createRoom("Sala de jogos", "Nenhuma pista");

    // Sala de jantar -> Lavabo e Sala de estar
    root->left->left->left->left  = createRoom("Lavabo", "Nenhuma pista");
    root->left->left->left->right = createRoom("Sala de estar", "Almofadas bagunçadas");

    // Quarto -> Banheiro e Closet
    root->left->right->left->left  = createRoom("Banheiro", "Chuveiro sujo de sangue");
    root->left->right->left->right = createRoom("Closet", "Roupas faltando");

    // Biblioteca -> Escritório e Sala de música
    root->left->right->right->left  = createRoom("Escritório", "Computador aberto com e-mail aberto");
    root->left->right->right->right = createRoom("Sala de música", "Nenhuma pista");

    // Sala de estar -> Terraço e Sala de TV
    root->left->left->left->right->left  = createRoom("Terraço", "Nenhuma pista");
    root->left->left->left->right->right = createRoom("Sala de TV", "Televisão ligada");

    TipNode* tipsCollected = NULL;

    // Inicia a exploração
    exploreRoomsWithTips(root, &tipsCollected);

    printf("\nPistas coletadas (ordem alfabética):\n");
    viweTips(tipsCollected);

    return 0;
}
