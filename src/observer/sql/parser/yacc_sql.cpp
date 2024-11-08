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
  YYSYMBOL_id_list = 101,                  /* id_list  */
  YYSYMBOL_exit_stmt = 102,                /* exit_stmt  */
  YYSYMBOL_help_stmt = 103,                /* help_stmt  */
  YYSYMBOL_sync_stmt = 104,                /* sync_stmt  */
  YYSYMBOL_begin_stmt = 105,               /* begin_stmt  */
  YYSYMBOL_commit_stmt = 106,              /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 107,            /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 108,          /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 109,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 110,          /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 111,        /* create_index_stmt  */
  YYSYMBOL_create_vector_index_stmt = 112, /* create_vector_index_stmt  */
  YYSYMBOL_vector_index_param_list = 113,  /* vector_index_param_list  */
  YYSYMBOL_vector_index_field = 114,       /* vector_index_field  */
  YYSYMBOL_drop_index_stmt = 115,          /* drop_index_stmt  */
  YYSYMBOL_as_select = 116,                /* as_select  */
  YYSYMBOL_create_table_stmt = 117,        /* create_table_stmt  */
  YYSYMBOL_create_view_stmt = 118,         /* create_view_stmt  */
  YYSYMBOL_attr_def_list = 119,            /* attr_def_list  */
  YYSYMBOL_attr_def = 120,                 /* attr_def  */
  YYSYMBOL_nullable_spec = 121,            /* nullable_spec  */
  YYSYMBOL_number = 122,                   /* number  */
  YYSYMBOL_type = 123,                     /* type  */
  YYSYMBOL_insert_stmt = 124,              /* insert_stmt  */
  YYSYMBOL_value_list = 125,               /* value_list  */
  YYSYMBOL_value = 126,                    /* value  */
  YYSYMBOL_vector_elem = 127,              /* vector_elem  */
  YYSYMBOL_vector_value_list = 128,        /* vector_value_list  */
  YYSYMBOL_storage_format = 129,           /* storage_format  */
  YYSYMBOL_delete_stmt = 130,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 131,              /* update_stmt  */
  YYSYMBOL_set_clause_list = 132,          /* set_clause_list  */
  YYSYMBOL_set_clause = 133,               /* set_clause  */
  YYSYMBOL_select_stmt = 134,              /* select_stmt  */
  YYSYMBOL_order_by = 135,                 /* order_by  */
  YYSYMBOL_order_by_list = 136,            /* order_by_list  */
  YYSYMBOL_order_by_item = 137,            /* order_by_item  */
  YYSYMBOL_limit = 138,                    /* limit  */
  YYSYMBOL_asc_desc = 139,                 /* asc_desc  */
  YYSYMBOL_calc_stmt = 140,                /* calc_stmt  */
  YYSYMBOL_expression_list = 141,          /* expression_list  */
  YYSYMBOL_expression = 142,               /* expression  */
  YYSYMBOL_agg_fun_attr_list = 143,        /* agg_fun_attr_list  */
  YYSYMBOL_agg_fun_attr = 144,             /* agg_fun_attr  */
  YYSYMBOL_rel_attr = 145,                 /* rel_attr  */
  YYSYMBOL_relation = 146,                 /* relation  */
  YYSYMBOL_rel_list = 147,                 /* rel_list  */
  YYSYMBOL_join_list = 148,                /* join_list  */
  YYSYMBOL_join = 149,                     /* join  */
  YYSYMBOL_where = 150,                    /* where  */
  YYSYMBOL_condition_list = 151,           /* condition_list  */
  YYSYMBOL_condition = 152,                /* condition  */
  YYSYMBOL_comp_op = 153,                  /* comp_op  */
  YYSYMBOL_group_by = 154,                 /* group_by  */
  YYSYMBOL_having = 155,                   /* having  */
  YYSYMBOL_load_data_stmt = 156,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 157,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 158,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 159             /* opt_semicolon  */
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
#define YYFINAL  81
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   504

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  179
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  382

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
       0,   285,   285,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   318,   321,   326,   335,   341,
     347,   352,   358,   364,   370,   376,   383,   389,   397,   416,
     437,   512,   516,   527,   531,   535,   539,   543,   547,   554,
     565,   568,   571,   576,   605,   620,   634,   637,   650,   659,
     679,   680,   681,   685,   688,   689,   690,   691,   692,   693,
     696,   713,   716,   727,   731,   735,   741,   753,   763,   769,
     773,   780,   783,   792,   795,   802,   814,   831,   836,   849,
     858,   867,   922,   925,   932,   938,   951,   959,   963,   967,
     975,   978,   985,   988,   992,   999,  1008,  1013,  1020,  1027,
    1036,  1048,  1062,  1065,  1068,  1071,  1074,  1078,  1081,  1084,
    1087,  1090,  1095,  1101,  1104,  1109,  1112,  1115,  1118,  1121,
    1140,  1143,  1157,  1162,  1165,  1173,  1178,  1188,  1194,  1201,
    1210,  1215,  1229,  1232,  1248,  1255,  1258,  1264,  1267,  1272,
    1277,  1337,  1345,  1354,  1363,  1373,  1389,  1405,  1415,  1425,
    1434,  1445,  1446,  1447,  1448,  1449,  1450,  1451,  1452,  1453,
    1454,  1460,  1464,  1472,  1475,  1480,  1493,  1501,  1511,  1512
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
  "$accept", "commands", "command_wrapper", "id_list", "exit_stmt",
  "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "create_vector_index_stmt",
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

