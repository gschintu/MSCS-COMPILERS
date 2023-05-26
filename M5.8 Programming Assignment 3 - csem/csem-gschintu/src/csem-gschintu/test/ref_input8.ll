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

userlbl_L1:                                       ; preds = %L2, %L1, %0
  %1 = load i32, i32* %i, align 4
  %2 = getelementptr [6 x double], [6 x double]* @m, i32 0, i32 %1
  %3 = load i32, i32* %i, align 4
  %4 = getelementptr [6 x double], [6 x double]* @m, i32 0, i32 %3
  %5 = load double, double* %4, align 8
  %6 = load i32, i32* %i, align 4
  %7 = load i32, i32* %j, align 4
  %8 = mul i32 %6, %7
  %9 = sitofp i32 %8 to double
  %10 = fadd double %5, %9
  store double %10, double* %2, align 8
  %11 = load i32, i32* %i, align 4
  %12 = getelementptr [6 x double], [6 x double]* @m, i32 0, i32 %11
  %13 = load double, double* %12, align 8
  %14 = fcmp ogt double %13, 3.000000e+01
  br i1 %14, label %L0, label %L1

L0:                                               ; preds = %userlbl_L1
  br label %userlbl_L0

L1:                                               ; preds = %userlbl_L1
  %15 = load i32, i32* %j, align 4
  %16 = sub i32 %15, 1
  store i32 %16, i32* %j, align 4
  br label %userlbl_L1

userlbl_L0:                                       ; preds = %L0
  %17 = load i32, i32* %i, align 4
  %18 = add i32 %17, 1
  store i32 %18, i32* %i, align 4
  %19 = load i32, i32* %i, align 4
  %20 = icmp slt i32 %19, 4
  br i1 %20, label %L2, label %L3

L2:                                               ; preds = %userlbl_L0
  store i32 8, i32* %j, align 4
  br label %userlbl_L1

L3:                                               ; preds = %userlbl_L0
  %21 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 0), align 8
  %22 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 1), align 8
  %23 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 2), align 8
  %24 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 3), align 8
  %25 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 4), align 8
  %26 = load double, double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 5), align 8
  %27 = call i32 (i8*, ...) @print(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @0, i32 0, i32 0), double %21, double %22, double %23, double %24, double %25, double %26)
  ret i32 0
}
