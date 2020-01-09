
include 'format/format.inc'


format MS64 COFF

include 'Exports.inc'


include 'datap.inc'



public start as 'start'

section '.data' data readable writeable align 16

	dataSecInitVal db 0						; Define arbitrary value. Placeholder if this section is needed.
	fileEntry1 db 'Entry 1',0
	handAddr dq 0
	alloc3 dq 0
	filename1 db 'file1.txt',0


section '.text' code readable writeable executable align 16


;align 16
start:
       push rbp
       mov rbp, rsp
       and rsp, -32
       sub rsp, 8*12;8;7;8;9
       and rsp, -32

	;newFile filename1,[handAddr]
	;writeFile [handAddr],entry1,4,[alloc3]


	 mov rcx, 0
	 sub rsp, 8*4
	 call [ExitProcess]
	 add rsp, 8*4