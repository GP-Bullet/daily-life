#include "strbuf.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <gtest/gtest.h>


// #define __SA_TEST__
#ifndef __SA_TEST__
// 获取由 malloc 类函数分配的 buf 的大小
// 本函数依赖 ptmalloc 实现
size_t getChunkSize(const void *pr) {
    size_t size = *(const size_t *) ((char *) pr - sizeof(size_t));
    return size & (~3);
}

// 本函数依赖 ptmalloc 实现
size_t getChunkFd(const void *pr) { return *(const size_t *) pr; }


// 不要在意这些常量
#define SIZE_SZ (sizeof(size_t))
#define MALLOC_ALIGNMENT (2 * SIZE_SZ < __alignof__(long double) \
                                  ? __alignof__(long double)     \
                                  : 2 * SIZE_SZ)
#define MIN_CHUNK_SIZE (4 * SIZE_SZ)

#define MALLOC_ALIGN_MASK (MALLOC_ALIGNMENT - 1)
#define MINSIZE \
    (unsigned long) (((MIN_CHUNK_SIZE + MALLOC_ALIGN_MASK) & ~MALLOC_ALIGN_MASK))

#define request2size(req) \
    (((req) + SIZE_SZ + MALLOC_ALIGN_MASK < MINSIZE) ? MINSIZE : ((req) + SIZE_SZ + MALLOC_ALIGN_MASK) & ~MALLOC_ALIGN_MASK)

//若一个由 malloc/realloc/calloc 申请的 buf 的大小一定不为 size 则返回 false，否则返回 true
// char * pr= malloc(0x20);
// AssertBufSize(pr , 0x20) 返回 true
// AssertBufSize(pr , 0x30) 返回 false
// 本函数依赖 ptmalloc 实现
#define AssertBufSize(pr, size) ASSERT_EQ(getChunkSize(pr), request2size(size))
#else

#define AssertBufSize(pr, size)

#endif
#define AssertStrbufAlloced(x) AssertBufSize((x)->buf, (x)->alloc)
#define AssertStrbufLen(x) ASSERT_GT((x)->alloc, (x)->len)

// 2A
TEST(strBufTest2A, init1) {
    strbuf t;
    strbuf_init(&t, 0x10);
    ASSERT_EQ(t.alloc, 0x10);
    ASSERT_EQ(t.len, 0);
    AssertBufSize(t.buf, 0x10);
    strbuf_release(&t);
}

TEST(strBufTest2A, init2) {
    strbuf t;
    strbuf_init(&t, 0x20);
    ASSERT_EQ(t.alloc, 0x20);
    ASSERT_EQ(t.len, 0);
    AssertBufSize(t.buf, 0x20);
    strbuf_release(&t);
}

TEST(strBufTest2A, init3) {
    strbuf t;
    strbuf_init(&t, 0x5);
    ASSERT_EQ(t.alloc, 0x5);
    ASSERT_EQ(t.len, 0);
    AssertBufSize(t.buf, 0x5);
    strbuf_release(&t);
}

TEST(strBufTest2A, init4) {
    strbuf t;
    strbuf_init(&t, 0x0);
    ASSERT_EQ(t.alloc, 0x0);
    ASSERT_EQ(t.len, 0);
    AssertBufSize(t.buf, 0x0);
    strbuf_release(&t);
}
TEST(strBufTest2A, attach1) {

    strbuf t;
    char *a = (char *) malloc(0x10);
    strcpy(a, "1234");
    strbuf_attach(&t, a, 4, 0x10);
    ASSERT_EQ(t.len, 4);
    ASSERT_EQ(t.alloc, 0x10);
    ASSERT_EQ(t.buf, a);
    ASSERT_STREQ(t.buf, "1234");
    strbuf_release(&t);
}

TEST(strBufTest2A, attach2) {
    strbuf t;
    char *a = (char *) malloc(0x18);
    strcpy(a, "123456789abcdef12234567");
    strbuf_attach(&t, a, 0x17, 0x20);
    ASSERT_EQ(t.alloc, 0x20);
    ASSERT_EQ(t.buf, a);
    ASSERT_EQ(t.len, 0x17);
    ASSERT_STREQ(t.buf, "123456789abcdef12234567");
    strbuf_release(&t);
}

