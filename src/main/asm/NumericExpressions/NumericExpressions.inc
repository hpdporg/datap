


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

	
	numExpTermList dq 0
	condExpTermList dq 0
	defExpTermList dq 0
	

section '.text' code readable writeable executable align 16


numericExpressions:
namespace numericExpressions
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
	add rcx, NumericExpression.expressionFlags
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4


;		.numericConditionFlag dq 0		; 0: Numeric 1: Condition
;		.expressionAlloc dq 0			; Expression alloc unparsed
;		.expressionExtractList dq 0		; Tokenized expression
;		.refsList dq 0				; Refs may need values replaced. refValuesList has final vals
;		.refValuesList dq 0			; Last list
;		.expressionFlags dq 0			; NUM_EXP_ Expression flags


	mov rbx, [handleAllocatedMemory]
	add rbx, NumericExpression.numericConditionFlag
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, NumericExpression.expressionAlloc
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, NumericExpression.expressionExtractList
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, NumericExpression.refsList
	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, NumericExpression.refValuesList
	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, NumericExpression.expressionFlags
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

parseExpression:
namespace parseExpression
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label matchIndexCount qword at rbp-32
	label numExpAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label expExtList qword at rbp-56
	label extItem qword at rbp-64
	label numExpTermListAddr qword at rbp-72
	label condExpTermListAddr qword at rbp-80
	label defExpTermListAddr qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [numExpAddr], rcx
	

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
	mov rdx, spaceLetter
	mov rbx, [numExpAddr]
	add rbx, NumericExpression.expressionAlloc
	mov rcx, [rbx]
	call matching.extractBetween
	add rsp, 8*8
	mov rbx, [numExpAddr]
	add rbx, NumericExpression.expressionExtractList
	mov [rbx], rax
	mov [expExtList], rax



	nextItem:
	mov r10, [expExtList]
	mov r11, r10
	add r11, List.index
	add r10, List.itemsCount
	mov rcx, [r11]
	mov rdx, [r10]
	cmp rcx, rdx
	jnl endList
	
	sub rsp, 8*8
	mov rcx, [expExtList]
	call list.getNextItem
	add rsp, 8*8
	mov [extItem], rax


	sub rsp, 8*8
	mov rdx, [numExpAddr]
	mov rcx, [extItem]
	call parseCondExp
	add rsp, 8*8
	cmp rax, 1b			; Match
	je hasCond

	sub rsp, 8*8
	mov rdx, [numExpAddr]
	mov rcx, [extItem]
	call parseNumExp
	add rsp, 8*8
	cmp rax, 1b			; Match
	je hasNum


	sub rsp, 8*8
	mov rdx, [numExpAddr]
	mov rcx, [extItem]
	call parseDefExp
	add rsp, 8*8
	cmp rax, 1b			; Match
	je hasDef





	jmp nextItem

	hasCond:
	mov rbx, [numExpAddr]
	add rbx, NumericExpression.numericConditionFlag
	mov rcx, 1b						; 0: Numeric 1: Condition
	mov [rbx], rcx

	jmp endList
	hasNum:
	mov rbx, [numExpAddr]
	add rbx, NumericExpression.numericConditionFlag
	mov rcx, 0b						; 0: Numeric 1: Condition
	mov [rbx], rcx
	jmp nextItem

	hasDef:
	jmp nextItem

	endList:

	mov rbx, [numExpAddr]					; Def by process of elimination
	add rbx, NumericExpression.numericConditionFlag
	mov rcx, 0b						; 0: Numeric 1: Condition
	mov r8, [rbx]
	cmp r8, rcx
	jne notDef
	
	mov rbx, [numExpAddr]
	add rbx, NumericExpression.expressionFlags
	mov rdx, [rbx]
	mov r8, 10000b		; NUM_EXP_DEF_NUM	10000b			4	; = ref1 + 100
	and r8, rdx
	cmp r8, 0
	jne notDef

	mov rbx, [numExpAddr]
	add rbx, NumericExpression.expressionFlags
	mov rdx, [rbx]
	bts rdx, 3		; NUM_EXP_DEF_ONLY	1000b			3	; = ref1
	mov [rbx], rdx



	notDef:


	completed:

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




;	numExpTermList dq 0
;	condExpTermList dq 0
;	defExpTermList dq 0

