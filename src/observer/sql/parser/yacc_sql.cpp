/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <cstdint>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <utility>
#include <limits>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"
#include "common/type/attr_type.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, SqlCommandFlag flag, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(flag);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundAggregateExpr *create_aggregate_expression(const char *aggregate_name,
                                           Expression *child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

bool is_valid_date(const char *date) {
  struct tm tm; bzero(&tm, sizeof(tm));
  char *result = strptime(date, "%Y-%m-%d", &tm);
  if (result == nullptr || *result != '\0') {
    return false;
  }

  int month2day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int year = tm.tm_year + 1900;
  if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && tm.tm_mon == 1) {
    return tm.tm_mday <= 29;
  }
  return tm.tm_mday <= month2day[tm.tm_mon];
}

#line 144 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_BY = 4,                         /* BY  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_DROP = 6,                       /* DROP  */
  YYSYMBOL_GROUP = 7,                      /* GROUP  */
  YYSYMBOL_HAVING = 8,                     /* HAVING  */
  YYSYMBOL_TABLE = 9,                      /* TABLE  */
  YYSYMBOL_TABLES = 10,                    /* TABLES  */
  YYSYMBOL_INDEX = 11,                     /* INDEX  */
  YYSYMBOL_CALC = 12,                      /* CALC  */
  YYSYMBOL_SELECT = 13,                    /* SELECT  */
  YYSYMBOL_DESC = 14,                      /* DESC  */
  YYSYMBOL_SHOW = 15,                      /* SHOW  */
  YYSYMBOL_SYNC = 16,                      /* SYNC  */
  YYSYMBOL_INSERT = 17,                    /* INSERT  */
  YYSYMBOL_DELETE = 18,                    /* DELETE  */
  YYSYMBOL_UPDATE = 19,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 20,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 21,                    /* RBRACE  */
  YYSYMBOL_COMMA = 22,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 23,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 24,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 25,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 26,                     /* INT_T  */
  YYSYMBOL_STRING_T = 27,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 28,                   /* FLOAT_T  */
  YYSYMBOL_VECTOR_T = 29,                  /* VECTOR_T  */
  YYSYMBOL_DATE_T = 30,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 31,                    /* TEXT_T  */
  YYSYMBOL_HELP = 32,                      /* HELP  */
  YYSYMBOL_EXIT = 33,                      /* EXIT  */
  YYSYMBOL_DOT = 34,                       /* DOT  */
  YYSYMBOL_INTO = 35,                      /* INTO  */
  YYSYMBOL_VALUES = 36,                    /* VALUES  */
  YYSYMBOL_FROM = 37,                      /* FROM  */
  YYSYMBOL_WHERE = 38,                     /* WHERE  */
  YYSYMBOL_AND = 39,                       /* AND  */
  YYSYMBOL_OR = 40,                        /* OR  */
  YYSYMBOL_SET = 41,                       /* SET  */
  YYSYMBOL_ON = 42,                        /* ON  */
  YYSYMBOL_LOAD = 43,                      /* LOAD  */
  YYSYMBOL_DATA = 44,                      /* DATA  */
  YYSYMBOL_INFILE = 45,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 46,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 47,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 48,                    /* FORMAT  */
  YYSYMBOL_EQ = 49,                        /* EQ  */
  YYSYMBOL_LT = 50,                        /* LT  */
  YYSYMBOL_GT = 51,                        /* GT  */
  YYSYMBOL_LE = 52,                        /* LE  */
  YYSYMBOL_GE = 53,                        /* GE  */
  YYSYMBOL_NE = 54,                        /* NE  */
  YYSYMBOL_LK = 55,                        /* LK  */
  YYSYMBOL_NLK = 56,                       /* NLK  */
  YYSYMBOL_IS_T = 57,                      /* IS_T  */
  YYSYMBOL_IS_NOT_T = 58,                  /* IS_NOT_T  */
  YYSYMBOL_MAX = 59,                       /* MAX  */
  YYSYMBOL_MIN = 60,                       /* MIN  */
  YYSYMBOL_COUNT = 61,                     /* COUNT  */
  YYSYMBOL_AVG = 62,                       /* AVG  */
  YYSYMBOL_SUM = 63,                       /* SUM  */
  YYSYMBOL_INNER = 64,                     /* INNER  */
  YYSYMBOL_JOIN = 65,                      /* JOIN  */
  YYSYMBOL_UNIQUE = 66,                    /* UNIQUE  */
  YYSYMBOL_LBRACKET = 67,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 68,                  /* RBRACKET  */
  YYSYMBOL_WITH = 69,                      /* WITH  */
  YYSYMBOL_DISTANCE = 70,                  /* DISTANCE  */
  YYSYMBOL_TYPE = 71,                      /* TYPE  */
  YYSYMBOL_LISTS = 72,                     /* LISTS  */
  YYSYMBOL_PROBES = 73,                    /* PROBES  */
  YYSYMBOL_IVFFLAT = 74,                   /* IVFFLAT  */
  YYSYMBOL_L2_DISTANCE = 75,               /* L2_DISTANCE  */
  YYSYMBOL_COSINE_DISTANCE = 76,           /* COSINE_DISTANCE  */
  YYSYMBOL_INNER_PRODUCT = 77,             /* INNER_PRODUCT  */
  YYSYMBOL_EXISTS_T = 78,                  /* EXISTS_T  */
  YYSYMBOL_NOT = 79,                       /* NOT  */
  YYSYMBOL_IN_T = 80,                      /* IN_T  */
  YYSYMBOL_VIEW = 81,                      /* VIEW  */
  YYSYMBOL_NULL_T = 82,                    /* NULL_T  */
  YYSYMBOL_NOT_NULL_T = 83,                /* NOT_NULL_T  */
  YYSYMBOL_ORDER_BY = 84,                  /* ORDER_BY  */
  YYSYMBOL_ASC = 85,                       /* ASC  */
  YYSYMBOL_AS = 86,                        /* AS  */
  YYSYMBOL_LIMIT = 87,                     /* LIMIT  */
  YYSYMBOL_NUMBER = 88,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 89,                     /* FLOAT  */
  YYSYMBOL_ID = 90,                        /* ID  */
  YYSYMBOL_SSS = 91,                       /* SSS  */
  YYSYMBOL_DATE = 92,                      /* DATE  */
  YYSYMBOL_93_ = 93,                       /* '+'  */
  YYSYMBOL_94_ = 94,                       /* '-'  */
  YYSYMBOL_95_ = 95,                       /* '*'  */
  YYSYMBOL_96_ = 96,                       /* '/'  */
  YYSYMBOL_UMINUS = 97,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 98,                  /* $accept  */
  YYSYMBOL_commands = 99,                  /* commands  */
  YYSYMBOL_command_wrapper = 100,          /* command_wrapper  */
  YYSYMBOL_id_maybe_keyword = 101,         /* id_maybe_keyword  */
  YYSYMBOL_id_list = 102,                  /* id_list  */
  YYSYMBOL_exit_stmt = 103,                /* exit_stmt  */
  YYSYMBOL_help_stmt = 104,                /* help_stmt  */
  YYSYMBOL_sync_stmt = 105,                /* sync_stmt  */
  YYSYMBOL_begin_stmt = 106,               /* begin_stmt  */
  YYSYMBOL_commit_stmt = 107,              /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 108,            /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 109,          /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 110,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 111,          /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 112,        /* create_index_stmt  */
  YYSYMBOL_create_vector_index_stmt = 113, /* create_vector_index_stmt  */
  YYSYMBOL_vector_index_param_list = 114,  /* vector_index_param_list  */
  YYSYMBOL_vector_index_field = 115,       /* vector_index_field  */
  YYSYMBOL_drop_index_stmt = 116,          /* drop_index_stmt  */
  YYSYMBOL_as_select = 117,                /* as_select  */
  YYSYMBOL_create_table_stmt = 118,        /* create_table_stmt  */
  YYSYMBOL_create_view_stmt = 119,         /* create_view_stmt  */
  YYSYMBOL_attr_def_list = 120,            /* attr_def_list  */
  YYSYMBOL_attr_def = 121,                 /* attr_def  */
  YYSYMBOL_nullable_spec = 122,            /* nullable_spec  */
  YYSYMBOL_number = 123,                   /* number  */
  YYSYMBOL_type = 124,                     /* type  */
  YYSYMBOL_insert_name_lists = 125,        /* insert_name_lists  */
  YYSYMBOL_insert_stmt = 126,              /* insert_stmt  */
  YYSYMBOL_value_list = 127,               /* value_list  */
  YYSYMBOL_value = 128,                    /* value  */
  YYSYMBOL_vector_elem = 129,              /* vector_elem  */
  YYSYMBOL_vector_value_list = 130,        /* vector_value_list  */
  YYSYMBOL_storage_format = 131,           /* storage_format  */
  YYSYMBOL_delete_stmt = 132,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 133,              /* update_stmt  */
  YYSYMBOL_set_clause_list = 134,          /* set_clause_list  */
  YYSYMBOL_set_clause = 135,               /* set_clause  */
  YYSYMBOL_select_stmt = 136,              /* select_stmt  */
  YYSYMBOL_order_by = 137,                 /* order_by  */
  YYSYMBOL_order_by_list = 138,            /* order_by_list  */
  YYSYMBOL_order_by_item = 139,            /* order_by_item  */
  YYSYMBOL_limit = 140,                    /* limit  */
  YYSYMBOL_asc_desc = 141,                 /* asc_desc  */
  YYSYMBOL_calc_stmt = 142,                /* calc_stmt  */
  YYSYMBOL_expression_list = 143,          /* expression_list  */
  YYSYMBOL_expression = 144,               /* expression  */
  YYSYMBOL_agg_fun_attr_list = 145,        /* agg_fun_attr_list  */
  YYSYMBOL_agg_fun_attr = 146,             /* agg_fun_attr  */
  YYSYMBOL_rel_attr = 147,                 /* rel_attr  */
  YYSYMBOL_relation = 148,                 /* relation  */
  YYSYMBOL_rel_list = 149,                 /* rel_list  */
  YYSYMBOL_join_list = 150,                /* join_list  */
  YYSYMBOL_join = 151,                     /* join  */
  YYSYMBOL_where = 152,                    /* where  */
  YYSYMBOL_condition_list = 153,           /* condition_list  */
  YYSYMBOL_condition = 154,                /* condition  */
  YYSYMBOL_comp_op = 155,                  /* comp_op  */
  YYSYMBOL_group_by = 156,                 /* group_by  */
  YYSYMBOL_having = 157,                   /* having  */
  YYSYMBOL_load_data_stmt = 158,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 159,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 160,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 161             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  88
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   626

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  64
/* YYNRULES -- Number of rules.  */
#define YYNRULES  188
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  393

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   348


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    95,    93,     2,    94,     2,    96,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    97
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   287,   287,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   320,   323,   326,   329,   332,
     335,   338,   344,   347,   352,   361,   367,   373,   378,   384,
     390,   396,   402,   409,   415,   423,   442,   463,   538,   542,
     553,   557,   561,   565,   569,   573,   580,   591,   594,   597,
     602,   631,   646,   660,   663,   676,   685,   705,   706,   707,
     711,   714,   715,   716,   717,   718,   719,   723,   726,   731,
     752,   755,   766,   770,   774,   780,   792,   802,   808,   812,
     819,   822,   831,   834,   841,   853,   870,   875,   888,   897,
     906,   961,   964,   971,   977,   990,   998,  1002,  1006,  1014,
    1017,  1024,  1027,  1031,  1038,  1047,  1052,  1059,  1066,  1075,
    1087,  1101,  1104,  1107,  1110,  1113,  1117,  1120,  1123,  1126,
    1129,  1134,  1140,  1143,  1148,  1151,  1154,  1157,  1160,  1179,
    1182,  1196,  1201,  1204,  1212,  1217,  1227,  1233,  1240,  1249,
    1254,  1268,  1271,  1287,  1294,  1297,  1303,  1306,  1311,  1316,
    1376,  1384,  1393,  1402,  1412,  1428,  1444,  1454,  1464,  1473,
    1484,  1485,  1486,  1487,  1488,  1489,  1490,  1491,  1492,  1493,
    1499,  1503,  1511,  1514,  1519,  1532,  1540,  1550,  1551
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "BY",
  "CREATE", "DROP", "GROUP", "HAVING", "TABLE", "TABLES", "INDEX", "CALC",
  "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE",
  "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T",
  "STRING_T", "FLOAT_T", "VECTOR_T", "DATE_T", "TEXT_T", "HELP", "EXIT",
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "OR", "SET", "ON",
  "LOAD", "DATA", "INFILE", "EXPLAIN", "STORAGE", "FORMAT", "EQ", "LT",
  "GT", "LE", "GE", "NE", "LK", "NLK", "IS_T", "IS_NOT_T", "MAX", "MIN",
  "COUNT", "AVG", "SUM", "INNER", "JOIN", "UNIQUE", "LBRACKET", "RBRACKET",
  "WITH", "DISTANCE", "TYPE", "LISTS", "PROBES", "IVFFLAT", "L2_DISTANCE",
  "COSINE_DISTANCE", "INNER_PRODUCT", "EXISTS_T", "NOT", "IN_T", "VIEW",
  "NULL_T", "NOT_NULL_T", "ORDER_BY", "ASC", "AS", "LIMIT", "NUMBER",
  "FLOAT", "ID", "SSS", "DATE", "'+'", "'-'", "'*'", "'/'", "UMINUS",
  "$accept", "commands", "command_wrapper", "id_maybe_keyword", "id_list",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "create_vector_index_stmt",
  "vector_index_param_list", "vector_index_field", "drop_index_stmt",
  "as_select", "create_table_stmt", "create_view_stmt", "attr_def_list",
  "attr_def", "nullable_spec", "number", "type", "insert_name_lists",
  "insert_stmt", "value_list", "value", "vector_elem", "vector_value_list",
  "storage_format", "delete_stmt", "update_stmt", "set_clause_list",
  "set_clause", "select_stmt", "order_by", "order_by_list",
  "order_by_item", "limit", "asc_desc", "calc_stmt", "expression_list",
  "expression", "agg_fun_attr_list", "agg_fun_attr", "rel_attr",
  "relation", "rel_list", "join_list", "join", "where", "condition_list",
  "condition", "comp_op", "group_by", "having", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-289)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     580,   159,    13,   318,   318,   466,    18,  -289,     6,   -12,
     466,  -289,  -289,  -289,  -289,  -289,   466,    16,   580,    57,
      31,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,
    -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,
    -289,  -289,  -289,   466,   466,    51,    55,   466,   466,   466,
     318,  -289,    49,    60,    98,   109,   116,   -57,   118,   124,
     125,  -289,  -289,  -289,  -289,  -289,  -289,   318,  -289,   101,
    -289,  -289,   428,  -289,   119,  -289,  -289,  -289,  -289,  -289,
    -289,  -289,   466,   466,   105,   112,   130,  -289,  -289,  -289,
    -289,     7,   121,    79,   466,    -7,  -289,   134,    -9,   342,
     342,   342,   342,   342,  -289,  -289,   165,   318,   318,   318,
    -289,   441,   318,   466,   318,   318,   318,   318,   167,   466,
     174,   160,   466,   300,   108,   466,   199,  -289,  -289,   466,
     163,   189,    -7,   211,   148,   466,  -289,  -289,   201,   217,
     226,  -289,   235,   238,   245,   247,   -57,   202,    89,   115,
     128,  -289,  -289,  -289,   228,   -50,   -50,  -289,  -289,   318,
     355,   249,   208,    -7,   243,   281,  -289,   225,   160,   258,
    -289,   250,   447,   260,  -289,   264,   466,   466,   265,    -7,
     199,  -289,   466,  -289,   342,  -289,  -289,  -289,  -289,   165,
    -289,   318,   318,   318,   318,  -289,   466,  -289,   466,   222,
     160,   208,   272,   274,   229,   275,   219,   488,  -289,    35,
     263,  -289,   466,   290,  -289,  -289,  -289,  -289,  -289,  -289,
      -1,   466,   279,   466,   282,   283,  -289,  -289,  -289,  -289,
    -289,     9,    38,    47,  -289,  -289,  -289,   466,   303,  -289,
    -289,   300,   291,   199,   293,  -289,  -289,  -289,  -289,  -289,
    -289,  -289,  -289,  -289,  -289,   234,   295,   367,   281,   281,
     199,  -289,  -289,   466,   239,  -289,  -289,  -289,   260,   284,
     301,   236,   466,  -289,  -289,  -289,   286,   328,   329,   314,
     520,   325,   199,   319,    34,   229,   133,  -289,  -289,   326,
    -289,  -289,   332,  -289,   302,   -10,  -289,   340,   343,   281,
     318,   281,   299,   300,   344,   404,  -289,   345,    34,   314,
     347,   353,  -289,    30,   335,  -289,   321,  -289,  -289,  -289,
    -289,   489,   309,   314,  -289,   229,   133,  -289,   314,   376,
     377,  -289,  -289,  -289,   466,   399,   400,   401,   402,  -289,
     403,    15,   348,  -289,  -289,   410,   412,  -289,  -289,  -289,
     192,   318,   318,   318,   489,  -289,  -289,  -289,  -289,  -289,
    -289,   374,   386,   389,   390,   419,   424,   151,   158,   182,
    -289,   -26,   373,   363,   364,  -289,   192,   318,   318,   318,
    -289,  -289,  -289,  -289,  -289,  -289,  -289,    58,    71,   107,
    -289,  -289,  -289
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,    39,    40,    41,    37,    36,     0,     0,     0,     0,
     187,    24,    23,    16,    17,    18,    19,    10,    11,    12,
      13,    14,    15,     8,     9,     5,     7,     6,     4,     3,
      20,    21,    22,     0,     0,     0,     0,     0,     0,     0,
       0,    26,    28,    27,    31,    29,    30,     0,     0,     0,
       0,    87,    82,    83,    25,    84,    85,     0,   132,   144,
     130,   114,   115,   131,     0,    28,    27,    31,    29,    30,
      44,    43,     0,     0,     0,     0,     0,   185,     1,   188,
       2,    57,     0,     0,     0,    32,    42,     0,     0,   141,
     141,   141,   141,   141,    88,    89,    90,     0,     0,     0,
     129,     0,     0,     0,     0,     0,     0,     0,   116,     0,
      77,   154,     0,     0,     0,     0,     0,    61,    59,     0,
       0,     0,    32,    33,     0,     0,   125,   142,   144,     0,
     139,   143,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   133,   145,   118,   117,   121,   122,   123,   124,     0,
     146,   149,   151,    32,     0,   156,    94,     0,   154,    96,
     186,     0,     0,    63,    58,     0,     0,     0,     0,    32,
       0,    56,     0,   134,   141,   135,   136,   137,   138,    90,
      86,     0,     0,     0,     0,   119,     0,   147,     0,     0,
     154,   151,     0,     0,     0,     0,     0,     0,   155,   157,
       0,    95,     0,     0,    71,    72,    73,    74,    75,    76,
      69,     0,     0,     0,     0,     0,    35,    34,    62,   140,
      91,     0,     0,     0,   120,   148,   150,     0,   180,   152,
      78,     0,     0,     0,     0,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,     0,     0,     0,   156,   156,
       0,    98,    97,     0,     0,    67,    68,    66,    63,    92,
       0,     0,     0,   126,   127,   128,     0,     0,   182,    80,
       0,     0,     0,     0,     0,     0,   160,   158,   159,     0,
     184,    70,     0,    64,     0,    57,    45,     0,     0,   156,
       0,   156,   101,     0,     0,     0,   166,     0,     0,    80,
       0,     0,    99,    69,     0,    60,     0,    46,   153,   181,
     183,     0,   109,    80,    79,     0,   168,   167,    80,     0,
       0,   162,   161,    65,     0,     0,     0,     0,     0,   102,
     103,   111,     0,   100,    81,     0,     0,   163,   164,    93,
       0,     0,     0,     0,     0,   113,   112,   105,   110,   169,
     165,     0,     0,     0,     0,     0,    48,     0,     0,     0,
     104,     0,     0,     0,     0,    47,     0,     0,     0,     0,
      50,    51,    52,    53,    54,    55,    49,     0,     0,     0,
     106,   107,   108
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -289,  -289,   435,    -5,    27,  -289,  -289,  -289,  -289,  -289,
    -289,  -289,  -289,  -289,  -289,  -289,    78,  -289,  -289,   173,
    -289,  -289,   214,   248,   147,  -289,  -289,  -289,  -289,  -288,
    -122,   324,   294,  -289,  -289,  -289,   285,  -289,   -65,  -289,
     152,  -289,  -289,  -289,  -289,    -2,   -44,   -93,  -289,   -85,
    -128,  -165,   304,  -289,  -164,   -62,  -289,   204,  -289,  -289,
    -289,  -289,  -289,  -289
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    69,   134,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,   365,   366,    32,   127,
      33,    34,   222,   173,   267,   292,   220,   164,    35,   304,
      70,   106,   147,   295,    36,    37,   168,   169,    38,   322,
     339,   340,   343,   357,    39,    71,    72,   139,   140,    73,
     161,   162,   200,   201,   166,   208,   209,   257,   278,   302,
      40,    41,    42,    90
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      80,   170,    74,     4,   211,    84,    98,   142,   143,   144,
     145,    85,   136,   132,   141,   141,   141,   141,   141,   264,
       4,   330,    48,   110,    49,    83,   128,   125,    81,   355,
     273,   104,   105,   236,    89,   344,   238,    51,    91,    92,
     346,    82,    95,    96,    97,   116,   117,     4,   224,   380,
     381,   382,    75,    76,    77,    78,    79,    88,   270,   274,
      86,   174,    93,   148,   149,   150,    94,   118,   275,    99,
     155,   156,   157,   158,   258,   259,   126,   120,   121,   390,
     100,   265,   266,    64,   114,   115,   116,   117,   261,   131,
     133,   229,   391,   126,   138,   138,   138,   138,   138,   141,
     356,    57,   114,   115,   116,   117,   152,   298,   154,   276,
     153,   191,   265,   266,   160,   228,    61,   167,   101,   279,
     172,   207,    62,    63,   175,    65,    66,   133,   392,   102,
     181,   114,   115,   116,   117,   111,   103,   192,   107,   242,
     114,   115,   116,   117,   108,   109,   122,   231,   232,   233,
     193,   114,   115,   116,   117,   197,   119,   195,   133,   178,
      98,   123,   309,   129,   114,   115,   116,   117,    43,   130,
      44,   160,   225,   377,   133,   124,   135,   152,   281,   138,
     378,   323,   114,   115,   116,   117,   328,   146,    45,   159,
     202,   235,   234,   160,   163,   289,   287,   288,   165,   171,
     114,   115,   116,   117,   379,   176,   227,   167,   114,   115,
     116,   117,     4,   286,   207,   207,   172,   307,   160,   310,
     311,   114,   115,   116,   117,    46,   114,   115,   116,   117,
     128,   177,   160,   179,   180,   182,   341,   318,   183,   320,
      47,    98,     4,   329,   114,   115,   116,   117,   184,    50,
     194,   114,   115,   116,   117,   207,   185,   207,   290,   186,
     345,   326,   361,   362,   363,   364,   187,   160,   188,   341,
     190,   198,   199,    51,   210,   114,   115,   116,   117,   203,
     212,    98,   221,   260,   223,   213,   226,   237,    52,    53,
      54,    55,    56,   240,   241,   243,    57,   244,   319,   263,
     269,   204,   271,   272,    58,    59,    60,   367,   368,   369,
     277,    61,   280,   282,   283,   284,   138,    62,    63,    64,
      65,    66,   296,    67,    68,    51,   297,   291,   299,   349,
      57,   294,   300,   387,   388,   389,   303,   301,    50,   308,
      52,    53,    54,    55,    56,    61,   306,   312,    57,   138,
     314,    62,    63,   313,    65,    66,    58,    59,    60,   205,
     206,   316,    51,    61,   317,   324,   327,    57,   331,    62,
      63,    64,    65,    66,   332,    67,    68,    52,    53,    54,
      55,    56,    61,   321,   334,    57,    51,   285,    62,    63,
     335,    65,    66,    58,    59,    60,   342,   347,   348,    51,
      61,    75,    76,    77,    78,    79,    62,    63,    64,    65,
      66,    51,    67,    68,    75,    76,    77,    78,    79,   350,
     351,   352,   353,   371,   325,   354,    52,    53,    54,    55,
      56,   359,    64,   360,    57,   372,   358,   137,   373,   374,
     375,   196,    58,    59,    60,    64,   376,   383,    51,    61,
     112,   384,   385,    87,   386,    62,    63,    64,    65,    66,
     333,    67,    68,    52,    53,    54,    55,    56,   315,   268,
     189,    57,    51,   214,   215,   216,   217,   218,   219,    58,
      59,    60,   293,   230,   305,    51,    61,    75,    76,    77,
      78,    79,    62,    63,    64,    65,    66,   262,    67,    68,
      75,    76,    77,    78,    79,   239,   370,     0,     0,     0,
      51,     0,     0,     0,   113,     0,     0,     0,    64,     0,
       0,   114,   115,   116,   117,    75,    76,    77,    78,    79,
       0,    64,     0,    51,     0,     0,   151,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,     0,    75,    76,
      77,    78,    79,     0,     0,     0,    64,     0,     0,     0,
       0,     0,     0,     0,   336,   337,   338,   255,   256,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,    64,
       0,   114,   115,   116,   117,     1,     2,     0,     0,     0,
       0,     0,     3,     4,     5,     6,     7,     8,     9,    10,
       0,     0,     0,    11,    12,    13,     0,     0,     0,     0,
       0,     0,    14,    15,     0,     0,     0,     0,     0,     0,
       0,    16,     0,    17,     0,     0,    18
};

