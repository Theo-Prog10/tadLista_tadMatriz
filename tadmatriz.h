#ifndef ___T__A__D_M_

#define ___T__A__D_M_

#include "tadlista.h"

typedef Lista tadmat;

tadmat cria_mat(int qlinhas, int qcolunas);
tadmat soma_mat(tadmat a, tadmat b);
tadmat multi_mat(tadmat a, tadmat b);
tadmat neg_mat(tadmat a);
tadmat transp_mat(tadmat a);
tadmat carrega_mat(char *nomearq);
tadmat salva_mat(tadmat a, char *nomearq);
tadmat printa_mat(tadmat a); //remover quando for entregar a prova

#endif