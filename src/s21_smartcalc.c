// "Copyright [2022] <Copyright Owner>"

#include "./s21_smartcalc.h"
int validator(char *str) {
  int ret_value = 0;
  char *buf = str;
  int i = 0, open = 0;
  int dot = 0;
  while (buf[i]) {
    if (buf[i] == '(')
      open++;
    else if (buf[i] == ')')
      open--;
    if (check_to_num(buf[i]) || check_to_sign(buf[i]) || buf[i] == '=') {
      ret_value = 1;
    } else if (check_to_trig(buf, i)) {
      ret_value = 1;
      i += check_to_trig(buf, i);
    } else {
      ret_value = 0;
    }
    if (!check_to_num(buf[i])) dot = 0;
    if ((buf[i] == '.') &&
        (!check_to_num(buf[i - 1]) || !check_to_num(buf[i + 1]) ||
         buf[i + 1] == '.' || dot == 1)) {
      ret_value = 0;
    }
    if (buf[i] == '.') dot = 1;
    if (strchr("+-*/^(", buf[i]) != NULL &&
        strchr("+-*/^)", buf[i + 1]) != NULL)
      ret_value = 0;
    if (open < 0) ret_value = 0;
    if (ret_value == 0) break;
    i++;
  }
  if (strchr("+=*/^", buf[0]) != NULL) ret_value = 0;
  if (open != 0) ret_value = 0;
  return ret_value;
}

char *remove_space(char *str) {
  char *buf = calloc(strlen(str) + 1, sizeof(char));
  int k = 0;
  int size = strlen(str);
  for (int i = 0; i < size; i++) {
    if (str[i] != ' ') {
      buf[k] = str[i];
      k++;
    }
  }
  char *un_min = unary_min(buf);
  free(buf);
  return un_min;
}

char *unary_min(char *str) {
  char *buf = calloc(strlen(str) + 10, sizeof(char));
  int k = 0;
  int size = strlen(str);
  for (int i = 0; i < size; i++) {
    if ((str[i] == '-' || str[i] == '+') && (i == 0 || str[i - 1] == '(')) {
      buf[k] = '0';
      buf[k + 1] = str[i];
      k += 2;
    } else {
      buf[k] = str[i];
      k++;
    }
  }
  return buf;
}

int check_to_num(char c) {
  return ((c > 47 && c < 58) || c == '.' || c == 'X');
}

int check_to_sign(char c) {
  int ret_value = 0;
  char *signs = " +-*/^()";
  for (int i = 0; i < 8; i++) {
    if (c == signs[i]) {
      ret_value = i;
      break;
    }
  }
  if (ret_value == 1 || ret_value == 2)
    ret_value = 1;
  else if (ret_value > 2 && ret_value < 5)
    ret_value = 2;
  else if (ret_value == 7 || ret_value == 6)
    ret_value = 3;
  else if (ret_value == 5)
    ret_value = 4;

  return ret_value;
}

int check_to_trig(char *buf, char i) {
  int ret_value = 0;
  char buf1[5] = {0};
  for (int k = 0; k < 5; k++) {
    buf1[k] = buf[i + k];
  }
  if (strncmp(buf1, "sin(", 4) == 0) ret_value = 2;
  if (strncmp(buf1, "cos(", 4) == 0) ret_value = 2;
  if (strncmp(buf1, "tan(", 4) == 0) ret_value = 2;
  if (strncmp(buf1, "log(", 4) == 0) ret_value = 2;
  if ((strncmp(buf1, "mod", 3) == 0) && i != 0 && check_to_num(buf[i - 1]) &&
      check_to_num(buf[i + 3]))
    ret_value = 2;
  if (strncmp(buf1, "ln(", 3) == 0) ret_value = 1;
  if (strncmp(buf1, "sqrt(", 5) == 0) ret_value = 3;
  if (strncmp(buf1, "asin(", 5) == 0) ret_value = 3;
  if (strncmp(buf1, "acos(", 5) == 0) ret_value = 3;
  if (strncmp(buf1, "atan(", 5) == 0) ret_value = 3;
  return ret_value;
}

N *parcer(char *str, N *new) {
  N *head = NULL;
  char *buf = str;
  int i = 0;
  while (buf[i]) {
    if (check_to_num(buf[i])) {
      char numb[255] = {0};
      int k = 0;
      while (check_to_num(buf[i])) {
        numb[k] = buf[i];
        i++, k++;
      }
      push(&head, atof(numb), 0);
    }
    if (check_to_sign(buf[i])) {
      push(&head, buf[i], check_to_sign(buf[i]));
    }
    if (check_to_trig(buf, i) > 0) {
      if (check_to_trig(buf, i) == 2) {
        if (buf[i] != 'm')
          push(&head, buf[i], 6);
        else
          push(&head, buf[i], 2);
        i += 2;
      } else if (check_to_trig(buf, i) == 1) {
        push(&head, '6', 6);
      } else {
        int val = 0;
        if (buf[i] == 'a') {
          if (buf[i + 1] == 's') val = '1';
          if (buf[i + 1] == 'c') val = '2';
          if (buf[i + 1] == 't') val = '3';
        } else if (buf[i] == 's') {
          val = '4';
        } else if (buf[i] == 'l') {
          val = '5';
        }
        push(&head, val, 6);
        i += 3;
      }
    }
    i++;
  }
  upend_stack(&head, &new);
  return new;
}

