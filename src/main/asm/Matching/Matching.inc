



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
new:
namespace new
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
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
	mov [heapAddress], rax
	add rsp, 8*4
	

	mov rcx, 0
	add rcx, Matches.subRangeEndIndex
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4




	mov rbx, [handleAllocatedMemory]
	add rbx, Matches.flags
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Matches.transformFlags
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Matches.containsRangeList
	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Matches.subRangeStartIndex
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Matches.subRangeEndIndex
	mov rax, 0
	mov [rbx], rax
	



	;lea rax, [list]
	;lea rcx, [list.indexedItemIndex]

	;sub rcx, rax
	;add rcx, 1000b

	;cld

	;lea rsi, [list]
	;mov rdi, [storage.handleAllocatedMemory]

	;rep movsb


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

newMatchFlow:
namespace newMatchFlow
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
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
	mov [heapAddress], rax
	add rsp, 8*4
	

	mov rcx, 0
	add rcx, MatchFlow.startEndLength
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4




	mov rbx, [handleAllocatedMemory]
	add rbx, MatchFlow.contains
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, MatchFlow.start
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, MatchFlow.end
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, MatchFlow.firstMatch
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, MatchFlow.everyMatch
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, MatchFlow.matchIndexCount
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, MatchFlow.startEndLength
	mov rax, 0
	mov [rbx], rax





	;lea rax, [list]
	;lea rcx, [list.indexedItemIndex]

	;sub rcx, rax
	;add rcx, 1000b

	;cld

	;lea rsi, [list]
	;mov rdi, [storage.handleAllocatedMemory]

	;rep movsb


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

