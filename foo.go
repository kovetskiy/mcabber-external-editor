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

static module_info_t info_editor = {
	.branch          = MCABBER_BRANCH,
	.api             = MCABBER_API_VERSION,
	.version         = "2.2",
	.description     = "Say messages using external editor",
	.requires        = NULL,
	.init            = EditorInit,
	.uninit          = EditorUninit,
	.next            = NULL,
};

typedef void (*cmdfn) (char*);

void logPrint (char *arg) {
	scr_LogPrint(LPRINT_NORMAL, arg);
}
*/
import "C"
import "unsafe"

func DoEsay(arg *C.char) {
	C.logPrint(C.CString("AAA"))
}

var cDoEsay = DoEsay

func EditorInit() {

	C.cmd_add(
		C.CString("esay"),
		C.CString("Say something to the selected buddy using external editor"),
		0, 0, C.cmdfn(unsafe.Pointer(&cDoEsay)), nil)
}

func EditorUninit() {

}
