package main

/*
#cgo pkg-config: mcabber
#cgo CFLAGS: -fno-PIC
#cgo LDFLAGS: -fno-PIC
*/
import "C"
import "log"

//export go_editor_init
func go_editor_init() {
	log.Printf("%#v", 123123)
}

//export go_editor_uninit
func go_editor_uninit() {
	log.Printf("%#v", 123123)
}

func main() {
}
