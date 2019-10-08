#ifndef TPG_UNIVERSAL_TPGUTILITY_H_
#define TPG_UNIVERSAL_TPGUTILITY_H_

#include <stdint.h>

#include <map>
#include <string>

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef int_fast8_t   int8_fast;
typedef int_fast16_t  int16_fast;
typedef int_fast32_t  int32_fast;
typedef int_fast64_t  int64_fast;

typedef struct
{
    int16 learnerRegisterSize;
    int64 nextTeamId;
    int64 nextLearnerId;
    std::map<std::string, void*> operationsMap;
} TpgParameters;

#endif
