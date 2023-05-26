	.text
	.file	"<stdin>"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$0, 4(%rsp)
	movq	m@GOTPCREL(%rip), %rax
	jmp	.LBB0_1
	.p2align	4, 0x90
.LBB0_3:                                # %L2
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	4(%rsp)
.LBB0_1:                                # %L0
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$5, 4(%rsp)
	jg	.LBB0_5
# %bb.2:                                # %L1
                                        #   in Loop: Header=BB0_1 Depth=1
	cmpl	$1, 4(%rsp)
	jle	.LBB0_3
# %bb.4:                                # %L3
                                        #   in Loop: Header=BB0_1 Depth=1
	movslq	4(%rsp), %rcx
	xorps	%xmm0, %xmm0
	cvtsi2sd	%ecx, %xmm0
	movsd	%xmm0, (%rax,%rcx,8)
	incl	%ecx
	movl	%ecx, 4(%rsp)
	cmpl	$5, %ecx
	jl	.LBB0_1
.LBB0_5:                                # %L6
	movsd	(%rax), %xmm0                   # xmm0 = mem[0],zero
	movsd	16(%rax), %xmm1                 # xmm1 = mem[0],zero
	movsd	40(%rax), %xmm2                 # xmm2 = mem[0],zero
	leaq	.L__unnamed_1(%rip), %rdi
	movb	$3, %al
	callq	print@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	m,@object                       # @m
	.bss
	.globl	m
	.p2align	4
m:
	.zero	48
	.size	m, 48

	.type	.L__unnamed_1,@object           # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"%5.1f %5.1f %5.1f\n"
	.size	.L__unnamed_1, 19

	.section	".note.GNU-stack","",@progbits
