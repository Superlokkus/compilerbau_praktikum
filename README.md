PL/0 Grammar is

```EBNF
<Morphem>       ::= <Sonderzeichen>|<Zahl>|<Bezeichner>
<Sonderzeichen> ::= + | - | * | / | , | . | ; | ( | ) | ? | ! | # | = | < | <= | > | >= | :=
<Zahl>          ::= Zi {<Zi>}
<Zi>            ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
<Bezeichner>    ::=Bu {BuZi}
<BuZi>          ::= Bu | Zi
<Bu>            ::= A | B | ... | Z | a | b | ... | z
```