#define YYPACT_NINF (-276)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     412,   334,    11,   168,   168,   -48,    30,  -276,    12,    17,
     -28,  -276,  -276,  -276,  -276,  -276,   -20,    29,   412,    83,
     103,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,    36,    41,   112,   121,    54,    58,    59,
     168,   131,   132,   133,   138,   139,   -32,   144,   146,   148,
    -276,  -276,  -276,   147,  -276,  -276,   168,  -276,  -276,  -276,
     114,  -276,   135,  -276,  -276,    92,    93,   145,   136,   142,
    -276,  -276,  -276,  -276,    18,   149,    99,   104,    -5,  -276,
     160,    23,   -60,   -60,   -60,   -60,   -60,  -276,  -276,   183,
     168,   168,   168,   -56,  -276,   168,   116,   190,   168,   168,
     168,   168,   124,   181,   177,   134,   372,   143,   151,   209,
    -276,  -276,   157,   191,   194,    -5,   203,   153,   158,  -276,
     215,  -276,   216,   229,  -276,   231,   232,   234,   243,   -32,
     198,    15,   125,   174,  -276,  -276,  -276,   249,   168,   -63,
     -63,  -276,  -276,   -41,   254,   219,   264,   218,  -276,   237,
     177,   265,  -276,   253,   449,   277,  -276,   285,   124,   221,
     293,    -5,   209,  -276,   225,  -276,   -60,  -276,  -276,  -276,
    -276,   183,  -276,   168,   168,   168,   168,  -276,   230,  -276,
     124,   261,   177,   219,   372,     4,   307,   250,   354,  -276,
      35,   310,  -276,   134,   322,  -276,  -276,  -276,  -276,  -276,
    -276,    -6,   151,   315,   124,   320,   321,  -276,  -276,  -276,
    -276,  -276,    34,    47,    61,  -276,  -276,  -276,   124,   335,
    -276,   324,   326,   209,   328,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,   269,   344,   262,   218,   218,
     209,  -276,  -276,   275,   267,  -276,  -276,  -276,   277,   331,
     346,   278,   124,  -276,  -276,  -276,   337,   369,   378,   372,
     359,   416,   374,   209,   376,    33,     4,   208,  -276,  -276,
     392,  -276,  -276,   393,  -276,   349,    16,  -276,   395,   398,
     218,   168,   218,   336,   324,  -276,   299,  -276,   400,    33,
     324,   401,   402,  -276,    31,   383,  -276,   371,  -276,  -276,
    -276,  -276,   -49,   351,  -276,     4,   208,  -276,   324,   420,
     421,  -276,  -276,  -276,   353,   426,   431,   432,   436,  -276,
     435,    -1,   394,  -276,   438,   441,  -276,  -276,  -276,   312,
     168,   168,   168,   -49,  -276,  -276,  -276,  -276,  -276,  -276,
     434,   437,   439,   440,   460,   462,   179,   239,   276,  -276,
      62,   411,   399,   403,  -276,   312,   168,   168,   168,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,    67,    80,    84,  -276,
    -276,  -276
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
       0,    32,    33,    34,    30,    29,     0,     0,     0,     0,
     178,    24,    23,    16,    17,    18,    19,    10,    11,    12,
      13,    14,    15,     8,     9,     5,     7,     6,     4,     3,
      20,    21,    22,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      78,    73,    74,   135,    75,    76,     0,   123,   121,   105,
     106,   122,     0,    37,    36,     0,     0,     0,     0,     0,
     176,     1,   179,     2,    50,     0,     0,     0,    25,    35,
       0,     0,   132,   132,   132,   132,   132,    79,    80,    81,
       0,     0,     0,     0,   120,     0,     0,   107,     0,     0,
       0,     0,     0,     0,   145,     0,     0,     0,     0,     0,
      54,    52,     0,     0,     0,    25,    26,     0,     0,   116,
     135,   133,     0,   130,   134,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   136,   124,   109,   108,     0,   112,
     113,   114,   115,   137,   140,   142,     0,   147,    85,     0,
     145,    87,   177,     0,     0,    56,    51,     0,     0,     0,
       0,    25,     0,    49,     0,   125,   132,   126,   127,   128,
     129,    81,    77,     0,     0,     0,     0,   110,     0,   138,
       0,     0,   145,   142,     0,     0,     0,     0,     0,   146,
     148,     0,    86,     0,     0,    64,    65,    66,    67,    68,
      69,    62,     0,     0,     0,     0,     0,    28,    27,    55,
     131,    82,     0,     0,     0,   111,   139,   141,     0,   171,
     143,    71,     0,     0,     0,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,     0,     0,     0,   147,   147,
       0,    89,    88,     0,     0,    60,    61,    59,    56,    83,
       0,     0,     0,   117,   118,   119,     0,     0,   173,     0,
       0,     0,     0,     0,     0,     0,     0,   151,   149,   150,
       0,   175,    63,     0,    57,     0,    50,    38,     0,     0,
     147,     0,   147,    92,    71,    70,     0,   157,     0,     0,
      71,     0,     0,    90,    62,     0,    53,     0,    39,   144,
     172,   174,     0,   100,    72,     0,   159,   158,    71,     0,
       0,   153,   152,    58,     0,     0,     0,     0,     0,    93,
      94,   102,     0,    91,     0,     0,   154,   155,    84,     0,
       0,     0,     0,     0,   104,   103,    96,   101,   160,   156,
       0,     0,     0,     0,     0,    41,     0,     0,     0,    95,
       0,     0,     0,     0,    40,     0,     0,     0,     0,    43,
      44,    45,    46,    47,    48,    42,     0,     0,     0,    97,
      98,    99
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -276,  -276,   472,  -102,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,   127,  -276,  -276,   207,  -276,
    -276,   236,   283,   192,  -276,  -276,  -276,  -275,  -104,   358,
     317,  -276,  -276,  -276,   296,  -276,   -83,  -276,   159,  -276,
    -276,  -276,  -276,    -2,   -50,   -85,  -276,   -89,  -150,  -142,
     308,  -276,  -139,   -79,  -276,   233,  -276,  -276,  -276,  -276,
    -276,  -276
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,   127,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,   354,   355,    32,   120,    33,
      34,   213,   165,   257,   283,   211,    35,   270,    68,    99,
     140,   286,    36,    37,   160,   161,    38,   313,   329,   330,
     333,   346,    39,    69,    70,   132,   133,    71,   154,   155,
     192,   193,   158,   199,   200,   247,   268,   293,    40,    41,
      42,    83
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      91,   121,    72,   134,   134,   134,   134,   134,   135,   136,
     137,   138,   162,   344,   254,   125,   104,     4,   215,   314,
      48,   202,    49,   170,    50,   320,   326,   327,   328,     4,
     130,     4,   110,   111,   144,   131,   166,   183,   118,   145,
      74,   130,    73,   335,   129,   188,     4,    75,   227,   189,
     141,   142,   143,   229,    76,   263,    97,    98,   149,   150,
     151,   152,    77,    51,    52,    53,    54,    55,   264,   218,
      78,    56,   260,    79,   248,   249,   255,   256,   266,    57,
      58,    59,   265,    81,   345,   126,    60,   134,   379,   219,
     231,   220,    61,    62,    63,    64,    65,   251,    66,    67,
      56,   380,   119,   146,   119,   381,    82,   198,   108,   109,
     110,   111,   232,   255,   256,    60,   108,   109,   110,   111,
     289,    61,    62,    86,    64,    65,    84,   108,   109,   110,
     111,    85,    87,   222,   223,   224,   105,   369,   370,   371,
     108,   109,   110,   111,    88,    91,   187,   184,    89,    90,
     272,    92,    93,    94,   108,   109,   110,   111,    95,    96,
     108,   109,   110,   111,   100,   294,   101,   280,   102,   278,
     279,   300,   112,   108,   109,   110,   111,   108,   109,   110,
     111,   103,   113,   114,   225,   116,   115,   117,    50,   123,
     298,   122,   301,   302,   124,   318,   185,   277,   198,   198,
     106,   366,   128,   121,   107,   139,   147,   108,   109,   110,
     111,   309,   148,   311,   153,   157,   319,   156,   108,   109,
     110,   111,     4,   331,   159,   171,    91,    51,    52,    53,
      54,    55,   334,   168,   163,    56,   169,   175,   195,   172,
     198,   164,   198,    57,    58,    59,   316,   167,   173,   174,
      60,   176,   177,   178,   331,   179,    61,    62,    63,    64,
      65,   367,    66,    67,   180,    91,   182,   108,   109,   110,
     111,   186,   108,   109,   110,   111,   190,    51,    52,    53,
      54,    55,   276,   191,   194,    56,   201,   203,   204,   310,
     356,   357,   358,    57,    58,    59,   196,   197,   368,   212,
      60,   108,   109,   110,   111,   214,    61,    62,    63,    64,
      65,   216,    66,    67,   217,   144,   376,   377,   378,   315,
     226,    51,    52,    53,    54,    55,   228,   233,   234,    56,
     250,   253,   108,   109,   110,   111,   259,    57,    58,    59,
     261,   262,   267,    43,    60,    44,   269,   271,   273,   274,
      61,    62,    63,    64,    65,   282,    66,    67,    51,    52,
      53,    54,    55,    45,   275,   281,    56,   287,   288,   108,
     109,   110,   111,   291,    57,    58,    59,    56,   285,   290,
     295,    60,   350,   351,   352,   353,   292,    61,    62,    63,
      64,    65,    60,    66,    67,   297,   299,   305,    61,    62,
      46,    64,    65,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   303,   304,    47,   307,     1,     2,   308,
     312,   317,   321,   322,     3,     4,     5,     6,     7,     8,
       9,    10,   324,   245,   246,    11,    12,    13,   332,    56,
     325,   336,   337,   338,    14,    15,   339,   108,   109,   110,
     111,   340,   341,    16,    60,    17,   342,   343,    18,   348,
      61,    62,   349,    64,    65,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   205,   206,   207,   208,   209,
     210,   364,   347,   360,   365,   372,   361,   373,   362,   363,
      80,   374,   375,   306,   284,   258,   323,   181,   221,   252,
       0,   230,   359,     0,   296
};

