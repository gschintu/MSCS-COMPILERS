#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/times.h>
#include <stdlib.h>
#include <float.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#define min(a, b) (((a)<(b))?(a):(b))

#define MATRIX_INITIALIZE 0
#define ARRAY_INITIALIZE 1
#define FACTORIAL 2
#define MATRIX_MULTIPLY 3

#define X 500
#define Y 12
#define Z 8

struct fn_args {
    int n;
    int *mem1;
    int *mem2;
    int *mem3;
    unsigned long long fac;
};

const char *op_names[] = {
    "MATRIX_INIT",
    "ARRAY_INIT",
    "FACTORIAL",
    "MATRIX_MULTIPLY"
};

const char usage[] =
"Usage: copt OP N LOOP\n\n"

"copt measures the execution time impact of source level optimizations\n"
"in C. copt runs and times an unoptimized and optimized version of a given\n"
"operation and input size.\n\n"

"Argument description:\n\n"

"OP is the operation to run for this invocation of copt. There are four\n"
"possible operations, each of which takes exactly one argument N:\n"
"  0: initialize a pair of square integer matrices. N is the size of the\n"
"     matrices.\n"
"  1: initialize an integer array. N is the length of the array\n"
"  2: compute factorial with a recursive routine. N is the number for\n"
"     which the routine computes the factorial\n"
"  3: multiply two square integer matrices. N is the size of the matrix\n\n"

"LOOP is the number of times to run the given operation with the given\n"
"argument. Timing starts before the first operation begins and ends when\n"
"the last operation has completed.\n\n"

"OP, N, and LOOP all must be integers <= INT_MAX\n";

int ttime()
{
   struct tms buffer;
   int utime;

   times(&buffer);
   utime = (buffer.tms_utime / 60.0) * 1000.0;
   return (utime);
}

int check(int x, int y) {
    return x < y;
}

void set(int *mat, int i, int num) {
    mat[i] = num;
}

void matrix_initialize_unopt(struct fn_args *args) {
    int i, j, n;
    int *mat1, *mat2;
    
    n = args->n;
    mat1 = args->mem1;
    mat2 = args->mem2;

    for (i = 0; check(i, n); i++){
        for (j = 0; check(j, n); j++){
            set(mat1, i * n + j, i);
            set(mat2, i * n + j, i+1);
        }
    }
}

#include <immintrin.h>

void matrix_initialize_opt(struct fn_args *args) {
    int i, j, n;
    int *mat1, *mat2;

    n = args->n;
    mat1 = args->mem1;
    mat2 = args->mem2;

    for (i = 0; i < n; i++) {
        int *mat1_row = mat1 + i * n;
        int *mat2_row = mat2 + i * n;
        int value1 = i;
        int value2 = i + 1;

        for (j = 0; j < n; j += 4) {
            if (j + 3 < n) {
                __m128i values1 = _mm_set1_epi32(value1);
                __m128i values2 = _mm_set1_epi32(value2);
                _mm_storeu_si128((__m128i *)(mat1_row + j), values1);
                _mm_storeu_si128((__m128i *)(mat2_row + j), values2);
            } else {
                for (; j < n; j++) {
                    mat1_row[j] = value1;
                    mat2_row[j] = value2;
                }
            }
        }
    }
}


/**
 * Extracted calculation from second loop as second loop only sets matrix value
 * Removed use of set and improved by almost 1 point
 * Removed check and improved by 1 point
*/
/*
void matrix_initialize_opt(struct fn_args *args) {
    int i, j, k, l, n, blk_size, *mat1, *mat2;

    n = args->n;
    mat1 = args->mem1;
    mat2 = args->mem2;

    blk_size = 16; // set block size for loop tiling
    for (i = 0; i < n; i += blk_size) {
        for (j = 0; j < n; j += blk_size) {
            for (k = i; k < i + blk_size && k < n; k++) {
                int value1 = k;
                int value2 = k + 1;
                for (l = j; l < j + blk_size && l < n; l++) {
                    // compute index for current element
                    int idx = k * n + l;

                    // assign values to mat1 and mat2 using indices and values
                    mat1[idx] = value1;
                    mat2[idx] = value2;
                }
            }
        }
    }
}
*/

/*
void matrix_initialize_opt(struct fn_args *args) {
    int i, j, n;
    int *mat1, *mat2;

    n = args->n;
    mat1 = args->mem1;
    mat2 = args->mem2;

    for (i = 0; i < n; i++) {
        int *mat1_row = mat1 + i * n;
        int *mat2_row = mat2 + i * n;
        int value1 = i;
        int value2 = i + 1;
        for (j = 0; j < n; j++) {
            mat1_row[j] = value1;
            mat2_row[j] = value2;
        }
    }

}
*/


void array_initialize_unopt(struct fn_args *args) {
    int i, mod, n, *arr;

    n = args->n;
    arr = args->mem1;
    for(i = 0; i < n; i++){
        mod = X % Y;
        arr[i] = i * mod * Z;
    }
}

