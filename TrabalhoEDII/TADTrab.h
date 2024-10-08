struct TpCode {
	char token[15];
	struct TpCode *prox;
}; typedef struct TpCode TpCode;

struct TpLista {
	struct TpLista *prox, *ant;
	TpCode *tokens;
}; typedef struct TpLista TpLista;

struct TpVariavel{
	char variavel[15];
}; typedef struct TpVariavel TpVariavel;

union TpInfo {
    float valor;
    char operacao[3];
    char funcao[20];
};

struct listagen {
    char terminal;
    union TpInfo info;
    struct listagen *cabeca, *cauda;
}; typedef struct listagen ListaGen;

struct TpTermo {
	char termo[15];
	struct TpTermo *prox;
}; typedef struct TpTermo TpTermo;

struct Pilha {
	ListaGen *info;
	struct Pilha *prox;
}; typedef struct Pilha Pilha;

struct Fila {
	ListaGen *info;
	struct Fila *prox;
}; typedef struct Fila Fila;

struct TpFrase {
	char frase[15];
	struct TpFrase *prox;
}; typedef struct TpFrase TpFrase;

union TpIdentificador {
	char variavel[10];
};

struct PilhaMemoria {
	char terminal;
	union TpIdentificador ident;
	char valor[10];
	TpLista *ponteiro;
	struct PilhaMemoria *prox;
}; typedef struct PilhaMemoria PilhaM;

// struct PilhaVarFuncao {
// 	char variavel[10];
// 	char valor[10];
// 	struct PilhaVarFuncao *prox;
// }; typedef struct PilhaVarFuncao PilhaVF;


//---------------TAD PILHA---------------------

void init(Pilha **p) {
	*p = NULL;
}

void push(Pilha **p, ListaGen *info) {
	Pilha *novo = (Pilha*)malloc(sizeof(Pilha));
	novo->info = info;
	novo->prox = *p;
	*p = novo;
}

void pop(Pilha **p, ListaGen **info) {
	Pilha *aux = *p;
	*info = aux->info;
	*p = aux->prox;
	free(aux);
}

char isEmptyP(Pilha *p) {
	return p == NULL;
}

//-------------TAD PILHA MEMORIA----------------
void initM(PilhaM **p) {
	*p = NULL;
}

void pushM(PilhaM **p, char *variavel, char *valor, TpLista *ponteiro) {
	PilhaM *novo = (PilhaM*)malloc(sizeof(PilhaM));

	novo->terminal = 'V';
	strcpy(novo->ident.variavel, variavel);
	strcpy(novo->valor, valor);
	novo->ponteiro = ponteiro;
	novo->prox = *p;
	*p = novo;
}

// void pushMF(PilhaM **p, TpLista *lista, TpLista *ponteiro) {
// 	PilhaM *novo = (PilhaM*)malloc(sizeof(PilhaM));

// 	novo->terminal = 'F';
// 	novo->ident.pfunc = NULL;
// 	novo.
// 	novo->valor[0] = '\0';
// 	novo->prox = *p;
// 	*p = novo;
// }

char isEmptyM(PilhaM *p) {
	return p == NULL;
}

//--------------TAD PILHA FUNC-----------------

// void initPF(PilhaVF **p) {
// 	*p = NULL;
// }

// void pushPF(PilhaVF **p, char *variavel) {
// 	PilhaVF *novo = (PilhaVF*)malloc(sizeof(PilhaVF));
// 	strcpy(novo->variavel, variavel);
// 	strcpy(novo->valor, "\0");
// 	novo->prox = *p;
// 	*p = novo;
// }

// char isEmptyPF(PilhaVF *p) {
// 	return p == NULL;
// }

// void popPF(PilhaVF **p, char *variavel) {
// 	PilhaVF *aux = *p;
// 	strcpy(variavel, aux->variavel);
// 	*p = aux->prox;
// 	free(aux);
// }

//----------------TAD FILA---------------------

void initF(Fila **f) {
	*f = NULL;
}

