# Building tensor-db

## Prerequisites

**CMake 3.22+**
```bash
sudo apt update && sudo apt install cmake -y
cmake --version
```

**Java** — required to run the ANTLR tool jar.
```bash
sudo apt install default-jdk -y
java -version
```

**C++ compiler with C++17 support**
```bash
sudo apt install build-essential -y
sudo apt-get install curl zip unzip tar pkg-config -y
```

---

## First-time setup

**1. Clone the repository**
```bash
git clone https://github.com/carbon-os/tensor-database.git
cd tensor-database
```

**2. Clone vcpkg**
```bash
git clone https://github.com/microsoft/vcpkg.git --depth 1
./vcpkg/bootstrap-vcpkg.sh

./vcpkg/vcpkg install
```

**vcpkg hash (optional)**
```bash
./vcpkg/vcpkg x-update-baseline --add-initial-baseline
```

**3. Generate the TQL parser**
```bash
cd parser
./build.sh
cd ..
```

---

## Building
```bash
cmake -B build \
  -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build --parallel
```

---

## Debug build
```bash
cmake -B build-debug \
  -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DCMAKE_BUILD_TYPE=Debug

cmake --build build-debug --parallel
```

---

## Regenerating the parser

If `TQLLexer.g4` or `TQLParser.g4` change, regenerate before building:
```bash
cd parser && ./build.sh && cd ..
cmake --build build --parallel
```

---

## Clean build
```bash
rm -rf build/
cmake -B build \
  -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build --parallel
```