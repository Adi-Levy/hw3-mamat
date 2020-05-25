#include "F2.h"
int K=0;
int add(int x, int y){
  K++;
  return x+y;
}
int sub(int x, int y){
  K++;
  return x-y;
}
int mult(int x, int y){
  K++;
  return x*y;
}
