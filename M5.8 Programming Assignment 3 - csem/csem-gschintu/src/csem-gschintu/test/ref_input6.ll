; ModuleID = '<stdin>'
source_filename = "<stdin>"

@m = global [6 x double] zeroinitializer
@0 = private unnamed_addr constant [19 x i8] c"%5.1f %5.1f %5.1f\0A\00", align 1

declare i32 @print(i8*, ...)

define i32 @main() {
  %i = alloca i32, align 4
  store i32 0, i32* %i, align 4
  br label %L0

L0:                                               ; preds = %L2, %L5, %0
  %1 = load i32, i32* %i, align 4
  %2 = icmp slt i32 %1, 6
  br i1 %2, label %L1, label %L6

L1:                                               ; preds = %L0
  %3 = load i32, i32* %i, align 4
  %4 = icmp slt i32 %3, 2
  br i1 %4, label %L2, label %L3

L2:                                               ; preds = %L1
  %5 = load i32, i32* %i, align 4
  %6 = add i32 %5, 1
  store i32 %6, i32* %i, align 4
  br label %L0

L3:                                               ; preds = %L1
  %7 = load i32, i32* %i, align 4
  %8 = getelementptr [6 x double], [6 x double]* @m, i32 0, i32 %7
  %9 = load i32, i32* %i, align 4
  %10 = sitofp i32 %9 to double
  store double %10, double* %8, align 8
  %11 = load i32, i32* %i, align 4
  %12 = add i32 %11, 1
  store i32 %12, i32* %i, align 4
  %13 = load i32, i32* %i, align 4
  %14 = icmp sgt i32 %13, 4
  br i1 %14, label %L4, label %L5

L4:                                               ; preds = %L3
  br label %L6

L5:                                               ; preds = %L3
  br label %L0

L6:                                               ; preds = %L4, %L0
  %15 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 0), align 8
  %16 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 2), align 8
  %17 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 5), align 8
  %18 = call i32 (i8*, ...) @print(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @0, i32 0, i32 0), double %15, double %16, double %17)
  ret i32 0
}