N *RPN(N *stack) {
  N *ready = NULL;
  N *new = NULL;
  N *oper = NULL;
  while (stack) {
    N *tmp = pop1(&stack);
    if (tmp->priority == 0) {
      push(&ready, tmp->value, 0);
    } else if (tmp->priority == 3) {
      if (tmp->value == ')') {
        int skobka = 0;
        while (skobka != '(') {
          N *skk = pop1(&oper);
          skobka = skk->value;
          if (skk->priority != 3) push(&ready, skk->value, skk->priority);
          free(skk);
        }
      } else {
        push(&oper, tmp->value, tmp->priority);
      }
    } else if (oper == NULL || (tmp->priority > peek(&oper)->priority) ||
               peek(&oper)->priority == 3) {
      push(&oper, tmp->value, tmp->priority);
    } else if (tmp->priority <= peek(&oper)->priority) {
      while (tmp->priority <= peek(&oper)->priority &&
             peek(&oper)->priority != 3) {
        N *tmp2 = pop1(&oper);
        push(&ready, tmp2->value, tmp2->priority);
        free(tmp2);
        if (oper == NULL) break;
      }
      push(&oper, tmp->value, tmp->priority);
    }
    free(tmp);
  }
  while (oper) {
    N *tmp3 = pop1(&oper);
    push(&ready, tmp3->value, tmp3->priority);
    free(tmp3);
  }
  upend_stack(&ready, &new);
  return new;
}

double calc(N *stack) {
  N *ready = NULL;
  while (stack) {
    N *tmp = pop1(&stack);
    if (tmp->priority != 0) {
      N *value = pop1(&ready);
      if (strchr("+-*/^m", tmp->value) != NULL) {
        N *value_2 = pop1(&ready);
        if (tmp->value == '+') {
          push(&ready, value->value + value_2->value, 0);
        } else if (tmp->value == '-') {
          push(&ready, value_2->value - value->value, 0);
        } else if (tmp->value == '*') {
          push(&ready, value->value * value_2->value, 0);
        } else if (tmp->value == '/') {
          push(&ready, value_2->value / value->value, 0);
        } else if (tmp->value == '^') {
          push(&ready, powf(value_2->value, value->value), 0);
        } else if (tmp->value == 'm') {
          push(&ready, fmod(value_2->value, value->value), 0);
        }
        free(value_2);
      } else if (tmp->value == 's') {
        push(&ready, sin(value->value), 0);
      } else if (tmp->value == 'c') {
        push(&ready, cos(value->value), 0);
      } else if (tmp->value == 't') {
        push(&ready, tan(value->value), 0);
      } else if (tmp->value == 'l') {
        push(&ready, log(value->value), 0);
      } else if (tmp->value == '1') {
        push(&ready, asin(value->value), 0);
      } else if (tmp->value == '2') {
        push(&ready, acos(value->value), 0);
      } else if (tmp->value == '3') {
        push(&ready, atan(value->value), 0);
      } else if (tmp->value == '4') {
        push(&ready, sqrt(value->value), 0);
      } else if (tmp->value == '5') {
        push(&ready, log(value->value), 0);
      } else if (tmp->value == '6') {
        push(&ready, log10f(value->value), 0);
      }
      free(value);
    } else {
      push(&ready, tmp->value, tmp->priority);
    }
    free(tmp);
  }
  N *tmp = pop1(&ready);
  double result = tmp->value;
  free(tmp);
  return result;
}

double calculate(char *str) {
  N *stack = NULL;
  double result = calc(RPN(parcer(str, stack)));
  return result;
}

void push(N **head, double value, int prior) {
  N *tmp = malloc(sizeof(N));
  if (tmp == NULL) {
    exit(1);
  }
  tmp->next = *head;
  tmp->value = value;
  tmp->priority = prior;
  *head = tmp;
}

N *pop1(N **head) {
  N *out;
  if ((*head) == NULL) {
    exit(2);
  }
  out = *head;
  *head = (*head)->next;
  return out;
}

N *peek(N **head) {
  if ((*head) == NULL) {
    exit(2);
  }
  return *head;
}

void upend_stack(N **head, N **new) {
  while (*head) {
    N *tmp = pop1(head);
    push(new, tmp->value, tmp->priority);
    free(tmp);
  }
}
