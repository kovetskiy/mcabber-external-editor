#include <mcabber/logprint.h>
#include <mcabber/commands.h>
#include <mcabber/screen.h>
#include <mcabber/settings.h>
#include <mcabber/modules.h>
#include <mcabber/config.h>

//void go_editor_init (void)  __asm__ ("example_main.editor_init");
extern void go_editor_init (void);
extern void go_editor_uninit (void);

static void editor_init   (void);
static void editor_uninit (void);

module_info_t info_editor = {
        .branch          = MCABBER_BRANCH,
        .api             = MCABBER_API_VERSION,
        .version         = "2.2",
        .description     = "Say messages using external editor",
        .requires        = NULL,
        .init            = editor_init,
        .uninit          = editor_uninit,
        .next            = NULL,
};

static void editor_init() {
    go_editor_init();
}

static void editor_uninit() {
    go_editor_uninit();
}
