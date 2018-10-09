#include "library.h"

extern "C" {
#include <eb/eb.h>
}

epwing::Library::Library() noexcept {
    eb_initialize_library();
}

epwing::Library::~Library() noexcept {
    eb_finalize_library();
}