static const yytype_int16 yycheck[] =
{
       5,   123,     4,    13,   168,    10,    50,   100,   101,   102,
     103,    16,    21,    20,    99,   100,   101,   102,   103,    20,
      13,   309,     9,    67,    11,    37,    91,    20,    10,    14,
      21,    88,    89,   198,     3,   323,   200,    44,    43,    44,
     328,    35,    47,    48,    49,    95,    96,    13,   176,    75,
      76,    77,    59,    60,    61,    62,    63,     0,   223,    21,
      44,   126,    11,   107,   108,   109,    11,    72,    21,    20,
     114,   115,   116,   117,    39,    40,    86,    82,    83,    21,
      20,    82,    83,    90,    93,    94,    95,    96,   210,    94,
      95,   184,    21,    86,    99,   100,   101,   102,   103,   184,
      85,    67,    93,    94,    95,    96,   111,   272,   113,   237,
     112,    22,    82,    83,   119,   180,    82,   122,    20,   241,
     125,   165,    88,    89,   129,    91,    92,   132,    21,    20,
     135,    93,    94,    95,    96,    34,    20,    22,    20,   204,
      93,    94,    95,    96,    20,    20,    41,   191,   192,   193,
      22,    93,    94,    95,    96,   160,    37,   159,   163,   132,
     204,    49,   284,    42,    93,    94,    95,    96,     9,    90,
      11,   176,   177,    22,   179,    45,    42,   182,   243,   184,
      22,   303,    93,    94,    95,    96,   308,    22,    29,    22,
     163,   196,   194,   198,    20,   260,   258,   259,    38,    91,
      93,    94,    95,    96,    22,    42,   179,   212,    93,    94,
      95,    96,    13,   257,   258,   259,   221,   282,   223,   284,
     285,    93,    94,    95,    96,    66,    93,    94,    95,    96,
     295,    42,   237,    22,    86,    34,   321,   299,    21,   301,
      81,   285,    13,   308,    93,    94,    95,    96,    22,    20,
      22,    93,    94,    95,    96,   299,    21,   301,   263,    21,
     325,   305,    70,    71,    72,    73,    21,   272,    21,   354,
      68,    22,    64,    44,    49,    93,    94,    95,    96,    36,
      22,   325,    22,    20,    20,    35,    21,    65,    59,    60,
      61,    62,    63,    21,    20,    20,    67,    78,   300,     9,
      21,    20,    20,    20,    75,    76,    77,   351,   352,   353,
       7,    82,    21,    20,    80,    20,   321,    88,    89,    90,
      91,    92,    21,    94,    95,    44,    90,    88,    42,   334,
      67,    47,     4,   377,   378,   379,    22,     8,    20,    20,
      59,    60,    61,    62,    63,    82,    21,    21,    67,   354,
      48,    88,    89,    21,    91,    92,    75,    76,    77,    78,
      79,    21,    44,    82,    21,    21,    21,    67,    21,    88,
      89,    90,    91,    92,    21,    94,    95,    59,    60,    61,
      62,    63,    82,    84,    49,    67,    44,    20,    88,    89,
      69,    91,    92,    75,    76,    77,    87,    21,    21,    44,
      82,    59,    60,    61,    62,    63,    88,    89,    90,    91,
      92,    44,    94,    95,    59,    60,    61,    62,    63,    20,
      20,    20,    20,    49,    20,    22,    59,    60,    61,    62,
      63,    21,    90,    21,    67,    49,    88,    95,    49,    49,
      21,    86,    75,    76,    77,    90,    22,    74,    44,    82,
      22,    88,    88,    18,   376,    88,    89,    90,    91,    92,
     313,    94,    95,    59,    60,    61,    62,    63,   295,   221,
     146,    67,    44,    26,    27,    28,    29,    30,    31,    75,
      76,    77,   268,   189,   280,    44,    82,    59,    60,    61,
      62,    63,    88,    89,    90,    91,    92,   212,    94,    95,
      59,    60,    61,    62,    63,   201,   354,    -1,    -1,    -1,
      44,    -1,    -1,    -1,    86,    -1,    -1,    -1,    90,    -1,
      -1,    93,    94,    95,    96,    59,    60,    61,    62,    63,
      -1,    90,    -1,    44,    -1,    -1,    95,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    77,    79,    80,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    90,
      -1,    93,    94,    95,    96,     5,     6,    -1,    -1,    -1,
      -1,    -1,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    43,    -1,    -1,    46
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    12,    13,    14,    15,    16,    17,    18,
      19,    23,    24,    25,    32,    33,    41,    43,    46,    99,
     100,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   116,   118,   119,   126,   132,   133,   136,   142,
     158,   159,   160,     9,    11,    29,    66,    81,     9,    11,
      20,    44,    59,    60,    61,    62,    63,    67,    75,    76,
      77,    82,    88,    89,    90,    91,    92,    94,    95,   101,
     128,   143,   144,   147,   143,    59,    60,    61,    62,    63,
     101,    10,    35,    37,   101,   101,    44,   100,     0,     3,
     161,   101,   101,    11,    11,   101,   101,   101,   144,    20,
      20,    20,    20,    20,    88,    89,   129,    20,    20,    20,
     144,    34,    22,    86,    93,    94,    95,    96,   101,    37,
     101,   101,    41,    49,    45,    20,    86,   117,   136,    42,
      90,   101,    20,   101,   102,    42,    21,    95,   101,   145,
     146,   147,   145,   145,   145,   145,    22,   130,   144,   144,
     144,    95,   101,   143,   101,   144,   144,   144,   144,    22,
     101,   148,   149,    20,   125,    38,   152,   101,   134,   135,
     128,    91,   101,   121,   136,   101,    42,    42,   102,    22,
      86,   101,    34,    21,    22,    21,    21,    21,    21,   129,
      68,    22,    22,    22,    22,   143,    86,   101,    22,    64,
     150,   151,   102,    36,    20,    78,    79,   144,   153,   154,
      49,   152,    22,    35,    26,    27,    28,    29,    30,    31,
     124,    22,   120,    20,   148,   101,    21,   102,   136,   145,
     130,   144,   144,   144,   143,   101,   149,    65,   152,   150,
      21,    20,   136,    20,    78,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    79,    80,   155,    39,    40,
      20,   128,   134,     9,    20,    82,    83,   122,   121,    21,
     149,    20,    20,    21,    21,    21,   148,     7,   156,   128,
      21,   136,    20,    80,    20,    20,   144,   153,   153,   136,
     101,    88,   123,   120,    47,   131,    21,    90,   149,    42,
       4,     8,   157,    22,   127,   155,    21,   136,    20,   128,
     136,   136,    21,    21,    48,   117,    21,    21,   153,   143,
     153,    84,   137,   128,    21,    20,   144,    21,   128,   136,
     127,    21,    21,   122,    49,    69,    75,    76,    77,   138,
     139,   147,    87,   140,   127,   136,   127,    21,    21,   101,
      20,    20,    20,    20,    22,    14,    85,   141,    88,    21,
      21,    70,    71,    72,    73,   114,   115,   144,   144,   144,
     138,    49,    49,    49,    49,    21,    22,    22,    22,    22,
      75,    76,    77,    74,    88,    88,   114,   144,   144,   144,
      21,    21,    21
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    98,    99,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   101,   101,   101,   101,   101,
     101,   101,   102,   102,   102,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   112,   113,   114,   114,
     115,   115,   115,   115,   115,   115,   116,   117,   117,   117,
     118,   118,   119,   120,   120,   121,   121,   122,   122,   122,
     123,   124,   124,   124,   124,   124,   124,   125,   125,   126,
     127,   127,   128,   128,   128,   128,   128,   128,   129,   129,
     130,   130,   131,   131,   132,   133,   134,   134,   135,   135,
     136,   137,   137,   138,   138,   139,   139,   139,   139,   140,
     140,   141,   141,   141,   142,   143,   143,   143,   143,   143,
     143,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   145,
     145,   146,   146,   146,   147,   147,   148,   148,   148,   149,
     149,   150,   150,   151,   152,   152,   153,   153,   153,   153,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     156,   156,   157,   157,   158,   159,   160,   161,   161
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     3,     2,     2,     8,     9,    13,     1,     3,
       3,     3,     3,     3,     3,     3,     5,     0,     2,     1,
       9,     4,     6,     0,     3,     6,     3,     1,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     0,     3,     9,
       0,     3,     1,     1,     1,     1,     4,     1,     1,     1,
       0,     3,     0,     4,     4,     5,     1,     3,     3,     5,
      10,     0,     2,     1,     3,     2,     6,     6,     6,     0,
       2,     0,     1,     1,     2,     1,     2,     3,     3,     4,
       5,     3,     3,     3,     3,     3,     6,     6,     6,     2,
       1,     1,     1,     3,     4,     4,     4,     4,     4,     1,
       3,     0,     1,     1,     1,     3,     1,     2,     3,     1,
       3,     0,     2,     5,     0,     2,     0,     1,     3,     3,
       3,     5,     5,     6,     6,     7,     4,     5,     5,     7,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     3,     0,     2,     7,     2,     4,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, flag, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner, flag); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  YY_USE (flag);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner, flag);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner, flag);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner, flag); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  YY_USE (flag);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 288 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 2026 "yacc_sql.cpp"
    break;

  case 25: /* id_maybe_keyword: ID  */