void array_initialize_opt(struct fn_args *args) {
    int i, n, *arr;

    n = args->n;
    arr = args->mem1;
    int step = (X % Y) * Z;

    for (i = 0; i < n; i += 8, arr += 8) {
        arr[0] = i * step;
        arr[1] = (i+1) * step;
        arr[2] = (i+2) * step;
        arr[3] = (i+3) * step;
        arr[4] = (i+4) * step;
        arr[5] = (i+5) * step;
        arr[6] = (i+6) * step;
        arr[7] = (i+7) * step;
    }
}




/*

void array_initialize_opt(struct fn_args *args) {
    int i, mod, n, *arr;

    n = args->n;
    arr = args->mem1;
    //mod = X % Y;
    int mod_times_Z = (X % Y) * Z;

    for (i = 0; i < n; i++) {
        *arr++ = i * mod_times_Z;
    }
}
*/

/*
void array_initialize_opt(struct fn_args *args) {
    int i = 0, n, *arr;
    int mod = X % Y;
    int mod_times_Z = mod * Z;
    int temp = 0;

    n = args->n;
    arr = args->mem1;

    if (i >= n) {
        goto end;
    }

    L1:
        *arr++ = temp;
        temp += mod_times_Z;
        if (++i < n) {
            goto L1;
        }

    end:
        ; // No operation
}
*/

unsigned long long factorial_unopt_helper(unsigned long long n) {
    if (n == 0ull)
        return 1ull;
    return n * factorial_unopt_helper(n-1);
}

void factorial_unopt(struct fn_args *args) {
    args->fac = factorial_unopt_helper((unsigned long long) args->n);
}

unsigned long long factorial_opt_helper(unsigned long long n) {
    if (n <= 1) {
        return 1;
    }

    unsigned long long acc = 1;
    unsigned long long i;
    for (i = 2; i <= n - 3; i += 4) {
        acc *= i * (i + 1) * (i + 2) * (i + 3);
    }

    // Handle the remaining iterations if n is not a multiple of 4
    for (; i <= n; ++i) {
        acc *= i;
    }

    return acc;
}

void factorial_opt(struct fn_args *args) {
    args->fac = factorial_opt_helper((unsigned long long) args->n);
}

/*
unsigned long long factorial_opt_helper(unsigned long long n) {
    if (n <= 1) {
        return 1;
    }

    unsigned long long acc = 1;
    for (unsigned long long i = 2; i <= n; ++i) {
        acc *= i;
    }
    return acc;
}

void factorial_opt(struct fn_args *args) {
    args->fac = factorial_opt_helper((unsigned long long) args->n);
}
*/

void matrix_multiply_unopt(struct fn_args *args) {
    int i, j, k, n;
    int *mat1, *mat2, *res;

    n = args->n;
    mat1 = args->mem1;
    mat2 = args->mem2;
    res = args->mem3;

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            res[i * n + j] = 0;
            for(k = 0; k < n; k++){
                res[i * n + j] += mat1[i * n + k] * mat2[k * n + j];
            }
        }
    }
}

#define MM_TILE_SIZE 16

void matrix_multiply_opt(struct fn_args *args) {
    int i, j, k, n;
    int *mat1, *mat2, *res;

    n = args->n;
    mat1 = args->mem1;
    mat2 = args->mem2;
    res = args->mem3;

    for (int ii = 0; ii < n; ii += MM_TILE_SIZE) {
        for (int jj = 0; jj < n; jj += MM_TILE_SIZE) {
            for (int kk = 0; kk < n; kk += MM_TILE_SIZE) {
                for (i = ii; i < ii + MM_TILE_SIZE && i < n; i++) {
                    for (j = jj; j < jj + MM_TILE_SIZE && j < n; j++) {
                        int sum = 0;
                        for (k = kk; k < kk + MM_TILE_SIZE && k < n; k++) {
                            sum += mat1[i * n + k] * mat2[k * n + j];
                        }
                        res[i * n + j] += sum;
                    }
                }
            }
        }
    }
}


// XXX: students should not modify any code below this point

void init_op(int op, int n, void (**unopt_fn)(struct fn_args *args),
    void (**opt_fn)(struct fn_args *args), struct fn_args *args) {

    if (op == MATRIX_INITIALIZE) {

        args->n = n;
        args->mem1 = malloc(sizeof(int) * (n * n));
        if (args->mem1 == NULL){
            exit(-ENOMEM);
        }

        args->mem2 = malloc(sizeof(int) * (n * n));
        if (args->mem2 == NULL){
            exit(-ENOMEM);
        }

        (*unopt_fn) = matrix_initialize_unopt;
        (*opt_fn) = matrix_initialize_opt;
    }
    
    else if (op == ARRAY_INITIALIZE) {

        args->n = n;
        args->mem1 = malloc(sizeof(int) * n);
        if (args->mem1 == NULL){
            exit(-ENOMEM);
        }

        (*unopt_fn) = array_initialize_unopt;
        (*opt_fn) = array_initialize_opt;
    }

    else if (op == FACTORIAL) {
        args->n = n;
        (*unopt_fn) = factorial_unopt;
        (*opt_fn) = factorial_opt;
    }

    else if (op == MATRIX_MULTIPLY) {

        args->n = n;
        args->mem1 = malloc(sizeof(int) * (n * n));
        if (args->mem1 == NULL){
            exit(-ENOMEM);
        }

        args->mem2 = malloc(sizeof(int) * (n * n));
        if (args->mem2 == NULL){
            exit(-ENOMEM);
        }

        args->mem3 = malloc(sizeof(int) * (n * n));
        if (args->mem3 == NULL){
            exit(-ENOMEM);
        }

        matrix_initialize_unopt(args);

        (*unopt_fn) = matrix_multiply_unopt;
        (*opt_fn) = matrix_multiply_opt;
    }
}

