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
  %1 = load i32, i32* %a, align 4
  %2 = load double, double* %b, align 8
  %3 = fptosi double %2 to i32
  %4 = icmp slt i32 %1, %3
  br i1 %4, label %L0, label %L2

L0:                                               ; preds = %0
  %5 = load i32, i32* %c, align 4
  %6 = load double, double* %d, align 8
  %7 = fptosi double %6 to i32
  %8 = icmp slt i32 %5, %7
  br i1 %8, label %L1, label %L2

L1:                                               ; preds = %L0
  %9 = load double, double* %d, align 8
  %10 = load i32, i32* %a, align 4
  %11 = sitofp i32 %10 to double
  %12 = fcmp ogt double %9, %11
  br i1 %12, label %L3, label %L2

L2:                                               ; preds = %L1, %L0, %0
  %13 = load i32, i32* %a, align 4
  %14 = load double, double* %b, align 8
  %15 = fptosi double %14 to i32
  %16 = icmp eq i32 %13, %15
  br i1 %16, label %L3, label %L4

L3:                                               ; preds = %L2, %L1
  %callret = call i32 (i8*, ...) @print(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @0, i32 0, i32 0))
  br label %L5

L4:                                               ; preds = %L2
  %callret1 = call i32 (i8*, ...) @print(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @1, i32 0, i32 0))
  br label %L5

L5:                                               ; preds = %L3, %L4
  ret i32 0
}
