## 何时使用new()和make()
- 切片、映射和通道，使用make;
- 数组、结构体和所有的值类型，使用new;

## 区别
二者都是在堆上分配内存，但行为不同，适用于不同的类型。
- `new(T)`为每个新的类型T分配一片内存，初始化为0并且返回类型为`*T`的内存地址。这种方法返回一个指向类型为T，值为0的地址的指针，它适用于值类型（如数组和结构体）。
- `make(T)`返回一个类型为T的初始值，它只适用于3种内建的引用类型（切片、map和channel）;

## 示例

```
	type A struct {
		X int
		Y int
  	}
```

```
	slice := make([]int, 50, 100)
	fmt.Println(len(slice), cap(slice))  // 50 100
  
	array := new([100]int)
	fmt.Println(cap(array))  // 100
  
	a := new(A)
	a.X = 5
	a.Y = 7
	fmt.Println(a)  // &{5 7}
```
