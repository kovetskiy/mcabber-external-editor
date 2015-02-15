package editor

/*
#cgo pkg-config: mcabber
#cgo LDFLAGS: -shared

#include <mcabber/logprint.h>
#include <mcabber/commands.h>
#include <mcabber/screen.h>
#include <mcabber/settings.h>
#include <mcabber/modules.h>
#include <mcabber/config.h>

void EditorInit(void);
void EditorUninit(void);

typedef void (*cmdfn) (char*);

void logPrint (char *arg) {
	scr_LogPrint(LPRINT_NORMAL, arg);
}
*/
import "C"
import "unsafe"

var cDoEsay = DoEsay
var cEditorInit = EditorInit
var cEditorUninit = EditorUninit

var info_editor = C.module_info_t{
	branch:      (*C.gchar)(C.CString(C.MCABBER_BRANCH)),
	api:         C.MCABBER_API_VERSION,
	version:     (*C.gchar)(C.CString("2.2")),
	description: (*C.gchar)(C.CString("Say messages using external editor")),
	requires:    nil,
	init:        C.module_init_t(unsafe.Pointer(&cEditorInit)),
	uninit:      C.module_uninit_t(unsafe.Pointer(&cEditorUninit)),
	next:        nil,
}

func EditorInit() {
	C.cmd_add(
		C.CString("esay"),
		C.CString("Say something to the selected buddy using external editor"),
		0, 0, C.cmdfn(unsafe.Pointer(&cDoEsay)), nil)
}

func EditorUninit() {

}

func DoEsay(arg *C.char) {
	C.logPrint(C.CString("AAA"))
}
