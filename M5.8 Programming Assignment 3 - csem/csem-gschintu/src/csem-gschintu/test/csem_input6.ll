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
  %addtmp = add i32 %5, 1
  store i32 %addtmp, i32* %i, align 4
  br label %L0

L3:                                               ; preds = %L1
  %6 = load i32, i32* %i, align 4
  %7 = getelementptr [6 x double], [6 x double]* @m, i32 0, i32 %6
  %8 = load i32, i32* %i, align 4
  %9 = sitofp i32 %8 to double
  store double %9, double* %7, align 8
  %10 = load i32, i32* %i, align 4
  %addtmp1 = add i32 %10, 1
  store i32 %addtmp1, i32* %i, align 4
  %11 = load i32, i32* %i, align 4
  %12 = icmp sgt i32 %11, 4
  br i1 %12, label %L4, label %L5

L4:                                               ; preds = %L3
  br label %L6

L5:                                               ; preds = %L3
  br label %L0

L6:                                               ; preds = %L0, %L4
  %callret = call i32 (i8*, ...) @print(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @0, i32 0, i32 0), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 0), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 2), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 5))
  ret i32 0
}
