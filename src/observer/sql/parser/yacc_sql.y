
%{

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

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
%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }
%parse-param { SqlCommandFlag flag }

//标识tokens
%token  SEMICOLON
        BY
        CREATE
        DROP
        GROUP
        HAVING
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        VECTOR_T
        DATE_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        STORAGE
        FORMAT
        EQ
        LT
        GT
        LE
        GE
        NE
        LK
        NLK
        MAX
        MIN
        COUNT
        AVG
        SUM
        INNER
        JOIN
        UNIQUE
        LBRACKET
        RBRACKET
        L2_DISTANCE
        COSINE_DISTANCE
        INNER_PRODUCT
        EXISTS_T
        NOT
        IN_T


/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                            sql_node;
  ConditionSqlNode *                         condition;
  Value *                                    value;
  enum CompOp                                comp;
  RelAttrSqlNode *                           rel_attr;
  SetClauseSqlNode *                         set_clause;
  std::vector<AttrInfoSqlNode> *             attr_infos;
  AttrInfoSqlNode *                          attr_info;
  Expression *                               expression;
  std::vector<std::unique_ptr<Expression>> * expression_list;
  // std::vector<Expression *> *                agg_fun_attr_list;
  std::vector<Value> *                       value_list;
  std::vector<ConditionSqlNode> *            condition_list;
  std::tuple<std::vector<std::string> *, std::vector<std::vector<ConditionSqlNode> *> *> *  join_tuple_list;
  std::tuple<std::string, std::vector<ConditionSqlNode> *> *  join_tuple;
  std::vector<RelAttrSqlNode> *              rel_attr_list;
  std::vector<std::string> *                 relation_list;
  std::vector<SetClauseSqlNode> *            set_clause_list;
  std::vector<float> *                       vector_elem_list;
  char *                                     string;
  int                                        number;
  float                                      floats;
  char *                                     date;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
%token <string> DATE
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <number>              number
%type <string>              relation
/* %type <condition>           subquery */
%type <comp>                comp_op
%type <rel_attr>            rel_attr
%type <expression>          agg_fun_attr
%type <expression>          agg_fun_attr_list
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <floats>              vector_elem
%type <vector_elem_list>    vector_value_list
%type <condition_list>      where
%type <condition_list>      having
%type <join_tuple_list>     join_list
%type <join_tuple>          join
%type <condition_list>      condition_list
%type <string>              storage_format
%type <relation_list>       rel_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <expression_list>     group_by
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
%type <set_clause>          set_clause
%type <set_clause_list>     set_clause_list
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%nonassoc EQ LT GT LE GE NE
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE rel_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      create_index.unique = false;
      if ($7 != nullptr) {
        create_index.attributes.swap(*$7);
        delete $7;
      }
      free($3);
      free($5);
    }
    | CREATE UNIQUE INDEX ID ON ID LBRACE rel_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      create_index.unique = true;
      if ($8 != nullptr) {
        create_index.attributes.swap(*$8);
        delete $8;
      }
      free($4);
      free($6);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
      if ($8 != nullptr) {
        create_table.storage_format = $8;
        free($8);
      }
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE 
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      free($1);
    }
    | ID type
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      if ((AttrType)$2 == AttrType::DATES) {
        $$->length = 8;
      } else if ((AttrType)$2 == AttrType::CHARS) {
        $$->length = 32;
      } else {
        $$->length = 4;
      }
      free($1);
    }
    ;
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$ = static_cast<int>(AttrType::INTS); }
    | STRING_T { $$ = static_cast<int>(AttrType::CHARS); }
    | FLOAT_T  { $$ = static_cast<int>(AttrType::FLOATS); }
    | VECTOR_T { $$ = static_cast<int>(AttrType::VECTORS); }
    | DATE_T   { $$ = static_cast<int>(AttrType::DATES); }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE 
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($7 != nullptr) {
        $$->insertion.values.swap(*$7);
        delete $7;
      }
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
      free($3);
    }
    ;

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
      free($1);
    }
    |DATE {
      char *tmp = common::substr($1,1,strlen($1)-2);
      if (!is_valid_date(tmp)) {
        $$ = new Value(AttrType::UNDEFINED, nullptr);
      } else {
        struct tm tm; bzero(&tm, sizeof(tm));
        strptime(tmp, "%Y-%m-%d", &tm);
        $$ = new Value(mktime(&tm));
      }
      free(tmp);
      free($1);
    }
    | LBRACKET vector_elem vector_value_list RBRACKET {
      vector<float>* cur = $3;
      if($3 == nullptr){
        cur = new vector<float>;
      }
      cur->push_back((float)$2);
      std::reverse(cur->begin(), cur->end());
      $$ = new Value(cur->data(), cur->size());
      delete cur;
    }
    ;
