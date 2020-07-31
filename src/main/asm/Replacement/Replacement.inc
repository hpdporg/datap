


section '.data' data readable writeable align 16




	;Flags
	;REPLACE_INSERT	REPLACE_BETWEEN




section '.text' code readable writeable executable align 16


replacement:
namespace replacement
lettersWithList:
namespace lettersWithList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*20);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label listAlloc qword at rbp-32
	label matchAddr qword at rbp-40
	label nextLetters qword at rbp-48
	label flags qword at rbp-56
	label lettersAlloc qword at rbp-64
	label matchingIndex qword at rbp-72
	label matchResultsList qword at rbp-80
	label startMatchFound qword at rbp-88
	label matchFoundCount qword at rbp-96
	label lettersLength qword at rbp-104
	label matchingEnd qword at rbp-112
	label startIndex qword at rbp-120
	label endIndex qword at rbp-128
	label lettersIndex qword at rbp-136
	label newLetters qword at rbp-144
	label nextListVal qword at rbp-152
	label lettersBetweenIndices qword at rbp-160
	
	
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [flags], rcx
	mov [lettersAlloc], rdx
	mov [listAlloc], r8
	mov [matchResultsList], r9


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
	mov [lettersIndex], rcx		; Begin as 0
	mov [newLetters], rcx
	mov [nextListVal], rcx


	

	mov r8, [flags]
	bt r8, 0b					; REPLACE between
	jnc replaceInsert		; Replace as insert at indices
	

	sub rsp, 8*8
	mov rcx, [lettersAlloc]
	call letters.letterLength
	add rsp, 8*8
	mov [lettersLength], rax



	nextMatchResult:
	mov rcx, [lettersIndex]
	mov rdx, [lettersLength]
	cmp rcx, rdx
	jnl endMatchResultsList
	
	mov rbx,  [matchResultsList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jl replacingOrNotReplacingVal

	mov r10, [lettersLength]
	mov r11,  [lettersIndex]
	add r10, r11
	add r10, 1b								; Decreased later
	mov [startIndex], r10



	jmp nonReplacedVal

	replacingOrNotReplacingVal:





	sub rsp, 8*8
	mov rcx, [matchResultsList]
	call list.getNextItem
	add rsp, 8*8
	mov [startIndex], rax


	sub rsp, 8*8
	mov rcx, [matchResultsList]
	call list.getNextItem
	add rsp, 8*8
	mov [endIndex], rax




	

	mov rcx, [lettersIndex]
	mov rdx, [startIndex]
	cmp rcx, rdx
	jnl appendListVal
	nonReplacedVal:

	mov rbx, [matchResultsList]
	add rbx, List.index
	mov rcx, [rbx]
	sub rcx, 10b
	mov [rbx], rcx						; Go back since not used




	sub rsp, 8*8
	mov r8, [startIndex]
	sub r8, 1b
	mov rdx, [lettersIndex]
	mov rcx, [lettersAlloc]
	call letters.betweenIndices
	add rsp, 8*8
	mov [lettersBetweenIndices], rax
	
	sub rsp, 8*8
	mov rdx, [lettersBetweenIndices]
	mov rcx, [newLetters]
	call letters.appendLetters
	add rsp, 8*8
	mov [newLetters], rax

	sub rsp, 8*8
	mov rcx, [lettersBetweenIndices]
	call letters.letterLength
	add rsp, 8*8
	mov r8, [lettersIndex]
	add r8, rax
	mov [lettersIndex], r8






	jmp nextMatchResult
	appendListVal:





	mov rbx, [listAlloc]
	mov r9, rbx
	add rbx, List.index
	add r9, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r9]
	cmp rcx, rdx
	jl getNextListVal

	sub rsp, 8*8
	mov rcx, [listAlloc]
	call list.resetIndex
	add rsp, 8*8

	getNextListVal:

	sub rsp, 8*8
	mov rcx, [listAlloc]
	call list.getNextItem
	add rsp, 8*8
	mov [nextListVal], rax


	sub rsp, 8*8
	mov rdx, [nextListVal]
	mov rcx, [newLetters]
	call letters.appendLetters
	add rsp, 8*8
	mov [newLetters], rax




	mov rdx, [endIndex]
	add rdx, 1b
	mov [lettersIndex], rdx


	

	jmp nextMatchResult
	endMatchResultsList:


	replaceInsert:					; TO-DO


	mov rax, [newLetters]


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

