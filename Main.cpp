#include <iostream>

struct cijfer_t {
	int waarde;
	char *uitspraak;
}; 

int main () {
    char sentence('w');
    struct cijfer_t myCijfer = {12, &sentence};
    std::cout << myCijfer.waarde << std::endl;
    return 0;
}
