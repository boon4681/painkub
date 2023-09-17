kub = ws statement ws

statement = stmt (stmt ws)*
stmt = declaration / function_call / if_stmt / while_stmt / for_stmt / assign / return_stmt

assign = ident WS [+\-*\/]?"=" WS (literal / ident / expression)

if_stmt = "if" WS condition ws block
while_stmt = "while" WS condition ws block
for_stmt = "for" WS ident WS "in" WS range_expr ws block
return_stmt = "return" " " expression
function_call = ident "(" ws func_params ws ")"
func_params = (literal / ident) (ws "," ws (literal / ident))*

condition = disjunction
disjunction = conjunction (ws "or" ws conjunction)*
conjunction = comparison (ws "and" ws comparison)*

comparison = expression ws comparison_opr ws expression

comparison_opr = ">" / "<" / "==" / ">=" / "<="

block = "{" ws statement ws "}"

expression = additive_expr
range_expr = additive_expr ".." additive_expr
parenthesized_expr = "(" ws expression ws ")"

additive_expr = multiplicative_expr (ws additive_opr ws multiplicative_expr)*

multiplicative_expr = primary_expr (ws multiplicative_opr ws primary_expr)*

primary_expr = parenthesized_expr / literal / ident

additive_opr = "+" / "-"
multiplicative_opr = "*" / "/"

declaration = function_declaration / variable_declaration

function_declaration = "fun" WS ident ws "(" ws ws ")" ws block
variable_declaration = "let" WS ident ws "=" ws literal / "let" WS ident ws

literal = number / string

number = [+-]? (int / float)

int = [1-9][0-9]+ / [0-9]

float = int "." [0-9]+

string = double_quote_string / single_quote_string
single_quote_string = "'" (escape_string / single_quote_char_string)* "'"
single_quote_char_string = [^\\\t\r\n\"\']

double_quote_string = '"' (escape_string / double_quote_char_string)* '"'
double_quote_char_string = [^\\\t\r\n\"\']
escape_string = '\\' [tbrn"'\\]

ident = [a-zA-Z_][a-zA-Z_0-9]*

WS "whitespace"
  = [ \t\n\r]+
ws "whitespace"
  = [ \t\n\r]*