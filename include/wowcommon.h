#ifndef _H_WOWCOMMON_
#define _H_WOWCOMMON_

#include <iostream>
#include <stdio.h>

/*!
 * \def LOGMESSAGE(X)
 * \brief Print message X on the standard output
 */

/*!
 * \def LOGMESSAGE_NO_ENDL(X)
 * \brief Print message X on the standard output WITHOUT endline.
 */

/*!
 * \def LOGMESSAGE_PARAM(X,Y)
 * \brief Print message X with parameter Y.
 */

/*!
 * \def LOGMESSAGE_PARAM_NO_ENDL(X,Y)
 * \brief Print message X with parameter Y WITHOUT endline.
 */

/*!
 * \def LOGMESSAGE_CONDITIONAL(CONDITION,MESSAGE,COMMAND)
 * \brief Print MESSAGE only if CONDITION is true.
 *
 * If CONDITION is true will be executed also COMMAND.
 *
 */

/*!
 * \def OK
 * \brief Print a green OK and a newline.
 */

/*!
 * \def FAIL
 * \brief Print a red FAIL and a newline.
 */


#define RED "\033[22;31m"
#define GREEN "\033[22;32m"
#define BLACK "\033[22;30m"
#define RESET "\033[0m"

#define LOGMESSAGE(X) std::cout << (X) << std::endl

#define LOGMESSAGE_NO_ENDL(X) std::cout << (X)

#define LOGMESSAGE_PARAM(X,Y) std::cout << (X) << "::" << (Y) << std::endl

#define LOGMESSAGE_PARAM_NO_ENDL(X,Y) std::cout << (X) << "::" << (Y)

#define LOGMESSAGE_CONDITIONAL(CONDITION,MESSAGE,COMMAND) if ((CONDITION)) { LOGMESSAGE(MESSAGE); COMMAND; }

#define OK printf("\t\t[%sOK%s]\n",GREEN,RESET)
#define FAIL printf("\t\t[%sFAIL%s]\n",RED,RESET)

#define INDENT(AMOUNT) for(int i=0;i<(AMOUNT);++i) { printf("\t"); }

/* TRIGGER MACRO */

#define DEBUG 1

#endif
