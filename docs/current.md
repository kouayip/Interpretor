Program = Statement;
Statement =
  | If:{ "if" cond:ParenExpr then:Statement else:{ "else" then:Statement } }
  | While:{ "while" cond:ParenExpr then:Statement }
  | Block:{ "{" then:Statement* "}" }
  | Expr:{ then:Statement? ";" }
  ;
ParenExpr = "(" Expr ")";
Expr =
  | Assign:{ id:Id "=" val:Expr }
  | Test:{ lhs:Expr "<" rhs:Expr }
  | Sum:{ lhs:Expr "+" rhs:Term }
  | Diff:{ lhs:Expr "-" rhs:Term }
  ;
Term =
  | Id:{ 'a'..='z'+ }
  | Int:{ '0'..='9'+ }
  | Expr:ParenExpr
  ;