TEST(strBufTest2A, attach3) {
    strbuf t;
    char *a = (char *) malloc(0x18);
    char str[] = "123456789abcdef12234567";
    str[6] = '\0';
    memcpy(a, str, 0x17);
    strbuf_attach(&t, a, 0x17, 0x20);
    ASSERT_EQ(t.alloc, 0x20);
    ASSERT_EQ(t.buf, a);
    ASSERT_EQ(t.len, 0x17);
    int ret = memcmp(t.buf, str, 0x17);
    ASSERT_EQ(ret, 0);
    strbuf_release(&t);
}
TEST(strBufTest2A, release1) {
    strbuf t;
    char *a = (char *) malloc(0x18);
    strcpy(a, "123456789abcdef12234567");
    strbuf_attach(&t, a, 0x17, 0x20);
    //测试内存是否被释放
#ifndef __SA_TEST__
    size_t backUp = getChunkFd(t.buf);
#endif
    strbuf_release(&t);
#ifndef __SA_TEST__
    if (t.buf != nullptr) {
        size_t fd = getChunkFd(t.buf);
        ASSERT_NE(backUp, fd);
    }
#endif
    strbuf_init(&t, 0x20);
    ASSERT_EQ(t.alloc, 0x20);
    ASSERT_EQ(t.len, 0);
    strbuf_release(&t);
}

TEST(strBufTest2A, swap1) {
    char *buf[2];
    buf[0] = (char *) malloc(0x20);
    buf[1] = (char *) malloc(0x30);
    strcpy(buf[0], "123456");
    strcpy(buf[1], "abcdefg");
    strbuf t[2];
    strbuf_attach(&t[0], buf[0], 6, 0x20);
    strbuf_attach(&t[1], buf[1], 7, 0x30);

    strbuf_swap(t, t + 1);

    ASSERT_EQ(t[0].alloc, 0x30);
    ASSERT_EQ(t[0].len, 7);
    ASSERT_EQ(t[0].buf, buf[1]);
    ASSERT_STREQ(t[0].buf, "abcdefg");
    AssertBufSize(t[0].buf, 0x30);

    ASSERT_EQ(t[1].alloc, 0x20);
    ASSERT_EQ(t[1].len, 6);
    ASSERT_EQ(t[1].buf, buf[0]);
    ASSERT_STREQ(t[1].buf, "123456");
    AssertBufSize(t[1].buf, 0x20);
    strbuf_release(&t[0]);
    strbuf_release(&t[1]);
}

TEST(strBufTest2A, detach1) {
    strbuf t;
    char *a = (char *) malloc(0x10);
    strcpy(a, "1234");
    strbuf_attach(&t, a, 4, 0x10);
    size_t size;
    char *ret = strbuf_detach(&t, &size);
    ASSERT_EQ(0x10, size);
    ASSERT_EQ(ret, a);
    ASSERT_STREQ(ret, "1234");
    free(a);
}

TEST(strBufTest2A, cmp1) {
    char *buf[2];
    buf[0] = (char *) malloc(0x20);
    buf[1] = (char *) malloc(0x30);
    strcpy(buf[0], "123456");
    strcpy(buf[1], "abcdefg");
    strbuf t[2];
    strbuf_attach(&t[0], buf[0], 6, 0x20);
    strbuf_attach(&t[1], buf[1], 7, 0x30);

    ASSERT_TRUE(strbuf_cmp(&t[0], &t[1]) != 0);

    ASSERT_EQ(t[0].alloc, 0x20);
    ASSERT_EQ(t[0].len, 6);
    ASSERT_EQ(t[0].buf, buf[0]);
    ASSERT_STREQ(t[0].buf, "123456");
    AssertBufSize(t[0].buf, 0x20);

    ASSERT_EQ(t[1].alloc, 0x30);
    ASSERT_EQ(t[1].len, 7);
    ASSERT_EQ(t[1].buf, buf[1]);
    ASSERT_STREQ(t[1].buf, "abcdefg");
    AssertBufSize(t[1].buf, 0x30);
    strbuf_release(&t[0]);
    strbuf_release(&t[1]);
}