void enqueue(Fila **f, ListaGen *info){
	Fila *novo = *f, *aux;
	if (*f == NULL) {
		// A fila esta vazia, inicializa o primeiro no
		*f = (Fila*)malloc(sizeof(Fila));
		(*f)->info = info;
		(*f)->prox = NULL;
	} 
	else {
	    while (novo->prox != NULL) 
	        novo = novo->prox;
	    
	    aux = (Fila*)malloc(sizeof(Fila));
	    aux->info = info;
	    aux->prox = NULL;
		novo->prox = aux;
	}
}

void dequeue (Fila **f, ListaGen **info){
	Fila *aux = *f;
	*info = aux->info;
	*f = aux->prox;
	free(aux);
}

char isEmpty(Fila *f){
	return f == NULL;
}

//----------------------------------------------

int isNumber(char termo[]) {
    int i = 0;
    int decimalPointCount = 0; // Contador para pontos decimais

    // Verifica se o primeiro caractere é um sinal de menos
    if (termo[0] == '-') {
        i = 1; // Começa a verificação a partir do segundo caractere
    }

    for (; termo[i] != '\0'; i++) { // Percorre cada caractere da string até o caractere nulo
        if (!isdigit(termo[i])) { // Se o caractere atual não é um dígito
            if (termo[i] == '.') { // Verifica se é um ponto decimal
                decimalPointCount++;
                if (decimalPointCount > 1) { // Se houver mais de um ponto decimal
                    return 0;
                }
            } else {
                return 0; // Se não for um dígito nem um ponto decimal
            }
        }
    }

    return 1; // Se todos os caracteres forem válidos
}

int isOperation(char termo[]) {
    return (strcmp(termo, "+") == 0 || strcmp(termo, "-") == 0 || 
            strcmp(termo, "*") == 0 || strcmp(termo, "/") == 0 || 
			strcmp(termo, "//") == 0 || strcmp(termo, "**") == 0 ||
			strcmp(termo, "%") == 0);
}

int isFunction(char termo[]) {
    return (strcmp(termo, "math.sqrt") == 0 || strcmp(termo, "math.fabs") == 0);
}

TpTermo *CriaTermo(char termo[]) {
	TpTermo *novo = (TpTermo*)malloc(sizeof(TpTermo));
	strcpy(novo->termo, termo);
	novo->prox = NULL;

	return novo;
}


ListaGen *CriaNo(char termo[]) {
    ListaGen *novo = (ListaGen*)malloc(sizeof(ListaGen));
    novo->cabeca = novo->cauda = NULL;

    if (isNumber(termo)) {
        novo->terminal = 'V';
        novo->info.valor = atof(termo);
    }
	if (isOperation(termo)) {
        novo->terminal = 'O';
        strcpy(novo->info.operacao, termo);
    } 
	if (isFunction(termo)) {
        novo->terminal = 'F';
        strcpy(novo->info.funcao, termo);
    } 
	novo->cabeca = novo->cauda = NULL;
    return novo;
}

char Nula(ListaGen *L) {
	return L == NULL;
}



void CriaL (TpLista **nova) {
	*nova = (TpLista*)malloc(sizeof(TpLista));
	(*nova)->ant = NULL;
	(*nova)->prox = NULL;
	(*nova)->tokens = NULL;
}


void InsereL(TpLista **pProgram) {
	TpLista *aux, *nova;
	CriaL(&nova);
	if(*pProgram == NULL)
		*pProgram = nova;
	
	else
	{
		aux = *pProgram;
		while(aux->prox != NULL)
		{
			aux = aux->prox;
		}
		aux->prox = nova;
		nova->ant = aux;
	}
}

void CriaT (TpCode **nova,char token[15]) {
	*nova = (TpCode*)malloc(sizeof(TpCode));
	strcpy((*nova)->token, token);
	(*nova)->prox = NULL;
}