static const yytype_int16 yycheck[] =
{
      50,    84,     4,    92,    93,    94,    95,    96,    93,    94,
      95,    96,   116,    14,    20,    20,    66,    13,   168,   294,
       9,   160,    11,   125,    20,   300,    75,    76,    77,    13,
      90,    13,    95,    96,    90,    95,   119,    22,    20,    95,
      10,    90,    90,   318,    21,    86,    13,    35,   190,    90,
     100,   101,   102,   192,    37,    21,    88,    89,   108,   109,
     110,   111,    90,    59,    60,    61,    62,    63,    21,   171,
      90,    67,   214,    44,    39,    40,    82,    83,   228,    75,
      76,    77,    21,     0,    85,    90,    82,   176,    21,   172,
     194,   176,    88,    89,    90,    91,    92,   201,    94,    95,
      67,    21,    86,   105,    86,    21,     3,   157,    93,    94,
      95,    96,   195,    82,    83,    82,    93,    94,    95,    96,
     262,    88,    89,    11,    91,    92,    90,    93,    94,    95,
      96,    90,    11,   183,   184,   185,    22,    75,    76,    77,
      93,    94,    95,    96,    90,   195,   148,    22,    90,    90,
     233,    20,    20,    20,    93,    94,    95,    96,    20,    20,
      93,    94,    95,    96,    20,   269,    20,   250,    20,   248,
     249,   275,    37,    93,    94,    95,    96,    93,    94,    95,
      96,    34,    90,    90,   186,    49,    41,    45,    20,    90,
     273,    42,   275,   276,    90,   299,    22,   247,   248,   249,
      86,    22,    42,   286,    90,    22,    90,    93,    94,    95,
      96,   290,    22,   292,    90,    38,   299,    36,    93,    94,
      95,    96,    13,   312,    90,    22,   276,    59,    60,    61,
      62,    63,   315,    42,    91,    67,    42,    21,    20,    86,
     290,    90,   292,    75,    76,    77,   296,    90,    90,    34,
      82,    22,    21,    21,   343,    21,    88,    89,    90,    91,
      92,    22,    94,    95,    21,   315,    68,    93,    94,    95,
      96,    22,    93,    94,    95,    96,    22,    59,    60,    61,
      62,    63,    20,    64,    20,    67,    49,    22,    35,   291,
     340,   341,   342,    75,    76,    77,    78,    79,    22,    22,
      82,    93,    94,    95,    96,    20,    88,    89,    90,    91,
      92,    90,    94,    95,    21,    90,   366,   367,   368,    20,
      90,    59,    60,    61,    62,    63,    65,    20,    78,    67,
      20,     9,    93,    94,    95,    96,    21,    75,    76,    77,
      20,    20,     7,     9,    82,    11,    22,    21,    20,    80,
      88,    89,    90,    91,    92,    88,    94,    95,    59,    60,
      61,    62,    63,    29,    20,    90,    67,    21,    90,    93,
      94,    95,    96,     4,    75,    76,    77,    67,    47,    42,
      21,    82,    70,    71,    72,    73,     8,    88,    89,    90,
      91,    92,    82,    94,    95,    21,    20,    48,    88,    89,
      66,    91,    92,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    21,    21,    81,    21,     5,     6,    21,
      84,    21,    21,    21,    12,    13,    14,    15,    16,    17,
      18,    19,    49,    79,    80,    23,    24,    25,    87,    67,
      69,    21,    21,    90,    32,    33,    20,    93,    94,    95,
      96,    20,    20,    41,    82,    43,    20,    22,    46,    21,
      88,    89,    21,    91,    92,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    26,    27,    28,    29,    30,
      31,    21,    88,    49,    22,    74,    49,    88,    49,    49,
      18,    88,   365,   286,   258,   212,   304,   139,   181,   203,
      -1,   193,   343,    -1,   271
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    12,    13,    14,    15,    16,    17,    18,
      19,    23,    24,    25,    32,    33,    41,    43,    46,    99,
     100,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   115,   117,   118,   124,   130,   131,   134,   140,
     156,   157,   158,     9,    11,    29,    66,    81,     9,    11,
      20,    59,    60,    61,    62,    63,    67,    75,    76,    77,
      82,    88,    89,    90,    91,    92,    94,    95,   126,   141,
     142,   145,   141,    90,    10,    35,    37,    90,    90,    44,
     100,     0,     3,   159,    90,    90,    11,    11,    90,    90,
      90,   142,    20,    20,    20,    20,    20,    88,    89,   127,
      20,    20,    20,    34,   142,    22,    86,    90,    93,    94,
      95,    96,    37,    90,    90,    41,    49,    45,    20,    86,
     116,   134,    42,    90,    90,    20,    90,   101,    42,    21,
      90,    95,   143,   144,   145,   143,   143,   143,   143,    22,
     128,   142,   142,   142,    90,    95,   141,    90,    22,   142,
     142,   142,   142,    90,   146,   147,    36,    38,   150,    90,
     132,   133,   126,    91,    90,   120,   134,    90,    42,    42,
     101,    22,    86,    90,    34,    21,    22,    21,    21,    21,
      21,   127,    68,    22,    22,    22,    22,   141,    86,    90,
      22,    64,   148,   149,    20,    20,    78,    79,   142,   151,
     152,    49,   150,    22,    35,    26,    27,    28,    29,    30,
      31,   123,    22,   119,    20,   146,    90,    21,   101,   134,
     143,   128,   142,   142,   142,   141,    90,   147,    65,   150,
     148,   126,   134,    20,    78,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    79,    80,   153,    39,    40,
      20,   126,   132,     9,    20,    82,    83,   121,   120,    21,
     147,    20,    20,    21,    21,    21,   146,     7,   154,    22,
     125,    21,   134,    20,    80,    20,    20,   142,   151,   151,
     134,    90,    88,   122,   119,    47,   129,    21,    90,   147,
      42,     4,     8,   155,   126,    21,   153,    21,   134,    20,
     126,   134,   134,    21,    21,    48,   116,    21,    21,   151,
     141,   151,    84,   135,   125,    20,   142,    21,   126,   134,
     125,    21,    21,   121,    49,    69,    75,    76,    77,   136,
     137,   145,    87,   138,   134,   125,    21,    21,    90,    20,
      20,    20,    20,    22,    14,    85,   139,    88,    21,    21,
      70,    71,    72,    73,   113,   114,   142,   142,   142,   136,
      49,    49,    49,    49,    21,    22,    22,    22,    22,    75,
      76,    77,    74,    88,    88,   113,   142,   142,   142,    21,
      21,    21
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    98,    99,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   101,   101,   101,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   111,
     112,   113,   113,   114,   114,   114,   114,   114,   114,   115,
     116,   116,   116,   117,   117,   118,   119,   119,   120,   120,
     121,   121,   121,   122,   123,   123,   123,   123,   123,   123,
     124,   125,   125,   126,   126,   126,   126,   126,   126,   127,
     127,   128,   128,   129,   129,   130,   131,   132,   132,   133,
     133,   134,   135,   135,   136,   136,   137,   137,   137,   137,
     138,   138,   139,   139,   139,   140,   141,   141,   141,   141,
     141,   141,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     143,   143,   144,   144,   144,   145,   145,   146,   146,   146,
     147,   147,   148,   148,   149,   150,   150,   151,   151,   151,
     151,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   154,   154,   155,   155,   156,   157,   158,   159,   159
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     3,     2,     2,     8,     9,
      13,     1,     3,     3,     3,     3,     3,     3,     3,     5,
       0,     2,     1,     9,     4,     6,     0,     3,     6,     3,
       1,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       8,     0,     3,     1,     1,     1,     1,     4,     1,     1,
       1,     0,     3,     0,     4,     4,     5,     1,     3,     3,
       5,    10,     0,     2,     1,     3,     2,     6,     6,     6,
       0,     2,     0,     1,     1,     2,     1,     2,     3,     3,
       4,     5,     3,     3,     3,     3,     3,     6,     6,     6,
       2,     1,     1,     1,     3,     4,     4,     4,     4,     4,
       1,     3,     0,     1,     1,     1,     3,     1,     2,     3,
       1,     3,     0,     2,     5,     0,     2,     0,     1,     3,
       3,     3,     5,     5,     6,     6,     7,     4,     5,     5,
       7,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     3,     0,     2,     7,     2,     4,     0,     1
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
#line 286 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1994 "yacc_sql.cpp"
    break;

  case 25: /* id_list: %empty  */
#line 318 "yacc_sql.y"
  {
    (yyval.id_list) = nullptr;
  }
#line 2002 "yacc_sql.cpp"
    break;

  case 26: /* id_list: ID  */
#line 321 "yacc_sql.y"
       {
    (yyval.id_list) = new std::vector<std::string>;
    (yyval.id_list)->emplace_back((yyvsp[0].string));
    free((yyvsp[0].string));
  }
#line 2012 "yacc_sql.cpp"
    break;

  case 27: /* id_list: ID COMMA id_list  */
#line 326 "yacc_sql.y"
                     {
    if ((yyvsp[0].id_list) != nullptr) {
      (yyval.id_list) = (yyvsp[0].id_list);
    } else {
      (yyval.id_list) = new std::vector<std::string>;
    }
    (yyval.id_list)->emplace((yyval.id_list)->begin(), (yyvsp[-2].string));
    free((yyvsp[-2].string));
  }
#line 2026 "yacc_sql.cpp"
    break;

  case 28: /* id_list: LBRACE id_list RBRACE  */
#line 335 "yacc_sql.y"
                          {
    (yyval.id_list) = (yyvsp[-1].id_list);
  }
#line 2034 "yacc_sql.cpp"
    break;

  case 29: /* exit_stmt: EXIT  */
#line 341 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 2043 "yacc_sql.cpp"
    break;

  case 30: /* help_stmt: HELP  */
#line 347 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2051 "yacc_sql.cpp"
    break;

  case 31: /* sync_stmt: SYNC  */
#line 352 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2059 "yacc_sql.cpp"
    break;

  case 32: /* begin_stmt: TRX_BEGIN  */
#line 358 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2067 "yacc_sql.cpp"
    break;

  case 33: /* commit_stmt: TRX_COMMIT  */
#line 364 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2075 "yacc_sql.cpp"
    break;

  case 34: /* rollback_stmt: TRX_ROLLBACK  */
#line 370 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2083 "yacc_sql.cpp"
    break;

  case 35: /* drop_table_stmt: DROP TABLE ID  */
#line 376 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2093 "yacc_sql.cpp"
    break;

  case 36: /* show_tables_stmt: SHOW TABLES  */
#line 383 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2101 "yacc_sql.cpp"
    break;

  case 37: /* desc_table_stmt: DESC ID  */
#line 389 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2111 "yacc_sql.cpp"
    break;

  case 38: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 398 "yacc_sql.y"
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
#line 2134 "yacc_sql.cpp"
    break;

  case 39: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 417 "yacc_sql.y"
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
#line 2156 "yacc_sql.cpp"
    break;

  case 40: /* create_vector_index_stmt: CREATE VECTOR_T INDEX ID ON relation LBRACE ID RBRACE WITH LBRACE vector_index_param_list RBRACE  */
#line 438 "yacc_sql.y"
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
#line 2232 "yacc_sql.cpp"
    break;

  case 41: /* vector_index_param_list: vector_index_field  */
#line 512 "yacc_sql.y"
                       {
      (yyval.vec_index_param_list) = new std::vector<VecIndexFieldAnno>();
      (yyval.vec_index_param_list)->push_back((yyvsp[0].vec_index_param));
    }
#line 2241 "yacc_sql.cpp"
    break;

  case 42: /* vector_index_param_list: vector_index_field COMMA vector_index_param_list  */
#line 516 "yacc_sql.y"
                                                       {
      if((yyvsp[0].vec_index_param_list) != nullptr){
        (yyval.vec_index_param_list) = (yyvsp[0].vec_index_param_list);
      } else {
        (yyval.vec_index_param_list) = new std::vector<VecIndexFieldAnno>();
      }
      (yyval.vec_index_param_list)->push_back((yyvsp[-2].vec_index_param));
    }
#line 2254 "yacc_sql.cpp"
    break;

  case 43: /* vector_index_field: DISTANCE EQ L2_DISTANCE  */
#line 528 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::DISTANCE_FIELD, static_cast<int>(DISTANCE_ALGO::L2_DISTANCE)};
    }