#line 320 "yacc_sql.y"
     {
    (yyval.string) = (yyvsp[0].string);
  }
#line 2034 "yacc_sql.cpp"
    break;

  case 26: /* id_maybe_keyword: DATA  */
#line 323 "yacc_sql.y"
         {
    (yyval.string) = strdup("data");
  }
#line 2042 "yacc_sql.cpp"
    break;

  case 27: /* id_maybe_keyword: MIN  */
#line 326 "yacc_sql.y"
        {
    (yyval.string) = strdup("min");
  }
#line 2050 "yacc_sql.cpp"
    break;

  case 28: /* id_maybe_keyword: MAX  */
#line 329 "yacc_sql.y"
        {
    (yyval.string) = strdup("max");
  }
#line 2058 "yacc_sql.cpp"
    break;

  case 29: /* id_maybe_keyword: AVG  */
#line 332 "yacc_sql.y"
        {
    (yyval.string) = strdup("avg");
  }
#line 2066 "yacc_sql.cpp"
    break;

  case 30: /* id_maybe_keyword: SUM  */
#line 335 "yacc_sql.y"
        {
    (yyval.string) = strdup("sum");
  }
#line 2074 "yacc_sql.cpp"
    break;

  case 31: /* id_maybe_keyword: COUNT  */
