# smartcalc
Smart calculator to solve math problems, build functions and count credit

Backend written on C, GUI - qt6, C++;

Calcutator get a string, after clic to '=' send this string to validator, if exxpression is correct, I parse this string to lexeme, and push them to stack.
Then make correct order of lexemes (to reverse polish notation) only then get an answer and send it to GUI

If exxpression  uncorrect you'll get a warning


To start smart calculator you should dounload it, then write in terminal 'make install' and app will installed in build_calc folder.
And with command 'make open' you can open it and use.