void InsereT(TpLista **pProgram, TpCode *nova) {
	TpLista *auxL = *pProgram;
	TpCode *aux;
	
	while(auxL->prox != NULL)
		auxL = auxL->prox;

	if(auxL->tokens == NULL)
		auxL->tokens = nova;

	else
	{
		aux = auxL->tokens;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = nova;
	}
}

char VerifVazia(TpLista *pProgram) {
	TpLista *aux = pProgram;
	while(aux->prox != NULL)
		aux = aux->prox;

	if(aux->tokens == NULL)
		return 1;

	else
		return 0;
}

void CarregaL(TpLista **pProgram) {
    FILE *arq;
    int i, j;
    char token[15], nome[15], auxS[80];
    TpCode *nova;
    printf("Digite o nome do arquivo: ");
    scanf("%s", nome);
    arq = fopen(nome, "r");

    if(arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
    }
	else {
        while(fgets(auxS, 80, arq) != NULL) {
			InsereL(pProgram);
			// printf("%s", auxS);

            if(strlen(auxS) == 1 && auxS[0] == '\n') {
                strcpy(token, "fim-def");
                CriaT(&nova, token);
                InsereT(pProgram, nova);
            } 
			else {
				for(i = 0; i < strlen(auxS); i++) {
					// Se o caractere atual for um caractere especial, armazena-o como token separado
					if(auxS[i] == '(' || auxS[i] == ')' || auxS[i] == ',' || auxS[i] == '=' || auxS[i] == '\"' || auxS[i] == '\'') {
						token[0] = auxS[i];  // Armazena o caractere especial
						token[1] = '\0';      // Marca o fim da string do token
						CriaT(&nova, token);  // Cria o token
						InsereT(pProgram, nova);  // Insere o token na lista
					} 
					// Se for uma palavra ou número
					else if(auxS[i] != ' ' && auxS[i] != '\n') {
						for(j = 0; auxS[i] != ' ' && auxS[i] != '\n' && auxS[i] != '(' && auxS[i] != ')' && auxS[i] != ',' && auxS[i] != '=' && auxS[i] != '\"' && auxS[i] != '\''; j++, i++) {
							token[j] = auxS[i];  // Copia o token
						}
						token[j] = '\0';  // Finaliza o token
						CriaT(&nova, token);
						InsereT(pProgram, nova);

						i--;  // Volta uma posição para não pular um caractere após o token especial
					}
					
					// Verifica se o último caractere é uma aspa fechando
					if (i == strlen(auxS) - 1 && (auxS[i] == '\"' || auxS[i] == '\'')) {
						token[0] = auxS[i];
						token[1] = '\0';
						CriaT(&nova, token);
						InsereT(pProgram, nova);
					}
				}
			}
        }
    }
    fclose(arq);
}

void exibe(TpLista *lista) {
	TpLista *auxL = lista;
	TpCode *auxT;

	while(auxL != NULL) {
		auxT = auxL->tokens;
		while(auxT != NULL) {
			printf("%s ", auxT->token);
			auxT = auxT->prox;
		}
		printf("\n");
		auxL = auxL->prox;
	}
}

