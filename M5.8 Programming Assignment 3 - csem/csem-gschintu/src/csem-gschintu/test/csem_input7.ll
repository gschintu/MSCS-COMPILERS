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
  %7 = load i32, i32* %i, align 4
  %8 = load i32, i32* %j, align 4
  %multmp = mul i32 %7, %8
  %9 = sitofp i32 %multmp to double
  %addtmp = add double* %6, double %9
  store double* %addtmp, double* %4, align 8
  %10 = load i32, i32* %i, align 4
  %11 = load i32, i32* %j, align 4
  %multmp1 = mul i32 %10, %11
  %remtmp = srem i32 %multmp1, 3
  %12 = icmp eq i32 %remtmp, 0
  br i1 %12, label %L3, label %L4

L3:                                               ; preds = %L2
  br label <badref>

L4:                                               ; preds = %L2
  %13 = load i32, i32* %j, align 4
  %subtmp = sub i32 %13, 1
  store i32 %subtmp, i32* %j, align 4
  br label %L5

L5:                                               ; preds = %L5, %L4
  %14 = load i32, i32* %j, align 4
  %15 = icmp sgt i32 %14, 0
  br i1 %15, label %L2, label %L5

L6:                                               ; No predecessors!
  %16 = load i32, i32* %i, align 4
  %addtmp2 = add i32 %16, 1
  store i32 %addtmp2, i32* %i, align 4
  br label %L0

L7:                                               ; preds = %L0
  %callret = call i32 (i8*, ...) @print(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @0, i32 0, i32 0), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 0), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 1), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 2), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 3), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 4), double* getelementptr inbounds ([6 x double], [6 x double]* @m, i32 0, i32 5))
  ret i32 0
}
