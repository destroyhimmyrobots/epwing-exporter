#ifndef EPWING_EXPORTER_HOOKS_H
#define EPWING_EXPORTER_HOOKS_H

extern "C" {

#include <eb/defs.h>

// https://isocpp.org/wiki/faq/mixing-c-and-cpp#cpp-objs-passed-to-c

#define EB_HOOK_FUNC(identifier) \
    EB_Error_Code \
    eb_hook_func_##identifier( \
        EB_Book *book, \
        EB_Appendix *appendix, \
        void *container, \
        EB_Hook_Code code, \
        int argc, \
        const unsigned int *argv \
    )

EB_HOOK_FUNC (begin_subscript);

EB_HOOK_FUNC (end_subscript);

EB_HOOK_FUNC (set_indent);

EB_HOOK_FUNC (newline);

EB_HOOK_FUNC (begin_superscript);

EB_HOOK_FUNC (end_superscript);

EB_HOOK_FUNC (begin_emphasis);

EB_HOOK_FUNC (end_emphasis);

EB_HOOK_FUNC (begin_candidate);

EB_HOOK_FUNC (end_candidate_group);

EB_HOOK_FUNC (end_candidate_leaf);

EB_HOOK_FUNC (begin_reference);

EB_HOOK_FUNC (end_reference);

EB_HOOK_FUNC (narrow_font);

EB_HOOK_FUNC (wide_font);

EB_HOOK_FUNC (narrow_JISX0208);

EB_HOOK_FUNC (wide_JISX0208);

EB_HOOK_FUNC (gb2313);

EB_HOOK_FUNC (iso8859_1);

/*
EB_HOOK_FUNC (begin_keyword);

EB_HOOK_FUNC (end_keyword);
*/

extern const EB_Hook TEXT_HOOKS[];
}

#endif // EPWING_EXPORTER_HOOKS_H
