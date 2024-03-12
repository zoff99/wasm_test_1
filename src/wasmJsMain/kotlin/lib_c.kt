@file:JsModule("./lib.c.mjs")

@JsName("default")
external object LIB_C {
    @JsName("_add")
    fun add(a: Int, b: Int): Int
}
