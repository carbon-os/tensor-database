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


## Run Tests
```bash



# Windows GPU visible to WSL?
nvidia-smi

# CUDA toolkit installed?
nvcc --version

# Which Ubuntu/WSL version
lsb_release -a
uname -r

# Any CUDA libs already present?
ldconfig -p | grep cuda




# 1. Install CUDA toolkit (Debian trixie needs the runfile, no apt repo yet)
wget https://developer.download.nvidia.com/compute/cuda/12.4.0/local_installers/cuda_12.4.0_550.54.14_linux.run
sudo sh cuda_12.4.0_550.54.14_linux.run --toolkit --silent --override

# 2. Add to PATH
echo 'export PATH=/usr/local/cuda/bin:$PATH' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH' >> ~/.bashrc
source ~/.bashrc

# 3. Enable CUDA feature in vcpkg.json — change the llama-cpp entry to:
# { "name": "llama-cpp", "features": ["cuda"] }

# 4. Rebuild
vcpkg install
cmake --build build --parallel


mkdir -p models

# ── Reasoning models ──────────────────────────────────────────────────────

# Worker: Qwen3-0.6B Q4_K_M (~397 MB) — from unsloth
wget -O models/qwen3-0.6b-q4_k_m.gguf \
  https://huggingface.co/unsloth/Qwen3-0.6B-GGUF/resolve/main/Qwen3-0.6B-Q4_K_M.gguf

# Aggregator: Qwen3-1.7B Q4_K_M (~1.11 GB) — from unsloth
wget -O models/qwen3-1.7b-instruct-q4_k_m.gguf \
  https://huggingface.co/unsloth/Qwen3-1.7B-GGUF/resolve/main/Qwen3-1.7B-Q4_K_M.gguf

# ── Embedding models ──────────────────────────────────────────────────────

# Search: nomic-embed-text-v1.5 Q4_K_M (~84 MB)
wget -O models/nomic-embed-text-v1.5.gguf \
  https://huggingface.co/nomic-ai/nomic-embed-text-v1.5-GGUF/resolve/main/nomic-embed-text-v1.5.Q4_K_M.gguf

# Classify: all-MiniLM-L6-v2 Q8_0 (~25 MB)
wget -O models/all-MiniLM-L6-v2.gguf \
  https://huggingface.co/second-state/All-MiniLM-L6-v2-Embedding-GGUF/resolve/main/all-MiniLM-L6-v2-Q8_0.gguf

# Code: jina-embeddings-v2-base-code F16 (~354 MB)
wget -O models/jina-embeddings-v2-base-code.gguf \
  https://huggingface.co/gaianet/jina-embeddings-v2-base-code-GGUF/resolve/main/jina-embeddings-v2-base-code-f16.gguf


./build/storage/storage_tests

# Embed (pick any one model to test with)
./build/inference/inference-embed-test models/nomic-embed-text-v1.5.gguf search

# Reasoning
./build/inference/inference-reasoning-test \
    models/qwen3-0.6b-q4_k_m.gguf \
    models/qwen3-1.7b-instruct-q4_k_m.gguf

./tests.sh
```