#include "rv_declarations.h"

/*** global declarations side 0: ***/
typedef int  (*rvs0_rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr)(void  *rv_arg_0, void  *rv_arg_1);
float  rvs0_rv_mult(float  x, float  y);
float  rvs0_rv_div(float  x, float  y);
int  rvs0_rv_mod(int  x, int  y);
typedef int  rvs0_pid_t;
typedef unsigned int  rvs0_size_t;
typedef unsigned char  rvs0_u_char;
typedef unsigned long  rvs0_ulong;
typedef unsigned short  rvs0_ushort;
typedef unsigned int  rvs0_uint;
typedef unsigned int  rvs0_off_t;
typedef unsigned int  rvs0_mode_t;
typedef unsigned int  rvs0_u_int;
typedef int  rvs0_uid_t;
void  rvs0_exit(int  status);
char  *rvs0_getenv(char  *name);
int  rvs0_system(char  *string);
void  rvs0_abort();
void  *calloc(rvs0_size_t  nmemb, rvs0_size_t  size);
void  *malloc(rvs0_size_t  size);
void  free(void  *ptr);
void  *realloc(void  *ptr, rvs0_size_t  size);
int  rvs0_atoi(char  *nptr);
long  rvs0_atol(char  *nptr);
long long  rvs0_atoll(char  *nptr);
long long  rvs0_atoq(char  *nptr);
float  rvs0_atof(char  *nptr);
int  rvs0_rand();
void  rvs0_srand(unsigned int  seed);
long  rvs0_random();
void  rvs0_srandom(unsigned int  seed);
char  *rvs0_initstate(unsigned int  seed, char  *state, rvs0_size_t  n);
char  *rvs0_setstate(char  *state);
int  rvs0_mkstemp(char  *temp);
void  rvs0_qsort(void  *base, rvs0_size_t  num, rvs0_size_t  width, rvs0_rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr  fncompare);
void  rvs0_myempty();
int  rvs0_F(int  *n);
int  rvs0_M(int  n);
int  rvs0_F(int  *n);
int  chk0_G(int  n);
int  rvs0_M(int  n);
int  rvs0_main();
int  rvs0_F(int  *n);
unsigned char  rvs0_Loop_main_for1(int  *rvp_i, int  *rvp_out, int  **rvp_p, int  *rvp_rvretval);
unsigned char  rvs0_Loop_main_for2(int  *rvp_i, int  *rvp_rvretval);
void  __CPROVER_assume(_Bool  rv_arg_6);

/*** global declarations side 1: ***/
typedef int  (*rvs1_rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr)(void  *rv_arg_2, void  *rv_arg_3);
float  rvs1_rv_mult(float  x, float  y);
float  rvs1_rv_div(float  x, float  y);
int  rvs1_rv_mod(int  x, int  y);
typedef int  rvs1_pid_t;
typedef unsigned int  rvs1_size_t;
typedef unsigned char  rvs1_u_char;
typedef unsigned long  rvs1_ulong;
typedef unsigned short  rvs1_ushort;
typedef unsigned int  rvs1_uint;
typedef unsigned int  rvs1_off_t;
typedef unsigned int  rvs1_mode_t;
typedef unsigned int  rvs1_u_int;
typedef int  rvs1_uid_t;
void  rvs1_exit(int  status);
char  *rvs1_getenv(char  *name);
int  rvs1_system(char  *string);
void  rvs1_abort();
void  *calloc(rvs1_size_t  nmemb, rvs1_size_t  size);
void  *malloc(rvs1_size_t  size);
void  free(void  *ptr);
void  *realloc(void  *ptr, rvs1_size_t  size);
int  rvs1_atoi(char  *nptr);
long  rvs1_atol(char  *nptr);
long long  rvs1_atoll(char  *nptr);
long long  rvs1_atoq(char  *nptr);
float  rvs1_atof(char  *nptr);
int  rvs1_rand();
void  rvs1_srand(unsigned int  seed);
long  rvs1_random();
void  rvs1_srandom(unsigned int  seed);
char  *rvs1_initstate(unsigned int  seed, char  *state, rvs1_size_t  n);
char  *rvs1_setstate(char  *state);
int  rvs1_mkstemp(char  *temp);
void  rvs1_qsort(void  *base, rvs1_size_t  num, rvs1_size_t  width, rvs1_rvt_FuncPtrSubst_int__const_void_ptr_const_void_ptr  fncompare);
void  rvs1_myempty();
int  rvs1_F(int  *n);
int  rvs1_M(int  n);
int  rvs1_F(int  *n);
int  chk1_G(int  n);
void  rvs1_plusone(int  *n);
int  rvs1_M(int  n);
void  rvs1_H(int  i);
int  rvs1_main();
int  rvs1_F(int  *n);
unsigned char  rvs1_Loop_main_for1(int  *rvp_i, int  *rvp_out, int  **rvp_p, int  *rvp_rvretval);
unsigned char  rvs1_Loop_main_for2(int  *rvp_i, int  *rvp_rvretval);
void  __CPROVER_assume(_Bool  rv_arg_7);