// Função para identificar se existe uma equação
int identificar_equacao(TpCode *atual, PilhaM *pilha) {
    PilhaM *auxP;
    int contParenteses = 0;

	while(atual != NULL) {
		auxP = pilha;
		if(strcmp(atual->token, "\"") == 0) // se for uma string
			return 0;

		if(strcmp(atual->token, "(") == 0) { // se for um parenteses
			contParenteses++;
			
			if(isOperation(atual->prox->token)) // se o próximo token for uma operação
				return 0;
		}
		if(strcmp(atual->token, ")") == 0) { // se for um parenteses
			contParenteses--;

			if(atual->prox != NULL) {
				if(strcmp(atual->prox->token, ")") != 0) { // se o próximo token não for um parenteses
					if(!isOperation(atual->prox->token)) // se o próximo token for uma operação
						return 0;
				}
			}
		}
		if(isOperation(atual->token)) { // se for uma operação
			if(strcmp(atual->prox->token, "(") != 0) { // se o próximo token não for um parenteses
				if(isOperation(atual->prox->token)) // se o próximo token for uma operação
					return 0;
			}
		}
		else { // se for um numero ou uma variavel
			if(atual->prox != NULL && !isOperation(atual->prox->token)) { // se o próximo token não for uma operação ou termina com null
				if(strcmp(atual->token, "(") != 0 && strcmp(atual->prox->token, ")") != 0) { // se não for parenteses
					if(atual->prox != NULL)
						return 0;
				}
			}
			else { // se for variavel
				if(!isNumber(atual->token)) {
					if(strcmp(atual->token, "(") != 0 && strcmp(atual->token, ")") != 0) { // se não for parenteses
						while(auxP != NULL && strcmp(auxP->ident.variavel, atual->token) != 0) {
							auxP = auxP->prox;
						}
						if(auxP == NULL) // se não encontrar a variável
							return 0;
					}
				}
			}
		}
		atual = atual->prox;
	}
	if(contParenteses != 0) // se o contador de parenteses for diferente de 0
		return 0;

	return 1;
}


TpTermo *separa(char equacao[100], PilhaM *pilhaM) {
	TpTermo *lista = NULL, *atual;
	char termo[15];
	int i = 0, j = 0;

	while(equacao[i] != '\0') {
		if(equacao[i] == ' ') {
			termo[j] = '\0';
			if(lista == NULL) {
				lista = CriaTermo(termo);
				atual = lista;
			}
			else {
				atual->prox = CriaTermo(termo);
				atual = atual->prox;
			}
			j = 0;
		}
		else {
			termo[j] = equacao[i];
			j++;
		}
		i++;
	}
}

float calcula(ListaGen *L) {
	float resultado = 0;
	ListaGen *atual = L;

	// Percorre a lista de nÃ³s
	while (atual != NULL) {
		if (atual->terminal == 'V') { // Se o nÃ³ Ã© um valor
			resultado = atual->info.valor; // Armazena o valor
		} else if (atual->terminal == 'O') { // Se o nÃ³ Ã© uma operaÃ§Ã£o
			float esquerda = resultado; // Calcula o valor do operando esquerdo
			float direita = calcula(atual->cauda); // Calcula o valor do operando direito
			if (strcmp(atual->info.operacao, "+") == 0) {
				resultado = esquerda + direita;
			} else if (strcmp(atual->info.operacao, "-") == 0) {
				resultado = esquerda - direita;
			} else if (strcmp(atual->info.operacao, "*") == 0) {
				resultado = esquerda * direita;
			} else if (strcmp(atual->info.operacao, "/") == 0) {
				resultado = esquerda / direita;
			} else if (strcmp(atual->info.operacao, "//") == 0) {
				resultado = (int)esquerda / (int)direita;
			} else if (strcmp(atual->info.operacao, "**") == 0) {
				resultado = pow(esquerda, direita);
			} else if (strcmp(atual->info.operacao, "%") == 0) {
				resultado = fmod(esquerda, direita);
			}
		} else if (atual->terminal == 'F') { // Se o nÃ³ Ã© uma funÃ§Ã£o
			if (strcmp(atual->info.funcao, "math.sqrt") == 0) {
				resultado = sqrt(calcula(atual->cabeca));
			} else if (strcmp(atual->info.funcao, "math.fabs") == 0) {
				resultado = fabs(calcula(atual->cabeca));
			}
		}
		atual = atual->cauda; // Move para o prÃ³ximo nÃ³
	}

	return resultado; // Retorna o resultado final
}

//Funcao ListaGen para resolver expressoes aritmeticas

