# TabelaVerdade-C
Programa que dá a tabela-verdade de uma expressão booleana, escrito em C:

Obs: o programa ainda não conta com o módulo que verifica se um expressão é válida ou não. Se uma expressão inválida for digitada, o programa provavelmente se comportará de forma inesperada.

=Os caracteres usados para representar os operadores booleanos são (além dos parênteses):
'.' : conjunção;
'+' : disjunção inclusiva;
'>' : condicional;
'=' : bicondicional;
'#' : disjunção exclusiva.

Exemplos de expressões convertidas à sintaxe do programa (retirados do livro Lógica e Álgebra de Boole, de Jacob Daghlian):

![Exemplo 1](https://i.imgur.com/OQCdBYy.png)

=p+!r>q.!r

![Exemplo 2](https://i.imgur.com/5gXnmPI.png)
=!(p.q)+!(q=p)
