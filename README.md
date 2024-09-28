# Ecommerce Store Project

This project is a CLI e-commerce store written in C++ by Rohan Poudel.

## Requirements

### Without Docker

To run the project without Docker, you need the following dependencies:

1. **C++ Compiler**:
   - `g++` or `clang++` (part of `build-essential` on Linux).

2. **CMake**:
   - Version 3.8 or higher to configure and build the project.

3. **GoogleTest** (Optional, for running tests):
   - GoogleTest framework for unit testing (will be fetched during the build process).

### With Docker

If you prefer running the project using Docker, only **Docker** is required.

1. **Docker**:
   - Docker Desktop for macOS/Windows, or Docker Engine for Linux.
   - No need for any local dependencies, as Docker will provide all necessary tools within the container.

---

## How to Run the Project

### Option 1: Running Without Docker

1. **Build the project**:
   ```bash
   ./build.sh
   ```

2. **Run the project**:
   ```bash
   ./run.sh
   ```

3. **Run the tests**:
   ```bash
   ./run_tests.sh
   ```

### Option 2: Running With Docker

1. **Build the Docker image**:
   ```bash
   docker build -t ecommerce_store_image .
   ```

2. **Run the project**:
   ```bash
   docker run --rm -it ecommerce_store_image
   ```

3. **Run the tests**:
   ```bash
   docker run --rm ecommerce_store_image ./run_tests.sh
   ```

### Additional Option

You can run the project via the docker container shell
```bash
  docker run --rm -it ecommerce_store_image /bin/bash
```