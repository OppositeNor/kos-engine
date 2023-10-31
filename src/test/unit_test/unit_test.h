#pragma once
#define CG_MODIFY_OUTPUT_MESSAGE
#include "kos_engine/defs.hpp"

#define CG_PRINT(...) CGPrint(CGSTR("KosEngine"), CGSTR("Output"), __VA_ARGS__)
#define CG_PRINT_WITH_FUNCTION(...) CGPrintWithFunction(CGSTR("KosEngine"), CGSTR("Output"), __FUNCTION__, __VA_ARGS__)
#define CG_ERROR(...) CGError()
#define CG_WARNING(...)

#include "cos_graphics/log.h"

#define KET_EXPECT_VALUES_EQUAL(val1, val2) \
    if ((val1) != (val2)) { \
        CG_PRINT_WITH_FUNCTION(CGSTR("Test failed: Expected value: %s, but get %s instead."), KE_TO_STRING(val1), KE_TO_STRING(val2)); \
        return CG_FALSE; \
    }