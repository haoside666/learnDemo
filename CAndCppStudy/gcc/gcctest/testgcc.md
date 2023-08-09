## 1、GCC的编译流程

GCC的编译流程分为4个阶段:

### (1) 预处理（Preprocessing）

```shell
$ gcc -E file.c -o file.i
```

注：如果没有“`-o  file.i`”，其结果只会输出到标准输出。

### (2) 编译（Compiling）：生成汇编代码

```shell
$ gcc -S file.i -o file.s
$ gcc -S file.c
```

注：上述命令会自动生成`file.s`文件（不用添加“`-o`”选项）。如果编译多个源文件，会为每个源文件都生成一个汇编语言模块。

### (3) 汇编（Assembling）：生成目标代码

```shell
$ gcc   -c  file.s -o file.o
$ gcc   -c  file.c
```

注：上述命令会自动生成`file.o`文件（不用添加“`-o`”选项）。

### (4) 链接（Linking）：生成二进制可执行程序

```shell
$ gcc file.o          // 生成a.out文件
$ gcc file.o -o file  // 生成file文件
```

注：生成最终的可执行文件的命令如果没有用“`-o`”选项指定，则默认输出为`a.out`。

以上四步可以单独执行，也可以合并在一起形成一条命令执行。

```shell
$ gcc (-g) -o file file.c //生成file文件
```



