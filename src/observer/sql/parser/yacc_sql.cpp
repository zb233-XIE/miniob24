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
  YYSYMBOL_insert_stmt = 125,              /* insert_stmt  */
  YYSYMBOL_value_list = 126,               /* value_list  */
  YYSYMBOL_value = 127,                    /* value  */
  YYSYMBOL_vector_elem = 128,              /* vector_elem  */
  YYSYMBOL_vector_value_list = 129,        /* vector_value_list  */
  YYSYMBOL_storage_format = 130,           /* storage_format  */
  YYSYMBOL_delete_stmt = 131,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 132,              /* update_stmt  */
  YYSYMBOL_set_clause_list = 133,          /* set_clause_list  */
  YYSYMBOL_set_clause = 134,               /* set_clause  */
  YYSYMBOL_select_stmt = 135,              /* select_stmt  */
  YYSYMBOL_order_by = 136,                 /* order_by  */
  YYSYMBOL_order_by_list = 137,            /* order_by_list  */
  YYSYMBOL_order_by_item = 138,            /* order_by_item  */
  YYSYMBOL_limit = 139,                    /* limit  */
  YYSYMBOL_asc_desc = 140,                 /* asc_desc  */
  YYSYMBOL_calc_stmt = 141,                /* calc_stmt  */
  YYSYMBOL_expression_list = 142,          /* expression_list  */
  YYSYMBOL_expression = 143,               /* expression  */
  YYSYMBOL_agg_fun_attr_list = 144,        /* agg_fun_attr_list  */
  YYSYMBOL_agg_fun_attr = 145,             /* agg_fun_attr  */
  YYSYMBOL_rel_attr = 146,                 /* rel_attr  */
  YYSYMBOL_relation = 147,                 /* relation  */
  YYSYMBOL_rel_list = 148,                 /* rel_list  */
  YYSYMBOL_join_list = 149,                /* join_list  */
  YYSYMBOL_join = 150,                     /* join  */
  YYSYMBOL_where = 151,                    /* where  */
  YYSYMBOL_condition_list = 152,           /* condition_list  */
  YYSYMBOL_condition = 153,                /* condition  */
  YYSYMBOL_comp_op = 154,                  /* comp_op  */
  YYSYMBOL_group_by = 155,                 /* group_by  */
  YYSYMBOL_having = 156,                   /* having  */
  YYSYMBOL_load_data_stmt = 157,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 158,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 159,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 160             /* opt_semicolon  */
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
#define YYLAST   635

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  186
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  389

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
       0,   286,   286,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   319,   322,   325,   328,   331,
     334,   337,   343,   346,   351,   360,   366,   372,   377,   383,
     389,   395,   401,   408,   414,   422,   441,   462,   537,   541,
     552,   556,   560,   564,   568,   572,   579,   590,   593,   596,
     601,   630,   645,   659,   662,   675,   684,   704,   705,   706,
     710,   713,   714,   715,   716,   717,   718,   721,   738,   741,
     752,   756,   760,   766,   778,   788,   794,   798,   805,   808,
     817,   820,   827,   839,   856,   861,   874,   883,   892,   947,
     950,   957,   963,   976,   984,   988,   992,  1000,  1003,  1010,
    1013,  1017,  1024,  1033,  1038,  1045,  1052,  1061,  1073,  1087,
    1090,  1093,  1096,  1099,  1103,  1106,  1109,  1112,  1115,  1120,
    1126,  1129,  1134,  1137,  1140,  1143,  1146,  1165,  1168,  1182,
    1187,  1190,  1198,  1203,  1213,  1219,  1226,  1235,  1240,  1254,
    1257,  1273,  1280,  1283,  1289,  1292,  1297,  1302,  1362,  1370,
    1379,  1388,  1398,  1414,  1430,  1440,  1450,  1459,  1470,  1471,
    1472,  1473,  1474,  1475,  1476,  1477,  1478,  1479,  1485,  1489,
    1497,  1500,  1505,  1518,  1526,  1536,  1537
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
  "attr_def", "nullable_spec", "number", "type", "insert_stmt",
  "value_list", "value", "vector_elem", "vector_value_list",
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

