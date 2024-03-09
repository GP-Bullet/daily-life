当你在Makefile中声明一个目标时，Make会默认假设这个目标是一个实际的文件，并尝试通过检查目标文件的时间戳来确定是否需要重新构建。但是，如果你声明一个目标为伪目标（使用.PHONY声明），Make会忽略目标文件的时间戳，始终执行该目标的命令。

所以，当你在Makefile中使用all作为目标时，如果你不将其声明为伪目标，Make会尝试查找名为all的实际文件，并根据其时间戳来判断是否需要重新构建。如果你将all声明为伪目标（使用.PHONY: all），Make将忽略时间戳，始终执行all目标下的命令。