float resolve(char equacao[100], PilhaM *pilhaM) {
    float result;
    
    //construir a ListaGen com todas a expressao aritmetica
    Pilha *p;
    ListaGen *L = NULL, *atual;
    Fila *f;
	TpTermo *aux;

    TpTermo *lista = separa(equacao, pilhaM);

	//imprime a lista
	aux = lista;
	while(aux != NULL) {
		printf("%s ", aux->termo);
		aux = aux->prox;
	}

    init(&p);
    initF(&f);

    while(lista != NULL) {
        if(L == NULL)
            L = atual = CriaNo(lista->termo);

        else {
            if(strcmp(lista->termo, "(") == 0) {
                atual->cauda = CriaNo("0");
                atual = atual->cauda;
                lista = lista->prox;
                push(&p, atual);

                atual->cabeca = CriaNo(lista->termo);
                atual = atual->cabeca;
            }
            else
                if(strcmp(lista->termo,")") == 0)
                    pop(&p, &atual);

                else {
                    atual->cauda = CriaNo(lista->termo);
                    atual = atual->cabeca;
                }
		}
        lista = lista->prox;
    }

    //resolvendo a expressao
    push(&p, L);
    enqueue(&f, L);
    
    while(!isEmpty(f)) {
        dequeue(&f, &atual);
        
        while(!Nula(atual)) {
            if(atual->cabeca != NULL) {
                push(&p, atual->cabeca);
                enqueue(&f, atual->cabeca);
            }   
            atual = atual->cauda;
        }
    }

    while(!isEmpty(p)) {
        pop(&p, &atual);
        if(atual != L)
            atual->info.valor = calcula(atual->cabeca);

        else 
            result = calcula(atual);
    }

	printf("\nresultado: %f\n", result);
    return result;
}

void mostrarPilhaMem(PilhaM *pilhaM) {
	PilhaM *aux = pilhaM;
	printf("\nPILHA:\n");

	while(aux != NULL) {
		if(aux->terminal == 'V') 
			printf("%s = %s\n", aux->ident.variavel, aux->valor);

		aux = aux->prox;
	}
}

// Armazenando as variáveis e seus valores na memória
void armazenaMemoria(TpCode *token, PilhaM **pilhaM, TpLista *lista) {
	TpCode *auxT = token;
    PilhaM *auxP = *pilhaM;
    
    float result;
	char equacao[100], resultado[10];
    auxT = auxT->prox;

	if(strcmp(auxT->token, "=") == 0) {
		auxT = auxT->prox;
		if(isNumber(auxT->token)) { // se numero
			if(auxT->prox == NULL)
				pushM(pilhaM, token->token, auxT->token, lista);
			
			else { // equacao
				if(identificar_equacao(auxT, *pilhaM) == 1) {	
					while (auxT != NULL) {
						strcat(equacao, auxT->token);
						strcat(equacao, " ");
						auxT = auxT->prox;
					}
					// Remover o último espaço adicionado
					if (strlen(equacao) > 0) {
						equacao[strlen(equacao) - 1] = '\0';
					}
					result = resolve(equacao, *pilhaM);
					sprintf(resultado, "%f", result);

					pushM(pilhaM, token->token, resultado, lista);
				}
			}
		}
		else {
			//procura na pilha de variaveis se existe uma variavel correspontente a auxT->token
			while(auxP != NULL && strcmp(auxT->token, auxP->ident.variavel) != 0) {
				auxP = auxP->prox;
			}
			if(auxT->prox == NULL) {
				if(strcmp(auxP->ident.variavel, auxT->token) == 0) {
					pushM(pilhaM, token->token, auxP->valor, lista);
				}
			}
			else { // equacao
				if(identificar_equacao(auxT, *pilhaM) == 1) {
					while (auxT != NULL) {
						strcat(equacao, auxT->token);
						strcat(equacao, " ");
						auxT = auxT->prox;
					}
					// Remover o último espaço adicionado
					if (strlen(equacao) > 0) {
						equacao[strlen(equacao) - 1] = '\0';
					}
					result = resolve(equacao, *pilhaM);
					printf("%f", result);
					pushM(pilhaM, token->token, resultado, lista);
				}

				if(auxT != NULL && strcmp(auxT->token, "\"") == 0) { // se string
					auxT = auxT->prox;
					pushM(pilhaM, token->token, auxT->token, lista);
					auxT = auxT->prox;
				}
			}
		}
	}
}

