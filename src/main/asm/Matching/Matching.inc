


section '.data' data readable writeable align 16


	struc Matches
		label .
		.flags dq 0		; Matches flags
		.transformFlags dq 0	; Transform Flags
		.containsRangeList dq 0	; Contains or Range list (Contains X versus Range 0-200)
		.subRangeStartIndex dq 0	; Sub range start index
		.subRangeEndIndex dq 0	; Sub range end index
	end struc


	;Flags
	;MATCH_SUBRANGE_END_IND	MATCH_SUBRANGE_START_IND	MATCH_SUBRANGE	MATCH_TRANSFORM	MATCH_EVERY	MATCH_FIRST	MATCH_END	MATCH_START

	;Transform Flags
	;TRANSFORM_CONTAIN_OPTIONAL_COUNT	TRANSFORM_CONTAINS_SEQUENTIAL	TRANSFORM_ENDS_WITH	TRANSFORM_STARTS_WITH	TRANSFORM_CONTAINS_DISCONTINUOUS	TRANSFORM_EXCLUDES	TRANSFORM_CONTAINS	TRANSFORM_RANGE	TRANSFORM_INSENSITIVE_CASE



	struc MatchFlow
		label .
		.contains dq 0		; Contains flow
		.start dq 0		; Start match
		.end dq 0		; End match
		.firstMatch dq 0	; Contains first Match flow
		.everyMatch dq 0	; Contains every Match flow
		.matchIndexCount dq 0	; Required match index count minimum or maximum
		.startEndLength dq 0	; Start and ends matched i.e. length
	end struc



	; Used with address offsets
	virtual at 0
		Matches Matches
	end virtual

	; ---- Structures
	;element Element

	; Used with address offsets
	virtual at 0
		MatchFlow MatchFlow
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

matching.newMatchFlow:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label newMatchFlow.heapAddress qword at rbp-8  
	label newMatchFlow.handleAllocatedMemory qword at rbp-16
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
	mov [newMatchFlow.heapAddress], rax
	add rsp, 8*4
	

	mov rcx, 0
	add rcx, MatchFlow.startEndLength
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [newMatchFlow.heapAddress]
	call [ HeapAlloc] 
	mov [newMatchFlow.handleAllocatedMemory], rax
	add rsp, 8*4




	mov rbx, [newMatchFlow.handleAllocatedMemory]
	add rbx, MatchFlow.contains
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newMatchFlow.handleAllocatedMemory]
	add rbx, MatchFlow.start
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newMatchFlow.handleAllocatedMemory]
	add rbx, MatchFlow.end
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newMatchFlow.handleAllocatedMemory]
	add rbx, MatchFlow.firstMatch
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newMatchFlow.handleAllocatedMemory]
	add rbx, MatchFlow.everyMatch
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newMatchFlow.handleAllocatedMemory]
	add rbx, MatchFlow.matchIndexCount
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newMatchFlow.handleAllocatedMemory]
	add rbx, MatchFlow.startEndLength
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


	mov rax, [newMatchFlow.handleAllocatedMemory]


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