#define YYPACT_NINF (-275)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     589,    26,    25,   316,   316,   508,     3,  -275,   -15,    13,
     508,  -275,  -275,  -275,  -275,  -275,   508,   -18,   589,    40,
      62,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,   508,   508,    82,    98,   508,   508,   508,
     316,  -275,    53,    95,    96,   102,   103,   -59,   105,   109,
     115,  -275,  -275,  -275,  -275,  -275,  -275,   316,  -275,   107,
    -275,  -275,   426,  -275,    89,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,   508,   508,    99,    94,   113,  -275,  -275,  -275,
    -275,    -6,   110,    57,   508,   290,  -275,   117,     7,   340,
     340,   340,   340,   340,  -275,  -275,   139,   316,   316,   316,
    -275,   464,   316,   508,   316,   316,   316,   316,   140,   508,
     132,   134,   508,   384,    78,   508,   161,  -275,  -275,   508,
     133,   135,   290,   157,    97,   508,  -275,  -275,   147,   168,
     160,  -275,   186,   191,   192,   194,   -59,   153,   106,   131,
     145,  -275,  -275,  -275,   206,   -43,   -43,  -275,  -275,   316,
     353,   207,   167,   212,   279,  -275,   185,   134,   214,  -275,
     209,   514,   220,  -275,   228,   508,   508,   231,   290,   161,
    -275,   508,  -275,   340,  -275,  -275,  -275,  -275,   139,  -275,
     316,   316,   316,   316,  -275,   508,  -275,   508,   198,   134,
     167,   384,   230,   229,   178,   481,  -275,    18,   413,  -275,
     508,   245,  -275,  -275,  -275,  -275,  -275,  -275,    29,   508,
     244,   508,   247,   248,  -275,  -275,  -275,  -275,  -275,    38,
      43,    55,  -275,  -275,  -275,   508,   266,  -275,   253,   260,
     161,   267,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,   208,   274,   365,   279,   279,   161,  -275,  -275,
     508,   210,  -275,  -275,  -275,   220,   239,   283,   205,   508,
    -275,  -275,  -275,   258,   304,   301,   384,   292,   532,   294,
     161,   291,    -7,   230,   -48,  -275,  -275,   295,  -275,  -275,
     296,  -275,   282,    -3,  -275,   310,   311,   279,   316,   279,
     249,   253,  -275,   402,  -275,   314,    -7,   253,   322,   323,
    -275,     5,   288,  -275,   278,  -275,  -275,  -275,  -275,   503,
     261,  -275,   230,   -48,  -275,   253,   338,   341,  -275,  -275,
    -275,   508,   343,   344,   345,   346,  -275,   350,   -11,   293,
    -275,   361,   366,  -275,  -275,  -275,   188,   316,   316,   316,
     503,  -275,  -275,  -275,  -275,  -275,  -275,   337,   339,   347,
     368,   369,   367,   176,   184,   189,  -275,   142,   320,   307,
     330,  -275,   188,   316,   316,   316,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,    70,    92,   100,  -275,  -275,  -275
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,    39,    40,    41,    37,    36,     0,     0,     0,     0,
     185,    24,    23,    16,    17,    18,    19,    10,    11,    12,
      13,    14,    15,     8,     9,     5,     7,     6,     4,     3,
      20,    21,    22,     0,     0,     0,     0,     0,     0,     0,
       0,    26,    28,    27,    31,    29,    30,     0,     0,     0,
       0,    85,    80,    81,    25,    82,    83,     0,   130,   142,
     128,   112,   113,   129,     0,    28,    27,    31,    29,    30,
      44,    43,     0,     0,     0,     0,     0,   183,     1,   186,
       2,    57,     0,     0,     0,    32,    42,     0,     0,   139,
     139,   139,   139,   139,    86,    87,    88,     0,     0,     0,
     127,     0,     0,     0,     0,     0,     0,     0,   114,     0,
       0,   152,     0,     0,     0,     0,     0,    61,    59,     0,
       0,     0,    32,    33,     0,     0,   123,   140,   142,     0,
     137,   141,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   131,   143,   116,   115,   119,   120,   121,   122,     0,
     144,   147,   149,     0,   154,    92,     0,   152,    94,   184,
       0,     0,    63,    58,     0,     0,     0,     0,    32,     0,
      56,     0,   132,   139,   133,   134,   135,   136,    88,    84,
       0,     0,     0,     0,   117,     0,   145,     0,     0,   152,
     149,     0,     0,     0,     0,     0,   153,   155,     0,    93,
       0,     0,    71,    72,    73,    74,    75,    76,    69,     0,
       0,     0,     0,     0,    35,    34,    62,   138,    89,     0,
       0,     0,   118,   146,   148,     0,   178,   150,    78,     0,
       0,     0,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,     0,     0,     0,   154,   154,     0,    96,    95,
       0,     0,    67,    68,    66,    63,    90,     0,     0,     0,
     124,   125,   126,     0,     0,   180,     0,     0,     0,     0,
       0,     0,     0,     0,   158,   156,   157,     0,   182,    70,
       0,    64,     0,    57,    45,     0,     0,   154,     0,   154,
      99,    78,    77,     0,   164,     0,     0,    78,     0,     0,
      97,    69,     0,    60,     0,    46,   151,   179,   181,     0,
     107,    79,     0,   166,   165,    78,     0,     0,   160,   159,
      65,     0,     0,     0,     0,     0,   100,   101,   109,     0,
      98,     0,     0,   161,   162,    91,     0,     0,     0,     0,
       0,   111,   110,   103,   108,   167,   163,     0,     0,     0,
       0,     0,    48,     0,     0,     0,   102,     0,     0,     0,
       0,    47,     0,     0,     0,     0,    50,    51,    52,    53,
      54,    55,    49,     0,     0,     0,   104,   105,   106
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -275,  -275,   401,    -5,  -124,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,    48,  -275,  -275,   128,
    -275,  -275,   158,   215,   118,  -275,  -275,  -275,  -274,  -122,
     285,   250,  -275,  -275,  -275,   226,  -275,   -60,  -275,    87,
    -275,  -275,  -275,  -275,    -2,   -46,   -78,  -275,   -84,  -163,
    -165,   252,  -275,  -158,   -52,  -275,   166,  -275,  -275,  -275,
    -275,  -275,  -275
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    69,   134,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,   361,   362,    32,   127,
      33,    34,   220,   172,   264,   290,   218,    35,   277,    70,
     106,   147,   293,    36,    37,   167,   168,    38,   320,   336,
     337,   340,   353,    39,    71,    72,   139,   140,    73,   161,
     162,   199,   200,   165,   206,   207,   254,   275,   300,    40,
      41,    42,    90
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      80,   169,    74,   351,    98,    84,     4,     4,   177,   209,
       4,    85,   222,    81,   125,   141,   141,   141,   141,   141,
      82,   110,   142,   143,   144,   145,    86,   321,   136,   104,
     105,   128,   234,   327,    48,    43,    49,    44,    91,    92,
      88,   236,    95,    96,    97,   114,   115,   116,   117,   261,
      83,   342,   116,   117,   225,    45,   267,   255,   256,   270,
      57,   148,   149,   150,   271,    89,   173,   118,   155,   156,
     157,   158,   273,    99,   352,    61,   272,   120,   121,   238,
     126,    62,    63,   126,    65,    66,   258,   262,   263,   131,
     133,   386,    46,    93,   138,   138,   138,   138,   138,   141,
     114,   115,   116,   117,   296,   227,   152,    47,   154,    94,
     153,   262,   263,   387,   160,   100,   101,   166,   205,   226,
     171,   388,   102,   103,   174,   107,   119,   133,   190,   108,
     180,   114,   115,   116,   117,   109,   114,   115,   116,   117,
     122,   111,   239,   123,   229,   230,   231,   130,   114,   115,
     116,   117,   129,   191,   301,   196,    98,   194,   124,   135,
     307,   146,   159,   114,   115,   116,   117,   192,   163,   170,
     160,   223,   164,   133,     4,   175,   152,   176,   138,   178,
     279,   181,   183,   179,   325,   114,   115,   116,   117,   182,
     233,   232,   160,   114,   115,   116,   117,   287,   373,   114,
     115,   116,   117,   285,   286,   166,   374,   184,   284,   205,
     205,   375,   185,   186,   171,   187,   160,   376,   377,   378,
     305,   189,   308,   309,   114,   115,   116,   117,   193,   197,
     160,   198,   201,   128,   208,   338,   210,    98,   114,   115,
     116,   117,   219,     4,   211,   316,   326,   318,   221,   240,
      50,   205,   224,   205,   260,   288,   241,   323,   357,   358,
     359,   360,   341,   235,   160,   266,   338,   268,   269,   114,
     115,   116,   117,   274,    51,   276,    98,   114,   115,   116,
     117,   278,   114,   115,   116,   117,   292,   280,   281,    52,
      53,    54,    55,    56,   282,   295,   317,    57,   289,   202,
     297,   363,   364,   365,   294,    58,    59,    60,   298,   299,
     132,   306,    61,   302,   138,   304,   310,   311,    62,    63,
      64,    65,    66,    51,    67,    68,   345,   383,   384,   385,
     312,   314,   315,   319,    51,   324,    50,   331,    52,    53,
      54,    55,    56,   328,   329,   138,    57,   332,   339,    75,
      76,    77,    78,    79,    58,    59,    60,   203,   204,   343,
      51,    61,   344,   346,   347,   348,   349,    62,    63,    64,
      65,    66,   350,    67,    68,    52,    53,    54,    55,    56,
      64,   354,   355,    57,    51,   283,   367,   356,   368,   372,
     371,    58,    59,    60,   379,   380,   369,    51,    61,    75,
      76,    77,    78,    79,    62,    63,    64,    65,    66,    51,
      67,    68,    75,    76,    77,    78,    79,   370,   381,    87,
     382,   313,   322,   291,    52,    53,    54,    55,    56,   330,
      64,   188,    57,   257,   265,   137,   259,   366,   228,   195,
      58,    59,    60,    64,   303,     0,    51,    61,   112,     0,
       0,    57,   237,    62,    63,    64,    65,    66,     0,    67,
      68,    52,    53,    54,    55,    56,    61,     0,     0,    57,
      51,     0,    62,    63,     0,    65,    66,    58,    59,    60,
      57,     0,     0,     0,    61,    75,    76,    77,    78,    79,
      62,    63,    64,    65,    66,    61,    67,    68,     0,     0,
       0,    62,    63,     0,    65,    66,     0,     0,    51,     0,
       0,     0,   113,     0,     0,     0,    64,     0,     0,   114,
     115,   116,   117,    75,    76,    77,    78,    79,     0,     0,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     212,   213,   214,   215,   216,   217,     0,    51,     0,     0,
       0,     0,    51,     0,    64,     0,     0,     0,     0,   151,
     252,   253,    75,    76,    77,    78,    79,    75,    76,    77,
      78,    79,     0,     0,   114,   115,   116,   117,   333,   334,
     335,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,     0,     0,    64,     1,     2,     0,     0,    64,     0,
       0,     3,     4,     5,     6,     7,     8,     9,    10,     0,
       0,     0,    11,    12,    13,     0,     0,     0,     0,     0,
       0,    14,    15,     0,     0,     0,     0,     0,     0,     0,
      16,     0,    17,     0,     0,    18
};