getNumExpTermList:
namespace getNumExpTermList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label matchIndexCount qword at rbp-32
	label numExpAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label expExtList qword at rbp-56
	label extItem qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	;mov [numExpAddr], rcx
	

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

	mov rdx, [numExpTermList]
	cmp rdx, 0
	
	jne completed				; Already initialized, just return alloc


	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [numExpTermList], rax


	sub rsp, 8*8
	mov rdx, moreLetters
	mov rcx, [numExpTermList]
	call list.newLastItem
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, lessLetters
	mov rcx, [numExpTermList]
	call list.newLastItem
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, divLetters
	mov rcx, [numExpTermList]
	call list.newLastItem
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, mulLetters
	mov rcx, [numExpTermList]
	call list.newLastItem
	add rsp, 8*8





	completed:

	mov rax, [numExpTermList]



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

getCondExpTermList:
namespace getCondExpTermList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label matchIndexCount qword at rbp-32
	label numExpAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label expExtList qword at rbp-56
	label extItem qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	;mov [numExpAddr], rcx
	

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

	mov rdx, [condExpTermList]
	cmp rdx, 0
	
	jne completed				; Already initialized, just return alloc


	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [condExpTermList], rax


	sub rsp, 8*8
	mov rdx, moreCondLetter
	mov rcx, [condExpTermList]
	call list.newLastItem
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, lessCondLetter
	mov rcx, [condExpTermList]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, sameLetters
	mov rcx, [condExpTermList]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, containsLetters
	mov rcx, [condExpTermList]
	call list.newLastItem
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, withinLetters
	mov rcx, [condExpTermList]
	call list.newLastItem
	add rsp, 8*8



	completed:

	mov rax, [condExpTermList]



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

getDefExpTermList:
namespace getDefExpTermList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label matchIndexCount qword at rbp-32
	label numExpAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label expExtList qword at rbp-56
	label extItem qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	;mov [extItem], rcx


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

	mov rdx, [defExpTermList]
	cmp rdx, 0
	
	jne completed				; Already initialized, just return alloc


	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [defExpTermList], rax


	sub rsp, 8*8
	mov rdx, sameLetter
	mov rcx, [defExpTermList]
	call list.newLastItem
	add rsp, 8*8






	completed:

	mov rax, [defExpTermList]



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


parseNumExp:
namespace parseNumExp
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label matchIndexCount qword at rbp-32
	label numExpAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label expExtList qword at rbp-56
	label extItem qword at rbp-64
	label numExpTermListAddr qword at rbp-72
	label condExpTermListAddr qword at rbp-80
	label defExpTermListAddr qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [extItem], rcx
	mov [numExpAddr], rdx
	

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
	mov rdx, [numExpAddr]
	mov rcx, [extItem]
	call parseNumFlags
	add rsp, 8*8


	sub rsp, 8*8
	call getNumExpTermList
	add rsp, 8*8
	mov [numExpTermListAddr], rax

	sub rsp, 8*8
	mov rcx, [numExpTermListAddr]
	call list.resetIndex
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [extItem]
	mov rcx, [numExpTermListAddr]
	call matching.listHasMatch
	add rsp, 8*8
	cmp rax, 1b
	je hasMatch

	mov rax, 0b
	jmp completed

	hasMatch:

	mov rbx, [numExpAddr]
	add rbx, NumericExpression.expressionFlags
	mov rdx, [rbx]
	bts rdx, 4		; NUM_EXP_DEF_NUM	10000b			4	; = ref1 + 100
	mov [rbx], rdx


	mov rax,1b


	completed:

	mov rax, rax




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

parseCondExp:
namespace parseCondExp
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label matchIndexCount qword at rbp-32
	label numExpAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label expExtList qword at rbp-56
	label extItem qword at rbp-64
	label numExpTermListAddr qword at rbp-72
	label condExpTermListAddr qword at rbp-80
	label defExpTermListAddr qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [extItem], rcx
	mov [numExpAddr], rdx


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
	mov rdx, [numExpAddr]
	mov rcx, [extItem]
	call parseCondFlags
	add rsp, 8*8



	sub rsp, 8*8
	call getCondExpTermList
	add rsp, 8*8
	mov [condExpTermListAddr], rax

	sub rsp, 8*8
	mov rcx, [condExpTermListAddr]
	call list.resetIndex
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [extItem]
	mov rcx, [condExpTermListAddr]
	call matching.listHasMatch
	add rsp, 8*8
	cmp rax, 1b
	je hasMatch

	mov rax, 0b
	jmp completed

	hasMatch:
	mov rax,1b


	completed:

	mov rax, rax



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