void store_op_result(int op, struct fn_args *args,
    int **arr_exp, unsigned long long *fac_exp) {

    int n;
    n = args->n;
    if (op == MATRIX_INITIALIZE) {

        (*arr_exp) = malloc((sizeof(int)*(n*n)*2));
        if ((*arr_exp) == NULL) {
            exit(-ENOMEM);
        }
        memcpy(&((*arr_exp)[0]), args->mem1, (sizeof(int)*(n*n)));
        memcpy(&((*arr_exp)[n*n]), args->mem2, (sizeof(int)*(n*n)));

    } else if (op == ARRAY_INITIALIZE) {

        (*arr_exp) = malloc(sizeof(int)*n);
        if ((*arr_exp) == NULL) {
            exit(-ENOMEM);
        }
        memcpy(&((*arr_exp)[0]), args->mem1, (sizeof(int)*n));

    } else if (op == FACTORIAL) {

        (*fac_exp) = args->fac;

    } else if (op == MATRIX_MULTIPLY) {

        (*arr_exp) = malloc((sizeof(int)*(n*n)));
        if ((*arr_exp) == NULL) {
            exit(-ENOMEM);
        }
        memcpy(&((*arr_exp)[0]), args->mem3, (sizeof(int)*(n*n)));
    }
}

void check_op_result(int op, struct fn_args *args, int *arr_exp,
    unsigned long long fac_exp) {

    int n, ret;

    ret = 0;
    n = args->n;
    if (op == MATRIX_INITIALIZE) {
        ret =  memcmp(&(arr_exp[0]), args->mem1, (sizeof(int)*(n*n)));
        ret += memcmp(&(arr_exp[n*n]), args->mem2, (sizeof(int)*(n*n)));
    } else if (op == ARRAY_INITIALIZE) {
        ret = memcmp(&(arr_exp[0]), args->mem1, (sizeof(int)*n));
    } else if (op == FACTORIAL) {
        ret = (fac_exp == args->fac) ? 0 : 1;
    } else if (op == MATRIX_MULTIPLY) {
        ret = memcmp(&(arr_exp[0]), args->mem3, (sizeof(int)*(n*n)));
    }

    if(ret != 0){
        fprintf(stderr, "result of optimized operation did not match result "
                        "of unoptimized operation\n");
        exit(1);
    }
}

float time_op(void (*fn) (struct fn_args *args),
    struct fn_args *args, int loop) {
    int i;
    float start, end;

    start = ttime();
    for(i = 0; i < loop; i++){
        (fn)(args);
    }
    end = ttime();

    return (end - start);
}

void parse_options(int argc, char **argv, int *op, int *n, int *loop) {
    if (argc != 4) {
        printf(usage);
        exit(-EINVAL);
    }

    *op = strtol(argv[1], NULL, 10);
    *n = strtol(argv[2], NULL, 10);
    *loop = strtol(argv[3], NULL, 10);

    if (errno) {
        printf(usage);
    }
}

int main(int argc, char **argv){
    int i, op, n, loop;
    int *arr_exp;
    float unopt_time, opt_time;
    struct fn_args fn_args;
    unsigned long long fac_exp;
    void (*unopt_fn) (struct fn_args *args);
    void (*opt_fn) (struct fn_args *args);

    parse_options(argc, argv, &op, &n, &loop);

    printf("Running %s with n = %d loop = %d\n\n", op_names[op], n, loop); fflush(stdout);

    memset(&fn_args,0,sizeof(fn_args));
    init_op(op, n, &unopt_fn, &opt_fn, &fn_args);
    unopt_time = time_op(unopt_fn, &fn_args, loop);

    printf("UNOPTIMIZED(ms):  %12.1f\n", unopt_time); fflush(stdout);

    store_op_result(op, &fn_args, &arr_exp, &fac_exp);

    memset(&fn_args,0,sizeof(fn_args));
    init_op(op, n, &unopt_fn, &opt_fn, &fn_args);
    opt_time = time_op(opt_fn, &fn_args, loop);

    check_op_result(op, &fn_args, arr_exp, fac_exp);

    printf("OPTIMIZED(ms):    %12.1f\n", opt_time);
    printf("SPEEDUP:          %12.1f\n", (unopt_time / opt_time));

    return 0;
}