static const yytype_int16 yycheck[] =
{
       5,   123,     4,    14,    50,    10,    13,    13,   132,   167,
      13,    16,   175,    10,    20,    99,   100,   101,   102,   103,
      35,    67,   100,   101,   102,   103,    44,   301,    21,    88,
      89,    91,   197,   307,     9,     9,    11,    11,    43,    44,
       0,   199,    47,    48,    49,    93,    94,    95,    96,    20,
      37,   325,    95,    96,   178,    29,   221,    39,    40,    21,
      67,   107,   108,   109,    21,     3,   126,    72,   114,   115,
     116,   117,   235,    20,    85,    82,    21,    82,    83,   201,
      86,    88,    89,    86,    91,    92,   208,    82,    83,    94,
      95,    21,    66,    11,    99,   100,   101,   102,   103,   183,
      93,    94,    95,    96,   269,   183,   111,    81,   113,    11,
     112,    82,    83,    21,   119,    20,    20,   122,   164,   179,
     125,    21,    20,    20,   129,    20,    37,   132,    22,    20,
     135,    93,    94,    95,    96,    20,    93,    94,    95,    96,
      41,    34,   202,    49,   190,   191,   192,    90,    93,    94,
      95,    96,    42,    22,   276,   160,   202,   159,    45,    42,
     282,    22,    22,    93,    94,    95,    96,    22,    36,    91,
     175,   176,    38,   178,    13,    42,   181,    42,   183,    22,
     240,    34,    22,    86,   306,    93,    94,    95,    96,    21,
     195,   193,   197,    93,    94,    95,    96,   257,    22,    93,
      94,    95,    96,   255,   256,   210,    22,    21,   254,   255,
     256,    22,    21,    21,   219,    21,   221,    75,    76,    77,
     280,    68,   282,   283,    93,    94,    95,    96,    22,    22,
     235,    64,    20,   293,    49,   319,    22,   283,    93,    94,
      95,    96,    22,    13,    35,   297,   306,   299,    20,    20,
      20,   297,    21,   299,     9,   260,    78,   303,    70,    71,
      72,    73,   322,    65,   269,    21,   350,    20,    20,    93,
      94,    95,    96,     7,    44,    22,   322,    93,    94,    95,
      96,    21,    93,    94,    95,    96,    47,    20,    80,    59,
      60,    61,    62,    63,    20,    90,   298,    67,    88,    20,
      42,   347,   348,   349,    21,    75,    76,    77,     4,     8,
      20,    20,    82,    21,   319,    21,    21,    21,    88,    89,
      90,    91,    92,    44,    94,    95,   331,   373,   374,   375,
      48,    21,    21,    84,    44,    21,    20,    49,    59,    60,
      61,    62,    63,    21,    21,   350,    67,    69,    87,    59,
      60,    61,    62,    63,    75,    76,    77,    78,    79,    21,
      44,    82,    21,    20,    20,    20,    20,    88,    89,    90,
      91,    92,    22,    94,    95,    59,    60,    61,    62,    63,
      90,    88,    21,    67,    44,    20,    49,    21,    49,    22,
      21,    75,    76,    77,    74,    88,    49,    44,    82,    59,
      60,    61,    62,    63,    88,    89,    90,    91,    92,    44,
      94,    95,    59,    60,    61,    62,    63,    49,    88,    18,
     372,   293,    20,   265,    59,    60,    61,    62,    63,   311,
      90,   146,    67,    20,   219,    95,   210,   350,   188,    86,
      75,    76,    77,    90,   278,    -1,    44,    82,    22,    -1,
      -1,    67,   200,    88,    89,    90,    91,    92,    -1,    94,
      95,    59,    60,    61,    62,    63,    82,    -1,    -1,    67,
      44,    -1,    88,    89,    -1,    91,    92,    75,    76,    77,
      67,    -1,    -1,    -1,    82,    59,    60,    61,    62,    63,
      88,    89,    90,    91,    92,    82,    94,    95,    -1,    -1,
      -1,    88,    89,    -1,    91,    92,    -1,    -1,    44,    -1,
      -1,    -1,    86,    -1,    -1,    -1,    90,    -1,    -1,    93,
      94,    95,    96,    59,    60,    61,    62,    63,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      26,    27,    28,    29,    30,    31,    -1,    44,    -1,    -1,
      -1,    -1,    44,    -1,    90,    -1,    -1,    -1,    -1,    95,
      79,    80,    59,    60,    61,    62,    63,    59,    60,    61,
      62,    63,    -1,    -1,    93,    94,    95,    96,    75,    76,
      77,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    -1,    -1,    90,     5,     6,    -1,    -1,    90,    -1,
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    -1,    43,    -1,    -1,    46
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    12,    13,    14,    15,    16,    17,    18,
      19,    23,    24,    25,    32,    33,    41,    43,    46,    99,
     100,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   116,   118,   119,   125,   131,   132,   135,   141,
     157,   158,   159,     9,    11,    29,    66,    81,     9,    11,
      20,    44,    59,    60,    61,    62,    63,    67,    75,    76,
      77,    82,    88,    89,    90,    91,    92,    94,    95,   101,
     127,   142,   143,   146,   142,    59,    60,    61,    62,    63,
     101,    10,    35,    37,   101,   101,    44,   100,     0,     3,
     160,   101,   101,    11,    11,   101,   101,   101,   143,    20,
      20,    20,    20,    20,    88,    89,   128,    20,    20,    20,
     143,    34,    22,    86,    93,    94,    95,    96,   101,    37,
     101,   101,    41,    49,    45,    20,    86,   117,   135,    42,
      90,   101,    20,   101,   102,    42,    21,    95,   101,   144,
     145,   146,   144,   144,   144,   144,    22,   129,   143,   143,
     143,    95,   101,   142,   101,   143,   143,   143,   143,    22,
     101,   147,   148,    36,    38,   151,   101,   133,   134,   127,
      91,   101,   121,   135,   101,    42,    42,   102,    22,    86,
     101,    34,    21,    22,    21,    21,    21,    21,   128,    68,
      22,    22,    22,    22,   142,    86,   101,    22,    64,   149,
     150,    20,    20,    78,    79,   143,   152,   153,    49,   151,
      22,    35,    26,    27,    28,    29,    30,    31,   124,    22,
     120,    20,   147,   101,    21,   102,   135,   144,   129,   143,
     143,   143,   142,   101,   148,    65,   151,   149,   127,   135,
      20,    78,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    79,    80,   154,    39,    40,    20,   127,   133,
       9,    20,    82,    83,   122,   121,    21,   148,    20,    20,
      21,    21,    21,   147,     7,   155,    22,   126,    21,   135,
      20,    80,    20,    20,   143,   152,   152,   135,   101,    88,
     123,   120,    47,   130,    21,    90,   148,    42,     4,     8,
     156,   127,    21,   154,    21,   135,    20,   127,   135,   135,
      21,    21,    48,   117,    21,    21,   152,   142,   152,    84,
     136,   126,    20,   143,    21,   127,   135,   126,    21,    21,
     122,    49,    69,    75,    76,    77,   137,   138,   146,    87,
     139,   135,   126,    21,    21,   101,    20,    20,    20,    20,
      22,    14,    85,   140,    88,    21,    21,    70,    71,    72,
      73,   114,   115,   143,   143,   143,   137,    49,    49,    49,
      49,    21,    22,    22,    22,    22,    75,    76,    77,    74,
      88,    88,   114,   143,   143,   143,    21,    21,    21
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
     123,   124,   124,   124,   124,   124,   124,   125,   126,   126,
     127,   127,   127,   127,   127,   127,   128,   128,   129,   129,
     130,   130,   131,   132,   133,   133,   134,   134,   135,   136,
     136,   137,   137,   138,   138,   138,   138,   139,   139,   140,
     140,   140,   141,   142,   142,   142,   142,   142,   142,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   144,   144,   145,
     145,   145,   146,   146,   147,   147,   147,   148,   148,   149,
     149,   150,   151,   151,   152,   152,   152,   152,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   155,   155,
     156,   156,   157,   158,   159,   160,   160
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
       1,     1,     1,     1,     1,     1,     1,     8,     0,     3,
       1,     1,     1,     1,     4,     1,     1,     1,     0,     3,
       0,     4,     4,     5,     1,     3,     3,     5,    10,     0,
       2,     1,     3,     2,     6,     6,     6,     0,     2,     0,
       1,     1,     2,     1,     2,     3,     3,     4,     5,     3,
       3,     3,     3,     3,     6,     6,     6,     2,     1,     1,
       1,     3,     4,     4,     4,     4,     4,     1,     3,     0,
       1,     1,     1,     3,     1,     2,     3,     1,     3,     0,
       2,     5,     0,     2,     0,     1,     3,     3,     3,     5,
       5,     6,     6,     7,     4,     5,     5,     7,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     3,
       0,     2,     7,     2,     4,     0,     1
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
#line 287 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 2024 "yacc_sql.cpp"
    break;

  case 25: /* id_maybe_keyword: ID  */
#line 319 "yacc_sql.y"
     {
    (yyval.string) = (yyvsp[0].string);
  }
#line 2032 "yacc_sql.cpp"
    break;

  case 26: /* id_maybe_keyword: DATA  */
#line 322 "yacc_sql.y"
         {
    (yyval.string) = strdup("data");
  }
#line 2040 "yacc_sql.cpp"
    break;

  case 27: /* id_maybe_keyword: MIN  */
#line 325 "yacc_sql.y"
        {
    (yyval.string) = strdup("min");
  }
#line 2048 "yacc_sql.cpp"
    break;

  case 28: /* id_maybe_keyword: MAX  */
#line 328 "yacc_sql.y"
        {
    (yyval.string) = strdup("max");
  }
#line 2056 "yacc_sql.cpp"
    break;

  case 29: /* id_maybe_keyword: AVG  */
#line 331 "yacc_sql.y"
        {
    (yyval.string) = strdup("avg");
  }
#line 2064 "yacc_sql.cpp"
    break;

  case 30: /* id_maybe_keyword: SUM  */
#line 334 "yacc_sql.y"
        {
    (yyval.string) = strdup("sum");
  }
#line 2072 "yacc_sql.cpp"
    break;

  case 31: /* id_maybe_keyword: COUNT  */
#line 337 "yacc_sql.y"
          {
    (yyval.string) = strdup("count");
  }
#line 2080 "yacc_sql.cpp"
    break;

  case 32: /* id_list: %empty  */
#line 343 "yacc_sql.y"
  {
    (yyval.id_list) = nullptr;
  }
#line 2088 "yacc_sql.cpp"
    break;

  case 33: /* id_list: id_maybe_keyword  */
#line 346 "yacc_sql.y"
                     {
    (yyval.id_list) = new std::vector<std::string>;
    (yyval.id_list)->emplace_back((yyvsp[0].string));
    free((yyvsp[0].string));
  }
#line 2098 "yacc_sql.cpp"
    break;

  case 34: /* id_list: id_maybe_keyword COMMA id_list  */
#line 351 "yacc_sql.y"
                                   {
    if ((yyvsp[0].id_list) != nullptr) {
      (yyval.id_list) = (yyvsp[0].id_list);
    } else {
      (yyval.id_list) = new std::vector<std::string>;
    }
    (yyval.id_list)->emplace((yyval.id_list)->begin(), (yyvsp[-2].string));
    free((yyvsp[-2].string));
  }
#line 2112 "yacc_sql.cpp"
    break;

  case 35: /* id_list: LBRACE id_list RBRACE  */
#line 360 "yacc_sql.y"
                          {
    (yyval.id_list) = (yyvsp[-1].id_list);
  }
#line 2120 "yacc_sql.cpp"
    break;

  case 36: /* exit_stmt: EXIT  */
#line 366 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 2129 "yacc_sql.cpp"
    break;

  case 37: /* help_stmt: HELP  */
#line 372 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2137 "yacc_sql.cpp"
    break;

  case 38: /* sync_stmt: SYNC  */
#line 377 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2145 "yacc_sql.cpp"
    break;

  case 39: /* begin_stmt: TRX_BEGIN  */
#line 383 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2153 "yacc_sql.cpp"
    break;

  case 40: /* commit_stmt: TRX_COMMIT  */
#line 389 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2161 "yacc_sql.cpp"
    break;

  case 41: /* rollback_stmt: TRX_ROLLBACK  */
#line 395 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2169 "yacc_sql.cpp"
    break;

  case 42: /* drop_table_stmt: DROP TABLE id_maybe_keyword  */
#line 401 "yacc_sql.y"
                                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2179 "yacc_sql.cpp"
    break;

  case 43: /* show_tables_stmt: SHOW TABLES  */
#line 408 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2187 "yacc_sql.cpp"
    break;

  case 44: /* desc_table_stmt: DESC id_maybe_keyword  */
#line 414 "yacc_sql.y"
                           {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2197 "yacc_sql.cpp"
    break;

  case 45: /* create_index_stmt: CREATE INDEX id_maybe_keyword ON id_maybe_keyword LBRACE rel_list RBRACE  */
#line 423 "yacc_sql.y"
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
#line 2220 "yacc_sql.cpp"
    break;

  case 46: /* create_index_stmt: CREATE UNIQUE INDEX id_maybe_keyword ON id_maybe_keyword LBRACE rel_list RBRACE  */
#line 442 "yacc_sql.y"
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
#line 2242 "yacc_sql.cpp"
    break;

  case 47: /* create_vector_index_stmt: CREATE VECTOR_T INDEX ID ON relation LBRACE ID RBRACE WITH LBRACE vector_index_param_list RBRACE  */
#line 463 "yacc_sql.y"
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
#line 2318 "yacc_sql.cpp"
    break;

  case 48: /* vector_index_param_list: vector_index_field  */
#line 537 "yacc_sql.y"
                       {
      (yyval.vec_index_param_list) = new std::vector<VecIndexFieldAnno>();
      (yyval.vec_index_param_list)->push_back((yyvsp[0].vec_index_param));
    }
#line 2327 "yacc_sql.cpp"
    break;

  case 49: /* vector_index_param_list: vector_index_field COMMA vector_index_param_list  */
#line 541 "yacc_sql.y"
                                                       {
      if((yyvsp[0].vec_index_param_list) != nullptr){
        (yyval.vec_index_param_list) = (yyvsp[0].vec_index_param_list);
      } else {
        (yyval.vec_index_param_list) = new std::vector<VecIndexFieldAnno>();
      }
      (yyval.vec_index_param_list)->push_back((yyvsp[-2].vec_index_param));
    }
#line 2340 "yacc_sql.cpp"
    break;

  case 50: /* vector_index_field: DISTANCE EQ L2_DISTANCE  */
#line 553 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::DISTANCE_FIELD, static_cast<int>(DISTANCE_ALGO::L2_DISTANCE)};
    }
#line 2348 "yacc_sql.cpp"
    break;

  case 51: /* vector_index_field: DISTANCE EQ COSINE_DISTANCE  */
#line 557 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::DISTANCE_FIELD, static_cast<int>(DISTANCE_ALGO::COSINE_DISTANCE)};
    }
