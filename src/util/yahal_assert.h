/*
 * yahal_assert.h
 *
 *  Created on: 05.02.2017
 *      Author: aterstegge
 */

#ifndef _YAHAL_ASSERT_H_
#define _YAHAL_ASSERT_H_

static const char * yahal_assert_file;
static int          yahal_assert_line;

static void yahal_assert_func() {
    (void)(yahal_assert_func);
    const char * file = yahal_assert_file; (void)(file);
    int          line = yahal_assert_line; (void)(line);
    while(true) ;
}


#ifdef NDEBUG
# define yahal_assert( cond ) ((void)0)
#else
# define yahal_assert( cond )           \
    if (!(cond)) {                      \
        yahal_assert_file = __FILE__;   \
        yahal_assert_line = __LINE__;   \
        yahal_assert_func();            \
    }
#endif

#endif /* _YAHAL_ASSERT_H_ */
