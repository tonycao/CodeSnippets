#include <cstdio>
#include <cassert>

using namespace std;

void* Memcpy(void *dst, const void *src, size_t size) {
	char *psrc;
	char *pdst;

	if (dst == nullptr || src == nullptr) {
		return nullptr;
	}

	if ((src < dst) && (char*) src + size > (char*)dst) { // copy from back to front
		psrc = (char*) src + size - 1;
		pdst = (char*) dst + size - 1;
		while (size--) {
			*pdst-- = *psrc--;
		}
	} else {
		psrc = (char*)src;
		pdst = (char*)dst;
		while (size--) {
			*pdst++ = *psrc++;
		}
	}
	
	return dst;

}

int main(int argc, char *argv[])  
{  
    char buf[100] = "abcdefghijk";  
    Memcpy(buf+2, buf, 5);  
    //Memcpy(buf+2, buf, 5);  
    printf("%s\n", buf+2);  
   
    return 0;  
}  