parseDefExp:
namespace parseDefExp
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label matchIndexCount qword at rbp-32
	label numExpAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label expExtList qword at rbp-56
	label extItem qword at rbp-64
	label numExpTermListAddr qword at rbp-72
	label condExpTermListAddr qword at rbp-80
	label defExpTermListAddr qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [extItem], rcx
	mov [numExpAddr], rdx

	

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
	mov rdx, [numExpAddr]
	mov rcx, [extItem]
	call parseDefFlags
	add rsp, 8*8


	sub rsp, 8*8
	call getDefExpTermList
	add rsp, 8*8
	mov [defExpTermListAddr], rax

	sub rsp, 8*8
	mov rcx, [defExpTermListAddr]
	call list.resetIndex
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [extItem]
	mov rcx, [defExpTermListAddr]
	call matching.listHasMatch
	add rsp, 8*8
	cmp rax, 1b
	je hasMatch

	mov rax, 0b
	jmp completed

	hasMatch:
	mov rax,1b


	completed:

	mov rax, rax



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

parseNumFlags:
namespace parseNumFlags
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label matchIndexCount qword at rbp-32
	label numExpAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label expExtList qword at rbp-56
	label extItem qword at rbp-64
	label numExpTermListAddr qword at rbp-72
	label condExpTermListAddr qword at rbp-80
	label defExpTermListAddr qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [extItem], rcx
	mov [numExpAddr], rdx
	

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







	completed:

	mov rax, rax




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

parseCondFlags:
namespace parseCondFlags
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label matchIndexCount qword at rbp-32
	label numExpAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label expExtList qword at rbp-56
	label extItem qword at rbp-64
	label numExpTermListAddr qword at rbp-72
	label condExpTermListAddr qword at rbp-80
	label defExpTermListAddr qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [extItem], rcx
	mov [numExpAddr], rdx
	

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
	mov rdx, moreCondLetter
	mov rcx, [extItem]
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 1b
	jne notMoreCond

	mov rbx, [numExpAddr]
	add rbx, NumericExpression.expressionFlags
	mov rdx, [rbx]
	bts rdx, 0	; NUM_EXP_MORE		1b			0	; ref1 > ref2
	mov [rbx], rdx

	jmp completed
	notMoreCond:

	sub rsp, 8*8
	mov rdx, lessCondLetter
	mov rcx, [extItem]
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 1b
	jne notLessCond

	mov rbx, [numExpAddr]
	add rbx, NumericExpression.expressionFlags
	mov rdx, [rbx]
	bts rdx, 1		; NUM_EXP_LESS		10b			1	; ref1 < ref2
	mov [rbx], rdx

	jmp completed
	notLessCond:

	sub rsp, 8*8
	mov rdx, sameLetters
	mov rcx, [extItem]
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 1b
	jne notSameCond

	mov rbx, [numExpAddr]
	add rbx, NumericExpression.expressionFlags
	mov rdx, [rbx]
	bts rdx, 2		; NUM_EXP_SAME		100b			2	; ref1 same ref2
	mov [rbx], rdx

	jmp completed
	notSameCond:

	sub rsp, 8*8
	mov rdx, containsLetters
	mov rcx, [extItem]
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 1b
	jne notContainsCond

	mov rbx, [numExpAddr]
	add rbx, NumericExpression.expressionFlags
	mov rdx, [rbx]
	bts rdx, 5		; NUM_EXP_CONTAINS	100000b			5	; ref1 contains ref2
	mov [rbx], rdx

	jmp completed
	notContainsCond:

	sub rsp, 8*8
	mov rdx, withinLetters
	mov rcx, [extItem]
	call matching.lettersSameExact
	add rsp, 8*8
	cmp rax, 1b
	jne notWithinCond

	mov rbx, [numExpAddr]
	add rbx, NumericExpression.expressionFlags
	mov rdx, [rbx]
	bts rdx, 6		; NUM_EXP_WITHIN	1000000b		6	; ref1 within ref2
	mov [rbx], rdx

	jmp completed
	notWithinCond:



	completed:



	mov rax, rax




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

parseDefFlags:
namespace parseDefFlags
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label matchIndexCount qword at rbp-32
	label numExpAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label expExtList qword at rbp-56
	label extItem qword at rbp-64
	label numExpTermListAddr qword at rbp-72
	label condExpTermListAddr qword at rbp-80
	label defExpTermListAddr qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [extItem], rcx
	mov [numExpAddr], rdx
	

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







	completed:

	mov rax, rax




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