TEST(strBufTest2A, cmp2) {

    char *buf[2];
    buf[0] = (char *) malloc(0x20);
    buf[1] = (char *) malloc(0x30);
    strcpy(buf[0], "123456");
    strcpy(buf[1], "123456");
    strbuf t[2];
    strbuf_attach(&t[0], buf[0], 6, 0x20);
    strbuf_attach(&t[1], buf[1], 6, 0x30);

    ASSERT_TRUE(strbuf_cmp(&t[0], &t[1]) == 0);

    ASSERT_EQ(t[0].alloc, 0x20);
    ASSERT_EQ(t[0].len, 6);
    ASSERT_EQ(t[0].buf, buf[0]);
    ASSERT_STREQ(t[0].buf, "123456");
    AssertBufSize(t[0].buf, 0x20);

    ASSERT_EQ(t[1].alloc, 0x30);
    ASSERT_EQ(t[1].len, 6);
    ASSERT_EQ(t[1].buf, buf[1]);
    ASSERT_STREQ(t[1].buf, "123456");
    AssertBufSize(t[1].buf, 0x30);
    strbuf_release(&t[0]);
    strbuf_release(&t[1]);
}

TEST(strBufTest2A, cmp3) {

    char *buf[2];
    buf[0] = (char *) malloc(0x20);
    buf[1] = (char *) malloc(0x20);
    strcpy(buf[0], "123456");
    strcpy(buf[1], "123");
    strbuf t[2];
    strbuf_attach(&t[0], buf[0], 6, 0x20);
    strbuf_attach(&t[1], buf[1], 3, 0x20);

    ASSERT_TRUE(strbuf_cmp(&t[0], &t[1]) != 0);

    ASSERT_EQ(t[0].alloc, 0x20);
    ASSERT_EQ(t[0].len, 6);
    ASSERT_EQ(t[0].buf, buf[0]);
    ASSERT_STREQ(t[0].buf, "123456");
    AssertBufSize(t[0].buf, 0x20);

    ASSERT_EQ(t[1].alloc, 0x20);
    ASSERT_EQ(t[1].len, 3);
    ASSERT_EQ(t[1].buf, buf[1]);
    ASSERT_STREQ(t[1].buf, "123");
    AssertBufSize(t[1].buf, 0x20);
    strbuf_release(&t[0]);
    strbuf_release(&t[1]);
}
TEST(strBufTest2A, reset1) {
    strbuf t;
    char *a = (char *) malloc(0x10);
    strcpy(a, "1234");
    strbuf_attach(&t, a, 4, 0x10);
    strbuf_reset(&t);
    ASSERT_EQ(t.len, 0);
    ASSERT_EQ(t.alloc, 0x10);
    AssertBufSize(t.buf, 0x10);
    strbuf_release(&t);
}

TEST(strBufTest2A, reset2) {
    strbuf t;
    char *a = (char *) malloc(0x10);
    strcpy(a, "1234");
    strbuf_attach(&t, a, 4, 0x10);
    strbuf_reset(&t);
    ASSERT_EQ(t.len, 0);
    ASSERT_EQ(t.alloc, 0x10);
    AssertBufSize(t.buf, 0x10);
    strbuf_release(&t);
}

// 2B测试代码

// 确保在len之后strbuf中至少有extra个字节的空闲空间可用。
TEST(StrBufTest2B, grow) {
    strbuf sb;
    strbuf_init(&sb, 0);

    strbuf_grow(&sb, 0);
    ASSERT_GE((sb.alloc - sb.len), 0);
    ASSERT_EQ(sb.len, 0);

    strbuf_grow(&sb, 10);
    ASSERT_GE((sb.alloc - sb.len), 10);
    ASSERT_EQ(sb.len, 0);
    AssertStrbufAlloced(&sb);

    strbuf_grow(&sb, 5);
    ASSERT_GE((sb.alloc - sb.len), 5);
    ASSERT_EQ(sb.len, 0);
    AssertStrbufAlloced(&sb);

    strbuf_grow(&sb, 20);
    ASSERT_GE((sb.alloc - sb.len), 20);
    ASSERT_EQ(sb.len, 0);
    AssertStrbufAlloced(&sb);

    strbuf_release(&sb);
}

