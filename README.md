# MSCS-COMPILERS
Graduate School - Compilers & Runtime Systems Course

### Html2LaTex
LaTex parser using lex and yacc

## CPASS
1. CPASS is a copy propagation optimizer based on Muchnick Copy Progragation and DFA algorithm
2. It uses LLVM API Instructions
3. Project consists in processing C code for 6 different inputs and creating LLVM Intermediate Representation (IR) ensuring local and global optimization.

## COPT
Straightforward project to optimize code for Arrays, Matrices structures and operations.

## CSEM
1. csem - semantic routines for C programs
2. IT uses LLVM API
3. Project consists on processing C code for 8 different inputs and creating LLVM Intermediate Representation (IR)
4. csem reads a C program (actually a subset of C) from its standard input and compiles it into LLVM intermediate representation (IR) on its standard output. It should support the following program constructs and statements in the C programming language:
 
<picture>
  <source media="(prefers-color-scheme: dark)" srcset="/assets/images/Screenshot 2023-05-26 at 10.25.36 AM.png">
  <source media="(prefers-color-scheme: light)" srcset="/assets/images/Screenshot 2023-05-26 at 10.25.36 AM.png">
  <img alt="" src="/assets/images/Screenshot 2023-05-26 at 10.25.36 AM.png">
</picture>

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="/assets/images/Screenshot 2023-05-26 at 10.40.50 AM.png">
  <source media="(prefers-color-scheme: light)" srcset="/assets/images/Screenshot 2023-05-26 at 10.40.50 AM.png">
  <img alt="" src="/assets/images/Screenshot 2023-05-26 at 10.40.50 AM.png">
</picture>

### INPUT 8
```
 #ifdef DEFAULT_CLANG
int print(const char *fmt, ...);
#endif

double m[6];

int main() {
  int i, j;

  i = 1;
  j = 8;

L1:
  m[i] = m[i] + i*j;
  if ( (m[i] > 30)) {
    goto L0;
  }
  j = j-1;
  goto L1;

L0:
  i = i+1;
  if (i < 4) {
    j = 8;
    goto L1;
  }

  print("%5.1f %5.1f %5.1f %5.1f %5.1f %5.1f\n",
        m[0], m[1], m[2], m[3], m[4], m[5]);
  return 0;
}
```

### OUTPUT 8


```
; ModuleID = '<stdin>'
source_filename = "<stdin>"

@m = global [6 x double] zeroinitializer
@0 = private unnamed_addr constant [37 x i8] c"%5.1f %5.1f %5.1f %5.1f %5.1f %5.1f\0A\00", align 1

declare i32 @print(i8*, ...)

define i32 @main() {
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  store i32 1, i32* %i, align 4
  store i32 8, i32* %j, align 4
  br label %userlbl_L1

userlbl_L1:                                       ; preds = %0
  %1 = load i32, i32* %i, align 4
  %2 = getelementptr [6 x double], [6 x double]* @m, i32 0, i32 %1
  %3 = load i32, i32* %i, align 4
  %4 = getelementptr [6 x double], [6 x double]* @m, i32 0, i32 %3
  %5 = load i32, i32* %i, align 4
  %6 = load i32, i32* %j, align 4
  %multmp = mul i32 %5, %6
  %7 = sitofp i32 %multmp to double
  %addtmp = add double* %4, double %7
  store double* %addtmp, double* %2, align 8
  %8 = load i32, i32* %i, align 4
  %9 = getelementptr [6 x double], [6 x double]* @m, i32 0, i32 %8
  %10 = fcmp ogt double* %9, double 3.000000e+01
  br i1 %10, label %L0, label %L1

L0:                                               ; preds = %userlbl_L1
  br label %L01

L01:                                              ; preds = %L0

L1:                                               ; preds = %userlbl_L1
  %11 = load i32, i32* %j, align 4
  %subtmp = sub i32 %11, 1
  store i32 %subtmp, i32* %j, align 4
  br label %L12
  br label %userlbl_L0

L12:                                              ; preds = %L1

userlbl_L0:                                       ; preds = %L1
  %12 = load i32, i32* %i, align 4
  %addtmp3 = add i32 %12, 1
  store i32 %addtmp3, i32* %i, align 4
  %13 = load i32, i32* %i, align 4
  %14 = icmp slt i32 %13, 4
  br i1 %14, label %L2, label %L3

L2:                                               ; preds = %userlbl_L0
  store i32 8, i32* %j, align 4
  br label %L14

L14:                                              ; preds = %L2

L3:                                               ; preds = %userlbl_L0
  %callret = call i32 (i8*, ...) @print(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @0, i32 0, i32 0), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 0), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 1), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 2), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 3), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 4), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 5))
  ret i32 0
}
```