TpFrase *criaFrase(char token[15]) {
	TpFrase *nova = (TpFrase*)malloc(sizeof(TpFrase));
	strcpy(nova->frase, token);
	nova->prox = NULL;

	return nova;
}

void print(TpCode *token, PilhaM *pilhaM) {
	TpCode *auxT = token;
	TpFrase *frase = NULL, *auxFrase;
	PilhaM *auxP = pilhaM;

	auxT = auxT->prox->prox; // pula o '('
	
	if(strcmp(auxT->token, "\"") == 0) {
		auxT = auxT->prox;

		while(strcmp(auxT->token, "\"") != 0) { 
			if(frase == NULL) { // se a frase nao tiver elemento
				frase = criaFrase(auxT->token);
				auxFrase = frase;
			}	

			else { // se a frase tiver elementos
				auxFrase->prox = criaFrase(auxT->token);
				auxFrase = auxFrase->prox;
			}
			auxT = auxT->prox;
		}
		auxT = auxT->prox; // depois do "
		auxFrase = frase;

		if(strcmp(auxT->token, "%") == 0) {	 // se tiver %s, %d, %f
			while(auxFrase != NULL) {
				if(auxFrase->frase[0] == '%') // print("%d" % 10)
					auxT = auxT->prox;

				if(strcmp(auxT->token, "(") == 0)  // print("%d %d" % (10, 20))
					auxT = auxT->prox;
				
				if(isNumber(auxT->token)) {	// print("%d %d" % (10, 20))				
					strcpy(auxFrase->frase, auxT->token);
					auxT = auxT->prox;
				}
				if(!isNumber(auxT->token)) { 			
					if(strcmp(auxT->token, "\"") == 0) { // print("%s %d" % ("teste", 20))
						auxT = auxT->prox;
						strcpy(auxFrase->frase, auxT->token);
						auxT = auxT->prox->prox; // pula o fecha "
					}
					else { //variavel?
						auxP = pilhaM;
						while(auxP != NULL) {
							if(auxP->terminal == 'V') {
								if(strcmp(auxP->ident.variavel, auxT->token) == 0) {
									strcpy(auxFrase->frase, auxP->valor);
									auxT = auxT->prox;
								}
								auxP = auxP->prox;
							}
						}
					}
				}
				auxFrase = auxFrase->prox;				
			}
		}
		else {
			if(strcmp(auxT->token, "+") == 0) {
				auxT=auxT->prox;
				
				while(auxFrase->prox != NULL) {
					auxFrase = auxFrase->prox;
				}
				if(strcmp(auxT->token, "(") == 0)
					auxT = auxT->prox;

				if(strcmp(auxT->token, "\"") == 0) {
					auxT = auxT->prox;
					auxFrase->prox = criaFrase(auxT->token);
					auxT = auxT->prox;
				}
				else {
					if(!isNumber(auxT->token)) {
						auxP = pilhaM;

						while(auxP != NULL) {
							if(auxP->terminal == 'V') {
								if(strcmp(auxP->ident.variavel, auxT->token) == 0) {
									auxFrase->prox = criaFrase(auxP->valor);
									auxT = auxT->prox;
								}
								auxP = auxP->prox;
							}
						}
					}
				}
			}
		}
		auxFrase = frase;
		while(auxFrase != NULL) {
			printf("%s ", auxFrase->frase);
			auxFrase = auxFrase->prox;
		}
	}
}