#line 2356 "yacc_sql.cpp"
    break;

  case 52: /* vector_index_field: DISTANCE EQ INNER_PRODUCT  */
#line 561 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::DISTANCE_FIELD, static_cast<int>(DISTANCE_ALGO::INNER_PRODUCT)};
    }
#line 2364 "yacc_sql.cpp"
    break;

  case 53: /* vector_index_field: TYPE EQ IVFFLAT  */
#line 565 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::TYPE_FIELD, 1};
    }
#line 2372 "yacc_sql.cpp"
    break;

  case 54: /* vector_index_field: LISTS EQ NUMBER  */
#line 569 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::LISTS_FIELD, (yyvsp[0].number)};
    }
#line 2380 "yacc_sql.cpp"
    break;

  case 55: /* vector_index_field: PROBES EQ NUMBER  */
#line 573 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::PROBES_FIELD, (yyvsp[0].number)};
    }
#line 2388 "yacc_sql.cpp"
    break;

  case 56: /* drop_index_stmt: DROP INDEX id_maybe_keyword ON id_maybe_keyword  */
#line 580 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2400 "yacc_sql.cpp"
    break;

  case 57: /* as_select: %empty  */
#line 590 "yacc_sql.y"
  {
    (yyval.sql_node) = nullptr;
  }