vector_elem:
    NUMBER {
      $$ = (float)$1;
      @$ = @1;
    }
    |FLOAT {
      $$ = (float)$1;
      @$ = @1;
    }
    ;
vector_value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA vector_elem vector_value_list{
      $$ = $3;
      if($$ == nullptr){
        $$ = new vector<float>;
      }
      $$->push_back($2);
    };
storage_format:
    /* empty */
    {
      $$ = nullptr;
    }
    | STORAGE FORMAT EQ ID
    {
      $$ = $4;
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
  UPDATE ID SET set_clause_list where 
  {
    $$ = new ParsedSqlNode(SCF_UPDATE);
    $$->update.relation_name = $2;
    if ($4 != nullptr) {
      $$->update.set_clauses.swap(*$4);
      delete $4;
    }
    if ($5 != nullptr) {
      $$->update.conditions.swap(*$5);
      delete $5;
    }
    free($2);
  }
  ;

set_clause_list:
  set_clause {
    $$ = new std::vector<SetClauseSqlNode>;
    $$->emplace_back(*$1);
    delete $1;
  }
  | set_clause COMMA set_clause_list
  {
    if ($3 != nullptr) {
      $$ = $3;
    } else {
      $$ = new std::vector<SetClauseSqlNode>;
    }
    $$->emplace($$->begin(), *$1);
    delete $1;
  }
  ;

set_clause:
  ID EQ value {
    $$ = new SetClauseSqlNode;
    $$->attribute_name = $1;
    $$->value = *$3;
    free($1);
    delete $3;
  }
  ;
select_stmt:        /*  select 语句的语法解析树*/
    SELECT expression_list FROM rel_list join_list where group_by having
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.expressions.swap(*$2);
        delete $2;
      }

      if ($4 != nullptr) {
        $$->selection.relations.swap(*$4);
        delete $4;
      }

      if ($5 != nullptr) {
        $$->selection.join_relations.swap(*(std::get<0>(*$5)));
        $$->selection.join_conditions.swap(*(std::get<1>(*$5)));
        delete std::get<0>(*$5);
        delete std::get<1>(*$5);
        std::reverse($$->selection.join_relations.begin(), $$->selection.join_relations.end());
        std::reverse($$->selection.join_conditions.begin(), $$->selection.join_conditions.end());
        delete $5;
      }

      if ($6 != nullptr) {
        $$->selection.conditions.swap(*$6);
        delete $6;
      }

      if ($7 != nullptr) {
        $$->selection.group_by.swap(*$7);
        delete $7;
      }

      // 处理having，having和where不能共存，先不考虑出现这种测试用例
      if ($8 != nullptr) {
        $$->selection.having.swap(*$8);
        delete $8;
      }
    }
    ;
calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression
    {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      $$->emplace($$->begin(), $1);
    }
    ;
expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | L2_DISTANCE LBRACE expression COMMA expression RBRACE {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::L2_DIS, $3, $5, sql_string, &@$);
    }
    | COSINE_DISTANCE LBRACE expression COMMA expression RBRACE {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::COS_DIS, $3, $5, sql_string, &@$);
    }
    | INNER_PRODUCT LBRACE expression COMMA expression RBRACE {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::INN_PDT, $3, $5, sql_string, &@$);
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | rel_attr {
      RelAttrSqlNode *node = $1;
      $$ = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | '*' {
      $$ = new StarExpr();
    }
    // your code here
    // 聚合函数
    | MAX LBRACE agg_fun_attr_list RBRACE {
      $$ = create_aggregate_expression("max", $3, sql_string, &@$);
    }
    | MIN LBRACE agg_fun_attr_list RBRACE {
      $$ = create_aggregate_expression("min", $3, sql_string, &@$);
    }
    | COUNT LBRACE agg_fun_attr_list RBRACE {
      $$ = create_aggregate_expression("count", $3, sql_string, &@$);
    }
    | AVG LBRACE agg_fun_attr_list RBRACE {
      $$ = create_aggregate_expression("avg", $3, sql_string, &@$);
    }
    | SUM LBRACE agg_fun_attr_list RBRACE {
      $$ = create_aggregate_expression("sum", $3, sql_string, &@$);
    }
    ;
agg_fun_attr_list:
    agg_fun_attr {
      $$ = $1;
    }
    | agg_fun_attr COMMA agg_fun_attr_list {
      $$ = nullptr;
      // 到这里肯定有问题
      if ($3) {
        delete $3;
      }
      if ($1) {
        delete $1;
      }
      yyerror(&@1, NULL, sql_result, NULL, SCF_ERROR_AGGREGATION, "aggregation func has too many fields");
    }
    ;
agg_fun_attr:
    /* empty */
    {
      std::string null_string = "";
      $$ = new UnboundFieldExpr(null_string, null_string);
      $$->set_name(null_string);
    }
    | '*' {
      $$ = new StarExpr();
    }
    | rel_attr {
      $$ = new UnboundFieldExpr($1->relation_name, $1->attribute_name);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    ;

rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    ;

relation:
    ID {
      $$ = $1;
    }
    ;
rel_list:
    relation {
      $$ = new std::vector<std::string>();
      $$->push_back($1);
      free($1);
    }
    | relation COMMA rel_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::string>;
      }

      $$->insert($$->begin(), $1);
      free($1);
    }
    ;

join_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | join join_list {
      if ($2 == nullptr) {
        std::vector<std::string> *vs = new std::vector<std::string>;
        std::vector<std::vector<ConditionSqlNode> *> *vvc = new std::vector<std::vector<ConditionSqlNode> *>;
        $$ = new std::tuple<std::vector<std::string> *, std::vector<std::vector<ConditionSqlNode> *> *>(vs, vvc);
      } else {
        $$ = $2;
      }
      std::vector<std::string> *vs = std::get<0>(*$$);
      std::vector<std::vector<ConditionSqlNode> *> *vvc = std::get<1>(*$$);
      vs->emplace_back(std::get<0>(*$1));
      vvc->emplace_back(std::get<1>(*$1));
      delete $1;
    }

join:
    INNER JOIN relation ON condition_list {
      $$ = new std::tuple<std::string, std::vector<ConditionSqlNode> *>($3, $5);
      free($3);
    }

where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    /* | WHERE subquery {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$2);
      delete $2;
    } */
    ;

