// IOIO_zap_karetka_4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>



bool SSE_check() {
	uint32_t flag;
	_asm {
		mov eax, 1
		cpuid
		shr edx, 25
		AND EDX, 1
		mov flag, edx
	}
	if (flag)
		return true;
	else
		return false;

}

bool SSE2_check() {
	uint32_t flag;
	_asm {
		mov eax, 1
		cpuid
		shr edx, 26
		AND EDX, 1
		mov flag, edx
	}
	if (flag)
		return true;
	else
		return false;

}

bool SSE3_check() {
	uint32_t flag;
	_asm {
		mov eax, 1
		cpuid
		shr ecx, 0
		AND ecx, 1
		mov flag, ecx
	}
	if (flag)
		return true;
	else
		return false;

}

bool SSSE3_check() {
	uint32_t flag;
	_asm {
		mov eax, 1
		cpuid
		shr ecx, 9
		AND ecx, 1
		mov flag, ecx
	}
	if (flag)
		return true;
	else
		return false;
}

bool SSE4dot1_check() {
	uint32_t flag;
	_asm {
		mov eax, 1
		cpuid
		shr ecx, 19
		AND ecx, 1
		mov flag, ecx
	}
	if (flag)
		return true;
	else
		return false;

}

bool SSE4dot2_check() {
	uint32_t flag;
	_asm {
		mov eax, 1
		cpuid
		shr ecx, 0
		AND ecx, 20
		mov flag, ecx
	}
	if (flag)
		return true;
	else
		return false;

}

bool MMX_check() {
	uint32_t flag;
	_asm {
		mov eax, 1
		cpuid
		shr edx, 23
		AND EDX, 1
		mov flag, edx
	}
	if (flag)
		return true;
	else
		return false;

}


int64_t MMX_PADDQ(int64_t a, int64_t b) {
	int64_t c = 0;
	_asm {
		movq mm0, a
		movq mm1, b
		paddq mm0, mm1
		movq c,  mm0
		emms
	}
	return c;

}

int64_t MMX_PSUBQ(int64_t a, int64_t b) {
	int64_t c = 0;
	_asm {
		movq mm0, a
		movq mm1, b
		psubq mm0, mm1
		movq c, mm0
		emms
	}
	return c;

}

int32_t MMX_PADDD(int32_t a, int32_t b) {
	int32_t c = 0;
	_asm {
		movd mm0, a
		movd mm1, b
		paddd mm0, mm1
		movd c, mm0
		emms
	}
	return c;

}

int32_t MMX_PSUBD(int32_t a, int32_t b) {
	int32_t c = 0;
	_asm {
		movd mm0, a
		movd mm1, b
		psubd mm0, mm1
		movd c, mm0
		emms
	}
	return c;

}

void SSE_ADDPS(int64_t a, int64_t b, int64_t c, int64_t d, int64_t &result1, int64_t &result2) {
	int64_t temp1;
	int64_t temp2;
	_asm {
		movlps xmm0, a
		movlps xmm1, b
		movhps xmm0, c
		movhps xmm1, d
		addps xmm0, xmm1
		movq temp1, xmm0
		punpckhqdq xmm0, xmm0
		movq temp2, xmm0
	}
	result1 = temp1;
	result2 = temp2;
}

void SSE_SUBPS(int64_t a, int64_t b, int64_t c, int64_t d, int64_t& result1, int64_t& result2) {
	int64_t temp1;
	int64_t temp2;
	_asm {
		movhps xmm0, a
		movhps xmm1, b
		movlps xmm0, c
		movlps xmm1, d
		subps xmm0, xmm1
		movq temp1, xmm0
		punpckhqdq xmm0, xmm0
		movq temp2, xmm0
	}
	result1 = temp1;
	result2 = temp2;
}

int64_t SSE_ADDSS(int64_t a, int64_t b) {
	int64_t c = 0;
	_asm {
		movsd xmm0, a
		movsd xmm1, b
		addss xmm0, xmm1
		movsd c, xmm0
	}
	return c;
}

int64_t SSE_SUBSS(int64_t a, int64_t b) {
	int64_t c = 0;
	_asm {
		movsd xmm0, a
		movsd xmm1, b
		subss xmm0, xmm1
		movsd c, xmm0
	}
	return c;
}

void cpuid() {
	std::cout << std::boolalpha << "SSE: " << SSE_check() << std::endl;
	std::cout << "SSE2: " << SSE2_check() << std::endl;
	std::cout << "SSE3: " << SSE3_check() << std::endl;
	std::cout << "SSSE3: " << SSSE3_check() << std::endl;
	std::cout << "SSE4.1: " << SSE4dot1_check() << std::endl;
	std::cout << "SSE4.2: " << SSE4dot2_check() << std::endl;
	std::cout << "MMX: " << MMX_check() << std::endl << std::endl;
}