#line 2262 "yacc_sql.cpp"
    break;

  case 44: /* vector_index_field: DISTANCE EQ COSINE_DISTANCE  */
#line 532 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::DISTANCE_FIELD, static_cast<int>(DISTANCE_ALGO::COSINE_DISTANCE)};
    }
#line 2270 "yacc_sql.cpp"
    break;

  case 45: /* vector_index_field: DISTANCE EQ INNER_PRODUCT  */
#line 536 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::DISTANCE_FIELD, static_cast<int>(DISTANCE_ALGO::INNER_PRODUCT)};
    }
#line 2278 "yacc_sql.cpp"
    break;

  case 46: /* vector_index_field: TYPE EQ IVFFLAT  */
#line 540 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::TYPE_FIELD, 1};
    }
#line 2286 "yacc_sql.cpp"
    break;

  case 47: /* vector_index_field: LISTS EQ NUMBER  */
#line 544 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::LISTS_FIELD, (yyvsp[0].number)};
    }
#line 2294 "yacc_sql.cpp"
    break;

  case 48: /* vector_index_field: PROBES EQ NUMBER  */
#line 548 "yacc_sql.y"
    {
      (yyval.vec_index_param) = VecIndexFieldAnno{VecIndexField::PROBES_FIELD, (yyvsp[0].number)};
    }
