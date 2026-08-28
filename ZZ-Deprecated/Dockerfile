FROM ubuntu:20.04

RUN apt-get update

# Set up the basics (e.g., make, gcc and boost)
RUN apt-get install -y g++ make build-essential curl wget
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libboost-all-dev

# Set Up Java
RUN apt-get install -y openjdk-11-jdk

# Set up Rust
RUN curl https://sh.rustup.rs -sSf | bash -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

# Set up Python
RUN apt-get install -y python3 python3-pip
RUN pip3 install pylint pycodestyle pyhamcrest

# Install C++ linters
RUN pip3 install cpplint

#-------------------------------------------------------------------------------
# Set up quality of life tools
#-------------------------------------------------------------------------------

# zsh
RUN apt-get install -y zsh

ENV TERM xterm
ENV ZSH_THEME agnoster

RUN wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | zsh || true

# vim
RUN apt-get install -y vim

# General tools
# RUN cargo install hyperfine
RUN wget https://github.com/sharkdp/hyperfine/releases/download/v1.9.0/hyperfine_1.9.0_amd64.deb
RUN dpkg -i hyperfine_1.9.0_amd64.deb

# Copy in example code
COPY . /cs417-examples
WORKDIR /cs417-examples

#-------------------------------------------------------------------------------
# Time Dilation Examples
#-------------------------------------------------------------------------------
RUN make -C /cs417-examples/TimeDilation

#-------------------------------------------------------------------------------
# Semester Project Input Libraries
#-------------------------------------------------------------------------------
RUN make -C /cs417-examples/SemesterProject-CPU-Temps/cpp
# RUN cd /cs417-examples/SemesterProject-CPU-Temps/java \
 # && bash ./gradlew build jar
# RUN make -C /cs417-examples/SemesterProject-CPU-Temps/python3

#-------------------------------------------------------------------------------
# Floating Point Precision Examples
#-------------------------------------------------------------------------------
# RUN make -C /cs417-examples/FPvsArbitraryPrecision/FP-ErrorEstimate-Python
RUN make -C /cs417-examples/FPvsArbitraryPrecision/FP-ErrorEstimate-C++ 
RUN cd /cs417-examples/FPvsArbitraryPrecision/FP-ErrorEstimate-Rust \
 && cargo build
# RUN make -C /cs417-examples/SqrtExample

#-------------------------------------------------------------------------------
# Monte Carlo Examples
#-------------------------------------------------------------------------------
#RUN make -C /cs417-examples/MonteCarloIntegration

CMD ["zsh"]

