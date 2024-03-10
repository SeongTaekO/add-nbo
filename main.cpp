#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf
#include <netinet/in.h> 


uint32_t read_byte(const char *path) {
    // r (read): 파일을 해당 경로에서 읽어옴
    // b (binary): 파일을 텍스트 형식이 아닌 바이너리 형식으로 처리한다. (바이너리 데이터를 올바르게 처리하기 위함)
    FILE *file = fopen(path, "rb");
    size_t read_data = 0;
    uint32_t data = 0;
    
    if (file != NULL) {
        // size_t fread(void* ptr, size_t size, size_t count, FILE *file);
        // void *ptr: FILE *로부터 읽어온 데이터를 저장할 배열(버퍼)의 포인터
        // size_tsize: ptr에 저장할 배열의 원소 하나의 크기를 입력
        // size_t count: 읽어올 요소의 개수
        // file: 데이터를 읽어올 파일을 가리키는 FILE 포인터
        // 반환값은 읽은 배열의 원소 개수
        // &: c언어에서 해당 기호는 주소 연산자이다. 이것은 변수의 주소를 반환한다.
        read_data = fread(&data, sizeof(data), 1, file);
        
        if (read_data == 1) {
            printf("network byte order: %x\n", data);
            data = ntohl(data);
            printf("host byte order: %x\n", data);
        }
        else {    // fread로 데이터를 얻지 못함
            printf("can't read data");
        }
        fclose(file);
    }
    
    return data;
}

// argc: 인자의 개수를 나타내는 정수. 프로그램 이름을 포함해 커맨드 라인에서 전달된 전체 인수의 개수를 나타냄
// argv[]: 인수를 포인터 배열로 나타낸다. 각 포인터는 커맨드 라인에서 전달된 인수를 가리킨다.
// argv[0]은 프로그램 이름, argv[1], argv[2], ...는 각각 추가적으로 전달된 인수를 가리킨다.
// 이를 통해 프로그램이 커맨드 라인에서 어떤 인수를 받았는지 확인할 수 있다.
int main(int argc, char *argv[]) {
    uint32_t byte1 = read_byte(argv[1]);
    uint32_t byte2 = read_byte(argv[2]);
    int sum = int(byte1) + int(byte2);
    
    printf("\n%d(%x) + %d(%x) = %d\n", byte1, byte1, byte2, byte2, sum);
}
