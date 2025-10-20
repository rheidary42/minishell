# Lightweight Debian base, amd64
FROM --platform=linux/amd64 debian:bullseye-slim

ENV DEBIAN_FRONTEND=noninteractive

# Install only what's necessary
RUN apt-get update && apt-get install -y --no-install-recommends \
	build-essential \
	git \
	gdb \
	libreadline-dev \
	libncurses-dev \
	&& rm -rf /var/lib/apt/lists/*

# Create non-root user
RUN useradd -m -s /bin/bash dev

USER dev
WORKDIR /home/dev/workspace

# Customize shell prompt
RUN echo 'export PS1="\W> "' >> /home/dev/.bashrc

ENTRYPOINT ["/bin/bash", "-lc"]
