#pragma once
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


#define KE_DECL_HAS_METHOD(method, bool_var_name)       \
    template <typename dT, typename = void>             \
    static constexpr bool bool_var_name = false;        \
    template <typename dT>                              \
    static constexpr bool bool_var_name<dT, std::void_t<decltype(std::declval<dT>().method)>> = true;