// strbuf_add，向sb追加长度为len的数据data。
TEST(StrBufTest2B, add) {
    strbuf sb;
    strbuf_init(&sb, 20);

    strbuf_add(&sb, "hello", 5);
    ASSERT_EQ(sb.len, 5);
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_STREQ("hello", sb.buf);
    AssertBufSize(sb.buf, sb.alloc);

    strbuf_add(&sb, "world", 5);
    ASSERT_EQ(sb.len, 10);
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_STREQ("helloworld", sb.buf);
    AssertBufSize(sb.buf, sb.alloc);

    strbuf_add(&sb, nullptr, 0);
    ASSERT_EQ(sb.len, 10);
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_STREQ("helloworld", sb.buf);
    AssertBufSize(sb.buf, sb.alloc);

    strbuf_release(&sb);
}

// strbuf_addch，向sb追加一个字符c。
TEST(StrBufTest2B, addch1) {
    strbuf sb;
    strbuf_init(&sb, 20);

    strbuf_addch(&sb, 'h');
    strbuf_addch(&sb, 'e');
    strbuf_addch(&sb, 'l');
    strbuf_addch(&sb, 'l');
    strbuf_addch(&sb, 'o');
    strbuf_addch(&sb, 'w');
    strbuf_addch(&sb, 'o');
    strbuf_addch(&sb, 'r');
    strbuf_addch(&sb, 'l');
    strbuf_addch(&sb, 'd');
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_EQ(sb.len, 10);
    ASSERT_STREQ("helloworld", sb.buf);
    AssertBufSize(sb.buf, sb.alloc);

    strbuf_release(&sb);
}

TEST(StrBufTest2B, addch2) {
    strbuf sb;
    strbuf_init(&sb, 10);

    for (int i = 0; i < 4; i++) {
        strbuf_addch(&sb, 'h');
        strbuf_addch(&sb, 'e');
        strbuf_addch(&sb, 'l');
        strbuf_addch(&sb, 'l');
        strbuf_addch(&sb, 'o');
        strbuf_addch(&sb, 'w');
        strbuf_addch(&sb, 'o');
        strbuf_addch(&sb, 'r');
        strbuf_addch(&sb, 'l');
        strbuf_addch(&sb, 'd');

        AssertBufSize(sb.buf, sb.alloc);
        ASSERT_EQ(sb.len, 10 * (i + 1));
    }
    ASSERT_STREQ(sb.buf, "helloworldhelloworldhelloworldhelloworld");
    strbuf_release(&sb);
}

// strbuf_addstr，向sb追加一个字符串s。
TEST(StrBufTest2B, addstr1) {
    strbuf sb;
    strbuf_init(&sb, 20);

    strbuf_addstr(&sb, "hello");
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_EQ(sb.len, 5);
    ASSERT_STREQ(sb.buf, "hello");

    strbuf_addstr(&sb, "world");
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_EQ(sb.len, 10);
    ASSERT_STREQ(sb.buf, "helloworld");

    strbuf_release(&sb);
}

TEST(StrBufTest2B, addstr2) {
    strbuf sb;
    strbuf_init(&sb, 20);

    strbuf_addstr(&sb, "helloworld");
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_EQ(sb.len, 10);
    ASSERT_STREQ(sb.buf, "helloworld");

    strbuf_addstr(&sb, "helloworld");
    ASSERT_EQ(sb.len, 20);
    ASSERT_STREQ(sb.buf, "helloworldhelloworld");
    AssertBufSize(sb.buf, sb.alloc);

    strbuf_addstr(&sb, "helloworld");
    ASSERT_EQ(sb.len, 30);
    ASSERT_STREQ(sb.buf, "helloworldhelloworldhelloworld");
    AssertBufSize(sb.buf, sb.alloc);

    strbuf_addstr(&sb, "helloworld");
    ASSERT_EQ(sb.len, 40);
    ASSERT_STREQ(sb.buf, "helloworldhelloworldhelloworldhelloworld");
    AssertBufSize(sb.buf, sb.alloc);

    strbuf_addstr(&sb, "helloworld");
    ASSERT_EQ(sb.len, 50);
    ASSERT_STREQ(sb.buf, "helloworldhelloworldhelloworldhelloworldhelloworld");
    AssertBufSize(sb.buf, sb.alloc);

    strbuf_addstr(&sb, "1234");
    ASSERT_EQ(sb.len, 54);
    ASSERT_STREQ(sb.buf, "helloworldhelloworldhelloworldhelloworldhelloworld1234");
    AssertBufSize(sb.buf, sb.alloc);

    strbuf_release(&sb);
}

