

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
	storage.filePathAddr dq 0

section '.text' code readable writeable executable align 16


; storage.defineFilePath
; storage.newFile

allocate:
namespace allocate
.linearAllocate:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label storage.newFile.handleAddr qword at rbp-8  
	label storage.newFile.filePath qword at rbp-16
	;virtual at rbp-64
	;	.list List
	;end virtual	

	mov [storage.newFile.filePath], rcx

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



	sub rsp, 8*4
	call [GetProcessHeap]
	mov [list.new.heapAddress], rax
	add rsp, 8*4
	

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [linearAllocate.heapAddress]
	call [ HeapAlloc] 
	mov [linearAllocate.handleAllocatedMemory], rax
	add rsp, 8*4

	mov rax, [linearAllocate.handleAllocatedMemory]


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