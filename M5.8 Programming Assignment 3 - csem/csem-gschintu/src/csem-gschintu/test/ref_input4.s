	.text
	.file	"<stdin>"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movl	$3, 28(%rsp)
	movabsq	$4616189618054758400, %rax      # imm = 0x4010000000000000
	movq	%rax, 32(%rsp)
	movl	$5, 12(%rsp)
	movabsq	$4618441417868443648, %rax      # imm = 0x4018000000000000
	movq	%rax, 16(%rsp)
	xorl	%eax, %eax
	testb	%al, %al
	jne	.LBB0_3
# %bb.1:                                # %L0
	cvtsi2sdl	12(%rsp), %xmm0
	ucomisd	16(%rsp), %xmm0
	jbe	.LBB0_2
.LBB0_3:                                # %L2
	leaq	.L__unnamed_1(%rip), %rdi
	jmp	.LBB0_4
.LBB0_2:                                # %L1
	leaq	.L__unnamed_2(%rip), %rdi
.LBB0_4:                                # %L3
	xorl	%eax, %eax
	callq	print@PLT
	xorl	%eax, %eax
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_2,@object           # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_2:
	.asciz	"whoa\n"
	.size	.L__unnamed_2, 6

	.type	.L__unnamed_1,@object           # @1
.L__unnamed_1:
	.asciz	"what\n"
	.size	.L__unnamed_1, 6

	.section	".note.GNU-stack","",@progbits