#line 338 "yacc_sql.y"
          {
    (yyval.string) = strdup("count");
  }
#line 2082 "yacc_sql.cpp"
    break;

  case 32: /* id_list: %empty  */
#line 344 "yacc_sql.y"
  {
    (yyval.id_list) = nullptr;
  }
#line 2090 "yacc_sql.cpp"
    break;

  case 33: /* id_list: id_maybe_keyword  */
#line 347 "yacc_sql.y"
                     {
    (yyval.id_list) = new std::vector<std::string>;
    (yyval.id_list)->emplace_back((yyvsp[0].string));
    free((yyvsp[0].string));
  }
#line 2100 "yacc_sql.cpp"
    break;

  case 34: /* id_list: id_maybe_keyword COMMA id_list  */
#line 352 "yacc_sql.y"
                                   {
    if ((yyvsp[0].id_list) != nullptr) {
      (yyval.id_list) = (yyvsp[0].id_list);
    } else {
      (yyval.id_list) = new std::vector<std::string>;
    }
    (yyval.id_list)->emplace((yyval.id_list)->begin(), (yyvsp[-2].string));
    free((yyvsp[-2].string));
  }
#line 2114 "yacc_sql.cpp"
    break;

  case 35: /* id_list: LBRACE id_list RBRACE  */
#line 361 "yacc_sql.y"
                          {
    (yyval.id_list) = (yyvsp[-1].id_list);
  }
#line 2122 "yacc_sql.cpp"
    break;

  case 36: /* exit_stmt: EXIT  */
#line 367 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 2131 "yacc_sql.cpp"
    break;

  case 37: /* help_stmt: HELP  */
#line 373 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2139 "yacc_sql.cpp"
    break;

  case 38: /* sync_stmt: SYNC  */
#line 378 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2147 "yacc_sql.cpp"
    break;

  case 39: /* begin_stmt: TRX_BEGIN  */
#line 384 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2155 "yacc_sql.cpp"
    break;

  case 40: /* commit_stmt: TRX_COMMIT  */
#line 390 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2163 "yacc_sql.cpp"
    break;

  case 41: /* rollback_stmt: TRX_ROLLBACK  */
#line 396 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2171 "yacc_sql.cpp"
    break;

  case 42: /* drop_table_stmt: DROP TABLE id_maybe_keyword  */
#line 402 "yacc_sql.y"
                                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2181 "yacc_sql.cpp"
    break;

  case 43: /* show_tables_stmt: SHOW TABLES  */
#line 409 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2189 "yacc_sql.cpp"
    break;

  case 44: /* desc_table_stmt: DESC id_maybe_keyword  */
