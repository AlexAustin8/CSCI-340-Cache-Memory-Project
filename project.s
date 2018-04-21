	.file	"project.c"
	.data
	.align 4
	.type	arrLength, @object
	.size	arrLength, 4
arrLength:
	.long	1000000
	.local	array
	.comm	array,4000000,32
	.local	arr
	.comm	arr,8000000,32
	.section	.rodata
.LC0:
	.string	"Average: %f\n"
.LC1:
	.string	"Mode: %lu\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	$0, -72(%rbp)
	movl	$0, -108(%rbp)
	movl	$0, -104(%rbp)
	movl	$1, -84(%rbp)
	movl	$0, -100(%rbp)
	jmp	.L2
.L3:
	leaq	-48(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	timespec_get
	movl	-100(%rbp), %eax
	cltq
	movl	array(,%rax,4), %eax
	movl	%eax, -80(%rbp)
	leaq	-32(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	timespec_get
	movq	-24(%rbp), %rdx
	movq	-40(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -56(%rbp)
	movl	-100(%rbp), %eax
	cltq
	movq	-56(%rbp), %rdx
	movq	%rdx, arr(,%rax,8)
	movq	-56(%rbp), %rax
	addq	%rax, -72(%rbp)
	addl	$1, -104(%rbp)
	movl	-84(%rbp), %eax
	addl	%eax, -100(%rbp)
.L2:
	movl	arrLength(%rip), %eax
	cmpl	%eax, -100(%rbp)
	jl	.L3
	movq	-72(%rbp), %rax
	testq	%rax, %rax
	js	.L4
	pxor	%xmm0, %xmm0
	cvtsi2ssq	%rax, %xmm0
	jmp	.L5
.L4:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	pxor	%xmm0, %xmm0
	cvtsi2ssq	%rdx, %xmm0
	addss	%xmm0, %xmm0
.L5:
	pxor	%xmm1, %xmm1
	cvtsi2ss	-104(%rbp), %xmm1
	divss	%xmm1, %xmm0
	movss	%xmm0, -76(%rbp)
	cvtss2sd	-76(%rbp), %xmm0
	movl	$.LC0, %edi
	movl	$1, %eax
	call	printf
	movl	$0, -96(%rbp)
	jmp	.L6
.L11:
	movl	$0, -92(%rbp)
	movl	$0, -88(%rbp)
	jmp	.L7
.L9:
	movl	-88(%rbp), %eax
	cltq
	movq	arr(,%rax,8), %rdx
	movl	-96(%rbp), %eax
	cltq
	movq	arr(,%rax,8), %rax
	cmpq	%rax, %rdx
	jne	.L8
	addl	$1, -92(%rbp)
.L8:
	movl	-84(%rbp), %eax
	addl	%eax, -88(%rbp)
.L7:
	movl	arrLength(%rip), %eax
	cmpl	%eax, -88(%rbp)
	jl	.L9
	movl	-92(%rbp), %eax
	cmpl	-108(%rbp), %eax
	jle	.L10
	movl	-92(%rbp), %eax
	movl	%eax, -108(%rbp)
	movl	-96(%rbp), %eax
	cltq
	movq	arr(,%rax,8), %rax
	movq	%rax, -64(%rbp)
.L10:
	movl	-84(%rbp), %eax
	addl	%eax, -96(%rbp)
.L6:
	movl	arrLength(%rip), %eax
	cmpl	%eax, -96(%rbp)
	jl	.L11
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L13
	call	__stack_chk_fail
.L13:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