// strbuf_addbuf，向一个sb追加另一个strbuf的数据。
TEST(StrBufTest2B, addbuf1) {
    strbuf sb1, sb2, sb3;
    strbuf_init(&sb1, 20);
    strbuf_init(&sb2, 20);
    strbuf_init(&sb3, 20);
    strbuf_addstr(&sb2, "hello");
    strbuf_addstr(&sb3, "world");
    ASSERT_EQ(sb1.len, 0);
    ASSERT_EQ(sb1.alloc, 20);

    strbuf_addbuf(&sb1, &sb2);
    ASSERT_EQ(sb1.len, 5);
    ASSERT_STREQ(sb1.buf, "hello");
    AssertBufSize(sb1.buf, sb1.alloc);
    strbuf_addbuf(&sb1, &sb3);
    ASSERT_EQ(sb1.len, 10);
    ASSERT_STREQ(sb1.buf, "helloworld");
    AssertBufSize(sb1.buf, sb1.alloc);

    strbuf_release(&sb1);
    strbuf_release(&sb2);
    strbuf_release(&sb3);
}

TEST(StrBufTest2B, addbuf2) {
    strbuf sb1, sb2, sb3;
    strbuf_init(&sb1, 0);
    strbuf_init(&sb2, 0);
    strbuf_init(&sb3, 0);
    strbuf_addstr(&sb2, "helloworldhelloworldhelloworldhelloworld12");
    strbuf_addstr(&sb3, "helloworldhelloworldhelloworldhelloworld34");

    strbuf_addbuf(&sb1, &sb2);
    ASSERT_EQ(sb1.len, 42);
    ASSERT_STREQ(sb1.buf, "helloworldhelloworldhelloworldhelloworld12");
    AssertBufSize(sb1.buf, sb1.alloc);
    strbuf_addbuf(&sb1, &sb3);
    ASSERT_EQ(sb1.len, 84);
    ASSERT_STREQ(sb1.buf, "helloworldhelloworldhelloworldhelloworld12helloworldhelloworldhelloworldhelloworld34");
    AssertBufSize(sb1.buf, sb1.alloc);
    strbuf_release(&sb1);
    strbuf_release(&sb2);
    strbuf_release(&sb3);
}

// strbuf_setlen，设置sb的长度len。
TEST(StrBufTest2B, setlen) {
    strbuf sb;
    strbuf_init(&sb, 20);
    strbuf_addstr(&sb, "123456789012345678");
    ASSERT_EQ(sb.len, 18);
    ASSERT_EQ(sb.buf[18], '\0');

    strbuf_setlen(&sb, 10);
    ASSERT_EQ(sb.len, 10);
    ASSERT_EQ(sb.buf[10], '\0');

    strbuf_setlen(&sb, 5);
    ASSERT_EQ(sb.len, 5);
    ASSERT_EQ(sb.buf[5], '\0');

    strbuf_setlen(&sb, 0);
    ASSERT_EQ(sb.len, 0);
    ASSERT_EQ(sb.buf[0], '\0');

    strbuf_release(&sb);
}

// strbuf_avail，计算 sb 目前仍可以向后追加的字符串长度。
TEST(StrBufTest2B, avail) {
    strbuf sb;
    strbuf_init(&sb, 10);

    int avail = strbuf_avail(&sb);
    ASSERT_EQ(sb.alloc, 10);
    ASSERT_EQ(sb.len, 0);
    ASSERT_EQ(avail, (sb.alloc - sb.len - 1));

    strbuf_addstr(&sb, "hello");
    avail = strbuf_avail(&sb);
    ASSERT_EQ(sb.alloc, 10);
    ASSERT_EQ(sb.len, 5);
    ASSERT_EQ(avail, (sb.alloc - sb.len - 1));

    strbuf_release(&sb);
}

// strbuf_insert，向 sb 内存坐标为 pos 位置插入长度为 len 的数据 data。
TEST(StrBufTest2B, insert) {
    strbuf sb;
    strbuf_init(&sb, 20);

    strbuf_addstr(&sb, "abcdefghi");
    strbuf_insert(&sb, 2, "hello", 5);
    ASSERT_STREQ(sb.buf, "abhellocdefghi");

    strbuf_release(&sb);
}

// 2C 测试代码