#line 2302 "yacc_sql.cpp"
    break;

  case 49: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 555 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2314 "yacc_sql.cpp"
    break;

  case 50: /* as_select: %empty  */
#line 565 "yacc_sql.y"
  {
    (yyval.sql_node) = nullptr;
  }
#line 2322 "yacc_sql.cpp"
    break;

  case 51: /* as_select: AS select_stmt  */
#line 568 "yacc_sql.y"
                   {
    (yyval.sql_node) = (yyvsp[0].sql_node);
  }
#line 2330 "yacc_sql.cpp"
    break;

  case 52: /* as_select: select_stmt  */
#line 571 "yacc_sql.y"
                {
    (yyval.sql_node) = (yyvsp[0].sql_node);
  }
#line 2338 "yacc_sql.cpp"
    break;

  case 53: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format as_select  */
#line 577 "yacc_sql.y"
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
#line 2371 "yacc_sql.cpp"
    break;

  case 54: /* create_table_stmt: CREATE TABLE ID as_select  */
#line 605 "yacc_sql.y"
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
#line 2389 "yacc_sql.cpp"
    break;

  case 55: /* create_view_stmt: CREATE VIEW ID id_list AS select_stmt  */
#line 620 "yacc_sql.y"
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
#line 2405 "yacc_sql.cpp"
    break;

  case 56: /* attr_def_list: %empty  */
#line 634 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2413 "yacc_sql.cpp"
    break;

  case 57: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 638 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2427 "yacc_sql.cpp"
    break;

  case 58: /* attr_def: ID type LBRACE number RBRACE nullable_spec  */
