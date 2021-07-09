.CODE

	code_system_call PROC PUBLIC
		mov r10, rcx							; 
		pop rcx										; 
		pop rax										; 
		mov qword ptr [rsp], rcx	; 
		mov eax, [rsp + 24]				; store system number in eax
		syscall										; execute system call instruction
		sub rsp, 08h							; 
		jmp qword ptr [rsp + 8]		; 
	code_system_call ENDP

END