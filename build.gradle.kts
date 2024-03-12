import org.jetbrains.kotlin.gradle.targets.js.ir.DefaultIncrementalSyncTask
import org.jetbrains.kotlin.gradle.tasks.Kotlin2JsCompile

plugins {
    kotlin("multiplatform") version "1.9.22"
}

repositories {
    mavenCentral()
}

kotlin {
    wasmJs {
        binaries.executable()
        browser()
    }
}

val compileNativeSources by tasks.creating(Exec::class) {
    commandLine(
        "emcc", "--no-entry", "-s", "IGNORE_MISSING_MAIN=1", "-s", "MODULARIZE=1",
        "-s", "ERROR_ON_UNDEFINED_SYMBOLS=1", "-s", "LLD_REPORT_UNDEFINED", "-s", "ENVIRONMENT=web",
        "-s", "EXIT_RUNTIME=0",
        "-s", "MALLOC=emmalloc",
        "-o", "build/emcc/lib.emcc.js", "src/nativeSources/lib.c"
    )

    outputs.files("build/emcc/lib.emcc.wasm", "build/emcc/lib.emcc.js")
}

val copyNativeBinariesAndGlueCode by tasks.creating(Copy::class) {
     dependsOn(compileNativeSources)

    from("./build/emcc/lib.emcc.wasm")
    from("./build/emcc/lib.emcc.js")
    from("./src/nativeSources/lib.c.mjs")

    val taskName = if (project.hasProperty("isProduction")
        || project.gradle.startParameter.taskNames.contains("installDist")
    ) {
        "wasmJsProductionExecutableCompileSync"
    } else {
        "wasmJsDevelopmentExecutableCompileSync"
    }
    val syncTask = tasks.named<DefaultIncrementalSyncTask>(taskName)

    into(syncTask.get().destinationDirectory.get())
}

tasks.withType<Kotlin2JsCompile>().configureEach {
    dependsOn(copyNativeBinariesAndGlueCode)
}
