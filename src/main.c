#include <stdio.h>
#include <string.h>

#include "s21_sprintf.h"

#include "../libs/s21_string.h"
// #define SZ 50
// #define T_S_W_ZERO "bytecode\0why"
// #define T_STR "Hello world!"
// #define T_SH_STR "Hello"
// #define T_NO_SYMB "GEn_5"
// #define T_STR_END "world"
// #define NOT_EXIST '['
// #define EXIST 'w'
// #define tk_1  ",.!?"
// #define tk_2  ",.o!?"
// #define tk_3  ",.t!?o"
// #define tk_4  "t,.!?"

int main(void) {

  //   // char *str = "%050.3s hello\n";works
  //   // char *str = "%*050.3s hello\n";not works as should be
  //   // char *str = "%#.3*s hello\n";
  //   // char *str = "%+- #*033.3ds hello\n";not works as should be
  //   // char *str = "%+- #0*33.3ds hello\n";
  //   char *str = "%+- #0*.3llds he%+- 0# dllo\n";
  //   char *str_1 = "";
  char *str_3 = "%klsdskjsdkjsd %.10*e sjdsj%d";
  char buffer[100] = {0};
  int res = 0;
  //   res = sprintf(buffer, str, 10, 3);
  //   printf("result = %d\nstr = %s\n\n", res, buffer);

  //   res = sprintf(buffer, str_1, 10, 3);
  //   printf("result = %d\nstr = %s\n\n", res, buffer);

  res = sprintf(buffer, str_3, 10.0 / 3);
  printf("result = %d\nstr = %s\n\n", res, buffer);

  char *c_string_0 =
      "hello     %#1 3.8500d\n world% #983.837364s from "
      "%*ssprintf%#- *s\nwoops%#+ 3.*d\nnowidth: %+0#- 123 .5d\nwith width = "
      "%+0#- 123.5s";

  char *c_string_1 =
      "lexemme 1 - %%flags only : %+-# 0d\nlexemme 2 -%d percents : %%\n";

  char *c_string_2 = "lexemme 1 - flags only : \nlexemme 2 - percents : \n";

  char *c_string_3 = "";

  char *c_string_4 =
      "lexemme 1 - flags only %d : \nlexe%%mme 2 - percents : \n";
  s21_sprintf("hello world from sprintf\n", c_string_4);

  // char dest[SZ]="Hello world!";
  // char s21_dest[SZ]="Hello world!";
  // char str[]="Hello world!";
  // char str_1[]="Hello world!";
  // char str_2[]="there is no power as no ";
  // char str_2_1[]="there is no power as no ";
  // char* str_3=" byte code";

  // char *const_dest="Hello world!";

  // strbrk
  //  printf("\nC:\tS21_string  = %p,
  //  %c",s21_strpbrk(T_STR,T_SH_STR),*(s21_strpbrk(T_STR,T_SH_STR)));
  //  printf("\nC:\tstring  = %p,
  //  %c",strpbrk(T_STR,T_SH_STR),*(strpbrk(T_STR,T_SH_STR)));
  //  printf("\nC:\tS21_string  = %p",s21_strpbrk(T_STR,""));
  //  printf("\nC:\tstring  = %p",strpbrk(T_STR,""));
  //  printf("\nC:\tS21_string  = %p,
  //  %c",s21_strpbrk(str_2,T_SH_STR),*(s21_strpbrk(str_2,T_SH_STR)));
  //  printf("\nC:\tstring  = %p,
  //  %c",strpbrk(str_2,T_SH_STR),*(strpbrk(str_2,T_SH_STR)));
  //  printf("\nC:\tS21_string  = %p,
  //  %c",s21_strpbrk(T_SH_STR,str_2),*(s21_strpbrk(T_SH_STR,str_2)));
  //  printf("\nC:\tstring  = %p,
  //  %c",strpbrk(T_SH_STR,str_2),*(strpbrk(T_SH_STR,str_2)));

  // printf("\nC:\tS21_string  = %p",s21_strpbrk(T_SH_STR,T_NO_SYMB));
  // printf("\nC:\tstring  = %p",strpbrk(T_SH_STR,T_NO_SYMB));

  // printf("\nC:\tS21_string  = %p",s21_strpbrk(str_1,T_NO_SYMB));
  // printf("\nC:\tstring  = %p",strpbrk(str_1,T_NO_SYMB));

  // printf("\nC:\tS21_string  = %p",s21_strpbrk(str_3,T_NO_SYMB));
  // printf("\nC:\tstring  = %p",strpbrk(str_3,T_NO_SYMB));

  // //strstr
  //     printf("\n\tS21_string  = %p",s21_strstr(T_STR,T_NO_SYMB));
  //     printf("\n\tstring  = %p",strstr(T_STR,T_NO_SYMB));

  //     printf("\n\tS21_string  = %p %s %p
  //     %s",s21_strstr(T_STR,""),T_STR,&T_STR,T_STR); printf("\n\tstring  = %p
  //     %s %p %s",strstr(T_STR,""),T_STR,&T_STR, T_STR);

  //     printf("\n\tS21_string  = %p %s %p
  //     %s",s21_strstr(T_STR,T_STR_END),T_STR,&T_STR,T_STR); printf("\n\tstring
  //     = %p %s %p %s",strstr(T_STR,T_STR_END),T_STR,&T_STR, T_STR);

  // //strrchr
  //     printf("\n\tS21_string  = %p",s21_strrchr(T_STR,NOT_EXIST));
  //     printf("\n\tstring  = %p",strrchr(T_STR,NOT_EXIST));

  //     printf("\n\tS21_string  = %p",s21_strrchr(T_STR,EXIST));
  //     printf("\n\tstring  = %p",strrchr(T_STR,EXIST));

  // //strcspn
  //     printf("\n\tS21_string  = %ld",s21_strcspn(str_2,tk_1));
  //     printf("\n\tstring  = %ld",strcspn(str_2,tk_1));

  //     printf("\n\tS21_string  = %ld",s21_strcspn(str_2,tk_2));
  //     printf("\n\tstring  = %ld",strcspn(str_2,tk_2));

  //     printf("\n\tS21_string  = %ld",s21_strcspn(str_2,tk_3));
  //     printf("\n\tstring  = %ld",strcspn(str_2,tk_3));

  //     printf("\n\tS21_string  = %ld",s21_strcspn(str,tk_1));
  //     printf("\n\tstring  = %ld",strcspn(str,tk_1));

  //     printf("\n\tS21_string  = %ld",s21_strcspn("",tk_1));
  //     printf("\n\tstring  = %ld",strcspn("",tk_1));

  //     printf("\n\tS21_string  = %ld",s21_strcspn(str,""));
  //     printf("\n\tstring  = %ld",strcspn(str,""));

  // char* res=memset(dest, -7,0);
  // char* s21_res=s21_memset(s21_dest,-7,0);

  // printf("s = %s s= %s",res,s21_res);

  // //restore data
  //     strncpy(dest,const_dest,strlen(const_dest));
  //     s21_strncpy(s21_dest,const_dest,s21_strlen(const_dest));
  //     printf("\nC:\tstring  = %s\nC:\ts21_string = %s\n",dest,s21_dest);

  // //res=memset(dest, -7,-7);
  // s21_res=s21_memset(s21_dest,-7,-7);

  // printf("s = %s ",s21_res);

  // //restore data
  //     strncpy(dest,const_dest,strlen(const_dest));
  //     s21_strncpy(s21_dest,const_dest,s21_strlen(const_dest));
  //     printf("\nC:\tstring  = %s\nC:\ts21_string = %s\n",dest,s21_dest);

  // memcpy

  // res=s21_memcpy(dest, str_3,-5);
  // s21_res=s21_memset(s21_dest,str_3,-5);

  // res=memchr(dest,-4,-5);
  // res=memchr(dest,-4,10);

  // res=s21_memchr(dest,-4,-5);
  // res=s21_memchr(dest,-4,10);

  // //strncpy

  //     char *s_res=s21_strncpy(s21_dest,T_NO_SYMB,4);
  //     printf("\nC:\tS21_string  = %p result = %s src =
  //     %s",s_res,s_res,s21_dest);

  //     char *res=strncpy(dest,T_NO_SYMB,4);
  //     printf("\nC:\tstring  = %p result = %s src = %s",res,res,dest);

  //     strncpy(dest,const_dest,strlen(const_dest));
  //     s21_strncpy(s21_dest,const_dest,s21_strlen(const_dest));
  //     printf("\nC:\tstring  = %s\nC:\ts21_string = %s\n",dest,s21_dest);

  //     s_res=s21_strncpy(s21_dest,T_NO_SYMB,10);
  //     printf("\nC:\tS21_string  = %p result = %s src =
  //     %s",s_res,s_res,s21_dest);

  //     res=strncpy(dest,T_NO_SYMB,10);
  //     printf("\nC:\tstring  = %p result = %s src = %s",res,res,dest);

  //     strncpy(dest,const_dest,strlen(const_dest));
  //     s21_strncpy(s21_dest,const_dest,s21_strlen(const_dest));
  //     printf("\nC:\tstring  = %s\nC:\ts21_string = %s\n",dest,s21_dest);

  //     s_res=s21_strncpy(s21_dest,T_NO_SYMB,0);
  //     printf("\nC:\tS21_string  = %p result = %s src =
  //     %s",s_res,s_res,s21_dest);

  //     res=strncpy(dest,T_NO_SYMB,0);
  //     printf("\nC:\tstring  = %p result = %s src = %s",res,res,dest);

  //     strncpy(dest,const_dest,strlen(const_dest));
  //     s21_strncpy(s21_dest,const_dest,s21_strlen(const_dest));
  //     printf("\nC:\tstring  = %s\nC:\ts21_string =%s\n",dest,s21_dest);

  return 0;
}