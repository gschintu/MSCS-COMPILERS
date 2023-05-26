; ModuleID = '<stdin>'
source_filename = "<stdin>"

@0 = private unnamed_addr constant [19 x i8] c"%d %3.2f %d %3.2f\0A\00", align 1

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
  %3 = load i32, i32* %c, align 4
  %4 = load double, double* %d, align 8
  %5 = call i32 (i8*, ...) @print(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @0, i32 0, i32 0), i32 %1, double %2, i32 %3, double %4)
  ret i32 0
}
