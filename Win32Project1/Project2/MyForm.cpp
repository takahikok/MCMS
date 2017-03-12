#include "MyForm.h"

using namespace Project2;

[STAThreadAttribute]
int main() {
	MyForm ^fm = gcnew MyForm();
	fm->ShowDialog();
	return 0;
}
