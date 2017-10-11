交互式文本编辑器, 如 Vim, 
可以用键盘命令来交互式地插入/删除或替换数据中的文本.

sed编辑器, 也称 流编辑器. 
在编辑器处理数据之前基于预先提供的一组规则来编辑数据流.

每次从输入中读取一行, 用提供的编辑器命令匹配数据, 按命令中指定的方式修改流中的数据, 然后将生成的数据输出到STDOUT.

*********************************************************************************
sed命令格式:
sed [-e script, -f file, -n] script file

	1. 在命令行使用编辑器命令
$ echo "this is a test" | sed 's/test/big test/'
this is a big test

$ echo "this is a test" | sed 's/test/big test/' > test.txt
$ cat test.txt
this is a big test

	2. [-e script] 在命令行使用多个编辑器命令
$ echo "this is a cat" | sed -e 's/cat/egg/;s/a/an/'
this is an egg
命令之间用分号分隔, 分号前后不能有空格.

	3. [-f file] 从文件中读取编辑器命令
$ cat script.s 
s/cat/dog/
s/a/an/
$ echo "this is a cat" | sed -f script.s
this is an dog

**********************************************************************************
**********************************************************************************

替换命令 s (substitute命令):
s命令, 在默认情况下只替换每行中出现的第一处.
要让替换命令对一行中不同地方出现的文本都起作用, 必须使用替换标记(substitution flag):
s/pattern/replacement/flags

(1) 数字, 替换第n处文本
$ echo "this is a cat cat cat" | sed 's/cat/dog/2'
this is a cat dog cat

(2) g 替换所有
$ echo "this is a cat cat cat" | sed 's/cat/dog/g'
this is a dog dog dog

(3) p 表明原来行的内容要打印出来

(4) w file, 将替换的结果写到文件中
$ echo "this is a cat" | sed 's/cat/dog/w wfile.txt' 
this is a dog
$ ls
wfile.txt
$ cat wfile.txt 
this is a dog


s命令替换字符
$ echo "/bin/bash" | sed 's/\/bin\/bash/\/bin\/sh/'
/bin/sh

$ echo "/bin/bash" | sed 's!/bin/bash!/bin/sh!'
/bin/sh
感叹号被用作字符串分隔符, 使得路径名很容易被读取和理解.

*********************************************************
删除行: 删除命令d
$ cat data.txt 
line 1
line 2
line 3
line 4
$ sed '3d' data.txt 
line 1
line 2
line 4

$ cat data.txt | sed '1,3d'
line 4

$ cat data.txt | sed '/line 1/d'
line 2
line 3
line 4

********************************************************
插入(insert)命令i  --> 在指定行前增加新行
追加(append)命令a     --> 在指定行后增加新行
$ cat data.txt | sed '2i\new line\'
line 1
new line
line 2
line 3
line 4

$ cat data.txt | sed '2a\new line\'
line 1
line 2
new line
line 3
line 4

*********************************************************
修改行: 修改(change)命令c
$ cat data.txt | sed '3c\changed line\'
line 1
line 2
changed line
line 4

********************************************************
转换命令y  --> 唯一可以处理单个字符的sed编辑器命令.
$ echo " 1 3 5 2 4 " | sed 'y/12345/67890/'
 6 8 0 7 9

**********************************************************************************
**********************************************************************************
sed 和 文件

	1. 向文件写入
	w命令格式
	[address]w filename
	
	$ cat data.txt 
	line 1
	line 2
	line 3
	line 4
	$ sed '1,2w wfile.txt' data.txt 
	line 1
	line 2
	line 3
	line 4
	$ ls
	data.txt  wfile.txt
	$ cat wfile.txt 
	line 1
	line 2
	
	
	2. 从文件读取数据
	读取命令格式:
	[address]r filename
	
	[ld@localhost Documents]$ cat data.txt 
	line 1
	line 2
	line 3
	line 4
	[ld@localhost Documents]$ cat wfile.txt 
	line 1
	line 2
	[ld@localhost Documents]$ sed '3r wfile.txt' data.txt 
	line 1
	line 2
	line 3
	line 1
	line 2
	line 4
	
	3. 读取命令和删除命令合用 --> 用另一文件中的数据替换文件中的占位文本.
	例如: 套用信件:
	[ld@localhost Documents]$ cat letter.txt 
	would the following people:
	LIST
	please report to the office.
	[ld@localhost Documents]$ cat people.txt 
	tom, kitty
	jack, rose
	[ld@localhost Documents]$ sed '/LIST/{
	> r people.txt
	> d
	> }' letter.txt
	would the following people:
	tom, kitty
	jack, rose
	please report to the office.
	

********************************************************
使用地址
在sed编辑器中, 有两种形式的行寻址:
	- 行的数字范围, 可用逗号隔开
	- 用文本模式来过滤出某行
	
文本模式过滤器格式:
/pattern/command


********************************************************
