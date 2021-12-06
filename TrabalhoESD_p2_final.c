#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int ID_PESSOA = 1;
int ID_FRIENDLIST = 1;

typedef struct pessoa
{
    int id;
    char nome[200];
    char sobrenome[200];
    char cpf[200];
} pessoa;

typedef struct pessoa_no
{
    pessoa *pessoa;
    struct pessoa_no *dir;
    struct pessoa_no *esq;
} pessoa_no;

typedef struct friendlist_no
{
    pessoa *pessoa;
    struct friendlist_no *prox;
} friendlist_no;

typedef struct lfriendlist_no{
    int id;
    char nome[200];
    friendlist_no *pessoas;
    struct lfriendlist_no *prox;
} lfriendlist_no;

pessoa *cadastrarPessoa()
{
    pessoa *novaPessoa;
    int i = 0;
    novaPessoa = malloc(sizeof(pessoa));

    novaPessoa->id = ID_PESSOA;
    ID_PESSOA++;
    printf("ID da pessoa: %d\n", novaPessoa->id);

    printf("Digite o nome da pessoa: ");

    fflush(stdin);
    fgets(novaPessoa->nome, 200, stdin);
    i = 0;
    while (novaPessoa->nome[i] != 0)
    {
        if (novaPessoa->nome[i] == '\n')
            novaPessoa->nome[i] = 0;
        i++;
    }

    printf("Digite o sobrenome: ");

    fflush(stdin);
    fgets(novaPessoa->sobrenome, 200, stdin);
    i = 0;
    while (novaPessoa->sobrenome[i] != 0)
    {
        if (novaPessoa->sobrenome[i] == '\n')
            novaPessoa->sobrenome[i] = 0;
        i++;
    }

    printf("Digite o cpf: ");

    fflush(stdin);
    fgets(novaPessoa->cpf, 200, stdin);
    i = 0;
    while (novaPessoa->cpf[i] != 0)
    {
        if (novaPessoa->cpf[i] == '\n')
            novaPessoa->cpf[i] = 0;
        i++;
    }
    return novaPessoa;
}

pessoa_no *insereArvorePessoas(pessoa_no *raiz, pessoa *pessoa)
{
    // Aloca um novo nó da árvore
    pessoa_no *novo = malloc(sizeof(pessoa_no));
    novo->pessoa = pessoa;
    novo->dir = NULL;
    novo->esq = NULL;

    if (raiz == NULL)
    {
        return novo;
    }
    else
    {

        int id_raiz = raiz->pessoa->id;
        int id = pessoa->id;

        if (id < id_raiz)
        {
            raiz->esq = insereArvorePessoas(raiz->esq, pessoa);
        }
        else
        {
            raiz->dir = insereArvorePessoas(raiz->dir, pessoa);
        }

        return raiz;
    }
}

void listarPessoasRecursivo(pessoa_no *ini)
{
    if (ini)
    {
        listarPessoasRecursivo(ini->esq);
        printf("\n");
        printf("==============\n");
        printf("ID da Pessoa: %d\n", ini->pessoa->id);
        printf("Nome:       %s\n", ini->pessoa->nome);
        printf("Sobrenome:  %s\n", ini->pessoa->sobrenome);
        printf("cpf:        %s\n", ini->pessoa->cpf);
        printf("==============\n");
        listarPessoasRecursivo(ini->dir);
    }
}

void listarPessoas(pessoa_no *ini)
{
    printf("\nLista das Pessoas: \n");
    listarPessoasRecursivo(ini);
}

friendlist_no *adicionarNovaPessoa(friendlist_no *pessoasPList, pessoa *novaPessoa)
{
    friendlist_no *novoNo = malloc(sizeof(friendlist_no));
    novoNo->pessoa = novaPessoa;

    if (pessoasPList == NULL)
    {
        novoNo->prox = novoNo;
        return novoNo;
    }
    else
    {
        friendlist_no *aux = pessoasPList;

        while (aux->prox != pessoasPList)
        {
            aux = aux->prox;
        }

        aux->prox = novoNo;
        novoNo->prox = pessoasPList;

        return pessoasPList;
    }
}

pessoa_no *acharPessoa(pessoa_no *raiz, int pessoaID)
{

    if (raiz == NULL)
    {
        return NULL;
    }

    int raizID = raiz->pessoa->id;

    if (raizID == pessoaID)
    {
        return raiz;
    }
    else
    {
        if (pessoaID < raizID)
        {
            return acharPessoa(raiz->esq, pessoaID);
        }
        else
        {
            return acharPessoa(raiz->dir, pessoaID);
        }
    }

    return NULL;
}