void mmx() {
	int64_t a_64 = 0x0fffffff00000000;
	int64_t b_64 = 0x00000000ffffffff;
	int32_t a_32 = 0x0fff0000;
	int32_t b_32 = 0x0000ffff;
	std::cout << std::setfill('/') << std::setw(47) << '/' << std::endl << std::endl;
	std::cout << std::setw(0) << "Instrukcje MMX\n" << std::endl;
	std::cout << std::hex << std::setfill('0');

	std::cout << std::setw(1) << "Instrucje na 64 bitach" << std::endl;
	std::cout << "a_64 = 0x" << std::setw(16) << a_64 << std::endl << std::setw(1) << "b_64 = 0x" << std::setw(16) << b_64 << std::endl;
	std::cout << std::setw(1) << "PADDQ a_64, b_64 = 0x" << std::setw(16) << MMX_PADDQ(a_64, b_64) << std::endl;
	std::cout << std::setw(1) << "PSUBQ a_64, b_64 = 0x" << std::setw(16) << MMX_PSUBQ(a_64, b_64) << std::endl << std::endl;

	std::cout << std::setw(1) << "Instrucje na 32 bitach" << std::endl;
	std::cout << "a_32 = 0x" << std::setw(8) << a_32 << std::endl << std::setw(1) << "b_32 = 0x" << std::setw(8) << b_32 << std::endl;
	std::cout << std::setw(1) << "PADDD a_32, b_32 = 0x" << std::setw(8) << MMX_PADDD(a_32, b_32) << std::endl;
	std::cout << std::setw(1) << "PSUBD a_32, b_32 = 0x" << std::setw(8) << MMX_PSUBD(a_32, b_32) << std::endl << std::endl;
}

void xmm() {
	int64_t a_64 = 0x0fffffff00000000;
	int64_t b_64 = 0x00000000ffffffff;
	int64_t c_64 = 0x0f00000000000000;
	int64_t d_64 = 0x000000000000000f;
	int64_t a_b = 0x0;
	int64_t c_d = 0x0;
	std::cout << std::setfill('/') << std::setw(47) << '/' << std::endl << std::endl;
	std::cout << std::setw(1) << std::setfill('0') << "Instrukcje SSE\n" << std::endl;
	std::cout << std::hex << std::setfill('0');
	std::cout << "a_64 = 0x" << std::setw(16) << a_64 << std::endl << std::setw(1) << "b_64 = 0x" << std::setw(16) << b_64 << std::endl;
	std::cout << "c_64 = 0x" << std::setw(16) << c_64 << std::endl << std::setw(1) << "d_64 = 0x" << std::setw(16) << d_64 << std::endl << std::endl;
	std::cout << std::setw(1) << "Instrukcje na wektorach (128 bitach)" << std::endl << std::endl;

	std::cout << std::setw(1) << "XMM0 = | C+D | A+B |" << std::endl;
	SSE_ADDPS(a_64, b_64, c_64, d_64, a_b, c_d);
	std::cout << "A+B = 0x" << std::setw(16) << a_b << std::endl << "C+D = 0x" << std::setw(16) << c_d << std::endl << std::endl;

	std::cout << std::setw(1) << "XMM0 = | A-B | C-D |" << std::endl;
	SSE_SUBPS(a_64, b_64, c_64, d_64, a_b, c_d);
	std::cout << "A-B = 0x" << std::setw(16) << a_b << std::endl << "C-D = 0x" << std::setw(16) << c_d << std::endl << std::endl;
	


	std::cout << std::setw(1) << "Instrukcje na skalarach (32 bitach)" << std::endl << std::endl;
	std::cout << std::setw(1) << "XMM0 = | 0 | 0 | 0 | A+B |" << std::endl;
	std::cout << std::setw(1) << "A + B [dolne 32 bity] = 0x" << std::setw(8) << SSE_ADDSS(b_64, c_64) << std::endl << std::endl;
	std::cout << std::setw(1) << "XMM0 = | 0 | 0 | 0 | D-C |" << std::endl;
	std::cout << std::setw(1) << "D - C [dolne 32 bity] = 0x" << std::setw(8) << SSE_SUBSS(d_64, c_64) << std::endl << std::endl;
}


int main()
{
	cpuid();
	mmx();
	xmm();
}