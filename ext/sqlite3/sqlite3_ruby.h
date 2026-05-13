#ifndef SQLITE3_RUBY
#define SQLITE3_RUBY

#include <ruby.h>
#include <ruby/thread.h>

// Per-OS-thread flag: non-zero while a sqlite call on this thread is running
// inside rb_thread_call_without_gvl. Sqlite invokes callbacks (busy_handler,
// tracefunc, authorizer, collation, UDFs) synchronously on the same thread,
// so they consult this flag to decide whether to re-acquire the GVL.
#if defined(_MSC_VER)
#  define SQLITE3_TLS __declspec(thread)
#else
#  define SQLITE3_TLS __thread
#endif
extern SQLITE3_TLS int sqlite3_ruby_in_nogvl;

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

#include <ruby/encoding.h>

#define USASCII_P(_obj) (rb_enc_get_index(_obj) == rb_usascii_encindex())
#define UTF8_P(_obj) (rb_enc_get_index(_obj) == rb_utf8_encindex())
#define UTF16_LE_P(_obj) (rb_enc_get_index(_obj) == rb_enc_find_index("UTF-16LE"))
#define UTF16_BE_P(_obj) (rb_enc_get_index(_obj) == rb_enc_find_index("UTF-16BE"))
#define SQLITE3_UTF8_STR_NEW2(_obj) (rb_utf8_str_new_cstr(_obj))

#ifdef USING_SQLCIPHER_INC_SUBDIR
#  include <sqlcipher/sqlite3.h>
#else
#  include <sqlite3.h>
#endif

#ifndef HAVE_TYPE_SQLITE3_INT64
typedef sqlite_int64 sqlite3_int64;
#endif

#ifndef HAVE_TYPE_SQLITE3_UINT64
typedef sqlite_uint64 sqlite3_uint64;
#endif

extern VALUE mSqlite3;
extern VALUE cSqlite3Blob;

#include <database.h>
#include <statement.h>
#include <exception.h>
#include <backup.h>
#include <timespec.h>

int bignum_to_int64(VALUE big, sqlite3_int64 *result);

#endif
