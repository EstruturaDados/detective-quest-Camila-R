#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da árvore (cômodo da mansão)
typedef struct Node
{
    char name[50];
    struct Node* left;
    struct Node* right;
} Node;

// Cria dinamicamente uma sala da mansão
Node* createRoom(char* name){
    Node* room = (Node*)malloc(sizeof(Node));

    if (room == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    strcpy(room->name, name);
    room->left = NULL;
    room->right = NULL;

    return room;
};

// Função para explorar os cômodos da mansão
void exploreRooms(struct Node* room){

    if(room == NULL){
        return;
    }

    printf("=====\n");
    printf("Você está aqui: %s\n", room->name);
    printf("=====\n");

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
        exploreRooms(room->left);
    } else if(choice == 'D' || choice == 'd'){
        exploreRooms(room->right);
    } else if(choice == 'S' || choice == 's'){
        printf("Você saiu da mansão\n");
        printf("Obrigado por jogar!\n");
        return;
    }
     else {
        printf("Escolha inválida! Tente novamente.\n");
        exploreRooms(room);
    }   

}

int main() {

    printf("=== Bem-vindo ao Detective Quest! ===\n");

    // Jardim -> Hall de entrada e Garagem
    Node* root = createRoom("Jardim");

    root->left  = createRoom("Hall de entrada");
    root->right = createRoom("Garagem");

    // Hall de entrada -> Cozinha e Escada
    root->left->left  = createRoom("Cozinha");
    root->left->right = createRoom("Escada");

    // Garagem -> Oficina e Lavanderia
    root->right->left  = createRoom("Oficina");
    root->right->right = createRoom("Lavanderia");

    // Cozinha -> Sala de jantar e Despensa
    root->left->left->left  = createRoom("Sala de jantar");
    root->left->left->right = createRoom("Despensa");

    // Escada -> Quarto e Biblioteca
    root->left->right->left  = createRoom("Quarto");
    root->left->right->right = createRoom("Biblioteca");

    // Oficina -> Lavabo e Sala de jogos
    root->right->left->left  = createRoom("Lavabo");
    root->right->left->right = createRoom("Sala de jogos");

    // Sala de jantar -> Lavabo e Sala de estar
    root->left->left->left->left  = createRoom("Lavabo");
    root->left->left->left->right = createRoom("Sala de estar");

    // Quarto -> Banheiro e Closet
    root->left->right->left->left  = createRoom("Banheiro");
    root->left->right->left->right = createRoom("Closet");

    // Biblioteca -> Escritório e Sala de música
    root->left->right->right->left  = createRoom("Escritório");
    root->left->right->right->right = createRoom("Sala de música");

    // Sala de estar -> Terraço e Sala de TV
    root->left->left->left->right->left  = createRoom("Terraço");
    root->left->left->left->right->right = createRoom("Sala de TV");

    // Inicia a exploração
    exploreRooms(root);

    return 0;
}
