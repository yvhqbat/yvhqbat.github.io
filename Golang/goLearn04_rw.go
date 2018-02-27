// rw project main.go
package main

import (
	"bufio"
	"fmt"
	"io"
	"os"

	"io/ioutil"
)

func main() {
	fmt.Println("Hello World!")

	// os.Args  --> 命令行参数列表
	fmt.Println(os.Args[0])

	//rw_cmd()
	rw_file()
	//rw_wholefile()
}

// 示例：读取用户输入
func rw_cmd() {
	// 创建一个读取器，并将其与标准输入绑定
	reader := bufio.NewReader(os.Stdin)

	fmt.Println("please input your name: ")

	// 读取器对象提供一个方法 ReadString(delim byte) ，
	// 该方法从输入中读取内容，直到碰到 delim 指定的字符，然后将读取到的内容连同 delim 字符一起放到缓冲区。
	name, err := reader.ReadString('\n')

	if err == nil {
		fmt.Println("name is", name)
	}
}

// 示例： 文件读写
func rw_file() {
	file, err := os.Open("test.dat")
	if err != nil {
		fmt.Println("open file failed.")
		return
	}
	defer file.Close()

	reader := bufio.NewReader(file)
	for {
		line, err := reader.ReadString('\n')
		fmt.Printf(line)
		if err == io.EOF {
			break
		}
	}

	file_w, _ := os.OpenFile("testwrite.dat", os.O_WRONLY|os.O_CREATE, 0666)
	defer file_w.Close()
	writer := bufio.NewWriter(file_w)
	n, err := writer.WriteString("hello world.\n")
	fmt.Println(n, err)
	writer.Flush()
}

// 示例：读取整个文件
func rw_wholefile() {
	data, err := ioutil.ReadFile("test.dat")
	if err == nil {
		fmt.Printf("%s", data)
	}

	err = ioutil.WriteFile("test_copy.dat", data, 0644)
	if err != nil {
		fmt.Println("write file failed.")
	}
}