#line 415 "yacc_sql.y"
                           {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2199 "yacc_sql.cpp"
    break;

  case 45: /* create_index_stmt: CREATE INDEX id_maybe_keyword ON id_maybe_keyword LBRACE rel_list RBRACE  */
#line 424 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      create_index.unique = false;

      if ((yyvsp[-1].relation_list) != nullptr) {
        std::vector<std::string> attributes;
        for (auto &rel : *(yyvsp[-1].relation_list)) {
          attributes.emplace_back(rel.name);
        }
        create_index.attributes.swap(attributes);
        delete (yyvsp[-1].relation_list);
      }
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 2222 "yacc_sql.cpp"
    break;

  case 46: /* create_index_stmt: CREATE UNIQUE INDEX id_maybe_keyword ON id_maybe_keyword LBRACE rel_list RBRACE  */
#line 443 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      create_index.unique = true;
      if ((yyvsp[-1].relation_list) != nullptr) {        
        std::vector<std::string> attributes;
        for (auto &rel : *(yyvsp[-1].relation_list)) {
          attributes.emplace_back(rel.name);
        }
        create_index.attributes.swap(attributes);
        delete (yyvsp[-1].relation_list);
      }
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 2244 "yacc_sql.cpp"
    break;

  case 47: /* create_vector_index_stmt: CREATE VECTOR_T INDEX ID ON relation LBRACE ID RBRACE WITH LBRACE vector_index_param_list RBRACE  */
#line 464 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VECTOR_INDEX);
      CreateVectorIndexSqlNode &create_vector_index = (yyval.sql_node)->create_vector_index;
      create_vector_index.index_name    = (yyvsp[-9].string);
      free((yyvsp[-9].string));
      create_vector_index.relation_name = (yyvsp[-7].relation)->name;
      create_vector_index.attribute     = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      create_vector_index.distance_algo = DISTANCE_ALGO::NONE;
      create_vector_index.type          = false;
      create_vector_index.centroids     = -1;
      create_vector_index.probes        = -1;

      int param_count = (yyvsp[-1].vec_index_param_list)->size();
      if(param_count != static_cast<int>(VecIndexField::FIELD_COUNT)){
        yyerror(&(yylsp[-12]), NULL, sql_result, NULL, SCF_ERROR_CREATE_VECTOR_INDEX, "param mismatch, need: {distance, type, lists, probes}");
      } else {
        bool flag = true;
        string err_msg;
        for(auto param: (*(yyvsp[-1].vec_index_param_list))){
          switch (static_cast<int>(param.field)){
            case static_cast<int>(VecIndexField::DISTANCE_FIELD): {
              if(create_vector_index.distance_algo != DISTANCE_ALGO::NONE){
                flag = false;
                err_msg = "distance field already set";
              }
              create_vector_index.distance_algo = static_cast<DISTANCE_ALGO>(param.value);
            } break;
            case static_cast<int>(VecIndexField::TYPE_FIELD): {
              if(create_vector_index.type){
                flag = false;
                err_msg = "index type field already set";
              }
              create_vector_index.type = true;
            } break;
            case static_cast<int>(VecIndexField::LISTS_FIELD): {
              if(create_vector_index.centroids != -1){
                flag = false;
                err_msg = "lists field already set";
              }
              if(param.value < 0){
                flag = false;
                err_msg = "lists field must be positive integer";
              }
              create_vector_index.centroids = param.value;
            } break;
            case static_cast<int>(VecIndexField::PROBES_FIELD): {
              if(create_vector_index.probes != -1){
                flag = false;
                err_msg = "probe field already set";
              }
              if(param.value < 0){
                flag = false;
                err_msg = "probe field must be positive integer";
              }
              create_vector_index.probes = param.value;
            } break;
            default: {
              flag = false;
              break;
            }
          }
          if(!flag) break;
        }
        if(!flag){
          yyerror(&(yylsp[-12]), NULL, sql_result, NULL, SCF_ERROR_CREATE_VECTOR_INDEX, err_msg.c_str());
        }
      }
      // error handling
    }
#line 2320 "yacc_sql.cpp"
    break;

  case 48: /* vector_index_param_list: vector_index_field  */
#line 538 "yacc_sql.y"
                       {
      (yyval.vec_index_param_list) = new std::vector<VecIndexFieldAnno>();
      (yyval.vec_index_param_list)->push_back((yyvsp[0].vec_index_param));
    }
#line 2329 "yacc_sql.cpp"
    break;

  case 49: /* vector_index_param_list: vector_index_field COMMA vector_index_param_list  */
#line 542 "yacc_sql.y"
                                                       {
      if((yyvsp[0].vec_index_param_list) != nullptr){
        (yyval.vec_index_param_list) = (yyvsp[0].vec_index_param_list);
      } else {
        (yyval.vec_index_param_list) = new std::vector<VecIndexFieldAnno>();
      }
      (yyval.vec_index_param_list)->push_back((yyvsp[-2].vec_index_param));
    }
#line 2342 "yacc_sql.cpp"
    break;

  case 50: /* vector_index_field: DISTANCE EQ L2_DISTANCE  */
#line 554 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::DISTANCE_FIELD, static_cast<int>(DISTANCE_ALGO::L2_DISTANCE)};
    }
#line 2350 "yacc_sql.cpp"
    break;

  case 51: /* vector_index_field: DISTANCE EQ COSINE_DISTANCE  */
#line 558 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::DISTANCE_FIELD, static_cast<int>(DISTANCE_ALGO::COSINE_DISTANCE)};
    }
#line 2358 "yacc_sql.cpp"
    break;

  case 52: /* vector_index_field: DISTANCE EQ INNER_PRODUCT  */
#line 562 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::DISTANCE_FIELD, static_cast<int>(DISTANCE_ALGO::INNER_PRODUCT)};
    }
#line 2366 "yacc_sql.cpp"
    break;

  case 53: /* vector_index_field: TYPE EQ IVFFLAT  */
#line 566 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::TYPE_FIELD, 1};
    }
#line 2374 "yacc_sql.cpp"
    break;

  case 54: /* vector_index_field: LISTS EQ NUMBER  */
#line 570 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::LISTS_FIELD, (yyvsp[0].number)};
    }
#line 2382 "yacc_sql.cpp"
    break;

  case 55: /* vector_index_field: PROBES EQ NUMBER  */
#line 574 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::PROBES_FIELD, (yyvsp[0].number)};
    }
#line 2390 "yacc_sql.cpp"
    break;

  case 56: /* drop_index_stmt: DROP INDEX id_maybe_keyword ON id_maybe_keyword  */
#line 581 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2402 "yacc_sql.cpp"
    break;

  case 57: /* as_select: %empty  */
#line 591 "yacc_sql.y"
  {
    (yyval.sql_node) = nullptr;
  }
#line 2410 "yacc_sql.cpp"
    break;

  case 58: /* as_select: AS select_stmt  */
#line 594 "yacc_sql.y"
                   {
    (yyval.sql_node) = (yyvsp[0].sql_node);
  }
#line 2418 "yacc_sql.cpp"
    break;

  case 59: /* as_select: select_stmt  */
#line 597 "yacc_sql.y"
                {
    (yyval.sql_node) = (yyvsp[0].sql_node);
  }
#line 2426 "yacc_sql.cpp"
    break;

  case 60: /* create_table_stmt: CREATE TABLE id_maybe_keyword LBRACE attr_def attr_def_list RBRACE storage_format as_select  */
#line 603 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-6].string);
      free((yyvsp[-6].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-3].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-4].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-4].attr_info);
      if ((yyvsp[-1].string) != nullptr) {
        create_table.storage_format = (yyvsp[-1].string);
        free((yyvsp[-1].string));
      }

      if ((yyvsp[0].sql_node) != nullptr) {
        create_table.has_subquery = true;
        create_table.subquery = (yyvsp[0].sql_node);
      } else {
        create_table.has_subquery = false;
        create_table.subquery = nullptr;
      }
    }
#line 2459 "yacc_sql.cpp"
    break;

  case 61: /* create_table_stmt: CREATE TABLE id_maybe_keyword as_select  */
#line 631 "yacc_sql.y"
                                              {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-1].string);
      free((yyvsp[-1].string));
      if ((yyvsp[0].sql_node) != nullptr) {
        create_table.has_subquery = true;
        create_table.subquery = (yyvsp[0].sql_node);
      } else {
        create_table.has_subquery = false;
        create_table.subquery = nullptr;
      }
    }
#line 2477 "yacc_sql.cpp"
    break;

  case 62: /* create_view_stmt: CREATE VIEW id_maybe_keyword id_list AS select_stmt  */
#line 646 "yacc_sql.y"
                                                      {
    (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
    (yyval.sql_node)->create_view.view_name = (yyvsp[-3].string);
    free((yyvsp[-3].string));
    if ((yyvsp[-2].id_list) != nullptr) {
      (yyval.sql_node)->create_view.col_names.swap(*(yyvsp[-2].id_list));
      delete (yyvsp[-2].id_list);
    }
    (yyval.sql_node)->create_view.selection = (yyvsp[0].sql_node);
    (yyval.sql_node)->create_view.sql_str = (yyvsp[0].sql_node)->sql_str;
  }
#line 2493 "yacc_sql.cpp"
    break;

  case 63: /* attr_def_list: %empty  */
#line 660 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2501 "yacc_sql.cpp"
    break;

  case 64: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 664 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2515 "yacc_sql.cpp"
    break;

  case 65: /* attr_def: id_maybe_keyword type LBRACE number RBRACE nullable_spec  */
#line 677 "yacc_sql.y"
  {
    (yyval.attr_info) = new AttrInfoSqlNode;
    (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
    (yyval.attr_info)->name = (yyvsp[-5].string);
    (yyval.attr_info)->length = (yyvsp[-2].number);
    (yyval.attr_info)->nullable = (yyvsp[0].nullable_spec);
    free((yyvsp[-5].string));
  }
#line 2528 "yacc_sql.cpp"
    break;

  case 66: /* attr_def: id_maybe_keyword type nullable_spec  */
#line 686 "yacc_sql.y"
  {
    (yyval.attr_info) = new AttrInfoSqlNode;
    (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
    (yyval.attr_info)->name = (yyvsp[-2].string);
    if ((AttrType)(yyvsp[-1].number) == AttrType::DATES) {
      (yyval.attr_info)->length = 8;
    } else if ((AttrType)(yyvsp[-1].number) == AttrType::CHARS) {
      (yyval.attr_info)->length = 32;
    } else if ((AttrType)(yyvsp[-1].number) == AttrType::TEXTS) {
      (yyval.attr_info)->length = LOB_OVERFLOW_THRESHOLD;
    } else {
      (yyval.attr_info)->length = 4;
    }
    (yyval.attr_info)->nullable = (yyvsp[0].nullable_spec);
    free((yyvsp[-2].string));
  }
#line 2549 "yacc_sql.cpp"
    break;

  case 67: /* nullable_spec: NULL_T  */
#line 705 "yacc_sql.y"
         { (yyval.nullable_spec) = true; }
#line 2555 "yacc_sql.cpp"
    break;

  case 68: /* nullable_spec: NOT_NULL_T  */
#line 706 "yacc_sql.y"
               { (yyval.nullable_spec) = false; }
#line 2561 "yacc_sql.cpp"
    break;

  case 69: /* nullable_spec: %empty  */
#line 707 "yacc_sql.y"
                { (yyval.nullable_spec) = true; }
#line 2567 "yacc_sql.cpp"
    break;

  case 70: /* number: NUMBER  */
#line 711 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2573 "yacc_sql.cpp"
    break;

  case 71: /* type: INT_T  */
#line 714 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2579 "yacc_sql.cpp"
    break;

  case 72: /* type: STRING_T  */
#line 715 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2585 "yacc_sql.cpp"
    break;

  case 73: /* type: FLOAT_T  */
#line 716 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2591 "yacc_sql.cpp"
    break;

  case 74: /* type: VECTOR_T  */
#line 717 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2597 "yacc_sql.cpp"
    break;

  case 75: /* type: DATE_T  */
#line 718 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2603 "yacc_sql.cpp"
    break;

  case 76: /* type: TEXT_T  */
#line 719 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2609 "yacc_sql.cpp"
    break;

  case 77: /* insert_name_lists: %empty  */
#line 723 "yacc_sql.y"
  {
    (yyval.id_list) = nullptr;
  }
#line 2617 "yacc_sql.cpp"
    break;

  case 78: /* insert_name_lists: LBRACE id_list RBRACE  */
#line 726 "yacc_sql.y"
                          {
    (yyval.id_list) = (yyvsp[-1].id_list);
  }
#line 2625 "yacc_sql.cpp"
    break;

  case 79: /* insert_stmt: INSERT INTO id_maybe_keyword insert_name_lists VALUES LBRACE value value_list RBRACE  */
#line 732 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-6].string);
      if ((yyvsp[-5].id_list) != nullptr) {
        (yyval.sql_node)->insertion.insertion_names.swap(*(yyvsp[-5].id_list));
        delete (yyvsp[-5].id_list);
      }
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-6].string));
    }
