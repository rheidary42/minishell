FROM --platform=linux/amd64 ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    gdb \
    libreadline-dev \
    libncurses-dev \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m -s /bin/bash dev
USER dev
WORKDIR /home/dev/workspace

# Make .ssh folder
RUN mkdir -p /home/dev/.ssh && chmod 700 /home/dev/.ssh

# Git config
RUN git config --global user.name "Dev User" \
    && git config --global user.email "dev@example.com"

# Customize prompt
RUN echo 'export PS1="\W> "' >> /home/dev/.bashrc

ENTRYPOINT ["/bin/bash", "-lc"]
