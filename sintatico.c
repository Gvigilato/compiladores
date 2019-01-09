#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>



int Token(char buffer[])
{
        char pReservado[13][8]={"id","num","inicio","fim",";",":=","leia","(",")","escreva",",",":","int"}; // vetor com as palavras reservadas da linguagem
        char Ops[3][1]={"+","-","*"};
        int i=0; // variavel de contagem
        int k=0; // variavel de parada das estruturas de repetição
        //int j=0;
        int tipo=0; // tipo de retorno

        do /*certa*/
        {
            if(strcmp(pReservado[i], buffer) == 0) //verifico se é palavra reservada
            {
                tipo = i+1;
                k=1;
            }
            i++;

        }while(i<13 && k!=1);
        if(k==0)//certo
        {
            i=0;
            do
            {
                if(Ops[i][0] == buffer[0] && buffer[1]== '\0') //verifica se é operador
                {
                    tipo=i+14;
                    k=1;
                }
                i++;
            }while(i<3 && k!= 1);
        }
        if(k == 0)// outras verificações
        {
            int i=0;
            if(buffer[0] >= 'a' && buffer[0] <= 'z' || buffer[0] >= 'A' && buffer[0] <= 'Z') // verifica se é identificador criado pelo usuario
            {
                do
                {
                    if(buffer[i] >='0' && buffer[i] <='9' || buffer[i] >= 'a' && buffer[i] <= 'z' || buffer[i] >= 'A' && buffer[i] <= 'Z') // verifico se todos são cacteres validos para id de usuario
                    {
                        i++;
                    }
                    else // caso n paro a execução da função e retorno como erro de id
                    {
                        k=1;
                        tipo = 0;
                    }
                }while(buffer[i]!= '\0' && k!=1);
                if(k==0) //  se n existe erro retorno como saida o valor equivalente ao token
                {
                    tipo = 18;
                    k=1;
                }
            }
            else if(buffer[0] >='0' && buffer[0] <='9') //  caso o primeiro seja um valor numerico
            {
                do
                {
                    while(buffer[i] >='0' && buffer[i] <='9' || buffer[i] == '.' || buffer[i] == ',') //  verifica se entre os numeros existem apenas pontos e virgulas
                    {
                        if(buffer[i] == '.' || buffer [i] == ',') // caso exista ponto e virgula levanto é atribuido a saida de erro numerico
                        {
                            tipo =-1;
                        }
                        i++;
                    }
                    if(buffer[i] != '\0') // verifico se o buffer no indice i não esta no \o existe ao menos 1 caracter que n é numérico, ponto ou virgula retorno como erro de id
                    {
                        k=1;
                        tipo =0;
                    }
                    if(tipo == -1)// se existe ponto ou virgula erro numero flag de parada recebe 1;
                    {
                        k=1;
                    }
                }while(buffer[i]!= '\0' && k!=1);//certo
                if(k==0) //  se a flag de parada n for 1 o valor é valido
                {
                    tipo = 18;
                }
            }
            if(buffer[0] == '-' && k==0)
            {
                i=1;
                do
                {
                    while(buffer[i] >='0' && buffer[i] <='9' || buffer[i] == '.' || buffer[i] == ',') //  verifica se entre os numeros existem apenas pontos e virgulas
                    {
                        i++;
                    }
                    if(buffer[i] == '\0') // se chegar até o fim do buffer existem apenas numeros pontos e virgulos nesse caso o erro é numerico
                    {
                        tipo = -1;
                    }
                    else // caso contrario o erro é de id de usuario
                    {
                        k=1;
                        tipo =0;
                    }

                }while(buffer[i]!= '\0' && k!=1);//certo

            }

        }
            return tipo;
}
typedef struct elemento
{
    int linha;
    char token[30];
    struct elemento* prox;
}no;
typedef struct
{
    no* inicio;
}LD;

void definirLD (LD* L)
{
    L->inicio = NULL;
}

void inserir(LD *L, no* novo) // sempre insere no final da lista
{
    no* aux;
    aux = L->inicio;
    if(L->inicio == NULL)
    {
        novo->prox = L->inicio;
        L->inicio = novo;
    }
    else
    {
        while(aux->prox != NULL)
        {
            aux = aux->prox;
        }
        novo->prox = aux->prox;
        aux->prox = novo;
    }
}
int Imprimirchaves (LD *L)
{
    no* aux;
    aux=L->inicio;
    if(L->inicio == NULL)
    {
        return (-1);
    }
    while(aux->prox!=NULL)
    {
        printf("<%s,%d> ",aux->token,aux->linha);
        aux=aux->prox;
    }
    return(1);
}
// implementação da pilha
typedef struct
{
    no* topo;

}Pilha;
void definirP(Pilha *P)
{
    P->topo = NULL;
}
no* desempilha(Pilha *P)
{
    no* aux;
    no* push;
    aux = P->topo;
    push = P->topo;
    aux = push->prox;
    P->topo = aux;
    return(push);
}
void empilha(Pilha *P, no *novo)
{
        novo->prox = P->topo;
        P->topo = novo;

}

