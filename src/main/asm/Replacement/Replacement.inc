


section '.data' data readable writeable align 16




	;Flags
	;REPLACE_INSERT	REPLACE_BETWEEN




section '.text' code readable writeable executable align 16


replacement:
namespace replacement
replacement.lettersWithList:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*20);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label lettersWithList.heapAddress qword at rbp-8  
	label lettersWithList.handleAllocatedMemory qword at rbp-16
	label lettersWithList.matchFlow qword at rbp-24 
	label lettersWithList.list qword at rbp-32
	label lettersWithList.matchAddr qword at rbp-40
	label lettersWithList.letters qword at rbp-48
	label lettersWithList.flags qword at rbp-56
	label lettersWithList.lettersAlloc qword at rbp-64
	label lettersWithList.matchingIndex qword at rbp-72
	label lettersWithList.matchResultsList qword at rbp-80
	label lettersWithList.startMatchFound qword at rbp-88
	label lettersWithList.matchFoundCount qword at rbp-96
	label lettersWithList.lettersLength qword at rbp-104
	label lettersWithList.matchingEnd qword at rbp-112
	label lettersWithList.startIndex qword at rbp-120
	label lettersWithList.endIndex qword at rbp-128
	label lettersWithList.lettersIndex qword at rbp-136
	label lettersWithList.newLetters qword at rbp-144
	label lettersWithList.nextListVal qword at rbp-152
	label lettersWithList.lettersBetweenIndices qword at rbp-160
	
	
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersWithList.flags], rcx
	mov [lettersWithList.letters], rdx
	mov [lettersWithList.list], r8
	mov [lettersWithList.matchResultsList], r9


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
	mov [lettersWithList.lettersIndex], rcx		; Begin as 0
	mov [lettersWithList.newLetters], rcx
	mov [lettersWithList.nextListVal], rcx


	

	mov r8, [lettersWithList.flags]
	bt r8, 0b					; REPLACE between
	jnc lettersWithList.replaceInsert		; Replace as insert at indices
	

	sub rsp, 8*8
	mov rcx, [lettersWithList.letters]
	call letters.letterLength
	add rsp, 8*8
	mov [lettersWithList.lettersLength], rax



	.nextMatchResult:
	mov rcx, [lettersWithList.lettersIndex]
	mov rdx, [lettersWithList.lettersLength]
	cmp rcx, rdx
	jnl lettersWithList.endMatchResultsList
	
	mov rbx,  [lettersWithList.matchResultsList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jl lettersWithList.replacingOrNotReplacingVal

	mov r10, [lettersWithList.lettersLength]
	mov r11,  [lettersWithList.lettersIndex]
	add r10, r11
	add r10, 1b								; Decreased later
	mov [lettersWithList.startIndex], r10



	jmp lettersWithList.nonReplacedVal

	.replacingOrNotReplacingVal:





	sub rsp, 8*8
	mov rcx, [lettersWithList.matchResultsList]
	call list.getNextItem
	add rsp, 8*8
	mov [lettersWithList.startIndex], rax


	sub rsp, 8*8
	mov rcx, [lettersWithList.matchResultsList]
	call list.getNextItem
	add rsp, 8*8
	mov [lettersWithList.endIndex], rax




	

	mov rcx, [lettersWithList.lettersIndex]
	mov rdx, [lettersWithList.startIndex]
	cmp rcx, rdx
	jnl lettersWithList.appendListVal
	.nonReplacedVal:

	mov rbx, [lettersWithList.matchResultsList]
	add rbx, List.index
	mov rcx, [rbx]
	sub rcx, 10b
	mov [rbx], rcx						; Go back since not used




	sub rsp, 8*8
	mov r8, [lettersWithList.startIndex]
	sub r8, 1b
	mov rdx, [lettersWithList.lettersIndex]
	mov rcx, [lettersWithList.letters]
	call letters.betweenIndices
	add rsp, 8*8
	mov [lettersWithList.lettersBetweenIndices], rax
	
	sub rsp, 8*8
	mov rdx, [lettersWithList.lettersBetweenIndices]
	mov rcx, [lettersWithList.newLetters]
	call letters.appendLetters
	add rsp, 8*8
	mov [lettersWithList.newLetters], rax

	sub rsp, 8*8
	mov rcx, [lettersWithList.lettersBetweenIndices]
	call letters.letterLength
	add rsp, 8*8
	mov r8, [lettersWithList.lettersIndex]
	add r8, rax
	mov [lettersWithList.lettersIndex], r8






	jmp lettersWithList.nextMatchResult
	.appendListVal:





	mov rbx, [lettersWithList.list]
	mov r9, rbx
	add rbx, List.index
	add r9, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r9]
	cmp rcx, rdx
	jl lettersWithList.getNextListVal

	sub rsp, 8*8
	mov rcx, [lettersWithList.list]
	call list.resetIndex
	add rsp, 8*8

	.getNextListVal:

	sub rsp, 8*8
	mov rcx, [lettersWithList.list]
	call list.getNextItem
	add rsp, 8*8
	mov [lettersWithList.nextListVal], rax


	sub rsp, 8*8
	mov rdx, [lettersWithList.nextListVal]
	mov rcx, [lettersWithList.newLetters]
	call letters.appendLetters
	add rsp, 8*8
	mov [lettersWithList.newLetters], rax




	mov rdx, [lettersWithList.endIndex]
	add rdx, 1b
	mov [lettersWithList.lettersIndex], rdx


	

	jmp lettersWithList.nextMatchResult
	.endMatchResultsList:


	.replaceInsert:					; TO-DO


	mov rax, [lettersWithList.newLetters]


	lettersWithList.end:


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

