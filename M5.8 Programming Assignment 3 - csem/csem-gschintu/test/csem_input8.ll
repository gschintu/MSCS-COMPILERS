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
