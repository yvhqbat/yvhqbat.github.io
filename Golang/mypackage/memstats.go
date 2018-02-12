package mypackage

import (
	"fmt"
	"runtime"
)

func MemTest() {
	m := new(runtime.MemStats)
	runtime.ReadMemStats(m)
	fmt.Printf("%d Kb\n", m.Alloc/1024) //m.Alloc为已分配内存总量
}
