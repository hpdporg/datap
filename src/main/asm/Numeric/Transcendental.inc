
		
section '.text' code readable writeable executable align 16


; Big angles may be incorrect (3.2)
sine:
	push rbp
	mov rbp, rsp
	sub rsp, (8*1)

	movq xmm0, xmm0
	;mov rcx, rcx;		[rbp+8]		;Angle
	;mov edx, [rbp+12]			;Tensor 2 address
	label .factorial qword at rbp-8
	;label .factorial qword at rbp-16

	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	
	;movq xmm0, rcx
	;movsd xmm0, [rcx]	; Destination
	movsd xmm1, xmm0	; Reference
	movsd xmm2, xmm0
	movsd xmm3, xmm0	; Power Reference
	movsd xmm4, xmm0
	movsd xmm5, xmm0

	mulsd xmm2, xmm1
	mulsd xmm2, xmm1
	movsd xmm3, xmm2

	;3
	mov [sine.factorial], 11b
	cvtsi2sd xmm4, [sine.factorial]
	mov [sine.factorial], 10b
	cvtsi2sd xmm5, [sine.factorial]
	mulsd xmm4, xmm5
	movsd xmm6, xmm4	; Factorial Reference
	divsd xmm2, xmm4
	subsd xmm0, xmm2

	;5
	movsd xmm2, xmm3
	mulsd xmm2, xmm1
	mulsd xmm2, xmm1
	movsd xmm3, xmm2
	mov [sine.factorial], 101b
	cvtsi2sd xmm4, [sine.factorial]
	mov [sine.factorial], 100b
	cvtsi2sd xmm5, [sine.factorial]
	mulsd xmm4, xmm5
	movsd xmm5, xmm6
	mulsd xmm4, xmm5
	movsd xmm6, xmm4
	divsd xmm2, xmm4
	addsd xmm0, xmm2



	;movsd [sine.sine], xmm0
	movq rax, xmm0

	;fld [sine.sine]

	;mov rax, [sine.sine]
	
	add rsp, 8
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0


cosine:
	push rbp 
	mov rbp, rsp
	;and rsp, -32					;32 alignment 
	;mov r13, rsp
	sub rsp, (8*0)+(8*0);8*8;8*6
	;sub rsp, 8					;16 alignment (optionally even out; 9 pushes below are odd)

	;mov rcx, rcx
	movq xmm0, xmm0
	;mov rdx, rdx
	;mov r8, r8
	;mov r9, r9

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	;label .angleAddress qword at rbp-8
	;virtual at rbp-104;56
	;	.app APP
	;end virtual	


	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8
	;align 16

	;mov [cosine.angleAddress], rcx
	;mov [newAPPKernel.APPAllocation], rdx
	;mov [newAPPKernel.app], r8
	;mov [newAPPKernel.spirvSize], r9

	movq xmm1, xmm0
	;movq xmm1, [cosine.angleAddress]
	;sinx: cosx, cosx:-sinx, -cosx, sinx
	mov rcx, 1b
	mov rdx, 10b
	cvtsi2sd xmm0, rcx
	cvtsi2sd xmm3, rdx
	movq xmm2, xmm1
	mulsd xmm2, xmm1
	divsd xmm2, xmm3
	subsd xmm0, xmm2

	;4
	movq xmm2, xmm1
	mulsd xmm2, xmm1
	mulsd xmm2, xmm1
	mulsd xmm2, xmm1
	mov rcx, 1b
	mov rdx, 10b
	cvtsi2sd xmm4, rcx
	cvtsi2sd xmm3, rdx
	movq xmm5, xmm3
	addsd xmm3, xmm4
	mulsd xmm5, xmm3
	addsd xmm3, xmm4
	mulsd xmm5, xmm3
	divsd xmm2, xmm5
	addsd xmm0, xmm2



	;6
	movq xmm2, xmm1
	mulsd xmm2, xmm1
	mulsd xmm2, xmm1
	mulsd xmm2, xmm1
	mulsd xmm2, xmm1
	mulsd xmm2, xmm1
	mov rcx, 1b
	mov rdx, 10b
	cvtsi2sd xmm4, rcx
	cvtsi2sd xmm3, rdx
	movq xmm5, xmm3
	addsd xmm3, xmm4
	mulsd xmm5, xmm3
	addsd xmm3, xmm4
	mulsd xmm5, xmm3
	addsd xmm3, xmm4
	mulsd xmm5, xmm3
	addsd xmm3, xmm4
	mulsd xmm5, xmm3
	divsd xmm2, xmm5
	subsd xmm0, xmm2



	add rsp, 8
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0