lfriendlist_no *cadastrarFriendlist(pessoa_no *listarPessoas)
{
    int i = 0;

    lfriendlist_no *novaFriendlist;
    novaFriendlist = malloc(sizeof(lfriendlist_no));

    novaFriendlist->id = ID_FRIENDLIST;
    ID_FRIENDLIST++;
    printf("ID da FriendList: %d\n", novaFriendlist->id);

    printf("Digite o nome da nova friendList: ");
    fflush(stdin);
    fgets(novaFriendlist->nome, 200, stdin);

    i = 0;
    while (novaFriendlist->nome[i] != 0)
    {
        if (novaFriendlist->nome[i] == '\n')
            novaFriendlist->nome[i] = 0;
        i++;
    }

    friendlist_no *pessoaPList = NULL;

    int pessoaID = 0;
    printf("Digite na sequencia os IDs das pessoas da nova friendlist, digite -1 no final: ");

    while (1)
    {
        scanf("%d", &pessoaID);

        if (pessoaID == -1)
        {
            break;
        }

        pessoa *pessoaSelec = acharPessoa(listarPessoas, pessoaID)->pessoa;

        if (pessoaSelec != NULL)
        {
            pessoaSelec = adicionarNovaPessoa(pessoaPList, pessoaSelec);
        }
        else
        {
            printf("Essa pessoa nao existe!\n");
        }
    }

    novaFriendlist->pessoas = pessoaPList;

    novaFriendlist->prox = NULL;

    return novaFriendlist;
}

void insereListaFriendlists(lfriendlist_no *cabeca, lfriendlist_no *novaFriendlist)
{
    novaFriendlist->prox = cabeca->prox;
    cabeca->prox = novaFriendlist;
}

void listarTodasFriendlists(lfriendlist_no *ini)
{
    ini = ini->prox;

    printf("\nLista das Friendlists: \n");
    while (ini)
    {
        printf("ID da Friendlist: %d\n", ini->id);
        printf("Nome: %s\n\n", ini->nome);

        friendlist_no *comeco = ini->pessoas;
        friendlist_no *aux = comeco;

        if (comeco != NULL)
        {
            do
            {
                printf("%d ", aux->pessoa->id);
                aux = aux->prox;
            } while (aux != comeco);
        }

        printf("\n");

        ini = ini->prox;
    }
}

lfriendlist_no *acharFriendlist(lfriendlist_no *listaFriendlists, int friendlistID)
{
    listaFriendlists = listaFriendlists->prox;

    while (listaFriendlists != NULL)
    {
        if (listaFriendlists->id == friendlistID)
        {
            return listaFriendlists;
        }
        else
        {
            listaFriendlists = listaFriendlists->prox;
        }
    }

    return NULL;
}

void exibirFriendlist(lfriendlist_no *listaFriendlists)
{
    int friendlistID = -1;

    printf("Digite o ID da Friendlist: ");
    scanf("%d", &friendlistID);

    lfriendlist_no *friendlist = acharFriendlist(listaFriendlists, friendlistID);

    printf("ID da Friendlist: %d\n", friendlist->id);
    printf("Nome: %s\n", friendlist->nome);
    printf("Pessoas:\n");

    friendlist_no *comeco = friendlist->pessoas;
    friendlist_no *pessoas = comeco;

    if (comeco != NULL)
    {
        do
        {
            printf("\tID da Pessoa: %d\n", pessoas->pessoa->id);
            printf("\tNome: %s\n", pessoas->pessoa->nome);
            printf("\tSobrenome: %s\n", pessoas->pessoa->sobrenome);
            printf("\tcpf: %s\n", pessoas->pessoa->cpf);
            printf("\t");
            printf("\n");
            pessoas = pessoas->prox;
        } while (pessoas != comeco);
    }
}

int calculaTamanho(friendlist_no *pessoas)
{
    if (pessoas == NULL)
    {
        return 0;
    }

    friendlist_no *atual = pessoas;
    friendlist_no *comeco = pessoas;

    int i = 1;

    do
    {
        i++;
        atual = atual->prox;
    } while (atual != comeco);

    return i;
}

