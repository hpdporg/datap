


section '.data' data readable writeable align 16


	struc NumericExpression
		label .
		.numericConditionFlag dq 0		; 0: Numeric 1: Condition
		.expressionAlloc dq 0			; Expression alloc unparsed
		.expressionExtractList dq 0		; Tokenized expression
		.refsList dq 0				; Refs may need values replaced. refValuesList has final vals
		.refValuesList dq 0			; Last list
		.expressionFlags dq 0			; NUM_EXP_ Expression flags
	end struc


	; NUM_EXP_ Flags
	; NUM_EXP_MORE		1b			0	; ref1 > ref2
	; NUM_EXP_LESS		10b			1	; ref1 < ref2
	; NUM_EXP_SAME		100b			2	; ref1 same ref2
	; NUM_EXP_DEF_ONLY	1000b			3	; = ref1
	; NUM_EXP_DEF_NUM	10000b			4	; = ref1 + 100
	; NUM_EXP_CONTAINS	100000b			5	; ref1 contains ref2
	; NUM_EXP_WITHIN	1000000b		6	; ref1 within ref2


	; refs can contain terms before:
		; first	ref1
		; average ref1
		; last ref1

	; Used with address offsets
	virtual at 0
		NumericExpression NumericExpression
	end virtual

	; ---- Structures
	;element Element


	; ---- Structures
	;element Element






	

	

section '.text' code readable writeable executable align 16


filtering:
namespace filtering
filtering.new:
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
	add rcx, Matches.subRangeEndIndex
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [new.heapAddress]
	call [ HeapAlloc] 
	mov [new.handleAllocatedMemory], rax
	add rsp, 8*4




	mov rbx, [new.handleAllocatedMemory]
	add rbx, Matches.flags
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Matches.transformFlags
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Matches.containsRangeList
	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Matches.subRangeStartIndex
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Matches.subRangeEndIndex
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


matching.processFlags:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label processFlags.heapAddress qword at rbp-8  
	label processFlags.handleAllocatedMemory qword at rbp-16
	label processFlags.matchFlow qword at rbp-24 
	label processFlags.matchIndexCount qword at rbp-32
	label processFlags.matchAddr qword at rbp-40
	label processFlags.letters qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processFlags.matchAddr], rcx
	

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
	call newMatchFlow
	add rsp, 8*8
	mov [processFlags.matchFlow], rax


	mov rcx, 0
	mov [processFlags.matchIndexCount], rcx		; Begin as 0

	mov rbx, [processFlags.matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 0					; MATCH_START	
	jnc processFlags.endIndex

	mov rbx, [processFlags.matchFlow]
	add rbx, MatchFlow.start
	mov rcx, 1b
	mov [rbx], rcx

	mov rcx, 1b
	mov rdx, [processFlags.matchIndexCount]
	add rdx, rcx
	mov [processFlags.matchIndexCount], rdx		; Increment


	.endIndex:
	mov rbx, [processFlags.matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 1b					; MATCH_END
	jnc processFlags.matchFirstOrEvery	

	mov rbx, [processFlags.matchFlow]
	add rbx, MatchFlow.end
	mov rcx, 1b
	mov [rbx], rcx

	mov rdx, [processFlags.matchFlow]
	add rdx, MatchFlow.start
	mov r8, [rdx]
	cmp r8, 0
	je processFlags.endOnly

	mov rbx, [processFlags.matchFlow]
	add rbx, MatchFlow.startEndLength		; MATCH start and end (length of contains)
	mov rcx, 1b
	mov [rbx], rcx


	.endOnly:

	mov rcx, 1b
	mov rdx, [processFlags.matchIndexCount]
	add rdx, rcx
	mov [processFlags.matchIndexCount], rdx		; Increment
	

	.matchFirstOrEvery:

	mov rbx, [processFlags.matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 10b					; MATCH_FIRST
	jnc processFlags.everyMatch


	mov rbx, [processFlags.matchFlow]
	add rbx, MatchFlow.firstMatch
	mov rcx, 1b
	mov [rbx], rcx

	jmp processFlags.hasTransform

	.everyMatch:
	mov rbx, [processFlags.matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 11b					; MATCH_EVERY
	jnc processFlags.hasTransform

	
	mov rbx, [processFlags.matchFlow]
	add rbx, MatchFlow.everyMatch
	mov rcx, 1b
	mov [rbx], rcx



	.hasTransform:
	mov rbx, [processFlags.matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 100b					; MATCH_TRANSFORM
	jnc processFlags.defineMatchIndexCounts

	
	mov rbx, [processFlags.matchAddr]
	add rbx, Matches.transformFlags
	mov r8, [rbx]
	bt r8, 10b					; TRANSFORM_CONTAINS
	jnc processFlags.defineMatchIndexCounts	

	mov rbx, [processFlags.matchFlow]
	add rbx, MatchFlow.contains
	mov rcx, 1b
	mov [rbx], rcx

	.defineMatchIndexCounts:

	mov rdx, [processFlags.matchIndexCount]
	mov rbx, [processFlags.matchFlow]
	add rbx, MatchFlow.matchIndexCount
	mov [rbx], rdx

	.end:

	mov rax, [processFlags.matchFlow]



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