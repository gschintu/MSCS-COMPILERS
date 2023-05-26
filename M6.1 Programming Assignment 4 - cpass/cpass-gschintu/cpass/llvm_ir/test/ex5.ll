; ModuleID = '<stdin>'
source_filename = "./inputs/ex5.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-redhat-linux-gnu"

@m = dso_local global [6 x i32] zeroinitializer, align 16
@.str = private unnamed_addr constant [10 x i8] c"%d %d %d\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @scale(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  %5 = icmp eq i32 %0, 0
  br i1 %5, label %6, label %7

6:                                                ; preds = %1
  store i32 0, i32* %2, align 4
  br label %22

7:                                                ; preds = %1
  store i32 0, i32* %4, align 4
  br label %8

8:                                                ; preds = %18, %7
  %9 = load i32, i32* %4, align 4
  %10 = icmp slt i32 %9, 6
  br i1 %10, label %11, label %21

11:                                               ; preds = %8
  %12 = load i32, i32* %3, align 4
  %13 = load i32, i32* %4, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds [6 x i32], [6 x i32]* @m, i64 0, i64 %14
  %16 = load i32, i32* %15, align 4
  %17 = mul nsw i32 %16, %12
  store i32 %17, i32* %15, align 4
  br label %18

18:                                               ; preds = %11
  %19 = load i32, i32* %4, align 4
  %20 = add nsw i32 %19, 1
  store i32 %20, i32* %4, align 4
  br label %8, !llvm.loop !4

21:                                               ; preds = %8
  store i32 1, i32* %2, align 4
  br label %22

22:                                               ; preds = %21, %6
  %23 = load i32, i32* %2, align 4
  ret i32 %23
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 9, i32* %4, align 4
  store i32 0, i32* %2, align 4
  br label %7

7:                                                ; preds = %10, %0
  %8 = load i32, i32* %2, align 4
  %9 = icmp slt i32 %8, 6
  br i1 %9, label %10, label %17

10:                                               ; preds = %7
  %11 = load i32, i32* %2, align 4
  %12 = load i32, i32* %2, align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds [6 x i32], [6 x i32]* @m, i64 0, i64 %13
  store i32 %11, i32* %14, align 4
  %15 = load i32, i32* %2, align 4
  %16 = add nsw i32 %15, 1
  store i32 %16, i32* %2, align 4
  br label %7, !llvm.loop !6

17:                                               ; preds = %7
  %18 = load i32, i32* %4, align 4
  store i32 %18, i32* %5, align 4
  %19 = load i32, i32* %2, align 4
  store i32 %19, i32* %6, align 4
  %20 = load i32, i32* getelementptr inbounds ([6 x i32], [6 x i32]* @m, i64 0, i64 0), align 16
  %21 = load i32, i32* getelementptr inbounds ([6 x i32], [6 x i32]* @m, i64 0, i64 2), align 8
  %22 = load i32, i32* getelementptr inbounds ([6 x i32], [6 x i32]* @m, i64 0, i64 5), align 4
  %23 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i64 0, i64 0), i32 noundef %20, i32 noundef %21, i32 noundef %22)
  store i32 %18, i32* %3, align 4
  %24 = call i32 @scale(i32 noundef %18)
  %25 = load i32, i32* getelementptr inbounds ([6 x i32], [6 x i32]* @m, i64 0, i64 0), align 16
  %26 = load i32, i32* getelementptr inbounds ([6 x i32], [6 x i32]* @m, i64 0, i64 2), align 8
  %27 = load i32, i32* getelementptr inbounds ([6 x i32], [6 x i32]* @m, i64 0, i64 5), align 4
  %28 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i64 0, i64 0), i32 noundef %25, i32 noundef %26, i32 noundef %27)
  ret i32 0
}

declare dso_local i32 @printf(i8* noundef, ...) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{!"clang version 14.0.6 (Red Hat 14.0.6-1.module+el8.7.0+15816+ec020e8f)"}
!4 = distinct !{!4, !5}
!5 = !{!"llvm.loop.mustprogress"}
!6 = distinct !{!6, !5}