// strbuf_ltrim, 去除 sb 缓冲区左端的所有 空格，tab, '\t'。
TEST(StrBufTest2C, ltrim) {
    strbuf sb;
    strbuf_init(&sb, 20);
    strbuf_addstr(&sb, "\t  he llo ");
    int res;
    res = memcmp(sb.buf, "\t  he llo ", 10);
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_EQ(sb.len, 10);
    ASSERT_EQ(res, 0);

    strbuf_ltrim(&sb);
    res = memcmp(sb.buf, "he llo ", 7);
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_EQ(sb.len, 7);
    ASSERT_EQ(res, 0);

    strbuf_release(&sb);
}

// strbuf_rtrim, 去除 sb 缓冲区右端的所有 空格，tab, '\t'。
TEST(StrBufTest2C, rtrim) {
    strbuf sb;
    strbuf_init(&sb, 20);
    strbuf_addstr(&sb, " he llo\t  ");
    int res;
    res = memcmp(sb.buf, " he llo\t  ", 10);
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_EQ(sb.len, 10);
    ASSERT_EQ(res, 0);

    strbuf_rtrim(&sb);
    res = memcmp(sb.buf, " he llo", 7);
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_EQ(sb.len, 7);
    ASSERT_EQ(res, 0);

    strbuf_release(&sb);
}

// strbuf_remove 删除 sb 缓冲区从 pos 坐标长度为 len 的内容。
TEST(StrBufTest2C, remove) {
    strbuf sb;
    strbuf_init(&sb, 20);
    strbuf_addstr(&sb, "abcdefghij");
    int res;
    res = memcmp(sb.buf, "abcdefghij", 10);
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_EQ(sb.len, 10);
    ASSERT_EQ(res, 0);

    strbuf_remove(&sb, 2, 5);
    res = memcmp(sb.buf, "abhij", 5);
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_EQ(sb.len, 5);
    ASSERT_EQ(res, 0);

    strbuf_release(&sb);
}

TEST(StrBufTest2D, read1) {
    strbuf sb;
    int TestFd = open("strbuf/FileTest/TestforFile_1.txt", O_RDWR, S_IRWXU);
    ASSERT_GT(TestFd, 0);
    strbuf_init(&sb, 0x10);
    strbuf_addstr(&sb, "123");
    size_t oldAlloc = sb.alloc;
    size_t oldLen = sb.len;
    strbuf_read(&sb, TestFd, 0x100);
    ASSERT_STREQ(sb.buf, "123I love coding.");
    ASSERT_EQ(sb.len, 17);
    ASSERT_GT(sb.alloc - oldLen, 0x100);
    AssertStrbufAlloced(&sb);
    close(TestFd);
    strbuf_release(&sb);
}
TEST(StrBufTest2D, read2) {
    strbuf sb;
    strbuf_init(&sb, 0x10);
    strbuf_addstr(&sb, "123");
    int fd = open("strbuf/FileTest/TestforFile_5.txt", O_RDWR, S_IRWXU);
    ASSERT_GT(fd, 0);
    size_t oldAlloc = sb.alloc;
    strbuf_read(&sb, fd, 0x100);
    ASSERT_EQ(sb.alloc, oldAlloc);
    ASSERT_EQ(sb.len, 3);
}

// TEST(StrBufTest2D, readFile) {
//     strbuf TestString;
//     strbuf_read_file(&TestString, "FileTest", 8192);
//     ASSERT_EQ(strcmp(TestString.buf, "I love coding."), 0);
//     strbuf_release(&TestString);
// }

TEST(StrBufTest2D, getline) {
    strbuf sb;
    FILE *fp = fopen("strbuf/FileTest/TestforFile_3.txt", "r");
    strbuf_init(&sb, 0x10);
    strbuf_getline(&sb, fp);
    ASSERT_STREQ(sb.buf, "123123123123");
    strbuf_getline(&sb, fp);
    ASSERT_STREQ(sb.buf, "12312312312312312");
    ASSERT_EQ(fclose(fp), 0);
    strbuf_release(&sb);
}

