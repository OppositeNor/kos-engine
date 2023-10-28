#include "cos_graphics/defs.h"
#include <string>

#ifdef CG_USE_WCHAR
    using KEString = std::wstring;
#else
    using KEString = std::string;
#endif