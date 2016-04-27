# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAX 10000
# define INFINIT 999999

typedef struct no {
  int chave;
  struct no *fesq;
  struct no *fdir;
}no;

int raiz[MAX][MAX] = {0};
int chaves[MAX] = {0};
float probabilidades[MAX] = {0}, ficticias[MAX] = {0}, e[MAX][MAX] = {0}, w[MAX][MAX] = {0};
int length, auxiliar = 0;
no *tree;

void input();
void optimalBst();
no* buildTree(int , int );
void DISPLAY(no *ROOT);

int main(){

  input();

  optimalBst();

  tree = buildTree(0,length);

  DISPLAY(tree);

  return 0;
}

void input(){
  int i,j;

  scanf("%d",&length);
  
  for(i = 1; i <= length; scanf("%d",&chaves[i]), i++);

  for(i = 1; i <= length; scanf("%f",&probabilidades[i]), i++);

  for(i = 0; i <= length; scanf("%f",&ficticias[i]), i++);
}

void optimalBst(){
  int linha, l, j, r, i;
  float t;

  for (linha = 0; linha <= length; linha++) {
    e[linha][linha] = ficticias[linha];
    w[linha][linha] = ficticias[linha];
  }
  for (l = 2; l <= length+1; l++){
    for (i = 0; i <= (length - l+1); i++){
      j = i+l-1;
      e[i][j] = INFINIT;
      w[i][j] = w[i][j-1] + probabilidades[j] + ficticias[j];
      for (r = i+1; r <= j; r++) {
        t = e[i][r-1] + e[r][j] + w[i][j];
        if (t < e[i][j]){
          e[i][j] = t;
          raiz[i][j] = r;
        }
      }
    }
  }
}

no* buildTree(int i, int j){
  no *tmp;

  if(i == j){
    tmp = (struct no*)malloc(sizeof(struct no));
    tmp->chave = auxiliar;
    tmp->fesq = NULL;
    tmp->fdir = NULL;
    auxiliar++;
  }
  else{
    tmp = (struct no*)malloc(sizeof(struct no));
    tmp->chave = chaves[raiz[i][j]];
    tmp->fesq = buildTree(i,raiz[i][j] - 1);
    tmp->fdir = buildTree(raiz[i][j],j);
  }
  return tmp;
}

void DISPLAY(no *ROOT)
{
  int i;
  if(ROOT != 0)
  {
    DISPLAY(ROOT->fesq);
    if (ROOT->fesq != NULL && ROOT->fdir != NULL){
      if(ROOT->fesq->fesq == NULL && ROOT->fdir->fdir != NULL ){
        printf("chave: %d fesq: d%d fdir: %d\n", ROOT->chave, ROOT->fesq->chave, ROOT->fdir->chave);
      }else if (ROOT->fesq->fesq != NULL && ROOT->fdir->fdir == NULL){
        printf("chave: %d fesq: %d fdir: d%d\n", ROOT->chave, ROOT->fesq->chave, ROOT->fdir->chave);
      }
      else if (ROOT->fesq->fesq == NULL && ROOT->fdir->fesq == NULL){
        printf("chave: %d fesq: d%d fdir: d%d\n", ROOT->chave, ROOT->fesq->chave, ROOT->fdir->chave);
      }
      else
        printf("chave: %d fesq: %d fdir: %d\n", ROOT->chave, ROOT->fesq->chave, ROOT->fdir->chave);
    }
    else if(ROOT->fesq == NULL && ROOT->fdir == NULL){
      printf("chave: d%d fesq: nil fdir: nil\n", ROOT->chave);
    }
    DISPLAY(ROOT->fdir);
  }
}
