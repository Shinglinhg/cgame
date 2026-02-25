from salis import *
from glob import glob

@Target.new
def build(target: Target):
    Command("rm -rf bin").set_silent().run()
    Command("mkdir -p bin").set_silent().run()

    CCompileCommand() \
        .add_source_files("src/main.c") \
        .add_include_directories(
            *glob("src/**/"),
            "src/", "3rdparty"
        ) \
        .add_libraries("m", "X11", "GL", "Xrandr") \
        .set_pedantic() \
        .set_output_file("bin/output") \
        .set_standard("c99") \
        .run()