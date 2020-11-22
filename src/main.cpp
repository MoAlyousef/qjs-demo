#include <quickjs-libc.h>
#include <quickjs.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage ./main filename.js\n");
        return 1;
    }

    JSRuntime *rt = JS_NewRuntime();
    if (!rt) {
        printf("Failed to init a JS runtime!\n");
        return 1;
    }

    JSContext *ctx = JS_NewContext(rt);
    if (!ctx) {
        printf("Failed to init a JS context!\n");
        return 1;
    }

    size_t buf1_len;
    uint8_t *buf1 = js_load_file(ctx, &buf1_len, argv[1]);

    JSValue val1 = JS_Eval(ctx, (const char *)buf1, buf1_len, argv[1], JS_EVAL_TYPE_GLOBAL);

    if (JS_IsException(val1)) {
        printf("A JS excepion occured!\n");
        js_std_dump_error(ctx);
        JS_FreeValue(ctx, val1);
        return 1;
    }

    switch (JS_VALUE_GET_TAG(val1)) {
    case JS_TAG_INT:
        printf("%d\n", JS_VALUE_GET_INT(val1));
        break;
    case JS_TAG_FLOAT64:
        printf("%f\n", JS_VALUE_GET_FLOAT64(val1));
        break;
    default:
        printf("%s\n", JS_ToCString(ctx, val1));
    }

    const char *buf2 = "2 + 1";
    JSValue val2 = JS_Eval(ctx, buf2, strlen(buf2), "", JS_EVAL_TYPE_GLOBAL);

    if (JS_IsException(val2)) {
        printf("A JS excepion occured!\n");
        js_std_dump_error(ctx);
        JS_FreeValue(ctx, val2);
        return 1;
    }

    switch (JS_VALUE_GET_TAG(val2)) {
    case JS_TAG_INT:
        printf("%d\n", JS_VALUE_GET_INT(val2));
        break;
    case JS_TAG_FLOAT64:
        printf("%lf\n", JS_VALUE_GET_FLOAT64(val2));
        break;
    default:
        printf("%s\n", JS_ToCString(ctx, val2));
    }

    JS_FreeValue(ctx, val1);
    JS_FreeValue(ctx, val2);
}