
section '.data' data readable writeable


	struc Flow
		label .
		.lists dq 0
		.width dq 0				; Max width: List count
		.i dq 0					; List index
		.j dq 0					; List item index
		.length dq 0				; Max length: Greatest List item count.
		.paddingValue dq 0			; Defaults 0
	end struc	
	


	; Used with address offsets
	virtual at 0
		Flow Flow
	end virtual


	; ---- Structures
	;list List


	;newSVGMsg db 'New SVG',0
	
		
section '.text' code readable writeable executable ;align 16



flow:
namespace flow
flow.new:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label new.heapAddress qword at rbp-8  
	label new.handleAllocatedMemory qword at rbp-16
	;virtual at rbp-64
	;	.list List
	;end virtual	



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
	mov [new.heapAddress], rax
	add rsp, 8*4
	

	mov rcx, 0
	add rcx, Flow.paddingValue
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [new.heapAddress]
	call [ HeapAlloc] 
	mov [new.handleAllocatedMemory], rax
	add rsp, 8*4


	mov rbx, [new.handleAllocatedMemory]
	add rbx, Flow.lists
	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Flow.width
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Flow.i
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Flow.j
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Flow.length
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Flow.paddingValue
	mov rax, 0
	mov [rbx], rax
	mov rax, 0
	mov [rbx], rax


	;lea rax, [new.list]
	;lea rcx, [new.list.indexedItemIndex]

	;sub rcx, rax
	;add rcx, 1000b

	;cld

	;lea rsi, [new.list]
	;mov rdi, [list.new.handleAllocatedMemory]

	;rep movsb


	mov rax, [new.handleAllocatedMemory]


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





; Called by flow.increaseWidth
; Increments Flow.width. Increases Flow.length if applicable
flow.newLastList:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label newLastList.heapAddress qword at rbp-8  
	label newLastList.handleAllocatedMemory qword at rbp-16
	label newLastList.list qword at rbp-24 
	label newLastList.flow qword at rbp-32
	label newLastList.prevItem qword at rbp-40
	label newLastList.priorIndex qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [newLastList.flow], rcx
	mov [newLastList.list], rdx


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
	mov rdx, [newLastList.list]
	mov rbx, [newLastList.flow]
	add rbx, Flow.lists
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8


;	struc Flow
;		label .
;		.lists dq 0
;		.width dq 0				; Max width: List count
;		.i dq 0					; List index
;		.j dq 0					; List item index
;		.length dq 0				; Max length: Greatest List item count.
;		.paddingValue dq 0			; Defaults 0
;	end struc	


	mov rbx, [newLastList.flow]
	add rbx, Flow.width
	mov rcx, [rbx]
	add rcx, 1b
	mov [rbx], rcx					; Increment

	mov rdx, [newLastList.list]
	add rdx, List.itemsCount
	mov rcx, [rdx]
	mov rbx, [newLastList.flow]
	add rbx, Flow.length
	mov r8, [rbx]

	cmp rcx, r8
	jle newLastList.flowLengthNotIncreased
	
	mov [rbx], rcx					; Length increased when greater


	.flowLengthNotIncreased:

	.end:

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


; Builds new List, passes to Flow
; Calls flow.newLastList
; Takes Flow reference, length value as parameters
flow.increaseWidth:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label increaseWidth.heapAddress qword at rbp-8  
	label increaseWidth.handleAllocatedMemory qword at rbp-16
	label increaseWidth.list qword at rbp-24 
	label increaseWidth.flow qword at rbp-32
	label increaseWidth.index qword at rbp-40
	label increaseWidth.length qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [increaseWidth.flow], rcx
	mov [increaseWidth.length], rdx


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


	mov rcx, 0
	mov [increaseWidth.index], rcx			; Begin as 0


	.nextList:
	mov rcx, [increaseWidth.index]
	mov rdx, [increaseWidth.length]
	cmp rcx, rdx
	jnl increaseWidth.increased


	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	sub rsp, 8*8
	mov rdx, rax
	mov rcx, [increaseWidth.flow]
	call flow.newLastList
	add rsp, 8*8


	mov rcx, [increaseWidth.index]
	add rcx, 1b
	mov [increaseWidth.index], rcx

	jmp increaseWidth.nextList
	.increased:





	.end:

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