#line 2646 "yacc_sql.cpp"
    break;

  case 80: /* value_list: %empty  */
#line 752 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2654 "yacc_sql.cpp"
    break;

  case 81: /* value_list: COMMA value value_list  */
#line 755 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2668 "yacc_sql.cpp"
    break;

  case 82: /* value: NUMBER  */
#line 766 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2677 "yacc_sql.cpp"
    break;

  case 83: /* value: FLOAT  */
#line 770 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2686 "yacc_sql.cpp"
    break;

  case 84: /* value: SSS  */
#line 774 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2697 "yacc_sql.cpp"
    break;

  case 85: /* value: DATE  */
#line 780 "yacc_sql.y"
          {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      if (!is_valid_date(tmp)) {
        (yyval.value) = new Value(AttrType::UNDEFINED, nullptr);
      } else {
        struct tm tm; bzero(&tm, sizeof(tm));
        strptime(tmp, "%Y-%m-%d", &tm);
        (yyval.value) = new Value(mktime(&tm));
      }
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2714 "yacc_sql.cpp"
    break;

  case 86: /* value: LBRACKET vector_elem vector_value_list RBRACKET  */
#line 792 "yacc_sql.y"
                                                      {
      vector<float>* cur = (yyvsp[-1].vector_elem_list);
      if((yyvsp[-1].vector_elem_list) == nullptr){
        cur = new vector<float>;
      }
      cur->push_back((float)(yyvsp[-2].floats));
      std::reverse(cur->begin(), cur->end());
      (yyval.value) = new Value(cur->data(), cur->size());
      delete cur;
    }
#line 2729 "yacc_sql.cpp"
    break;

  case 87: /* value: NULL_T  */
#line 802 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2738 "yacc_sql.cpp"
    break;

  case 88: /* vector_elem: NUMBER  */
#line 808 "yacc_sql.y"
           {
      (yyval.floats) = (float)(yyvsp[0].number);
      (yyloc) = (yylsp[0]);
    }
#line 2747 "yacc_sql.cpp"
    break;

  case 89: /* vector_elem: FLOAT  */
#line 812 "yacc_sql.y"
           {
      (yyval.floats) = (float)(yyvsp[0].floats);
      (yyloc) = (yylsp[0]);
    }
#line 2756 "yacc_sql.cpp"
    break;

  case 90: /* vector_value_list: %empty  */
#line 819 "yacc_sql.y"
    {
      (yyval.vector_elem_list) = nullptr;
    }
#line 2764 "yacc_sql.cpp"
    break;

  case 91: /* vector_value_list: COMMA vector_elem vector_value_list  */
#line 822 "yacc_sql.y"
                                         {
      (yyval.vector_elem_list) = (yyvsp[0].vector_elem_list);
      if((yyval.vector_elem_list) == nullptr){
        (yyval.vector_elem_list) = new vector<float>;
      }
      (yyval.vector_elem_list)->push_back((yyvsp[-1].floats));
    }
#line 2776 "yacc_sql.cpp"
    break;

  case 92: /* storage_format: %empty  */
#line 831 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2784 "yacc_sql.cpp"
    break;

  case 93: /* storage_format: STORAGE FORMAT EQ id_maybe_keyword  */
#line 835 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2792 "yacc_sql.cpp"
    break;

  case 94: /* delete_stmt: DELETE FROM id_maybe_keyword where  */
#line 842 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2806 "yacc_sql.cpp"
    break;

  case 95: /* update_stmt: UPDATE id_maybe_keyword SET set_clause_list where  */
#line 854 "yacc_sql.y"
  {
    (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
    (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
    if ((yyvsp[-1].set_clause_list) != nullptr) {
      (yyval.sql_node)->update.set_clauses.swap(*(yyvsp[-1].set_clause_list));
      delete (yyvsp[-1].set_clause_list);
    }
    if ((yyvsp[0].condition_list) != nullptr) {
      (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
    free((yyvsp[-3].string));
  }
#line 2824 "yacc_sql.cpp"
    break;

  case 96: /* set_clause_list: set_clause  */
#line 870 "yacc_sql.y"
             {
    (yyval.set_clause_list) = new std::vector<SetClauseSqlNode>;
    (yyval.set_clause_list)->emplace_back(*(yyvsp[0].set_clause));
    delete (yyvsp[0].set_clause);
  }
#line 2834 "yacc_sql.cpp"
    break;

  case 97: /* set_clause_list: set_clause COMMA set_clause_list  */
#line 876 "yacc_sql.y"
  {
    if ((yyvsp[0].set_clause_list) != nullptr) {
      (yyval.set_clause_list) = (yyvsp[0].set_clause_list);
    } else {
      (yyval.set_clause_list) = new std::vector<SetClauseSqlNode>;
    }
    (yyval.set_clause_list)->emplace((yyval.set_clause_list)->begin(), *(yyvsp[-2].set_clause));
    delete (yyvsp[-2].set_clause);
  }
#line 2848 "yacc_sql.cpp"
    break;

  case 98: /* set_clause: id_maybe_keyword EQ value  */
#line 888 "yacc_sql.y"
                            {
    (yyval.set_clause) = new SetClauseSqlNode;
    (yyval.set_clause)->attribute_name = (yyvsp[-2].string);
    (yyval.set_clause)->value = *(yyvsp[0].value);
    (yyval.set_clause)->has_subquery = false;
    (yyval.set_clause)->subquery = nullptr;
    free((yyvsp[-2].string));
    delete (yyvsp[0].value);
  }
#line 2862 "yacc_sql.cpp"
    break;

  case 99: /* set_clause: id_maybe_keyword EQ LBRACE select_stmt RBRACE  */
#line 897 "yacc_sql.y"
                                                  {
    (yyval.set_clause) = new SetClauseSqlNode;
    (yyval.set_clause)->attribute_name = (yyvsp[-4].string);
    (yyval.set_clause)->has_subquery = true;
    (yyval.set_clause)->subquery = (yyvsp[-1].sql_node);
    free((yyvsp[-4].string));
  }
#line 2874 "yacc_sql.cpp"
    break;

  case 100: /* select_stmt: SELECT expression_list FROM rel_list join_list where group_by having order_by limit  */
#line 907 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      (yyval.sql_node)->sql_str = token_name(sql_string, &(yyloc));
      if ((yyvsp[-8].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-8].expression_list));
        delete (yyvsp[-8].expression_list);
      }

      if ((yyvsp[-6].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-6].relation_list));
        delete (yyvsp[-6].relation_list);
      }

      if ((yyvsp[-5].join_tuple_list) != nullptr) {
        (yyval.sql_node)->selection.join_relations.swap(*(std::get<0>(*(yyvsp[-5].join_tuple_list))));
        (yyval.sql_node)->selection.join_conditions.swap(*(std::get<1>(*(yyvsp[-5].join_tuple_list))));
        delete std::get<0>(*(yyvsp[-5].join_tuple_list));
        delete std::get<1>(*(yyvsp[-5].join_tuple_list));
        std::reverse((yyval.sql_node)->selection.join_relations.begin(), (yyval.sql_node)->selection.join_relations.end());
        std::reverse((yyval.sql_node)->selection.join_conditions.begin(), (yyval.sql_node)->selection.join_conditions.end());
        delete (yyvsp[-5].join_tuple_list);
      }

      if ((yyvsp[-4].condition_list) != nullptr) {
        ConditionSqlNode last = (yyvsp[-4].condition_list)->back();
        if (last.flag) {
          (yyvsp[-4].condition_list)->pop_back();
          (yyval.sql_node)->selection.is_and = 0;
        }
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-4].condition_list));
        delete (yyvsp[-4].condition_list);
      }

      if ((yyvsp[-3].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-3].expression_list));
        delete (yyvsp[-3].expression_list);
      }

      // 处理having，having和where不能共存，先不考虑出现这种测试用例
      if ((yyvsp[-2].condition_list) != nullptr) {
        (yyval.sql_node)->selection.having.swap(*(yyvsp[-2].condition_list));
        delete (yyvsp[-2].condition_list);
      }

			if ((yyvsp[-1].order_by_list) != nullptr) {
				(yyval.sql_node)->selection.order_by.swap(*(yyvsp[-1].order_by_list));
				delete (yyvsp[-1].order_by_list);
			}
      (yyval.sql_node)->selection.limits = (yyvsp[0].number);
	}