processFlags:
namespace processFlags
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label matchIndexCount qword at rbp-32
	label matchAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [matchAddr], rcx
	

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
	mov [matchFlow], rax


	mov rcx, 0
	mov [matchIndexCount], rcx		; Begin as 0

	mov rbx, [matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 0					; MATCH_START	
	jnc endIndex

	mov rbx, [matchFlow]
	add rbx, MatchFlow.start
	mov rcx, 1b
	mov [rbx], rcx

	mov rcx, 1b
	mov rdx, [matchIndexCount]
	add rdx, rcx
	mov [matchIndexCount], rdx		; Increment


	endIndex:
	mov rbx, [matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 1b					; MATCH_END
	jnc matchFirstOrEvery	

	mov rbx, [matchFlow]
	add rbx, MatchFlow.end
	mov rcx, 1b
	mov [rbx], rcx

	mov rdx, [matchFlow]
	add rdx, MatchFlow.start
	mov r8, [rdx]
	cmp r8, 0
	je endOnly

	mov rbx, [matchFlow]
	add rbx, MatchFlow.startEndLength		; MATCH start and end (length of contains)
	mov rcx, 1b
	mov [rbx], rcx


	endOnly:

	mov rcx, 1b
	mov rdx, [matchIndexCount]
	add rdx, rcx
	mov [matchIndexCount], rdx		; Increment
	

	matchFirstOrEvery:

	mov rbx, [matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 10b					; MATCH_FIRST
	jnc everyMatch


	mov rbx, [matchFlow]
	add rbx, MatchFlow.firstMatch
	mov rcx, 1b
	mov [rbx], rcx

	jmp hasTransform

	everyMatch:
	mov rbx, [matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 11b					; MATCH_EVERY
	jnc hasTransform

	
	mov rbx, [matchFlow]
	add rbx, MatchFlow.everyMatch
	mov rcx, 1b
	mov [rbx], rcx



	hasTransform:
	mov rbx, [matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 100b					; MATCH_TRANSFORM
	jnc defineMatchIndexCounts

	
	mov rbx, [matchAddr]
	add rbx, Matches.transformFlags
	mov r8, [rbx]
	bt r8, 10b					; TRANSFORM_CONTAINS
	jnc defineMatchIndexCounts	

	mov rbx, [matchFlow]
	add rbx, MatchFlow.contains
	mov rcx, 1b
	mov [rbx], rcx

	defineMatchIndexCounts:

	mov rdx, [matchIndexCount]
	mov rbx, [matchFlow]
	add rbx, MatchFlow.matchIndexCount
	mov [rbx], rdx

	completed:

	mov rax, [matchFlow]



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

get:
namespace get
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label listAlloc qword at rbp-32
	label matchAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label containsRangeList qword at rbp-56
	label containsAddr qword at rbp-64
	label matchingIndex qword at rbp-72
	label containsLength qword at rbp-80
	label startMatchFound qword at rbp-88
	label matchFoundCount qword at rbp-96
	label lettersLength qword at rbp-104
	label matchingEnd qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [matchAddr], rcx
	mov [lettersAlloc], rdx


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
	mov [heapAddress], rax
	add rsp, 8*4

	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [listAlloc], rax


	sub rsp, 8*8
	mov rcx, [lettersAlloc]
	call letters.letterLength
	add rsp, 8*8
	mov [lettersLength], rax



	mov rbx, [matchAddr]
	add rbx, Matches.containsRangeList
	mov rdx, [rbx]
	mov [containsRangeList], rdx



	sub rsp, 8*8
	mov rcx, [matchAddr]
	call matching.processFlags
	add rsp, 8*8
	mov [matchFlow], rax
	

	mov rbx, [matchFlow]
	add rbx, MatchFlow.contains
	mov r8, [rbx]
	bt r8, 0b					; Match contains
	jnc endMatching				; Until others are supported

	
	mov rcx, 0
	mov [matchingIndex], rcx			; Begin at 0
	mov rcx, 0
	mov [matchFoundCount], rcx			; Begin as 0
	mov rcx, 0
	mov [startMatchFound], rcx			; Begin as 0


	nextMatch:


	mov rcx, [matchingIndex]
	mov rdx, [lettersLength]
	cmp rcx, rdx
	jnl endMatching

	mov rbx, [matchFlow]
	add rbx, MatchFlow.firstMatch
	mov r8, [rbx]
	bt r8, 0b					; Match firstMatch
	jnc matchEvery


	mov rbx, [matchFlow]
	add rbx, MatchFlow.matchIndexCount
	mov r8, [rbx]
	mov rdx, [matchFoundCount]
	cmp r8, rdx					; Already reached start & end when required?
	je endMatching


	matchEvery:


	matchingEndOrStart:

	mov rbx, [matchFlow]
	add rbx, MatchFlow.start
	mov r8, [rbx]
	bt r8, 0b					; Match start
	jnc matchEnd				; Only match end

	mov rbx, [startMatchFound]
	mov rcx, 1b
	cmp rcx, rbx
	je matchEnd

	mov rcx, 0
	mov [matchingEnd], rcx


	jmp nextContains
	matchEnd:

	mov rbx, [matchFlow]
	add rbx, MatchFlow.end
	mov r8, [rbx]
	bt r8, 0b					; Match end
	jnc nextContains				; Only match start


	mov rcx, 1b
	mov [matchingEnd], rcx


	nextContains:
	mov rbx, [containsRangeList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endContains


	sub rsp, 8*8
	mov rcx, [containsRangeList]
	call list.getNextItem
	add rsp, 8*8
	mov [containsAddr], rax


	sub rsp, 8*8
	mov rcx, [containsAddr]
	call letters.letterLength
	add rsp, 8*8
	mov [containsLength], rax


	mov rcx, [matchingIndex]
	mov [containsLength], rax
	add rcx, rax
	mov rdx, [lettersLength]
	cmp rcx, rdx					; Lengths less than or equal
	jnle nextContains


	cld

	mov rdi, [containsAddr]
	mov rsi, [lettersAlloc]
	mov r8, [matchingIndex]
	add rsi, r8
	
	mov rcx, [containsLength]

	repe cmpsb

	jnz nextMatch				; noMatch


	matchFound:

	

	mov rdx, [matchingEnd]
	mov rcx, 1b
	cmp rcx, rdx
	jne matchingStart

	mov rbx, [matchingIndex]
	mov rcx, [containsLength]
	sub rcx, 1b
	add rbx, rcx
	mov rdx, rbx
	
	jmp newMatchListItem

	matchingStart:	

	mov rdx, [matchingIndex]


	newMatchListItem:

	sub rsp, 8*8
	;mov rdx,[containsLength]
	mov rcx, [listAlloc]
	call list.newLastItem
	add rsp, 8*8

	mov rbx, [matchFoundCount]
	add rbx, 1b
	mov [matchFoundCount], rbx

	mov rbx, [matchFlow]
	add rbx, MatchFlow.startEndLength
	mov r8, [rbx]
	bt r8, 0b					; Match start end length
	jnc notMatchingStartEndLength		

	sub rsp, 8*8
	mov rbx, [matchingIndex]
	mov rcx, [containsLength]
	sub rcx, 1b
	add rbx, rcx
	mov rdx, rbx
	mov rcx, [listAlloc]
	call list.newLastItem
	add rsp, 8*8

	mov rbx, [matchFoundCount]
	add rbx, 1b
	mov [matchFoundCount], rbx

	mov rcx, 1b
	mov [startMatchFound], rcx

	notMatchingStartEndLength:

	mov rcx, 1b
	mov r8, 0
	mov rbx, [startMatchFound]
	cmp rbx, rcx
	je clearMatchStartFound		; Either way, invert

	mov [startMatchFound], rcx

	jmp increaseMatchingIndex
	clearMatchStartFound:

	mov [startMatchFound], r8


	increaseMatchingIndex:


	mov rbx, [matchingIndex]
	mov rcx, [containsLength]
	add rbx, rcx
	mov [matchingIndex], rbx		; Increase by 1 when no match, containsLength when match

	jmp resetContains


	endContains:

	mov rbx, [matchingIndex]
	mov rcx, 1b
	add rbx, rcx
	mov [matchingIndex], rbx		; Increase by 1 when no match, containsLength when match

	resetContains:
	

	sub rsp, 8*8
	mov rcx, [containsRangeList]
	call list.resetIndex
	add rsp, 8*8


	jmp nextMatch





	endMatching:

	sub rsp, 8*8
	mov r8, [matchFlow]
	mov rdx, 0
	mov rcx, [heapAddress]
	call [HeapFree]
	add rsp, 8*8

	mov rax, [listAlloc]


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

; Returns match results with 0 items when letters not same
; Returns greater than 0 items in List results when match

lettersSame:
namespace lettersSame
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label listAlloc qword at rbp-32
	label matches qword at rbp-40
	label lettersAlloc qword at rbp-48
	label containsRangeList qword at rbp-56
	label containsAddr qword at rbp-64
	label matchingIndex qword at rbp-72
	label containLetters qword at rbp-80
	label startMatchFound qword at rbp-88
	label matchFoundCount qword at rbp-96
	label lettersLength qword at rbp-104
	label matchingEnd qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersAlloc], rcx
	mov [containLetters], rdx


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
	mov [matches], rax

	mov rbx, [matches]
	add rbx, Matches.flags
	mov r8, 10001b
	mov [rbx], r8

	mov rbx, [matches]
	add rbx, Matches.transformFlags
	mov r8, 100b
	mov [rbx], r8

	sub rsp, 8*8
	mov rdx, [containLetters]
	mov rbx, [matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [lettersAlloc]
	mov rcx, [matches]
	call get
	add rsp, 8*8
	mov rax, rax


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


; Returns 0 when letters not same, and not same lengths
; Returns 1

lettersSameExact:
namespace lettersSameExact
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label listAlloc qword at rbp-32
	label matches qword at rbp-40
	label lettersAlloc qword at rbp-48
	label containsRangeList qword at rbp-56
	label containsAddr qword at rbp-64
	label matchResult qword at rbp-72
	label containLetters qword at rbp-80
	label length1 qword at rbp-88
	label length2 qword at rbp-96
	label lettersLength qword at rbp-104
	label matchingEnd qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersAlloc], rcx
	mov [containLetters], rdx


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
	mov [matchResult], rcx			; Begin as 0

	sub rsp, 8*8
	mov rcx, [lettersAlloc]
	call letters.letterLength
	add rsp, 8*8
	mov [length1], rax

	;sub rsp, 8*8
	;mov rcx, [length1]
	;call storage.debugNumMsg
	;add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [containLetters]
	call letters.letterLength
	add rsp, 8*8
	mov [length2], rax

	;sub rsp, 8*8
	;mov rcx, [length2]
	;call storage.debugNumMsg
	;add rsp, 8*8

	
	mov rcx, [length1]
	mov rdx, [length2]
	cmp rcx, rdx
	je sameLength

	sub rsp, 8*8
	call list.new
	add rsp, 8*8

	add rax, List.itemsCount
	mov rdx, [rax]
	mov [matchResult], rdx



	jmp completed


	sameLength:


	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [matches], rax

	mov rbx, [matches]
	add rbx, Matches.flags
	mov r8, 10001b
	mov [rbx], r8

	mov rbx, [matches]
	add rbx, Matches.transformFlags
	mov r8, 100b
	mov [rbx], r8

	sub rsp, 8*8
	mov rdx, [containLetters]
	mov rbx, [matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [lettersAlloc]
	mov rcx, [matches]
	call get
	add rsp, 8*8
	mov rax, rax

	add rax, List.itemsCount
	mov rdx, [rax]
	mov [matchResult], rdx


	completed:

	mov rax, [matchResult]


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

getNextIndex:
namespace getNextIndex
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label listAlloc qword at rbp-32
	label matches qword at rbp-40
	label lettersAlloc qword at rbp-48
	label containsRangeList qword at rbp-56
	label containsAddr qword at rbp-64
	label matchingIndex qword at rbp-72
	label containLetters qword at rbp-80
	label matchIndex qword at rbp-88
	label matchList qword at rbp-96
	label lettersLength qword at rbp-104
	label matchingEnd qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersAlloc], rcx
	mov [containLetters], rdx


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
	mov [heapAddress], rax
	add rsp, 8*4




	mov rcx, 0
	mov [matchIndex], rcx			; Begin as 0

	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [matches], rax

	mov rbx, [matches]
	add rbx, Matches.flags
	mov rcx, 10101b
	mov [rbx], rcx
	mov rbx, [matches]
	add rbx, Matches.transformFlags
	mov rcx, 100b
	mov [rbx], rcx


	sub rsp, 8*8
	mov rdx, [containLetters]
	mov rbx, [matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [lettersAlloc]
	mov rcx, [matches]
	call get
	add rsp, 8*8
	mov [matchList], rax


	mov rbx,[matchList]
	add rbx, List.itemsCount
	mov rcx, 0
	mov rdx, [rbx]
	cmp rcx, rdx
	je completed				; No match

	
	sub rsp, 8*8
	mov rcx, [matchList]
	call list.getNextItem
	add rsp, 8*8
	mov [matchIndex], rax



	completed:

	sub rsp, 8*8
	mov r8, [matches]
	mov rdx, 0
	mov rcx, [heapAddress]
	call [HeapFree]
	add rsp, 8*8


	mov rax, [matchIndex]



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

hasMatch:
namespace hasMatch
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label listAlloc qword at rbp-32
	label matches qword at rbp-40
	label lettersAlloc qword at rbp-48
	label containsRangeList qword at rbp-56
	label containsAddr qword at rbp-64
	label matchingIndex qword at rbp-72
	label containLetters qword at rbp-80
	label hasMatchIndex qword at rbp-88
	label matchList qword at rbp-96
	label lettersLength qword at rbp-104
	label matchingEnd qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersAlloc], rcx
	mov [containLetters], rdx


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
	mov [heapAddress], rax
	add rsp, 8*4





	mov rcx, 0
	mov [hasMatchIndex], rcx			; Begin as 0

	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [matches], rax

	mov rbx, [matches]
	add rbx, Matches.flags
	mov rcx, 10101b
	mov [rbx], rcx
	mov rbx, [matches]
	add rbx, Matches.transformFlags
	mov rcx, 100b
	mov [rbx], rcx


	sub rsp, 8*8
	mov rdx, [containLetters]
	mov rbx, [matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [lettersAlloc]
	mov rcx, [matches]
	call get
	add rsp, 8*8
	mov [matchList], rax


	mov rbx,[matchList]
	add rbx, List.itemsCount
	mov rcx, 0
	mov rdx, [rbx]
	cmp rcx, rdx
	je completed				; No match

	mov rcx, 1b
	mov [hasMatchIndex], rcx



	completed:

	sub rsp, 8*8
	mov r8, [matches]
	mov rdx, 0
	mov rcx, [heapAddress]
	call [HeapFree]
	add rsp, 8*8


	mov rax, [hasMatchIndex]



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

listHasMatch:
namespace listHasMatch
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label listAlloc qword at rbp-32
	label matches qword at rbp-40
	label lettersAlloc qword at rbp-48
	label containsRangeList qword at rbp-56
	label containsAddr qword at rbp-64
	label matchingIndex qword at rbp-72
	label containLetters qword at rbp-80
	label hasMatchIndex qword at rbp-88
	label matchList qword at rbp-96
	label lettersLength qword at rbp-104
	label itemAlloc qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [listAlloc], rcx
	mov [containLetters], rdx


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
	mov [hasMatchIndex], rcx			; Begin as 0

	nextItem:
	mov rbx, [listAlloc]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl endItems


	sub rsp, 8*8
	mov rcx, [listAlloc]
	call list.getNextItem
	add rsp, 8*8
	mov [itemAlloc], rax

	sub rsp, 8*8
	mov rdx, [containLetters]
	mov rcx, [itemAlloc]
	call lettersSameExact
	add rsp, 8*8
	cmp rax, 0
	je nextItem
	
	mov rax, 1
	mov [hasMatchIndex], rax
	jmp completed

	endItems:


	completed:



	mov rax, [hasMatchIndex]



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

; Extract list of matches between a delimiter
; Tokenizer
extractBetween:
namespace extractBetween
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label letterLength qword at rbp-32
	label matches qword at rbp-40
	label lettersAlloc qword at rbp-48
	label startIndex qword at rbp-56
	label endIndex qword at rbp-64
	label matchingIndex qword at rbp-72
	label containLetters qword at rbp-80
	label extractIndex qword at rbp-88
	label matchList qword at rbp-96
	label extractList qword at rbp-104
	label delimiter qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersAlloc], rcx
	mov [delimiter], rdx


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
	mov [heapAddress], rax
	add rsp, 8*4


	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [matches], rax

	mov rbx, [matches]
	mov rdx, rbx
	add rbx, Matches.flags
	mov r10, 11001b			; MATCH_START MATCH_EVERY MATCH_TRANSFORM
	mov [rbx], r10
	add rdx, Matches.transformFlags
	mov r11, 100b			; TRANSFORM_CONTAINS
	mov [rdx], r11

	sub rsp, 8*8
	mov rdx, [delimiter]
	mov rbx, [matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8



	sub rsp, 8*8
	mov rdx, [lettersAlloc]
	mov rcx, [matches]
	call get
	add rsp, 8*8
	mov [matchList], rax
	


	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [extractList], rax

	mov rcx, 0
	mov [startIndex], rcx
	mov [endIndex], rcx		; Begin as 0

	nextMatch:
	mov rbx,[matchList]
	mov rdx, rbx
	add rdx, List.index
	add rbx, List.itemsCount
	mov rcx, [rdx]
	mov r8, [rbx]
	cmp rcx, r8
	jnl endMatchList

	

	sub rsp, 8*8
	mov rcx, [matchList]
	call list.getNextItem
	add rsp, 8*8
	mov [endIndex], rax

	mov rcx, [endIndex]
	sub rcx, 1b
	mov [endIndex], rcx		; Non-inclusive


	
	sub rsp, 8*8
	mov r8, [endIndex]
	mov rdx, [startIndex]
	mov rcx, [lettersAlloc]
	call letters.betweenIndices
	add rsp, 8*8
	sub rsp, 8*8
	mov rdx, rax
	mov rcx, [extractList]
	call list.newLastItem
	add rsp, 8*8

	mov rcx, [endIndex]
	add rcx, 10b
	mov [startIndex], rcx		; Non-inclusive, skip ahead 2, swap on next run

	jmp nextMatch

	endMatchList:

	mov rcx, [endIndex]
	cmp rcx, 0					; Get last extraction value? i.e. val3 in val1,val2,val3
	je completed				; No matches

	sub rsp, 8*8
	mov rcx, [lettersAlloc]
	call letters.letterLength
	add rsp, 8*8
	mov [letterLength], rax

	mov rcx, [endIndex]
	add rcx, 1b					; Was decremented earlier
	mov rax, [letterLength]
	sub rax, 1b
	cmp rcx, rax
	jnl completed

	sub rsp, 8*8
	mov r8, [letterLength]		
	mov rdx, [endIndex]
	add rdx, 10b					; Non-inclusive, was decremented before as end, must be advanced as start
	mov rcx, [lettersAlloc]
	call letters.betweenIndices
	add rsp, 8*8
	sub rsp, 8*8
	mov rdx, rax
	mov rcx, [extractList]
	call list.newLastItem
	add rsp, 8*8


	completed:

	sub rsp, 8*8
	mov r8, [matches]
	mov rdx, 0
	mov rcx, [heapAddress]
	call [HeapFree]
	add rsp, 8*8


	mov rax, [extractList]



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

; Extract Flow from matches between two delimiters
; Tokenizer on tabular data, i.e. rows and columns from file with newlines and commas/tabs as delimiters
extractFlowBetween:
namespace extractFlowBetween
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*16);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label letterLength qword at rbp-32
	label jItem qword at rbp-40
	label lettersAlloc qword at rbp-48
	label startIndex qword at rbp-56
	label endIndex qword at rbp-64
	label matchingIndex qword at rbp-72
	label iDelimiter qword at rbp-80
	label extractIndex qword at rbp-88
	label matchList qword at rbp-96
	label flowAlloc qword at rbp-104
	label jDelimiter qword at rbp-112
	label iExtractList qword at rbp-120
	label jExtractList qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersAlloc], rcx
	mov [iDelimiter], rdx		; Across
	mov [jDelimiter], r8			; Vertical


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
	mov [heapAddress], rax
	add rsp, 8*4

	sub rsp, 8*8
	call flow.new
	add rsp, 8*8
	mov [flowAlloc], rax


	sub rsp, 8*8
	mov rdx, [jDelimiter]
	mov rcx, [lettersAlloc]
	call extractBetween
	add rsp, 8*8
	mov [jExtractList], rax


	nextJItem:
	mov rbx, [jExtractList]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl endJList


	sub rsp, 8*8
	mov rcx, [jExtractList]
	call list.getNextItem
	add rsp, 8*8
	mov [jItem], rax

	sub rsp, 8*8
	mov rdx, [iDelimiter]
	mov rcx, [jItem]
	call extractBetween
	add rsp, 8*8
	mov [iExtractList], rax

	mov rbx, [iExtractList]
	add rbx, List.itemsCount
	mov rcx, [rbx]
	mov r11, [flowAlloc]
	add r11, Flow.width
	mov rdx, [r11]
	cmp rcx, rdx
	jle flowWidthNotIncreased

	sub rsp, 8*8
	mov rbx, [iExtractList]
	add rbx, List.itemsCount
	mov rdx, [rbx]
	mov rcx, [flowAlloc]
	call flow.increaseWidth
	add rsp, 8*8


	flowWidthNotIncreased:


	sub rsp, 8*8
	mov rdx, [iExtractList]
	mov rcx, [flowAlloc]
	call flow.newLastIVals
	add rsp, 8*8




	jmp nextJItem
	endJList:





	completed:

	mov rax, [flowAlloc]



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