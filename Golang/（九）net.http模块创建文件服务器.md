## （九）net.http模块创建文件服务器.md

```go
// FileServer project main.go
package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"strings"
)

type FileHandle struct {
}

func (fh *FileHandle) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	path := r.URL.Path[1:]
	data, err := ioutil.ReadFile(string(path))
	if err != nil {
		log.Printf("Error with path %s: %v", path, err)
		w.WriteHeader(404)
		w.Write([]byte("404"))
		return
	}

	if strings.HasSuffix(path, ".html") {
		w.Header().Add("Content-Type", "text/html")
	} else if strings.HasSuffix(path, ".mp4") {
		w.Header().Add("Content-Type", "video/mp4")
	} else if strings.HasSuffix(path, ".jpg") {
		w.Header().Add("Content-Type", "image/jpg")
	} else if strings.HasSuffix(path, ".png") {
		w.Header().Add("Content-Type", "image/png")
	} else {
		w.Header().Add("Content-Type", "otherfile")
	}

	w.Write(data)
}

func main() {
	fmt.Println("starting the server")

	// 多路复用器
	mux := http.NewServeMux()
	fh := new(FileHandle)
	mux.Handle("/", fh)
	err := http.ListenAndServe(":3333", mux)
	if err != nil {
		log.Fatalf("listen and serve failed, %s\n", err)
	}
	fmt.Printf("end\n")
}


```
