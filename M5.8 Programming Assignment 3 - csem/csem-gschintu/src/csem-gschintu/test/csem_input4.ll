; ModuleID = '<stdin>'
source_filename = "<stdin>"

@0 = private unnamed_addr constant [6 x i8] c"whoa\0A\00", align 1
@1 = private unnamed_addr constant [6 x i8] c"what\0A\00", align 1

declare i32 @print(i8*, ...)

define i32 @main() {
  %a = alloca i32, align 4
  %c = alloca i32, align 4
  %b = alloca double, align 8
  %d = alloca double, align 8
  store i32 3, i32* %a, align 4
  store double 4.000000e+00, double* %b, align 8
  store i32 5, i32* %c, align 4
  store double 6.000000e+00, double* %d, align 8
  %1 = load double, double* %b, align 8
  %2 = load i32, i32* %a, align 4
  %3 = sitofp i32 %2 to double
  %4 = fcmp olt double %1, %3
  br i1 %4, label %L2, label %L0

L0:                                               ; preds = %0
  %5 = load double, double* %d, align 8
  %6 = load i32, i32* %c, align 4
  %7 = sitofp i32 %6 to double
  %8 = fcmp olt double %5, %7
  br i1 %8, label %L2, label %L1

L1:                                               ; preds = %L0
  %callret = call i32 (i8*, ...) @print(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @0, i32 0, i32 0))
  br label %L3

L2:                                               ; preds = %L0, %0
  %callret1 = call i32 (i8*, ...) @print(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @1, i32 0, i32 0))
  br label %L3

L3:                                               ; preds = %L1, %L2
  ret i32 0
}
