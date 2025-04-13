#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf
#include <netinet/in.h> // for htons, htonl

void Cal_files() {

}

int main(int argc, char*argv[]) {
    uint32_t result=0;

    if(argc<2){
        printf("Usage: %s<file1> <file2>...\n",argv[0]);
        return 1;
    }

    for(int i=1; i<argc;i++){
        FILE*file=fopen(argv[i],"rb");
        if(file==NULL){
            printf("Error %s\n", argv[i]);
            return 1;
        }

        uint32_t num;
        size_t byte_num=fread(&num,1,sizeof(uint32_t),file);
        if(byte_num != sizeof(uint32_t)){
            printf("Error: %s is not long enough", argv[i]);
            fclose(file);
            return 1;
        }
        fclose(file);

        uint32_t oper=ntohl(num);
        printf("%u(0x%08x)", oper, oper);

        if(i<argc-1){
            printf(" + ");
        }
        result+=oper;

    }

    printf(" = %u(0x%08x)",result, result);

    return 0;
}
