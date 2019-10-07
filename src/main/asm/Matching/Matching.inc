


section '.data' data readable writeable align 16


	struc Match
		label .
		.flags dq 0		; Match flags
		.transformFlags dq 0	; Transform Flags
		.containsRangeList dq 0	; Contains or Range list (Contains X versus Range 0-200)
		.subRangeStartIndex dq 0	; Sub range start index
		.subRangeEndIndex dq 0	; Sub range end index
	end struc




	; Used with address offsets
	virtual at 0
		Match Match
	end virtual

	; ---- Structures
	;element Element

	

section '.text' code readable writeable executable align 16


matching:
namespace matching
matching.new:
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
	add rcx, Match.subRangeEndIndex
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [new.heapAddress]
	call [ HeapAlloc] 
	mov [new.handleAllocatedMemory], rax
	add rsp, 8*4




	mov rbx, [new.handleAllocatedMemory]
	add rbx, Match.flags
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Match.transformFlags
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Match.containsRangeList
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Match.subRangeStartIndex
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Match.subRangeEndIndex
	mov rax, 0
	mov [rbx], rax



	;lea rax, [new.list]
	;lea rcx, [new.list.indexedItemIndex]

	;sub rcx, rax
	;add rcx, 1000b

	;cld

	;lea rsi, [new.list]
	;mov rdi, [storage.new.handleAllocatedMemory]

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

matching.parseFlags:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label parseFlags.heapAddress qword at rbp-8  
	label parseFlags.handleAllocatedMemory qword at rbp-16
	label parseFlags.letterLength qword at rbp-24 
	label parseFlags.sizeWritten qword at rbp-32
	label parseFlags.matchAddr qword at rbp-40
	label parseFlags.letters qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parseFlags.matchAddr], rcx
	mov [parseFlags.letters], rdx


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


	





	mov rax, 0;	[parseFlags.recordAddr]


	parseFlags.end:


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