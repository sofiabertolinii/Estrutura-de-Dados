typedef struct no No;

void lst_cria (No ** inicio);
void lst_libera (No** inicio);

void lst_insere_comeco (No** inicio, int i);
void lst_insere_ordenado (No** inicio, int v);
void lst_insere_final (No** inicio, int v);

No* lst_busca (No* inicio, int v);

int lst_conta_menores (No* inicio, int v);

void lst_retira (No** inicio, int v);
void lst_retira_rec (No** no, int v);

void lst_imprime (No* inicio);
void lst_imprime_rec (No* no);

int lst_igual (No* n1, No* n2);
int lst_igual_rec (No* n1, No* n2);