tangent:
	push rbp 
	mov rbp, rsp
	;and rsp, -32					;32 alignment 
	;mov r13, rsp
	sub rsp, (8*2)+(8*0);8*8;8*6
	;sub rsp, 8					;16 alignment (optionally even out; 9 pushes below are odd)

	movq xmm0, xmm0
	;movq xmm1, xmm1
	;mov rcx, rcx
	;mov rdx, rdx
	;mov r8, r8
	;mov r9, r9

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label .sine qword at rbp-8
	label .angle qword at rbp-16
	;virtual at rbp-104;56
	;	.app APP
	;end virtual	


	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8
	;align 16

	;mov [tangent.sineAddress], rcx
	;mov [tangent.cosineAddress], rcx

	;movq xmm0, [tangent.sineAddress]
	;movq xmm1, [tangent.cosineAddress]

	movq [tangent.angle], xmm0
	sub rsp, 8*4
	call sine
	add rsp, 8*4
	movq [tangent.sine], xmm0
	movq xmm0, [tangent.angle]
	sub rsp, 8*4
	call cosine
	add rsp, 8*4
	movq xmm1, xmm0	
	movq xmm0, [tangent.sine]


	divsd xmm0, xmm1




	add rsp, 8
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp
	retn 0

arctangent:
	push rbp 
	mov rbp, rsp
	;and rsp, -32					;32 alignment 
	;mov r13, rsp
	sub rsp, (8*0)+(8*0);8*8;8*6
	;sub rsp, 8					;16 alignment (optionally even out; 9 pushes below are odd)

	movq xmm0, xmm0
	;movq xmm1, xmm1
	;mov rcx, rcx
	;mov rdx, rdx
	;mov r8, r8
	;mov r9, r9

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	;label .sine qword at rbp-8
	;label .angle qword at rbp-16
	;virtual at rbp-104;56
	;	.app APP
	;end virtual	


	and rsp, -32
	push rbx rbp rdi rsi rsp r12 r13 r14 r15
	sub rsp, 8

	; f(x+h) = x - ((x^3)/3) + (((x^5))/5) - ((x^7)/7) + ..
	
	movq xmm0, xmm0
	
	mov rcx, 11b		; 3
	mov rdx, 101b		; 5	
	mov rax, 111b		; 7
	cvtsi2sd xmm4, rcx
	cvtsi2sd xmm5, rdx
	cvtsi2sd xmm6, rax

	movq xmm7, xmm0		; Cache x
	movq xmm3, xmm7
	mulsd xmm3, xmm7	
	mulsd xmm3, xmm7	; x^3
	movq xmm2, xmm3		; accum
	divsd xmm3, xmm4	; ((x^3)/3)
	movq xmm0, xmm7
	subsd xmm0, xmm3	; x - ((x^3)/3)
	mulsd xmm2, xmm7
	mulsd xmm2, xmm7	; x^5
	movq xmm3, xmm2
	divsd xmm3, xmm5	; (((x^5))/5)
	addsd xmm0, xmm3

	mov rax, 1001b		; 9
	cvtsi2sd xmm4, rax

	mulsd xmm2, xmm7
	mulsd xmm2, xmm7	; x^7
	movq xmm3, xmm2
	divsd xmm3, xmm6	; ((x^7)/7)
	subsd xmm0, xmm3
	mulsd xmm2, xmm7
	mulsd xmm2, xmm7	; x^9
	movq xmm3, xmm2
	divsd xmm3, xmm4	; (((x^9))/9)
	addsd xmm0, xmm3	
	




	

	add rsp, 8
	pop r15 r14 r13 r12 rsp rsi rdi rbp rbx

	mov rsp, rbp
	pop rbp

	retn 0