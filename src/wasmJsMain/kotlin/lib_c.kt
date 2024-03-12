@file:JsModule("./lib.c.mjs")

@JsName("default")
external object LIB_C {
//    @JsName("_add")
//    fun add(a: Int, b: Int): Int

      @JsName("_wasmtoxversion")
      fun wasmtoxversion(): Int

      @JsName("_wasm_new_message_id")
      fun wasm_new_message_id(): Int

      @JsName("_wasm_tox_new")
      fun wasm_tox_new(): Int
}