#line 651 "yacc_sql.y"
  {
    (yyval.attr_info) = new AttrInfoSqlNode;
    (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
    (yyval.attr_info)->name = (yyvsp[-5].string);
    (yyval.attr_info)->length = (yyvsp[-2].number);
    (yyval.attr_info)->nullable = (yyvsp[0].nullable_spec);
    free((yyvsp[-5].string));
  }
#line 2440 "yacc_sql.cpp"
    break;

  case 59: /* attr_def: ID type nullable_spec  */
#line 660 "yacc_sql.y"
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
#line 2461 "yacc_sql.cpp"
    break;

  case 60: /* nullable_spec: NULL_T  */
#line 679 "yacc_sql.y"
         { (yyval.nullable_spec) = true; }
#line 2467 "yacc_sql.cpp"
    break;

  case 61: /* nullable_spec: NOT_NULL_T  */
#line 680 "yacc_sql.y"
               { (yyval.nullable_spec) = false; }
#line 2473 "yacc_sql.cpp"
    break;

  case 62: /* nullable_spec: %empty  */
#line 681 "yacc_sql.y"
                { (yyval.nullable_spec) = true; }
#line 2479 "yacc_sql.cpp"
    break;

  case 63: /* number: NUMBER  */
#line 685 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2485 "yacc_sql.cpp"
    break;

  case 64: /* type: INT_T  */
#line 688 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2491 "yacc_sql.cpp"
    break;

  case 65: /* type: STRING_T  */
#line 689 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2497 "yacc_sql.cpp"
    break;

  case 66: /* type: FLOAT_T  */
#line 690 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2503 "yacc_sql.cpp"
    break;

  case 67: /* type: VECTOR_T  */
#line 691 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2509 "yacc_sql.cpp"
    break;

  case 68: /* type: DATE_T  */
#line 692 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2515 "yacc_sql.cpp"
    break;

  case 69: /* type: TEXT_T  */
#line 693 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2521 "yacc_sql.cpp"
    break;

  case 70: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 697 "yacc_sql.y"
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
#line 2538 "yacc_sql.cpp"
    break;

  case 71: /* value_list: %empty  */
#line 713 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2546 "yacc_sql.cpp"
    break;

  case 72: /* value_list: COMMA value value_list  */
#line 716 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2560 "yacc_sql.cpp"
    break;

  case 73: /* value: NUMBER  */
#line 727 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2569 "yacc_sql.cpp"
    break;

  case 74: /* value: FLOAT  */
#line 731 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2578 "yacc_sql.cpp"
    break;

  case 75: /* value: SSS  */
#line 735 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2589 "yacc_sql.cpp"
    break;

  case 76: /* value: DATE  */
#line 741 "yacc_sql.y"
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
#line 2606 "yacc_sql.cpp"
    break;

  case 77: /* value: LBRACKET vector_elem vector_value_list RBRACKET  */
#line 753 "yacc_sql.y"
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
#line 2621 "yacc_sql.cpp"
    break;

  case 78: /* value: NULL_T  */
#line 763 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2630 "yacc_sql.cpp"
    break;

  case 79: /* vector_elem: NUMBER  */
#line 769 "yacc_sql.y"
           {
      (yyval.floats) = (float)(yyvsp[0].number);
      (yyloc) = (yylsp[0]);
    }
#line 2639 "yacc_sql.cpp"
    break;

  case 80: /* vector_elem: FLOAT  */
#line 773 "yacc_sql.y"
           {
      (yyval.floats) = (float)(yyvsp[0].floats);
      (yyloc) = (yylsp[0]);
    }
#line 2648 "yacc_sql.cpp"
    break;

  case 81: /* vector_value_list: %empty  */
#line 780 "yacc_sql.y"
    {
      (yyval.vector_elem_list) = nullptr;
    }
#line 2656 "yacc_sql.cpp"
    break;

  case 82: /* vector_value_list: COMMA vector_elem vector_value_list  */
#line 783 "yacc_sql.y"
                                         {
      (yyval.vector_elem_list) = (yyvsp[0].vector_elem_list);
      if((yyval.vector_elem_list) == nullptr){
        (yyval.vector_elem_list) = new vector<float>;
      }
      (yyval.vector_elem_list)->push_back((yyvsp[-1].floats));
    }
#line 2668 "yacc_sql.cpp"
    break;

  case 83: /* storage_format: %empty  */
#line 792 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2676 "yacc_sql.cpp"
    break;

  case 84: /* storage_format: STORAGE FORMAT EQ ID  */
#line 796 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2684 "yacc_sql.cpp"
    break;

  case 85: /* delete_stmt: DELETE FROM ID where  */
#line 803 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2698 "yacc_sql.cpp"
    break;

  case 86: /* update_stmt: UPDATE ID SET set_clause_list where  */
#line 815 "yacc_sql.y"
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
#line 2716 "yacc_sql.cpp"
    break;

  case 87: /* set_clause_list: set_clause  */
#line 831 "yacc_sql.y"
             {
    (yyval.set_clause_list) = new std::vector<SetClauseSqlNode>;
    (yyval.set_clause_list)->emplace_back(*(yyvsp[0].set_clause));
    delete (yyvsp[0].set_clause);
  }
#line 2726 "yacc_sql.cpp"
    break;

  case 88: /* set_clause_list: set_clause COMMA set_clause_list  */
#line 837 "yacc_sql.y"
  {
    if ((yyvsp[0].set_clause_list) != nullptr) {
      (yyval.set_clause_list) = (yyvsp[0].set_clause_list);
    } else {
      (yyval.set_clause_list) = new std::vector<SetClauseSqlNode>;
    }
    (yyval.set_clause_list)->emplace((yyval.set_clause_list)->begin(), *(yyvsp[-2].set_clause));
    delete (yyvsp[-2].set_clause);
  }
#line 2740 "yacc_sql.cpp"
    break;

  case 89: /* set_clause: ID EQ value  */
#line 849 "yacc_sql.y"
              {
    (yyval.set_clause) = new SetClauseSqlNode;
    (yyval.set_clause)->attribute_name = (yyvsp[-2].string);
    (yyval.set_clause)->value = *(yyvsp[0].value);
    (yyval.set_clause)->has_subquery = false;
    (yyval.set_clause)->subquery = nullptr;
    free((yyvsp[-2].string));
    delete (yyvsp[0].value);
  }
#line 2754 "yacc_sql.cpp"
    break;

  case 90: /* set_clause: ID EQ LBRACE select_stmt RBRACE  */
#line 858 "yacc_sql.y"
                                    {
    (yyval.set_clause) = new SetClauseSqlNode;
    (yyval.set_clause)->attribute_name = (yyvsp[-4].string);
    (yyval.set_clause)->has_subquery = true;
    (yyval.set_clause)->subquery = (yyvsp[-1].sql_node);
    free((yyvsp[-4].string));
  }
#line 2766 "yacc_sql.cpp"
    break;

  case 91: /* select_stmt: SELECT expression_list FROM rel_list join_list where group_by having order_by limit  */
#line 868 "yacc_sql.y"
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
#line 2821 "yacc_sql.cpp"
    break;

  case 92: /* order_by: %empty  */
#line 922 "yacc_sql.y"
        {
		(yyval.order_by_list) = nullptr;
	}
#line 2829 "yacc_sql.cpp"
    break;

  case 93: /* order_by: ORDER_BY order_by_list  */
#line 926 "yacc_sql.y"
        {
		(yyval.order_by_list) = (yyvsp[0].order_by_list);
	}
#line 2837 "yacc_sql.cpp"
    break;

  case 94: /* order_by_list: order_by_item  */
#line 933 "yacc_sql.y"
        {
		(yyval.order_by_list) = new std::vector<OrderByItem>;
		(yyval.order_by_list)->emplace_back(*(yyvsp[0].order_by_item));
		delete (yyvsp[0].order_by_item);
	}
#line 2847 "yacc_sql.cpp"
    break;

  case 95: /* order_by_list: order_by_item COMMA order_by_list  */
#line 939 "yacc_sql.y"
        {
		if ((yyvsp[0].order_by_list) != nullptr) {
			(yyval.order_by_list) = (yyvsp[0].order_by_list);
		} else {
			(yyval.order_by_list) = new std::vector<OrderByItem>;
		}
		(yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), *(yyvsp[-2].order_by_item));
		delete (yyvsp[-2].order_by_item);
	}
#line 2861 "yacc_sql.cpp"
    break;

  case 96: /* order_by_item: rel_attr asc_desc  */
#line 952 "yacc_sql.y"
        {
		(yyval.order_by_item) = new OrderByItem;
		(yyval.order_by_item)->attr = *(yyvsp[-1].rel_attr);
		(yyval.order_by_item)->asc = (yyvsp[0].asc_desc);
    (yyval.order_by_item)->expression = nullptr;
		delete (yyvsp[-1].rel_attr);
	}
#line 2873 "yacc_sql.cpp"
    break;

  case 97: /* order_by_item: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 959 "yacc_sql.y"
                                                          {
    (yyval.order_by_item) = new OrderByItem;
    (yyval.order_by_item)->expression = create_arithmetic_expression(ArithmeticExpr::Type::L2_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
  }
#line 2882 "yacc_sql.cpp"
    break;

  case 98: /* order_by_item: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 963 "yacc_sql.y"
                                                              {
    (yyval.order_by_item) = new OrderByItem;
    (yyval.order_by_item)->expression = create_arithmetic_expression(ArithmeticExpr::Type::COS_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
  }
#line 2891 "yacc_sql.cpp"
    break;

  case 99: /* order_by_item: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 967 "yacc_sql.y"
                                                            {
    (yyval.order_by_item) = new OrderByItem;
    (yyval.order_by_item)->expression = create_arithmetic_expression(ArithmeticExpr::Type::INN_PDT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
  }
#line 2900 "yacc_sql.cpp"
    break;

  case 100: /* limit: %empty  */
#line 975 "yacc_sql.y"
  {
    (yyval.number) = INT_MAX; // set to invalid number
  }
