; ----------------------------------------------------------------------------------------
;      Creates folder based on name input. If no input given, creates folder named FOLDER
;               if too much input, creates folder named FOLDER
;
;     nasm -felf64 frank.asm && gcc -no-pie frank.o && ./a.out [new folder name]
;       rdi = argc, rsi = argv 
;----------------------------------------------------------------------------------------


        global  main
        extern  puts
        section .text
main:
        push    rdi                     ;   Don't know why but Toal has these
        push    rsi
        sub     rsp, 8                  ;   Align stacks (i copied this part from Toal)

        dec     rdi                     ; if(argc != 2) <-> if(argc-2 != 0)
        dec     rdi             
        jz      create_named            ; if (argc - 2) == 0, correct arg input, do it

        jmp     create_default          ; correct input

create_default: 

        mov     rdi, Argument_ERROR
        call    puts

        mov     rax, mkdir              ; mkdir
        mov     rdi, Hardcoded_Name     ; put argument in rdi (new file name)
        mov     rsi, 0777o              ; set permissions
        syscall
        
        jmp     exit

create_named:

        add     rsi, 8
        mov     rax, mkdir              ; create folder of name argv[1]
        mov     rdi, [rsi]
        mov     rsi, 0777o
        syscall

        jmp     exit

exit: 
        mov     rdi, Goodbye_MSG
        call    puts
        mov     rax, sys_exit
        xor     rdi, rdi
        syscall


;Some syscall definitions (so I don't have to put the actual numbers in the program)
sys_exit        equ     60
mkdir           equ     83
mkfile          equ     85


Argument_ERROR:
        db              "Input ONE argument, default FOLDER made",0

Hardcoded_Name:                          ;Default name
        db              "FOLDER",0      

Goodbye_MSG:                             ;Message at end of call
        db              "Goodbye",0     
