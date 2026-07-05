# Use a base image with g++
FROM gcc:latest

# Set working directory inside the container
WORKDIR /app

# Copy your files into the container
COPY start.cpp .
COPY content.txt .
COPY users.txt .

# Compile your C++ code
RUN g++ start.cpp -o app

# Run the compiled program by default
CMD ["./app"]
