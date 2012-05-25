#include <windows.h>
#include "jogo.h"
int main(){
	SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);
	jogo();
	return 0;
}