matching.get:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label get.heapAddress qword at rbp-8  
	label get.handleAllocatedMemory qword at rbp-16
	label get.matchFlow qword at rbp-24 
	label get.list qword at rbp-32
	label get.matchAddr qword at rbp-40
	label get.letters qword at rbp-48
	label get.containsRangeList qword at rbp-56
	label get.containsAddr qword at rbp-64
	label get.matchingIndex qword at rbp-72
	label get.containsLength qword at rbp-80
	label get.startMatchFound qword at rbp-88
	label get.matchFoundCount qword at rbp-96
	label get.lettersLength qword at rbp-104
	label get.matchingEnd qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [get.matchAddr], rcx
	mov [get.letters], rdx


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
	mov [get.heapAddress], rax
	add rsp, 8*4

	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [get.list], rax


	sub rsp, 8*8
	mov rcx, [get.letters]
	call letters.letterLength
	add rsp, 8*8
	mov [get.lettersLength], rax



	mov rbx, [get.matchAddr]
	add rbx, Matches.containsRangeList
	mov rdx, [rbx]
	mov [get.containsRangeList], rdx



	sub rsp, 8*8
	mov rcx, [get.matchAddr]
	call matching.processFlags
	add rsp, 8*8
	mov [get.matchFlow], rax
	

	mov rbx, [get.matchFlow]
	add rbx, MatchFlow.contains
	mov r8, [rbx]
	bt r8, 0b					; Match contains
	jnc get.endMatching				; Until others are supported

	
	mov rcx, 0
	mov [get.matchingIndex], rcx			; Begin at 0
	mov rcx, 0
	mov [get.matchFoundCount], rcx			; Begin as 0
	mov rcx, 0
	mov [get.startMatchFound], rcx			; Begin as 0


	get.nextMatch:


	mov rcx, [get.matchingIndex]
	mov rdx, [get.lettersLength]
	cmp rcx, rdx
	jnl get.endMatching

	mov rbx, [get.matchFlow]
	add rbx, MatchFlow.firstMatch
	mov r8, [rbx]
	bt r8, 0b					; Match firstMatch
	jnc get.matchEvery


	mov rbx, [get.matchFlow]
	add rbx, MatchFlow.matchIndexCount
	mov r8, [rbx]
	mov rdx, [get.matchFoundCount]
	cmp r8, rdx					; Already reached start & end when required?
	je get.endMatching


	get.matchEvery:


	.matchingEndOrStart:

	mov rbx, [get.matchFlow]
	add rbx, MatchFlow.start
	mov r8, [rbx]
	bt r8, 0b					; Match start
	jnc get.matchEnd				; Only match end

	mov rbx, [get.startMatchFound]
	mov rcx, 1b
	cmp rcx, rbx
	je get.matchEnd

	mov rcx, 0
	mov [get.matchingEnd], rcx


	jmp get.nextContains
	get.matchEnd:

	mov rbx, [get.matchFlow]
	add rbx, MatchFlow.end
	mov r8, [rbx]
	bt r8, 0b					; Match end
	jnc get.nextContains				; Only match start


	mov rcx, 1b
	mov [get.matchingEnd], rcx


	get.nextContains:
	mov rbx, [get.containsRangeList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl get.endContains


	sub rsp, 8*8
	mov rcx, [get.containsRangeList]
	call list.getNextItem
	add rsp, 8*8
	mov [get.containsAddr], rax


	sub rsp, 8*8
	mov rcx, [get.containsAddr]
	call letters.letterLength
	add rsp, 8*8
	mov [get.containsLength], rax


	mov rcx, [get.matchingIndex]
	mov [get.containsLength], rax
	add rcx, rax
	mov rdx, [get.lettersLength]
	cmp rcx, rdx					; Lengths less than or equal
	jnle get.nextContains


	cld

	mov rdi, [get.containsAddr]
	mov rsi, [get.letters]
	mov r8, [get.matchingIndex]
	add rsi, r8
	
	mov rcx, [get.containsLength]

	repe cmpsb

	jnz get.nextMatch				; noMatch


	.matchFound:

	

	mov rdx, [get.matchingEnd]
	mov rcx, 1b
	cmp rcx, rdx
	jne get.matchingStart

	mov rbx, [get.matchingIndex]
	mov rcx, [get.containsLength]
	sub rcx, 1b
	add rbx, rcx
	mov rdx, rbx
	
	jmp get.newMatchListItem

	.matchingStart:	

	mov rdx, [get.matchingIndex]


	get.newMatchListItem:

	sub rsp, 8*8
	;mov rdx,[get.containsLength]
	mov rcx, [get.list]
	call list.newLastItem
	add rsp, 8*8

	mov rbx, [get.matchFoundCount]
	add rbx, 1b
	mov [get.matchFoundCount], rbx

	mov rbx, [get.matchFlow]
	add rbx, MatchFlow.startEndLength
	mov r8, [rbx]
	bt r8, 0b					; Match start end length
	jnc get.notMatchingStartEndLength		

	sub rsp, 8*8
	mov rbx, [get.matchingIndex]
	mov rcx, [get.containsLength]
	sub rcx, 1b
	add rbx, rcx
	mov rdx, rbx
	mov rcx, [get.list]
	call list.newLastItem
	add rsp, 8*8

	mov rbx, [get.matchFoundCount]
	add rbx, 1b
	mov [get.matchFoundCount], rbx

	mov rcx, 1b
	mov [get.startMatchFound], rcx

	.notMatchingStartEndLength:

	mov rcx, 1b
	mov r8, 0
	mov rbx, [get.startMatchFound]
	cmp rbx, rcx
	je get.clearMatchStartFound		; Either way, invert

	mov [get.startMatchFound], rcx

	jmp get.increaseMatchingIndex
	.clearMatchStartFound:

	mov [get.startMatchFound], r8


	.increaseMatchingIndex:


	mov rbx, [get.matchingIndex]
	mov rcx, [get.containsLength]
	add rbx, rcx
	mov [get.matchingIndex], rbx		; Increase by 1 when no match, containsLength when match

	jmp get.resetContains


	get.endContains:

	mov rbx, [get.matchingIndex]
	mov rcx, 1b
	add rbx, rcx
	mov [get.matchingIndex], rbx		; Increase by 1 when no match, containsLength when match

	get.resetContains:
	

	sub rsp, 8*8
	mov rcx, [get.containsRangeList]
	call list.resetIndex
	add rsp, 8*8


	jmp get.nextMatch





	get.endMatching:

	sub rsp, 8*8
	mov r8, [get.matchFlow]
	mov rdx, 0
	mov rcx, [get.heapAddress]
	call [HeapFree]
	add rsp, 8*8

	mov rax, [get.list]


	get.end:


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

; Returns match results with 0 items when letters not same
; Returns greater than 0 items in List results when match

matching.lettersSame:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label lettersSame.heapAddress qword at rbp-8  
	label lettersSame.handleAllocatedMemory qword at rbp-16
	label lettersSame.matchFlow qword at rbp-24 
	label lettersSame.list qword at rbp-32
	label lettersSame.matches qword at rbp-40
	label lettersSame.letters qword at rbp-48
	label lettersSame.containsRangeList qword at rbp-56
	label lettersSame.containsAddr qword at rbp-64
	label lettersSame.matchingIndex qword at rbp-72
	label lettersSame.containLetters qword at rbp-80
	label lettersSame.startMatchFound qword at rbp-88
	label lettersSame.matchFoundCount qword at rbp-96
	label lettersSame.lettersLength qword at rbp-104
	label lettersSame.matchingEnd qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersSame.letters], rcx
	mov [lettersSame.containLetters], rdx


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
	call new
	add rsp, 8*8
	mov [lettersSame.matches], rax

	mov rbx, [lettersSame.matches]
	add rbx, Matches.flags
	mov r8, 10001b
	mov [rbx], r8

	mov rbx, [lettersSame.matches]
	add rbx, Matches.transformFlags
	mov r8, 100b
	mov [rbx], r8

	sub rsp, 8*8
	mov rdx, [lettersSame.containLetters]
	mov rbx, [lettersSame.matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [lettersSame.letters]
	mov rcx, [lettersSame.matches]
	call get
	add rsp, 8*8
	mov rax, rax


	lettersSame.end:


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


; Returns 0 when letters not same, and not same lengths
; Returns 1

matching.lettersSameExact:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label lettersSameExact.heapAddress qword at rbp-8  
	label lettersSameExact.handleAllocatedMemory qword at rbp-16
	label lettersSameExact.matchFlow qword at rbp-24 
	label lettersSameExact.list qword at rbp-32
	label lettersSameExact.matches qword at rbp-40
	label lettersSameExact.letters qword at rbp-48
	label lettersSameExact.containsRangeList qword at rbp-56
	label lettersSameExact.containsAddr qword at rbp-64
	label lettersSameExact.matchResult qword at rbp-72
	label lettersSameExact.containLetters qword at rbp-80
	label lettersSameExact.length1 qword at rbp-88
	label lettersSameExact.length2 qword at rbp-96
	label lettersSameExact.lettersLength qword at rbp-104
	label lettersSameExact.matchingEnd qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersSameExact.letters], rcx
	mov [lettersSameExact.containLetters], rdx


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
	mov [lettersSameExact.matchResult], rcx			; Begin as 0

	sub rsp, 8*8
	mov rcx, [lettersSameExact.letters]
	call letters.letterLength
	add rsp, 8*8
	mov [lettersSameExact.length1], rax

	;sub rsp, 8*8
	;mov rcx, [lettersSameExact.length1]
	;call storage.debugNumMsg
	;add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [lettersSameExact.containLetters]
	call letters.letterLength
	add rsp, 8*8
	mov [lettersSameExact.length2], rax

	;sub rsp, 8*8
	;mov rcx, [lettersSameExact.length2]
	;call storage.debugNumMsg
	;add rsp, 8*8

	
	mov rcx, [lettersSameExact.length1]
	mov rdx, [lettersSameExact.length2]
	cmp rcx, rdx
	je lettersSameExact.sameLength

	sub rsp, 8*8
	call list.new
	add rsp, 8*8

	add rax, List.itemsCount
	mov rdx, [rax]
	mov [lettersSameExact.matchResult], rdx



	jmp lettersSameExact.end


	.sameLength:


	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [lettersSameExact.matches], rax

	mov rbx, [lettersSameExact.matches]
	add rbx, Matches.flags
	mov r8, 10001b
	mov [rbx], r8

	mov rbx, [lettersSameExact.matches]
	add rbx, Matches.transformFlags
	mov r8, 100b
	mov [rbx], r8

	sub rsp, 8*8
	mov rdx, [lettersSameExact.containLetters]
	mov rbx, [lettersSameExact.matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [lettersSameExact.letters]
	mov rcx, [lettersSameExact.matches]
	call get
	add rsp, 8*8
	mov rax, rax

	add rax, List.itemsCount
	mov rdx, [rax]
	mov [lettersSameExact.matchResult], rdx


	lettersSameExact.end:

	mov rax, [lettersSameExact.matchResult]


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


matching.getNextIndex:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getNextIndex.heapAddress qword at rbp-8  
	label getNextIndex.handleAllocatedMemory qword at rbp-16
	label getNextIndex.matchFlow qword at rbp-24 
	label getNextIndex.list qword at rbp-32
	label getNextIndex.matches qword at rbp-40
	label getNextIndex.letters qword at rbp-48
	label getNextIndex.containsRangeList qword at rbp-56
	label getNextIndex.containsAddr qword at rbp-64
	label getNextIndex.matchingIndex qword at rbp-72
	label getNextIndex.containLetters qword at rbp-80
	label getNextIndex.matchIndex qword at rbp-88
	label getNextIndex.matchList qword at rbp-96
	label getNextIndex.lettersLength qword at rbp-104
	label getNextIndex.matchingEnd qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getNextIndex.letters], rcx
	mov [getNextIndex.containLetters], rdx


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
	mov [getNextIndex.heapAddress], rax
	add rsp, 8*4




	mov rcx, 0
	mov [getNextIndex.matchIndex], rcx			; Begin as 0

	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [getNextIndex.matches], rax

	mov rbx, [getNextIndex.matches]
	add rbx, Matches.flags
	mov rcx, 10101b
	mov [rbx], rcx
	mov rbx, [getNextIndex.matches]
	add rbx, Matches.transformFlags
	mov rcx, 100b
	mov [rbx], rcx


	sub rsp, 8*8
	mov rdx, [getNextIndex.containLetters]
	mov rbx, [getNextIndex.matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [getNextIndex.letters]
	mov rcx, [getNextIndex.matches]
	call get
	add rsp, 8*8
	mov [getNextIndex.matchList], rax


	mov rbx,[getNextIndex.matchList]
	add rbx, List.itemsCount
	mov rcx, 0
	mov rdx, [rbx]
	cmp rcx, rdx
	je getNextIndex.end				; No match

	
	sub rsp, 8*8
	mov rcx, [getNextIndex.matchList]
	call list.getNextItem
	add rsp, 8*8
	mov [getNextIndex.matchIndex], rax



	.end:

	sub rsp, 8*8
	mov r8, [getNextIndex.matches]
	mov rdx, 0
	mov rcx, [getNextIndex.heapAddress]
	call [HeapFree]
	add rsp, 8*8


	mov rax, [getNextIndex.matchIndex]



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


matching.hasMatch:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label hasMatch.heapAddress qword at rbp-8  
	label hasMatch.handleAllocatedMemory qword at rbp-16
	label hasMatch.matchFlow qword at rbp-24 
	label hasMatch.list qword at rbp-32
	label hasMatch.matches qword at rbp-40
	label hasMatch.letters qword at rbp-48
	label hasMatch.containsRangeList qword at rbp-56
	label hasMatch.containsAddr qword at rbp-64
	label hasMatch.matchingIndex qword at rbp-72
	label hasMatch.containLetters qword at rbp-80
	label hasMatch.hasMatchIndex qword at rbp-88
	label hasMatch.matchList qword at rbp-96
	label hasMatch.lettersLength qword at rbp-104
	label hasMatch.matchingEnd qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [hasMatch.letters], rcx
	mov [hasMatch.containLetters], rdx


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
	mov [hasMatch.heapAddress], rax
	add rsp, 8*4





	mov rcx, 0
	mov [hasMatch.hasMatchIndex], rcx			; Begin as 0

	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [hasMatch.matches], rax

	mov rbx, [hasMatch.matches]
	add rbx, Matches.flags
	mov rcx, 10101b
	mov [rbx], rcx
	mov rbx, [hasMatch.matches]
	add rbx, Matches.transformFlags
	mov rcx, 100b
	mov [rbx], rcx


	sub rsp, 8*8
	mov rdx, [hasMatch.containLetters]
	mov rbx, [hasMatch.matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [hasMatch.letters]
	mov rcx, [hasMatch.matches]
	call get
	add rsp, 8*8
	mov [hasMatch.matchList], rax


	mov rbx,[hasMatch.matchList]
	add rbx, List.itemsCount
	mov rcx, 0
	mov rdx, [rbx]
	cmp rcx, rdx
	je hasMatch.end				; No match

	mov rcx, 1b
	mov [hasMatch.hasMatchIndex], rcx



	.end:

	sub rsp, 8*8
	mov r8, [hasMatch.matches]
	mov rdx, 0
	mov rcx, [hasMatch.heapAddress]
	call [HeapFree]
	add rsp, 8*8


	mov rax, [hasMatch.hasMatchIndex]



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

; Extract list of matches between a delimiter
; Tokenizer
matching.extractBetween:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label extractBetween.heapAddress qword at rbp-8  
	label extractBetween.handleAllocatedMemory qword at rbp-16
	label extractBetween.matchFlow qword at rbp-24 
	label extractBetween.letterLength qword at rbp-32
	label extractBetween.matches qword at rbp-40
	label extractBetween.letters qword at rbp-48
	label extractBetween.startIndex qword at rbp-56
	label extractBetween.endIndex qword at rbp-64
	label extractBetween.matchingIndex qword at rbp-72
	label extractBetween.containLetters qword at rbp-80
	label extractBetween.extractIndex qword at rbp-88
	label extractBetween.matchList qword at rbp-96
	label extractBetween.extractList qword at rbp-104
	label extractBetween.delimiter qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [extractBetween.letters], rcx
	mov [extractBetween.delimiter], rdx


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
	mov [extractBetween.heapAddress], rax
	add rsp, 8*4


	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [extractBetween.matches], rax

	mov rbx, [extractBetween.matches]
	mov rdx, rbx
	add rbx, Matches.flags
	mov r10, 11001b			; MATCH_START MATCH_EVERY MATCH_TRANSFORM
	mov [rbx], r10
	add rdx, Matches.transformFlags
	mov r11, 100b			; TRANSFORM_CONTAINS

	sub rsp, 8*8
	mov rdx, [extractBetween.delimiter]
	mov rbx, [extractBetween.matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, [extractBetween.letters]
	mov rcx, [extractBetween.matches]
	call get
	add rsp, 8*8
	mov [extractBetween.matchList], rax
	

	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [extractBetween.extractList], rax

	mov rcx, 0
	mov [extractBetween.startIndex], rcx
	mov [extractBetween.endIndex], rcx		; Begin as 0

	.nextMatch:
	mov rbx,[extractBetween.matchList]
	mov rdx, rbx
	add rdx, List.index
	add rbx, List.itemsCount
	mov rcx, [rdx]
	mov r8, [rbx]
	cmp rcx, r8
	jnl extractBetween.endMatchList

	
	sub rsp, 8*8
	mov rcx, [extractBetween.matchList]
	call list.getNextItem
	add rsp, 8*8
	mov [extractBetween.endIndex], rax
	
	sub rsp, 8*8
	mov r8, [extractBetween.endIndex]
	mov rdx, [extractBetween.startIndex]
	mov rcx, [extractBetween.letters]
	call letters.betweenIndices
	add rsp, 8*8
	sub rsp, 8*8
	mov rdx, rax
	mov rcx, [extractBetween.extractList]
	call list.newLastItem
	add rsp, 8*8

	mov r13, [extractBetween.endIndex]
	mov [extractBetween.startIndex], r13		; Swap on next run

	jmp extractBetween.nextMatch

	.endMatchList:

	mov rcx, [extractBetween.endIndex]
	cmp rcx, 0					; Get last extraction value? i.e. val3 in val1,val2,val3
	je extractBetween.end				; No matches

	sub rsp, 8*8
	mov rcx, [extractBetween.letters]
	call letters.letterLength
	add rsp, 8*8
	mov [extractBetween.letterLength], rax

	mov rcx, [extractBetween.endIndex]
	mov rax, [extractBetween.letterLength]
	sub rax, 1b
	cmp rcx, rax
	jnl extractBetween.end

	sub rsp, 8*8
	mov r8, [extractBetween.letterLength]		; -1? How can you include the end if end index is exclusive
	mov rdx, [extractBetween.endIndex]
	mov rcx, [extractBetween.letters]
	call letters.betweenIndices
	add rsp, 8*8
	sub rsp, 8*8
	mov rdx, rax
	mov rcx, [extractBetween.extractList]
	call list.newLastItem
	add rsp, 8*8


	.end:

	sub rsp, 8*8
	mov r8, [extractBetween.matches]
	mov rdx, 0
	mov rcx, [extractBetween.heapAddress]
	call [HeapFree]
	add rsp, 8*8


	mov rax, [extractBetween.extractList]



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