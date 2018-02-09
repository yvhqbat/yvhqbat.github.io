// learnDemo project main.go
package main

import (
	"fmt"
)

/*main函数*/
func main() {

	mapTest()

}

/*===========================================*/

/* Map */
func mapTest() {
	// 1. 先申明再用make创建
	var info map[string]interface{}
	info = make(map[string]interface{})

	// 2. 直接创建
	//info := make(map[string]interface{})

	// 赋值
	info["name"] = "dog"
	info["age"] = 26

	// 大小
	fmt.Println("map size is", len(info))

	// 遍历，for-range
	for key, value := range info {
		fmt.Println(key, value)
	}

	//判断是否存在
	if value, ok := info["name"]; ok {
		fmt.Println(value)
	} else {
		fmt.Println("name is not exist")
	}

	// value是一个数组切片，family:[mam dad brother sister]
	family := []string{"mam", "dad", "brother", "sister"}
	info["family"] = family
	fmt.Println(info)
}

/* 多参数 函数*/
//pt(1, 2, 3, "i love you", false)
func pt(argv ...interface{}) {
	for pos, val := range argv {
		fmt.Println(pos, val)
	}
}
