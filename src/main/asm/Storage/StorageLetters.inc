


;section '.data' data readable writeable align 16



	

section '.text' code readable writeable executable align 16




namespace storage


retrieveLetters:
namespace retrieveLetters
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label listAddr qword at rbp-24 
	label item qword at rbp-32
	label recordAddr qword at rbp-40
	label sizeretrieved qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [recordAddr], rcx


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

	sub rsp, 8*8
	mov rbx, [recordAddr]
	add rbx, Record.allocSize
	mov rdx, [rbx]
	mov rbx, [recordAddr]
	add rbx, Record.allocAddr
	mov rcx, [rbx]
	call letters.appendZero
	add rsp, 8*8

	mov rbx, [recordAddr]
	add rbx, Record.allocAddr
	mov [rbx], rax

	mov rbx, [recordAddr]
	add rbx, Record.allocSize
	mov r8, [rbx]
	add r8, 1b
	mov [rbx], r8

	



	mov rax, [recordAddr]
	
	completed:


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