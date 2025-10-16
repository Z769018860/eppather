	.file	"spectre3.c"
	.text
	.globl	simulate_attack
	.type	simulate_attack, @function
simulate_attack:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$1120, %rsp
	movl	%edi, -1108(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$16, -1068(%rbp)
	movl	$0, -1092(%rbp)
	movl	$1, -1064(%rbp)
	movl	$0, -1084(%rbp)
	jmp	.L2
.L3:
	movl	$0, -1072(%rbp)
	addl	$1, -1084(%rbp)
.L2:
	cmpl	$255, -1084(%rbp)
	jle	.L3
	movl	$999, -1088(%rbp)
	jmp	.L4
.L15:
	movl	-1088(%rbp), %eax
	cltd
	idivl	-1068(%rbp)
	movl	%edx, -1060(%rbp)
	movl	$29, -1080(%rbp)
	jmp	.L5
.L7:
	movl	-1080(%rbp), %ecx
	movslq	%ecx, %rax
	imulq	$715827883, %rax, %rax
	shrq	$32, %rax
	movq	%rax, %rdx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	leal	-1(%rdx), %eax
	movw	$0, %ax
	movl	%eax, -1052(%rbp)
	movl	-1052(%rbp), %eax
	sarl	$16, %eax
	orl	%eax, -1052(%rbp)
	movl	-1108(%rbp), %eax
	xorl	-1060(%rbp), %eax
	andl	-1052(%rbp), %eax
	xorl	-1060(%rbp), %eax
	movl	%eax, -1052(%rbp)
	movl	-1052(%rbp), %eax
	cmpl	-1068(%rbp), %eax
	jge	.L6
	movl	-1048(%rbp), %eax
	imull	-1044(%rbp), %eax
	sall	$9, %eax
	andl	%eax, -1092(%rbp)
.L6:
	subl	$1, -1080(%rbp)
.L5:
	cmpl	$0, -1080(%rbp)
	jns	.L7
	movl	$0, -1084(%rbp)
	jmp	.L8
.L10:
	movl	-1084(%rbp), %eax
	imull	$167, %eax, %eax
	addl	$13, %eax
	andl	$255, %eax
	movl	%eax, -1056(%rbp)
	movl	-1088(%rbp), %eax
	cltd
	idivl	-1068(%rbp)
	movl	%edx, %eax
	cmpl	%eax, -1056(%rbp)
	je	.L9
	addl	$1, -1072(%rbp)
.L9:
	addl	$1, -1084(%rbp)
.L8:
	cmpl	$255, -1084(%rbp)
	jle	.L10
	movl	$-1, -1076(%rbp)
	movl	-1076(%rbp), %eax
	movl	%eax, -1080(%rbp)
	movl	$0, -1084(%rbp)
	jmp	.L11
.L12:
	movl	-1080(%rbp), %eax
	movl	%eax, -1076(%rbp)
	movl	-1084(%rbp), %eax
	movl	%eax, -1080(%rbp)
	addl	$1, -1084(%rbp)
.L11:
	cmpl	$255, -1084(%rbp)
	jle	.L12
	movl	-1072(%rbp), %eax
	addl	$2, %eax
	addl	%eax, %eax
	cmpl	%eax, -1072(%rbp)
	jg	.L13
	cmpl	$2, -1072(%rbp)
	jne	.L14
	cmpl	$0, -1072(%rbp)
	je	.L13
.L14:
	subl	$1, -1088(%rbp)
.L4:
	cmpl	$0, -1088(%rbp)
	jg	.L15
.L13:
	movl	-1080(%rbp), %eax
	movl	%eax, -1044(%rbp)
	movl	-1072(%rbp), %eax
	movl	%eax, -1064(%rbp)
	movl	-1076(%rbp), %eax
	movl	%eax, -1044(%rbp)
	movl	-1072(%rbp), %eax
	movl	%eax, -1064(%rbp)
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L16
	call	__stack_chk_fail@PLT
.L16:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	simulate_attack, .-simulate_attack
	.section	.rodata
	.align 8
.LC2:
	.string	"Function execution time: %.16f milliseconds\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-48(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	gettimeofday@PLT
	movl	$10, %edi
	call	simulate_attack
	leaq	-32(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	gettimeofday@PLT
	movq	-32(%rbp), %rdx
	movq	-48(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -64(%rbp)
	movq	-24(%rbp), %rdx
	movq	-40(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -56(%rbp)
	movq	-64(%rbp), %rax
	imulq	$1000, %rax, %rax
	cvtsi2sdq	%rax, %xmm1
	cvtsi2sdq	-56(%rbp), %xmm0
	movsd	.LC0(%rip), %xmm2
	divsd	%xmm2, %xmm0
	addsd	%xmm0, %xmm1
	movsd	.LC1(%rip), %xmm0
	addsd	%xmm1, %xmm0
	leaq	.LC2(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L19
	call	__stack_chk_fail@PLT
.L19:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	0
	.long	1083129856
	.align 8
.LC1:
	.long	0
	.long	1071644672
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
