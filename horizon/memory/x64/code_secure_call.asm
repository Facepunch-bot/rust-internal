.DATA
	g_arg_data	dq 0

.CODE

	code_secure_call PROC PUBLIC
		pop r11									; store return address in r11
		add rsp, 8							; skip reserved stack space
		mov rax, [rsp + 24]			; store arg_data in rax
		mov r10, [rax]					; store arg_data.m_jmp in r10
		mov [rsp], r10					; store gadget as return address
		mov r10, [rax + 8]			; store arg_data.m_procedure in r10
		mov [rax + 8], r11			; store return address in arg_data.m_procedure
		mov [rax + 16], rdi			; store rdi in arg_data.m_register
		mov g_arg_data, rax			; store rax in g_arg_data
		lea rdi, quit						; store address of quit in rdi
		; mov [rax], rdi					; store quit in arg_data.m_jmp
		; mov rdi, rax						; store rax in rdi
		jmp r10									; jump to arg_data.m_procedure
	quit:
		sub rsp, 16							; 
		; mov rcx, rdi						; restore arg_data
		mov rcx, g_arg_data			; restore arg_data
		; mov rcx, [rsp + 24]			; restore arg_data
		mov rdi, [rcx + 16]			; restore rdi from arg_data.m_register
		jmp qword ptr [rcx + 8]	; jump to arg_data.m_procedure
	code_secure_call ENDP

END