#line 2408 "yacc_sql.cpp"
    break;

  case 58: /* as_select: AS select_stmt  */
#line 593 "yacc_sql.y"
                   {
    (yyval.sql_node) = (yyvsp[0].sql_node);
  }
#line 2416 "yacc_sql.cpp"
    break;

  case 59: /* as_select: select_stmt  */
#line 596 "yacc_sql.y"
                {
    (yyval.sql_node) = (yyvsp[0].sql_node);
  }
#line 2424 "yacc_sql.cpp"
    break;

  case 60: /* create_table_stmt: CREATE TABLE id_maybe_keyword LBRACE attr_def attr_def_list RBRACE storage_format as_select  */
#line 602 "yacc_sql.y"
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
#line 2457 "yacc_sql.cpp"
    break;

  case 61: /* create_table_stmt: CREATE TABLE id_maybe_keyword as_select  */
#line 630 "yacc_sql.y"
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
#line 2475 "yacc_sql.cpp"
    break;

  case 62: /* create_view_stmt: CREATE VIEW id_maybe_keyword id_list AS select_stmt  */
#line 645 "yacc_sql.y"
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
#line 2491 "yacc_sql.cpp"
    break;

  case 63: /* attr_def_list: %empty  */
#line 659 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2499 "yacc_sql.cpp"
    break;

  case 64: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 663 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2513 "yacc_sql.cpp"
    break;

  case 65: /* attr_def: id_maybe_keyword type LBRACE number RBRACE nullable_spec  */
