; ----------------------------------------------------------------------------------------
;     First, creates a folder then renames it based on the next argument
;       then, creates a link based on the original name
;       if no next argument (last argument in odd amount), leave as original name
;               that way, if you just do one, you can just create a folder
;       did folders instead of files beacuse seemed more fun (based on idea from you in README)
;
;     nasm -felf64 combo.asm && gcc -no-pie combo.o && ./a.out 
;       rdi = argc, rsi = argv 
;----------------------------------------------------------------------------------------


        global  main
        extern  puts

        section .text
main:

        push    rdi                     ; Clear beforehand
        push    rsi
        sub     rsp, 8                  ; Clear stacks (this part is removed from my program but worth keeping in case I add to it)

        cmp     rdi, 1                  ; If only the one argument, not enough. Works for n arguments if n > 1!
        je      error_too_few


        mov     [argc], rdi             ; Since rdi and rsi will be destroyed multiple times with syscall store them safely away
        mov     [argv], rsi

        call    iterate_over_args       ; The main function

        jmp     exit


iterate_over_args:

        ;create argument based on argument (n)

        mov     rdi, [argc]             ;   Retrieve running argc value

        dec     rdi                     ;   If (--argc)==0, exit (decrement first since we don't include argv[0])
        jz      done

        mov     [argc], rdi             ;   update running argc value
        
        mov     rsi, [argv]             ;   store current argv to rdi
        add     rsi, 8                  ;   go to next argv (aka, the one we want)
        mov     [argv], rsi             ;   update running argv value
        mov     rdi, [rsi]

        call    create_named_directory  ;   we've fulfilled assumption that rdi holds name of dir 

        ;now rename based on the next argument (n+1)

        mov     rsi, rdi                ; store old name is rsi for like two seconds
        mov     rdi, [argc]

        dec     rdi                     ; check if there's another argument
        jz      done                    ; if not, exit
        mov     [argc], rdi

        mov     rdi, rsi                ; there is another argument, it therefore is the new name of the folder
        mov     rsi, [argv]
        add     rsi, 8
        mov     [argv], rsi
        mov     rsi, [rsi]

        call    rename_and_link

        ;restart :) go until reach the amount of arguments
        jmp     iterate_over_args

create_named_directory:                 ;   Assuming rdi holds val to name directory 

        mov     [folder_name], rdi      ;   store folder name since rdi is unstable on system call
       
        mov     rax, mkdir              ;   create folder of name argv[1]
        mov     rsi, permission
        syscall

        mov     rdi, rax
        jz      error_dirCreate         ;   Check if successful, exit if not
        
        mov     rdi, [folder_name]

        ret                             ;   Return to parent function

rename_and_link:                        ; rdi holds old name - rsi holds new name

        mov     [folder_name], rdi      ; Store values since rdi, rsi are destroyed by rename syscall
        mov     [new_name], rsi

        mov     rax, rename             ; Rename! from rdi to rsi
        syscall

        mov     rsi, [folder_name]      ; Recover rdi and rsi values, flipping them since we want to recreate the old name
        mov     rdi, [new_name]
        
        mov     rax, link               ; Create a link with old name pointing to new name
        syscall

        ret
        


;Errors
error_in_mkfile:
        mov     rdi, mkfile_error_MSG
        call    puts
        jmp     exit

error_dirCreate:
        mov    rdi, mkdir_error_MSG
        call    puts
        jmp     exit

error_too_few:
        mov     rdi, no_args_MSG
        call    puts
        jmp     exit


;Finishing functions
done:                                   ;Print success and exit
        mov     rdi, success_MSG
        call    puts
        jmp     exit
        
exit:                                   ;Print goodbye and exit 
        mov     rdi, Goodbye_MSG
        call    puts
        mov     rax, sys_exit
        xor     rdi, rdi
        syscall


;Some syscall definitions (so I don't have to put the actual numbers in the program)
sys_exit        equ     60
mkdir           equ     83
link            equ     88
make_file       equ     85
permission      equ     0777o 
rename          equ     82

        section .data
;Constants
mkfile_error_MSG        db      "Unexpected error in make file.",0
mkdir_error_MSG         db      "Unexpected error in make directory",0 
success_MSG             db      "Success!",0
Goodbye_MSG             db      "Goodbye",0
no_args_MSG             db      "Too few args, require 1 minimum",0

;Variables
argc                    dq      0
argv                    dq      0

;Buffer variables :) (could also use registers!! But, I wanted to show I could do this I guess, plus easier naming)
folder_name             dq      "default_folder",0
new_name                dq      "default_new",0
