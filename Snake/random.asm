.386
.model flat,stdcall
option casemap:none

.code
Random proc dwSeed:DWORD
	xor eax, eax
	ret
Random endp

end