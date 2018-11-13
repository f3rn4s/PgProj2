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
int  set_cardinality( const Set s ){
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
  // A implementar
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
   // A implementar
   return false;
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
	// A implementar
	return false;
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
	// A implementar
}

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
	// A implementar
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
	// A implementar
	return false;
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
	// A implementar
	return false;	
}
