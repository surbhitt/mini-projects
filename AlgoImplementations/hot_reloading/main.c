#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <assert.h>
#include <openssl/md5.h>
#include <stdbool.h>
#include <stdio.h>

bool compare_digest(unsigned char md5d[MD5_DIGEST_LENGTH],
                    unsigned char fh[MD5_DIGEST_LENGTH]) {
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
        if (fh[i] != md5d[i])
            return true;
    return false;
}

int main(int argc, char **argv) {
    assert(argc > 1);
    FILE *f;

    unsigned char file_hash[MD5_DIGEST_LENGTH];

    size_t bytes_read;
    bool first_hash = true;

    while (1) {
        f = fopen(argv[1], "rb");
        if (!f) {
            printf("%s", argv[1]);
            perror("[ERR] Error opening file");
            return 1;
        }
        // refresh md5 context
        // and buffer
        unsigned char buffer[1024];
        MD5_CTX md5_context;
        MD5_Init(&md5_context);

        // optimize by storing these chunks
        // upfront at the beginning of the program
        // we can identify which chunk was changed
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), f)) != 0) {
            MD5_Update(&md5_context, buffer, bytes_read);
        }

        unsigned char md5_digest[MD5_DIGEST_LENGTH];
        MD5_Final(md5_digest, &md5_context);
        if (first_hash || compare_digest(md5_digest, file_hash)) {
            if (first_hash)
                printf("[INFO] watching %s\n", argv[1]);
            else
                printf("[INFO] file changed\n");
            for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
                file_hash[i] = md5_digest[i];
            first_hash = false;
        }

        fclose(f);
    }

    /* MD5(f, sizeof(f), md5_digest); */
    /* for (int i = 0; i < MD5_DIGEST_LENGTH; i++) */
    /*     printf("%02x", file_hash[i]); */

    return 0;
}
