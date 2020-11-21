#include "quickjs-libc.h"
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

  size_t buf_len;
  uint8_t *buf = js_load_file(ctx, &buf_len, argv[1]);

  JSValue val =
      JS_Eval(ctx, (const char *)buf, buf_len, argv[1], JS_EVAL_TYPE_GLOBAL);

  if (JS_IsException(val)) {
    printf("A JS excepion occured!\n");
    js_std_dump_error(ctx);
    JS_FreeValue(ctx, val);
    return 1;
  }

  switch (JS_VALUE_GET_TAG(val)) {
  case JS_TAG_INT:
    printf("%d\n", JS_VALUE_GET_INT(val));
    break;
  default:
    printf("Whatever!\n");
  }

  JS_FreeValue(ctx, val);
}