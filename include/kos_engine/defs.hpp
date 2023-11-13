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

#define KE_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286

#if __GNUC__
    #define KE_FORCE_INLINE inline __attribute__((always_inline))
#elif defined _MSC_VER
    #define KE_FORCE_INLINE __forceinline
#else
    #define KE_FORCE_INLINE inline
#endif