pessoa_no *removerPessoaRecursivo(pessoa_no *raiz, pessoa_no *pessoa)
{
    if (raiz == pessoa)
    {
        if (raiz->esq == NULL && raiz->dir == NULL)
        { // Sem filhos
            // Só deleta
            free(raiz);
            raiz = NULL;
        }
        else if (raiz->esq == NULL)
        { // Tem filho direito
            // Como uma lista encadeada, o anterior aponta pro prox
            pessoa_no *aux = raiz;
            raiz = raiz->dir;
            free(aux);
        }
        else if (raiz->dir == NULL)
        { // Tem filho esquerdo
            // Como uma lista encadeada, o anterior aponta pro prox
            pessoa_no *aux = raiz;
            raiz = raiz->esq;
            free(aux);
        }
        else
        { // Tem os dois filhos
            // Pegar o menor do lado direito
            pessoa_no *novaRaiz = raiz->dir;

            // Ir até a folha
            while (novaRaiz->esq->esq != NULL)
            {
                novaRaiz = novaRaiz->esq;
            }

            // Temos uma folha

            // Salvar a folha
            pessoa_no *folha = novaRaiz->esq;

            // Remover a folha de seu pai
            novaRaiz->esq = NULL;

            // Reatribuir os filhos
            folha->esq = raiz->esq;
            folha->dir = raiz->dir;

            // Libera a memória do nó da árvore
            free(raiz);

            // Re atribui a raiz para o retorno
            raiz = folha;
        }
    }
    else
    {
        // Caso recursivo
        int raizID = raiz->pessoa->id;
        int pessoaID = pessoa->pessoa->id;

        // Decide se vai remover na esquerda ou direita
        if (pessoaID < raizID)
        {
            raiz->esq = removerPessoaRecursivo(raiz->esq, pessoa);
        }
        else
        {
            raiz->dir = removerPessoaRecursivo(raiz->dir, pessoa);
        }
    }

    return raiz;
}

pessoa_no *removerPessoa(pessoa_no *raiz, lfriendlist_no *listaFriendlists)
{
    int pessoaID = -1;

    printf("Digite o ID da pessoa: ");
    scanf("%d", &pessoaID);

    pessoa_no *pessoa = acharPessoa(raiz, pessoaID);

    if (pessoa == NULL)
    {
        printf("Pessoa nao existe!\n");
        return NULL;
    }

    // Remove da playlists, igual antess
    listaFriendlists = listaFriendlists->prox;
    while (listaFriendlists)
    {

        friendlist_no *atual = listaFriendlists->pessoas;
        friendlist_no *comeco = listaFriendlists->pessoas;

        do
        {
            if (atual->prox->pessoa == pessoa->pessoa)
            {
                friendlist_no *prox = atual->prox;
                atual->prox = prox->prox;

                if (prox == comeco)
                {
                    listaFriendlists->pessoas = comeco->prox;
                }

                if (atual == prox)
                {
                    listaFriendlists->pessoas = NULL;
                }

                free(prox);
                break;
            }
            atual = atual->prox;
        } while (atual != comeco);

        listaFriendlists = listaFriendlists->prox;
    }

    // Remove da árvore
    return removerPessoaRecursivo(raiz, pessoa);
}

void menuPrincipal(pessoa_no *arvorePessoas, lfriendlist_no *listaFriendlists)
{
    int opc;

    do
    {
        printf("\n########## MENU ##########\n\n");
        printf("1 - Cadastrar Pessoa.\n");
        printf("2 - Listar todas as pessoas.\n");
        printf("3 - Remover pessoa.\n");
        printf("4 - Criar friendlist.\n");
        printf("5 - Listar todas as friendlists\n");
        printf("6 - Exibir amigos da friendlist.\n");
        printf("7 - Sair.\n\n");
        printf("Digite a opcao: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            arvorePessoas = insereArvorePessoas(arvorePessoas, cadastrarPessoa());
            break;
        case 2:
            listarPessoas(arvorePessoas);
            break;
        case 3:
            arvorePessoas = removerPessoa(arvorePessoas, listaFriendlists);
            break;
        case 4:
            insereListaFriendlists(listaFriendlists, cadastrarFriendlist(arvorePessoas));
            break;
        case 5:
            listarTodasFriendlists(listaFriendlists);
            break;
        case 6:
            exibirFriendlist(listaFriendlists);
            break;
        case 7:
            break;
        default:
            printf("Opcao invalida!");
            break;
        }
    } while (opc != 7);
}

pessoa_no *cria_arvore_pessoa()
{
    // A árvore não tem nó cabeça, só retorna NULL
    return NULL;
}

lfriendlist_no *cria_lista_friendlist()
{
    lfriendlist_no *cabeca = malloc(sizeof(lfriendlist_no));

    cabeca->id = -1;
    cabeca->nome[0] = '\0';
    cabeca->pessoas = NULL;
    cabeca->prox = NULL;

    return cabeca;
}

int main()
{
    srand(time(NULL));

    pessoa_no *arvorePessoas = cria_arvore_pessoa();
    lfriendlist_no *listaFriendlists = cria_lista_friendlist();

    menuPrincipal(arvorePessoas, listaFriendlists);

    return 0;
}
