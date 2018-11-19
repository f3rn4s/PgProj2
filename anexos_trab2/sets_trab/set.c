/**
 * set.c
 * ISEL, outubro 2018

 *--------------------------------------------------------------------------- */

#include  "set.h"

 

/**
 * Descrição:
 *   Saber quantos elementos tem o conjunto recebido em parametro.
 * Parâmetros:
 *   s - o conjunto do qual se pretende saber a dimensão 
 * Retorno:
 *   retorna o total de elementos do conjunto
 */
int  set_cardinality(const Set s ){
	return s[0];
}



/**
 * Descrição:
 *   	Saber se o elemento consta no conjunto.
 * Parâmetros:
 *      s - conjunto de entrada
 *   	elem - inteiro a verificar se existe no conjunto "s"
 * Retorno:
 *   	retorna true se o inteiro "elem" existe no conjunto "s", e false caso contrário
 */
bool set_is_member( const Set s,  int elem ){

int dim = set_cardinality(s);
  
  for (int i = 1; i < dim; i++)
  {
  	if (s[i] == elem)
  	{
  		return true;
  	}
  }

  return false;
}

/**
 * Descrição:
 *   verifica se os dois conjuntos recebidos por parametro são iguais
 * Parâmetros:
 *     s1  - conjunto  1
 *     s2  - conjunto  2
 * Retorno:
 *   Retorna true se os conjuntos recebidos são iguais, isto é,
 *   se têm os mesmos elementos, mesmo que arrumados por outra ordem.
 *   Caso contrário, retorna false.
 */
bool set_equals(const Set s1, const Set s2 ){

   int dim1 = set_cardinality(s1);
   int dim2 = set_cardinality(s2);
   bool equal = false;
   int i = 0;

   if (dim1 != dim2)
   {
   	equal = false;
   }
   else
   {
   	for (i = 1; i <= dim2 ; i++)
   	{
   		equal = set_is_member (s1, s2[i]);
   	}
   }
   return equal;
} 


/**
 * Descrição:
 *   Realiza a união entre os elementos dos conjuntos recebidos em s1 e s2 e coloca o 
 *   resultado em sr. 
 * Parâmetros:
 *    s1   - conjunto 1
 *    s2   - conjunto 2
 *    sr   - conjunto resultado da união dos conjuntos "s1" e "s2"
 * Retorno:
 *    true se o conjunto união foi gerado corretamente, e false se o array "sr" não
 *    tem capacidade para conter todos os elementos do conjunto união.
 */
bool set_union( const Set s1, const Set s2, Set sr ){

	if((s1[0] + s2[0]) > 256) // perguntar colocar Max_SET????????????
		return false;//se exceder sair
	sr[0] = s1[0] + s2[0];//definir tamanho de sr
	
	int i, j, start2idx = s1[0] + 1;
	
	
	for( i = 1; i <= s1[0]; i++)// para copy do s1 em sr
		sr[i] = s1[i];
	
	for(i = 1, j = start2idx; i<=s2[0]; i++, j++)// apos fim de s1...
		sr[j] = s2[i];//... colocar s2
		
	return true;// se chegou aqui terá feito tudo corretamente
}

/**
 * Descrição:
 *   Realiza a intersecção entre os elementos dos conjuntos recebidos em s1 e s2 e  
 *   coloca o resultado em sr. 
 * Parâmetros:
 *    s1   - conjunto 1
 *    s2   - conjunto 2
 *    sr   - conjunto resultado da intersecção dos conjuntos "s1" e "s2"
 * Retorno:
 *   Não retorna valor. É sempre possível realizar a intersecção
 */
 void set_intersection( const Set s1, const Set s2, Set sr ){

	int i, j, count = 0;
		
	for(i = 1; i <= s1[0]; i++)// a cada s1
		for(j = 1; j <= s2[0]; j++)// compara com todos de s2
			if(s1[i] == s2[j])
			{
				count++;//contador e posicionador para sr
				sr[count] = s1[i];
			}
	sr[0] = count;	
	return;//esta fc parte do principio de k não há elementos repetidos
}//perguntar se há elementos repetidos????

/**
 * Descrição:
 *   realiza a diferença entre os elementos dos conjuntos recebidos s1 e s2 
 *   e coloca o resultado em sr. 
 * Parâmetros:
 *    s1   - conjunto 1
 *    s2   - conjunto 2
 *    sr   - conjunto resultado da diferença s1 - s2
 * Retorno:
 *   Não retorna valor. É sempre possível realizar a diferença
 */
void set_difference(const Set s1, const Set s2, Set sr ){
	//if(s1[0]>s2[0]) perguntar qt à diferença com s1/2 vazio
	sr[0] = (s1[0]<s2[0]) ? s1[0] : s2[0];//tamanho sr condicionado 
	int i; 
	
	for( i = 1; i < s1[0] || i<s2[0]; i++)// para copy do s1 em sr
		sr[i] = s1[i]-s2[i];
			
	return;
}

/**
 * Descrição:
 *   verifica se o conjuntos recebidos s1 contém o conjunto recebido "s2". 
 * Parâmetros:
 *    s1   - conjunto com os elementos a verificar se contém o conjunto "s1"
 * 
 *    s2   - conjunto com os elementos a verificar se são contidos em "s1"
 * Retorno:
 *   retorna valor de true se "s1" contém "s2", e false caso contrário.
 */
bool set_contains(const Set s1, const Set s2 ){

	int dim2 = set_cardinality(s2);//dimensao do 2 conjunto
	bool devolve = false;
	int conta=0;


	for (int ct1=1; ct1<=dim2; ct1++)
	{
	   if ( set_is_member(s1, s2[ct1])) 
	   {
	   	conta ++;
	   }

	   if (conta == dim2 ){
	        devolve = true;
	   }
	   else{
	        devolve = false;
	   }
	}
	return devolve = false;
}

/**
 * Descrição:
 * 		verifica se o set é valido, isto, se o tamanho está entre 0 e MAX_SET,
 * 		e não existem repetições
 * Parâmetros
 * 	    s  - conjunto a validar
 *  * Retorno:
 *    true se o conjunto é válido, false caso contrário.
 **/
bool set_is_valid(Set s) {

	bool devolve = true;
    int conta =0;
	int dim = set_cardinality(s);//dimensao do conjunto

	if (dim>=0 && dim <= MAX_SET)
		devolve = true;
	else
		devolve = false;

	for (int ct1=1; ct1<dim; ct1++ )
	  if (s[ct1] == s[ct1+1]) conta++;

	  if (conta>0) devolve = false;

	return devolve = false;
}
