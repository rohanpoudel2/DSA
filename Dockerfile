# Step 1: Use a base image with Ubuntu and required tools
FROM ubuntu:latest

# Step 2: Install essential build tools, CMake, and other dependencies
RUN apt-get update && apt-get install -y \
  build-essential \
  cmake \
  git \
  wget \
  curl \
  gdb \
  && apt-get clean

# Step 3: Set the working directory inside the container
WORKDIR /app

# Step 4: Copy the entire project (including your scripts) into the container
COPY . /app

# Step 5: Make sure the scripts are executable
RUN chmod +x ./build.sh ./run.sh ./run_tests.sh

# Step 6: Run the build script to build the project
RUN ./build.sh

# Step 7: Specify the default command to run your app (optional)
CMD ["./run.sh"]