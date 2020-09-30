;	This function will take two numbers and print them as integers (front-end will notice nothing)
;	Input: number to output
;	output: echo of number put in
;	nasm -felf64 convert-and-printf.asm && gcc -no-pie convert-and-printf.o && ./a.out [number to output]

			global	main
			extern	atoi
			extern	printf
			extern	puts

			section	.text
main:
			cmp	rdi, 2
			jne	incorrectArgumentCount

			add rsi,8				; Go to argv[1]	 (this is my unique contribution!)
			mov	rdi, [rsi]			; atoi(string_to_convert) <--- first parameter in rdi
			call	atoi			; Result will be in rax (calling convention!).

			mov	rdi, resultFormat	; printf(resultFormat, number) <--- args in rdi then rsi
			mov	rsi, rax			; Result of atoi goes to rsi now.
			xor	rax, rax			; printf is special: needs rax to be 0.
			call	printf

			ret

incorrectArgumentCount:
			mov	rdi, incorrectArgumentCountMessage
			call	puts
			ret

			section	.data
incorrectArgumentCountMessage:
			db	"One argument is needed for conversion to a number.", 0

resultFormat:		db	"Here it is: %d", 10, 0
hardCodedNumber:	db	"42", 0
