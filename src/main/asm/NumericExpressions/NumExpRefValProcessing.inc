


section '.text' code readable writeable executable align 16



namespace numExpRefVal

process:
namespace process
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label matchIndexCount qword at rbp-32
	label numExpAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label expExtList qword at rbp-56
	label valLoc qword at rbp-64
	label numExpTermListAddr qword at rbp-72
	label condExpTermListAddr qword at rbp-80
	label defExpTermListAddr qword at rbp-88
	label labelAllocLoc qword at rbp-96
	label numExpRefValLoc qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [numExpRefValLoc], rcx
	

	and rsp, -32
	push rbx 
	push rbp 
	push rdi 
	push rsi
	push rsp 
	push r12 
	push r13 
	push r14 
	push r15
	sub rsp, 8

	mov rbx, [numExpRefValLoc]
	add rbx, NumExpRefVal.labelAlloc
	mov r11, [rbx]
	mov [labelAllocLoc],r11			; Cache


	mov rbx, [numExpRefValLoc]
	add rbx, NumExpRefVal.flags
	mov rdx, [rbx]
	mov rcx, 10b				; ; NUM_EXP_REF_VAL_INTEGER	10b			1	; 8498
	and rcx, rdx
	cmp rcx, 0
	je notInteger
	
	sub rsp, 8*8
	mov rcx, [labelAllocLoc]
	call letters.lettersAsNum
	add rsp, 8*8
	mov [valLoc], rax

	jmp valProcessed
	notInteger:

	;je notFloat
	;call matching.extractBetween

	;ref
	;rep cmpne abcdefgh

	valProcessed:


	mov rbx, [numExpRefValLoc]
	add rbx, NumExpRefVal.val
	mov r12, [valLoc]
	mov [rbx], r12





	completed:

	mov rax, 0



	add rsp, 8	
	pop r15 
	pop r14 
	pop r13 
	pop r12 
	pop rsp 
	pop rsi 
	pop rdi 
	pop rbp 
	pop rbx

	mov rsp, rbp
	pop rbp

	retn 0
end namespace





end namespace