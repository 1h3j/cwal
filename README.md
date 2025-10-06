<h1 align="center">cwal</h1>

cwal is a command-line tool for generating color palettes based on a given image. It is a tool written with simplicity in mind.

## JSON Output
By default, cwal outputs in plain text seperated by new lines, however if you instead prefer JSON output it can do that.
```
$ cwal SomeImage.jpg -jn 5
{"palette":["#35aaff","#2bf446","#8a3e83","#a39da3","#cc913f"]}
```

## Building
First, set up meson build files
```
meson setup build
```

Second, build the executable
```
cd build
ninja
```

The binary (`cwal`) should be inside `build/`
```
$ ls
build.ninja            cwal    meson-info  meson-private
compile_commands.json  cwal.p  meson-logs
```