#line 676 "yacc_sql.y"
  {
    (yyval.attr_info) = new AttrInfoSqlNode;
    (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
    (yyval.attr_info)->name = (yyvsp[-5].string);
    (yyval.attr_info)->length = (yyvsp[-2].number);
    (yyval.attr_info)->nullable = (yyvsp[0].nullable_spec);
    free((yyvsp[-5].string));
  }
#line 2526 "yacc_sql.cpp"
    break;

  case 66: /* attr_def: id_maybe_keyword type nullable_spec  */
#line 685 "yacc_sql.y"
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
#line 2547 "yacc_sql.cpp"
    break;

  case 67: /* nullable_spec: NULL_T  */
#line 704 "yacc_sql.y"
         { (yyval.nullable_spec) = true; }
#line 2553 "yacc_sql.cpp"
    break;

  case 68: /* nullable_spec: NOT_NULL_T  */
#line 705 "yacc_sql.y"
               { (yyval.nullable_spec) = false; }
#line 2559 "yacc_sql.cpp"
    break;

  case 69: /* nullable_spec: %empty  */
#line 706 "yacc_sql.y"
                { (yyval.nullable_spec) = true; }
#line 2565 "yacc_sql.cpp"
    break;

  case 70: /* number: NUMBER  */
#line 710 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2571 "yacc_sql.cpp"
    break;

  case 71: /* type: INT_T  */
#line 713 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2577 "yacc_sql.cpp"
    break;

  case 72: /* type: STRING_T  */
#line 714 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2583 "yacc_sql.cpp"
    break;

  case 73: /* type: FLOAT_T  */
#line 715 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2589 "yacc_sql.cpp"
    break;

  case 74: /* type: VECTOR_T  */
#line 716 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2595 "yacc_sql.cpp"
    break;

  case 75: /* type: DATE_T  */
#line 717 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2601 "yacc_sql.cpp"
    break;

  case 76: /* type: TEXT_T  */
#line 718 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2607 "yacc_sql.cpp"
    break;

  case 77: /* insert_stmt: INSERT INTO id_maybe_keyword VALUES LBRACE value value_list RBRACE  */
#line 722 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 2624 "yacc_sql.cpp"
    break;

  case 78: /* value_list: %empty  */
#line 738 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2632 "yacc_sql.cpp"
    break;

  case 79: /* value_list: COMMA value value_list  */
#line 741 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2646 "yacc_sql.cpp"
    break;

  case 80: /* value: NUMBER  */
#line 752 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2655 "yacc_sql.cpp"
    break;

  case 81: /* value: FLOAT  */
#line 756 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2664 "yacc_sql.cpp"
    break;

  case 82: /* value: SSS  */
#line 760 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2675 "yacc_sql.cpp"
    break;

  case 83: /* value: DATE  */
#line 766 "yacc_sql.y"
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
#line 2692 "yacc_sql.cpp"
    break;

  case 84: /* value: LBRACKET vector_elem vector_value_list RBRACKET  */
#line 778 "yacc_sql.y"
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
#line 2707 "yacc_sql.cpp"
    break;

  case 85: /* value: NULL_T  */
#line 788 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2716 "yacc_sql.cpp"
    break;

  case 86: /* vector_elem: NUMBER  */
#line 794 "yacc_sql.y"
           {
      (yyval.floats) = (float)(yyvsp[0].number);
      (yyloc) = (yylsp[0]);
    }
#line 2725 "yacc_sql.cpp"
    break;

  case 87: /* vector_elem: FLOAT  */
#line 798 "yacc_sql.y"
           {
      (yyval.floats) = (float)(yyvsp[0].floats);
      (yyloc) = (yylsp[0]);
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 88: /* vector_value_list: %empty  */
#line 805 "yacc_sql.y"
    {
      (yyval.vector_elem_list) = nullptr;
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 89: /* vector_value_list: COMMA vector_elem vector_value_list  */
#line 808 "yacc_sql.y"
                                         {
      (yyval.vector_elem_list) = (yyvsp[0].vector_elem_list);
      if((yyval.vector_elem_list) == nullptr){
        (yyval.vector_elem_list) = new vector<float>;
      }
      (yyval.vector_elem_list)->push_back((yyvsp[-1].floats));
    }
#line 2754 "yacc_sql.cpp"
    break;

  case 90: /* storage_format: %empty  */
#line 817 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2762 "yacc_sql.cpp"
    break;

  case 91: /* storage_format: STORAGE FORMAT EQ id_maybe_keyword  */
#line 821 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2770 "yacc_sql.cpp"
    break;

  case 92: /* delete_stmt: DELETE FROM id_maybe_keyword where  */
#line 828 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2784 "yacc_sql.cpp"
    break;

  case 93: /* update_stmt: UPDATE id_maybe_keyword SET set_clause_list where  */
#line 840 "yacc_sql.y"
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
#line 2802 "yacc_sql.cpp"
    break;

  case 94: /* set_clause_list: set_clause  */
#line 856 "yacc_sql.y"
             {
    (yyval.set_clause_list) = new std::vector<SetClauseSqlNode>;
    (yyval.set_clause_list)->emplace_back(*(yyvsp[0].set_clause));
    delete (yyvsp[0].set_clause);
  }
#line 2812 "yacc_sql.cpp"
    break;

  case 95: /* set_clause_list: set_clause COMMA set_clause_list  */
#line 862 "yacc_sql.y"
  {
    if ((yyvsp[0].set_clause_list) != nullptr) {
      (yyval.set_clause_list) = (yyvsp[0].set_clause_list);
    } else {
      (yyval.set_clause_list) = new std::vector<SetClauseSqlNode>;
    }
    (yyval.set_clause_list)->emplace((yyval.set_clause_list)->begin(), *(yyvsp[-2].set_clause));
    delete (yyvsp[-2].set_clause);
  }
#line 2826 "yacc_sql.cpp"
    break;

  case 96: /* set_clause: id_maybe_keyword EQ value  */
#line 874 "yacc_sql.y"
                            {
    (yyval.set_clause) = new SetClauseSqlNode;
    (yyval.set_clause)->attribute_name = (yyvsp[-2].string);
    (yyval.set_clause)->value = *(yyvsp[0].value);
    (yyval.set_clause)->has_subquery = false;
    (yyval.set_clause)->subquery = nullptr;
    free((yyvsp[-2].string));
    delete (yyvsp[0].value);
  }
#line 2840 "yacc_sql.cpp"
    break;

  case 97: /* set_clause: id_maybe_keyword EQ LBRACE select_stmt RBRACE  */
#line 883 "yacc_sql.y"
                                                  {
    (yyval.set_clause) = new SetClauseSqlNode;
    (yyval.set_clause)->attribute_name = (yyvsp[-4].string);
    (yyval.set_clause)->has_subquery = true;
    (yyval.set_clause)->subquery = (yyvsp[-1].sql_node);
    free((yyvsp[-4].string));
  }
#line 2852 "yacc_sql.cpp"
    break;

  case 98: /* select_stmt: SELECT expression_list FROM rel_list join_list where group_by having order_by limit  */
#line 893 "yacc_sql.y"
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
#line 2907 "yacc_sql.cpp"
    break;

  case 99: /* order_by: %empty  */
#line 947 "yacc_sql.y"
        {
		(yyval.order_by_list) = nullptr;
	}
#line 2915 "yacc_sql.cpp"
    break;

  case 100: /* order_by: ORDER_BY order_by_list  */
#line 951 "yacc_sql.y"
        {
		(yyval.order_by_list) = (yyvsp[0].order_by_list);
	}
#line 2923 "yacc_sql.cpp"
    break;

  case 101: /* order_by_list: order_by_item  */
#line 958 "yacc_sql.y"
        {
		(yyval.order_by_list) = new std::vector<OrderByItem>;
		(yyval.order_by_list)->emplace_back(*(yyvsp[0].order_by_item));
		delete (yyvsp[0].order_by_item);
	}
#line 2933 "yacc_sql.cpp"
    break;

  case 102: /* order_by_list: order_by_item COMMA order_by_list  */
#line 964 "yacc_sql.y"
        {
		if ((yyvsp[0].order_by_list) != nullptr) {
			(yyval.order_by_list) = (yyvsp[0].order_by_list);
		} else {
			(yyval.order_by_list) = new std::vector<OrderByItem>;
		}
		(yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), *(yyvsp[-2].order_by_item));
		delete (yyvsp[-2].order_by_item);
	}
#line 2947 "yacc_sql.cpp"
    break;

  case 103: /* order_by_item: rel_attr asc_desc  */
#line 977 "yacc_sql.y"
        {
		(yyval.order_by_item) = new OrderByItem;
		(yyval.order_by_item)->attr = *(yyvsp[-1].rel_attr);
		(yyval.order_by_item)->asc = (yyvsp[0].asc_desc);
    (yyval.order_by_item)->expression = nullptr;
		delete (yyvsp[-1].rel_attr);
	}
#line 2959 "yacc_sql.cpp"
    break;

  case 104: /* order_by_item: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 984 "yacc_sql.y"
                                                          {
    (yyval.order_by_item) = new OrderByItem;
    (yyval.order_by_item)->expression = create_arithmetic_expression(ArithmeticExpr::Type::L2_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
  }
#line 2968 "yacc_sql.cpp"
    break;

  case 105: /* order_by_item: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 988 "yacc_sql.y"
                                                              {
    (yyval.order_by_item) = new OrderByItem;
    (yyval.order_by_item)->expression = create_arithmetic_expression(ArithmeticExpr::Type::COS_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
  }
#line 2977 "yacc_sql.cpp"
    break;

  case 106: /* order_by_item: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 992 "yacc_sql.y"
                                                            {
    (yyval.order_by_item) = new OrderByItem;
    (yyval.order_by_item)->expression = create_arithmetic_expression(ArithmeticExpr::Type::INN_PDT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
  }
#line 2986 "yacc_sql.cpp"
    break;

  case 107: /* limit: %empty  */
#line 1000 "yacc_sql.y"
  {
    (yyval.number) = -1; // set to invalid number
  }
#line 2994 "yacc_sql.cpp"
    break;

  case 108: /* limit: LIMIT NUMBER  */
#line 1004 "yacc_sql.y"
  {
    (yyval.number) = (yyvsp[0].number);
  }
#line 3002 "yacc_sql.cpp"
    break;

  case 109: /* asc_desc: %empty  */
#line 1010 "yacc_sql.y"
        {
		(yyval.asc_desc) = true; // default is ascending
	}
#line 3010 "yacc_sql.cpp"
    break;

  case 110: /* asc_desc: ASC  */
#line 1014 "yacc_sql.y"
        {
		(yyval.asc_desc) = true;
	}
#line 3018 "yacc_sql.cpp"
    break;

  case 111: /* asc_desc: DESC  */
#line 1018 "yacc_sql.y"
        {
		(yyval.asc_desc) = false;
	}
#line 3026 "yacc_sql.cpp"
    break;

  case 112: /* calc_stmt: CALC expression_list  */
#line 1025 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 3036 "yacc_sql.cpp"
    break;

  case 113: /* expression_list: expression  */
#line 1034 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 3045 "yacc_sql.cpp"
    break;

  case 114: /* expression_list: expression id_maybe_keyword  */
#line 1038 "yacc_sql.y"
                                  {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      (yyval.expression_list)->back()->set_name((yyvsp[0].string));
      (yyval.expression_list)->back()->set_aliased(true);
      free((yyvsp[0].string));
    }
#line 3057 "yacc_sql.cpp"
    break;

  case 115: /* expression_list: expression AS id_maybe_keyword  */
#line 1045 "yacc_sql.y"
                                     {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
      (yyval.expression_list)->back()->set_name((yyvsp[0].string));
      (yyval.expression_list)->back()->set_aliased(true);
      free((yyvsp[0].string));
    }
#line 3069 "yacc_sql.cpp"
    break;

  case 116: /* expression_list: expression COMMA expression_list  */
#line 1053 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 3082 "yacc_sql.cpp"
    break;

  case 117: /* expression_list: expression id_maybe_keyword COMMA expression_list  */
#line 1062 "yacc_sql.y"
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
#line 3098 "yacc_sql.cpp"
    break;

  case 118: /* expression_list: expression AS id_maybe_keyword COMMA expression_list  */
#line 1074 "yacc_sql.y"
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
#line 3114 "yacc_sql.cpp"
    break;

  case 119: /* expression: expression '+' expression  */
#line 1087 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3122 "yacc_sql.cpp"
    break;

  case 120: /* expression: expression '-' expression  */
#line 1090 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3130 "yacc_sql.cpp"
    break;

  case 121: /* expression: expression '*' expression  */
#line 1093 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3138 "yacc_sql.cpp"
    break;

  case 122: /* expression: expression '/' expression  */
#line 1096 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3146 "yacc_sql.cpp"
    break;

  case 123: /* expression: LBRACE expression RBRACE  */
#line 1099 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3155 "yacc_sql.cpp"
    break;

  case 124: /* expression: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 1103 "yacc_sql.y"
                                                            {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3163 "yacc_sql.cpp"
    break;

  case 125: /* expression: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 1106 "yacc_sql.y"
                                                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COS_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3171 "yacc_sql.cpp"
    break;

  case 126: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 1109 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INN_PDT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3179 "yacc_sql.cpp"
    break;

  case 127: /* expression: '-' expression  */
#line 1112 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3187 "yacc_sql.cpp"
    break;

  case 128: /* expression: value  */
#line 1115 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 3197 "yacc_sql.cpp"
    break;

  case 129: /* expression: rel_attr  */
#line 1120 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 3208 "yacc_sql.cpp"
    break;

  case 130: /* expression: '*'  */
#line 1126 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 3216 "yacc_sql.cpp"
    break;

  case 131: /* expression: id_maybe_keyword DOT '*'  */
#line 1129 "yacc_sql.y"
                               {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
    }
#line 3224 "yacc_sql.cpp"
    break;

  case 132: /* expression: MAX LBRACE agg_fun_attr_list RBRACE  */
#line 1134 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("max", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3232 "yacc_sql.cpp"
    break;

  case 133: /* expression: MIN LBRACE agg_fun_attr_list RBRACE  */
#line 1137 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("min", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3240 "yacc_sql.cpp"
    break;

  case 134: /* expression: COUNT LBRACE agg_fun_attr_list RBRACE  */
#line 1140 "yacc_sql.y"
                                            {
      (yyval.expression) = create_aggregate_expression("count", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3248 "yacc_sql.cpp"
    break;

  case 135: /* expression: AVG LBRACE agg_fun_attr_list RBRACE  */
#line 1143 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("avg", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3256 "yacc_sql.cpp"
    break;

  case 136: /* expression: SUM LBRACE agg_fun_attr_list RBRACE  */
#line 1146 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("sum", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3264 "yacc_sql.cpp"
    break;

  case 137: /* agg_fun_attr_list: agg_fun_attr  */
#line 1165 "yacc_sql.y"
                 {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3272 "yacc_sql.cpp"
    break;

  case 138: /* agg_fun_attr_list: agg_fun_attr COMMA agg_fun_attr_list  */
#line 1168 "yacc_sql.y"
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
#line 3288 "yacc_sql.cpp"
    break;

  case 139: /* agg_fun_attr: %empty  */
#line 1182 "yacc_sql.y"
    {
      std::string null_string = "";
      (yyval.expression) = new UnboundFieldExpr(null_string, null_string);
      (yyval.expression)->set_name(null_string);
    }
#line 3298 "yacc_sql.cpp"
    break;

  case 140: /* agg_fun_attr: '*'  */
#line 1187 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 3306 "yacc_sql.cpp"
    break;

  case 141: /* agg_fun_attr: rel_attr  */
#line 1190 "yacc_sql.y"
               {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[0].rel_attr)->relation_name, (yyvsp[0].rel_attr)->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 3316 "yacc_sql.cpp"
    break;

  case 142: /* rel_attr: id_maybe_keyword  */
#line 1198 "yacc_sql.y"
                     {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3326 "yacc_sql.cpp"
    break;

  case 143: /* rel_attr: id_maybe_keyword DOT id_maybe_keyword  */
#line 1203 "yacc_sql.y"
                                            {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3338 "yacc_sql.cpp"
    break;

  case 144: /* relation: id_maybe_keyword  */
#line 1213 "yacc_sql.y"
                     {
      (yyval.relation) = new RelationSqlNode();
      (yyval.relation)->name = (yyvsp[0].string);
      (yyval.relation)->alias = "";
      free((yyvsp[0].string));
    }
#line 3349 "yacc_sql.cpp"
    break;

  case 145: /* relation: id_maybe_keyword id_maybe_keyword  */
#line 1219 "yacc_sql.y"
                                        {
      (yyval.relation) = new RelationSqlNode();
      (yyval.relation)->name = (yyvsp[-1].string);
      (yyval.relation)->alias = (yyvsp[0].string);
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3361 "yacc_sql.cpp"
    break;

  case 146: /* relation: id_maybe_keyword AS id_maybe_keyword  */
#line 1226 "yacc_sql.y"
                                           {
      (yyval.relation) = new RelationSqlNode();
      (yyval.relation)->name = (yyvsp[-2].string);
      (yyval.relation)->alias = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3373 "yacc_sql.cpp"
    break;

  case 147: /* rel_list: relation  */
#line 1235 "yacc_sql.y"
             {
      (yyval.relation_list) = new std::vector<RelationSqlNode>();
      (yyval.relation_list)->push_back(*(yyvsp[0].relation));
      delete((yyvsp[0].relation));
    }
#line 3383 "yacc_sql.cpp"
    break;

  case 148: /* rel_list: relation COMMA rel_list  */
#line 1240 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelationSqlNode>;
      }

      (yyval.relation_list)->insert((yyval.relation_list)->begin(), *(yyvsp[-2].relation));
      delete((yyvsp[-2].relation));
    }
#line 3398 "yacc_sql.cpp"
    break;

  case 149: /* join_list: %empty  */
#line 1254 "yacc_sql.y"
    {
      (yyval.join_tuple_list) = nullptr;
    }
#line 3406 "yacc_sql.cpp"
    break;

  case 150: /* join_list: join join_list  */
#line 1257 "yacc_sql.y"
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
#line 3425 "yacc_sql.cpp"
    break;

  case 151: /* join: INNER JOIN relation ON condition_list  */
#line 1273 "yacc_sql.y"
                                          {
      (yyval.join_tuple) = new std::tuple<std::string, std::vector<ConditionSqlNode> *>((yyvsp[-2].relation)->name, (yyvsp[0].condition_list));
      delete (yyvsp[-2].relation);
    }
#line 3434 "yacc_sql.cpp"
    break;

  case 152: /* where: %empty  */
#line 1280 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3442 "yacc_sql.cpp"
    break;

  case 153: /* where: WHERE condition_list  */
#line 1283 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3450 "yacc_sql.cpp"
    break;

  case 154: /* condition_list: %empty  */
#line 1289 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3458 "yacc_sql.cpp"
    break;

  case 155: /* condition_list: condition  */
#line 1292 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3468 "yacc_sql.cpp"
    break;

  case 156: /* condition_list: condition AND condition_list  */
#line 1297 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3478 "yacc_sql.cpp"
    break;

  case 157: /* condition_list: condition OR condition_list  */
#line 1302 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      ConditionSqlNode *tmp = new ConditionSqlNode;
      tmp->flag = 1;
      (yyval.condition_list)->emplace_back(*tmp);
      delete (yyvsp[-2].condition);
      delete tmp;
    }
#line 3492 "yacc_sql.cpp"
    break;

  case 158: /* condition: expression comp_op expression  */
#line 1363 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3504 "yacc_sql.cpp"
    break;

  case 159: /* condition: expression comp_op LBRACE select_stmt RBRACE  */
#line 1370 "yacc_sql.y"
                                                   {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-4].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 3518 "yacc_sql.cpp"
    break;

  case 160: /* condition: expression IN_T LBRACE select_stmt RBRACE  */
#line 1379 "yacc_sql.y"
                                                {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-4].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::IN;
    }
#line 3532 "yacc_sql.cpp"
    break;

  case 161: /* condition: expression NOT IN_T LBRACE select_stmt RBRACE  */
#line 1388 "yacc_sql.y"
                                                    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-5].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::NOT_IN;
    }
#line 3546 "yacc_sql.cpp"
    break;

  case 162: /* condition: expression IN_T LBRACE value value_list RBRACE  */
#line 1398 "yacc_sql.y"
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
#line 3567 "yacc_sql.cpp"
    break;

  case 163: /* condition: expression NOT IN_T LBRACE value value_list RBRACE  */
#line 1414 "yacc_sql.y"
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
#line 3588 "yacc_sql.cpp"
    break;

  case 164: /* condition: EXISTS_T LBRACE select_stmt RBRACE  */
#line 1430 "yacc_sql.y"
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
#line 3603 "yacc_sql.cpp"
    break;

  case 165: /* condition: NOT EXISTS_T LBRACE select_stmt RBRACE  */
#line 1440 "yacc_sql.y"
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
#line 3618 "yacc_sql.cpp"
    break;

  case 166: /* condition: LBRACE select_stmt RBRACE comp_op expression  */
#line 1450 "yacc_sql.y"
                                                   {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      UnboundSubqueryExpr *left_expr = new UnboundSubqueryExpr((yyvsp[-3].sql_node));
      (yyval.condition)->left_expr = left_expr;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3632 "yacc_sql.cpp"
    break;

  case 167: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 1459 "yacc_sql.y"
                                                                  {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = new UnboundSubqueryExpr((yyvsp[-5].sql_node));
      (yyval.condition)->right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 3645 "yacc_sql.cpp"
    break;

  case 168: /* comp_op: EQ  */
#line 1470 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3651 "yacc_sql.cpp"
    break;

  case 169: /* comp_op: LT  */
#line 1471 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3657 "yacc_sql.cpp"
    break;

  case 170: /* comp_op: GT  */
#line 1472 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3663 "yacc_sql.cpp"
    break;

  case 171: /* comp_op: LE  */
#line 1473 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3669 "yacc_sql.cpp"
    break;

  case 172: /* comp_op: GE  */
#line 1474 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3675 "yacc_sql.cpp"
    break;

  case 173: /* comp_op: NE  */
#line 1475 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3681 "yacc_sql.cpp"
    break;

  case 174: /* comp_op: LK  */
#line 1476 "yacc_sql.y"
         { (yyval.comp) = LIKE; }
#line 3687 "yacc_sql.cpp"
    break;

  case 175: /* comp_op: NLK  */
#line 1477 "yacc_sql.y"
          {(yyval.comp) = NOT_LIKE; }
#line 3693 "yacc_sql.cpp"
    break;

  case 176: /* comp_op: IS_T  */
#line 1478 "yacc_sql.y"
           { (yyval.comp) = IS; }
#line 3699 "yacc_sql.cpp"
    break;

  case 177: /* comp_op: IS_NOT_T  */
#line 1479 "yacc_sql.y"
               { (yyval.comp) = IS_NOT; }
#line 3705 "yacc_sql.cpp"
    break;

  case 178: /* group_by: %empty  */
#line 1485 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3713 "yacc_sql.cpp"
    break;

  case 179: /* group_by: GROUP BY expression_list  */
#line 1490 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3721 "yacc_sql.cpp"
    break;

  case 180: /* having: %empty  */
#line 1497 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3729 "yacc_sql.cpp"
    break;

  case 181: /* having: HAVING condition_list  */
#line 1500 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3737 "yacc_sql.cpp"
    break;

  case 182: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE id_maybe_keyword  */
#line 1506 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3751 "yacc_sql.cpp"
    break;

  case 183: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1519 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3760 "yacc_sql.cpp"
    break;

  case 184: /* set_variable_stmt: SET id_maybe_keyword EQ value  */
#line 1527 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3772 "yacc_sql.cpp"
    break;


#line 3776 "yacc_sql.cpp"

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

#line 1539 "yacc_sql.y"

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