TEST(StrBufTestCHALLENGE, splitBuf1) {
    char string[] = "14 11 12 123";
    strbuf **result = strbuf_split_buf(string, strlen(string), ' ', 1024);

    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result[4], nullptr);
    AssertBufSize(result, 5 * sizeof(strbuf *));

    ASSERT_EQ(result[0]->len, 2);
    ASSERT_STREQ(result[0]->buf, "14");
    AssertStrbufAlloced(result[0]);
    AssertStrbufLen(result[0]);
    strbuf_release(result[0]);

    ASSERT_EQ(result[1]->len, 2);
    ASSERT_STREQ(result[1]->buf, "12");
    AssertStrbufAlloced(result[1]);
    AssertStrbufLen(result[1]);
    strbuf_release(result[1]);

    ASSERT_EQ(result[2]->len, 2);
    ASSERT_STREQ(result[2]->buf, "12");
    AssertStrbufAlloced(result[2]);
    AssertStrbufLen(result[2]);
    strbuf_release(result[2]);

    ASSERT_EQ(result[3]->len, 3);
    ASSERT_STREQ(result[3]->buf, "123");
    AssertStrbufAlloced(result[3]);
    AssertStrbufLen(result[3]);
    strbuf_release(result[3]);

    free(result);
}
TEST(StrBufTestCHALLENGE, splitBuf2) {

    char string[] = "   123 345    3123   3123  ";
    strbuf **result = strbuf_split_buf(string, strlen(string), ' ', 1024);
    ASSERT_NE(string, nullptr);
    ASSERT_EQ(result[4], nullptr);

    AssertBufSize(result, 5 * sizeof(strbuf *));

    ASSERT_EQ(result[0]->len, 3);
    ASSERT_STREQ(result[0]->buf, "123");
    AssertStrbufAlloced(result[0]);
    AssertStrbufLen(result[0]);
    strbuf_release(result[0]);

    ASSERT_STREQ(result[1]->buf, "345");
    ASSERT_EQ(result[1]->len, 3);
    AssertStrbufAlloced(result[1]);
    AssertStrbufLen(result[1]);
    strbuf_release(result[1]);

    ASSERT_STREQ(result[2]->buf, "3123");
    ASSERT_EQ(result[2]->len, 4);
    AssertStrbufAlloced(result[2]);
    AssertStrbufLen(result[2]);
    strbuf_release(result[2]);

    ASSERT_STREQ(result[3]->buf, "3123");
    ASSERT_EQ(result[3]->len, 4);
    AssertStrbufAlloced(result[3]);
    AssertStrbufLen(result[3]);
    strbuf_release(result[3]);

    free(result);
}

TEST(StrBufTestCHALLENGE, splitBuf3) {

    char string[] = "   123 345    3123   3123  ";
    strbuf **result = strbuf_split_buf(string, strlen(string), ' ', 2);
    ASSERT_NE(string, nullptr);
    ASSERT_EQ(result[2], nullptr);
    AssertBufSize(result, 3 * sizeof(strbuf *));

    ASSERT_EQ(result[0]->len, 3);
    ASSERT_STREQ(result[0]->buf, "123");
    AssertStrbufAlloced(result[0]);
    AssertStrbufLen(result[0]);
    strbuf_release(result[0]);

    ASSERT_STREQ(result[1]->buf, "345");
    ASSERT_EQ(result[1]->len, 3);
    AssertStrbufAlloced(result[1]);
    AssertStrbufLen(result[1]);
    strbuf_release(result[1]);

    free(result);
}
TEST(StrBufTestCHALLENGE, beginJudge) {
    char testString[] = "123f123ddddfan";
    char beginString[] = "123f";
    ASSERT_TRUE(strbuf_begin_judge(testString, beginString, sizeof(testString)));
    char beginString_2[] = "123dddd";
    ASSERT_FALSE(strbuf_begin_judge(testString, beginString_2, sizeof(testString)));
    char *beginString_3 = nullptr;
    ASSERT_TRUE(strbuf_begin_judge(testString, beginString_3, 0));
}

TEST(StrBufTestCHALLENGE, getMidBuf) {
    char targetbuf[] = "123fan123";
    ASSERT_EQ(strcmp(strbuf_get_mid_buf(targetbuf, 3, 6, 10), "fan"), 0);
    char targetbuf_2[] = "\0\n\n\n123123\a\a\a";
    ASSERT_STREQ(strbuf_get_mid_buf(targetbuf_2, 1, 1, 13), "");
    char *tString = nullptr;
    ASSERT_EQ(strbuf_get_mid_buf(tString, 1, 2, 0), nullptr);
}