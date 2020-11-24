17 + 3

factor = (expr)

expr = term { (+|-) term }

term = integer

interger = digit+

digit = 0|1|2|3|4|5|6|7|8|9

Test memory: 

valgrind --leak-check=full ./main