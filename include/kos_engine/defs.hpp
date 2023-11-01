#include "cos_graphics/defs.h"
#include <string>
#include <stdexcept>

#ifdef CG_USE_WCHAR
    using KEString = std::wstring;
    #define KE_TO_STRING std::to_wstring
#else
    using KEString = std::string;
    #define KE_TO_STRING std::to_string
#endif

