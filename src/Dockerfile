# Используем образ Ubuntu с эмуляцией x86_64
FROM --platform=linux/amd64 ubuntu:latest

# Обновляем пакеты и устанавливаем необходимые инструменты
RUN apt-get update && apt-get install -y \
    build-essential \
    valgrind \
    check \
    git \
    vim \
    gdb \
    && rm -rf /var/lib/apt/lists/*

# Устанавливаем рабочую директорию
WORKDIR /app

# Ожидаем, что код будет копироваться в контейнер через Docker Volume или Docker Copy
CMD ["/bin/bash"]
