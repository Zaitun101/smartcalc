#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct N {
  double value;
  int priority;
  struct N *next;
} N;

N *RPN(N *stack);
N *peek(N **head);
N *pop1(N **head);
double calculate(char *str);
double calc(N *stack);
char *unary_min(char *str);
void upend_stack(N **head, N **new_stack);
void push(N **head, double value, int prior);
int validator(char *str);
N *parcer(char *str, N *new_stack);
int check_to_num(char c);
int check_to_sign(char c);
int check_to_trig(char *buf, char i);
char *remove_space(char *str);
