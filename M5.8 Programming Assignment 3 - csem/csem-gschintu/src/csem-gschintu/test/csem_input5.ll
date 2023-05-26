; ModuleID = '<stdin>'
source_filename = "<stdin>"

@m = global [6 x double] zeroinitializer
@0 = private unnamed_addr constant [19 x i8] c"%5.1f %5.1f %5.1f\0A\00", align 1
@1 = private unnamed_addr constant [18 x i8] c"%5.1f %5.1f %5.1f\00", align 1

declare i32 @print(i8*, ...)

define internal i32 @scale(double %x) {
  %x1 = alloca double, align 8
  store double %x, double* %x1, align 8
  %i = alloca i32, align 4
  %1 = load double, double* %x1, align 8
  %2 = fcmp oeq double %1, 0.000000e+00
  br i1 %2, label %L0, label %L1

L0:                                               ; preds = %0
  ret i32 0

L1:                                               ; preds = %0
  store i32 0, i32* %i, align 4
  br label %L2

L2:                                               ; preds = %L3, %L1
  %3 = load i32, i32* %i, align 4
  %4 = icmp slt i32 %3, 6
  br i1 %4, label %L4, label %L5

L3:                                               ; preds = %L4
  %5 = load volatile i32, i32* %i, align 4
  %addtmp = add i32 %5, 1
  store i32 %addtmp, i32* %i, align 4
  br label %L2

L4:                                               ; preds = %L2
  %6 = load i32, i32* %i, align 4
  %7 = getelementptr [6 x double], [6 x double]* @m, i32 0, i32 %6
  %8 = load double, double* %x1, align 8
  %9 = load volatile double, double* %7, align 8
  %multmp = fmul double %9, %8
  store double %multmp, double* %7, align 8
  br label %L3

L5:                                               ; preds = %L2
  ret i32 1
}

define i32 @main() {
  %i = alloca i32, align 4
  %x = alloca double, align 8
  store i32 0, i32* %i, align 4
  br label %L6

L6:                                               ; preds = %L7, %0
  %1 = load i32, i32* %i, align 4
  %2 = icmp slt i32 %1, 6
  br i1 %2, label %L7, label %L8

L7:                                               ; preds = %L6
  %3 = load i32, i32* %i, align 4
  %4 = getelementptr [6 x double], [6 x double]* @m, i32 0, i32 %3
  %5 = load i32, i32* %i, align 4
  %6 = sitofp i32 %5 to double
  store double %6, double* %4, align 8
  %7 = load i32, i32* %i, align 4
  %addtmp = add i32 %7, 1
  store i32 %addtmp, i32* %i, align 4
  br label %L6

L8:                                               ; preds = %L6
  %callret = call i32 (i8*, ...) @print(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @0, i32 0, i32 0), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 0), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 2), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 5))
  store double 5.000000e+00, double* %x, align 8
  %8 = load double, double* %x, align 8
  %callret1 = call i32 @scale(double %8)
  %callret2 = call i32 (i8*, ...) @print(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @1, i32 0, i32 0), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 0), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 2), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 5))
  ret i32 0
}
