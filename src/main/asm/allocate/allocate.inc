

section '.data' data readable writeable align 16



	;struc File{
	;	.text			dq 0		;
	;}
	


	; Used with address offsets
	;virtual at 0
	;	Element Element
	;end virtual

	; ---- Structures
	;element Element


	fileAddr db 'C:\Users\lewis\Desktop\1100111b.txt',0
	fileHandleAddr dq 0
	fileValue db 'A',0
	fileValue2 db 'B',0
	bytesWritten dq 0
	valueSize dq 0
	;newElementMsg db 'New Element',0
	filePathAddr dq 0

section '.text' code readable writeable executable align 16


; defineFilePath
; newFile

allocate:
namespace allocate
linear:
namespace linear
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*3);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label handleAddr qword at rbp-8  
	label size qword at rbp-16
	label heapAddress qword at rbp-24
	;virtual at rbp-64
	;	.list List
	;end virtual	

	mov [size], rcx

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
	call [GetProcessHeap]
	mov [heapAddress], rax
	add rsp, 8*8
	

	sub rsp, 8*8
	mov r8, [size]	
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAddr], rax
	add rsp, 8*8

	mov rax, [handleAddr]


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

; Takes last member offset as a param i.e. strucName.member5
new:
namespace new
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*3);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label size qword at rbp-24
	;virtual at rbp-64
	;	.list List
	;end virtual	

	mov [size], rcx			; Last Member offset

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


	mov rdx, [size]
	mov rcx, 0
	add rcx, rdx
	add rcx, 1000b
	mov [size], rcx

	sub rsp, 8*4
	call [GetProcessHeap]
	mov [heapAddress], rax
	add rsp, 8*4
	

	sub rsp, 8*4
	mov r8, [size]
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4



	mov rcx, [size]
	cld
	mov rax, 0

	mov rdi, [handleAllocatedMemory]

	rep stosb					; Zero out (initialize).


	mov rax, [handleAllocatedMemory]


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