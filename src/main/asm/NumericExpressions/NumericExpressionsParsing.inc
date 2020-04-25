
section '.text' code readable writeable executable align 16


namespace numericExpressions
parse:
namespace parse
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


	mov rbx, [numExpAddr]
	add rbx, NumericExpression.evalFlags
	mov rdx, [rbx]
	bts rdx, 0		; NUM_EXP_EVAL_PARSED		1b			0	; Expression parsed
	mov [rbx], rdx



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






end namespace