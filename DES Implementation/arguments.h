#ifndef _DEBUG
#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_

#include <string>

/*\
 *	Questa struttura contiene gli argomenti.
 *	Serve principalmente per evitare di dover lavorare con 'argv' a livello globale.
\*/
struct arguments_container_t
{
	std::string program_function;	// argv[1]
	std::string input_string;		// argv[2]
	std::string key_string;			// argv[3]
};

/*\
 *	Dichiarazione delle variabili
\*/
extern arguments_container_t	g_arguments;
extern int						g_argumentCount;

#endif // _ARGUMENTS_H_
#endif // _DEBUG