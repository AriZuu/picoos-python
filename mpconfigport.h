#include <stdint.h>

// options to control how Micro Python is built

#define MICROPY_NLR_SETJMP (1)
#define MICROPY_ALLOC_PATH_MAX      (256)
#define MICROPY_EMIT_X64            (0)
#define MICROPY_EMIT_THUMB          (0)
#define MICROPY_EMIT_INLINE_THUMB   (0)
#define MICROPY_COMP_MODULE_CONST   (0)
#define MICROPY_COMP_CONST          (0)
#define MICROPY_COMP_DOUBLE_TUPLE_ASSIGN (0)
#define MICROPY_COMP_TRIPLE_TUPLE_ASSIGN (0)
#define MICROPY_MEM_STATS           (0)
#define MICROPY_DEBUG_PRINTERS      (0)
#define MICROPY_ENABLE_GC           (1)
#define MICROPY_REPL_EVENT_DRIVEN   (0)
#define MICROPY_HELPER_REPL         (1)
#define MICROPY_HELPER_LEXER_UNIX   (0)
#define MICROPY_ENABLE_SOURCE_LINE  (0)
#define MICROPY_ENABLE_DOC_STRING   (0)
#define MICROPY_ERROR_REPORTING     (MICROPY_ERROR_REPORTING_TERSE)
#define MICROPY_PY_BUILTINS_BYTEARRAY (0)
#define MICROPY_PY_BUILTINS_MEMORYVIEW (0)
#define MICROPY_PY_BUILTINS_ENUMERATE (0)
#define MICROPY_PY_BUILTINS_FROZENSET (0)
#define MICROPY_PY_BUILTINS_REVERSED (0)
#define MICROPY_PY_BUILTINS_SET     (0)
#define MICROPY_PY_BUILTINS_SLICE   (0)
#define MICROPY_PY_BUILTINS_PROPERTY (0)
#define MICROPY_PY___FILE__         (0)
#define MICROPY_PY_GC               (0)
#define MICROPY_PY_ARRAY            (0)
#define MICROPY_PY_ATTRTUPLE        (0)
#define MICROPY_PY_COLLECTIONS      (0)
#define MICROPY_PY_MATH             (0)
#define MICROPY_PY_CMATH            (0)
#define MICROPY_PY_IO               (0)
#define MICROPY_PY_STRUCT           (0)
#define MICROPY_PY_SYS              (0)
#define MICROPY_MODULE_FROZEN       (0)
#define MICROPY_CPYTHON_COMPAT      (0)
#ifdef xxxunix
#define MICROPY_LONGINT_IMPL        (MICROPY_LONGINT_IMPL_LONGLONG)
#else
#define MICROPY_LONGINT_IMPL        (MICROPY_LONGINT_IMPL_NONE)
#endif
#define MICROPY_FLOAT_IMPL          (MICROPY_FLOAT_IMPL_NONE)

// type definitions for the specific machine

#define BYTES_PER_WORD (4)

#define MICROPY_MAKE_POINTER_CALLABLE(p) ((void*)((mp_uint_t)(p) | 1))

// This port is intended to be 32-bit, but unfortunately, int32_t for
// different targets may be defined in different ways - either as int
// or as long. This requires different printf formatting specifiers
// to print such value. So, we avoid int32_t and use int directly.
#ifdef xxxxunix
#define UINT_FMT "%lu"
#define INT_FMT "%ld"
typedef long mp_int_t; // must be pointer size
typedef unsigned long mp_uint_t; // must be pointer size

typedef void *machine_ptr_t; // must be of pointer size
typedef const void *machine_const_ptr_t; // must be of pointer size
typedef long mp_off_t;
#else
#define UINT_FMT "%u"
#define INT_FMT "%d"
typedef int mp_int_t; // must be pointer size
typedef unsigned mp_uint_t; // must be pointer size

typedef void *machine_ptr_t; // must be of pointer size
typedef const void *machine_const_ptr_t; // must be of pointer size
typedef int mp_off_t;
#endif

void mp_hal_stdout_tx_strn_cooked(const char *str, mp_uint_t len);
//#define MP_PLAT_PRINT_STRN(str, len) mp_hal_stdout_tx_strn_cooked(str, len)

// extra built in names to add to the global namespace
extern const struct _mp_obj_fun_builtin_t mp_builtin_open_obj;
#define MICROPY_PORT_BUILTINS \
    { MP_OBJ_NEW_QSTR(MP_QSTR_open), (mp_obj_t)&mp_builtin_open_obj },

// We need to provide a declaration/definition of alloca()
//#include <alloca.h>
#include <stdlib.h>

#define HAL_GetTick() 0
int mp_hal_stdin_rx_chr(void);
void mp_hal_stdout_tx_str(const char *str);
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len);
void mp_hal_stdout_tx_strn_cooked(const char *str, mp_uint_t len);

static inline void mp_hal_set_interrupt_char(char c) {}

#define MICROPY_HW_BOARD_NAME "minimal"
#define MICROPY_HW_MCU_NAME "unknown-cpu"

#ifdef xxxxunix
#define MICROPY_MIN_USE_STDOUT (1)
#endif

#define MP_STATE_PORT MP_STATE_VM

#define MICROPY_PORT_ROOT_POINTERS \
    const char *readline_hist[8];