void verifCond(TpCode *token, PilhaM *pilhaM) {
	TpCode *auxT = token;
	PilhaM *auxP = pilhaM;
	int verdade[10], i = 0, f = 0;
	char cond[10];

	auxT = auxT->prox; // pula o if
	while(strcmp(auxT->token, ":") != 0) {
		// Tudo isso se for uma variavel, mas se for uma string ou um numero?
		while(auxP != NULL && strcmp(auxT->token, auxP->ident.variavel) != 0) { // enquanto nao acha a variavel na pilha de variaveis
			auxP = auxP->prox;
		}
		if(auxP != NULL) {
			auxT = auxT->prox; // pula a variavel
			if(strcmp(auxT->token, "==") == 0) {
				auxT = auxT->prox; // pula o ==
				if(isNumber(auxT->token)) { // se compara auxP->valor com um token
					if(auxP->valor == auxT->token)
						verdade[i] = 1;

					else
						verdade[i] = 0;
					i++;
				}
				else //se for variavel
				{
				}
				//Colocar para váriavel dps
			}
			else {
				if (strcmp(auxT->token, "!=") == 0) {
					auxT = auxT->prox; // pula o !=

					if(isNumber(auxT->token)) {
						if(auxP->valor != auxT->token)
							verdade[i] = 1;

						else
							verdade[i] = 0;
						i++;
					}
					//Colocar para váriavel dps
				}
				else{
					if (strcmp(auxT->token, ">") == 0) {
						auxT = auxT->prox; // pula o >

						if(isNumber(auxT->token)) {
							if(auxP->valor > auxT->token)
								verdade[i] = 1;

							else
								verdade[i] = 0;
							i++;
						}
						//Colocar para váriavel dps
					}
					else {
						if(strcmp(auxT->token, "<") == 0) {
							auxT = auxT->prox; // pula o <

							if(isNumber(auxT->token)) {
								if(auxP->valor < auxT->token)
									verdade[i] = 1;

								else
									verdade[i] = 0;
								i++;
							}
							//Colocar para váriavel dps
						}
						else {
							if (strcmp(auxT->token, ">=") == 0) {
								auxT = auxT->prox; // pula o >=
								if(isNumber(auxT->token)){
									if(auxP->valor >= auxT->token)
										verdade[i] = 1;

									else
										verdade[i] = 0;
									i++;
								}
								//Colocar para váriavel dps
							}
							else {
								if (strcmp(auxT->token, "<=") == 0) {
									auxT = auxT->prox; // pula o <=

									if(isNumber(auxT->token)) {
										if(auxP->valor <= auxT->token)
											verdade[i] = 1;

										else
											verdade[i] = 0;
										i++;
									}
									//Colocar para váriavel dps
								}
							}
						}
					}
				}
			}
			auxT = auxT->prox; // pula o valor
			if(strcmp(auxT->token, "and") == 0) {
				cond[f++] = '&';
				auxT = auxT->prox; // pula o and
			}
			else {
				if(strcmp(auxT->token, "or") == 0) {
					cond[f++] = '|';
					auxT = auxT->prox; // pula o or
				}
				else {
					if(strcmp(auxT->token, "not") == 0) {
						cond[f++] = '!';
						auxT = auxT->prox; // pula o not
					}
				}
			}
		}
	}
}

void verIF(TpCode *token, PilhaM *pilhaM){
	verifCond(token, pilhaM);

}

void verWHILE(TpCode *token, PilhaM *pilhaM, TpLista *lista){
	verifCond(token, pilhaM);

}

void compilar(TpLista *pProgram , PilhaM **pilhaM) {
	TpLista *auxL = pProgram;
	TpCode *auxT, auxT2;

	initM(&(*pilhaM));

	while(auxL != NULL)
	{
		auxT = auxL->tokens;

		if(strcmp(auxT->token, "def") == 0) { //se for uma funcao pula para o fim da funcao
			while(strcmp(auxT->token, "fim-def") != 0) {
				auxL = auxL->prox;
				auxT = auxL->tokens;
			}
		}
		else {
			if(strcmp(auxT->token, "print") == 0) {
				print(auxT, *pilhaM);
			}
			else {
				if(strcmp(auxT->token, "if") == 0)
				{
					// verIF(auxT, *pilhaM);
				}
				else{
					if(strcmp(auxT->token, "while") == 0)
					{
						// verWHILE(auxT, *pilhaM, auxL);
					}
					else {
						armazenaMemoria(auxT, &(*pilhaM), auxL);
					}
				}
			}
			
		}
		auxL = auxL->prox;
	}
}