/* subquery:
    expression IN_T LBRACE select_stmt RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->is_subquery = 1;
      $$->comp = CompOp::IN;
      $$->expr = $1;
      $$->sub_sqlnode = $4;
    }
    | expression NOT IN_T LBRACE select_stmt RBRACE {
      $$ = new ConditionSqlNode;
      $$->is_subquery = 1;
      $$->comp = CompOp::NOT_IN;
      $$->expr = $1;
      $$->sub_sqlnode = $5;
    }
    | EXISTS_T LBRACE select_stmt RBRACE {
      $$ = new ConditionSqlNode;
      $$->is_subquery = 1;
      $$->comp = CompOp::EXISTS;
      $$->sub_sqlnode = $3;
    }
    | NOT EXISTS_T LBRACE select_stmt RBRACE {
      $$ = new ConditionSqlNode;
      $$->is_subquery = 1;
      $$->comp = CompOp::NOT_EXISTS;
      $$->sub_sqlnode = $4;
    }
    | expression comp_op LBRACE select_stmt RBRACE {
      $$ = new ConditionSqlNode;
      $$->is_subquery = 1;
      $$->comp = $2;
      $$->expr = $1;
      $$->sub_sqlnode = $4;
    }
    | LBRACE select_stmt RBRACE comp_op expression {
      $$ = new ConditionSqlNode;
      $$->is_subquery = 1;
      $$->comp = $4;
      $$->expr = $5;
      $$->sub_sqlnode = $2;
    }
    ; */

condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
condition:
    /* rel_attr comp_op value
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op value 
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | rel_attr comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | */
    expression comp_op expression// 6. where语句中会出现表达式
    {
      $$ = new ConditionSqlNode;
      $$->neither = 1;
      $$->left_expr = $1;
      $$->right_expr = $3;
      $$->comp = $2;
    }
    | expression IN_T LBRACE select_stmt RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->is_subquery = 1;
      $$->comp = CompOp::IN;
      $$->expr = $1;
      $$->sub_sqlnode = $4;
    }
    | expression NOT IN_T LBRACE select_stmt RBRACE {
      $$ = new ConditionSqlNode;
      $$->is_subquery = 1;
      $$->comp = CompOp::NOT_IN;
      $$->expr = $1;
      $$->sub_sqlnode = $5;
    }
    | expression IN_T LBRACE value value_list RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->is_subquery = 1;
      $$->comp = CompOp::IN;
      $$->expr = $1;
      if ($5 != nullptr) {
        $$->values.swap(*$5);
        delete $5;
      }
      $$->values.emplace_back(*$4);
      delete $4;
      $$->sub_sqlnode = nullptr;
    }
    | expression NOT IN_T LBRACE value value_list RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->is_subquery = 1;
      $$->comp = CompOp::NOT_IN;
      $$->expr = $1;
      if ($6 != nullptr) {
        $$->values.swap(*$6);
        delete $6;
      }
      $$->values.emplace_back(*$5);
      delete $5;
      $$->sub_sqlnode = nullptr;
    }
    | EXISTS_T LBRACE select_stmt RBRACE {
      $$ = new ConditionSqlNode;
      $$->is_subquery = 1;
      $$->comp = CompOp::EXISTS;
      $$->sub_sqlnode = $3;
    }
    | NOT EXISTS_T LBRACE select_stmt RBRACE {
      $$ = new ConditionSqlNode;
      $$->is_subquery = 1;
      $$->comp = CompOp::NOT_EXISTS;
      $$->sub_sqlnode = $4;
    }
    | expression comp_op LBRACE select_stmt RBRACE {
      $$ = new ConditionSqlNode;
      $$->is_subquery = 1;
      $$->comp = $2;
      $$->expr = $1;
      $$->sub_sqlnode = $4;
    }
    | LBRACE select_stmt RBRACE comp_op expression {
      $$ = new ConditionSqlNode;
      $$->is_subquery = 1;
      $$->comp = $4;
      $$->expr = $5;
      $$->sub_sqlnode = $2;
      $$->left_is_expr = 0;
    }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LK { $$ = LIKE; }
    | NLK {$$ = NOT_LIKE; }
    ;

// your code here
group_by:
    /* empty */
    {
      $$ = nullptr;
    }
    /* group by后面可以是表达式 */
    | GROUP BY expression_list
    {
      $$ = $3;
    }
    ;

having:
    /* empty */
    {
      $$ = nullptr;
    }
    | HAVING condition_list {
      $$ = $2;
    }

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
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