/*** end of global declarations side 1: ***/
/*** end of global declarations. ***/

/*** Functions side 0: ***/
int  chk0_G(int  n)
{
  int  *p = (int *) (malloc(sizeof(int ) ));

  *p = n - 1;
  return rvs0_F(p);
}


/*** Functions side 1: ***/
int  chk1_G(int  n)
{
  int  *p = (int *) (malloc(sizeof(int ) ));
  int  t0;
  int  *t1;
  int  **a;

  t1 = &t0;
  a = &t1;
  *a = p;
  *p = n - 1;
  return rvs1_F(*a);
}


/* Implementations of the uninterpreted functions: */

  /* Declarations of the CBMC uninterpreted functions */
int  __CPROVER_uninterpreted_n(int );
int  __CPROVER_uninterpreted_retval(int );

  /* CBMC-UF side 0: */ 
int  rvs0_F(int  *n)
{
  int  retval;

  /* Declarations: */
  int  rv_D0_0;	/* Generated by:  gen_side0_cbmc_uf(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/

  /* Protecting pointers from being NULL-dereferenced: */
  if (n== 0) {
  n = &rv_D0_0;	/* Generated by:  gen_side0_cbmc_uf(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  }

  /* Each output is assigned a UF:*/
  *n= __CPROVER_uninterpreted_n(*n);
  retval= __CPROVER_uninterpreted_retval(*n);

  return retval;
}


  /* CBMC-UF side 1: */ 
int  rvs1_F(int  *n)
{
  int  retval;

  /* Declarations: */
  int  rv_D1_0;	/* Generated by:  gen_side1_cbmc_uf(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc/ rv_temps.cpp:327*/

  /* Protecting pointers from being NULL-dereferenced: */
  if (n== 0) {
  n = &rv_D1_0;	/* Generated by:  gen_side1_cbmc_uf(608)/ protect_pointer [op=9](613)(379)(608)/ protect_pointer [op=9](613)(379)(608)(613)(379)(601)(326)/ gen_safe_alloc/ rv_temps.cpp:332*/
  }

  /* Each output is assigned a UF:*/
  *n= __CPROVER_uninterpreted_n(*n);
  retval= __CPROVER_uninterpreted_retval(*n);

  return retval;
}

  /* now starting main */

int main()
{
  _Bool equal = 1;
  /* Declarations: */
  int  retval0;	/* Generated by:  gen_retval_declarations/ rv_temps.cpp:269*/
  int  retval1;	/* Generated by:  gen_retval_declarations/ rv_temps.cpp:269*/
  int  rvs0_n;	/* Generated by:  gen_arg_decl(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/
  int  rvs1_n;	/* Generated by:  gen_arg_decl(107)/ gen_decl_low(148)(107)/ gen_decl_low(148)/ rv_temps.cpp:274*/

  /* output: */
  /* Allocations for side 0: */
  /* Allocations for side 1: */

  /* Assume input args are equal: */ 
  rvs0_n = rvs1_n;	/* Generated by:  gen_args_equality(608)(613)(379)(293)/ rv_temps.cpp:362*/

  /* run each side's main() */
  retval0 = chk0_G(rvs0_n);
  retval1 = chk1_G(rvs1_n);
  /* Assertions: */

  /* Compare return values: */ 
  assert( retval0 == retval1 );	/* Generated by:  gen_main(608)(613)(379)(309)/ rv_temps.cpp:352*/

  /* Compare output args: */ 


  return 0;
}
