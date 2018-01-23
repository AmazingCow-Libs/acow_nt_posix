
// Amazing Cow Libs
#include "acow/cpp_goodies.h"


#if (ACOW_OS_IS_WINDOWS)
    //--------------------------------------------------------------------------
    //
    #include <io.h>

    #define isatty _isatty

#else
    //--------------------------------------------------------------------------
    // Just include the default header
    #include <unistd.h>

#endif // #if (ACOW_OS_IS_WINDOWS)