#line 2908 "yacc_sql.cpp"
    break;

  case 101: /* limit: LIMIT NUMBER  */
#line 979 "yacc_sql.y"
  {
    (yyval.number) = (yyvsp[0].number);
  }
#line 2916 "yacc_sql.cpp"
    break;

  case 102: /* asc_desc: %empty  */
#line 985 "yacc_sql.y"
        {
		(yyval.asc_desc) = true; // default is ascending
	}
#line 2924 "yacc_sql.cpp"
    break;

  case 103: /* asc_desc: ASC  */
#line 989 "yacc_sql.y"
        {
		(yyval.asc_desc) = true;
	}
#line 2932 "yacc_sql.cpp"
    break;

  case 104: /* asc_desc: DESC  */
#line 993 "yacc_sql.y"
        {
		(yyval.asc_desc) = false;
	}
#line 2940 "yacc_sql.cpp"
    break;

  case 105: /* calc_stmt: CALC expression_list  */
#line 1000 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2950 "yacc_sql.cpp"
    break;

  case 106: /* expression_list: expression  */
#line 1009 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2959 "yacc_sql.cpp"
    break;

  case 107: /* expression_list: expression ID  */
#line 1013 "yacc_sql.y"
                    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      (yyval.expression_list)->back()->set_name((yyvsp[0].string));
      (yyval.expression_list)->back()->set_aliased(true);
      free((yyvsp[0].string));
    }
#line 2971 "yacc_sql.cpp"
    break;

  case 108: /* expression_list: expression AS ID  */
#line 1020 "yacc_sql.y"
                       {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
      (yyval.expression_list)->back()->set_name((yyvsp[0].string));
      (yyval.expression_list)->back()->set_aliased(true);
      free((yyvsp[0].string));
    }
#line 2983 "yacc_sql.cpp"
    break;

  case 109: /* expression_list: expression COMMA expression_list  */
#line 1028 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2996 "yacc_sql.cpp"
    break;

  case 110: /* expression_list: expression ID COMMA expression_list  */
#line 1037 "yacc_sql.y"
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
#line 3012 "yacc_sql.cpp"
    break;

  case 111: /* expression_list: expression AS ID COMMA expression_list  */
#line 1049 "yacc_sql.y"
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
#line 3028 "yacc_sql.cpp"
    break;

  case 112: /* expression: expression '+' expression  */
#line 1062 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3036 "yacc_sql.cpp"
    break;

  case 113: /* expression: expression '-' expression  */
#line 1065 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3044 "yacc_sql.cpp"
    break;

  case 114: /* expression: expression '*' expression  */
#line 1068 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3052 "yacc_sql.cpp"
    break;

  case 115: /* expression: expression '/' expression  */
#line 1071 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 3060 "yacc_sql.cpp"
    break;

  case 116: /* expression: LBRACE expression RBRACE  */
#line 1074 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3069 "yacc_sql.cpp"
    break;

  case 117: /* expression: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 1078 "yacc_sql.y"
                                                            {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3077 "yacc_sql.cpp"
    break;

  case 118: /* expression: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 1081 "yacc_sql.y"
                                                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COS_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3085 "yacc_sql.cpp"
    break;

  case 119: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 1084 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INN_PDT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3093 "yacc_sql.cpp"
    break;

  case 120: /* expression: '-' expression  */
#line 1087 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 3101 "yacc_sql.cpp"
    break;

  case 121: /* expression: value  */
#line 1090 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 3111 "yacc_sql.cpp"
    break;

  case 122: /* expression: rel_attr  */
#line 1095 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 3122 "yacc_sql.cpp"
    break;

  case 123: /* expression: '*'  */
#line 1101 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 3130 "yacc_sql.cpp"
    break;

  case 124: /* expression: ID DOT '*'  */
#line 1104 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
    }
#line 3138 "yacc_sql.cpp"
    break;

  case 125: /* expression: MAX LBRACE agg_fun_attr_list RBRACE  */
#line 1109 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("max", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3146 "yacc_sql.cpp"
    break;

  case 126: /* expression: MIN LBRACE agg_fun_attr_list RBRACE  */
#line 1112 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("min", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3154 "yacc_sql.cpp"
    break;

  case 127: /* expression: COUNT LBRACE agg_fun_attr_list RBRACE  */
