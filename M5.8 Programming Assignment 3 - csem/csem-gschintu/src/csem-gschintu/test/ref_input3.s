	.text
	.file	"<stdin>"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$3, (%rsp)
	movabsq	$4616189618054758400, %rax      # imm = 0x4010000000000000
	movq	%rax, 16(%rsp)
	movl	$5, 4(%rsp)
	movabsq	$4618441417868443648, %rax      # imm = 0x4018000000000000
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	testb	%al, %al
	jne	.LBB0_3
# %bb.1:                                # %L0
	movsd	8(%rsp), %xmm0                  # xmm0 = mem[0],zero
	cvtsi2sdl	4(%rsp), %xmm1
	ucomisd	%xmm1, %xmm0
	jbe	.LBB0_3
# %bb.2:                                # %L1
	movsd	8(%rsp), %xmm0                  # xmm0 = mem[0],zero
	xorps	%xmm1, %xmm1
	cvtsi2sdl	(%rsp), %xmm1
	ucomisd	%xmm1, %xmm0
	ja	.LBB0_4
.LBB0_3:                                # %L2
	xorps	%xmm0, %xmm0
	cvtsi2sdl	(%rsp), %xmm0
	ucomisd	16(%rsp), %xmm0
	jne	.LBB0_5
	jp	.LBB0_5
.LBB0_4:                                # %L3
	leaq	.L__unnamed_1(%rip), %rdi
	jmp	.LBB0_6
.LBB0_5:                                # %L4
	leaq	.L__unnamed_2(%rip), %rdi
.LBB0_6:                                # %L5
	xorl	%eax, %eax
	callq	print@PLT
	xorl	%eax, %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_1,@object           # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"whoa\n"
	.size	.L__unnamed_1, 6

	.type	.L__unnamed_2,@object           # @1
.L__unnamed_2:
	.asciz	"what\n"
	.size	.L__unnamed_2, 6

	.section	".note.GNU-stack","",@progbits
