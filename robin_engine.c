#include <stdio.h>
#include <string.h>

#include <openssl/crypto.h>
#include <openssl/objects.h>
#include <openssl/engine.h>

static const char *engine_id = "robin_engine";
static const char *engine_name = "Robin engine";

static int robin_engine_init(ENGINE *e)
{
    printf ("%s: %s\n", engine_name, __FUNCTION__);
    
    return 1;
}

static int robin_engine_finish(ENGINE *e)
{
    printf ("%s: %s\n", engine_name, __FUNCTION__);
    return 1;
}

static int robin_engine_ctrl(ENGINE *e, int cmd, long i, void *p, void(*f) ()) 
{
    printf ("%s: %s\n", engine_name, __FUNCTION__);
    switch (cmd) {
        default:
        break;
    }
    return 1;
}

static int robin_engine_rand_bytes (unsigned char *buf, int num){
    printf ("%s: %s: fake rand, output 'A' \n", engine_name, __FUNCTION__);

    if (!buf)
        return 0;

    memset ((void *) buf, (int) 'A', num);

    return 1;
}

static const RAND_METHOD robin_engine_rand = {.bytes = robin_engine_rand_bytes};

static int robin_engine_bind(ENGINE *e, const char *id)
{
    printf ("Loading %s.\n", engine_name);

    if (!ENGINE_set_id(e, engine_id)) {
        printf("ENGINE_set_id failed\n");
        goto end;
	}
	if (!ENGINE_set_name(e, engine_name)) {
        printf("ENGINE_set_name failed\n");
        goto end;
	}

    if (!ENGINE_set_init_function(e, robin_engine_init)) {
		printf("ENGINE_set_init_function failed\n");
		goto end;
	}
	if (!ENGINE_set_finish_function(e, robin_engine_finish)) {
		printf("ENGINE_set_finish_function failed\n");
		goto end;
	}

    if (!ENGINE_set_RAND(e, &robin_engine_rand)) {
		printf("ENGINE_set_default_RAND failed\n");
		goto end;
	}
    
    return 1;

end:
    return 0;
}

IMPLEMENT_DYNAMIC_CHECK_FN();
IMPLEMENT_DYNAMIC_BIND_FN(robin_engine_bind);