#line 1115 "yacc_sql.y"
                                            {
      (yyval.expression) = create_aggregate_expression("count", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3162 "yacc_sql.cpp"
    break;

  case 128: /* expression: AVG LBRACE agg_fun_attr_list RBRACE  */
#line 1118 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("avg", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3170 "yacc_sql.cpp"
    break;

  case 129: /* expression: SUM LBRACE agg_fun_attr_list RBRACE  */
#line 1121 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("sum", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3178 "yacc_sql.cpp"
    break;

  case 130: /* agg_fun_attr_list: agg_fun_attr  */
#line 1140 "yacc_sql.y"
                 {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3186 "yacc_sql.cpp"
    break;

  case 131: /* agg_fun_attr_list: agg_fun_attr COMMA agg_fun_attr_list  */
#line 1143 "yacc_sql.y"
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
#line 3202 "yacc_sql.cpp"
    break;

  case 132: /* agg_fun_attr: %empty  */
#line 1157 "yacc_sql.y"
    {
      std::string null_string = "";
      (yyval.expression) = new UnboundFieldExpr(null_string, null_string);
      (yyval.expression)->set_name(null_string);
    }
#line 3212 "yacc_sql.cpp"
    break;

  case 133: /* agg_fun_attr: '*'  */
#line 1162 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 3220 "yacc_sql.cpp"
    break;

  case 134: /* agg_fun_attr: rel_attr  */
#line 1165 "yacc_sql.y"
               {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[0].rel_attr)->relation_name, (yyvsp[0].rel_attr)->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 3230 "yacc_sql.cpp"
    break;

  case 135: /* rel_attr: ID  */
#line 1173 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3240 "yacc_sql.cpp"
    break;

  case 136: /* rel_attr: ID DOT ID  */
#line 1178 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3252 "yacc_sql.cpp"
    break;

  case 137: /* relation: ID  */
#line 1188 "yacc_sql.y"
       {
      (yyval.relation) = new RelationSqlNode();
      (yyval.relation)->name = (yyvsp[0].string);
      (yyval.relation)->alias = "";
      free((yyvsp[0].string));
    }
#line 3263 "yacc_sql.cpp"
    break;

  case 138: /* relation: ID ID  */
#line 1194 "yacc_sql.y"
            {
      (yyval.relation) = new RelationSqlNode();
      (yyval.relation)->name = (yyvsp[-1].string);
      (yyval.relation)->alias = (yyvsp[0].string);
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3275 "yacc_sql.cpp"
    break;

  case 139: /* relation: ID AS ID  */
#line 1201 "yacc_sql.y"
               {
      (yyval.relation) = new RelationSqlNode();
      (yyval.relation)->name = (yyvsp[-2].string);
      (yyval.relation)->alias = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3287 "yacc_sql.cpp"
    break;

  case 140: /* rel_list: relation  */
#line 1210 "yacc_sql.y"
             {
      (yyval.relation_list) = new std::vector<RelationSqlNode>();
      (yyval.relation_list)->push_back(*(yyvsp[0].relation));
      delete((yyvsp[0].relation));
    }
#line 3297 "yacc_sql.cpp"
    break;

  case 141: /* rel_list: relation COMMA rel_list  */
#line 1215 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelationSqlNode>;
      }

      (yyval.relation_list)->insert((yyval.relation_list)->begin(), *(yyvsp[-2].relation));
      delete((yyvsp[-2].relation));
    }
#line 3312 "yacc_sql.cpp"
    break;

  case 142: /* join_list: %empty  */
#line 1229 "yacc_sql.y"
    {
      (yyval.join_tuple_list) = nullptr;
    }
#line 3320 "yacc_sql.cpp"
    break;

  case 143: /* join_list: join join_list  */
#line 1232 "yacc_sql.y"
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
#line 3339 "yacc_sql.cpp"
    break;

  case 144: /* join: INNER JOIN relation ON condition_list  */
#line 1248 "yacc_sql.y"
                                          {
      (yyval.join_tuple) = new std::tuple<std::string, std::vector<ConditionSqlNode> *>((yyvsp[-2].relation)->name, (yyvsp[0].condition_list));
      delete (yyvsp[-2].relation);
    }
#line 3348 "yacc_sql.cpp"
    break;

  case 145: /* where: %empty  */
#line 1255 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3356 "yacc_sql.cpp"
    break;

  case 146: /* where: WHERE condition_list  */
#line 1258 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3364 "yacc_sql.cpp"
    break;

  case 147: /* condition_list: %empty  */
#line 1264 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3372 "yacc_sql.cpp"
    break;

  case 148: /* condition_list: condition  */
#line 1267 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3382 "yacc_sql.cpp"
    break;

  case 149: /* condition_list: condition AND condition_list  */
#line 1272 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3392 "yacc_sql.cpp"
    break;

  case 150: /* condition_list: condition OR condition_list  */
#line 1277 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      ConditionSqlNode *tmp = new ConditionSqlNode;
      tmp->flag = 1;
      (yyval.condition_list)->emplace_back(*tmp);
      delete (yyvsp[-2].condition);
      delete tmp;
    }
#line 3406 "yacc_sql.cpp"
    break;

  case 151: /* condition: expression comp_op expression  */
#line 1338 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3418 "yacc_sql.cpp"
    break;

  case 152: /* condition: expression comp_op LBRACE select_stmt RBRACE  */
#line 1345 "yacc_sql.y"
                                                   {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-4].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 3432 "yacc_sql.cpp"
    break;

  case 153: /* condition: expression IN_T LBRACE select_stmt RBRACE  */
#line 1354 "yacc_sql.y"
                                                {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-4].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::IN;
    }
#line 3446 "yacc_sql.cpp"
    break;

  case 154: /* condition: expression NOT IN_T LBRACE select_stmt RBRACE  */
#line 1363 "yacc_sql.y"
                                                    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-5].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::NOT_IN;
    }
#line 3460 "yacc_sql.cpp"
    break;

  case 155: /* condition: expression IN_T LBRACE value value_list RBRACE  */
#line 1373 "yacc_sql.y"
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
#line 3481 "yacc_sql.cpp"
    break;

  case 156: /* condition: expression NOT IN_T LBRACE value value_list RBRACE  */
#line 1389 "yacc_sql.y"
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
#line 3502 "yacc_sql.cpp"
    break;

  case 157: /* condition: EXISTS_T LBRACE select_stmt RBRACE  */
#line 1405 "yacc_sql.y"
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
#line 3517 "yacc_sql.cpp"
    break;

  case 158: /* condition: NOT EXISTS_T LBRACE select_stmt RBRACE  */
#line 1415 "yacc_sql.y"
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
#line 3532 "yacc_sql.cpp"
    break;

  case 159: /* condition: LBRACE select_stmt RBRACE comp_op expression  */
#line 1425 "yacc_sql.y"
                                                   {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      UnboundSubqueryExpr *left_expr = new UnboundSubqueryExpr((yyvsp[-3].sql_node));
      (yyval.condition)->left_expr = left_expr;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3546 "yacc_sql.cpp"
    break;

  case 160: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 1434 "yacc_sql.y"
                                                                  {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = new UnboundSubqueryExpr((yyvsp[-5].sql_node));
      (yyval.condition)->right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 3559 "yacc_sql.cpp"
    break;

  case 161: /* comp_op: EQ  */
#line 1445 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3565 "yacc_sql.cpp"
    break;

  case 162: /* comp_op: LT  */
#line 1446 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3571 "yacc_sql.cpp"
    break;

  case 163: /* comp_op: GT  */
#line 1447 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3577 "yacc_sql.cpp"
    break;

  case 164: /* comp_op: LE  */
#line 1448 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3583 "yacc_sql.cpp"
    break;

  case 165: /* comp_op: GE  */
#line 1449 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3589 "yacc_sql.cpp"
    break;

  case 166: /* comp_op: NE  */
#line 1450 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3595 "yacc_sql.cpp"
    break;

  case 167: /* comp_op: LK  */
#line 1451 "yacc_sql.y"
         { (yyval.comp) = LIKE; }
#line 3601 "yacc_sql.cpp"
    break;

  case 168: /* comp_op: NLK  */
#line 1452 "yacc_sql.y"
          {(yyval.comp) = NOT_LIKE; }
#line 3607 "yacc_sql.cpp"
    break;

  case 169: /* comp_op: IS_T  */
#line 1453 "yacc_sql.y"
           { (yyval.comp) = IS; }
#line 3613 "yacc_sql.cpp"
    break;

  case 170: /* comp_op: IS_NOT_T  */
#line 1454 "yacc_sql.y"
               { (yyval.comp) = IS_NOT; }
#line 3619 "yacc_sql.cpp"
    break;

  case 171: /* group_by: %empty  */
#line 1460 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3627 "yacc_sql.cpp"
    break;

  case 172: /* group_by: GROUP BY expression_list  */
#line 1465 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3635 "yacc_sql.cpp"
    break;

  case 173: /* having: %empty  */
#line 1472 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3643 "yacc_sql.cpp"
    break;

  case 174: /* having: HAVING condition_list  */
#line 1475 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3651 "yacc_sql.cpp"
    break;

  case 175: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1481 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3665 "yacc_sql.cpp"
    break;

  case 176: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1494 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3674 "yacc_sql.cpp"
    break;

  case 177: /* set_variable_stmt: SET ID EQ value  */
#line 1502 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3686 "yacc_sql.cpp"
    break;


#line 3690 "yacc_sql.cpp"

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

#line 1514 "yacc_sql.y"

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
