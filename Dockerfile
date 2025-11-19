FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# --- Install dependencies ---
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    curl \
    pkg-config \
    libopencv-dev \
    python3-opencv \
    dos2unix \
    && rm -rf /var/lib/apt/lists/*

# --- Fix: add missing pkg-config file for OpenCV (Darknet requires it) ---
RUN mkdir -p /usr/lib/pkgconfig && \
    echo "prefix=/usr\nexec_prefix=\${prefix}\nlibdir=/usr/lib\nincludedir=/usr/include\n\nName: opencv\nDescription: OpenCV\nVersion: 4.2.0\nLibs: -L\${libdir} -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_objdetect\nCflags: -I\${includedir}/opencv4" \
    > /usr/lib/pkgconfig/opencv.pc

# --- Clone Darknet ---
RUN git clone https://github.com/AlexeyAB/darknet.git /darknet

WORKDIR /darknet

# --- Enable OpenCV ---
RUN sed -i 's/OPENCV=0/OPENCV=1/' Makefile

# --- Build ---
RUN make -j"$(nproc)"

# --- Add YOLO run script ---
COPY ./yolo-run /usr/local/bin/yolo-run
RUN chmod +x /usr/local/bin/yolo-run

RUN dos2unix /usr/local/bin/yolo-run

# 기존
# COPY yolov3.weights /darknet/yolov3.weights

# 1. 필요한 패키지 설치
#RUN apt-get update && apt-get install -y wget ca-certificates


# 2. weights 다운로드
RUN wget --no-check-certificate https://pjreddie.com/media/files/yolov3.weights -O /darknet/yolov3.weights


RUN apt-get update && apt-get install -y curl