#line 2929 "yacc_sql.cpp"
    break;

  case 101: /* order_by: %empty  */
#line 961 "yacc_sql.y"
        {
		(yyval.order_by_list) = nullptr;
	}
#line 2937 "yacc_sql.cpp"
    break;

  case 102: /* order_by: ORDER_BY order_by_list  */
#line 965 "yacc_sql.y"
        {
		(yyval.order_by_list) = (yyvsp[0].order_by_list);
	}
#line 2945 "yacc_sql.cpp"
    break;

  case 103: /* order_by_list: order_by_item  */
#line 972 "yacc_sql.y"
        {
		(yyval.order_by_list) = new std::vector<OrderByItem>;
		(yyval.order_by_list)->emplace_back(*(yyvsp[0].order_by_item));
		delete (yyvsp[0].order_by_item);
	}
#line 2955 "yacc_sql.cpp"
    break;

  case 104: /* order_by_list: order_by_item COMMA order_by_list  */
#line 978 "yacc_sql.y"
        {
		if ((yyvsp[0].order_by_list) != nullptr) {
			(yyval.order_by_list) = (yyvsp[0].order_by_list);
		} else {
			(yyval.order_by_list) = new std::vector<OrderByItem>;
		}
		(yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), *(yyvsp[-2].order_by_item));
		delete (yyvsp[-2].order_by_item);
	}
#line 2969 "yacc_sql.cpp"
    break;

  case 105: /* order_by_item: rel_attr asc_desc  */
#line 991 "yacc_sql.y"
        {
		(yyval.order_by_item) = new OrderByItem;
		(yyval.order_by_item)->attr = *(yyvsp[-1].rel_attr);
		(yyval.order_by_item)->asc = (yyvsp[0].asc_desc);
    (yyval.order_by_item)->expression = nullptr;
		delete (yyvsp[-1].rel_attr);
	}
#line 2981 "yacc_sql.cpp"
    break;

  case 106: /* order_by_item: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 998 "yacc_sql.y"
                                                          {
    (yyval.order_by_item) = new OrderByItem;
    (yyval.order_by_item)->expression = create_arithmetic_expression(ArithmeticExpr::Type::L2_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
  }
#line 2990 "yacc_sql.cpp"
    break;

  case 107: /* order_by_item: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 1002 "yacc_sql.y"
                                                              {
    (yyval.order_by_item) = new OrderByItem;
    (yyval.order_by_item)->expression = create_arithmetic_expression(ArithmeticExpr::Type::COS_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
  }
#line 2999 "yacc_sql.cpp"
    break;

  case 108: /* order_by_item: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 1006 "yacc_sql.y"
                                                            {
    (yyval.order_by_item) = new OrderByItem;
    (yyval.order_by_item)->expression = create_arithmetic_expression(ArithmeticExpr::Type::INN_PDT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
  }
#line 3008 "yacc_sql.cpp"
    break;

  case 109: /* limit: %empty  */
#line 1014 "yacc_sql.y"
  {
    (yyval.number) = -1; // set to invalid number
  }
#line 3016 "yacc_sql.cpp"
    break;

  case 110: /* limit: LIMIT NUMBER  */
#line 1018 "yacc_sql.y"
  {
    (yyval.number) = (yyvsp[0].number);
  }
#line 3024 "yacc_sql.cpp"
    break;

  case 111: /* asc_desc: %empty  */
#line 1024 "yacc_sql.y"
        {
		(yyval.asc_desc) = true; // default is ascending
	}
#line 3032 "yacc_sql.cpp"
    break;

  case 112: /* asc_desc: ASC  */
#line 1028 "yacc_sql.y"
        {
		(yyval.asc_desc) = true;
	}
#line 3040 "yacc_sql.cpp"
    break;

  case 113: /* asc_desc: DESC  */
#line 1032 "yacc_sql.y"
        {
		(yyval.asc_desc) = false;
	}
#line 3048 "yacc_sql.cpp"
    break;

  case 114: /* calc_stmt: CALC expression_list  */
#line 1039 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 3058 "yacc_sql.cpp"
    break;

  case 115: /* expression_list: expression  */
#line 1048 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 3067 "yacc_sql.cpp"
    break;

  case 116: /* expression_list: expression id_maybe_keyword  */
#line 1052 "yacc_sql.y"
                                  {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      (yyval.expression_list)->back()->set_name((yyvsp[0].string));
      (yyval.expression_list)->back()->set_aliased(true);
      free((yyvsp[0].string));
    }
#line 3079 "yacc_sql.cpp"
    break;

  case 117: /* expression_list: expression AS id_maybe_keyword  */
#line 1059 "yacc_sql.y"
                                     {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
      (yyval.expression_list)->back()->set_name((yyvsp[0].string));
      (yyval.expression_list)->back()->set_aliased(true);
      free((yyvsp[0].string));
    }
#line 3091 "yacc_sql.cpp"
    break;

  case 118: /* expression_list: expression COMMA expression_list  */
#line 1067 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 3104 "yacc_sql.cpp"
    break;

  case 119: /* expression_list: expression id_maybe_keyword COMMA expression_list  */
#line 1076 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-3].expression));
      (yyval.expression_list)->front()->set_name((yyvsp[-2].string));
      (yyval.expression_list)->front()->set_aliased(true);
      free((yyvsp[-2].string));
    }
#line 3120 "yacc_sql.cpp"
    break;

  case 120: /* expression_list: expression AS id_maybe_keyword COMMA expression_list  */
#line 1088 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-4].expression));
      (yyval.expression_list)->front()->set_name((yyvsp[-2].string));
      (yyval.expression_list)->front()->set_aliased(true);
      free((yyvsp[-2].string));
    }
#line 3136 "yacc_sql.cpp"
    break;

  case 121: /* expression: expression '+' expression  */
#line 1101 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3144 "yacc_sql.cpp"
    break;

  case 122: /* expression: expression '-' expression  */
#line 1104 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3152 "yacc_sql.cpp"
    break;

  case 123: /* expression: expression '*' expression  */
#line 1107 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3160 "yacc_sql.cpp"
    break;

  case 124: /* expression: expression '/' expression  */
#line 1110 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3168 "yacc_sql.cpp"
    break;

  case 125: /* expression: LBRACE expression RBRACE  */
#line 1113 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3177 "yacc_sql.cpp"
    break;

  case 126: /* expression: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 1117 "yacc_sql.y"
                                                            {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3185 "yacc_sql.cpp"
    break;

  case 127: /* expression: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 1120 "yacc_sql.y"
                                                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COS_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3193 "yacc_sql.cpp"
    break;

  case 128: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 1123 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INN_PDT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3201 "yacc_sql.cpp"
    break;

  case 129: /* expression: '-' expression  */
#line 1126 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3209 "yacc_sql.cpp"
    break;

  case 130: /* expression: value  */
#line 1129 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 3219 "yacc_sql.cpp"
    break;

  case 131: /* expression: rel_attr  */
#line 1134 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 3230 "yacc_sql.cpp"
    break;

  case 132: /* expression: '*'  */
#line 1140 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 3238 "yacc_sql.cpp"
    break;

  case 133: /* expression: id_maybe_keyword DOT '*'  */
#line 1143 "yacc_sql.y"
                               {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
    }
#line 3246 "yacc_sql.cpp"
    break;

  case 134: /* expression: MAX LBRACE agg_fun_attr_list RBRACE  */
#line 1148 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("max", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3254 "yacc_sql.cpp"
    break;

  case 135: /* expression: MIN LBRACE agg_fun_attr_list RBRACE  */
#line 1151 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("min", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3262 "yacc_sql.cpp"
    break;

  case 136: /* expression: COUNT LBRACE agg_fun_attr_list RBRACE  */