void mostraPilha(Pilha *P)
{
    no* aux;
    aux = P->topo;
    while(aux != NULL)
    {
        printf("%s ",aux->token);
        aux = aux->prox;
    }
}


int main()
{
        char buffer[20]= "\0";
        char ch;
        int linhas = 1;
        int x =0;
        int i=0;
        int contComen=0;
        LD ListaT;
        definirLD(&ListaT);
        no* saida;
       // x = Token(Buffer);
        //printf(" saida: %d",x);
        FILE *fp;
        fp = fopen("entrada.txt","r");
        if(fp == NULL)
        {
                printf("arquivo vazio");
                exit(0);
        }
        int j=0;
        while((ch = fgetc(fp)) != EOF) // ler char a char até o fim do arquivo
        {
            if(ch != ' ' && ch != '\n' ) // verifico se n é um espaço ou um pulo de linha e  armazeno na string buffer
            {
                buffer[i] = ch;
                i++;
            }
            else if(ch == ' ' || ch == '\n' ) //  se chegar em um pulo de linhas ou um espaço eu reseto o contador do buffer para armazenar a proximas palavra
            {
                buffer[i] = '\0'; // finalizando a string do buffer caso ache um espaço
                if(buffer[0] == '/' && buffer[1] == '*' && contComen==0) // verifica o inicio dos comentarios
                {
                    contComen =1;
                }
                else if(buffer[1] == '/' && buffer[0] == '*' && contComen ==1) //verifica o fim dos comentarios
                {
                    contComen = 0;
                }
                if(contComen == 0 && buffer[0] != '*' &&  buffer[1] != '/')// verificando se o flag de comentario esta baixo e se o caracter do buffer não é a finalização de um comentario
                {
                    x= Token(buffer); // aqui eu analiso o tipo de entrada dada no buffer
                    saida = malloc(sizeof(no));
                    if(x==1)
                    {
                        strcpy(saida->token,"ID");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==2)
                    {
                        strcpy(saida->token,"NUM");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==3)
                    {
                        strcpy(saida->token,"INI");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==4)
                    {
                        strcpy(saida->token,"FIM");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==5)
                    {
                        strcpy(saida->token,"PONTVIG");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==6)
                    {
                        strcpy(saida->token,"ATRIB");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==7)
                    {
                        strcpy(saida->token,"LEIA");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==8)
                    {
                        strcpy(saida->token,"APAR");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==9)
                    {
                        strcpy(saida->token,"FPAR");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==10)
                    {
                        strcpy(saida->token,"ESCREV");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==11)
                    {
                        strcpy(saida->token,"VIRG");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==12)
                    {
                        strcpy(saida->token,"DOISP");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==13)
                    {
                        strcpy(saida->token,"INT");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==14)
                    {
                        strcpy(saida->token,"ADD");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==15)
                    {
                        strcpy(saida->token,"SUB");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==16)
                    {
                        strcpy(saida->token,"MULT");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==17)
                    {
                        strcpy(saida->token,"NUM");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==18)
                    {
                        strcpy(saida->token,"USERID");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==0)
                    {
                        printf("<  ERRO USERID ,%d > ",linhas);
                    }
                    else if(x==-1)
                    {
                        printf("< ERRO NUMERICO ,%d > ",linhas);
                    }
                }
                    i=0; // contador do buffer resetado
                    if(ch == '\n')
                    {
                        linhas ++; // caso seja um pulo de linha eu incremento o contador de linhas
                    }
            }
        }
        if(contComen == 0 && (buffer[0] != '*' &&  buffer[1] != '/') ||  (buffer[0] != '/' &&  buffer[1] != '*')) //para o ultimo caracter
        {
            buffer[i] = '\0';
            saida = malloc(sizeof(no));
            if(x==1)
                    {
                        strcpy(saida->token,"ID");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==2)
                    {
                        strcpy(saida->token,"NUM");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==3)
                    {
                        strcpy(saida->token,"INI");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==4)
                    {
                        strcpy(saida->token,"FIM");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==5)
                    {
                        strcpy(saida->token,"PONTVIG");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==6)
                    {
                        strcpy(saida->token,"ATRIB");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==7)
                    {
                        strcpy(saida->token,"LEIA");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==8)
                    {
                        strcpy(saida->token,"APAR");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==9)
                    {
                        strcpy(saida->token,"FPAR");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==10)
                    {
                        strcpy(saida->token,"ESCREV");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==11)
                    {
                        strcpy(saida->token,"VIRG");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==12)
                    {
                        strcpy(saida->token,"DOISP");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==13)
                    {
                        strcpy(saida->token,"INT");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==14)
                    {
                        strcpy(saida->token,"ADD");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==15)
                    {
                        strcpy(saida->token,"SUB");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==16)
                    {
                        strcpy(saida->token,"MULT");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==17)
                    {
                        strcpy(saida->token,"NUM");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==18)
                    {
                        strcpy(saida->token,"USERID");
                        saida->linha = (linhas);
                        inserir(&ListaT,saida);
                    }
                    else if(x==0)
                    {
                        printf("< ERRO NUMERICO ,%d >",linhas);
                    }
                    else if(x==-1)
                    {
                        printf("< ERRO USERID , %d >",linhas);
                    }
        }
        printf("\n");
        strcpy(saida->token,"$");
        saida = malloc(sizeof(no));
        inserir(&ListaT,saida);
        free(saida);
        Imprimirchaves(&ListaT);



       //----------------------------------------------------------------------------------------------------------------------------------------
       //----------------------------------------------------------------------------------------------------------------------------------------
       //----------------------------------------------------------------------------------------------------------------------------------------

       /*analisador sintatico trab 2*/

       Pilha P;
       definirP(&P);
       no* topo;
       no* aux;
       no*Fita;
       int erro = 0;
       topo = malloc(sizeof(no));
       strcpy(topo->token,"$");
       empilha(&P,topo);
       topo = malloc(sizeof(no));
       strcpy(topo->token,"<PROGRAMA>");
        empilha(&P,topo);
        aux = P.topo;
        Fita = ListaT.inicio;
        int certo;

        //


        while(certo!=1 && erro!=1)
        {
                mostraPilha(&P);
                printf("\n");
                printf("%s",Fita->token);
                printf("\n");
            if(strcmp(aux->token,"<PROGRAMA>") == 0 && strcmp(Fita->token,"INI") == 0)
            {
                topo = desempilha(&P);
                free(topo);
                topo = malloc(sizeof(no));
                strcpy(topo->token,"FIM");
                empilha(&P,topo);
                topo = malloc(sizeof(no));
                strcpy(topo->token,"PONTVIG");
                empilha(&P,topo);
                topo = malloc(sizeof(no));
                strcpy(topo->token,"<COMANDOS>");
                empilha(&P,topo);
                topo = malloc(sizeof(no));
                strcpy(topo->token,"PONTVIG");
                empilha(&P,topo);
                topo = malloc(sizeof(no));
                strcpy(topo->token,"<DECL_SEQUENCIA>");
                empilha(&P,topo);
                topo = malloc(sizeof(no));
                strcpy(topo->token,"INI");
                empilha(&P,topo);
               // mostraPilha(&P);
                aux = P.topo;
            }
            else if(strcmp(aux->token,Fita->token)== 0)
            {
                if(strcmp(aux->token,"$") == 0 && strcmp(Fita->token,"$") == 0)
                {
                    certo = 1;
                }
                else
                {
                    desempilha(&P);
                    Fita=Fita->prox;
                    aux =P.topo;
                }

               // printf("%s",Fita->token);
               // printf("\n");
               // mostraPilha(&P);
            }
            else if(strcmp(aux->token,"<DECL_SEQUENCIA>") == 0 && strcmp(Fita->token,"INT") == 0)
            {
                topo = desempilha(&P);
                free(topo);
                topo = malloc(sizeof(no));
                strcpy(topo->token,"<DECL>");
                empilha(&P,topo);
                topo = malloc(sizeof(no));
                strcpy(topo->token,"DOISP");
                empilha(&P,topo);
                topo = malloc(sizeof(no));
                strcpy(topo->token,"INT");
                empilha(&P,topo);
                aux = P.topo;
                //printf("\n");
                //mostraPilha(&P);
            }
             else if(strcmp(aux->token,"<DECL>") == 0 && strcmp(Fita->token,"USERID") == 0)
             {
                topo = desempilha(&P);
                free(topo);
                topo = malloc(sizeof(no));
                strcpy(topo->token,"<DECL2>");
                empilha(&P,topo);
                topo = malloc(sizeof(no));
                strcpy(topo->token,"USERID");
                empilha(&P,topo);
                aux = P.topo;

             }
             else if(strcmp(aux->token,"<DECL2>") == 0 && strcmp(Fita->token,"PONTVIG") == 0)
             {

                topo = desempilha(&P);
                free(topo);
                aux = P.topo;
             }
             else if(strcmp(aux->token,"<DECL2>") == 0 && strcmp(Fita->token,"VIRG") == 0)
             {
                topo = desempilha(&P);
                free(topo);
                topo = malloc(sizeof(no));
                strcpy(topo->token,"<DECL>");
                empilha(&P,topo);
                topo = malloc(sizeof(no));
                strcpy(topo->token,"VIRG");
                empilha(&P,topo);
                aux = P.topo;
             }
             else if(strcmp(aux->token,"<COMANDOS>") == 0 && strcmp(Fita->token,"ESCREV") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<COMANDOS2>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<COMANDO>");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<COMANDOS>") == 0 && strcmp(Fita->token,"LEIA") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<COMANDOS2>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<COMANDO>");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<COMANDOS>") == 0 && strcmp(Fita->token,"USERID") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<COMANDOS2>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<COMANDO>");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<COMANDOS2>") == 0 && strcmp(Fita->token,"PONTVIG") == 0)
             {
                 topo = Fita->prox;
                 if(strcmp(topo->token,"LEIA") == 0 || strcmp(topo->token,"ESCREV") == 0 || strcmp(topo->token,"USERID")== 0)
                 {
                        topo = desempilha(&P);
                        free(topo);
                        topo = malloc(sizeof(no));
                        strcpy(topo->token,"<COMANDOS2>");
                        empilha(&P,topo);
                        topo = malloc(sizeof(no));
                        strcpy(topo->token,"<COMANDOS>");
                        empilha(&P,topo);
                        topo = malloc(sizeof(no));
                        strcpy(topo->token,"PONTVIG");
                        empilha(&P,topo);
                        aux = P.topo;
                 }
                 else
                 {
                        topo = desempilha(&P);
                        free(topo);
                        aux = P.topo;
                 }
             }
             else if(strcmp(aux->token,"<COMANDO>") == 0 && strcmp(Fita->token,"ESCREV") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"FPAR");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"USERID");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"APAR");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"ESCREV");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<COMANDO>") == 0 && strcmp(Fita->token,"LEIA") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"FPAR");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"USERID");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"APAR");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"LEIA");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<COMANDO>") == 0 && strcmp(Fita->token,"USERID") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP1>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"ATRIB");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"USERID");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP1>") == 0 && strcmp(Fita->token,"USERID") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP1'>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP2>");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP1>") == 0 && strcmp(Fita->token,"APAR") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP1'>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP2>");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP1>") == 0 && strcmp(Fita->token,"NUM") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP1'>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP2>");
                    empilha(&P,topo);
                    aux = P.topo;
             }
              else if(strcmp(aux->token,"<EXP1'>") == 0 && strcmp(Fita->token,"PONTVIG") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP1'>") == 0 && strcmp(Fita->token,"FPAR") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP1'>") == 0 && strcmp(Fita->token,"ADD") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP1'>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP2>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"ADD");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP1'>") == 0 && strcmp(Fita->token,"SUB") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP1'>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP2>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"SUB");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP2>") == 0 && strcmp(Fita->token,"APAR") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP2'>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP3>");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP2>") == 0 && strcmp(Fita->token,"NUM") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP2'>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP3>");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP2>") == 0 && strcmp(Fita->token,"USERID") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP2'>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP3>");
                    empilha(&P,topo);
                    aux = P.topo;
             }
              else if(strcmp(aux->token,"<EXP2'>") == 0 && strcmp(Fita->token,"FPAR") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    aux = P.topo;
             }
              else if(strcmp(aux->token,"<EXP2'>") == 0 && strcmp(Fita->token,"ADD") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    aux = P.topo;
             }
              else if(strcmp(aux->token,"<EXP2'>") == 0 && strcmp(Fita->token,"SUB") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP2'>") == 0 && strcmp(Fita->token,"PONTVIG") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP2'>") == 0 && strcmp(Fita->token,"MULT") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP2'>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP3>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"MULT");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP3>") == 0 && strcmp(Fita->token,"USERID") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"USERID");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP3>") == 0 && strcmp(Fita->token,"APAR") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"FPAR");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"<EXP1>");
                    empilha(&P,topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"APAR");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP3>") == 0 && strcmp(Fita->token,"NUM") == 0)
             {
                    topo = desempilha(&P);
                    free(topo);
                    topo = malloc(sizeof(no));
                    strcpy(topo->token,"NUM");
                    empilha(&P,topo);
                    aux = P.topo;
             }
             else if(strcmp(aux->token,"<EXP3>") == 0 && strcmp(Fita->token,"NUM") == 0)
             {

             }
             else
             {
                 erro = 1;

             }
             if(certo ==1 )
             {
                 printf("aceito");
             }
             else if(erro ==1)
             {
                 printf("erro");
             }
        }
    return 0;
}