; Convenience wrapper around lettersWithList using contains assumptions
replacement.containsLettersWithList:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*20);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label containsLettersWithList.heapAddress qword at rbp-8  
	label containsLettersWithList.handleAllocatedMemory qword at rbp-16
	label containsLettersWithList.matchFlow qword at rbp-24 
	label containsLettersWithList.list qword at rbp-32
	label containsLettersWithList.matchAddr qword at rbp-40
	label containsLettersWithList.letters qword at rbp-48
	label containsLettersWithList.flags qword at rbp-56
	label containsLettersWithList.lettersAlloc qword at rbp-64
	label containsLettersWithList.matchingIndex qword at rbp-72
	label containsLettersWithList.matchResultsList qword at rbp-80
	label containsLettersWithList.startMatchFound qword at rbp-88
	label containsLettersWithList.matchFoundCount qword at rbp-96
	label containsLettersWithList.lettersLength qword at rbp-104
	label containsLettersWithList.matchingEnd qword at rbp-112
	label containsLettersWithList.startIndex qword at rbp-120
	label containsLettersWithList.endIndex qword at rbp-128
	label containsLettersWithList.containsLetters qword at rbp-136
	label containsLettersWithList.newLetters qword at rbp-144
	label containsLettersWithList.nextListVal qword at rbp-152
	label containsLettersWithList.lettersBetweenIndices qword at rbp-160
	
	
	;virtual at rbp-64
	;	.list List
	;end virtual	



	mov [containsLettersWithList.letters], rcx
	mov [containsLettersWithList.list], rdx
	mov [containsLettersWithList.containsLetters], r8


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
	call matching.new
	add rsp, 8*8	
	mov [containsLettersWithList.matchAddr], rax
	

	mov rbx, [containsLettersWithList.matchAddr]
	mov rdx, rbx
	add rbx, Matches.flags
	mov r8, 11011b							;MATCH_START  MATCH_END  MATCH_EVERY  MATCH_TRANSFORM
	mov [rbx], r8
	add rdx, Matches.transformFlags
	mov r9, 100b							;TRANSFORM_CONTAINS
	mov [rdx], r9
	
	sub rsp, 8*8
	mov rdx, [containsLettersWithList.containsLetters]
	mov rbx, [containsLettersWithList.matchAddr]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [containsLettersWithList.letters]
	mov rcx, [containsLettersWithList.matchAddr]
	call matching.get
	add rsp, 8*8



	sub rsp, 8*8
	mov r9, rax
	mov r8, [containsLettersWithList.list]
	mov rdx, [containsLettersWithList.letters]
	mov rcx, 1b 					; REPLACE_BETWEEN
	call lettersWithList
	add rsp, 8*8
	mov [containsLettersWithList.newLetters], rax





	.end:
	mov rax, [containsLettersWithList.newLetters]

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