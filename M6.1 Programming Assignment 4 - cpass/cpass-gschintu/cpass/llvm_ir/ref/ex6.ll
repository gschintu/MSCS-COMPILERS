; ModuleID = '<stdin>'
source_filename = "./inputs/ex6.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-redhat-linux-gnu"

@.str = private unnamed_addr constant [42 x i8] c"i: %d\0A j: %d\0A a: %d\0A b: %d\0A c: %d\0A d: %d\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 1, i32* %2, align 4
  store i32 2, i32* %3, align 4
  store i32 6, i32* %4, align 4
  store i32 7, i32* %5, align 4
  store i32 8, i32* %6, align 4
  store i32 9, i32* %7, align 4
  br label %9

9:                                                ; preds = %34, %0
  %10 = load i32, i32* %2, align 4
  %11 = icmp ne i32 %10, 100
  br i1 %11, label %12, label %37

12:                                               ; preds = %9
  %13 = load i32, i32* %7, align 4
  %14 = srem i32 %13, 2
  %15 = icmp ne i32 %14, 0
  br i1 %15, label %16, label %34

16:                                               ; preds = %12
  %17 = load i32, i32* %4, align 4
  %18 = add nsw i32 %17, 14
  store i32 %18, i32* %4, align 4
  %19 = icmp ne i32 %18, 0
  %20 = xor i1 %19, true
  %21 = zext i1 %20 to i32
  %22 = srem i32 %21, 2
  %23 = icmp ne i32 %22, 0
  br i1 %23, label %24, label %33

24:                                               ; preds = %16
  %25 = load i32, i32* %3, align 4
  %26 = add nsw i32 %25, 1
  store i32 %26, i32* %8, align 4
  store i32 %18, i32* %3, align 4
  %27 = icmp slt i32 %26, %18
  br i1 %27, label %28, label %32

28:                                               ; preds = %24
  store i32 11, i32* %6, align 4
  %29 = icmp eq i32 11, 11
  br i1 %29, label %30, label %31

30:                                               ; preds = %28
  store i32 18, i32* %5, align 4
  br label %31

31:                                               ; preds = %30, %28
  br label %32

32:                                               ; preds = %31, %24
  br label %33

33:                                               ; preds = %32, %16
  store i32 %18, i32* %7, align 4
  br label %34

34:                                               ; preds = %33, %12
  %35 = load i32, i32* %2, align 4
  %36 = add nsw i32 %35, 1
  store i32 %36, i32* %2, align 4
  br label %9, !llvm.loop !4

37:                                               ; preds = %9
  %38 = load i32, i32* %6, align 4
  store i32 %38, i32* %2, align 4
  %39 = load i32, i32* %5, align 4
  store i32 %39, i32* %3, align 4
  %40 = load i32, i32* %4, align 4
  %41 = load i32, i32* %5, align 4
  %42 = load i32, i32* %6, align 4
  %43 = load i32, i32* %7, align 4
  %44 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([42 x i8], [42 x i8]* @.str, i64 0, i64 0), i32 noundef %38, i32 noundef %39, i32 noundef %40, i32 noundef %41, i32 noundef %42, i32 noundef %43)
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
