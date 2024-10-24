# Use a base image with Ubuntu and required tools
FROM ubuntu:latest

# Install essential build tools, CMake, and other dependencies
RUN apt-get update && apt-get install -y \
  build-essential \
  cmake \
  git \
  wget \
  curl \
  gdb \
  libsqlite3-dev \
  lcov \
  && apt-get clean

# Set the working directory inside the container
WORKDIR /app

# Copy the entire project (including your scripts) into the container
COPY . /app

# Make sure the scripts are executable
RUN chmod +x ./build.sh ./run.sh ./run_tests.sh

# Run the build script to build the project
RUN ./build.sh

# Specify the default command to run your app 
CMD ["./run.sh"]