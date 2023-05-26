; ModuleID = '<stdin>'
source_filename = "<stdin>"

@m = global [6 x double] zeroinitializer
@0 = private unnamed_addr constant [37 x i8] c"%5.1f %5.1f %5.1f %5.1f %5.1f %5.1f\0A\00", align 1

declare i32 @print(i8*, ...)

define i32 @main() {
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  store i32 0, i32* %i, align 4
  br label %L0

L0:                                               ; preds = %L6, %0
  %1 = load i32, i32* %i, align 4
  %2 = icmp slt i32 %1, 6
  br i1 %2, label %L1, label %L7

L1:                                               ; preds = %L0
  store i32 5, i32* %j, align 4
  br label %L2

L2:                                               ; preds = %L5, %L1
  %3 = load i32, i32* %i, align 4
  %4 = getelementptr [6 x double], [6 x double]* @m, i32 0, i32 %3
  %5 = load i32, i32* %i, align 4
  %6 = getelementptr [6 x double], [6 x double]* @m, i32 0, i32 %5
  %7 = load double, double* %6, align 8
  %8 = load i32, i32* %i, align 4
  %9 = load i32, i32* %j, align 4
  %10 = mul i32 %8, %9
  %11 = sitofp i32 %10 to double
  %12 = fadd double %7, %11
  store double %12, double* %4, align 8
  %13 = load i32, i32* %i, align 4
  %14 = load i32, i32* %j, align 4
  %15 = mul i32 %13, %14
  %16 = srem i32 %15, 3
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %L3, label %L4

L3:                                               ; preds = %L2
  br label %L6

L4:                                               ; preds = %L2
  %18 = load i32, i32* %j, align 4
  %19 = sub i32 %18, 1
  store i32 %19, i32* %j, align 4
  br label %L5

L5:                                               ; preds = %L4
  %20 = load i32, i32* %j, align 4
  %21 = icmp sgt i32 %20, 0
  br i1 %21, label %L2, label %L6

L6:                                               ; preds = %L3, %L5
  %22 = load i32, i32* %i, align 4
  %23 = add i32 %22, 1
  store i32 %23, i32* %i, align 4
  br label %L0

L7:                                               ; preds = %L0
  %24 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 0), align 8
  %25 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 1), align 8
  %26 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 2), align 8
  %27 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 3), align 8
  %28 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 4), align 8
  %29 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 5), align 8
  %30 = call i32 (i8*, ...) @print(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @0, i32 0, i32 0), double %24, double %25, double %26, double %27, double %28, double %29)
  ret i32 0
}
