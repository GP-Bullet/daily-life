
#include <assert.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
int main() {
  char *const name[] = {"何浩源", "刘佳欢", "史站丽", "吴启豪", "封宇腾",
                        "张昊哲", "张钧成", "朱一鸣", "李泉霖", "杨鹏达",
                        "楚梦凡", "王康宁", "王育杰", "胡宇腾", "袁野",
                        "许泽文", "郭天宇", "陈振鑫", "陈欣宇", "颜然",
                        "高鹏",   "魏子涵"};
  int fd = open("/dev/random", O_RDONLY);
  uint64_t seed;
  size_t size = read(fd, &seed, sizeof(seed));
  assert(size == sizeof(seed));
  srand(seed);
  uint64_t idx = rand() % (sizeof(name) / sizeof(char *));

}