
 gcc -shared -o libcal.so cal.c
 gcc -rdynamic -o cal_use cal_use.c -ldl
 
 
 cal.c
 ```
 int add(int a, int b)
{
    return (a+b);
}
 ```
 
 cal.use.c
 ```
 #include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef int (*FUNC)(int,int);


int main(int argc, char **argv)
{
    void *handle;
    //int (*add)(int, int);
    FUNC add;
    char *error;

   handle = dlopen("./libcal.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

   dlerror();    /* Clear any existing error */

   /* Writing: cosine = (double (*)(double)) dlsym(handle, "cos");
 *        would seem more natural, but the C99 standard leaves
 *               casting from "void *" to a function pointer undefined.
 *                      The assignment used below is the POSIX.1-2003 (Technical
 *                             Corrigendum 1) workaround; see the Rationale for the
 *                                    POSIX specification of dlsym(). */

   //*(void **) (&add) = dlsym(handle, "add");
   add=(FUNC)dlsym(handle,"add");
   if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

   printf("%d\n", (*add)(2,3));
    dlclose(handle);
    exit(EXIT_SUCCESS);
}
 ```
