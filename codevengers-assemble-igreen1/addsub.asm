;	This program will take a simple calculation (addition or subtraction) and perform it
;	input: [number] +/- [number]
;	output: Result of operation
; 	To run: nasm -felf64 addsub.asm && gcc -no-pie addsub.o && ./a.out [number] +/- [number]		
			global	main
			extern	atoi
			extern	strlen			; The specific externs that you will need
			extern	strncmp			; depend on your implementation; edit this
			extern	printf			; list as necessary.
			extern	puts

			section	.text
main:
			cmp	rdi, 4
			jne	incorrectArgumentCount

			push	r12				; The necessity of these will depend on implementation;
			push	r13				; this is mainly a reminder to preserve any callee-save
			push	r14				; registers that you might use.
			push 	rdi
			push	rsi


			;Convert rsi[1] and rsi[2] to integers in r12, r13 respectively
			push	rsi				;save rsi (argv) for later
			mov rdi, [rsi+8]		;move the first argv[1] into rdi
			call atoi				;to integer
			mov r12, rax			;save this result in r12 register
			pop 	rsi				;get our argv back

			push	rsi				;same as above but store in r13
			mov rdi, [rsi+24]
			call atoi
			mov r13, rax
			pop 	rsi

			;first find length (for strncmp)
			push rsi
			mov  rdi, [rsi+16] 
			call strlen
			mov  rdx, rax
			pop rsi

			;do string comapre
			push rsi
			mov	r14, rdx
			mov  rdi, [rsi+16]
			mov  rsi, minusOperator
			;rdx already stored for this call
			call strncmp
			pop rsi

			cmp	rax, 0				;if input op is minusOp, subtract
			je subtract

			push rsi
			mov rdi, [rsi+16]
			mov rsi, plusOperator
			mov rdx, r14
			call strncmp
			pop rsi

			cmp rax, 0
			je addition				;if input op is plusOp, add

			jmp incorrectOperator	;unknown operation, ERROR call


subtract:

			mov r14, r12			;mov r12 to r14 then add r13 to it so
			sub	r14, r13			;r14 = r12 - r13 :)

			;now, print it all with printf and format given
			;very straigth forward, put eaceh argument in the right register
			mov rdi, resultFormat
			mov rsi, r12
			mov rdx, minusOperator
			mov rcx, r13
			mov r8, r14
			xor rax, rax
			call printf
			jmp finished

addition:

			mov r14, r12			;mov r12 to r14 then add r13 to it so
			add	r14, r13			;r14 = r12 + r13 :)

			;now, print it all with printf and format given
			;very straigth forward, put eaceh argument in the right register
			mov rdi, resultFormat
			mov rsi, r12
			mov rdx, plusOperator
			mov rcx, r13
			mov r8, r14
			xor rax, rax
			call printf

			jmp finished

finished:
			pop 	rsi
			pop 	rdi
			pop		r14
			pop		r13
			pop		r12
			ret

incorrectArgumentCount:
			mov	rdi, incorrectArgumentCountMessage
			call	puts
			ret

incorrectOperator:
			mov	rdi, incorrectOperatorMessage
			call	puts
			jmp	finished

			section	.data
plusOperator:		db	"+", 0
minusOperator:		db	"-", 0
resultFormat:		db	"%d %s %d = %d", 10, 0

te: 	db 	"test",0

incorrectArgumentCountMessage:
			db	"To use this program, either enter <number> + <number> or <number> - <number>.", 0

incorrectOperatorMessage:
			db	"This program only recognizes + or -.", 0
