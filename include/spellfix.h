#ifndef _SQLITE3_SPELLFIX_H_
#define _SQLITE3_SPELLFIX_H_

#include "sqlite3.h"

#ifdef __cplusplus
extern "C" {
#endif

struct sqlite3_api_routines;
int sqlite3_spellfix_init(sqlite3 *db, char **pzErrMsg, const struct sqlite3_api_routines *pApi);

#ifdef __cplusplus
};
#endif

#endif /* _SQLITE3_SPELLFIX_H_ */