; Convenience wrapper around lettersWithList using contains assumptions
containsLettersWithList:
namespace containsLettersWithList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*20);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label containsheapAddress qword at rbp-8  
	label containshandleAllocatedMemory qword at rbp-16
	label containsmatchFlow qword at rbp-24 
	label containslist qword at rbp-32
	label containsmatchAddr qword at rbp-40
	label containsletters qword at rbp-48
	label containsflags qword at rbp-56
	label containslettersAlloc qword at rbp-64
	label containsmatchingIndex qword at rbp-72
	label containsmatchResultsList qword at rbp-80
	label containsstartMatchFound qword at rbp-88
	label containsmatchFoundCount qword at rbp-96
	label containslettersLength qword at rbp-104
	label containsmatchingEnd qword at rbp-112
	label containsstartIndex qword at rbp-120
	label containsendIndex qword at rbp-128
	label containscontainsLetters qword at rbp-136
	label containsnewLetters qword at rbp-144
	label containsnextListVal qword at rbp-152
	label containslettersBetweenIndices qword at rbp-160
	
	
	;virtual at rbp-64
	;	.list List
	;end virtual	



	mov [containsletters], rcx
	mov [containslist], rdx
	mov [containscontainsLetters], r8


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
	mov [containsmatchAddr], rax
	

	mov rbx, [containsmatchAddr]
	mov rdx, rbx
	add rbx, Matches.flags
	mov r8, 11011b							;MATCH_START  MATCH_END  MATCH_EVERY  MATCH_TRANSFORM
	mov [rbx], r8
	add rdx, Matches.transformFlags
	mov r9, 100b							;TRANSFORM_CONTAINS
	mov [rdx], r9
	
	sub rsp, 8*8
	mov rdx, [containscontainsLetters]
	mov rbx, [containsmatchAddr]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [containsletters]
	mov rcx, [containsmatchAddr]
	call matching.get
	add rsp, 8*8



	sub rsp, 8*8
	mov r9, rax
	mov r8, [containslist]
	mov rdx, [containsletters]
	mov rcx, 1b 					; REPLACE_BETWEEN
	call lettersWithList
	add rsp, 8*8
	mov [containsnewLetters], rax

	


	completed:
	mov rax, [containsnewLetters]

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

; containsLettersWithList but using Flow
; Contains Letters will be replaced using a List of Flow i (horizontal values)
; Result is a List the size of Flow length (j, row count)
containsLettersWithFlow:
namespace containsLettersWithFlow
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*20);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label containsheapAddress qword at rbp-8  
	label containshandleAllocatedMemory qword at rbp-16
	label containsmatchFlow qword at rbp-24 
	label containsList qword at rbp-32
	label containsmatchAddr qword at rbp-40
	label containsLetters qword at rbp-48
	label replacedLettersAlloc qword at rbp-56
	label lettersAddr qword at rbp-64
	label containsmatchingIndex qword at rbp-72
	label containsmatchResultsList qword at rbp-80
	label containsstartMatchFound qword at rbp-88
	label containsmatchFoundCount qword at rbp-96
	label containslettersLength qword at rbp-104
	label containsmatchingEnd qword at rbp-112
	label containsstartIndex qword at rbp-120
	label containsendIndex qword at rbp-128
	label containscontainsLetters qword at rbp-136
	label replacedLettersList qword at rbp-144
	label flowAddr qword at rbp-152
	label containslettersBetweenIndices qword at rbp-160
	
	
	;virtual at rbp-64
	;	.list List
	;end virtual	



	mov [lettersAddr], rcx
	mov [flowAddr], rdx
	mov [containsLetters], r8



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
	call list.new
	add rsp, 8*8
	mov [replacedLettersList], rax



	sub rsp, 8*8
	mov rcx, [flowAddr]
	call flow.resetIJ
	add rsp, 8*8



	nextFlowJReplaceItems:
	mov r11, [flowAddr]
	mov r12, r11
	add r11, Flow.j
	add r12, Flow.length
	mov rcx, [r11]
	mov rdx, [r12]
	cmp rcx, rdx
	jnl endFlowJReplaceItems




	sub rsp, 8*8
	mov rcx, [flowAddr]
	call flow.getNextJVals
	add rsp, 8*8
	mov [containsList], rax


	sub rsp, 8*8
	mov r8, [containsLetters]
	mov rdx, [containsList]
	mov rcx, [lettersAddr]
	call containsLettersWithList
	add rsp, 8*8
	mov [replacedLettersAlloc], rax



	sub rsp, 8*8
	mov rdx, [replacedLettersAlloc]
	mov rcx, [replacedLettersList]
	call list.newLastItem
	add rsp, 8*8


	jmp nextFlowJReplaceItems
	endFlowJReplaceItems:




	completed:
	mov rax, [replacedLettersList]

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