#line 1154 "yacc_sql.y"
                                            {
      (yyval.expression) = create_aggregate_expression("count", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3270 "yacc_sql.cpp"
    break;

  case 137: /* expression: AVG LBRACE agg_fun_attr_list RBRACE  */
#line 1157 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("avg", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3278 "yacc_sql.cpp"
    break;

  case 138: /* expression: SUM LBRACE agg_fun_attr_list RBRACE  */
#line 1160 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("sum", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3286 "yacc_sql.cpp"
    break;

  case 139: /* agg_fun_attr_list: agg_fun_attr  */
#line 1179 "yacc_sql.y"
                 {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3294 "yacc_sql.cpp"
    break;

  case 140: /* agg_fun_attr_list: agg_fun_attr COMMA agg_fun_attr_list  */
#line 1182 "yacc_sql.y"
                                           {
      (yyval.expression) = nullptr;
      // 到这里肯定有问题
      if ((yyvsp[0].expression)) {
        delete (yyvsp[0].expression);
      }
      if ((yyvsp[-2].expression)) {
        delete (yyvsp[-2].expression);
      }
      yyerror(&(yylsp[-2]), NULL, sql_result, NULL, SCF_ERROR_AGGREGATION, "aggregation func has too many fields");
    }
#line 3310 "yacc_sql.cpp"
    break;

  case 141: /* agg_fun_attr: %empty  */
#line 1196 "yacc_sql.y"
    {
      std::string null_string = "";
      (yyval.expression) = new UnboundFieldExpr(null_string, null_string);
      (yyval.expression)->set_name(null_string);
    }
#line 3320 "yacc_sql.cpp"
    break;

  case 142: /* agg_fun_attr: '*'  */
#line 1201 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 3328 "yacc_sql.cpp"
    break;

  case 143: /* agg_fun_attr: rel_attr  */
#line 1204 "yacc_sql.y"
               {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[0].rel_attr)->relation_name, (yyvsp[0].rel_attr)->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 3338 "yacc_sql.cpp"
    break;

  case 144: /* rel_attr: id_maybe_keyword  */
#line 1212 "yacc_sql.y"
                     {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3348 "yacc_sql.cpp"
    break;

  case 145: /* rel_attr: id_maybe_keyword DOT id_maybe_keyword  */
#line 1217 "yacc_sql.y"
                                            {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3360 "yacc_sql.cpp"
    break;

  case 146: /* relation: id_maybe_keyword  */
#line 1227 "yacc_sql.y"
                     {
      (yyval.relation) = new RelationSqlNode();
      (yyval.relation)->name = (yyvsp[0].string);
      (yyval.relation)->alias = "";
      free((yyvsp[0].string));
    }
#line 3371 "yacc_sql.cpp"
    break;

  case 147: /* relation: id_maybe_keyword id_maybe_keyword  */
#line 1233 "yacc_sql.y"
                                        {
      (yyval.relation) = new RelationSqlNode();
      (yyval.relation)->name = (yyvsp[-1].string);
      (yyval.relation)->alias = (yyvsp[0].string);
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3383 "yacc_sql.cpp"
    break;

  case 148: /* relation: id_maybe_keyword AS id_maybe_keyword  */
#line 1240 "yacc_sql.y"
                                           {
      (yyval.relation) = new RelationSqlNode();
      (yyval.relation)->name = (yyvsp[-2].string);
      (yyval.relation)->alias = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3395 "yacc_sql.cpp"
    break;

  case 149: /* rel_list: relation  */
#line 1249 "yacc_sql.y"
             {
      (yyval.relation_list) = new std::vector<RelationSqlNode>();
      (yyval.relation_list)->push_back(*(yyvsp[0].relation));
      delete((yyvsp[0].relation));
    }
#line 3405 "yacc_sql.cpp"
    break;

  case 150: /* rel_list: relation COMMA rel_list  */
#line 1254 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelationSqlNode>;
      }

      (yyval.relation_list)->insert((yyval.relation_list)->begin(), *(yyvsp[-2].relation));
      delete((yyvsp[-2].relation));
    }
#line 3420 "yacc_sql.cpp"
    break;

  case 151: /* join_list: %empty  */
#line 1268 "yacc_sql.y"
    {
      (yyval.join_tuple_list) = nullptr;
    }
#line 3428 "yacc_sql.cpp"
    break;

  case 152: /* join_list: join join_list  */
#line 1271 "yacc_sql.y"
                     {
      if ((yyvsp[0].join_tuple_list) == nullptr) {
        std::vector<std::string> *vs = new std::vector<std::string>;
        std::vector<std::vector<ConditionSqlNode> *> *vvc = new std::vector<std::vector<ConditionSqlNode> *>;
        (yyval.join_tuple_list) = new std::tuple<std::vector<std::string> *, std::vector<std::vector<ConditionSqlNode> *> *>(vs, vvc);
      } else {
        (yyval.join_tuple_list) = (yyvsp[0].join_tuple_list);
      }
      std::vector<std::string> *vs = std::get<0>(*(yyval.join_tuple_list));
      std::vector<std::vector<ConditionSqlNode> *> *vvc = std::get<1>(*(yyval.join_tuple_list));
      vs->emplace_back(std::get<0>(*(yyvsp[-1].join_tuple)));
      vvc->emplace_back(std::get<1>(*(yyvsp[-1].join_tuple)));
      delete (yyvsp[-1].join_tuple);
    }
#line 3447 "yacc_sql.cpp"
    break;

  case 153: /* join: INNER JOIN relation ON condition_list  */
#line 1287 "yacc_sql.y"
                                          {
      (yyval.join_tuple) = new std::tuple<std::string, std::vector<ConditionSqlNode> *>((yyvsp[-2].relation)->name, (yyvsp[0].condition_list));
      delete (yyvsp[-2].relation);
    }
#line 3456 "yacc_sql.cpp"
    break;

  case 154: /* where: %empty  */
#line 1294 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3464 "yacc_sql.cpp"
    break;

  case 155: /* where: WHERE condition_list  */
#line 1297 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3472 "yacc_sql.cpp"
    break;

  case 156: /* condition_list: %empty  */
#line 1303 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3480 "yacc_sql.cpp"
    break;

  case 157: /* condition_list: condition  */
#line 1306 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3490 "yacc_sql.cpp"
    break;

  case 158: /* condition_list: condition AND condition_list  */
#line 1311 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3500 "yacc_sql.cpp"
    break;

  case 159: /* condition_list: condition OR condition_list  */
#line 1316 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      ConditionSqlNode *tmp = new ConditionSqlNode;
      tmp->flag = 1;
      (yyval.condition_list)->emplace_back(*tmp);
      delete (yyvsp[-2].condition);
      delete tmp;
    }
#line 3514 "yacc_sql.cpp"
    break;

  case 160: /* condition: expression comp_op expression  */
#line 1377 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3526 "yacc_sql.cpp"
    break;

  case 161: /* condition: expression comp_op LBRACE select_stmt RBRACE  */
#line 1384 "yacc_sql.y"
                                                   {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-4].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 3540 "yacc_sql.cpp"
    break;

  case 162: /* condition: expression IN_T LBRACE select_stmt RBRACE  */
#line 1393 "yacc_sql.y"
                                                {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-4].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::IN;
    }
#line 3554 "yacc_sql.cpp"
    break;

  case 163: /* condition: expression NOT IN_T LBRACE select_stmt RBRACE  */
#line 1402 "yacc_sql.y"
                                                    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-5].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::NOT_IN;
    }
#line 3568 "yacc_sql.cpp"
    break;

  case 164: /* condition: expression IN_T LBRACE value value_list RBRACE  */
#line 1412 "yacc_sql.y"
                                                    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-5].expression);
      std::vector<Value> *values;
      if ((yyvsp[-1].value_list) != nullptr) {
        values = (yyvsp[-1].value_list);
      } else {
        values = new std::vector<Value>();
      }
      values->emplace_back(*(yyvsp[-2].value));
      ValueListExpr *right_expr = new ValueListExpr(values);
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::IN;
    }
#line 3589 "yacc_sql.cpp"
    break;

  case 165: /* condition: expression NOT IN_T LBRACE value value_list RBRACE  */
#line 1428 "yacc_sql.y"
                                                        {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-6].expression);
      std::vector<Value> *values;
      if ((yyvsp[-1].value_list) != nullptr) {
        values = (yyvsp[-1].value_list);
      } else {
        values = new std::vector<Value>();
      }
      values->emplace_back(*(yyvsp[-2].value));
      ValueListExpr *right_expr = new ValueListExpr(values);
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::NOT_IN;
    }
#line 3610 "yacc_sql.cpp"
    break;

  case 166: /* condition: EXISTS_T LBRACE select_stmt RBRACE  */
#line 1444 "yacc_sql.y"
                                         {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      DumbExpr *left_expr = new DumbExpr();
      (yyval.condition)->left_expr = left_expr;
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::EXISTS;
    }
#line 3625 "yacc_sql.cpp"
    break;

  case 167: /* condition: NOT EXISTS_T LBRACE select_stmt RBRACE  */
#line 1454 "yacc_sql.y"
                                             {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      DumbExpr *left_expr = new DumbExpr();
      (yyval.condition)->left_expr = left_expr;
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::NOT_EXISTS;
    }
#line 3640 "yacc_sql.cpp"
    break;

  case 168: /* condition: LBRACE select_stmt RBRACE comp_op expression  */
#line 1464 "yacc_sql.y"
                                                   {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      UnboundSubqueryExpr *left_expr = new UnboundSubqueryExpr((yyvsp[-3].sql_node));
      (yyval.condition)->left_expr = left_expr;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3654 "yacc_sql.cpp"
    break;

  case 169: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 1473 "yacc_sql.y"
                                                                  {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = new UnboundSubqueryExpr((yyvsp[-5].sql_node));
      (yyval.condition)->right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 3667 "yacc_sql.cpp"
    break;

  case 170: /* comp_op: EQ  */
#line 1484 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3673 "yacc_sql.cpp"
    break;

  case 171: /* comp_op: LT  */
#line 1485 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3679 "yacc_sql.cpp"
    break;

  case 172: /* comp_op: GT  */
#line 1486 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3685 "yacc_sql.cpp"
    break;

  case 173: /* comp_op: LE  */
#line 1487 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3691 "yacc_sql.cpp"
    break;

  case 174: /* comp_op: GE  */
#line 1488 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3697 "yacc_sql.cpp"
    break;

  case 175: /* comp_op: NE  */
#line 1489 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3703 "yacc_sql.cpp"
    break;

  case 176: /* comp_op: LK  */
#line 1490 "yacc_sql.y"
         { (yyval.comp) = LIKE; }
#line 3709 "yacc_sql.cpp"
    break;

  case 177: /* comp_op: NLK  */
#line 1491 "yacc_sql.y"
          {(yyval.comp) = NOT_LIKE; }
#line 3715 "yacc_sql.cpp"
    break;

  case 178: /* comp_op: IS_T  */
#line 1492 "yacc_sql.y"
           { (yyval.comp) = IS; }
#line 3721 "yacc_sql.cpp"
    break;

  case 179: /* comp_op: IS_NOT_T  */
#line 1493 "yacc_sql.y"
               { (yyval.comp) = IS_NOT; }
#line 3727 "yacc_sql.cpp"
    break;

  case 180: /* group_by: %empty  */
#line 1499 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3735 "yacc_sql.cpp"
    break;

  case 181: /* group_by: GROUP BY expression_list  */
#line 1504 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3743 "yacc_sql.cpp"
    break;

  case 182: /* having: %empty  */
#line 1511 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3751 "yacc_sql.cpp"
    break;

  case 183: /* having: HAVING condition_list  */
#line 1514 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3759 "yacc_sql.cpp"
    break;

  case 184: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE id_maybe_keyword  */
#line 1520 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3773 "yacc_sql.cpp"
    break;

  case 185: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1533 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3782 "yacc_sql.cpp"
    break;

  case 186: /* set_variable_stmt: SET id_maybe_keyword EQ value  */
#line 1541 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3794 "yacc_sql.cpp"
    break;


#line 3798 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, flag, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner, flag);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner, flag);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, flag, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner, flag);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner, flag);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1553 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner, SCF_ERROR);
  yylex_destroy(scanner);
  return result;
}
